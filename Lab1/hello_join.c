/* Codigo: "Hello World" usando threads em C e a funcao que espera as threads terminarem
Programa da Atividade 4 do Lab1*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS  10 //total de threads a serem criadas

//cria a estrutura de dados para armazenar os argumentos da thread
typedef struct{
    int idThread, nThread;
} t_Args;

//funcao executa pelas threads
void *PrintHello(void *arg){
    t_Args *args = (t_Args *) arg;
    printf("Sou a thread %d de %d threads\n", args -> idThread, args -> nThread);
    free(arg); //aqui pode liberar a alocaçao feita na main
    pthread_exit(NULL);
}

//funcao principal do programa
int main(){
    pthread_t tid_sistema[NTHREADS]; //identificadores das threads no sistema
    int thread; //variavel auxiliar
    t_Args *arg; //recebera os argumentos para a thread

    for(thread=1; thread<NTHREADS+1; thread++){
        printf("--Aloca e preenche argumentos para thread %d\n", thread);

        //Fazendo o alocamento de memoria da estrutura t_Args na variavel arg
        arg = malloc(sizeof(t_Args));
        if(arg == NULL){
            printf("--ERRO: malloc()\n");
            exit(-1);
        }

        arg -> idThread = thread;
        arg -> nThread = NTHREADS;

        printf("--Cria a thread %d\n", thread);
        if(pthread_create(&tid_sistema[thread], NULL, PrintHello, (void*) arg)){
            printf("--ERRO: pthread_create() \n");
            exit(-1);
        }
    }

    //--espera todas as threads terminarem)
    for(thread=1; thread<NTHREADS+1; thread++){
        if(pthread_join(tid_sistema[thread], NULL)){
            printf("--ERRO: pthread_join()\n");
            exit(-1);
        }
    }
    printf("--Thread principal terminou\n");
    pthread_exit(NULL);
}
