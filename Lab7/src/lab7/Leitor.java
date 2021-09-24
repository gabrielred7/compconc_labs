
package lab7;

public class Leitor extends Thread{
    int id; //identificador da thread
    int delay; //atraso bobo
    LeitorEscritor monitor; //objeto monitor para coordenar a logica de execucao das threads

    public Leitor(int id, int delay, LeitorEscritor monitor) {
        this.id = id;
        this.delay = delay;
        this.monitor = monitor;
    }
    
    // Metodo executado pela thread
    public void run(){
        double j = 777777777.7, i;
        try{
            for (;;) {
                this.monitor.EntraLeitor(this.id);
                for (i = 0; i < 100000000; i++) { j=j/2;}
                this.monitor.SaiLeitor(this.id);
                sleep(this.delay);
            }
        } catch (InterruptedException e) {return; }
    }
}
