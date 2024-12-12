#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

HINSTANCE handle;

// Declara��o de ponteiros de fun��o
typedef int (*AbreConexaoImpressora_t)(int, const char *, const char *, int);
typedef int (*FechaConexaoImpressora_t)();
typedef int (*ImpressaoTexto_t)(const char *, int, int, int);
typedef int (*ImpressaoQRCode_t)(const char *, int, int);
typedef int (*ImpressaoCodigoBarras_t)(int, const char *, int, int, int);
typedef int (*ImprimeXMLSAT_t)(const char *, int);
typedef int (*ImprimeXMLCancelamentoSAT_t)(const char *, const char *, int);
typedef int (*SinalSonoro_t)(int, int, int);
typedef int (*AvancaPapel_t)(int);
typedef int (*Corte_t)(int);
typedef int (*AbreGavetaElgin_t)();
typedef int (*AbreGaveta_t)(int, int, int);

AbreConexaoImpressora_t AbreConexaoImpressora;
FechaConexaoImpressora_t FechaConexaoImpressora;
ImpressaoTexto_t ImpressaoTexto;
ImpressaoQRCode_t ImpressaoQRCode;
ImpressaoCodigoBarras_t ImpressaoCodigoBarras;
ImprimeXMLSAT_t ImprimeXMLSAT;
ImprimeXMLCancelamentoSAT_t ImprimeXMLCancelamentoSAT;
SinalSonoro_t SinalSonoro;
AvancaPapel_t AvancaPapel;
Corte_t Corte;
AbreGavetaElgin_t AbreGavetaElgin;
AbreGaveta_t AbreGaveta;

int carregarFuncoes() {
    handle = LoadLibrary("E1_Impressora01.dll");
    if (!handle) {
        fprintf(stderr, "Erro ao carregar a biblioteca.\n");
        return 0;
    }

    // Carregar as fun��es da DLL
    AbreConexaoImpressora = (AbreConexaoImpressora_t)GetProcAddress(handle, "AbreConexaoImpressora");
    FechaConexaoImpressora = (FechaConexaoImpressora_t)GetProcAddress(handle, "FechaConexaoImpressora");
    ImpressaoTexto = (ImpressaoTexto_t)GetProcAddress(handle, "ImpressaoTexto");
    ImpressaoQRCode = (ImpressaoQRCode_t)GetProcAddress(handle, "ImpressaoQRCode");
    ImpressaoCodigoBarras = (ImpressaoCodigoBarras_t)GetProcAddress(handle, "ImpressaoCodigoBarras");
    ImprimeXMLSAT = (ImprimeXMLSAT_t)GetProcAddress(handle, "ImprimeXMLSAT");
    ImprimeXMLCancelamentoSAT = (ImprimeXMLCancelamentoSAT_t)GetProcAddress(handle, "ImprimeXMLCancelamentoSAT");
    SinalSonoro = (SinalSonoro_t)GetProcAddress(handle, "SinalSonoro");
    AvancaPapel = (AvancaPapel_t)GetProcAddress(handle, "AvancaPapel");
    Corte = (Corte_t)GetProcAddress(handle, "Corte");
    AbreGavetaElgin = (AbreGavetaElgin_t)GetProcAddress(handle, "AbreGavetaElgin");
    AbreGaveta = (AbreGaveta_t)GetProcAddress(handle, "AbreGaveta");

    // Verificar se todas as fun��es foram carregadas
    if (!AbreConexaoImpressora || !FechaConexaoImpressora || !ImpressaoTexto || !ImpressaoQRCode ||
        !ImpressaoCodigoBarras || !ImprimeXMLSAT || !ImprimeXMLCancelamentoSAT || !SinalSonoro ||
        !AvancaPapel || !Corte || !AbreGavetaElgin || !AbreGaveta) {
        fprintf(stderr, "Erro ao carregar as fun��es da biblioteca.\n");
        return 0;
    }
    return 1;
}

void liberarBiblioteca() {
    if (handle) {
        FreeLibrary(handle);
    }
}

void exibirMenu() {
	
	printf ("\n");
    int hashtags = 0;

    while (hashtags <= 167) {
        printf("*");
        hashtags++;
    }

    hashtags = 0;
    while (hashtags <= 75) {
        printf("*");
        hashtags++;
    }

    printf(" MENU PRINCIPAL ");

    hashtags = 0;
    while (hashtags <= 75) {
        printf("*");
        hashtags++;
    }

    hashtags = 0;
    while (hashtags <= 167) {
        printf("*");
        hashtags++;
    }

    printf("\n1 - Configurar Conexao \n2 - Abrir Conexao \n3 - Impressao Texto "
           "\n4 - Impressao QR Code \n5 - Impressao do Codigo de Barras "
           "\n6 - Impressao XML SAT \n7 - Impressao XML Canc SAT "
           "\n8 - Abrir Gaveta Elgin \n9 - Abrir Gaveta "
           "\n10 - Sinal Sonoro \n0 - Fechar Conexao e Sair\n\n");
}

