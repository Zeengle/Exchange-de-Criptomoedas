#ifndef manip_exchange
#define manip_exchange

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void menu(int usuariologado);
void menuinicial(int usuariologado);
void consultarsaldo(int usuariologado);
void consultarextrato(int usuariologado);
void depositar(int usuariologado);
void sacar(int usuariologado);
void comprar(int usuariologado);
void vender(int usuariologado);
void atualizar();
void verificação(int usuariologado);
int verificaCPF(char *cpf);

#endif