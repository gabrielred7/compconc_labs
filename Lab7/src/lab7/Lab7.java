
package lab7;

public class Lab7 {
    static final int L = 4;
    static final int E = 3;
    
    public static void main(String[] args) {
        LeitorEscritor monitor = new LeitorEscritor(); // Monitor (objeto compartilhado entre leitores e escritores)
        Leitor[] ler = new Leitor[L]; // Threads leitores
        Escritor[] escrever = new Escritor[E]; // Threads escritores
        
        for (int i=0; i<L; i++) {
            ler[i] = new Leitor(i+1, (i+1)*500, monitor);
            ler[i].start(); 
        }
    
        for (int i=0; i<E; i++) {
            escrever[i] = new Escritor(i+1, (i+1)*500, monitor);
            escrever[i].start(); 
        }
    }
    
}
