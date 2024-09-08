#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>//para usar o toupper nas escolhas
// #include "manip_exchange.h"

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

typedef struct {
    float cotacaoBTC;
    float cotacaoETH;
    float cotacaoXRP;
} Moedas;

pessoa pessoas[10];
Moedas moedas = {100.0, 50.0, 25.0};

void menu(int usuariologado);
void menuinicial(int usuariologado);
void consultarsaldo(int usuariologado);
void consultarextrato(int usuariologado);
void depositar(int usuariologado);
void sacar(int usuariologado);
void comprar(int usuariologado);
void vender(int usuariologado);
void atualizar();
void verificacao(int usuariologado);
int verificaCPF(char *cpf);

int main() {
    int usuariologado = -1;
    menuinicial(usuariologado);
    return 0;
}

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

void verificacao(int usuariologado){
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

void consultarsaldo(int usuariologado) {
    printf("══════════[Saldo]══════════\n");
    printf("Nome: %s\nCPF: %s\n\nReais: %.2f\nBitcoin: %.2f\nEthereum: %.2f\nRipple: %.2f\n", 
           pessoas[usuariologado].nome, pessoas[usuariologado].CPF, pessoas[usuariologado].reais, 
           pessoas[usuariologado].btc, pessoas[usuariologado].eth, pessoas[usuariologado].xrp);
}

void consultarextrato(int usuariologado) {
    printf("══════════[Extrato]══════════\n");
}

void depositar(int usuariologado) {
    system("cls");  //funciona (implementar no manip dps) e ver o tempo sertin de colocar
    float depositado = 0;
    verificacao(usuariologado);
    printf("══════════[Depositar]══════════\n");
    printf("Quantos reais deseja depositar?\n");
    scanf("%f", &depositado);
    pessoas[usuariologado].reais += depositado;
    consultarsaldo(usuariologado);
}

void sacar(int usuariologado) {
    system("cls");
    float sacado = 0;
    verificacao(usuariologado);
    printf("══════════[Sacar]══════════\n");
    printf("Quantos reais deseja sacar?\n");
    scanf("%f", &sacado);
    if(sacado <= pessoas[usuariologado].reais){
        pessoas[usuariologado].reais -= sacado;
        consultarsaldo(usuariologado);
    } else{
        printf("Impossível sacar este valor.\n");
    }
}

void comprar(int usuariologado) {       //funcionando :) (testa mais vezes com outros valores e tal)
    system("cls");
    char escolha;
    float comprar, taxa;
    verificacao(usuariologado);
    printf("══════════[Comprar Cripto]══════════\n");
    printf("════════════════════════════════════\n");
    printf("Cotação das Criptomoedas:\n\tBitcoin:\t%f\n\tEthereum:\t%f\n\tRipple:\t%f\n\nQue moeda deseja comprar? (B/E/R)", moedas.cotacaoBTC, moedas.cotacaoETH, moedas.cotacaoXRP);
    scanf(" %c", &escolha);
    escolha = toupper(escolha);
    //Fazer uma função para poupar linhas aqui, onde a mesma recebe as opc
    switch (escolha)
    {
    case 'B':
        system("cls");  
        printf("Você possui:\tR$%.2f\nCotação do Bitcoin:\t%f\n\nQuantos Bitcoins deseja comprar? ", pessoas[usuariologado].reais,moedas.cotacaoBTC);
        scanf("%f", &comprar);
        if(pessoas[usuariologado].reais - ((moedas.cotacaoBTC*comprar)+((moedas.cotacaoBTC*comprar)*0.02))>=0){    //verificar se vai dar valor negativo com a taxa aplicada
            pessoas[usuariologado].btc += comprar;                                                              //adiciona os bitcoins comprados
            pessoas[usuariologado].reais -= ((moedas.cotacaoBTC*comprar)+((moedas.cotacaoBTC*comprar)*0.02));   //faz a taxação na cotação e adiciona nos reais
            consultarsaldo(usuariologado);                                                                      //Quando fizeros o extrato, colocar pra adicionar isso no extrato 
        }
        else{
            printf("Você não possui reais necessarios para comprar essa quantia de Bitcoin");
        }
        break;
    case 'E':
        system("cls");
        printf("Você possui:\tR$%.2f\nCotação do Ethereum:\t%f\n\nQuantos Ethereum deseja comprar? ",pessoas[usuariologado].reais, moedas.cotacaoETH);
        scanf("%f", &comprar);
        if(pessoas[usuariologado].reais - ((moedas.cotacaoETH*comprar)+((moedas.cotacaoETH*comprar)*0.01))>=0){    
            pessoas[usuariologado].eth += comprar;                                                              
            pessoas[usuariologado].reais -= ((moedas.cotacaoETH*comprar)+((moedas.cotacaoETH*comprar)*0.01));   
            consultarsaldo(usuariologado);                                                                       
        }
        else{
            printf("Você não possui reais necessarios para comprar essa quantia de Ethereum");
        }
        break;
    case 'R':
        system("cls");
        printf("Você possui:\tR$%.2f\nCotação do Ripple:\t%f\n\nQuantos Ripple deseja comprar? ",pessoas[usuariologado].reais, moedas.cotacaoXRP);
        scanf("%f", &comprar);
        if(pessoas[usuariologado].reais - ((moedas.cotacaoXRP*comprar)+((moedas.cotacaoXRP*comprar)*0.01))>=0){    
            pessoas[usuariologado].xrp += comprar;                                                              
            pessoas[usuariologado].reais -= ((moedas.cotacaoXRP*comprar)+((moedas.cotacaoXRP*comprar)*0.01));   
            consultarsaldo(usuariologado);                                                                      
        }
        else{
            printf("Você não possui reais necessarios para comprar essa quantia de Ripple");
        }
        break;
    
    default:
        printf("Este comando não é valido, tente novamente.");
        break;
    }
}

void vender(int usuariologado) {
    system("cls");
    char escolha;
    float venda;
    verificacao(usuariologado);
    printf("══════════[Vender Cripto]══════════\n");
    printf("════════════════════════════════════\n");
    printf("Cotação das Criptomoedas:\n\tBitcoin:\t%f\n\tEthereum:\t%f\n\tRipple:\t%f\n\nQue moeda deseja vender? (B/E/R)", moedas.cotacaoBTC, moedas.cotacaoETH, moedas.cotacaoXRP);
    scanf(" %c", &escolha);
    escolha = toupper(escolha);
    switch (escolha)
    {
    case 'B':
        system("cls");
        printf("Você possui:\tR$%.2f\nCotação do Bitcoin:\t%f\n\nQuantos Bitcoins deseja vender? ", pessoas[usuariologado].reais,moedas.cotacaoBTC);
        scanf("%f", venda);
        if(pessoas[usuariologado].btc - venda >= 0){
            //printf("Até aqui foi"); DEBUGANDO...
            pessoas[usuariologado].btc -= venda;                                
            pessoas[usuariologado].reais += ((venda * moedas.cotacaoBTC)-(venda * moedas.cotacaoBTC * 0.03));  
            printf("Venda realizada com sucesso!\n");
            printf("Você ficou com :R$%.2f e com %.2f BTC", pessoas[usuariologado].reais, pessoas[usuariologado].btc);       
            consultarsaldo(usuariologado);
        }
        else{
            printf("Saldo de Bitcoins indisponível.");
        }
        break;
    case 'E':
        system("cls");
        printf("Você possui:\tR$%.2f\nCotação do Ethereum:\t%f\n\nQuantos Ethereuns deseja vender? ", pessoas[usuariologado].reais,moedas.cotacaoETH);
        scanf("%f", venda);
        if(pessoas[usuariologado].eth - venda >= 0){
            //printf("Até aqui foi"); DEBUGANDO...
            pessoas[usuariologado].eth -= venda;                                
            pessoas[usuariologado].reais += ((venda * moedas.cotacaoETH)-(venda * moedas.cotacaoETH * 0.02));  
            printf("Venda realizada com sucesso!\n");
            printf("Você ficou com :R$%.2f e com %.2f ETH", pessoas[usuariologado].reais, pessoas[usuariologado].eth);       
            consultarsaldo(usuariologado);
        }
        else{
            printf("Saldo de Bitcoins indisponível.");
        }
        break;
    case 'R':
        system("cls");
        printf("Você possui:\tR$%.2f\nCotação do Ripple:\t%f\n\nQuantos Ripples deseja vender? ", pessoas[usuariologado].reais,moedas.cotacaoXRP);
        scanf("%f", venda);
        if(pessoas[usuariologado].xrp - venda >= 0){
            //printf("Até aqui foi"); DEBUGANDO...
            pessoas[usuariologado].xrp -= venda;                                
            pessoas[usuariologado].reais += ((venda * moedas.cotacaoXRP)-(venda * moedas.cotacaoXRP * 0.01));  
            printf("Venda realizada com sucesso!\n");
            printf("Você ficou com :R$%.2f e com %.2f XRP", pessoas[usuariologado].reais, pessoas[usuariologado].xrp);       
            consultarsaldo(usuariologado);
        }
        else{
            printf("Saldo de Bitcoins indisponível.");
        }
        break;
    default:
        printf("Este comando não é valido, tente novamente");
        break;
    }
}

void atualizar() {
    printf("══════════[Atualizar]══════════\n");
}

void login(int usuariologado) {
    system("cls");
    char cpflogin[12];
    char senhalogin[7];

    printf("══════════[Login]══════════\n");
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
                menu(usuariologado);
                return;
            } else {
                printf("Senha incorreta\n");
                menuinicial(usuariologado);
                return;
            }
        }
    }
    printf("CPF não cadastrado!\n");
    menuinicial(usuariologado);
}

