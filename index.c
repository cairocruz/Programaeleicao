/** Programa de uma eleição, é opicional a execução da parte do administrador, devendo ser executada apenas uma vez para cadastro**/
/* gera 3 arquivos, eleitores, gestor, e fiscal, todos conteem uma estrutra id:nome*/
/* PROGRAMA MOLDADO PARA 3 FISCAIS E 2 GESTORES, MUDANÇA NESSES VALORES DEVEM SER FEITAS NAS VARIVAEIS INT VET GESTORNOME RESPECTIVAMENTE A MESMA LOGICA SE APLICA AO FISCAR**/
/* a quantidade de eleitores aceita para o funcionamento perfeito do programa é de 5 eleitores*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/***ESCOPO****/
int cadastroEleitor();
int cadastroCandidato();
int registro();
int verificador();
int menu();
int acessoAdmin();
int eleicao();
int retorno();
/*** FIM ESCOPO***/
#define tamF 3
#define tamG 2
#define tam 5

/****AUXILIARES***/
typedef struct
{
    char identificador[8];
    char nome[100];
} aux;
aux auxFiscal[3];
aux auxGestor[2];
int flagReturn = 0;
/****FIM AUXILIARES***/

/**ADMINSTRADOR**/
/*** CADASTRO ELEITOR**/
int cadastroEleitor() // OK
{
    flagReturn = 3;
    typedef struct
    {
        char indentificador[8];
        char nome[100];
    } BDeleitores;
    BDeleitores *eleitor;

    FILE *eleitores;

    eleitor = (BDeleitores *)malloc(sizeof(BDeleitores) * tam);
    eleitores = fopen("eleitores.txt", "w");
    if (eleitores == NULL)
    {
        printf("Erro na criação da base de dados dos eleitores");
        return 1;
    }
    printf("\n--------------Bem vindo ao cadastro de novos eleitores--------\n");

    for (int i = 0; i < tam; i++)
    {
        printf("\nPorfavor digite seu rg,somente numeros: ");
        scanf("%s", eleitor[i].indentificador);
        setbuf(stdin, NULL);
        printf("Digite seu nome completo: ");
        fgets(eleitor[i].nome, 100, stdin);
    }
    for (int i = 0; i < tam; i++)
    {
        fprintf(eleitores, "%s %s", eleitor[i].indentificador, eleitor[i].nome);
    }

    printf("\n Dados cadastrados com sucesso!\n");

    fclose(eleitores);
    retorno();
}

