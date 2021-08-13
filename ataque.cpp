/** Aluno: Matheus Eiji Endo 15/0018169
 * Trabalho 1 - Segurança Computacional
 * Cifra de Vigenère e análise de freqências   
 *                                     **/

#include<bits/stdc++.h>
using namespace std;


string fix_criptograma(string criptograma_original){//função para remover todos caracteres que não sejam letras minusculas de um cirptograma
    int tamanho_criptograma = 0;
    string criptograma;

    tamanho_criptograma = criptograma_original.size();
    for(int i = 0; i < tamanho_criptograma ; i++){//remove caracteres que não são letras minusculas do criptograma
        if('a'<= criptograma_original[i] && criptograma_original[i] <= 'z'){
            criptograma.push_back(criptograma_original[i]);
        }
    }
    return criptograma;
}
//estima o tamanho da chave/senha do criptograma    
int tamanho_chave(string criptograma){
    int tamanho_criptograma = 0;
    int tamanho = 0;
    int flag = 0;
    vector<char> trigrama(3,0);//utiliza trigramas de caracteres para encontrar repetições
    vector<int> vetor_dist;//armazena as distâncias de cada repetição
    vector<int> freq_rep (19,0);//armazena as frequencias em que cada possível tamanho da chave seja fator de alguma distancia
    
    criptograma=fix_criptograma(criptograma);
    tamanho_criptograma = criptograma.size();
    
    for(int i = 0; i < tamanho_criptograma - 3; i++){//itera sobre o criptograma até os últimos 3 elementos, pois são necessários 4 elementos para haver uma repetição
        trigrama[0] = criptograma[i];
        trigrama[1] = criptograma[i+1];
        trigrama[2] = criptograma[i+2];
        for (int j = i + 1; j < tamanho_criptograma - 2 ; j++){//itera sob o criptograma comparando a trigrama com valores posteriores, se os 3 forem iguais guarda a distancia
            if (trigrama[0] == criptograma[j] && trigrama[1] == criptograma[j+1] && trigrama[2] == criptograma[j+2]){
                if(find(vetor_dist.begin(), vetor_dist.end(), j-i)==vetor_dist.end()){//checa se a distancia ja foi computada, se for não armazena
                    vetor_dist.push_back(j-i);
                }
                break;
            }
        }
    }
    
    for(int i = 0; i < vetor_dist.size(); i++){//itera sob o vetor de distancias e checa se os possiveis tamanhos de chave são fatores da distancia
        for (int j = 2; j <= 19; j++){//começa em 2 pois 0 e 1 não são considerados como possiveis tamanhos de chave
            if (vetor_dist[i] % j == 0){//se for fator( resto 0 ) adiciona 1 ao vetor de frequencias, 
                freq_rep[j-2] = freq_rep[j-2] + 1;
            }
            
        }
    }
    cout<<endl<<endl<<"1-Fazer a escolha do tamanho da senha com base na frequencia dos tamanhos/periodos possiveis"<<endl;
    cout<<"2-Deixar o programa fazer essa escolha"<<endl;
    cin>>flag;
    
    if(flag == 2){//se o tamanho for estimado de forma automatica(flag = 2) pega o tamanho com maior frequencia
        int max = 0;
        for(int i = 0; i < freq_rep.size(); i++){
            if (freq_rep[i] >= max){
                max = freq_rep[i];
                if(i+2 <= tamanho_criptograma){//i é somado 2 pois esse e o primeiro valor considerado para o tamanho, limita o tamanho da chave a ser menor ou igual ao tamanho da criptograma
                    tamanho = i+2;
                }
            }
        }
        cout<<"Tamanho da chave : "<<tamanho<<endl;
    }
    else {//caso a escolha do tamanho seja feita pelo usuario
        for(int i = 0; i < freq_rep.size(); i++){//printa o numero de repeticoes de cada fator
            cout<< "Numero de repeticoes do fator "<<i+2<< " = "<<freq_rep[i]<<endl;
        }
        cout<<endl<<" Digite o tamanho de senha:"<<endl;//e pega o input do tamanho do usuario
        cin>> tamanho;

    }
    
    
    return tamanho;
}

