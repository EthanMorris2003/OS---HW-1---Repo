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

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; 
        sem_wait(empty); 
        pthread_mutex_lock(mutex);

        table[*count] = item;
        (*count)++;
        printf("Producer produced: %d\n", item);

        pthread_mutex_unlock(mutex); 
        sem_post(full); 
        sleep(1); 
    }
}

int main() {
    pthread_t prod_thread;

    int shm_fd = shm_open("/shm_table", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(int) * TABLE_SIZE + sizeof(int) + sizeof(sem_t) * 2 + sizeof(pthread_mutex_t));
    void *shm_ptr = mmap(0, sizeof(int) * TABLE_SIZE + sizeof(int) + sizeof(sem_t) * 2 + sizeof(pthread_mutex_t),
                         PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    table = (int *)shm_ptr;
    count = (int *)(shm_ptr + sizeof(int) * TABLE_SIZE);
    empty = (sem_t *)(shm_ptr + sizeof(int) * TABLE_SIZE + sizeof(int));
    full = (sem_t *)(shm_ptr + sizeof(int) * TABLE_SIZE + sizeof(int) + sizeof(sem_t));
    mutex = (pthread_mutex_t *)(shm_ptr + sizeof(int) * TABLE_SIZE + sizeof(int) + sizeof(sem_t) * 2);

    *count = 0;
    sem_init(empty, 1, TABLE_SIZE); 
    sem_init(full, 1, 0);         
    pthread_mutex_init(mutex, NULL);

    pthread_create(&prod_thread, NULL, producer, NULL);

    pthread_join(prod_thread, NULL);

    sem_destroy(empty);
    sem_destroy(full);
    pthread_mutex_destroy(mutex);
    shm_unlink("/shm_table");

    return 0;
}