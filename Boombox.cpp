#include <Arduino.h>
#include "Boombox.h"
#include "melodies/melody.h"
#include "melodies/melodies.cpp"

Boombox::Boombox(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
};

void Boombox::play(uint8_t melody)  {
  if(melody >= 10) return;

  if(_playing) return;
  _playing = true;
  _playingTime = _currentTime;
  memcpy_P(&_playingMelody, &melodies[melody], sizeof(_playingMelody));
  _playingNote = 0;
  tick();
};

bool Boombox::isPlaying(){
  return _playing;
}

void Boombox::tick() {
  _currentTime = millis();
  if(_playing) {
    for (int thisNote = 0; thisNote < _playingMelody.length; thisNote++) {
      if (thisNote == _playingNote) {
        int noteDuration = floor(60000 / _playingMelody.bpm / 8) * _playingMelody.noteDurations[thisNote];
        int pauseBetweenNotes = noteDuration * 1.30;

        if (abs(_currentTime - _playingTime) > noteDuration) {
          noTone(_pin);
          if(abs(_currentTime - _playingTime) > pauseBetweenNotes) {
            _nextNote();
          }
        } else {
          tone(_pin, _playingMelody.notes[thisNote], noteDuration);
        }
        break;
      }
    }
  }
};

void Boombox::_nextNote() {
  uint8_t note = _playingNote + 1;
  if(note < _playingMelody.length) {
    _playingTime = _currentTime;
    _playingNote = note;
  } else {
    _playing = false;
   
    if(_playingMelody.nextMelody > 0) {
      play(_playingMelody.nextMelody);
    }
  }
};