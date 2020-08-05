#include <Arduino.h>
#include "Boombox.h"
#include "melodies/melody.h"
#include "melodies/melodies.cpp"

Boombox::Boombox(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);

  
};

void Boombox::play(uint8_t melody)  {
  uint8_t melodiesCount = sizeof(melodies)/sizeof(melodies[0]);
  if(melody >= melodiesCount) return;

  if(_playing) return;
  _playing = true;
  _playingTime = _currentTime;
  _playingMelody = melody;
  _playingNote = 0;
  tick();
};

void Boombox::tick() {
  _currentTime = millis();
  if(_playing) {
    for (int thisNote = 0; thisNote < melodies[_playingMelody].length; thisNote++) {
      if (thisNote == _playingNote) {
        int noteDuration = floor(60000 / melodies[_playingMelody].bpm / 8) * melodies[_playingMelody].noteDurations[thisNote];
        int pauseBetweenNotes = noteDuration * 1.30;

        if (abs(_currentTime - _playingTime) > noteDuration) {
          noTone(_pin);
          if(abs(_currentTime - _playingTime) > pauseBetweenNotes) {
            _nextNote(_playingMelody);
          }
        } else {
          tone(_pin, melodies[_playingMelody].notes[thisNote], noteDuration);
        }
        break;
      }
    }
  }
};

void Boombox::_nextNote(uint8_t melody) {
  uint8_t note = _playingNote + 1;
  if(note < melodies[melody].length) {
    _playingTime = _currentTime;
    _playingMelody = melody;
    _playingNote = note;
  } else {
    _playing = false;
   
    if(melodies[melody].nextMelody > 0) {
      play(melodies[melody].nextMelody);
    }
  }
};