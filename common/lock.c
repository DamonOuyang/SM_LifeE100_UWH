#include "lock.h"

#include <assert.h>

LOCK lock_alloc(const char* name)
{
    int result;
    pthread_mutex_t * mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    result = pthread_mutex_init(mutex, NULL);
    assert(result == 0);
    if(result != 0) {
        lock_free(mutex);
        mutex = NULL;
    }
    return mutex;
}

void lock_free(LOCK lock)
{
    int result;
    result = pthread_mutex_destroy(lock);
    assert(result == 0);
    free(lock);
}

void lock(LOCK lock)
{
    int result;
    result = pthread_mutex_lock(lock);
    assert(result == 0);
}

void unlock(LOCK lock)
{
    int result;
    result = pthread_mutex_unlock(lock);
    assert(result == 0);
}
