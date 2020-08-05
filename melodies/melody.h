#pragma once

struct Melody {
  uint8_t length;
  uint8_t bpm;
  uint8_t nextMelody;
  int notes[32];
  uint8_t noteDurations[32];
};