
package lab7;

public class Escritor extends Thread {
    int id; //identificador da thread
    int delay; //atraso bobo...
    LeitorEscritor monitor; //objeto monitor para coordenar a lÃ³gica de execuÃ§Ã£o das threads

    //Construtor
    public Escritor(int id, int delay, LeitorEscritor monitor) {
        this.id = id;
        this.delay = delay;
        this.monitor = monitor;
    }
    
    // MÃ©todo executado pela thread
    public void run () {
        double j=777777777.7, i;
        try {
            for (;;) {
                this.monitor.EntraEscritor(this.id); 
                for (i=0; i<100000000; i++) {j=j/2;} //...loop bobo para simbolizar o tempo de escrita
                this.monitor.SaiEscritor(this.id); 
                sleep(this.delay); //atraso bobo...
            }
        } catch (InterruptedException e) { return; }
    }
}
