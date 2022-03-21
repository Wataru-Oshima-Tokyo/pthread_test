#include <iostream>
#include <pthread.h>
#include <time.h>
#define NUM_THREADS 4
#define MAX_VALUE 20000
#define rep(i,a,b) for(int i=a; i<b; i++)
using namespace std;

struct threadParameters{
    int idx;
    int rows;
    int cols;
    int num_threads;
};


void *threadFunction(void* arguments){
    int idx = ((struct threadParameters*)arguments)->idx;
    int rows = ((struct threadParameters*)arguments)->rows;
    int cols = ((struct threadParameters*)arguments)->cols;
    int num_threads = ((struct threadParameters*)arguments)->num_threads;
    int startval = (idx*(cols/num_threads));
    int endval = (idx*(cols/num_threads)) + (cols/num_threads);
    rep(k,startval,endval){
        // rep(l, 0,rows){
        //     cout << l << " ";
        // }
        cout << k << endl;
        // printfs("\n");
    }
    printf("startval is %d and endval is %d\n", startval, endval);
}


int main(int argc, char** argv){
    struct timespec start, stop;
    double fstart, fstop;           
    int num_thread = NUM_THREADS;
    if(argc==2){
        // cout << argv[1] <<endl;
        num_thread = std::atoi(argv[1]);
        while(MAX_VALUE%num_thread!=0){
            num_thread--;
            // if(num_thread<=2)
            //     break;
        };
        
    }

    int rows = MAX_VALUE;
    int cols = MAX_VALUE;
    pthread_t thread[num_thread];
    
    int i, rc;
    clock_gettime(CLOCK_MONOTONIC, &start); fstart=(double)start.tv_sec + ((double)start.tv_nsec/1000000000.0);
    for(i=0; i<num_thread; i++){
        threadParameters *args = (struct threadParameters *)malloc(sizeof(struct threadParameters));
        args->idx = i;
        args->rows = rows;
        args->cols = cols;
        args->num_threads = num_thread;
        // cout << "create a thread ID." << i << endl;
        rc = pthread_create(&thread[i], NULL, threadFunction, args);
    }
    for(i=0; i<num_thread;i++)
        pthread_join(thread[i], NULL);
    clock_gettime(CLOCK_MONOTONIC, &stop); fstop=(double)stop.tv_sec + ((double)stop.tv_nsec/1000000000.0);

    cout << "The number of threads created is " << num_thread <<endl;
    cout << "the time elapsed is " << (fstop-fstart) <<endl;
    return 0;
}