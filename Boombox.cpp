#include <Arduino.h>
#include "pitches.h"
#include "Boombox.h"

Boombox::Boombox(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);

  /// Beep
  _melodies[0] = {
    1,
    { NOTE_D3 },
    { 32 }
  };

  /// хз
  _melodies[1] = {
    8,
    { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 },
    { 4, 8, 8, 4, 4, 4, 4, 4 }
  };

  /// Californication
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

  /// В питере пить
  _melodies[3] = {
    16,
    {
      NOTE_A5, NOTE_GS5, NOTE_FS5, NOTE_FS5, 0, NOTE_A5, NOTE_GS5, NOTE_FS5, NOTE_B5, 0,
      NOTE_GS5, NOTE_GS5, NOTE_GS5, NOTE_GS5, NOTE_GS5, NOTE_FS5,
     },
    {
      8, 8, 8, 8, 4, 8, 8, 8, 8, 2,
      8, 8, 8, 8, 4, 4
    }
  };

  /// Рюмка водки!
  _melodies[4] = {
    24,
    {
      NOTE_A5, NOTE_G5, 0, NOTE_B5, NOTE_B5, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_FS5, NOTE_G5, 0,
      NOTE_A5, NOTE_B5, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_B5, NOTE_A5, NOTE_A5, NOTE_G5
     },
    {
      2, 3, 2, 4, 8, 4, 3, 4, 8, 4, 2,
      8, 8, 4, 4, 8, 4, 4, 8, 1, 2, 2, 2, 2
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

bool Boombox::isPlaying(){
  return _playing;
}

void Boombox::tick() {
  if(_playing) {
    for (int thisNote = 0; thisNote < _melodies[_playingMelody].length; thisNote++) {
      if (thisNote == _playingNote) {
        int noteDuration = 1000 / _melodies[_playingMelody].noteDurations[thisNote];
        int pauseBetweenNotes = noteDuration * 1.30;
        if (abs(millis() - _playingTime) > pauseBetweenNotes) {
          noTone(_pin);
          if(abs(millis() - _playingTime) - pauseBetweenNotes > 20) {
            _nextNote(_playingMelody);
          }
        } else {
          tone(_pin, _melodies[_playingMelody].notes[thisNote], noteDuration);
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
    //tick();
  } else {
    _playing = false;
  }
};