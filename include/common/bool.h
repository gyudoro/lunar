#ifndef COMMON_BOOL_H
#define COMMON_BOOL_H

#include "common/types.h"

#ifdef __STDC_VERSION__
#if __STDC_VERSION__ > 202200

#define __NO_BOOLEAN__

#endif
#endif

#undef bool
#undef true
#undef false

#ifndef __NO_BOOLEAN__

typedef u8 bool;

#define true 1
#define false 0

#else

#undef __NO_BOOLEAN__

#endif

#endif /* COMMON_BOOL_H */
