#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

typedef struct produto//Dados dos produtos
{
    char nome[50]; 
    int codigo;
    int quantidade;
    float preco;

}stru;

int codiguinho = 0;//codigo dos produtos(inicializa com 0 para não ter possibilidade de dar pau)

//Criando e validando arquivo exclusivo do código dos produtos:

void validar_codigo()
{
    FILE * fptr;
    fptr = fopen("codigo", "rb");

    if(fptr == NULL)//Caso o arquivo não exista, a variável será inicializada com 0
    {
        codiguinho = 0;
    }
    else
    {
        fread(&codiguinho, sizeof(int), 1, fptr);//Caso o arquivo exista, o valor nele será passado a variável codiguinho
        fclose(fptr);//Fecha o arquivo
    }
}

void salvar_codigo()
{
    FILE * fptr;
    fptr = fopen("codigo", "wb");//Abre o arquivo no modo Write Binary(WB) - Já que nesse caso, não há problema em apagar e reescrever oq está lá

    if(fptr != NULL)
    {
        fwrite(&codiguinho, sizeof(int), 1, fptr);//Salva o valor da variável "codiguinho" no arquivo, sobrescrevendo códigos passados
        fclose(fptr);//Fecha o arquivo
    }
}

void alterar_preco()
{
    FILE * fptr;
    fptr = fopen("cadastro", "rb+");

    if(fptr == NULL)
    {
        system("cls");
        printf("\n> ERRO AO ABRIR O ARQUIVO!\n\n");
        system("pause");//Pausando o terminal caso o arquivo não consiga ser aberto
        system("cls");
        fclose(fptr);
    }
    else
    {
        int codigo_val;
        bool nuossa = true, para_o_querido_do_usuario = false;
        stru prod;

        system("cls");
        printf("\t  ----'ALTERAR'----\n\n");
        printf("> Digite o codigo do produto a ser alterado: ");
        scanf("%d", &codigo_val);
        fflush(stdin);

        while(fread(&prod, sizeof(stru), 1, fptr) == 1)
        {
            if(codigo_val == prod.codigo)
            {
                int confirmar;
                bool receba = false;
                nuossa = false;

                printf("\n> Produto %s encontrado\n", prod.nome);

                do//Validar p o usuario n digitar nada por engano
                {
                    prod.preco = 0;

                    if(para_o_querido_do_usuario)
                    {
                        system("cls");

                        printf("\t  ----'ALTERAR'----\n\n");
                         printf("> Digite o codigo do produto a ser alterado: ");
                        printf("\n\n> Produto %s encontrado", prod.nome);
                        printf("\n\n|> DIGITE UM NUMERO VALIDO!\n");
                    }

                    printf("\n|Digite o novo preco: R$ ");
                    scanf("%f", &prod.preco);//Armazenando diretamente da struct pq no final n vai fazer diferença
                    fflush(stdin);

                    para_o_querido_do_usuario = true;

                }while(prod.preco <= 0);

                printf("\n");
                system("pause");
                system("cls");

                do//Loop p a confirmação de alteração
                {   system("cls");
                    printf("\t  ----'ALTERAR'----\n\n");
                    printf("> Confirmar alteracao?\n");
                    printf("\n[1] - SIM\n");
                    printf("[2] - NAO\n\n");

                    if(receba)
                    {
                        printf("|> DIGITE UM NUMERO VALIDO!\n\n");//Validação de número inválido
                    }

                    printf("|: ");
                    scanf("%d", &confirmar);
                    fflush(stdin);

                    switch(confirmar)//Optei por switch para uma melhor validação de input com o default
                    {
                        case 1:

                        system("cls");
                        fseek(fptr, -sizeof(stru), SEEK_CUR);
                        //fptr: Aponta p posição atual do arquivo
                        //-sizeof: O "-" vem para que o dado alterado não seja adicionado como um novo registro, sendo o caractere um indicativo q o registro anterior é q receberá o dado
                        //SEEK_CUB: É a referência a paritr da qual o deslocamento será calculado
                        //Resumindo, fptr da o dado atual do ponteiro no arquivo, -sizeof o tamanho em bytes da estrutura sendo negativa para não dar b.o de registro, SEEK_CUR usa a posição atual como ponto de partida

                        fwrite(&prod, sizeof(stru), 1, fptr);//Escrevendo o novo dado no arquivo

                        printf("\t  ----'ALTERAR'----\n\n");
                        printf("> ALTERACAO REALIZADA COM SUCESSO\n\n");
                        system("pause");
                        system("cls");

                        break;

                        case 2:

                            system("cls");
                            printf("\t  ----'ALTERAR'----\n\n");
                            printf("> ALTERACAO CANCELADA\n\n");
                            system("pause");
                            system("cls");

                        break;

                        default:
                        receba = true;
                    }
            
                }while(confirmar != 2 && confirmar != 1);
                break;
            }
        }

        if(nuossa)
        {
            printf("\n-> PRODUTO NAO ENCONTRADO\n\n");
            system("pause");
            system("cls");
        }
        fclose(fptr);
    }
}

