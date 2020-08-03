#pragma once
#include <Arduino.h>

struct Melody {
  uint8_t length;
  int notes[8];
  uint8_t noteDurations[8];
};

class Boombox {
  public:
    Boombox(uint8_t pin);
    void tick();
    void play(uint8_t melody);
  private:
    uint8_t _pin;
    unsigned long _toneStart;
    Melody _melodies[1];
    bool _playing;
    uint8_t _playingMelody;
    uint8_t _playingNote;
    unsigned long _playingTime;
    void _nextNote(uint8_t melody);
};
