/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 4 */
/* Atividade 4 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS  4

int status = 0;
pthread_mutex_t status_mutex;
pthread_cond_t status_cond_inicio;
pthread_cond_t status_cond_final;


//T1 -> Fique a vontade.
void *A (void *T){
    pthread_mutex_lock(&status_mutex);

    if (status == 0){
        pthread_cond_wait(&status_cond_inicio, &status_mutex);
    }
    printf("Fique a vontade!\n");
    status++;
    if (status == 4){
        printf("A:  status = %d, vai sinalizar a condicao \n", status);
        pthread_cond_signal(&status_cond_final);
    }
    pthread_mutex_unlock(&status_mutex);

    pthread_exit(NULL);
}

//T2 -> Seja bem-vindo!
void *B (void *T){
    printf("Seja bem-vindo!\n");
    pthread_mutex_lock(&status_mutex);

    status++;
    printf("B: status = %d, vai sinalizar a condicao \n", status);
    pthread_cond_broadcast(&status_cond_inicio);

    pthread_mutex_unlock(&status_mutex);
    pthread_exit(NULL);
}

//T3 -> Volte sempre!
void *C (void *T){
    pthread_mutex_lock(&status_mutex);
    status++;
    if (status < 4){
        printf("C: status = %d, vai se bloquear...\n", status);
        pthread_cond_wait(&status_cond_final, &status_mutex);
        printf("C: sinal recebido e mutex realocado. status = %d\n", status);
    }
    printf("Volte sempre!\n");
    pthread_mutex_unlock(&status_mutex);
    pthread_exit(NULL);
}

//T4 -> Sente-se por favor.
void *D (void *T){
    pthread_mutex_lock(&status_mutex);
    if (status == 0){
        pthread_cond_wait(&status_cond_inicio, &status_mutex);
    }
    printf("Sente-se por favor\n");
    status++;
    if (status == 4){
        printf("D:  status = %d, vai sinalizar a condicao \n", status);
        pthread_cond_signal(&status_cond_final);
    }
    pthread_mutex_unlock(&status_mutex); 
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
    pthread_t threads[NTHREADS];
  
    /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
    pthread_mutex_init(&status_mutex, NULL);
    pthread_cond_init (&status_cond_inicio, NULL);
    pthread_cond_init (&status_cond_final, NULL);

    /* Cria as threads */
    pthread_create(&threads[0], NULL, A, NULL);
    pthread_create(&threads[1], NULL, B, NULL);
    pthread_create(&threads[2], NULL, C, NULL);
    pthread_create(&threads[3], NULL, D, NULL);
    
    /* Espera todas as threads completarem */
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    /* Desaloca variaveis e termina */
    pthread_mutex_destroy(&status_mutex);
    pthread_cond_destroy(&status_cond_inicio);
    pthread_cond_destroy(&status_cond_final);
}