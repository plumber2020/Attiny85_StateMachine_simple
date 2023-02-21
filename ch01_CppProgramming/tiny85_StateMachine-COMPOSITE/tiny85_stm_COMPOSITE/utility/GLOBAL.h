/*********************************************************************//**
* \file			GLOBAL.h		                                              
* \created      8/24/2022                                                      
* \author       abramov_da   
* \brief		
*
*
*************************************************************************/


#ifndef __GLOBAL_H__
#define __GLOBAL_H__


#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

/** \ingroup	MATH_STRUCTURE
*////@{

void* operator new(size_t size);						///< operator new
void* operator new[](size_t size);						///< operator new[]
void  operator delete(void* ptr);						///< operator delete
void  operator delete(void* ptr, unsigned);				///< operator delete
void  operator delete[](void* ptr);						///< operator delete[]
void  operator delete[](void* ptr, unsigned);			///< operator delete[]

__extension__ typedef int __guard __attribute__((mode (__DI__)));
extern "C" int  __cxa_guard_acquire(__guard*);
extern "C" void __cxa_guard_release(__guard*);
extern "C" void __cxa_guard_abort(__guard*);
extern "C" void __cxa_pure_virtual(void);

///@}

#endif //__GLOBAL_H__

