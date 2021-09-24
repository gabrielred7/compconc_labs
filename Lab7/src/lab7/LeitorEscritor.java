
package lab7;

public class LeitorEscritor {
    private int leitor, escritor;
    
    //Construtor
    public LeitorEscritor() {
        this.leitor = 0; //leitores lendo (0 ou mais)
        this.escritor = 0; //escritor escrevendo (0 ou 1)
    }
    
    // Entrada para Leitores
    public synchronized void EntraLeitor (int id){
        try {
            //while (this.escrever > 0)
            if (this.escritor > 0){
                
                wait(); //bloqueia pela condicao logica da aplicacao 
            }
            this.leitor++;
            
        } catch (InterruptedException e) {}
    }
    
    // Saida para Leitores
    public synchronized void SaiLeitor (int id){
        this.leitor--;
        if (this.leitor == 0) {
            this.notify(); //libera escritor (caso exista escritor bloqueado)
        }
        
    }
    
    // Entrada para escritores
    public synchronized void EntraEscritor (int id){
        try {
            //while ((this.leitor > 0) || (this.escritor > 0))
            if ((this.leitor > 0) || (this.escritor > 0)) {
                System.out.println("le.escritorBloqueado("+id+")");
                wait();
            }
            this.escritor++; //registra que ha um escritor escrevendo
            System.out.println("le.escritorEscrevendo("+id+")");
        } catch (InterruptedException e) { }
    }
    
    // Saida para escritores
    public synchronized void SaiEscritor (int id) {
        this.escritor--; //registra que o escritor saiu
        notifyAll(); //libera leitores e escritores (caso existam leitores ou escritores bloqueados)
        System.out.println ("le.escritorSaindo("+id+")");
    }
}
