#include "SCV/stdafx.h"
#include "SCV/StateButton.h"
#include "SCV/Kernel.h"

namespace scv {

StateButton::StateButton(bool state) {
   _state = state;
   _buttonGroup = NULL;
}

bool StateButton::getState(void) const {
   return _state;
}

void StateButton::setState(bool state) {
   _state = state;
   if (_buttonGroup != NULL) _buttonGroup->update(this);
   onValueChange();
}

void StateButton::registerButtonGroup(ButtonGroup *buttonGroup) {
   _buttonGroup = buttonGroup;
   _buttonGroup->_componentsArray.push_back(this);
}

} // namespace scv
