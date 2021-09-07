
package pkg01_.hellothread;

//--PASSO 1: criar uma classe que implementa a interface Runnable 
public class Hello implements Runnable{
    private String msg;
    
    //--construtor
    public Hello(String m) {
        this.msg = m;
    }
    
   //--metodo responsavel pelo codigo que devera ser executado pela thread.
    public void run() {
        System.out.println(msg); 
    }
}
