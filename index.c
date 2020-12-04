/** Programa de uma eleição, é opicional a execução da parte do administrador, devendo ser executada apenas uma vez para cadastro**/
/* gera 3 arquivos eleitores, gestor, e fiscal, todos conteem uma estrutra id:nome*/
/* PROGRAMA MOLDADO PARA 3 FISCAIS E 2 GESTORES, MUDANÇA NESSES VALORES DEVEM SER FEITAS NAS VARIVAEIS INT VET GESTOR NOMEE AFINS**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/***ESCOPO****/
int cadastroEleitor();
int cadastroCandidato();
void votacao();
void repeticao();
void recebeNome();
/*** FIM ESCOPO***/

/****AUXILIARES***/
int vet[2];
int *vetGestor = &vet[2];
const char *Gestornome[2];
/****FIM AUXILIARES***/

/**ADMINSTRADOR**/
/*** CADASTRO ELEITOR**/
int cadastroEleitor()
{

    typedef struct
    {
        int indentificador;
        char nome[100];
    } BDeleitores;
    BDeleitores *eleitor;
#define tam 5
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
        scanf("%d", &eleitor[i].indentificador);
        setbuf(stdin, NULL);
        printf("Digite seu nome completo: ");
        fgets(eleitor[i].nome, 100, stdin);
    }
    for (int i = 0; i < tam; i++)
    {
        fprintf(eleitores, "Identificador:%d : Nome:%s", eleitor[i].indentificador, eleitor[i].nome);
    }

    printf("\n Dados cadastrados com sucesso!\n");
    fclose(eleitores);
}
/**FIM CADASTRO ELEITOR***/

/**CADASTRO CANDIDADOS GESTOR,FISCAL**/
int cadastroCandidato()
{
#define tamF 3

    typedef struct
    {
        int indentificador;
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
        scanf("%d", &fiscal[i].indentificador);
        setbuf(stdin, NULL);
        printf("\nDigite seu nome para candidado como fiscal:");
        fgets(fiscal[i].nome, 100, stdin);
    }
    for (int i = 0; i < tamF; i++)
    {
        fprintf(Fiscal_arq, "Identificador:%d : Nome:%s", fiscal[i].indentificador, fiscal[i].nome);
    }
    printf("\nDados Cadastrados com sucesso!\n");
    fclose(Fiscal_arq);
/**CADASTRO GESTOR**/
#define tamG 2
    typedef struct
    {
        int indentificador;
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
        scanf("%d", &gestor[i].indentificador);
        vetGestor[i] = gestor[i].indentificador;
        setbuf(stdin, NULL);
        printf("\nDigite seu nome para candidado como gestor:");
        fgets(gestor[i].nome, 100, stdin);
        Gestornome[i] = gestor[i].nome;
    }
    for (int i = 0; i < tamG; i++)
    {
        fprintf(gestor_Arq, "Identificador:%d  Nome:%s", gestor[i].indentificador, gestor[i].nome);
    }
    printf("\n Dados Cadastrados com sucesso!\n");
    fclose(gestor_Arq);
}
void votacao()
{
    
    int indetificador;
    char nome[100];
    int voto = 0;
    FILE *gestor_Arq;
    FILE *fiscal_Arq;
    FILE *contabiliza_Arq;

    gestor_Arq = fopen("gestor.txt", "r");
    //fiscal_Arq = fopen("Fiscal.txt","r");
    contabiliza_Arq = fopen("Contabilização_votos.txt", "a");
    printf("Digite seu voto");
    scanf("%d", &voto);
    fprintf(contabiliza_Arq, "%d\n", voto);

    fclose(contabiliza_Arq);
    printf("%d\n",vetGestor[0]);
    printf("%s\n",Gestornome[0]);
}

void registro()
{
    char gestor1[100];
    char gestor2[100];
    int voto1;
    int voto2;
    char nome[100];
    int id;
    int aux = 0;
    FILE *cont;
    FILE *gestor;
    cont = fopen("Contabilização_votos.txt", "r");
    gestor = fopen("gestor.txt", "r");
    while (fscanf(cont, " %d", &id) != EOF)
    {
        if (id == 12312)
        {
            voto1++;
        }
        else if (id == 1231)
        {
            voto2++;
        }
    }
    printf("%d\n", voto1);
    printf("%d\n", voto2);
    fclose(gestor);
    fclose(cont);
}
/*void RecebeNome()
{
    int recebeNumero;
    int guardaNumero[2];
    char nome[100];
    char *guardaNome[2];
    
    FILE *recebe;
    recebe = fopen("gestor.txt","r");
    while(fscanf(recebe,"%d %s",&recebeNumero,nome) != EOF)
    {
        fgets(GestorBaseLocal.voto,)
}*/

int main(void)
{
    //cadastroEleitor();
    cadastroCandidato();
    votacao();
    //registro();
    //RecebeNome();
}