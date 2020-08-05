#pragma once
#include <Arduino.h>
#include "GeneralProperties.h"

class Barman {
public:
  Barman(GeneralProperties gp);

  /// Генерирует рандомное состояние девайса
  void generateData();

  /// Устанавливает спрайт для слота
  void setSlotSprite(int slot, int sprite);

  /// Получить текст для заголовка
  String getCaption();

  // Увеличить порцию
  void portionIncrease();

  // Уменьшить порцию
  void portionDecrease();

  /// Выполняется каждый цикл
  void tick();

  /// Возвращает информацию о спрайтах в слотах
  uint8_t * getSlots();

  /// Возвращает емкость аккумулятора
  uint8_t getCapacity();

  /// Возвращает порцию
  uint8_t getPortion();

private:
  /// Параметры дисплея
  GeneralProperties _gp;

  ///  Режим работы: 0 - Автоматический режим; 1 - Ручной режим
  uint8_t _workMode;

  /// Порция. Объем алкоголя наливаемый за один раз
  uint8_t _portion;

  /// Объем алкоголя налитый за "сессию"
  int _total;

  /// Процент заряда батареи.
  uint8_t _capacity;

  /// Слоты
  uint8_t _slots[5];
};