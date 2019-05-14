# FileManager

Universidade Federal de Santa Catarina - UFSC<br>
Centro de Ciências, Tecnologias e Saúde<br>
Departamento de Computação<br>
Curso de Engenharia da Computação<br><br>

Alunos:<br>
Matheus André Soares - 15103102<br>
Patrick Davila Kochan - 15102827<br><br>

Enunciado do Trabalho:<br>
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
