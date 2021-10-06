/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 9 */
/* Atividade 1 */

/* Implementar uma variação na implementação do problema produtor/consumidor, usando semáforos. */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define N 5 //tamanho do buffer
#define P 2 //qtd de threads produtoras
#define C 2 //qtd de threads consumidora

//variaveis do problema
int Buffer[N]; //area de dados compartilhados
int count = 0, in = 0; 
int out; 
//auxiliares, permitem dar informações de estado do buffer

//variaveis para sincronização
//pthread_mutex_t mutex; //variavel de exclusao mutua
//pthread_cond_t cond_cons, cond_prod; //variaveis de condição
sem_t cons, prod; //variaveis de semaforo

//inicializa o buffer
void IniciaBuffer(int n){
    for (int i = 0; i < n; i++){
        Buffer[i] = 0;
    }
}

//imprime o buffer
void ImprimeBuffer(int n){
    for (int i = 0; i < n; i++){
        printf("%d", Buffer[i]);
    }
    printf("\n");
}

//thread produtora
void *produtor(void * arg){
    int *id = (int *) arg;
    printf("Sou a thread produtora %d\n", *id);
    while (1){
        sem_wait(&prod);
        int item = *(int *) arg;
        printf("P[%d] quer inserir\n", *id);
        if (count == N){
            printf("P[%d] bloqueou\n", *id);
            sem_post(&cons);
            sem_wait(&prod);
            printf("P[%d] desbloqueou\n", *id);
        }
        Buffer[in] = item;
        in = (in + 1) % N;
        count++;
        printf("P[%d] inseriu\n", *id);
        ImprimeBuffer(N);
        sem_post(&prod);
        sleep(1);
    }
    free(arg);
    pthread_exit(NULL);
}

//thread consumidora
void *consumidor(void * arg){
    int *id = (int *) arg;
    printf("Sou a thread consumidora %d\n", *id);
    while (1){
        sem_wait(&cons);
        int item;
        printf("C[%d] quer consumir\n", *id);
        for (out = 0; out < N; out++){
            item = Buffer[out];            
            printf("C[%d] consumiu %d\n", *id, item);
            Buffer[out] = 0;
            count--;
        }
        ImprimeBuffer(N);        
        sem_post(&prod);
        sleep(1);
    }
    free(arg);
    pthread_exit(NULL);
}

//função principal
int main(void){
    //auxiliares
    int i;

    //identificadores de threads
    pthread_t tid[P+C];
    int *id[P+C];

    //aloca espaço para os IDs das threads
    for(i = 0; i < P+C; i++){
        id[i] = malloc(sizeof(int));
        if (id[i] == NULL) exit(-1);
        *id[i] = i+1;
    }

    //inicializa o Buffer
    IniciaBuffer(N);

    //inicia os semaforos
    sem_init(&cons, 0, 0);
    sem_init(&prod, 0, 1);

    //cria as threads produtoras
    for (i = 0; i < P; i++){
        if (pthread_create(&tid[i], NULL, produtor, (void *) id[i])) exit(-1);            
    }

    //cria as threads consumidores
    for (i = 0; i < C; i++){
        if (pthread_create(&tid[i+P], NULL, consumidor, (void *) id[i+P])) exit(-1);
    }

    pthread_exit(NULL);
    return 1;
}