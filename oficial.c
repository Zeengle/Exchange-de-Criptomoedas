#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>//para usar o toupper nas escolhas
// #include "manip_exchange.h"
#include <math.h>

typedef struct {
    char CPF[12];
    char senha[7];  
    char nome[100];
    float reais;
    float btc;
    float eth;
    float xrp;
    char ext[100][100];
} pessoa;

/*---------------------------------------PROTÓTIPOS MENUS---------------------------------------*/

void menu(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado);
void menuinicial(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado);

/*---------------------------------PROTÓTIPOS FUNÇÕES PRINCIPAIS---------------------------------*/

void login(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado);
void cadastrar(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado);
void consultarsaldo(pessoa pessoas[], int usuariologado);
void consultarextrato(pessoa pessoas[], int usuariologado);
void depositar(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado);
void sacar(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado);
void comprar(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado);
void vender(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado);
void atualizar(pessoa pessoas[],float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado);

/*---------------------------------PROTÓTIPOS FUNÇÕES AUXILIARES---------------------------------*/

void verificacao(pessoa pessoas[], int usuariologado);
int verificaCPF(char *cpf);
void printarcpf(char *cpf);
void criaextrato(pessoa pessoas[], int usuariologado, char sinal, float valor, char moeda[6], float taxa);
void limpaterminal();
void espera();
void recibocompra(float compra, float taxa);
void recibovenda(float compra, float taxa);
void ler(FILE *file, pessoa pessoas[], int quantidade, float *cotacaoBTC, float *cotacaoETH, float *cotacaoXRP);
void escrever(pessoa pessoas[], int quantidade, float cotacaoBTC, float cotacaoETH, float cotacaoXRP);
int arquivoexiste(const char *filename);

/*---------------------------------------MAIN----------------------------------------*/