int registro(aux auxFiscal[], aux auxGestor[])
{
    flagReturn = 2;
    /*registro de variaveis para comparação*/
    char idFisUm[8];
    char idFisDois[8];
    char idFisTres[8];
    char idGestUm[8];
    char idGestDois[8];
    /*FIM REGISTRO DE VARIVAEIS PARA COMPARAÇÃO*/

    /*ATRIBUIÇÃO DE VALORES PARA AS VARIAVEIS DE COMPARAÇÃO*/
    strcpy(idFisUm, auxFiscal[0].identificador);
    strcpy(idFisDois, auxFiscal[1].identificador);
    strcpy(idFisTres, auxFiscal[2].identificador);
    strcpy(idGestUm, auxGestor[0].identificador);
    strcpy(idGestDois, auxGestor[1].identificador);
    /*FIM DA ATRIBUIÇÃO DE VALORES PARA AS VARIVAEIS DE COMPARAÇÃO*/
    /*RECEPTORES DE VOTOS*/
    int vFiscalUm = 0;
    int vFiscalDois = 0;
    int vFiscalTres = 0;
    int vGestorUm = 0;
    int vGestorDois = 0;
    /*FIM RECEPTORES DE VOTOS*/

    typedef struct
    {
        char indentifcadorRecebido[8];
    } contagem;
    contagem *recebeContagem;
    recebeContagem = (contagem *)malloc(sizeof(contagem *) * 3);
    FILE *fiscal;
    FILE *contabilFiscal;
    FILE *gestor;
    FILE *contabilGestor;
    char identificador[8];
    char nome[100]; //variavel para evitar erros de leitura
    char votos[8];
    int nulo = 0;
    int branco = 0;
    int vetorFiscalVoto[3];
    int vetorGestorVoto[2];
    int guardaIndiceF = 0;
    int guardaIndiceG = 0;
    int maiorFiscal = 0;
    int maiorGestor = 0;
    fiscal = fopen("Fiscal.txt", "r");
    gestor = fopen("gestor.txt", "r");
    contabilFiscal = fopen("Contabilização_votosFiscal.txt", "r");
    contabilGestor = fopen("Contabalização_votosGestor.txt", "r");
    if (fiscal == NULL || contabilFiscal == NULL)
    {
        printf("Impossivel achar a base de fiscais");
    }
    if (gestor == NULL || contabilGestor == NULL)
    {
        printf("Impossivel achar a base de gestor\n");
    }
    /**CONTAGEM DE VOTOS FISCAL**/
    while (fscanf(contabilFiscal, "%s", votos) != EOF)
    {
        if (strcmp(idFisUm, votos) == 0)
        {
            vFiscalUm++;
        }
        else if (strcmp(idFisDois, votos) == 0)
        {
            vFiscalDois++;
        }
        else if (strcmp(idFisTres, votos) == 0)
        {
            vFiscalTres++;
        }
        else if (strcmp("000", votos) == 0)
        {
            branco++;
        }
        else
        {
            nulo++;
        }
    }
    /**FIM CONTAGEM DE VOTOS FISCAL**/

    /**CONTAGEM DE VOTOS GESTOR**/
    while (fscanf(contabilGestor, "%s", votos) != EOF)
    {
        if (strcmp(idGestUm, votos) == 0)
        {
            vGestorUm++;
        }
        else if (strcmp(idGestDois, votos) == 0)
        {
            vGestorDois++;
        }
        else if (strcmp("000", votos) == 0)
        {
            branco++;
        }
        else
        {
            nulo++;
        }
    }
    vetorFiscalVoto[0] = vFiscalUm;
    vetorFiscalVoto[1] = vFiscalDois;
    vetorFiscalVoto[2] = vFiscalTres;
    vetorGestorVoto[0] = vGestorUm;
    vetorGestorVoto[1] = vGestorDois;
    /*analise do maior entre fiscal e gestor*/
    for (int i = 0; i < 3; i++)
    {
        if (vetorFiscalVoto[i] > maiorFiscal)
        {
            maiorFiscal = vetorFiscalVoto[i];
            guardaIndiceF = i;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (vetorGestorVoto[i] > maiorGestor)
        {
            maiorGestor = vetorGestorVoto[i];
            guardaIndiceG = i;
        }
    }

    /*print de forma mais votado menos votado*/
    printf("Fiscal:\n");
    if (guardaIndiceF == 0)
    {
        printf("%s", auxFiscal[0].nome);
        if (vFiscalDois > vFiscalTres)
        {
            printf("%s", auxFiscal[1].nome);
            printf("%s", auxFiscal[2].nome);
        }
        else
        {
            printf("%s", auxFiscal[2].nome);
            printf("%s", auxFiscal[1].nome);
        }
    }
    else if (guardaIndiceF == 1)
    {
        printf("%s", auxFiscal[1].nome);
        if (vFiscalUm > vFiscalTres)
        {
            printf("%s", auxFiscal[0].nome);
            printf("%s", auxFiscal[2].nome);
        }
        else
        {
            printf("%s", auxFiscal[2].nome);
            printf("%s", auxFiscal[0].nome);
        }
    }
    else if (guardaIndiceF == 2)
    {
        printf("%s", auxFiscal[2].nome);
        if (vFiscalUm > vFiscalDois)
        {
            printf("%s", auxFiscal[0].nome);
            printf("%s", auxFiscal[1].nome);
        }
        else
        {
            printf("%s", auxFiscal[1].nome);
            printf("%s", auxFiscal[0].nome);
        }
    }
    /*FIM PRINT DE fiscais*/
    /*print de gestores*/
    printf("Gestores:\n");
    if (guardaIndiceG == 0)
    {
        printf("%s", auxGestor[guardaIndiceG].nome);
        printf("%s", auxGestor[1].nome);
    }
    else
    {
        printf("%s", auxGestor[1].nome);
        printf("%s", auxGestor[0].nome);
    }
    printf("\nBrancos:%d Nulos:%d\n", branco, nulo);
    /*fim print de gestores*/
    //printf("fiscal mais votado %s, gestor mais votado: %s, votos nulos:%d, votos em branco:%d",auxFiscal[guardaIndiceF].nome,auxGestor[guardaIndiceG].nome,nulo,branco);
    fclose(fiscal);
    fclose(gestor);
    fclose(contabilFiscal);
    fclose(contabilGestor);
    retorno();
}
/**FIM CADASTRO ELEITOR***/

/**CADASTRO CANDIDADOS GESTOR,FISCAL**/
int cadastroCandidato(aux auxFiscal[], aux auxGestor[]) // OK/ FALTLA GUARDAR LOCALMENTE OS DADOS PARA A  CONTABILIZAÇÃO DOS VOTOS... VALIDADO MAS NECESSARIO REVISAO
{
    flagReturn = 1;
    typedef struct
    {
        char indentificador[8];
        char nome[100];
    } BDfiscal;
    BDfiscal *fiscal;
    FILE *Fiscal_arq;

    fiscal = (BDfiscal *)malloc(sizeof(BDfiscal) * tamF);
    Fiscal_arq = fopen("Fiscal.txt", "w");
    if (Fiscal_arq == NULL)
    {
        printf("Erro na criação da base de dados dos fiscais");
        return 1;
    }
    printf("\n------------------------ Bem vindo ao cadastro de Fiscais-----------");
    for (int i = 0; i < tamF; i++)
    {
        printf("\n Porfavor digite seu número identificador:");
        scanf("%s", fiscal[i].indentificador);
        strcpy(auxFiscal[i].identificador, fiscal[i].indentificador);
        setbuf(stdin, NULL);
        printf("\nDigite seu nome para candidado como fiscal:");
        fgets(fiscal[i].nome, 100, stdin);
        strcpy(auxFiscal[i].nome, fiscal[i].nome);
    }
    for (int i = 0; i < tamF; i++)
    {
        fprintf(Fiscal_arq, "%s  %s", fiscal[i].indentificador, fiscal[i].nome);
    }
    printf("\nDados Cadastrados com sucesso!\n");

    fclose(Fiscal_arq);

    /**CADASTRO GESTOR** --OK*/

    typedef struct
    {
        char indentificador[8];
        char nome[100];
    } BDgestor;
    BDgestor *gestor;
    FILE *gestor_Arq;
    gestor = (BDgestor *)malloc(sizeof(BDgestor) * tamG);
    gestor_Arq = fopen("gestor.txt", "w");
    if (gestor_Arq == NULL)
    {
        printf("Erro na criação da base de dados dos gestores");
        return 1;
    }
    printf("\n---------------- Bem vindo ao cadastro de gestores-----------\n");
    for (int i = 0; i < tamG; i++)
    {
        printf("\n Porfavor digite seu número identificador:");
        scanf("%s", gestor[i].indentificador);
        strcpy(auxGestor[i].identificador, gestor[i].indentificador);
        setbuf(stdin, NULL);
        printf("\nDigite seu nome para candidado como gestor:");
        fgets(gestor[i].nome, 100, stdin);
        strcpy(auxGestor[i].nome, gestor[i].nome);
    }
    for (int i = 0; i < tamG; i++)
    {
        fprintf(gestor_Arq, "%s  %s", gestor[i].indentificador, gestor[i].nome);
    }
    printf("\n Dados Cadastrados com sucesso!\n");
    retorno();
}

int acessoAdmin()
{
    int op = 0;
    printf("\nDigite a opção desejada:\n 1- CadastroEleitor, 2- CadastroCandidato, 3- Registro, 4-Eleicao\n");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        cadastroEleitor();
        break;
    case 2:
        cadastroCandidato(auxFiscal, auxGestor);
        break;
    case 3:
        registro(auxFiscal, auxGestor);
        break;
    case 4:
        eleicao();
        break;
    default:
        printf("Opção invalida");
        break;
    }
}
int eleicao()
{
    printf("\n começo da eleicao:\n");
    verificador();
    retorno();
}

