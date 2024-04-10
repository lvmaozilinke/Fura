#pragma once

// TDll.h
#ifndef TDLL_H
#define TDLL_H

#ifdef __cplusplus
extern "C" {
#endif

	__declspec(dllexport) int add(int a, int b);

#ifdef __cplusplus
}
#endif

#endif // TDLL_H