void configurarConexao(int *tipo, char *modelo, char *conexao, int *parametro) {
	
    printf("\nEscolha o tipo: ");
    scanf("%d", tipo);
    printf("\nEscolha o modelo: ");
    scanf("%9s", modelo);
    printf("\nEscolha a conex�o: ");
    scanf("%9s", conexao);
    printf("\nEscolha o par�metro: ");
    scanf("%d", parametro);
    
}

void abrirConexao() {
    int tipo, parametro, ret;
    char modelo[10], conexao[10];
 
    configurarConexao(&tipo, modelo, conexao, &parametro);

    ret = AbreConexaoImpressora(tipo, modelo, conexao, parametro);
    if (ret == 0) {
        printf("Conex�o aberta com sucesso!\n");
    } else {
        printf("ERRO DE CONEX�O. Retorno: %d\n", ret);
    }
}

void impressaoTexto() {
    char texto[256];
    int alinhamento, negrito, italico;

    // Solicita ao usu�rio as informa��es para impress�o
    printf("Digite o texto a ser impresso (m�x. 255 caracteres): ");
    getchar(); // Limpa o buffer antes de fgets
    fgets(texto, sizeof(texto), stdin);

    // Remove o caractere de nova linha, se presente
    size_t len = strlen(texto);
    if (len > 0 && texto[len - 1] == '\n') {
        texto[len - 1] = '\0';
    }

    printf("Escolha o alinhamento (0 - Esquerda, 1 - Centro, 2 - Direita): ");
    scanf("%d", &alinhamento);
    printf("Negrito (0 - N�o, 1 - Sim): ");
    scanf("%d", &negrito);
    printf("It�lico (0 - N�o, 1 - Sim): ");
    scanf("%d", &italico);

    // Chama a fun��o de impress�o de texto
    int ret = ImpressaoTexto(texto, alinhamento, negrito, italico);
    if (ret == 0) {
        printf("Texto impresso com sucesso!\n");
    } else {
        printf("Erro ao imprimir texto! Retorno: %d\n", ret);
    }
}

void impressaoQRCode() {
    int ret;
    const char *dadosQRCode = "http://www.exemplo.com";
    
    // Verifica se a fun��o de impress�o de QR Code foi carregada
    if (ImpressaoQRCode) {
        ret = ImpressaoQRCode(dadosQRCode, 0, 0);  // 0, 0 s�o apenas placeholders para os par�metros
        if (ret == 0) {
            printf("QR Code impresso com sucesso!\n");
        } else {
            printf("Erro ao imprimir QR Code! Retorno: %d\n", ret);
        }
    } else {
        printf("Fun��o de impress�o de QR Code n�o carregada.\n");
    }
}

void imprimeCodigoBarras(int tipo, const char *dados, int altura, int largura, int HRI) {
    // Chama a fun��o de impress�o de c�digo de barras da DLL
    int ret = ImpressaoCodigoBarras(tipo, dados, altura, largura, HRI);

    // Verifica o retorno
    switch(ret) {
        case 0:
            printf("Dados recebidos e c�digo de barras impresso com sucesso!\n");
            break;
        case 1:
            printf("ERRO: Tipo de c�digo de barras n�o suportado!\n");
            break;
        case 2:
            printf("ERRO: Dados inv�lidos para o c�digo de barras!\n");
            break;
        case 3:
            printf("ERRO: Falha no dispositivo de impress�o!\n");
            break;
        case 4:
            printf("ERRO: Par�metros de altura ou largura inv�lidos!\n");
            break;
        default:
            printf("ERRO: C�digo de erro desconhecido. Retorno: %d\n", ret);
    }
}
// Fun��es adicionais
void imprimeXMLSAT() {
    const char *xml = "<xml>Exemplo de XML</xml>";
    int ret = ImprimeXMLSAT(xml, 0);
    switch(ret) {
        case 0:
            printf("XML SAT impresso com sucesso!\n");
            break;
        case 1:
            printf("Erro ao imprimir XML SAT. Erro: Falha no dispositivo de impress�o.\n");
            break;
        case 2:
            printf("Erro ao imprimir XML SAT. Erro: XML inv�lido.\n");
            break;
        default:
            printf("Erro ao imprimir XML SAT. Retorno: %d\n", ret);
    }
}

