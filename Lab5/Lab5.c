#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

/* Variaveis Globais */
int tBloqueadas = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

int nthreads; // numero de threads
int *vetor; // vetor de entrada com dimensao dim

// Funcao Barreira
void barreira(int nthreads){
    pthread_mutex_lock(&x_mutex); //inicio secao critica
    if (tBloqueadas == (nthreads - 1)){
        //ultima thread a chegar na barreira
        pthread_cond_broadcast(&x_cond);
        tBloqueadas = 0;
    } else {
        tBloqueadas++;
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    pthread_mutex_unlock(&x_mutex);
}

//funcao thread
void * tarefa(void * arg){
    int id = *(int*)arg; //thread atual
    int somaLocal = 0;
    for (int l = 0; l < nthreads; l++){
        for (int k = 0; k < nthreads; k++){
            somaLocal += vetor[k];
        }
        barreira(nthreads);
        int sortear = rand();
        vetor[id] = (id * sortear) % 10;
        barreira(nthreads);
    }
    pthread_exit((void*) somaLocal);
}

int main(int argc, char *argv[]){
    pthread_mutex_init(&x_mutex, NULL);
    pthread_cond_init(&x_cond, NULL);
    //recebe e valida os parametros de entrada (n do vetor, n de threads)
    if(argc < 2){
        fprintf(stderr, "Digite: %s <n de threads>\n", argv[0]);
        return 1;
    }
    nthreads = atoi(argv[1]);

    int tSegredo;
    vetor[nthreads];
    pthread_t threads[nthreads];
    int id[nthreads];
    int *retorno; //valor de retorno das threads

    //aloca o vetor de entrada
    vetor = (int*) malloc(sizeof(int) * nthreads); //malloc converte ponteiro para void
    if (vetor == NULL){fprintf(stderr, "Erro--malloc--vetor\n"); return 2;}

    srand(time(NULL));
    for(int i = 0; i < nthreads; i++){
        tSegredo = (int) rand() % 10;
        vetor[i] = tSegredo;
        printf( "%d ", tSegredo);
    }
    printf("\n");
    
    retorno = (int*) malloc(sizeof(int));
    if(retorno == NULL){puts("ERRO--malloc--retorno\n"); return 2;}

    long int vetorSomas[nthreads];
    long int pos = 0;

    //criação thread
    for(long int i=0; i<nthreads; i++){
        id[i] = i;
        if(pthread_create(&threads[i], NULL, tarefa, (void*) &id[i])){
            fprintf(stderr, "ERRO--pthread_create\n"); return 3;
        }
    }

    //aguardar o termino das threads
    for(long int i=0; i<nthreads; i++){
        if(pthread_join(*(threads+i),  (void**) &retorno[i])){ //o segundo argumento é o retorna da função
            fprintf(stderr, "ERRO--pthread_join\n"); return 3;            
        }
        printf("Para a thread %d temos %d. \n", i, retorno[i]);
        free(retorno);
    }

    bool corretude = false;
    for(int v = 0; v<nthreads-1; v++){
        if(retorno[v] != retorno[v+1]){
            corretude = true;
    }

    if (corretude){
        printf("Todos os valores recebidos sao iguais");
    }else{
        printf("Todos os valores recebidos nao sao iguais");
    }
    

    //libera a memoria alocada
    free(vetor);
    return 0;
}