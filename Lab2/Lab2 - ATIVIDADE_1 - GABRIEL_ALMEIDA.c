//Programação Concorrente (uso de threads)
/*Versao 4.0 - Definindo qual o numero de thread a se usar
na saida, escolher o mais proximo ao numero de processadores.
Com adicional de medição de tempo de execução*/
//Problema de multiplicação de matrizes (considerando matrizes quadradas)
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <locale.h>
#include "timer.h"


float *mat1; //matriz de entrada 1
float *mat2; //matriz de entrada 2
float *saida; //matriz de saida
int nthreads; //numero de threads

typedef struct {
    int id; //elemento que a thread ira processar
    int dim; //dimensao das estruturas de entrada
} tArgs; //nome do tipo da struct

void * tarefa(void *arg){
    tArgs *args = (tArgs*) arg; //typecast de ponteiro para o novo tipo tArgs
    printf("Thread %d\n", args->id);
    for(int i=args->id; i<args->dim; i+=nthreads){
        for(int j=0; j<args->dim; j++){
            saida[(args->id)*(args->dim)+j] = 0;
            for(int k=0; k<args->dim; k++){
                saida[(args->id)*(args->dim)+j] += mat1[(args->id)*(args->dim)+k] * mat2[(args->id)*(args->dim)+k];
            }
        }
    }
    pthread_exit(NULL);
}

int main (int argc, char* argv[]){
    setlocale(LC_ALL,"");
    int dim;
    pthread_t *tid; //identificadores das threads no sistema
    tArgs *args; //identificadores locais das threads e dimensao

    double inicio, fim, delta;
    GET_TIME(inicio);

    //Avaliando os parametos de entrada da main
    if (argc < 3){
        printf("Digite: %s <dim da matris> <n de threads>\n", argv[0]);
        return 1;
    }
    dim = atoi(argv[1]); //transforma string para inteiro de cada dimensao
    nthreads = atoi(argv[2]); //transforma string para inteiro de cada n de threads
    if (nthreads > dim) nthreads = dim;

    //alocação de memoria para as estruturas de dados principais
    mat1 = (float *) malloc(sizeof(float) * dim * dim);
    if (mat1 == NULL){printf("ERRO--malloc\n"); return 2;}
    mat2 = (float *) malloc(sizeof(float) * dim * dim);
    if (mat2 == NULL){printf("ERRO--malloc\n"); return 2;}
    saida = (float *) malloc(sizeof(float) * dim * dim);
    if (saida == NULL){printf("ERRO--malloc\n"); return 2;}

    //inicialização das estruturas de dados principais
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            mat1[i*dim+j] = 4;  //equivalente mat[i][j]
            mat2[i*dim+j] = 2;
            saida[i*dim+j] = 0;
        }
    }

    //multiplicacao da matriz pelo vetor
    //alocacao de memoria da estruturas de dado e das threads
    tid = (pthread_t*) malloc(sizeof(pthread_t)*dim*dim);
    if(tid==NULL){puts("ERRO--malloc"); return 2;}
    args = (tArgs*) malloc(sizeof(tArgs)*dim*dim);
    if(args==NULL){puts("ERRO--malloc");return 2;}

    GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo de inicialização das estruturas de dados;: %.lf\n", delta);


    GET_TIME(inicio);

    //criacao das threads
    for(int i=0; i<dim; i++){
        (args+i)->id = i;
        (args+i)->dim = dim;
        if(pthread_create(tid+i, NULL, tarefa, (void*)(args+i))){
            puts("ERRO--pthread_create"); return 3;
        }
    }

    //espera pelo termino da threads
    for(int i=0; i<nthreads; i++){
        pthread_join(*(tid+i), NULL);
    }

    GET_TIME(fim)
    delta = fim - inicio;
    printf("Tempo de criação das threads, execução da multiplicação, e termino das threads: %.lf\n", delta);


    GET_TIME(inicio)
    /*
    //exibicao dos resultados
    puts("Primeira Matriz de Entrada:");
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++)
            printf("%.1f ", mat1[i*dim+j]);
        puts("");
    }

    puts("Segunda Matriz de Entrada:");
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++)
            printf("%.1f ", mat2[i*dim+j]);
        puts("");
    }
    */
    puts("Valor Único de Identificação:");
    printf("%.1f ", saida[dim]);
    printf("Tudo certo!");
    puts(" ");

    //liberacao da memoria
    free(mat1);
    free(mat2);
    free(saida);
    free(tid);
    free(args);

    GET_TIME(fim)
    delta = fim - inicio;
    printf("Tempo de finalização do programa: %.lf\n", delta);
    return 0;
}