void alterar_quantidade()
{
    FILE * fptr;
    fptr = fopen("cadastro", "rb+");

    if(fptr == NULL)
    {
        system("cls");
        printf("\n> ERRO AO ABRIR O ARQUIVO!\n\n");
        system("pause");//Pausando o terminal caso o arquivo não consiga ser aberto
        system("cls");
        fclose(fptr);
    }
    else
    {
        int codigo_val;
        stru prod;
        bool validar = true, para_o_querido_do_usuario = false;

        system("cls");
        printf("\t  ----'ALTERAR'----\n\n");
        printf("> Digite o codigo do produto a ser alterado: ");
        scanf("%d", &codigo_val);
        fflush(stdin);

        while(fread(&prod, sizeof(stru), 1, fptr) == 1)
        {
            if(codigo_val == prod.codigo)
            {
                int confirmar;
                bool receba = false;
                validar = false;

                printf("\n> Produto %s encontrado\n", prod.nome);

                do//Validar p o usuario n digitar algo por engano
                {
                    prod.quantidade = 0;

                    if(para_o_querido_do_usuario)
                    {
                        system("cls");

                        printf("\t  ----'ALTERAR'----\n\n");
                         printf("> Digite o codigo do produto a ser alterado: ");
                        printf("\n\n> Produto %s encontrado", prod.nome);
                        printf("\n\n|> DIGITE UM NUMERO VALIDO!\n");
                    }

                    printf("\n|Digite a nova quantidade: ");
                    scanf("%d", &prod.quantidade);//Armazenando diretamente da struct pq no final n vai fazer diferença
                    fflush(stdin);

                    para_o_querido_do_usuario = true;

                }while(prod.quantidade <= 0);

                printf("\n");
                system("pause");
                system("cls");

                do//Loop p a confirmação de alteração
                {   system("cls");
                    printf("\t  ----'ALTERAR'----\n\n");
                    printf("> Confirmar alteracao?\n");
                    printf("\n[1] - SIM\n");
                    printf("[2] - NAO\n\n");

                    if(receba)
                    {
                        printf("|> DIGITE UM NUMERO VALIDO!\n\n");//Validação de número inválido
                    }

                    printf("|: ");
                    scanf("%d", &confirmar);
                    fflush(stdin);

                    switch(confirmar)//Optei por switch para uma melhor validação de input com o default
                    {
                        case 1:

                        system("cls");
                        fseek(fptr, -sizeof(stru), SEEK_CUR);
                        //fptr: Aponta p posição atual do arquivo
                        //-sizeof: O "-" vem para que o dado alterado não seja adicionado como um novo registro, sendo o caractere um indicativo q o registro anterior é q receberá o dado
                        //SEEK_CUB: É a referência a paritr da qual o deslocamento será calculado
                        //Resumindo, fptr da o dado atual do ponteiro no arquivo, -sizeof o tamanho em bytes da estrutura sendo negativa para não dar b.o de registro, SEEK_CUR usa a posição atual como ponto de partida

                        fwrite(&prod, sizeof(stru), 1, fptr);//Escrevendo o novo dado no arquivo

                        printf("\t  ----'ALTERAR'----\n\n");
                        printf("> ALTERACAO REALIZADA COM SUCESSO\n\n");
                        system("pause");
                        system("cls");

                        break;

                        case 2:

                            system("cls");
                            printf("\t  ----'ALTERAR'----\n\n");
                            printf("> ALTERACAO CANCELADA\n\n");
                            system("pause");
                            system("cls");

                        break;

                        default:
                        receba = true;
                    }
            
                }while(confirmar != 2 && confirmar != 1);
                break;
            }
        }

        if(validar)
        {
            printf("\n-> PRODUTO NAO ENCONTRADO\n\n");
            system("pause");
            system("cls");
        }
        fclose(fptr);
    }
}

