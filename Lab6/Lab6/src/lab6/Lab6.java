
package lab6;

public class Lab6 {
    
    static final int N = 3;
    static int tam = 10;
    static int vetorInteiros[];
    static int totSoma = 0;
    
    public static void main(String[] args) {
        
      vetorInteiros = new int[tam];
      
      //preenchendo o vetor com valores aleatorios
      for (int pos = 0; pos < vetorInteiros.length; pos++) {
          int valor = (int)(Math.random()*10)%10;
          vetorInteiros[pos] = valor;
      }
      
      //imprimir
      for (int pos = 0; pos < vetorInteiros.length; pos++) {
          System.out.println(pos + " " + vetorInteiros[pos]);
      }
      
      //reserva espaaço para um vetor de threads
      Thread[] threads = new Thread[N];
      
      //cria uma instancia do recurso compartilhado entre as threads
      Compartilhado s = new Compartilhado();
      
      //cria as threads da aplicacao
      for (int i = 0; i < threads.length; i++) {
          threads[i] = new Tid(i, s);
      }
      
      //inicia as threads
      for (int i = 0; i < threads.length; i++) {
          threads[i].start();
      }
      
      //espera pelo termino de todas as threads
      for (int i = 0; i < threads.length; i++) {
          try { threads[i].join(); } 
          catch (InterruptedException e) { return; }
      }
      
      System.out.println("O vetor tem " + (s.getR()) + " elementos pares.");
    }
}