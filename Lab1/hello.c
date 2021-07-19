/* Codigo: "Hello World" usando threads em C
Programa da Atividade 1 do Lab1*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 10 //total de threads a serem criados

//funcao executada pela threads
void *PrintHello(void *arg){
    printf("Hello, world\n");
    pthread_exit(NULL);
}

//funcao principal do programa
int main(){
    pthread_t tid_sistema[NTHREADS]; //identificadores das threads no sistema
    int thread; //variavel auxiliar

    //Executa 10 thread que executam a mesma função ao mesmo tempo
    for(thread=1; thread<NTHREADS+1; thread++){
        printf("--Cria a thread %d\n", thread);
        if(pthread_create(&tid_sistema[thread], NULL, PrintHello, NULL)){
            printf("--ERRO: pthread_create()\n");
            exit(-1);
        }
    }

    printf("--Thread principal terminou\n");
    pthread_exit(NULL);
}

/* Existe mudança na ordem de execução pq as threads sao executadas ao mesmo
tempo entao pode escapar da ordem dependendo do compilador. */
