/** Aluno: Matheus Eiji Endo 15/0018169
 * Trabalho 1 - Segurança Computacional
 * Cifra de Vigenère e ataque por análise 
 * de freqências   
 *                                     **/

#include<bits/stdc++.h>
using namespace std;

    
//funcao para fazer a cifração de uma mensage, recebe duas strings, a mensagem e a senha
string cifra(string mensagem, string senha){
    int tamanho_mensagem = 0;
    int contador = 0; //contador para saber quantos caracteres diferentes de letras minusculas foram lidos
    string criptograma;
    //pega o tamanho da mensagem para iterar sobre ela
    tamanho_mensagem = mensagem.size();
    // 'soma' as duas letras e pega o resto da divisão por 26 para saber qual a letra correto do alfabeto, 
    // subtrai o valor de a(97) para ajustar a tabela ASCII para letras minusculas.
    for(int i = 0; i < tamanho_mensagem; i++){
        if('a'<= mensagem[i] && mensagem[i] <= 'z'){//checa se os caracteres são letras, se não forem não são cifrados
            char letra = ((mensagem[i] - 'a') + (senha[i-contador] -'a')) % 26;
            letra = letra + 'a' ;
            criptograma.push_back(letra);
        }
        else{
            contador++;
            criptograma.push_back(mensagem[i]);
        }
        
    }
    return criptograma;
}

string decifra(string criptograma, string senha){
    int tamanho_criptograma = 0;
    int contador = 0; //contador para saber quantos caracteres diferentes de letras minusculas foram lidos
    string mensagem;

    tamanho_criptograma= criptograma.size();
    // mesma coisa da cifração, porém faz o processo inverso, em vez de somar as letras ele diminui
    // soma 26 para encontrar o valor correto da letra caso o resultado da subtração seja negativo
    for(int i = 0; i < tamanho_criptograma; i++){
        if('a'<= criptograma[i] && criptograma[i] <= 'z'){
            char letra = (criptograma[i] - senha[i-contador] + 26) % 26;
            letra = letra + 'a';
            mensagem.push_back(letra);
        }
        else{
            contador++;
            mensagem.push_back(criptograma[i]);
        }
        
    }
    return mensagem;


}


//ajusta a senha para o tamanho da mensagem
string ajuste_senha(string mensagem,string senha){
    int tamanho_mensagem = 0;
    int tamanho_senha = 0;

    
    tamanho_mensagem = mensagem.size();
    tamanho_senha = senha.size();

    if(tamanho_senha >= tamanho_mensagem){//se a senha for maior ou igual não precisa ser ajustada
        return senha;
    }
    else{//calcula a diferença entre o tamanho da senha e da mensagem, e acrescenta os caracteres a senha na ordem
        int diferenca = tamanho_mensagem - tamanho_senha;
        for (int i = 0; i < diferenca; i++){
            senha.push_back(senha[i]);
        }
    }
    
    return senha;
}







