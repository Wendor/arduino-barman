#include <lcdgfx.h>
#include <GyverEncoder.h>
#include "Barman.h"
#include "GeneralProperties.h"
#include "Boombox.h"

#include "images/images.cpp"

DisplaySSD1306_128x32_I2C display(-1);
Encoder encoder(6, 5, 4);
GeneralProperties _gp = { 128, 32, 16, 5 };

Barman barman(_gp);
Boombox boombox(A3);

unsigned long lastDisplayTime = 0;
bool forceRedraw = true;

enum states { initialyzing, working, pouring, tuningCount, volumeTuning, modeSelecting };
enum pouringModes { automatic, manual };
states state;
pouringModes pouringMode;

const char *modeItemsMenu[] = {
    "Automatic",
    "Manual"
};
SAppMenu menu;
bool isShowMenu = false;

void setup()
{
  encoder.setType(AUTO);
  display.setFixedFont( ssd1306xled_font6x8 );
  display.begin();
  display.clear();
  state = initialyzing;
  Serial.begin(9600);
  boombox.play(5);
};

void loop() {
  switch (state)
  {
    case initialyzing:
      initialyzingAct();
      break;

    case working:
      workingAct();
      break;

    case pouring:
      /* code */
      break;

    case volumeTuning:
      tuningVolumeAct();
      break;
    
    case modeSelecting:
      modeSelectingAct();
      break;

    default:
      break;
  }
  
}

void initialyzingAct()
{
  if (lastDisplayTime < 1)
  {
    lastDisplayTime = millis();
  }
  boombox.tick();
  if (!boombox.isPlaying() || encoder.isClick())
  {
    display.clear();
    state = volumeTuning;
    forceRedraw = true;
    return;
  }
  if (forceRedraw)
  {
    display.setFixedFont( ssd1306xled_font8x16 );
    display.printFixed(0, 0, "Hello");
    forceRedraw = false;
  }
}

void workingAct()
{
  display.setFixedFont( ssd1306xled_font6x8 );
  unsigned long currentTime = millis();

  encoder.tick();
  barman.tick();
  boombox.tick();

  if (encoder.isRight()) barman.portionIncrease();
  if (encoder.isLeft()) barman.portionDecrease();

  if (encoder.isDouble())
  {
    ChangeState(volumeTuning);
    return;
  }
  

  if (encoder.isTurn()) {
    forceRedraw = true;
    boombox.play(0);
  }
  if (encoder.isClick()) {
    barman.generateData();
    forceRedraw = true;
    boombox.play(barman.getPortion());
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

void tuningVolumeAct()
{
  display.setFixedFont( ssd1306xled_font6x8 );
  unsigned long currentTime = millis();

  encoder.tick();
  barman.tick();
  boombox.tick();

  if (encoder.isRight()) barman.portionIncrease();
  if (encoder.isLeft()) barman.portionDecrease();

  if (encoder.isTurn()) {
    forceRedraw = true;
    boombox.play(0);
  }
  if (encoder.isClick()) {
    ChangeState(modeSelecting);
    return;
  }

  // redraw display
  if(!forceRedraw && abs(currentTime - lastDisplayTime) < 2000) return;
  lastDisplayTime = currentTime;
  forceRedraw = false;
  
  drawCaption(barman.getCaption());
  drawInfo("Please select", 16);
  drawInfo("volume of cup", 24);
  drawBattery(barman.getCapacity());
}

void modeSelectingAct()
{
  if (!isShowMenu)
  {
    display.createMenu( &menu, modeItemsMenu, sizeof(modeItemsMenu) / sizeof(char *), {10, 10, 120, 15} );
    display.showMenu( &menu );
    drawCaption(barman.getCaption());
    isShowMenu = true;
  }
  drawBattery(barman.getCapacity());
  encoder.tick();
  if (encoder.isLeft())
  {
    display.menuDown(&menu);
    display.updateMenu(&menu);
  }
  if (encoder.isRight())
  {
    display.menuUp(&menu);
    display.updateMenu(&menu);
  }
  if (encoder.isClick())
  {
    switch (display.menuSelection(&menu))
    {
    case 0:
      pouringMode = automatic;
      break;
    case 1:
      pouringMode = manual;
      break;
    default:
      break;
    }
    isShowMenu = false;
    ChangeState(working);
  }
  
  
  
}

void drawSlot(int slot, const uint8_t * cap) {
  uint8_t slotSpacer = (_gp.width - _gp.spriteSize * _gp.totalSlots) / (_gp.totalSlots - 1);
  int x = slot * _gp.spriteSize + slot * slotSpacer;
  display.drawBitmap1(x, _gp.height - _gp.spriteSize, _gp.spriteSize, _gp.spriteSize, cap);
}

void drawCaption(String text) {
  display.printFixed(0, 0, text.c_str());
}

void drawInfo(String text, lcdint_t yPosition) {
  display.printFixed(0, yPosition, text.c_str());
}

void drawBattery(int capacity) {
  int current = 4;
  if(capacity <= 75) current = 3;
  if(capacity <= 50) current = 2;
  if(capacity <= 25) current = 1;
  if(capacity <= 5) current = 0;

  display.drawBitmap1(_gp.width - _gp.spriteSize, 0, _gp.spriteSize, _gp.spriteSize/2, batteries[current]);
}

void ChangeState(states newState)
{
  state = newState;
  display.clear();
  boombox.stop();
  forceRedraw = true;
}