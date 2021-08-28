#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/* Variaveis Globais */
int tBloqueadas = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

int nthreads; // numero de threads
float *vetor; // vetor de entrada com dimensao dim
int somaGlobal = 0;

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
    int id = *(int*)arg;
    int somaLocal = 0;
    for (int k = 0; k < nthreads; k++){
        somaLocal += vetor[k];
        printf("Thread %d tem somatorio = %d\n", id, somaLocal); 
    }
    somaGlobal+=somaLocal;
    barreira(nthreads);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
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

    //aloca o vetor de entrada
    vetor = (float*) malloc(sizeof(float) * nthreads); //malloc converte ponteiro para void
    if (vetor == NULL){fprintf(stderr, "Erro--malloc--vetor\n"); return 2;}

    srand(time(NULL));
    for(int i = 0; i < nthreads; i++){
        tSegredo = (int) rand() % 10;
        vetor[i] = tSegredo;
        printf( "%d ", tSegredo);
    }
    printf("\n");

    //criação thread
    for(long int i=0; i<nthreads; i++){
        id[i] = i;
        if(pthread_create(&threads[i], NULL, tarefa, (void*) &id[i])){
            fprintf(stderr, "ERRO--pthread_create\n"); return 3;
        }
    }

    //aguardar o termino das threads
    for(long int i=0; i<nthreads; i++){
        if(pthread_join(threads[i], NULL)){ //o segundo argumento é o retorna da função
            fprintf(stderr, "ERRO--pthread_join\n"); return 3;            
        }
    }
    //libera a memoria alocada
    free(vetor);
    free(threads);
    return 0;
}