void imprimeXMLCancelamentoSAT() {
    const char *xml = "<xml>Exemplo de XML Cancelamento</xml>";
    const char *assQRCode = "Q5DLkpdRijIRGY6YSSNsTWK1TztHL1vD0V1Jc4spo/CEUqICEb9SFy82ym8EhBRZjbh3btsZhF+sjHqEMR159i4agru9x6KsepK/q0E2e5xlU5cv3m1woYfgHyOkWDNcSdMsS6bBh2Bpq6s89yJ9Q6qh/J8YHi306ce9Tqb/drKvN2XdE5noRSS32TAWuaQEVd7u+TrvXlOQsE3fHR1D5f1saUwQLPSdIv01NF6Ny7jZwjCwv1uNDgGZONJdlTJ6p0ccqnZvuE70aHOI09elpjEO6Cd+orI7XHHrFCwhFhAcbalc+ZfO5b/+vkyAHS6CYVFCDtYR9Hi5qgdk31v23w==";
    
    // Chama a fun��o para imprimir o XML de cancelamento
    int ret = ImprimeXMLCancelamentoSAT(xml, assQRCode, 0);

    // Verifica o retorno e imprime a mensagem apropriada
    switch (ret) {
        case 0:
            printf("XML de cancelamento SAT impresso com sucesso!\n");
            break;
        case 1:
            printf("Erro: XML inv�lido. Verifique o formato do XML.\n");
            break;
        case 2:
            printf("Erro: QR Code inv�lido ou assinatura inv�lida.\n");
            break;
        case 3:
            printf("Erro: Falha ao conectar ao dispositivo de impress�o.\n");
            break;
        case 4:
            printf("Erro: Falha na comunica��o com o SAT.\n");
            break;
        case 5:
            printf("Erro: Configura��o inv�lida para impress�o do cancelamento.\n");
            break;
        default:
            printf("Erro desconhecido. C�digo de erro: %d\n", ret);
    }
}

void abreGavetaElgin() {
    int ret = AbreGavetaElgin();
    if (ret == 0) {
        printf("Gaveta aberta com sucesso (Elgin)!\n");
    } else {
        printf("Erro ao abrir a gaveta (Elgin). Retorno: %d\n", ret);
    }
}

void abreGaveta() {
    int tempoON = 100, tempoOFF = 200, tempoSinal = 3;
    int ret = AbreGaveta(tempoON, tempoOFF, tempoSinal);
    if (ret == 0) {
        printf("Gaveta aberta com sucesso!\n");
    } else {
        printf("Erro ao abrir a gaveta. Retorno: %d\n", ret);
    }
}

void sinalSonoro() {
    int ret = SinalSonoro(4, 50, 5);
    if (ret == 0) {
        printf("Sinal sonoro emitido com sucesso!\n");
    } else {
        printf("Erro ao emitir sinal sonoro. Retorno: %d\n", ret);
    }
}

void avancaPapel() {
    int linhas;
    printf("Digite o n�mero de linhas para avan�ar o papel: ");
    scanf("%d", &linhas);
    int ret = AvancaPapel(linhas);
    if (ret == 0) {
        printf("Papel avan�ado com sucesso!\n");
    } else {
        printf("Erro ao avan�ar o papel. Retorno: %d\n", ret);
    }
}

void corte() {
    int avanco;
    printf("Digite o n�mero de unidades para avan�ar ap�s o corte: ");
    scanf("%d", &avanco);
    int ret = Corte(avanco);
    if (ret == 0) {
        printf("Papel cortado com sucesso!\n");
    } else {
        printf("Erro ao cortar o papel. Retorno: %d\n", ret);
    }
}

// Programa principal
int main() {
	
	int tipo = 1;        
    const char *dados = "123456789";  
    int altura = 100;    
    int largura = 2;     
    int HRI = 1;   
	
    if (!carregarFuncoes()) {
        return 1;
    }

    int opcao;
    do {
        exibirMenu();
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
             printf("Configurando conex�o...\n");
                int tipo, parametro;
                char modelo[10], conexao[10];
                configurarConexao(&tipo, modelo, conexao, &parametro);
                break;
        case 2:
             printf("Abrindo conex�o...\n");
                abrirConexao();
                break;
        case 3:
            printf("Imprimindo texto...\n");
                impressaoTexto();
                break;
        case 4:
		    impressaoQRCode();
            break;
        case 5:
        	printf("Imprimindo c�digo de barras...\n");
            imprimeCodigoBarras(tipo, dados, altura, largura, HRI);
            break;
            
        case 6:
            printf("Imprimindo XML SAT...\n");
                imprimeXMLSAT("XML-SAT-Exemplo", 0);
                break;
        case 7:
            printf("Imprimindo XML Cancelamento SAT...\n");
            imprimeXMLCancelamentoSAT("XML-Cancelamento", "Q5DLkpdRijIRGY6YSSNsTWK1...", 0);
            break;
        case 8:
            printf("Abrindo gaveta Elgin...\n");
            int ret = AbreGavetaElgin();
            if (ret == 0) {
                printf("Gaveta aberta com sucesso!\n");
            } else {
               printf("Erro ao abrir gaveta. Retorno: %d\n", ret);
            }
            break;
        case 9:
            printf("Abrindo gaveta padr�o...\n");
            AbreGaveta(27, 1, 100);
            break;
        case 10:
             printf("Emitindo sinal sonoro...\n");
             SinalSonoro(4, 50, 5);
             break;
        case 0:
            if (FechaConexaoImpressora) {
                int ret = FechaConexaoImpressora();
                if (ret == 0) {
                    printf("Conex�o encerrada com sucesso.\n");
                } else {
                    printf("Erro ao encerrar a conex�o. Retorno: %d\n", ret);
                }
            }
            printf("Encerrando o programa...\n");
            break;
        default:
            printf("Op��o inv�lida. Tente novamente.\n");
            break;
        }
    } while (opcao != 0);

    liberarBiblioteca();
    return 0;
}

