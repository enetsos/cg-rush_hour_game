#pragma once
#ifndef SHARED_H
#define SHARED_H
/////////////
// VERSION //
/////////////

// Generic info:
#define LIB_NAME      "Game Engine v0.1"  ///< Library credits
#define LIB_VERSION   10                              ///< Library version (divide by 10)

#ifdef _WINDOWS
   // Export API:
   // Specifies i/o linkage (VC++ spec):
#ifdef ENGINE_EXPORTS
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif
#else // Under Linux
#define LIB_API  // Dummy declaration
#endif

#include <glm.cpp>
#include <gtx/string_cast.cpp>
#include <gtc/matrix_transform.cpp>
#include <gtc/type_ptr.cpp>
using namespace std;

#endif //SHARED_H
