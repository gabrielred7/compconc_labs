
package pkg01_tincrementobase;

//classe que estende Thread e implementa a tarefa de cada thread do programa 
public class T extends Thread{
    
    //identificador da thread
    private int id;
   
    //objeto compartilhado com outras threads
    S s;

    public T(int id, S s) {
        this.id = id;
        this.s = s;
    }
   
    // metodo main da thread
    @Override
    public void run(){
        System.out.println("Thread " + this.id + " iniciou!");
        for (int i = 0; i < 100000; i++) {
            this.s.incR();
        }
        System.out.println("Thread " + this.id + " terminou!");
    }
}
