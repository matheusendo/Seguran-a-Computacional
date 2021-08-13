/** Aluno: Matheus Eiji Endo 15/0018169
 * Trabalho 1 - Segurança Computacional
 * Cifra de Vigenère e análise de freqências   
 *                                     **/

#include <string>
using namespace std;
#ifndef VIGENERE_H  
#define VIGENERE_H 

string cifra(string mensagem, string senha);

string decifra(string criptograma, string senha);

string ajuste_senha(string mensagem, string senha);



#endif