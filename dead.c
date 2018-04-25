#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/time.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

    void *function1()
    {

           pthread_mutex_lock(&lock1);
           sleep(1);
           pthread_mutex_lock(&lock2);           
           printf("first2\n");
           pthread_mutex_unlock(&lock2);
           pthread_mutex_unlock(&lock1);

    } 
    void *function2(){

           pthread_mutex_lock(&lock2); 
           sleep(1);
           pthread_mutex_lock(&lock1);
           printf("second\n");
           pthread_mutex_unlock(&lock1);
           pthread_mutex_unlock(&lock2);
        
    } 
  
    int main()
    {
       pthread_t thread1;
       pthread_t thread2;
       pthread_create(&thread1, NULL, function1, NULL);
       pthread_create(&thread2, NULL, function2, NULL);
    
    pthread_join(thread1,0);
    pthread_join(thread2,0);
    }