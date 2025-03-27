#include <semaphore.h>
#include <pthread.h>

typedef int buffer_item;
#define BUFFER_SIZE 5

//declare and initialize buffer
buffer_item buffer[BUFFER_SIZE];

// Declare empty and full semaphores as well as the mutex lock
sem_t sem_empty, full;
pthread_mutex_t mutex;

int in = 0; // Index in the buffer where a producer can produce next
int out = 0; // Index in the buffer from where a consumer can consume