
package pkg02_olathreads;

//--PASSO 1: cria uma classe que estende a classe Thread 
public class Ola extends Thread{
    private String msg;
    
    //--construtor
    public Ola(String msg) {
        this.msg = msg;
    }
    
    //--metodo executado pela thread
    public void run() {
        System.out.println(msg); 
    }
}
