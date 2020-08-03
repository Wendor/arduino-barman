#include <lcdgfx.h>
#include <GyverEncoder.h>
#include "Barman.h"
#include "GeneralProperties.h"

#include "images/images.cpp"

DisplaySSD1306_128x32_I2C display(-1);
Encoder encoder(6, 5, 4);
GeneralProperties _gp = { 128, 32, 16, 5 };

Barman barman(_gp);

unsigned long lastDisplayTime = 0;
bool forceRedraw = true;

void setup()
{
  encoder.setType(AUTO);
  display.setFixedFont( ssd1306xled_font6x8 );
  display.begin();
  display.clear();
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();

  encoder.tick();
  barman.tick();

  if (encoder.isRight()) barman.portionIncrease();
  if (encoder.isLeft()) barman.portionDecrease();

  if (encoder.isTurn()) forceRedraw = true;
  if (encoder.isClick()) {
    barman.generateData();
    forceRedraw = true;
  }

  // redraw display
  if(!forceRedraw && abs(currentTime - lastDisplayTime) < 2000) return;
  lastDisplayTime = currentTime;
  forceRedraw = false;
  
  uint8_t * slots = barman.getSlots();

  for(int i = 0; i < _gp.totalSlots; i++) {
    drawSlot(i, caps[slots[i]]);
  }
  
  drawCaption(barman.getCaption());
  drawBattery(barman.getCapacity());
}

void drawSlot(int slot, const uint8_t * cap) {
  uint8_t slotSpacer = (_gp.width - _gp.spriteSize * _gp.totalSlots) / (_gp.totalSlots - 1);
  int x = slot * _gp.spriteSize + slot * slotSpacer;
  display.drawBitmap1(x, _gp.height - _gp.spriteSize, _gp.spriteSize, _gp.spriteSize, cap);
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

  display.drawBitmap1(_gp.width - _gp.spriteSize, 0, _gp.spriteSize, _gp.spriteSize/2, batteries[current]);
}
