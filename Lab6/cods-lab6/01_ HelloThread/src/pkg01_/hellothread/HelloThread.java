/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratorio: 6 */
/* Codigo: "Hello World" usando threads em Java */

/* 
Atividade 1 
Objetivo: Mostrar como criar um programa concorrente em Java. Em Java, a classe
java.lang.Thread oferece metodos para criar threads, inicia-las, suspende-las e 
esperar pelo seu termino. 
*/

package pkg01_.hellothread;

//--classe do metodo main
public class HelloThread {
    static final int N = 10;

    public static void main(String[] args) {
        //--reserva espaço para um vetor de threads
        Thread[] threads = new Thread[N];
        
        //--PASSO 2: transformar o objeto Runnable em Thread
        for (int i = 0; i < threads.length; i++) {
            final String m = "Hello World da thread: " + i;
            System.out.println("--Cria a thread " + i);
            threads[i] = new Thread(new Hello(m));
        }
        
        //--PASSO 3: iniciar a thread
        for (int i = 0; i < threads.length; i++) {
            threads[i].start();
        }
        
        /*Em Java criar e iniciar thread sao feitos em separado*/
        
        //--PASSO 4: esperar pelo termino das threads
        for (int i=0; i<threads.length; i++) {
            try { threads[i].join(); } 
            catch (InterruptedException e) { return; }
        }
        
        System.out.println("Terminou");
    }
}
