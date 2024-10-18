#ifndef SHARED_H
#define SHARED_H

#include <pthread.h>
#include <semaphore.h>

#define TABLE_SIZE 2

extern int table[TABLE_SIZE];
extern int count;

extern sem_t empty;
extern sem_t full;
extern pthread_mutex_t mutex;

#endif