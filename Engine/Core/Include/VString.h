// compile with: /EHsc /MTd /W2 /c

#ifndef V_STRING
#define V_STRING

#include "CoreAPI.h"
#include <string>

/** Simply wrap up std string */
class CORE_API String : std::string {};

#endif