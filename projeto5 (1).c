#include <stdio.h>
#include <string.h>
#include <time.h>

char usuarioCorreto[] = "admin";
int hashSalvo = 202; // senha 1234

void linha()
{
    printf("\n=====================================\n");
}

/* hash simples p/ senha */
int gerarHash(char senha[])
{
    int i = 0, soma = 0;

    while(senha[i] != '\0')
    {
        soma += senha[i];
        i++;
    }

    return soma;
}

/* criar arquivo */
void criarArquivo()
{
    FILE *arq;

    arq = fopen("dados.txt", "r");

    if(arq == NULL)
    {
        arq = fopen("dados.txt", "w");

        fprintf(arq, "Arquivo protegido do sistema\n");
        fprintf(arq, "Somente usuarios autorizados podem visualizar.\n");
        fprintf(arq, "Projeto de Seguranca em Sistemas Operacionais.\n");

        fclose(arq);
    }
    else
    {
        fclose(arq);
    }
}

/* login */
int login()
{
    char usuario[30];
    char senha[30];
    int tentativas = 0;

    while(tentativas < 3)
    {
        linha();
        printf("LOGIN DO SISTEMA\n");
        linha();

        printf("Usuario: ");
        scanf("%29s", usuario);

        printf("Senha: ");
        getchar();
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = 0;

        if(strlen(senha) == 0)
        {
            printf("Senha vazia.\n");
            continue;
        }

        if(strcmp(usuario, usuarioCorreto) == 0 &&
           gerarHash(senha) == hashSalvo)
        {
            printf("\nLogin realizado com sucesso!\n");
            return 1;
        }

        tentativas++;
        printf("Login invalido. Tentativa %d de 3\n", tentativas);
    }

    printf("\nConta bloqueada.\n");
    return 0;
}

/* controle de acesso */
void acessoArquivo()
{
    int op;
    FILE *arq;
    char texto[200];

    linha();
    printf("CONTROLE DE ACESSO\n");
    linha();

    printf("1 - Ler arquivo protegido\n");
    printf("2 - Alterar arquivo protegido\n");
    printf("Escolha: ");
    scanf("%d", &op);

    if(op == 1)
    {
        criarArquivo();

        arq = fopen("dados.txt", "r");

        printf("\nConteudo do arquivo:\n\n");

        while(fgets(texto, sizeof(texto), arq) != NULL)
            printf("%s", texto);

        fclose(arq);
    }

    else if(op == 2)
    {
        printf("\nPermissao negada para alteracao.\n");
        printf("Somente administrador pode modificar.\n");
    }

    else
    {
        printf("\nOpcao invalida.\n");
    }
}

/* simulacao de ataque */
void ataque()
{
    int i;
    char senhas[5][20] =
    {
        "123",
        "admin",
        "senha",
        "0000",
        "1234"
    };

    linha();
    printf("SIMULACAO DE ATAQUE\n");
    linha();

    for(i = 0; i < 5; i++)
    {
        printf("Tentativa %d usando senha: %s\n", i + 1, senhas[i]);

        if(i == 2)
        {
            printf("\nSistema bloqueou apos 3 erros.\n");
            return;
        }
    }
}

/* benchmark */
void benchmark()
{
    int i, resultado = 0;
    clock_t inicio, fim;
    double tempo;

    linha();
    printf("BENCHMARK\n");
    linha();

    inicio = clock();

    for(i = 0; i < 1000000; i++)
        resultado += gerarHash("1234");

    fim = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo: %.4f segundos\n", tempo);
    printf("Valor final: %d\n", resultado);
}

/* menu principal */
int main()
{
    int op = -1;

    while(op != 0)
    {
        linha();
        printf("PROJETO 5 - SEGURANCA EM SO\n");
        linha();

        printf("1 - Conceitos de seguranca\n");
        printf("2 - Login + acesso\n");
        printf("3 - Simular ataque\n");
        printf("4 - Benchmark\n");
        printf("0 - Sair\n");

        printf("Escolha: ");

        if(scanf("%d", &op) != 1)
        {
            printf("Entrada invalida.\n");

            while(getchar() != '\n');

            op = -1;
            continue;
        }

        if(op == 1)
        {
            linha();
            printf("CONCEITOS DE SEGURANCA\n");
            linha();

            printf("Confidencialidade: somente usuarios autorizados acessam dados.\n");
            printf("Integridade: dados nao devem ser alterados indevidamente.\n");
            printf("Disponibilidade: sistema deve funcionar quando necessario.\n");
            printf("Autenticacao: verifica identidade do usuario.\n");
            printf("Controle de acesso: define permissoes no sistema.\n");
        }

        else if(op == 2)
        {
            if(login() == 1)
                acessoArquivo();
        }

        else if(op == 3)
        {
            ataque();
        }

        else if(op == 4)
        {
            benchmark();
        }

        else if(op == 0)
        {
            printf("\nPrograma encerrado.\n");
        }

        else
        {
            printf("\nOpcao invalida.\n");
        }
    }

    return 0;
}
