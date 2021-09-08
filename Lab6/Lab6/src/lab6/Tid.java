
package lab6;

//classe que estende Thread e implementa a tarefa de cada thread do programa
import static lab6.Lab6.N;
import static lab6.Lab6.tam;
import static lab6.Lab6.vetorInteiros;

public class Tid extends Thread{
    
    private int id; //identificador da thread 
    Compartilhado s; //objeto compartilhado com outras threads
    private int contagem;

    public Tid(int id, Compartilhado s) {
        this.id = id;
        this.s = s;
    }
   
    // metodo main da thread
    @Override
    public void run(){
        //dividindo os blocos das threads
        int tamBloco = tam/N; //tamanho do bloco de cada thread
        int inicio = id*tamBloco; //elemento inicial do bloco da thread
        int fim;
                
        if (id == N - 1){fim = tam;} // tratamento do final. caso eu seja a ultima thread
        else {fim = inicio + tamBloco;} //trata o resto se houver
                
        for (int pos = inicio; pos < fim; pos++) {
            if (vetorInteiros[pos] % 2 == 0) {
                this.contagem++;
            }
        }
        
        this.s.incR(contagem);
    }
}
