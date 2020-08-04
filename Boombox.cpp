#include <Arduino.h>
#include "pitches.h"
#include "Boombox.h"

Boombox::Boombox(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);

  _melodies[0] = {
    1,
    { NOTE_D3 },
    { 32 }
  };

  _melodies[1] = {
    8,
    { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 },
    { 4, 8, 8, 4, 4, 4, 4, 4 }
  };

  _melodies[2] = {
    17,
    {
      NOTE_A3, NOTE_E4, NOTE_B4, NOTE_C5, 0, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4,
      NOTE_F3, NOTE_C4, NOTE_G4, NOTE_A4, 0, NOTE_D4, NOTE_C4
     },
    {
      4, 4, 4, 4, 4, 4, 8, 16, 16, 4,
      4, 4, 4, 4, 4, 4, 3
    }
  };
};

void Boombox::play(uint8_t melody)  {
  if(_playing) return;
  _playing = true;
  _playingTime = millis();
  _playingMelody = melody;
  _playingNote = 0;
  tick();
};

void Boombox::tick() {
  if(_playing) {
    for (int thisNote = 0; thisNote < _melodies[_playingMelody].length; thisNote++) {
      if (thisNote == _playingNote) {
        int noteDuration = 1000 / _melodies[_playingMelody].noteDurations[thisNote];
        tone(_pin, _melodies[_playingMelody].notes[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        if (abs(millis() - _playingTime) > pauseBetweenNotes) {
          noTone(_pin);
          _nextNote(_playingMelody);
        }
        break;
      }
    }
  }
};

void Boombox::_nextNote(uint8_t melody) {
  uint8_t note = _playingNote + 1;
  if(note < _melodies[melody].length) {
    _playingTime = millis();
    _playingMelody = melody;
    _playingNote = note;
    tick();
  } else {
    _playing = false;
  }
};