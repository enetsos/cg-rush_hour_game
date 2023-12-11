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

//include string.h
#include <iostream>
#include <string>

//include glm
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>

using namespace std;

#endif //SHARED_H
