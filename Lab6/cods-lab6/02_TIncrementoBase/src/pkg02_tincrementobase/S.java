
package pkg02_tincrementobase;

//classe da estrutura de dados (recurso) compartilhado entre as threads
public class S {
  //recurso compartilhado
  private int r;
  
  //construtor
  public S() { 
     this.r = 0; 
  }
  /*
  public int getR() {
    return this.r;
  }

  public void incR() {
    this.r++;
  }
  */
  
  // ou...
  
  public synchronized int getR() { 
    return this.r; 
  }
  
  public synchronized void incR() { 
    this.r++; 
  }
  
}
