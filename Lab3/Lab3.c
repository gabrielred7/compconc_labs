/*Programa da Atividade 1 do Lab3*/

// Problema de encontrar o maior e o menor elemento em um vetor; e avaliar o desempenho da aplicac ̧ao em termos de tempo de execução.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <locale.h>

long long int N; // n de elementos do vetor
int nthreads; // numero de threads
float *vetor; // vetor de entrada com dimensao dim 

float maiorSeq, menorSeq = 0;
float maiorConc, menorConc = 0;

typedef struct {
    float maiorLocal; 
    float menorLocal;
} tArgs;

// Função da Forma Sequencial
void sequencial(){
    maiorSeq = menorSeq = vetor[0];
    for(long int i=0; i<N; i++){            
        if (vetor[i] > maiorSeq){
            maiorSeq = vetor[i];
        }
        if (vetor[i] < menorSeq){
            menorSeq = vetor[i];
        }
    }
}

//fluxo das threads
void * tarefa(void * arg){
    long int id = (long int) arg; //identificaor da thread
    tArgs *args = (tArgs*) arg; //typecast de ponteiro para o novo tipo de Args
    //dividindo os blocos das threads
    long int tamBloco = N/nthreads; //tamanho do bloco de cada thread
    long int inicial = id*tamBloco; //elemento inicial do bloco da thread
    long int final; //elemento final do bloco da thread

    //toda var ponteiro é necessario alocar espaço (endereço de um float no caso) e depois inicializar
    args = (tArgs*) malloc(sizeof(tArgs));
    if(args == NULL){fprintf(stderr, "ERRO--malloc--args \n"); exit(1);}
    
    //Tem que ser com o primeiro elemento do bloco do vetor tratado pela thread
    args->maiorLocal = args->menorLocal = vetor[inicial];
    if (id == nthreads - 1){final = N;} // tratamento do final. caso eu seja a ultima thread
    else {final = inicial + tamBloco;} //trata o resto se houver
    
    //iteração principal
    for (long int i=inicial+1; i<final; i++){
        if (vetor[i] > args->maiorLocal){
            args->maiorLocal = vetor[i];
        }
        if (vetor[i] < args->menorLocal){
            args->menorLocal = vetor[i];
        }
    }
    //retorna o resultado da soma local
    pthread_exit((void*) args); //somalocal salva o endereço da soma
}

int main(int argc, char *argv[]){
    float tSegredo;
    pthread_t *tid; //identificadores das threads no sistema
    tArgs *retorno; //valor de retorno das threads

    clock_t inic, fim; //tomada de tempo
    double delta = 0;

    //recebe e valida os parametros de entrada (n do vetor, n de threads)
    if(argc < 3){
        fprintf(stderr, "Digite: %s <n de elementos> <n de threads>\n", argv[0]);
        return 1;
    }
    N = atoll(argv[1]); //atoll converte string para long long int
    nthreads = atoi(argv[2]);

    float maxmin[nthreads];

    //aloca o vetor de entrada
    vetor = (float*) malloc(sizeof(float) * N); //malloc converte ponteiro para void
    if (vetor == NULL){fprintf(stderr, "Erro--malloc--vetor\n"); return 2;}
    
    // inicializa e preenche o vetor de entrada
    /* Preenche os campos com valores aleatórios do tipo float. */
    srand(time(NULL));
    for(long int i=0; i<N; i++){
        tSegredo = (float) rand() / RAND_MAX * 100;
        vetor[i] = tSegredo;
        printf( "%.2f ", tSegredo);
    }
    printf("\n");

    /*------------------------------------------------------------------------------------------------*/
    /* VERIFICAÇÃO DE MAIOR E MENOR NA FORMA SEQUENCIAL DOS ELEMENTOS */
    inic = clock();

    sequencial();
    fim = clock();

    delta = (double)(fim - inic) * 1000 / CLOCKS_PER_SEC; 
    printf("Tempo de sequencial: %.5lf\n", delta);
    
    /*------------------------------------------------------------------------------------------------*/
    /* VERIFICAÇÃO DE MAIOR E MENOR NA FORMA CONCORRENTE DOS ELEMENTOS */
    //aloca as threads
    inic = clock();
    tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
    if (tid == NULL){fprintf(stderr, "ERRO--malloc--tid\n"); return 2;}
    retorno = (tArgs*) malloc(sizeof(tArgs));
    if(retorno == NULL){puts("ERRO--malloc--retorno\n"); return 2;}

    //criação thread
    for(long int i=0; i<nthreads; i++){
        if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
            fprintf(stderr, "ERRO--pthread_create\n"); return 3;
        }
    }

    //aguardar o termino das threads
    for(long int i=0; i<nthreads; i++){
        if(pthread_join(*(tid+i), (void**) &retorno)){ //o segundo argumento é o retorna da função
            fprintf(stderr, "ERRO--pthread_join\n"); return 3;            
        }
        
        if (i == 0){
            maxmin[0] = maiorConc = retorno->maiorLocal;
            maxmin[1] = menorConc = retorno->menorLocal;
        }else{
            if (maxmin[0] > retorno->menorLocal){
                maxmin[0] = retorno->menorLocal;
                menorConc = maxmin[0];
            }
            if (maxmin[1] < retorno->maiorLocal){
                maxmin[1] = retorno->maiorLocal;
                maiorConc = maxmin[1];
            } 
        } 
    }

    fim = clock();
    delta = (double)(fim - inic) * 1000/ CLOCKS_PER_SEC; 
    printf("Tempo de concorrente: %.5lf\n", delta);
    
    /*------------------------------------------------------------------------------------------------*/

    //exibir os resultados
    printf("Com a Funcao Sequencial. O maior e: %.2f e O menor e: %.2f \n", maiorSeq, menorSeq);
    printf("Com a Funcao Concorrente. O maior e: %.2f e O menor e: %.2f \n", maiorConc, menorConc);
    
    //libera a memoria alocada
    free(vetor);
    free(tid);

    return 0;
}