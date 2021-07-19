/* Codigo: "Hello World" usando threads em C passando mais de um argumento
Programa da Atividade 3 do Lab1*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 10 //total de threads a serem criados

//cria a estrutura de dados para armazenar os argumentos da thread
typedef struct{
    int idThread, nThread;
} t_Args;

//funcao executada pela threads
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
    t_Args *arg; //receberá os argumentos para a thread por referencia

    for(thread=1; thread<NTHREADS+1; thread++){
        printf("--Aloca e preeche argumento para thread %d\n", thread);

        //Fazendo a alocaçção de memoria para os varios parametros
        arg = malloc(sizeof(t_Args));
        if(arg == NULL){
            printf("--ERRO: malloc()\n");
            exit(-1);
        }

        arg -> idThread = thread;
        arg -> nThread = NTHREADS;

        printf("--Cria a thread %d\n", thread);
        if(pthread_create(&tid_sistema[thread], NULL, PrintHello, (void*) arg)){
            printf("--ERRO: pthread_create()\n");
            exit(-1);
        }
    }

    printf("--Thread principal terminou\n");
    pthread_exit((NULL));
}
