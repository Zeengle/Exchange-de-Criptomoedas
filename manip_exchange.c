void consultarsaldo() {
    printf("EM construção\n");
    return;
}

void consultarextrato() {
    printf("EM construção\n");
    return;
}

void depositar() {
    printf("EM construção\n");
    return;
}

void sacar() {
    printf("EM construção\n");
    return;
}

void comprar() {
    printf("EM construção\n");
    return;
}

void vender() {
    printf("EM construção\n");
    return;
}

void atualizar() {
    printf("EM construção\n");
    return;
}

void login() {
    printf("Em construção");
    return;
}

void cadastro() {
    printf("Em construção");
}

void menuinicial() { // Função com as opções iniciais
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
            cadastro();
            return;
        case '2':
            login();
            return;
        case '3':
            return;
        default:
            printf("Opção inválida, tente novamente\n");
            break;
        }
    }
}

void menu() { // Função que mostra as funções pros usuários
    char opc;
    while (1) {
        printf(" ╠════════════════════════════════════════════════╣\n");
        printf("   Bem-vindo, x");
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
            consultarsaldo();
            return;
        case '2':
            consultarextrato();
            return;
        case '3':
            depositar();
            return;
        case '4':
            sacar();
            return;
        case '5':
            comprar();
            return;
        case '6':
            vender();
            return;
        case '7':
            atualizar();
            return;
        case '8':
            menuinicial();
            return;
        default:
            printf("Opção inválida, tente novamente\n");
            return;
        }
    }
}