void cadastro(int usuariologado) {
    system("cls");
    char cpfcadastro[12];
    char senhacadastro[7];

    printf("══════════[Cadastro]══════════\n");
    printf("Digite seu CPF (Só pode possuir 11 dígitos): ");
    scanf("%11s", cpfcadastro);
    getchar(); 

    for (int i = 0; i < 10; i++) {
        if ((strcmp(cpfcadastro, pessoas[i].CPF) == 0)) {
            printf("CPF já cadastrado\n");
            menuinicial(usuariologado);
            return;
        }else if((strlen(cpfcadastro) != 11) || (verificaCPF(cpfcadastro) == 0)){
            printf("CPF inválido!\n");
            menuinicial(usuariologado);
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
                }
                pessoas[i].btc = 0.00;
                pessoas[i].eth = 0.00;
                pessoas[i].xrp = 0.00;
                pessoas[i].reais = 0.00;
                printf("Cadastro realizado com sucesso!\n");
                menuinicial(usuariologado);
                return;
            } else {
                printf("Senha inválida. Deve ter 6 dígitos.\n");
                menuinicial(usuariologado);
                return;
            }
        }
    }
}

void menuinicial(int usuariologado) {
    system("cls");
    char opc;
    while (1) {
        printf("╔══════════[Menu Inicial]══════════╗\n");
        printf("║ [1] Cadastro                     ║\n");
        printf("║ [2] Login                        ║\n");
        printf("║ [3] Sair                         ║\n");
        printf("╚══════════════════════════════════╝\n");
        printf("Digite a opção: ");
        scanf(" %c", &opc);
        getchar(); 

        switch (opc) {
        case '1':
            cadastro(usuariologado);
            return;
        case '2':
            login(usuariologado);
            return;
        case '3':
            exit(0);
            return;
        default:
            printf("Opção inválida, tente novamente\n");
            break;
        }
    }
}

