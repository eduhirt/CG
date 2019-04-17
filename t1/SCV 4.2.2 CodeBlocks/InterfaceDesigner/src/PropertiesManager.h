#ifndef __PROPERTIES_MANAGER_H__
#define __PROPERTIES_MANAGER_H__

#include "Properties.h"
#include "SpecializedProperties.h"
#include "CodeGenerator.h"

class PropertiesManager {
public:
   static Properties *getProperties(scv::Component *object) {
       /*SCV 4.2.0*/
      /*CountersProperties::Singleton<CountersProperties>::getInstance()->setVisible(false);
      StringsProperties::Singleton<StringsProperties>::getInstance()->setVisible(false);
      StatesProperties::Singleton<StatesProperties>::getInstance()->setVisible(false);
      InternalFrameProperties::Singleton<InternalFrameProperties>::getInstance()->setVisible(false);
      ImageProperties::Singleton<ImageProperties>::getInstance()->setVisible(false);
      FrameProperties::Singleton<FrameProperties>::getInstance()->setVisible(false);*/
        /*SCV 4.2.1*/
      Singleton<CountersProperties>::getInstance()->setVisible(false);
      Singleton<StringsProperties>::getInstance()->setVisible(false);
      Singleton<StatesProperties>::getInstance()->setVisible(false);
      Singleton<InternalFrameProperties>::getInstance()->setVisible(false);
      Singleton<ImageProperties>::getInstance()->setVisible(false);
      Singleton<FrameProperties>::getInstance()->setVisible(false);


      Properties::getInstance()->setVisible(false);


      if (dynamic_cast<scv::Slider*>(object) || dynamic_cast<scv::Spinner*>(object)) {
         _curr = Singleton<CountersProperties>::getInstance();
      } else if (dynamic_cast<scv::Button*>(object) || dynamic_cast<scv::Label*>(object) || dynamic_cast<scv::TextField*>(object) || dynamic_cast<scv::TextBox*>(object)) {
         _curr = Singleton<StringsProperties>::getInstance();
      }  else if (dynamic_cast<scv::CheckBox*>(object) || dynamic_cast<scv::RadioButton*>(object) || dynamic_cast<scv::ToggleButton*>(object)) {
         _curr = Singleton<StatesProperties>::getInstance();
      }  else if (dynamic_cast<scv::InternalFrame*>(object)) {
         if (static_cast<scv::InternalFrame*>(object) == CodeGenerator::getInstance()->getSCVFrame()) {
            _curr = Singleton<FrameProperties>::getInstance();
         } else {
            _curr = Singleton<InternalFrameProperties>::getInstance();
         }
      } else if (dynamic_cast<scv::Image*>(object)) {
         _curr = Singleton<ImageProperties>::getInstance();
      }  else {
         _curr = Properties::getInstance();
      }

      getCurr()->setVisible(true);
      return getCurr();
   }

   static Properties *getCurr(void) {
      if (_curr == NULL) _curr = Properties::getInstance();
      return _curr;
   }

protected:
   static Properties *_curr;
};

#endif //__PROPERTIES_MANAGER_H__
