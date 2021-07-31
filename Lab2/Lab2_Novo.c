/*Programa da Atividade 1 do Lab2*/

//Problema de multiplicacao de matrizes (considerando matrizes quadradas)
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <locale.h>
#include <time.h>


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
                saida[(args->id)*(args->dim)+j] += mat1[(args->id)*(args->dim)+k] * mat2[(k)*(args->dim)+j];
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

    clock_t inicio, fim;
    double delta;

    inicio = clock();
    //Avaliando os parametos de entrada da main
    if (argc < 3){
        printf("Digite: %s <dim da matris> <n de threads>\n", argv[0]);
        return 1;
    }
    dim = atoi(argv[1]); //transforma string para inteiro de cada dimensao
    nthreads = atoi(argv[2]); //transforma string para inteiro de cada n de threads
    if (nthreads > dim) nthreads = dim;

    //alocacaoo de memoria para as estruturas de dados principais
    mat1 = (float *) malloc(sizeof(float) * dim * dim);
    if (mat1 == NULL){printf("ERRO--malloc\n"); return 2;}
    mat2 = (float *) malloc(sizeof(float) * dim * dim);
    if (mat2 == NULL){printf("ERRO--malloc\n"); return 2;}
    saida = (float *) malloc(sizeof(float) * dim * dim);
    if (saida == NULL){printf("ERRO--malloc\n"); return 2;}

    //inicializacao das estruturas de dados principais
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            mat1[i*dim+j] = 1;  //equivalente mat[i][j]
            mat2[i*dim+j] = 1;
            saida[i*dim+j] = 0;
        }
    }

    fim = clock();
    delta = (double)(fim - inicio) * 1000.0 / CLOCKS_PER_SEC; 
    printf("Tempo de inicializacao das estruturas de dados: %.f\n", delta);

    inicio = clock();
    //multiplicacao da matriz pelo vetor
    //alocacao de memoria da estruturas de dado e das threads
    tid = (pthread_t*) malloc(sizeof(pthread_t)*dim*dim);
    if(tid==NULL){puts("ERRO--malloc"); return 2;}
    args = (tArgs*) malloc(sizeof(tArgs)*dim*dim);
    if(args==NULL){puts("ERRO--malloc");return 2;}

    //criação das threads
    for(int i=0; i<nthreads; i++){
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

    fim = clock();
    delta = (double)(fim - inicio)* 1000.0 / CLOCKS_PER_SEC; 
    printf("Tempo de criacao das threads, execucao da multiplicacao, e termino das threads: %.f\n", delta);

    inicio = clock();
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

    printf("Valor unico de Identificacao: %.2f ", saida[dim]);
    puts(" ");

    //liberacao da memoria
    free(mat1);
    free(mat2);
    free(saida);
    free(tid);
    free(args);

    fim = clock();
    delta = (double)(fim - inicio)* 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo de finalizacao do programa: %.f\n", delta);
    return 0;
}