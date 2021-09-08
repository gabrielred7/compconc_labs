
package lab6;

public class Compartilhado {
    //recurso compartilhado
    private int soma;
  
    //construtor
    public Compartilhado() {
        this.soma = 0;
    }
    
    public synchronized int getR() { 
        return this.soma; 
    }
    
    public synchronized void incR(int contagem) { 
        this.soma += contagem;
    }
}
