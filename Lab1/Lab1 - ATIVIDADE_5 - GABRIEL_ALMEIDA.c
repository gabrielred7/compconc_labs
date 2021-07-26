/*Programa da Atividade 5 do Lab1*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NTHREADS 2 //total de threads a serem criados
#define TVETOR 10000

//função auxiliar que calcular a potencia de 2 cada elemento do vetor de 10000
void *Potenciacao(void* arg){
    int idVetor = *(int*) arg;
    for(int cont=1; cont<idVetor+1; cont++){
        printf("%.f ", pow(cont,2));
    }
    pthread_exit(NULL);
}

//funcao principal do programa
int main(){
    pthread_t tid_sistema[NTHREADS]; //identificadores das threads no sistema
    int thread; //variavel auxiliar
    int tid_local[TVETOR]; //identificadores locais das thread

    //Cria as thread
    for(thread=1; thread<NTHREADS+1; thread++){
        printf("--Cria a thread %d\n", thread);
        tid_local[thread] = TVETOR;
        if(pthread_create(&tid_sistema[thread], NULL, Potenciacao, (void*) &tid_local[thread])){
            printf("--ERRO: pthread_create()\n");
            exit(-1);
        }
    }

    //--Espera todas as threads terminarem)
    for(thread=1; thread<NTHREADS+1; thread++){
        if(pthread_join(tid_sistema[thread], NULL)){
            printf("--ERRO: pthread_join()\n");
            exit(-1);
        }
    }

    printf("--Thread principal terminou\n");
    pthread_exit(NULL);
}
