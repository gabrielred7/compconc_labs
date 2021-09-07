/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratorio: 6 */
/* Codigo: Estendendo a classe Thread de Java */

/* 
Atividade 2
Objetivo: Mostrar outra forma de criar threads em Java, usando herança.
*/
package pkg02_olathreads;

public class OlaThread {
static final int N = 10;

   public static void main (String[] args) {
      //--reserva espaÃ§o para um vetor de threads
      Thread[] threads = new Thread[N];
    
      //--PASSO 2: cria threads da classe que estende Thread
      for (int i=0; i<threads.length; i++) {
         final String m = "Ola da thread " + i;
         System.out.println("--Cria a thread " + i);
         threads[i] = new Ola(m);
      }

      //--PASSO 3: iniciar as threads
      for (int i=0; i<threads.length; i++) {
         threads[i].start();
      }

      //--PASSO 4: esperar pelo termino de todas as threads
      for (int i=0; i<threads.length; i++) {
         try { threads[i].join(); } 
         catch (InterruptedException e) { return; }
      }

      System.out.println("Terminou"); 
   }
}