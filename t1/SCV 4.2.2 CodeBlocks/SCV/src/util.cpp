#include "SCV/stdafx.h"
#include "SCV/util.h"

namespace scv {

std::string trim(const std::string &str) {
   std::string result(str);
   result.erase(result.find_last_not_of( " " ) + 1);
   result.erase(0, result.find_first_not_of( " " ));
   return result;
}

} //namespace scv