void menu(int usuariologado) {
    system("cls");
    char opc;
    while (1) {
        printf(" ╠════════════════════════════════════════════════╣\n");
        printf("   Bem-vindo, %s\n", pessoas[usuariologado].nome);
        printf(" ╠════════════════[Menu de opções]════════════════╣\n");
        printf(" ║ Aperte [1] para consultar saldo                ║\n");
        printf(" ║ Aperte [2] para consultar extrato              ║\n");
        printf(" ║ Aperte [3] para depositar                      ║\n");
        printf(" ║ Aperte [4] para sacar                          ║\n");
        printf(" ║ Aperte [5] para comprar moedas                 ║\n");
        printf(" ║ Aperte [6] para vender moedas                  ║\n");
        printf(" ║ Aperte [7] para atualizar cotação              ║\n");
        printf(" ║ Aperte [8] para voltar ao menu principal       ║\n");
        printf(" ╚════════════════════════════════════════════════╝\n");
        printf("Digite a opção: ");
        scanf(" %c", &opc);
        getchar();
        switch (opc) {
        case '1':
            consultarsaldo(usuariologado);
            break;
        case '2':
            consultarextrato(usuariologado);
            break;
        case '3':
            depositar(usuariologado);
            break;
        case '4':
            sacar(usuariologado);
            break;
        case '5':
            comprar(usuariologado);
            break;
        case '6':
            vender(usuariologado);
            break;
        case '7':
            atualizar();
            break;
        case '8':
            menuinicial(usuariologado);
            break;
        default:
            printf("Opção inválida, tente novamente\n");
            break;
        }
    }
}