void alterar_nome()
{
    FILE * fptr;
    fptr = fopen("cadastro", "rb+");

    if(fptr == NULL)
    {
        system("cls");
        printf("\n> ERRO AO ABRIR O ARQUIVO!\n\n");
        system("pause");//Pausando o terminal caso o arquivo não consiga ser aberto
        system("cls");
        fclose(fptr);
    }
    else
    {
        int codigo_val, tamanho;//Declarando variáveis
        bool validar = false;
        stru prod;

            system("cls");
            printf("\t  ----'ALTERAR'----\n\n");
            printf("> Digite o codigo do produto a ser alterado: ");
            scanf("%d", &codigo_val);
            fflush(stdin);

        while(fread(&prod, sizeof(stru), 1, fptr) == 1)
        {
            if(codigo_val == prod.codigo)
            {
                int confirmar;//Variavel para a confirmação de alteração
                bool receba = false;//Variaveis para a confirmação de alteração
                validar = true;

                printf("\n> Produto %s encontrado", prod.nome);
                printf("\n\n|Digite o novo nome: ");
                fgets(prod.nome, 50, stdin);//Armazenando diretamente da struct pq no final n vai fazer diferença
                fflush(stdin);

                prod.nome[strcspn(prod.nome, "\n")] = '\0';//Tirando a quebra de linha

                tamanho = strlen(prod.nome);//Armazenando o tamanho exato em inteiro do tamanho da palavra em uma variável separada

                for(int i = 0; i < tamanho; i++)//Loop para aumentar todas as letras(optei fazer isso p evitar qualquer engano sem intenção do usuário ao digitar)
                {
                    prod.nome[i] = toupper(prod.nome[i]);
                }

                printf("\n");
                system("pause");

                do//Loop p a confirmação de alteração
                {   system("cls");
                    printf("\t  ----'ALTERAR'----\n\n");
                    printf("> Confirmar alteracao?\n");
                    printf("\n[1] - SIM\n");
                    printf("[2] - NAO\n\n");

                    if(receba)
                    {
                        printf("|> DIGITE UM NUMERO VALIDO!\n\n");//Validação de número inválido
                    }

                    printf("|: ");
                    scanf("%d", &confirmar);
                    fflush(stdin);

                    switch(confirmar)//Optei por switch para uma melhor validação de input com o default
                    {
                        case 1:

                        system("cls");
                        fseek(fptr, -sizeof(stru), SEEK_CUR);
                        //fptr: Aponta p posição atual do arquivo
                        //-sizeof: O "-" vem para que o dado alterado não seja adicionado como um novo registro, sendo o caractere um indicativo q o registro anterior é q receberá o dado
                        //SEEK_CUB: É a referência a paritr da qual o deslocamento será calculado
                        //Resumindo, fptr da o dado atual do ponteiro no arquivo, -sizeof o tamanho em bytes da estrutura sendo negativa para não dar b.o de registro, SEEK_CUR usa a posição atual como ponto de partida

                        fwrite(&prod, sizeof(stru), 1, fptr);//Escrevendo o novo dado no arquivo

                        printf("\t  ----'ALTERAR'----\n\n");
                        printf("> ALTERACAO REALIZADA COM SUCESSO\n\n");
                        system("pause");
                        system("cls");

                        break;

                        case 2:

                            system("cls");
                            printf("\t  ----'ALTERAR'----\n\n");
                            printf("> ALTERACAO CANCELADA\n\n");
                            system("pause");
                            system("cls");

                        break;

                        default:
                        receba = true;
                    }
            
                }while(confirmar != 2 && confirmar != 1);
                break;
            }
        }

        if(!validar)
        {
            printf("\n-> PRODUTO NAO ENCONTRADO\n\n");
            system("pause");
            system("cls");
        }
        fclose(fptr);
    }
}

void alterar()
{
    int escolha;
    bool receba = false;

    do
    {
        escolha = 0;//Inicializo como 0 para evitar possiveis problemas

        system("cls");
        printf("\t  ----'ALTERAR'----\n\n");//Menu para alteração de dados
        printf("> Digite o que deseja alterar no produto:\n\n");
        printf("[1] - NOME\n");
        printf("[2] - QUANTIDADE\n");
        printf("[3] - PRECO\n");
        printf("[4] - VOLTAR\n");

        if(receba)//Validação de número inválido
        {
            printf("\n|> DIGITE UM NUMERO VALIDO!\n");
            receba = false;
        }

        printf("\n|: ");
        scanf("%d", &escolha);
        fflush(stdin);

        switch(escolha)//Optei em usar funções para uma melhor organização
        {
            case 1:

            alterar_nome();//Chamando a função alterar_nome

            break;

            case 2:

            alterar_quantidade();//Chamando a função alterar_quantidade

            break;

            case 3:

            alterar_preco();//Chamando a função alterar_preco

            break;

            default:
            receba = true;
        }
    }
    while(escolha != 4);    

    system("cls");
}

