#include "SCV/stdafx.h"
#include "SCV/ButtonGroup.h"
#include "SCV/StateButton.h"

namespace scv {

void ButtonGroup::update(StateButton *ptr) {
   for (int i = 0; i < (int)_componentsArray.size(); i++)
      _componentsArray[i]->_state = false;
   ptr->_state = true;
}

int ButtonGroup::getActive(void) {
   for (int i = 0; i < (int)_componentsArray.size(); i++) {
      if (_componentsArray[i]->getState()) return i;
   }
   return -1;
}

} // namespace scv
