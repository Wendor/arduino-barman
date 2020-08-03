#include <lcdgfx.h>
#include <GyverEncoder.h>
#include "images/images.cpp"

DisplaySSD1306_128x32_I2C display(-1);
Encoder enc1(6, 5, 4);

const int oledWidth = 128;
const int oledHeight = 32;
const int totalSlots = 5;
const int spriteSize = 16;
const int slotSpacer = (oledWidth - spriteSize * totalSlots) / (totalSlots - 1);



int slots[totalSlots] = {};
int capacity = 0;
int part = 0;
int total = 0;

unsigned long lastDisplayTime = 0;
bool holded = false;

void setup()
{
  enc1.setType(AUTO);
  display.setFixedFont( ssd1306xled_font6x8 );
  display.begin();
  display.clear();
  Serial.begin(9600);

  generateData();
}

void loop() {
  unsigned long currentTime = millis();

  enc1.tick();
  if (enc1.isRight()) part++;
  if (enc1.isLeft()) part--;
  if (enc1.isTurn()) lastDisplayTime = 0;
  if (enc1.isHold() && !holded) {
    generateData();
  }
  holded = enc1.isHold();

  if(currentTime - lastDisplayTime < 2000) return;
  lastDisplayTime = millis();
  
  for(int i = 0; i < totalSlots; i++) {
    drawSlot(i);
  }
  
  String caption = "A " + String(part) + "ml/" + String(total) + "ml";
  int spaces = floor(oledWidth / 6) - 4 - caption.length() - String(capacity).length();

  for(int i = 0; i < spaces; i ++) {
    caption += " ";
  }

  caption += String(capacity) + "%";

  drawCaption(caption);
  drawBattery(capacity);
}

void generateData() {
  for(int i = 0; i < totalSlots; i++) {
    slots[i] = random(3);
  }
  capacity = random(100);
  total = part*random(5,50);
  lastDisplayTime = 0;
}

void drawSlot(int slot) {
  int x = slot*spriteSize + slot*slotSpacer;
  display.drawBitmap1(x, oledHeight - spriteSize, spriteSize, spriteSize, caps[slots[slot]]);
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

