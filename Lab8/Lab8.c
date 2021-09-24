/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 8 */
/* Atividade 1 */

/* Introdução: O objetivo deste Laboratorio é praticar o uso de semáforos para implementar exclusão mútua e sincronização condicional. Vamos repetir o exercício do Lab4, agora usando semaforos, ao invés de locks e variáveis de condição. */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 4

//Variaveis globais
int status = 0; //variaveis compartilhadas entre as threads
sem_t condt2, condt3, condt4, condt5; //semaforo para sincronizar a ordem de execucao das threads

//funcao executada pela thread 1
//T1 -> Seja bem-vindo! 
void *A(void *tid){
    printf("Seja bem-vindo!\n");
    sem_post(&condt2); //permite que B execute
    sem_post(&condt3); //permite que C execute
    pthread_exit(NULL);
}

//T2 -> Fique a vontade.
void *B (void *tid){
    sem_wait(&condt2); //espera A executar
    printf("Fique a vontade.\n");
    sem_post(&condt4); //permite que D execute
    pthread_exit(NULL);
}

//T3 -> Sente-se por favor.
void *C (void *tid){
    sem_wait(&condt3); //espera A executar
    printf("Sente-se por favor.\n");
    sem_post(&condt5); //permite que D execute
    pthread_exit(NULL);
}

//T4 -> Volte sempre!
void *D (void *tid){
    sem_wait(&condt4); //espera B 
    sem_wait(&condt5); //espera C 
    printf("Volte sempre!\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_t threads[NTHREADS];
    int *id[4], t;

    /* Forma de alocar memoria */
    for (t = 0; t < NTHREADS; t++){
        if ((id[t] = malloc(sizeof(int))) == NULL){
            pthread_exit(NULL); return 1;
        }
        *id[t] = t + 1;
    }

    //inicia os semaforos
    sem_init(&condt2, 0, 0);
    sem_init(&condt3, 0, 0);
    sem_init(&condt4, 0, 0);
    sem_init(&condt5, 0, 0);

    //cria as tres threads
    if (pthread_create(&threads[0], NULL, A, (void*)id[0])) {printf("--ERRO: pthread_create()\n"); exit(-1);}

    if (pthread_create(&threads[1], NULL, B, (void*)id[1])) {printf("--ERRO: pthread_create()\n"); exit(-1);}

    if (pthread_create(&threads[2], NULL, C, (void*)id[2])) {printf("--ERRO: pthread_create()\n"); exit(-1);}

    if (pthread_create(&threads[3], NULL, D, (void*)id[3])) {printf("--ERRO: pthread_create()\n"); exit(-1);}

    //--espera todas as threads terminarem
    for (t=0; t<NTHREADS; t++) {
        if (pthread_join(threads[t], NULL)) {
            printf("--ERRO: pthread_join() \n"); exit(-1); 
        } 
        free(id[t]);
    } 
    pthread_exit(NULL);
}
