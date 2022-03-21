#ifndef _LOCK_H_
#define _LOCK_H_

#include "lock_def.h"

#ifdef __cplusplus
extern "C"{
#endif

LOCK lock_alloc(const char* name);
void lock_free(LOCK lock);

void lock(LOCK lock);
void unlock(LOCK lock);

#ifdef __cplusplus
}
#endif

#endif