string ataque_freq(string criptograma, int tamanho_senha, int lingua){//dado o tamanho da senha utiliza a frequencia de letras das linguas ingles e portugues para achar a senha
    int tamanho_criptograma = 0;
    int k = 0;
    string senha;

    map <char,float> freq_letras_en {{'a',8.167},{'b',1.492},{'c',2.782},{'d',4.253},{'e',12.702},{'f',2.228}
    ,{'g',2.015},{'h',6.094},{'i',6.966}, {'j',0.153},{'k',0.772}, {'l',4.025},{'m',2.406},{'n',6.749},{'o',7.507}
    ,{'p',1.929},{'q',0.095},{'r',5.987},{'s',6.327},{'t',9.056},{'u',2.758},{'v',0.978},{'w',2.36},{'x',0.15}
    ,{'y',1.974},{'z',0.074}};//map com as frequencias de cada letra da linga inglesa

    map <char,float> freq_letras_pt {{'a',14.63},{'b',1.04},{'c',3.88},{'d',4.99},{'e',12.57},{'f',1.02}
    ,{'g',1.30},{'h',1.28},{'i',6.18}, {'j',0.4},{'k',0.02}, {'l',2.78},{'m',4.74},{'n',5.05},{'o',10.73}
    ,{'p',2.52},{'q',1.20},{'r',6.53},{'s',7.81},{'t',4.34},{'u',4.63},{'v',1.67},{'w',0.01},{'x',0.21}
    ,{'y',0.01},{'z',0.47}};//map com as frequencias de cada letra da linga portuguesa

    map <char, float> freq_letras_criptograma {{'a',0},{'b',0},{'c',0},{'d',0},{'e',0},{'f',0}
    ,{'g',0},{'h',0},{'i',0}, {'j',0},{'k',0}, {'l',0},{'m',0},{'n',0},{'o',0}
    ,{'p',0},{'q',0},{'r',0},{'s',0},{'t',0},{'u',0},{'v',0},{'w',0},{'x',0}
    ,{'y',0},{'z',0}};//map com as frequencias de cada letra de grupos do criptograma

    

    criptograma=fix_criptograma(criptograma);//retira caacteres que nao sejam letras minusculsa do criptograma
    tamanho_criptograma = criptograma.size();//o tamanho do criptograma ajustado
    
    // for (const auto& x : freq_letras_criptograma ) {//
    //     cout << x.first << " -- "<< x.second<<endl; 
        
    // }

    
    k = tamanho_criptograma / tamanho_senha; //numero de palavras em cada grupo, desconsidera resto

    float t = 100/float(k); // valor em porcentagem correspondente a frequencia de uma letra em um grupo
    
    for(int i = 0; i < tamanho_senha; i++){//for que itera por cada 'slot' da senha
        for(int j = 97; j < 123; j++){//reseta o map de freq de letras de cada grupo
            freq_letras_criptograma.at(j)=0;
        }
        
        for (int j = 0; j < k ;j++){//checa a j-esima letra do criptograma, correspondente aos grupos de cada 'slot' da senha, ex: senha tamanho 5, checa a 1ª letra, a 6ª, 11ª e etc.
            freq_letras_criptograma.at(criptograma[(j*tamanho_senha)+i]) = freq_letras_criptograma.at(criptograma[(j*tamanho_senha)+i]) + t;//atualiza o valor do map corresponde a letra
            
        }

        
        senha.push_back(0);//adiciona um valor a senha, que sera atualizado conforme as diferenças de frequencias sao calculadas
        float min = 999999;//valor inicial de min par semprr ser atualizado na 1ª vez
        for(int l = 0; l < 26 ; l++){//for para calcular a diferença entre a frequencia de letras de cada grupo com a frequencia da lingua desejada, calculando todas as letras como possiveis senhas do grupo 
            float dif_total = 0;
            int index = 0;//index para iterar sob o map de forma correta(se chegar ao fim deve voltar ao começo)
            for(int m ='a'; m <= 'z'; m++){//começa do a até o z, calculando a diferença entre as frequencias, index faz as 'rotações' para comparar as diferentes frequencias
                
                if(m+l > 'z'){//ajuste do index
                    index = m + l - 26;
                }
                else{
                    index = m + l;
                }
                if(lingua==1){//se for lingua inglesa
                    if(freq_letras_en.at(m)>freq_letras_criptograma.at(index)){
                        dif_total += (freq_letras_en.at(m) - freq_letras_criptograma.at(index));
                    }
                    else{
                        dif_total += (freq_letras_criptograma.at(index) - freq_letras_en.at(m));
                    }
                }
                else{//se for lingua portuguesa
                    if(freq_letras_pt.at(m)>freq_letras_criptograma.at(index)){
                        dif_total += (freq_letras_pt.at(m) - freq_letras_criptograma.at(index));
                    }
                    else{
                        dif_total += (freq_letras_criptograma.at(index) - freq_letras_pt.at(m));
                    }
                }
            }
            if(dif_total < min){//atualiza o valor do min se a dif calcula for menor que o min atual, se for atualiza a senha
                min = dif_total;
                senha[i]='a'+l;//soma o valor de a para senha ficar com a letra correta
            }
        }
        
        // for (const auto& x : freq_letras_criptograma ) {
        //     cout << x.first << " -- "<< x.second<<endl; 
    }
    cout<<endl<<"Senha = "<<senha<<endl;
    return senha;
}