void exibir()
{
    FILE * fptr;
    fptr = fopen("cadastro", "rb");//Abrindo arquivo no modo Read Binary(RB) - para a leitura do arquivo 

    if(fptr == NULL)
    {
        system("cls");
        printf("\n> ERRO AO ABRIR O ARQUIVO!\n\n");
        system("pause");//Pausando o terminal caso o arquivo não consiga ser aberto
        system("cls");
        fclose(fptr);
    }
    else
    {
        system("cls");
        printf("\t  ----'EXIBIR'----\n\n");
        printf("> Dados do estoque:\n\n");
        stru prod;//Declarando variável que receberá os valores do arquivo

        while(fread(&prod, sizeof(stru), 1, fptr) == 1)
        {
            printf("|NOME............%s\n|QUANTIDADE.......%d Unit.\n|PRECO.......R$ %.2f Unit.\n|CODIGO.................%d\n\n", prod.nome, prod.quantidade, prod.preco, prod.codigo);
            //Embora eu tenha salvado as informações no arquivo como vetor, não há a necessidade de usar vetor para a leitura
        }

        fclose(fptr);
        system("pause");
        system("cls");
    }
}

void pesquisa()
{

    FILE * fptr;
    fptr = fopen("cadastro", "rb");

    if(fptr == NULL)
    {
        system("cls");
        printf("\n> ERRO AO ABRIR O ARQUIVO!\n\n");
        system("pause");//Pausando o terminal caso o arquivo não consiga ser aberto
        system("cls");
        fclose(fptr);
    }
    else
    {
        int pesquisar;//Declarando variáveis
        bool validar = false;
        stru prod;

        system("cls");
        printf("\t  ----'PESQUISA'----\n\n");
        printf("> Digite o codigo do produto para a pesquisa: ");
        scanf("%d", &pesquisar);
        fflush(stdin);

        while(fread(&prod, sizeof(stru), 1, fptr) == 1)
        {
            if(prod.codigo == pesquisar)
            {
                printf("\n-> Produto encontrado:\n\n");
                printf("|NOME............%s\n|QUANTIDADE.......%d Unit.\n|PRECO.......R$ %.2f Unit.\n|CODIGO.................%d\n\n", prod.nome, prod.quantidade, prod.preco, prod.codigo);
                validar = true;
                system("pause");
                system("cls");
                break;
            }
        }
        if(!validar)
        {
            printf("\n-> PRODUTO NAO ENCONTRADO\n\n");
            system("pause");
            system("cls");
        }

        fclose(fptr);
    }
}

