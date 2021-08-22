/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 4 */
/* Atividade 1 */
/* Codigo: Uso de variáveis de condição e suas operações básicas para sincronização por condição */

/***** Condicao logica da aplicacao: a thread B so pode imprimir "Bye" depois que duas threads A imprimirem  "Hello"  ****/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  3

/* Variaveis globais */
int x = 0;
pthread_mutex_t status_mutex;
pthread_cond_t status_cond;

/* Thread A */
void *A (void *t) {
  int boba1, boba2;

  printf("A: Comecei\n");
  
  /* faz alguma coisa pra gastar tempo... */
  boba1 = 10000; 
  boba2 = -10000; 
  while (boba2 < boba1) boba2++;
  
  printf("HELLO\n");

  pthread_mutex_lock(&status_mutex); //passa informação de estado
  x++;
  if (x == 2) {
      printf("A:  x = %d, vai sinalizar a condicao \n", x);
      pthread_cond_signal(&status_cond);
  }
  pthread_mutex_unlock(&status_mutex);

  pthread_exit(NULL);
}

/* Thread B */
void *B (void *t) {
  printf("B: Comecei\n");

  pthread_mutex_lock(&status_mutex);
  if (x < 2) { 
     printf("B: x= %d, vai se bloquear...\n", x);
     pthread_cond_wait(&status_cond, &status_mutex);
     printf("B: sinal recebido e mutex realocado, x = %d\n", x);
  }
  printf("BYE\n");
  pthread_mutex_unlock(&status_mutex); 

  pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[NTHREADS];

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&status_mutex, NULL);
  pthread_cond_init (&status_cond, NULL);

  /* Cria as threads */
  pthread_create(&threads[2], NULL, A, NULL);
  pthread_create(&threads[1], NULL, A, NULL);
  pthread_create(&threads[0], NULL, B, NULL);

  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("\nFIM\n");

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&status_mutex);
  pthread_cond_destroy(&status_cond);
}
