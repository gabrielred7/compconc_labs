/* Codigo: "Hello World" usando threads em C com passagem de um argumento
Programa da Atividade 2 do Lab1*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS  10 //total de threads a serem criadas

//funcao executada pelas threads
void *PrintHello(void* arg){
    int idThread = *(int*) arg;
    printf("Hello, world da thread: %d\n", idThread);
    pthread_exit(NULL);
}

//funcao principal do programa
int main(){
    pthread_t tid_sistema[NTHREADS]; //identificadores das threads no sistema
    int thread; //variavel auxiliar
    int tid_local[NTHREADS]; //identificadores locais das threads

    //Cria as thread
    for(thread=1; thread<NTHREADS+1; thread++){
        printf("--Cria a thread %d\n", thread);
        tid_local[thread] = thread;
        if(pthread_create(&tid_sistema[thread], NULL, PrintHello, (void*) &tid_local[thread])){
            printf("--ERRO: pthread_create()\n");
            exit(-1);
        }
    }
    printf("--Thread principal terminou\n");
    pthread_exit(NULL);
}