void cadastro()
{
    FILE * fptr;//Definindo ponteiro para as operações com arquivo nesta função
    fptr = fopen("cadastro", "ab");//Abrindo arquivo no modo Append Binary(AB)

    if(fptr ==  NULL)//Validação da abertura de arquivo
    {
        system("cls");
        printf("\n> ERRO AO ABRIR O ARQUIVO!\n\n");
        system("pause");//Pausando o terminal caso o arquivo não consiga ser aberto
        system("cls");
        fclose(fptr);
    }
    else
    {
        int qtde, finalizar, tamanho;//Declarando variáveis
        bool val = false;//VAriável de validção de toda a função cadastro

        do
        {
            qtde = 0;//Inicializo como zero para evitar problema

            system("cls");//Limpando o terminal

            printf("\t  ----'CADASTRO'----\n\n");

            if(val)//Validação do quantidade de produtos cadastrados
            {
                printf("|> DIGITE UM NUMERO VALIDO!\n\n");
            }

            printf("|Digite a quantidade de produtos para cadastro: ");
            scanf("%d", &qtde);
            fflush(stdin);

            val = true;

        }while(qtde <= 0);

         stru prod[qtde];//Declarando atributos de produto a prod, sendo ainda um vetor para quantidade diversas de produtos
         val = false;

        for(int i = 0; i < qtde; i++)//Inicializando loop de acordo com a quantidade digitada pelo usuário
        {
            system("cls");
            printf("\t  ----'CADASTRO'----\n");

            prod[i].codigo = codiguinho++;

            printf("\n|Digite o nome do produto %d: ", i + 1);
            fgets(prod[i].nome, 50, stdin);//Input do nome do produto
            fflush(stdin);//Limpando buffer

            prod[i].nome[strcspn(prod[i].nome, "\n")] = '\0';//Tirando a quebra de linha

            tamanho = strlen(prod[i].nome);//Armazenando o tamanho exato em inteiro do tamanho da palavra em uma variável separada

            for(int j = 0; j < tamanho; j++)//Loop para aumentar todas as letras(optei fazer isso p evitar qualquer engano sem intenção do usuário ao digitar)
            {
                prod[i].nome[j] = toupper(prod[i].nome[j]);
            }

            do//Validando a quantidade de produto
            {
                system("cls");
                prod[i].quantidade = 0;
                printf("\t  ----'CADASTRO'----\n");

                if(val)
                {
                    printf("\n> DIGITE UM NUMERO VALIDO!\n");
                }

                printf("\n|Digite a quantidade do produto %s a ser cadastrado: ", prod[i].nome);
                scanf("%d", &prod[i].quantidade);//Input de quantidade de produto
                fflush(stdin);

                val = true;

            }while(prod[i].quantidade <= 0);

            val = false;

            do//Validando o preço do produto
            {
                system("cls");
                prod[i].preco = 0;
                printf("\t  ----'CADASTRO'----\n");

                if(val)
                {
                    printf("\n> DIGITE UM NUMERO VALIDO!\n");
                }

                printf("\n|Digite o preco do produto %s: R$ ", prod[i].nome);
                scanf("%f", &prod[i].preco);//Input do preço do produto
                fflush(stdin);

                val = true;
            }
            while(prod[i].preco <= 0);

            printf("\n");
            system("pause");
            system("cls");
        }

        val = false;

        do//Loop para a confirmação do cadastro
        {
            system("cls");
            printf("\t  ----'CADASTRO'----\n");
            printf("\n> Deseja confirmar o cadastro de %d novo(s) produtos?\n", qtde);
            printf("\n[1] - SIM\n");
            printf("[2] - NAO\n\n");

            if(val)
            {
                printf("|> DIGITE UM NUMERO VALIDO!\n\n");//Validação de número inválido
            }

            printf(":| ");
            scanf("%d", &finalizar);
            fflush(stdin);

            switch(finalizar)//Optei por switch na escolha para uma melhor validação com o uso de default
            {
                case 1:

                system("cls");

                    for(int i = 0; i < qtde; i++)
                    {
                        fwrite(&prod[i], sizeof(stru), 1, fptr);
                    }

                    salvar_codigo();
                    fclose(fptr);

                printf("\t  ----'CADASTRO'----\n\n");
                printf("> CADASTRO REALIZADO COM SUCESSO\n\n");
                system("pause");
                system("cls");

                break;

                case 2:

                fclose(fptr);
                system("cls");
                printf("\t  ----'CADASTRO'----\n\n");
                printf("> CADASTRO CANCELADO\n\n");
                system("pause");
                system("cls");

                break;
                
                default:
                val = true;
            }

        }
        while(finalizar != 2 && finalizar != 1);   
    }
}

int main()
{
    validar_codigo();//Já inicializa a validação do código do produto

    int escolha;//Declarando variáveis
    bool invalido = false;

    do
    {
        escolha = 0;//Inicializo como zero para evitar problema

        system("cls");
        printf("\t  ----'ESTOQUE'----\n\n");//Menu de escolha
        printf("> Digite o que deseja:\n\n");
        printf("[1] - CADASTRAR\n");
        printf("[2] - PESQUISAR\n");
        printf("[3] - ALTERAR\n");
        printf("[4] - EXIBIR\n");
        printf("[5] - SAIR\n");

        if(invalido)//Validação de número inválido
        {
            printf("\n|> DIGITE UM NUMERO VALIDO!\n");
            invalido = false;
        }

        printf("\n|: ");
        scanf("%d", &escolha);//input de escolha do usuário
        fflush(stdin);

            switch(escolha)//Escolhas possíveis do menu
            {
                case 1:

                cadastro();//Chamando a função cadastro

                break;

                case 2:

                pesquisa();//Chamando a função pesquisa

                break;

                case 3:

                alterar();//Chamando a função alterar

                break;

                case 4:

                exibir();//Chamando a função exibir

                break;

                default:
                invalido = true;
            }
    }
    while(escolha != 5);

    system("cls");
    printf("\t  ----'ESTOQUE'----\n\n");//Exibição de fechamento do programa
    printf("|PROGRAMA FINALIZADO\n\n");
}