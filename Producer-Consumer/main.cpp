#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <semaphore.h>
#include <fstream>
#include <string> 
#include <chrono>
#include "buffer.h"
#include "thread"
#include <atomic>

using namespace std;

bool trackCompletion = true;
std::chrono::time_point<std::chrono::system_clock> start;

void inputFiles();

int insert_item(buffer_item item) 
{
    // wait until there is at least one empty spot in the buffer, then decrement empty
    sem_wait(&sem_empty);

    // get the lock
    pthread_mutex_lock(&mutex);

    // Insert item into the buffer
    buffer[in] = item;

    // increment in (circular queue)
    in = (in + 1) % BUFFER_SIZE;

    // release the lock
    pthread_mutex_unlock(&mutex);

    // increment (signal full)
    sem_post(&full);

    return 0;
}

int remove_item(buffer_item *item) 
{
    // wait until there is at least one full slot in the buffer, then decrement full
    sem_wait(&full);

    // get the lock
    pthread_mutex_lock(&mutex);

    // Retrieve the item from the buffer
    *item = buffer[out];

    // increment out (circular queue)
    out = (out + 1) % BUFFER_SIZE;

    // release the lock
    pthread_mutex_unlock(&mutex);

    // increment (signal empty)
    sem_post(&sem_empty); 

    return 0;
}

void *producer(void *param) {
    buffer_item item;

    while (trackCompletion) 
    {
        // Sleep for a random period of time
        sleep(rand() % 100 * 0.01); 
        

        // Generate a random number
        item = rand(); 
        
        
        if (insert_item(item) != 0) {
            cout << "Error!" << endl;
        }
        else 
        {
            cout << "Producer produced " << item << endl;
        }
        
    }

    pthread_exit(0);
    return nullptr;
}

void *consumer(void *param) {
    buffer_item item;

    while (trackCompletion) 
    {
        // Sleep for a random period of time
        sleep(rand() % 100 * 0.01); 

        if (remove_item(&item) != 0) {
            cout << "Error!" << endl;
        }
        else 
        {
           cout << "Consumer consumed " << item << endl;
        }

    }

    pthread_exit(0);
    return nullptr;
}

int main(int argc, char *argv[]) {
    // only allow for 4 arguments
    if (argc != 4) {
        cout << "Error! Incorrect number of arguments" << endl;
        return -1;
    }

    srand(time(NULL));

    //get argv[1], argv[2], and argv[3] from the command line
    int total_sleep_time = atoi(argv[1]);
    int total_producers = atoi(argv[2]);
    int total_consumers = atoi(argv[3]);


    // Initialize the buffer, already done in buffer.h
    // Initialize semaphores and mutex
    sem_init(&sem_empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads 
    pthread_t producers[total_producers];
    pthread_t consumers[total_consumers];

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < total_producers; i++) 
    {
        pthread_create(&producers[i], NULL, producer, NULL);  
    }

    for (int i = 0; i < total_consumers; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    // Sleep
    sleep(total_sleep_time);

    trackCompletion = false;

    // Join threads
    /*for (int i = 0; i < total_producers; i++) {
        pthread_join(producers[i], NULL);
        cout << i << endl;
    }

    for (int i = 0; i < total_consumers; i++) {
        pthread_join(consumers[i], NULL);
        cout << i << endl;
    }*/

   //calculate overall turnaroundtime
    auto overall_turnAround_time = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start);
    cout << "Finished: Sleep time = " << total_sleep_time
         << ", Producers = " << total_producers
         << ", Consumers = " << total_consumers 
         << " Overall Turnaround Time = " << overall_turnAround_time.count() << " miliseconds" << endl;


    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem_empty);
    sem_destroy(&full);

    // Check if user wants to read input files and print results to output file
    char userInput = ' ';
    cout << "Would you like to read from the input files and print the results to the output files? (Y) Yes or (N) No: ";
    cin >> userInput;
    if (userInput == 'Y' || userInput == 'y') {
        inputFiles();
    } 
    else 
    {
        cout << "DONE!" << endl;
    }

    //Exit
    //pthread_exit(0);
    exit(0);
    return 0;
}

//read input files and display results with test cases in other output files
void inputFiles() 
{
    ifstream input;
    ofstream output;
    string title = "";
    for(int i = 2; i < 8; i= i+2)
    {
        int total_sleep_time = 0;
        int total_producers = 0;
        int total_consumers = 0;
        input.open("sleep_" + to_string(i) + ".txt");
        getline(input, title);

        output.open("output_sleep_" + to_string(i) + ".txt");
        output << title << endl;
        for(int i = 0; i < 12; i++)
        {
            input >> total_sleep_time;
            input >> total_producers;
            input >> total_consumers;

            
            srand(time(NULL));

            // Initialize the buffer, already done in buffer.h
            // Initialize semaphores and mutex
            sem_init(&sem_empty, 0, BUFFER_SIZE);
            sem_init(&full, 0, 0);
            pthread_mutex_init(&mutex, NULL);

            // Create producer and consumer threads 
            pthread_t producers[total_producers];
            pthread_t consumers[total_consumers];

            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < total_producers; i++) 
            {
                pthread_create(&producers[i], NULL, producer, NULL);  
            }

            for (int i = 0; i < total_consumers; i++) 
            {
                pthread_create(&consumers[i], NULL, consumer, NULL);
            }

            // Sleep
            sleep(total_sleep_time);

            trackCompletion = false;

            // Join threads
            /*for (int i = 0; i < numProducers; i++) {
            pthread_join(producers[i], NULL);
            cout << i << endl;
            }

            for (int i = 0; i < numConsumers; i++) {
            pthread_join(consumers[i], NULL);
            cout << i << endl;
            }*/

            //calculate overall turnaroundtime
            auto overall_turnAround_time = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start);
            output << "Finished: Sleep time = " << total_sleep_time
                    << ", Producers = " << total_producers
                    << ", Consumers = " << total_consumers 
                    << " Overall Turnaround Time = " << overall_turnAround_time.count() << " miliseconds" << endl;


            pthread_mutex_destroy(&mutex);
            sem_destroy(&sem_empty);
            sem_destroy(&full);
        }

        input.close();
        output.close();
        
    }
    //pthread_exit(0);
}














































//References
//https://www.youtube.com/watch?v=Qx3P2wazwI0&t=636s
//https://www.geeksforgeeks.org/chrono-in-c/
//https://www.youtube.com/watch?v=r2Hec8YBfXA
//https://www.youtube.com/watch?v=l6zkaJFjUbM
//https://andrew128.github.io/ProducerConsumer/
//https://github.com/sicKitchen/Producer-Consumer-Problem/tree/master

