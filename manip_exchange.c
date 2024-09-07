#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "manip_exchange.h"

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


int verificaCPF(char *cpf){
    int numeros_cpf[11];
    int soma=0;
    int maxv1=10;
    int maxv2=11;
    int resto;
    int verificador1,verificador2;
    for (int i =0;i<11;i++){
        numeros_cpf[i]=cpf[i]-48;
    }
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
    float depositado = 0;
    verificacao(usuariologado);
    printf("══════════[Depositar]══════════\n");
    printf("Quantos reais deseja depositar?\n");
    scanf("%f", &depositado);
    pessoas[usuariologado].reais += depositado;
    consultarsaldo(usuariologado);
}

void sacar(int usuariologado) {
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

void comprar(int usuariologado) {
    verificacao(usuariologado);
    printf("══════════[Comprar Cripto]══════════\n");
}

void vender(int usuariologado) {
    verificacao(usuariologado);
    printf("══════════[Vender Cripto]══════════\n");
}

void atualizar() {
    printf("══════════[Atualizar]══════════\n");
}

void login(int usuariologado) {
    char cpflogin[12];
    char senhalogin[7];

    printf("Login\n");
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
    char cpfcadastro[12];
    char senhacadastro[7];

    printf("Cadastro\n");
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
