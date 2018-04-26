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
pthread_mutex_t lock3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock4 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock5 = PTHREAD_MUTEX_INITIALIZER;


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
           pthread_mutex_lock(&lock3);
           printf("second\n");
           pthread_mutex_unlock(&lock3);
           pthread_mutex_unlock(&lock2);
        
    } 
    void *function3(){

           pthread_mutex_lock(&lock3); 
           sleep(1);
           pthread_mutex_lock(&lock4);
           printf("third\n");
           pthread_mutex_unlock(&lock4);
           pthread_mutex_unlock(&lock3);
        
    }
    void *function4(){

           pthread_mutex_lock(&lock4); 
           sleep(1);
           pthread_mutex_lock(&lock5);
           printf("fourth\n");
           pthread_mutex_unlock(&lock5);
           pthread_mutex_unlock(&lock4);
        
    } 
    
    void *function5(){

           pthread_mutex_lock(&lock5); 
           sleep(1);
           pthread_mutex_lock(&lock1);
           printf("fifth\n");
           pthread_mutex_unlock(&lock1);
           pthread_mutex_unlock(&lock5);
        
    } 
    int main()
    {
       pthread_t thread1;
       pthread_t thread2;
       pthread_t thread3;
       pthread_t thread4;
       pthread_t thread5;
       pthread_create(&thread1, NULL, function1, NULL);
       pthread_create(&thread2, NULL, function2, NULL);
       pthread_create(&thread3, NULL, function3, NULL);
       pthread_create(&thread4, NULL, function4, NULL);   
       pthread_create(&thread5, NULL, function5, NULL);
    
    pthread_join(thread1,0);
    pthread_join(thread2,0);
    pthread_join(thread3,0);
    pthread_join(thread4,0);
    pthread_join(thread5,0);
    }