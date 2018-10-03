# FileManager

Universidade Federal de Santa Catarina - UFSC<br>
Centro de Ciências, Tecnologias e Saúde<br>
Departamento de Computação<br>
Curso de Engenharia da Computação<br><br>

Alunos:<br>
Matheus André Soares - 15103102<br>
Patrick Davila Kochan - 15102827<br><br>

Enunciado do Trabalho:
    O sistema deve permitir que arquivos locais sejam acessados por usuarios remotos simultaneamente.<br>
    As operacoes permitidas pelo sistema devem incluir:<br>
    criar (sub)diretorio<br>
    remover (sub)diretorio<br>
    entrar em (sub)diretorio<br>
    mostrar conteudo do diretorio<br>
    criar arquivo<br>
    remover arquivo<br>
    escrever um sequencia de caracteres em um arquivo<br>
    mostrar conteudo do arquivo<br><br>

    Etapa 1:
        Desenvolver a estrutura de acesso do servidor de arquivos.
        Ele devera sera acessado via socket TCP. Cada conexao devera ser gerida por uma thread.
        Condicoes de corrida deverao ser tratadas por meio de semaforos ou mutexes.
        Nesta etapa voce nao precisa implementar as operacoes sobre arquivos listadas acima.
        Ao inves disso, use as operacoes diretamente do sistema de arquivos do seu sistema operacional.
        Recomenda-se que o servidor imprima mensagens na tela para demonstrar o funcionamento ao professor.

    Observacoes:
        Nao e necessario autenticacao dos usuarios.
        Nao e necessario criar um aplicativo cliente. Voce pode usar o aplicativo netcat disponivel para Linux e Windows.
     
Anotacoes da equipe:
    - A funcao cat mostra apenas a primeira linha do arquivo (funcao fgets)
    - Sao iniciados dois clientes. O primeiro deles inicia a insercao de um comando mkdir para criar uma pasta
no diretorio atual do servidor (diretorio A). O outro cliente tambem inicia a insercao de um comando, um cd,
e realiza a mudanca de diretorio confirmando a operacao (diretorio B). O servidor troca de diretorio. O primeiro 
cliente confirma enfim a operacao mkdir. O resultado sera a criacao da pasta no diretorio B. Deveriamos adaptar o 
mutex para resolver essa situacao.
    - Temos um servidor aberto e dois clientes. Quantas threads e quantos processos temos?
        - 2 threads (clientes) e 1 processo (servidor)?