int menu()
{
    int op = 0;
    printf("Digite a opção Desejada:\n 1-Administrador\n 2-Eleicao\n 3-Sair\n");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        acessoAdmin();
        break;
    case 2:
        eleicao();
        break;
    case 3:
        return 0;
        break;
    default:
        printf("Opcao invalida");
        break;
    }
}

int retorno()
{
    int op;
    printf("\nDeseja voltar a opção anterior?\n 1-sim\n 2-não\n");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        if (flagReturn == 1)
        {
            cadastroCandidato(auxFiscal, auxGestor);
            break;
        }
        else if (flagReturn == 2)
        {
            registro(auxFiscal, auxGestor);
            break;
        }
        else if (flagReturn == 3)
        {
            cadastroEleitor();
            break;
        }
        else if (flagReturn == 4)
        {
            verificador();
            break;
        }
        break;
    case 2:
        menu();
        break;
    default:
        printf("opcao invalida");
        retorno();
        break;
    }
}
int verificador() // OK
{
    flagReturn = 4;
    char recebeNome[100];
    char verificaRepIdentidade[100];
    char verificaRepNome[100];
    char recebeIdentificador[8];
    int votoGestor = 0;
    int votoFiscal = 0;
    char Identificador[8];
    int flag = 0;
    int auxverify = 0;
    FILE *file;
    FILE *validacao;
    FILE *contabiliza_Arq_Fiscal;
    FILE *contabiliza_Arq_Gestor;
    FILE *verificaRepeti;
    file = fopen("eleitores.txt", "r");
    validacao = fopen("validaEleitor.txt", "a+");
    contabiliza_Arq_Fiscal = fopen("Contabilização_votosFiscal.txt", "a");
    contabiliza_Arq_Gestor = fopen("Contabalização_votosGestor.txt", "a");
    verificaRepeti = fopen("validaEleitor.txt", "r");
    printf("Digite seu rg:");
    scanf("%s", Identificador);
    setbuf(stdin, NULL);
    if (file == NULL)
    {
        printf("Erro na leitura do arquivo de eleitores");
        return 0;
    }
    if (validacao == NULL)
    {
        printf("Erro na criação da validacao");
    }
    while (fscanf(file, "%s %s", recebeIdentificador, recebeNome) != EOF)
    {
        if (strcmp(Identificador, recebeIdentificador) == 0)
        {
            while (fscanf(validacao, "%s %s", verificaRepIdentidade, verificaRepNome) != EOF)
            {
                if (strcmp(Identificador, verificaRepIdentidade) == 0)
                {
                    printf("voto não contabilizado você já votou\n");
                    flag = 1;
                    break;
                }
            }
            fprintf(validacao, "%s %s\n", Identificador, recebeNome);
        }
        else if (strcmp(Identificador, recebeIdentificador) != 0)
        {
            auxverify++;
        }
        if (auxverify == 5)
        {
            printf("Eleitor não cadastrado\n");
            return 0;
        }
    }
    if (flag == 0)
    {
        printf("Digite a identificação do seu candidato a fiscal:");
        scanf("%d", &votoFiscal);
        printf("Digite a identificação do seu candidato para gestor:");
        scanf("%d", &votoGestor);
        fprintf(contabiliza_Arq_Fiscal, "%d\n", votoFiscal);
        fprintf(contabiliza_Arq_Gestor, "%d\n", votoGestor);
    }
    flag = 0;
    fclose(file);
    fclose(validacao);
    fclose(contabiliza_Arq_Fiscal);
    fclose(contabiliza_Arq_Gestor);
    retorno();
}

int main(void)
{

    //cadastroEleitor();
    //cadastroCandidato(auxFiscal, auxGestor);
    menu();
    //verificador();
    //registro(auxFiscal, auxGestor);
}