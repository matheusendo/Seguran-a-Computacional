/** Aluno: Matheus Eiji Endo 15/0018169
 * Trabalho 1 - Segurança Computacional
 * Cifra de Vigenère e análise de freqências   
 *                                     **/
#include <string>
using namespace std;
#ifndef ATAQUE_H  
#define ATAQUE_H 

string fix_criptograma(string criptograma_original);

int tamanho_chave(string mensagem);

string ataque_freq(string mensagem_original, int tamanho_senha, int lingua);

#endif