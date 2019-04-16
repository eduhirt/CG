#include "SCV/stdafx.h"
#include "SCV/Counter.h"
#include "SCV/Kernel.h"

namespace scv {

Counter::Counter(double minValue, double maxValue, double startValue, double stepValue) : _startValue(startValue) {
   _minValue = minValue;
   _maxValue = maxValue;
   _currValue = startValue;
   _stepValue = stepValue;
}

Counter::~Counter(void) {
}

void Counter::setValue(double value) {
   if(value >= _maxValue) {
      _currValue = _maxValue;
   } else if (value <= _minValue) {
      _currValue = _minValue;
   } else {
      _currValue = value;
   }

   onValueChange();
}

void Counter::IncrementStep(void) {
   setValue(getValue() + getStepValue());
}
void Counter::DecrementStep(void) {
   setValue(getValue() - getStepValue());
}

} // namespace scv
