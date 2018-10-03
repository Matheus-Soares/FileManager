# FileManager

Universidade Federal de Santa Catarina - UFSC
Centro de Ciências, Tecnologias e Saúde
Departamento de Computação
Curso de Engenharia da Computação

Alunos: Matheus André Soares - 15103102.
        Patrick Davila Kochan - 15102827.

Enunciado do Trabalho:
    O sistema deve permitir que arquivos locais sejam acessados por usuarios remotos simultaneamente.
    As operacoes permitidas pelo sistema devem incluir:
    criar (sub)diretorio
    remover (sub)diretorio
    entrar em (sub)diretorio
    mostrar conteudo do diretorio
    criar arquivo
    remover arquivo
    escrever um sequencia de caracteres em um arquivo
    mostrar conteudo do arquivo

    Etapa 1:
        Desenvolver a estrutura de acesso do servidor de arquivos.
        Ele devera sera acessado via socket TCP. Cada conexao devera ser gerida por uma thread.
        Condicoes de corrida deverao ser tratadas por meio de semaforos ou mutexes.
        Nesta etapa voce nao precisa implementar as operacoes sobre arquivos listadas acima.
        Ao inves disso, use as operacoes diretamente do sistema de arquivos do seu sistema operacional.
        Recomenda-se que o servidor imprima mensagens na tela para demonstrar o funcionamento ao professor.

    Observacoes:
        Não e necessario autenticacao dos usuarios.
        Não e necessario criar um aplicativo cliente. Voce pode usar o aplicativo netcat disponivel para Linux e Windows.
     
        Anotacoes
            - A funcao cat mostra apenas a primeira linha do arquivo (funcao fgets)
            - Sao iniciados dois clientes. O primeiro deles inicia a insercao de um comando mkdir para criar uma pasta
        no diretorio atual do servidor (diretorio A). O outro cliente tambem inicia a insercao de um comando, um cd,
        e realiza a mudanca de diretorio confirmando a operacao (diretorio B). O servidor troca de diretorio. O primeiro 
        cliente confirma enfim a operacao mkdir. O resultado sera a criacao da pasta no diretorio B. Deveriamos adaptar o 
        mutex para resolver essa situacao.
            - Temos um servidor aberto e dois clientes. Quantas threads e quantos processos temos?
                - 2 threads (clientes) e 1 processo (servidor)?
