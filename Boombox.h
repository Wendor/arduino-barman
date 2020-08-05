#pragma once
#include <Arduino.h>

class Boombox {
  public:
    Boombox(uint8_t pin);
    void tick();
    void play(uint8_t melody);
  private:
    uint8_t _pin;
    unsigned long _toneStart;
    bool _playing;
    uint8_t _playingMelody;
    uint8_t _playingNote;
    unsigned long _playingTime;
    void _nextNote(uint8_t melody);
    unsigned long _currentTime;
};
