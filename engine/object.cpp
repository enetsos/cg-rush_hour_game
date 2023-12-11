#include "object.h"
int LIB_API Object::current_id = 0;

/**
* LIB_API is used to export/import functions and classes from/to the DLL.
* int LIB_API Object::current_id = 0 --> it initializes the static variable current_id to 0.
*/