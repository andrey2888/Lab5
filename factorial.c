#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <getopt.h>


#include <sys/wait.h>
#include <sys/time.h>

struct FactArgs {
  int begin;
  int end;
  int k;
};

long fact_global = 1;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void multiply_fact(int a, int k);

void *fact_from_to(void* args);

int main(int argc, char **argv){
    
int mod = 0;
int n = 0;
int threads_num = 0;

while (1) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"mod", required_argument, 0, 0},
                                      {"threads_num", required_argument, 0, 0},
                                      //{"argument", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, ":k:", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            mod = atoi(optarg);
            if (mod <= 0) {
                 printf("mod is a positive number\n");
                 return 1;
            }
            break;
          case 1:
            threads_num = atoi(optarg);
            if (threads_num <= 0) {
                printf("threads_num is a positive number\n");
                return 1;
            }
            break;
          /*case 2:
            n = atoi(optarg);
            if (n <= 0) {
                printf("threads_num is a positive number\n");
                return 1;
            }
            break;*/
          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      case 'k':
        n = atoi(optarg);
      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  /*if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }*/
 
fflush(NULL);


pthread_t threads[threads_num];
struct FactArgs  args[threads_num];

struct timeval start_time;
struct timeval fin_time;
gettimeofday(&start_time, NULL);
  
int step = n/threads_num;
printf("n %i\n",n);
printf("num %i\n",threads_num);
printf("step %i\n",step);
  for (int i = 0; i < threads_num; i++) {
    args[i].k = mod;
    args[i].begin = step * i + 1;
    args[i].end   = (i == threads_num - 1) ? n + 1: step * (i+1) + 1;
    if (pthread_create(&threads[i], NULL, fact_from_to, (void *)(args+i))) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }
   for (int i = 0; i < threads_num; i++) {
   pthread_join(threads[i], NULL);
   }
   printf("%ld\n",fact_global);
  
  gettimeofday(&fin_time, NULL);
  double elapsed_time = (fin_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (fin_time.tv_usec - start_time.tv_usec) / 1000.0;
  printf("Elapsed time: %fms\n", elapsed_time);
   
}


void multiply_fact(int a, int k){
    //pthread_mutex_lock(&mut);
    fact_global *= a;
    fact_global %= k;
    //pthread_mutex_unlock(&mut);
}

void *fact_from_to(void* args){
    pthread_mutex_lock(&mut);
    struct FactArgs* FA = args;
    //long partial_factorial = 1;
    long partial_factorial = fact_global;
    for(int i = FA->begin; i < FA->end; i++){
        partial_factorial *= i;
        partial_factorial %= FA->k; 
    }
    
    //printf("%i    %i    %ld\n", FA->begin, FA->end, partial_factorial);
    
    //multiply_fact(partial_factorial,FA->k);
    fact_global = partial_factorial;
    
    pthread_mutex_unlock(&mut);
    return 0;
}