#include "Barman.h"
#include "GeneralProperties.h"

Barman::Barman(GeneralProperties gp) {
  _gp = gp;
  _workMode = 0;
  _portion = 1;
  _total = 900;
  _capacity = 100;

  _slots[5] = {};

  generateData();
}

void Barman::generateData() {
  for(int i = 0; i < _gp.totalSlots; i++) {
    setSlotSprite(i, random(3));
  }
  _capacity = random(100);
  _total = 900;
}

void Barman::setPouringMode(String mode)
{
  _pouringMode = mode;
}

void Barman::setSlotSprite(int slot, int sprite) {
  _slots[slot] = sprite;
}

String Barman::getCaption() {
  if (_pouringMode == NULL)
  {
    _pouringMode = "M";
  }
  
  String caption = _pouringMode + " " + String(_portion)+ "ml/" + String(_total) + "ml";
  int spaces = floor(_gp.width / 6) - 4 - caption.length() - String(_capacity).length();

  for(int i = 0; i < spaces; i ++) {
    caption += " ";
  }

  caption += String(_capacity) + "%";
  return caption;
}

void Barman::portionIncrease() {
  _portion = min(_portion + 1, 50);
}

void Barman::portionDecrease() {
  _portion = max(_portion - 1, 0);
}

void Barman::tick() {
  
}

uint8_t * Barman::getSlots(){
  return _slots;
}

uint8_t Barman::getCapacity() {
  return _capacity;
}

uint8_t Barman::getPortion() {
  return _portion;
}