#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define TABLE_SIZE 2

int *table;
int *count;
sem_t *empty, *full;
pthread_mutex_t *mutex;

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(full); 
        pthread_mutex_lock(mutex); 

        item = table[--(*count)];
        printf("Consumer consumed: %d\n", item);

        pthread_mutex_unlock(mutex); 
        sem_post(empty); 
        sleep(1); 
    }
}

int main() {
    pthread_t cons_thread;

    int shm_fd = shm_open("/shm_table", O_RDWR, 0666);
    void *shm_ptr = mmap(0, sizeof(int) * TABLE_SIZE + sizeof(int) + sizeof(sem_t) * 2 + sizeof(pthread_mutex_t),
                         PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    table = (int *)shm_ptr;
    count = (int *)(shm_ptr + sizeof(int) * TABLE_SIZE);
    empty = (sem_t *)(shm_ptr + sizeof(int) * TABLE_SIZE + sizeof(int));
    full = (sem_t *)(shm_ptr + sizeof(int) * TABLE_SIZE + sizeof(int) + sizeof(sem_t));
    mutex = (pthread_mutex_t *)(shm_ptr + sizeof(int) * TABLE_SIZE + sizeof(int) + sizeof(sem_t) * 2);

    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(cons_thread, NULL);

    return 0;
}
