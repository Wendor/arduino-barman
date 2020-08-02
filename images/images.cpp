#include "caps/cap1.cpp"
#include "caps/nocap.cpp"
#include "caps/fullcap.cpp"

#include "battery/battery0.cpp"
#include "battery/battery25.cpp"
#include "battery/battery50.cpp"
#include "battery/battery75.cpp"
#include "battery/battery100.cpp"

const uint8_t * caps[] = { nocap, cap1, fullcap };
const uint8_t * batteries[] = { battery0, battery25, battery50, battery75, battery100 };