int main() {
    FILE *file;
    pessoa pessoas[10];
    float cotacaoBTC = 100;
    float cotacaoETH = 50;
    float cotacaoXRP = 25;
    int usuariologado = -1;

    int verificacao = arquivoexiste("dados.bin");

    if(verificacao == 0){ // O arquivo existe
        escrever(pessoas, 10, cotacaoBTC, cotacaoETH, cotacaoXRP);
    }else{
        ler(&file, pessoas, 10, &cotacaoBTC, &cotacaoETH, &cotacaoXRP);
    }
    menuinicial(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
    return 0;
}

/*---------------------------------------MENUS----------------------------------------*/
// Funções da "interface do programa"

// Mostra as opções iniciais do programa
void menuinicial(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado) {
    limpaterminal();
    char opc;
    while (1) {
        printf(" |---------------[Menu Inicial]---------------| \n");
        printf(" | [1] Cadastro                               | \n");
        printf(" | [2] Login                                  | \n");
        printf(" | [3] Sair                                   | \n");
        printf(" |--------------------------------------------| \n");
        printf(" Digite a opção: ");
        scanf(" %c", &opc);
        getchar(); 

        switch (opc) {
        case '1':
            cadastrar(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
            return;
        case '2':
            login(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
            return;
        case '3':
            escrever(pessoas, 10, cotacaoBTC, cotacaoETH, cotacaoXRP);
            exit(0);
            return;
        default:
            printf(" Opção inválida, tente novamente\n");
            break;
        }
    }
}

// Mostra as opções que usuário pode executar quando logado
void menu(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado){
    limpaterminal();
    char opc;
    while (1) {
        printf(" |------------------------------------------------| \n");
        printf("   Bem-vindo, %s\n", pessoas[usuariologado].nome);
        printf(" |----------------[Menu de opções]----------------|\n");
        printf(" | Aperte [1] para consultar saldo                |\n");
        printf(" | Aperte [2] para consultar extrato              |\n");
        printf(" | Aperte [3] para depositar                      |\n");
        printf(" | Aperte [4] para sacar                          |\n");
        printf(" | Aperte [5] para comprar moedas                 |\n");
        printf(" | Aperte [6] para vender moedas                  |\n");
        printf(" | Aperte [7] para atualizar cotação              |\n");
        printf(" | Aperte [8] para voltar ao menu principal       |\n");
        printf(" |------------------------------------------------|\n");
        printf(" Digite a opção: ");
        scanf(" %c", &opc);
        getchar();
        switch (opc) {
        case '1':
            consultarsaldo(pessoas, usuariologado);
            break;
        case '2':
            consultarextrato(pessoas, usuariologado);
            break;
        case '3':
            depositar(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
            break;
        case '4':
            sacar(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
            break;
        case '5':
            comprar(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
            break;
        case '6':
            vender(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
            break;
        case '7':
            atualizar(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
            break;
        case '8':
            menuinicial(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
            break;
        default:
            printf(" Opção inválida, tente novamente\n");
            break;
        }
    }
}

/*---------------------------------FUNÇÕES PRINCIPAIS---------------------------------*/

// Função responsável pelo cadastro de novos usuários
void cadastrar(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado) {
    limpaterminal();
    char cpfcadastro[12];
    char senhacadastro[7];
    int cadastrados;

    printf("|------------------------------[Cadastro]------------------------------|\n");
    if (cadastrados == 9){
        printf("Limite de cadastro atingido!\n");
        espera();
        menuinicial(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
        return;
    }
    else{
        printf("Digite seu CPF (Só pode possuir 11 dígitos): ");
        scanf("%11s", cpfcadastro);
        getchar(); 
        for (int i = 0; i < 10; i++) {
            if ((strcmp(cpfcadastro, pessoas[i].CPF) == 0)) {
                printf("CPF já cadastrado\n");
                espera();
                menuinicial(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
                return;
            }else if((strlen(cpfcadastro) != 11) || (verificaCPF(cpfcadastro) == 0)){
                printf("CPF inválido!\n");
                espera();
                menuinicial(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
                return;
            }else if (pessoas[i].CPF[0] == '\0') {
                printf("Digite sua senha (numérica com 6 dígitos): ");
                scanf("%6s", senhacadastro);
                getchar();
                if (strlen(senhacadastro) == 6) {
                    strcpy(pessoas[i].CPF, cpfcadastro);
                    strcpy(pessoas[i].senha, senhacadastro);
                    printf("Digite seu nome: ");
                    fgets(pessoas[i].nome, 100, stdin);
                    size_t len = strlen(pessoas[i].nome);
                    if (len > 0 && pessoas[i].nome[len - 1] == '\n') { 
                        pessoas[i].nome[len - 1] = '\0';
                    }else if(len < 3){
                        printf("Nome inválido, tente novamente!");
                        espera();
                        menuinicial(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
                    }
                    pessoas[i].btc = 0.00;
                    pessoas[i].eth = 0.00;
                    pessoas[i].xrp = 0.00;
                    pessoas[i].reais = 0.00;
                    cadastrados +=1;
                    printf("Cadastro realizado com sucesso!\n");
                    espera();
                    menuinicial(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
                    return;
                } else {
                    printf("Senha inválida. Deve ter 6 dígitos.\n");
                    espera();
                    menuinicial(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
                    return;
                }
            }
        }
    }
}

// Função responsável por permetir o acesso do usuário a sua conta
void login(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado) {
    limpaterminal();
    char cpflogin[12];
    char senhalogin[7];

    printf("|------------------------------[Login]------------------------------|\n");
    printf("Digite o CPF: ");
    scanf("%11s", cpflogin);
    getchar();

    for (int i = 0; i < 10; i++) {
        if (strcmp(cpflogin, pessoas[i].CPF) == 0) {
            printf("Digite sua senha: ");
            scanf("%6s", senhalogin);
            getchar();
            if (strcmp(senhalogin, pessoas[i].senha) == 0) {
                printf("Logado com sucesso\n");
                usuariologado = i;
                espera();
                menu(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
                return;
            } else {
                printf("Senha incorreta\n");
                espera();
                menuinicial(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
                return;
            }
        }
    }
    printf("CPF não cadastrado!\n");
    espera();
    menuinicial(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
}

// Função responsável por mostrar o saldo atualizado do usuário
void consultarsaldo(pessoa pessoas[], int usuariologado) {
    printf("|------------------------------------------------[Saldo]-----------------------------------------------|\n");
    printf("Nome: %s\n",pessoas[usuariologado].nome);
    printf("CPF: ");
    printarcpf(pessoas[usuariologado].CPF);
    printf("\nReais: %.2f\nBitcoin: %.2f\nEthereum: %.2f\nRipple: %.2f\n",pessoas[usuariologado].reais, 
           pessoas[usuariologado].btc, pessoas[usuariologado].eth, pessoas[usuariologado].xrp);
    espera();
    limpaterminal();
}

// Função que mostra as transações realizadas pelo usuário com data, hora, valor, moeda e seu saldo resumido
void consultarextrato(pessoa pessoas[], int usuariologado) {
    printf("|------------------------------[Extrato]------------------------------\n");
    printf("\tDATA/HORA\t\tSINAL\t\tVALOR\t\tMOEDA\t\tTAXA\t\tQUANT BTC\t\tQUANT ETH\t\tQUANT XRP\n");
    for (int i = 0; i < 100; i++) {
        if (pessoas[usuariologado].ext[i][0] != '\0') {
            printf("%s\n", pessoas[usuariologado].ext[i]);
        }
    }
    espera();
    limpaterminal();
}

// Função que permite o deposito de uma quantia pelo usuário
void depositar(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado){
    limpaterminal();  //funciona (implementar no manip dps) e ver o tempo sertin de colocar
    float depositado = 0;
    printf("|------------------------------------------------[Depositar]------------------------------------------------| \n");
    printf("Quantos reais deseja depositar?\n");
    scanf("%f", &depositado);
    if(depositado < 0){ // talvez eu tenha levado a sério demais
        printf("Vai toma no cu seu filho da puta para de ser burro aq é depósito seu animal bota um valor de gnt arrombado do krl toma nesse seu cu");
    }
    verificacao(pessoas, usuariologado);
    pessoas[usuariologado].reais += depositado;
    consultarsaldo(pessoas, usuariologado);
    criaextrato(pessoas, usuariologado, '+', depositado, "REAIS", 0);
}

// Função que realiza o saque, caso a qunatia seja válida, pelo usuário
void sacar(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado) {
    limpaterminal();
    float sacado = 0;
    printf("|------------------------------------------------[Sacar]------------------------------------------------| \n");
    printf("Você possui %.2f reais para ser sacados \nQuantos reais deseja sacar?\n", pessoas[usuariologado].reais);
    scanf("%f", &sacado);
    verificacao(pessoas, usuariologado);
    if(sacado <= pessoas[usuariologado].reais){
        pessoas[usuariologado].reais -= sacado;
        consultarsaldo(pessoas, usuariologado);
        criaextrato(pessoas, usuariologado, '-', sacado, "REAIS", 0);
    } else{
        printf("Impossível sacar este valor.\n");
        espera();
    }
}

// Função que permite a compra de criptomoedas pelo usuário
void comprar(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado) {  //funcionando :) (testa mais vezes com outros valores e tal)
    limpaterminal();
    char escolha;
    float comprar, taxa, compra;
    printf("|------------------------------------------------[Comprar Cripto]------------------------------------------------|\n");
    printf("Cotação das Criptomoedas:\n\tBitcoin:\t%.2f\n\tEthereum:\t%.2f\n\tRipple:\t\t%.2f\nQue moeda deseja comprar? (B/E/R) \n", cotacaoBTC, cotacaoETH, cotacaoXRP);
    scanf(" %c", &escolha);
    escolha = toupper(escolha);
    //Fazer uma função para poupar linhas aqui, onde a mesma recebe as opc
    switch (escolha)
    {
    case 'B':
        limpaterminal(); 
        printf("Você possui: R$%.2f\nCotação do Bitcoin: %.2f Taxa: 2.00%\nQuantos Bitcoins deseja comprar? \n", pessoas[usuariologado].reais,cotacaoBTC);
        scanf("%f", &comprar);
        compra = cotacaoBTC*comprar;
        taxa = ((cotacaoBTC*comprar)*0.02);
        verificacao(pessoas, usuariologado);
        if(roundf((pessoas[usuariologado].reais - (compra+taxa))* 100.00)/100.00>=0){    //verificar se vai dar valor negativo com a taxa aplicada
            pessoas[usuariologado].btc += comprar;                                                              //adiciona os bitcoins comprados
            pessoas[usuariologado].reais -= (compra+taxa);   //faz a taxação na cotação e adiciona nos reais
            criaextrato(pessoas, usuariologado, '+', compra, "BTC", 0.02);
            recibocompra(compra, taxa);
            consultarsaldo(pessoas, usuariologado);
        }
        else{      
            printf("Você não possui reais necessarios para comprar essa quantia de Bitcoin \n");
            recibocompra(compra, taxa);
            espera();
        }
        break;
    case 'E':
        limpaterminal();
        printf("Você possui: R$%.2f\nCotação do Ethereum: %.2f Taxa: 1.00%\nQuantos Ethereum deseja comprar? \n",pessoas[usuariologado].reais, cotacaoETH);
        scanf("%f", &comprar);
        compra = cotacaoETH*comprar;
        taxa = ((cotacaoETH*comprar)*0.01);
        verificacao(pessoas, usuariologado);
        if(roundf((pessoas[usuariologado].reais - (compra+taxa))* 100.00)/100.00>=0){    
            pessoas[usuariologado].eth += comprar;                                                              
            pessoas[usuariologado].reais -= (compra+taxa);   
            criaextrato(pessoas, usuariologado, '+', compra, "ETH", 0.01);
            recibocompra(compra, taxa);
            consultarsaldo(pessoas, usuariologado);                                                                
        }
        else{      
            printf("Você não possui reais necessarios para comprar essa quantia de Ethereum \n");
            recibocompra(compra, taxa);
            espera();
        }
        break;
    case 'R':
        limpaterminal();
        printf("Você possui:\tR$%.2f\nCotação do Ripple:\t%.2f Taxa: 1.00%\nQuantos Ripple deseja comprar? \n",pessoas[usuariologado].reais, cotacaoXRP);
        scanf("%f", &comprar);
        compra = cotacaoXRP*comprar;
        taxa = ((cotacaoXRP*comprar)*0.01);
        verificacao(pessoas, usuariologado);
        if(roundf((pessoas[usuariologado].reais - (compra+taxa))* 100.00)/100.00>=0){    
            pessoas[usuariologado].xrp += comprar;                                                              
            pessoas[usuariologado].reais -= (compra+taxa);   
            criaextrato(pessoas, usuariologado, '+', compra, "XRP", 0.01);
            recibocompra(compra, taxa);
            consultarsaldo(pessoas, usuariologado);                                                          
        }else{  
            printf("Você não possui reais necessarios para comprar essa quantia de Ripple \n");
            recibocompra(compra, taxa);
            espera();
        }
        break;
    default:      
        printf("Este comando não é valido, tente novamente. \n");
        espera();
        break;
    }
    limpaterminal();
}

// Função que permite a venda, caso válida, de criptomoedas do usuário
void vender(pessoa pessoas[], float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado){
    limpaterminal();
    char escolha;
    float venda, taxa, conversao;
    printf("|------------------------------------------------[Vender Cripto]------------------------------------------------| \n");
    printf("Cotação das Criptomoedas:\n\tBitcoin:\t%.2f\n\tEthereum:\t%.2f\n\tRipple:\t\t%.2f\n\nQue moeda deseja vender? (B/E/R)", cotacaoBTC, cotacaoETH, cotacaoXRP);
    scanf(" %c", &escolha);
    escolha = toupper(escolha);
    switch (escolha)
    {
    case 'B':
        limpaterminal();
        printf("Você possui:\t%.2f BTC\nCotação do Bitcoin:\t%.2f\n\nQuantos Bitcoins deseja vender? ", pessoas[usuariologado].btc, cotacaoBTC);
        scanf("%f", &venda);
        taxa = (venda * cotacaoBTC * 0.03);
        conversao = cotacaoBTC*venda;
        verificacao(pessoas, usuariologado);
        if(pessoas[usuariologado].btc - venda >= 0){
            //printf("Até aqui foi"); DEBUGANDO...
            pessoas[usuariologado].btc -= venda;                                
            pessoas[usuariologado].reais += (conversao-taxa);  
            printf("Venda realizada com sucesso!\n");
            recibovenda(conversao, taxa);       
            criaextrato(pessoas, usuariologado, '-', conversao, "BTC", 0.02);
            consultarsaldo(pessoas, usuariologado);
        }
        else{     
            printf("Saldo de Bitcoins indisponível. \n");
            recibovenda(conversao, taxa);  
            espera(); 
        }
        break;
    case 'E':
        limpaterminal();
        printf("Você possui:\t%.2f ETH\nCotação do Ethereum:\t%.2f\n\nQuantos Ethereuns deseja vender? ", pessoas[usuariologado].eth, cotacaoETH);
        scanf("%f", &venda);
        taxa = (venda * cotacaoETH * 0.02);
        conversao = cotacaoETH*venda;
        verificacao(pessoas, usuariologado);
        if(pessoas[usuariologado].eth - venda >= 0){
            //printf("Até aqui foi"); DEBUGANDO...
            pessoas[usuariologado].eth -= venda;                                
            pessoas[usuariologado].reais += ((venda * cotacaoETH)-(venda * cotacaoETH * 0.02));  
            printf("Venda realizada com sucesso!\n");
            printf("Você ficou com :R$%.2f e com %.2f ETH", pessoas[usuariologado].reais, pessoas[usuariologado].eth); 
            recibovenda(conversao, taxa);      
            criaextrato(pessoas, usuariologado, '-', conversao, "ETH", 0.02);
            consultarsaldo(pessoas, usuariologado); 
        }else{
            printf("Saldo de Etherium indisponível. \n");
            recibovenda(conversao, taxa);          
        }
        break;
    case 'R':
        limpaterminal();
        printf("Você possui:\t%.2f XRP\nCotação do Ripple:\t%.2f\n\nQuantos Ripples deseja vender? ", pessoas[usuariologado].xrp, cotacaoXRP);
        scanf("%f", &venda);
        taxa = (venda * cotacaoETH * 0.02);
        conversao = cotacaoETH*venda;
        verificacao(pessoas, usuariologado);
        if(pessoas[usuariologado].xrp - venda >= 0){
            //printf("Até aqui foi"); DEBUGANDO...
            pessoas[usuariologado].xrp -= venda;                                
            pessoas[usuariologado].reais += ((venda * cotacaoXRP)-(venda * cotacaoXRP * 0.01));  
            printf("Venda realizada com sucesso!\n");
            printf("Você ficou com :R$%.2f e com %.2f XRP", pessoas[usuariologado].reais, pessoas[usuariologado].xrp);

            criaextrato(pessoas, usuariologado, '-', conversao, "XRP", 0.02);
            consultarsaldo(pessoas, usuariologado);    
        }else{     
            printf("Saldo de Ripple indisponível.");
            recibovenda(conversao, taxa);      
            espera();
        }
        break;
    default:      
        printf("Este comando não é valido, tente novamente");
        espera();
        break;
    }
    limpaterminal();
}

// Função que faz a atualização das cotações de cada moeda variarem até +5% ou -5%
void atualizar(pessoa pessoas[],float cotacaoBTC, float cotacaoETH, float cotacaoXRP, int usuariologado) {
    limpaterminal();
    srand(time(NULL));

    float variacaoBTC = cotacaoBTC*(((rand()%10)-5.00)/100.00); // Cria o valor que vai ser aumentado ou não (+/-5%)
    variacaoBTC = roundf(variacaoBTC * 100.00)/100.00; // Arredondanda a variação pra 2 dígitos
    cotacaoBTC = roundf((cotacaoBTC + variacaoBTC)*100.00)/100.00; // Soma na nova cotação

    float variacaoETH = cotacaoETH*(((rand()%10)-5.00)/100.00); // Cria o valor que vai ser aumentado ou não (+/-5%)
    variacaoETH = roundf(variacaoETH * 100.00)/100.00; // Arredondanda a variação pra 2 dígitos
    cotacaoETH = roundf((cotacaoETH + variacaoETH)*100.00)/100.00; // Soma na nova cotação

    float variacaoXRP = cotacaoXRP*(((rand()%10)-5.00)/100.00); // Cria o valor que vai ser aumentado ou não (+/-5%)
    variacaoXRP = roundf(variacaoXRP * 100.00)/100.00; // Arredondanda a variação pra 2 dígitos
    cotacaoXRP = roundf((cotacaoXRP + variacaoXRP)*100.00)/100.00; // Soma na nova cotação

    printf("|------------------------------[Atualizando as cotações]------------------------------| \n");
    printf(" Nova cotação do Bitcoin: %.2f Variação: %.2f%\n", cotacaoBTC, variacaoBTC);
    printf(" Nova cotação do Etherium: %.2f Variação: %.2f%\n", cotacaoETH, variacaoETH);
    printf(" Nova cotação do Ripple: %.2f Variação: %.2f%\n", cotacaoXRP, variacaoXRP);
    printf(" Cotações atualizadas com sucesso.\n");
    printf("|-------------------------------------------------------------------------------------| \n");
    espera();
    menu(pessoas, cotacaoBTC, cotacaoETH, cotacaoXRP, usuariologado);
    return;
}

/*---------------------------------FUNÇÕES AUXILIARES---------------------------------*/

// Função que limpa o termina independente do sistema operacional
void limpaterminal(){
    system("cls || clear");
}

// Função que espera a ação do usuário para dar prosseguimento
void espera(){
    fflush(stdin);
    printf("Aperte ENTER para SAIR!");
    getchar();
}

// Função que verifica se o CPF é válido
int verificaCPF(char *cpf){
    int numeros_cpf[11];
    int soma=0;
    int maxv1=10;
    int maxv2=11;
    int resto;
    int veri;
    int verificador1,verificador2;
    for (int i =0;i<11;i++){
        numeros_cpf[i]=cpf[i]-48;
    }
    for (int i =0; i<11;i++){
        //implementação da verificação de cpfs com todos os digitos iguais
        if (numeros_cpf[i] == numeros_cpf[0]){
            veri +=1;
        }
    }
    if (veri == 11){
        printf("CPF Inválido");
    }
    else{

        for(int i = 0;i<9;i++){
            soma+=numeros_cpf[i]*maxv1;
            maxv1--;
        }

        resto = soma%11;

        if (resto == 1 || resto == 0){
            verificador1 = 0;
        } else{
            verificador1 = 11 - resto;
        }
        soma = 0;

        for (int i = 0;i<10;i++){
            soma+=numeros_cpf[i]*maxv2;
            maxv2--;
        }

        resto = soma%11;
        if (resto == 1 || resto == 0){
            verificador2 = 0;
        } else{
            verificador2 = 11 - resto;
        }

        if (verificador1 == numeros_cpf[9] && verificador2 == numeros_cpf[10]){
            return 1;
        } else{
            return 0;
        }
    }
}

// Função que faz a verificação da senha do usuário logado para permitir a execução de certas ações
void verificacao(pessoa pessoas[], int usuariologado){
    while (1){
        char senha[7];
        printf("Digite sua senha: ");
        scanf("%s", senha);
        if(strcmp(pessoas[usuariologado].senha, senha) == 0){
            return;
        } else{
            printf("Senha inválida. Tente novamente\n");
        }
    }
}

// Função que mostra o CPF de maneira formatada 
void printarcpf(char *cpf) {
  for (int i = 1; i < 12; i++) {
    if (i % 3 == 0 && i != 1 && i != 9) {
      printf("%c.", cpf[i - 1]);
    } else if (i == 9) {
      printf("%c-", cpf[i - 1]);
    } else {
      printf("%c", cpf[i - 1]);
    }
  }
  printf("\n");
}

// Responsável por adicionar uma transação no extrato do usuário
void criaextrato(pessoa pessoas[], int usuariologado, char sinal, float valor, char moeda[6], float taxa){
    char extrato[100];
    time_t t = time(NULL);  // Pega o horário atual
    struct tm tm = *localtime(&t); // Serve pra pegar cada informação das datas

    snprintf(extrato, sizeof(extrato), "[%02d/%02d/%d %02d:%02d] \t%c%.2f \t%s \t%.2f \t %.2f\t %.2f \t\t %.2f \t\t %.2f",
    tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, sinal, valor, moeda, taxa,pessoas[usuariologado].reais,pessoas[usuariologado].btc, pessoas[usuariologado].eth, pessoas[usuariologado].xrp);

    // Procura uma linha vazia no extrato
    for (int i = 0; i < 100; i++) {
        if (pessoas[usuariologado].ext[i][0] == '\0') {
            strcpy(pessoas[usuariologado].ext[i], extrato);
            break;
        }
    }
}

// Mostra o valor da total da compra de criptomoedas para o usuário
void recibocompra(float compra, float taxa){
    printf("|-----------------------[Recibo Compra]-----------------------| \n");
    printf("Total da compra: \n");
    printf("COMPRA + TAXA = TOTAL \n");
    printf("%.2f + %.2f = %.2f \n", compra, taxa, compra+taxa);
}

// Mostra o valor total da venda de criptomoedas para o usuário
void recibovenda(float conversao, float taxa){
    printf("|-----------------------[Recibo Venda]-----------------------| \n");
    printf("Total da venda: \n");
    printf("VENDA - TAXA = TOTAL \n");
    printf("%.2f - %.2f = %.2f \n", conversao, taxa, conversao-taxa);
}

void escrever(pessoa pessoas[], int quantidade, float cotacaoBTC, float cotacaoETH, float cotacaoXRP) {
    FILE *file = fopen("dados.bin", "wb");

    fwrite(pessoas, sizeof(pessoa), 10, file);
    fwrite(&cotacaoBTC, sizeof(float), 1, file);
    fwrite(&cotacaoETH, sizeof(float), 1, file);
    fwrite(&cotacaoXRP, sizeof(float), 1, file);

    fclose(file);
}

void ler(FILE *file, pessoa pessoas[], int quantidade, float *cotacaoBTC, float *cotacaoETH, float *cotacaoXRP) {
    file = fopen("dados.bin", "rb");

    fread(pessoas, sizeof(pessoa), 10, file);
    fread(cotacaoBTC, sizeof(float), 1, file);
    fread(cotacaoETH, sizeof(float), 1, file);
    fread(cotacaoXRP, sizeof(float), 1, file);

    fclose(file);
}

int arquivoexiste(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file); 
        return 1;  
    }
    return 0;
}