#pragma once

#ifdef GRAY_BUILD_DLL
	#define  GRAY_API __declspec(dllexport)
#else
	#define GRAY_API __declspec(dllimport)
#endif