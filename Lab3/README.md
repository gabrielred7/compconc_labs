# Nome: Gabriel Almeida Mendes / DRE: 11704949
Modulo 1 - Laboratório 3 - Atividade 1

4 - Verifique a corretude da solução concorrente comparando seus resultados como os resultados da versão sequencial para o mesmo vetor de entrada. <br>
R= A solução concorrente não seleciona os mesmos números maiores e menores que os da solução sequencial quando é escolhido numeros pequenos. <br>

5 - Calcule o ganho de desempenho obitdo com a versão concorrente: (Tsequencial/Tconcorrente). Considere os seguintes valores de N: 10^5, 10^7, 10^9. Para a versão concorrentem experimente com 2 e 4 threads. Inicialize o vetor uma vez, e repita as execuções da funções sequencial e concorrente várias vezes para cada configuração dos parâmetros de entrada. Calule o tempo médio obtido nessas execuções para a versão sequencial e para a versão concorrente e então calcule a aceleração. <br>

-> Para valor de N = 10^5 e versão concocorrente com 2 threads: <br>
Tempo médio para a versão sequencial - 0.50000 ms; <br>
Tempo médio para a versão concorrente - 1.00000 ms; <br>
Calculo da aceleração - 1.00000 ms; <br>

-> Para valor de N = 10^7 e versão concocorrente com 2 threads: <br>
Tempo médio para a versão sequencial - 43.20000 ms; <br>
Tempo médio para a versão concorrente - 25.60000 ms; <br>
Calculo da aceleração - 1.68750 ms; <br>

-> Para valor de N = 10^9 e versão concocorrente com 2 threads: <br>
OBS: Professora, não foi possivel alocar memoria para um vetor desse tamanho em minha máquina. <br>
Tempo médio para a versão sequencial - <br>
Tempo médio para a versão concorrente - <br>
Calculo da aceleração -  <br>

--------------------------------------------------------------------

-> Para valor de N = 10^5 e versão concocorrente com 4 threads: <br>;
Tempo médio para a versão sequencial - 0.50000 ms; <br>
Tempo médio para a versão concorrente - 2.00000 ms; <br>
Calculo da aceleração - 0.25000 ms <br>

-> Para valor de N = 10^7 e versão concocorrente com 4 threads: <br>
Tempo médio para a versão sequencial - 43.20000 ms; <br>
Tempo médio para a versão concorrente - 15.60000 ms; <br>
Calculo da aceleração - 2.76923 ms; <br>

-> Para valor de N = 10^9 e versão concocorrente com 4 threads: <br>
OBS: Professora, não foi possivel alocar memoria para um vetor desse tamanho em minha máquina. <br>
Tempo médio para a versão sequencial - <br>
Tempo médio para a versão concorrente - <br>
Calculo da aceleração -  <br>