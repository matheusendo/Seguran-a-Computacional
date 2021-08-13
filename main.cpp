/** Aluno: Matheus Eiji Endo 15/0018169
 * Trabalho 1 - Segurança Computacional
 * Cifra de Vigenère e ataque por análise 
 * de freqências   
 *                                     **/

#include<bits/stdc++.h>
#include "vigenere.h"
#include "ataque.h"
using namespace std;

int main(){
    int opcao = 0;
    int flag = 0;
    int lingua = 0;
    string mensagem,senha,criptograma;

    while (flag == 0){//fica no menu ate a opção de sair
        cout<<endl <<endl <<endl << "1 - Cifra"<<endl;
        cout<< "2 - Decifra"<<endl;
        cout<< "3 - Ataque"<<endl;
        cout<< "4 - Sair"<<endl;

        cin>> opcao;
        
        switch (opcao){
            
            case 1://caso de cifrar, pega a mensagem, a senha, ajusta a senha para a mensagem, usa a funcao de cifra e imprime o criptograma
                cout<<endl<<endl<< " Digite a mensagem:"<<endl;
                cin.ignore();
                getline(cin, mensagem, '\n');
                cout<< " Digite a senha:"<<endl;
                cin>> senha;
                senha = ajuste_senha(mensagem,senha);
                criptograma = cifra(mensagem,senha);
                cout<< " Criptograma: "<<criptograma <<endl;
                cout <<endl<< "Pressione Enter to Continue";
                cin.ignore();
                cin.ignore();
                break;
            case 2://caso de decifrar, similar a anterior 
                cout<<endl<<endl<< " Digite o criptograma:"<<endl;
                cin.ignore();
                getline(cin, criptograma, '\n');
                cout<< " Digite a senha:"<<endl;
                cin>> senha;
                senha = ajuste_senha(criptograma,senha);
                mensagem = decifra(criptograma,senha);
                cout<< "Mensagem: "<< mensagem << endl;
                cout <<endl<< "Pressione Enter to Continue";
                cin.ignore();
                cin.ignore();
                break;
            case 3://caso seja a opcao de ataque, pega o criptograma, a opcao da lingua, usa as funcoes para achar o tamanho da senha, fazer o ataque utilizando frequencia
                //ajusta a senha obtida pelo ataque e decifra o criptograma com a senha
                cout<<endl<<endl<< " Digite o criptograma:"<<endl;
                cin.ignore();
                getline(cin, criptograma, '\n');//usa getline para pegar espaços em branco

                cout<<endl<<endl<<" De qual lingua deve ser utilizada a frequencia para o ataque?"<<endl;
                cout<<"1 - Inglesa"<<endl<<"2 - Portuguesa"<<endl;
                cin>> lingua;
                
                senha = ataque_freq(criptograma,tamanho_chave(criptograma),lingua);
                senha = ajuste_senha(criptograma,senha);
                mensagem = decifra(criptograma,senha);
                cout<<endl<< "Mensagem: "<< mensagem << endl;
                cout <<endl<< "Pressione Enter to Continue";
                cin.ignore();
                cin.ignore();
                break;
            case 4://para sair
                flag=1;
                break;
            default:
                flag=1;
                break;
        }
    }

    return 0;
}
