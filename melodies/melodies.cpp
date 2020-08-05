#include "pitches.h"
#include "melody.h"

static const Melody melodies[9] PROGMEM = {
  /// 0 - Beep
  {
    1, 240, 0,
    { NOTE_D3 },
    { 1 }
  },
  /// 1 - Деревня дураков 1
  {
    28, 160, 2,
    {
      NOTE_GS6, NOTE_AS6, NOTE_GS6, NOTE_G6, NOTE_GS6, NOTE_AS6, NOTE_C7, NOTE_CS7,
      NOTE_DS7, NOTE_C7, NOTE_C7, NOTE_C7, NOTE_C7, NOTE_C7, 0,
      NOTE_CS7, NOTE_CS7, NOTE_CS7, NOTE_CS7, NOTE_CS7, 0,
      NOTE_DS7, NOTE_C7, NOTE_C7, NOTE_C7, NOTE_C7, NOTE_C7, 0
    },
    {
      2,2,2,2,2,2,2,2,
      4,4,1,1,1,1,8,
      4,1,1,1,1,4,
      4,4,1,1,1,1,4
    }
  },
  /// 2 - Деревня дураков 2
  {
    26, 160, 0,
    {
      NOTE_GS6, NOTE_AS6, NOTE_GS6, NOTE_G6, NOTE_GS6, NOTE_AS6, NOTE_C7, NOTE_CS7,
      NOTE_DS7, NOTE_C7, NOTE_C7, NOTE_C7, NOTE_C7, NOTE_C7, 0,
      NOTE_D7, NOTE_C7, NOTE_AS6, NOTE_D7, NOTE_C7, NOTE_AS6,
      NOTE_DS7, NOTE_DS7, NOTE_DS7, NOTE_DS7, NOTE_DS7
    },
    {
      2,2,2,2,2,2,2,2,
      4,4,1,1,1,1,4,
      2,2,4,2,2,4,
      1,1,1,1,1
    }
  },
  /// 3 - В питере пить
  {
    21, 72, 0,
    {
      NOTE_A5, NOTE_GS5, NOTE_FS5, NOTE_B5, 0, NOTE_GS5, NOTE_FS5, NOTE_F5, NOTE_FS5, 0,
      NOTE_CS6, NOTE_B5, NOTE_A5, NOTE_D6, 0, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_A5
      },
    {
      4,2,1,1,8,4,2,1,1,8,
      4,1,2,1,8,1,1,1,1,2,8
    }
  },
  /// 4 - Рюмка водки!
  {
    24, 74, 0,
    {
      NOTE_A5, NOTE_G5, 0, NOTE_B5, NOTE_B5, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_FS5, NOTE_G5, 0,
      NOTE_A5, NOTE_B5, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_B5, NOTE_A5, NOTE_A5, NOTE_G5
    },
    {
      4, 6, 10, 2, 1, 3, 2, 2, 1, 7, 2,
      1, 1, 2, 2, 1, 2, 2, 1, 6, 4, 4, 4, 4
    }
  },
  /// 5 - Battle City (танчики)
  {
    30, 140, 0,
    {
      NOTE_C6, NOTE_D6, NOTE_DS6, NOTE_C6, NOTE_D6, NOTE_DS6, NOTE_DS6, NOTE_F6,
      NOTE_G6, NOTE_DS6, NOTE_F6, NOTE_G6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_F6,
      NOTE_G6, NOTE_A6, NOTE_GS6, NOTE_AS6, NOTE_C7, NOTE_GS6, NOTE_AS6, NOTE_C7,
      NOTE_C7, 0, NOTE_C7, NOTE_C7, NOTE_C7, NOTE_C7
    },
    {
      2,2,2,2,2,2,2,2,
      2,2,2,2,2,2,2,2,
      2,2,2,2,2,2,2,2,
      2,4,2,2,2,2
    }
  },
  /// 6 - Star Wars - Cantina 1
  {
    31, 160, 7,
    {
      NOTE_A5, NOTE_D6, NOTE_A5, NOTE_D6,
      NOTE_A5, NOTE_D6, NOTE_A5, 0, NOTE_GS5, NOTE_A5,
      NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_G5, 0, NOTE_FS5, NOTE_G5, NOTE_FS5,
      NOTE_F5, NOTE_D5, 0,
      NOTE_A5, NOTE_D6, NOTE_A5, NOTE_D6,
      NOTE_A5, NOTE_D6, NOTE_A5, 0, NOTE_GS5, NOTE_A5
    },
    {
      4,4,4,4,
      2,4,2,2,2,4,
      2,2,2,2,2,2,2,2,
      6,2,8,
      4,4,4,4,
      2,4,2,2,2,4
    }
  },
  /// 7 - Star Wars - Cantina 2
  {
    31, 160, 8,
    {
      NOTE_G5, 0, NOTE_G5, 0, NOTE_FS5, NOTE_G5,
      NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_G5,
      NOTE_A5, NOTE_D6, NOTE_A5, NOTE_D6,
      NOTE_A5, NOTE_D6, NOTE_A5, 0, NOTE_GS5, NOTE_A5,
      NOTE_C6, 0, NOTE_C6, 0, NOTE_A5, NOTE_G5,
      NOTE_F5, NOTE_D5, 0,
      NOTE_D5, NOTE_F5,
    },
    {
      2,2,4,2,2,4,
      2,4,4,6,
      4,4,4,4,
      2,4,2,2,2,4,
      2,2,4,2,2,4,
      6,2,8,
      8,8
    }
  },
  /// 8 - Star Wars - Cantina 3
  {
    7, 160, 0,
    {
      NOTE_A5, NOTE_C6,
      NOTE_DS6, NOTE_D6, NOTE_GS5, NOTE_A5, NOTE_F5
    },
    {
      8,8,
      4,4,2,4,2
    }
  }
};
