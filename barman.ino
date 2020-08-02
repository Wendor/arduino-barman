#include <lcdgfx.h>
#include "images/images.cpp"

DisplaySSD1306_128x32_I2C display(-1);

const int oledWidth = 128;
const int oledHeight = 32;
const int totalSlots = 5;
const int spriteSize = 16;
const int slotSpacer = (oledWidth - spriteSize * totalSlots) / (totalSlots - 1);

void setup()
{
  display.setFixedFont( ssd1306xled_font6x8 );
  display.begin();
  display.clear();
}

void loop() {
  for(int i = 0; i < totalSlots; i++) {
    drawSlot(caps[random(3)], i);  
  }

  int part = 5 + random(10)*5;
  int total = random(5,50)*part;
  int capacity = random(100);
  String caption = "A " + String(part) + "ml/" + String(total) + "ml";
  int spaces = floor(oledWidth / 6) - 4 - caption.length() - String(capacity).length();

  for(int i = 0; i < spaces; i ++) {
    caption += " ";
  }

  caption += String(capacity) + "%";

  drawCaption(caption);
  drawBattery(capacity);
  delay(1000);
}

void drawSlot(const uint8_t bitmap[], int slot) {
  int x = slot*spriteSize + slot*slotSpacer;
  display.drawBitmap1(x, oledHeight - spriteSize, spriteSize, spriteSize, bitmap);
}

void drawCaption(String text) {
     display.printFixed(0, 0, text.c_str());
}

void drawBattery(int capacity) {
  int current = 4;
  if(capacity <= 75) current = 3;
  if(capacity <= 50) current = 2;
  if(capacity <= 25) current = 1;
  if(capacity <= 5) current = 0;

  display.drawBitmap1(oledWidth - spriteSize, 0, spriteSize, spriteSize/2, batteries[current]);
}

