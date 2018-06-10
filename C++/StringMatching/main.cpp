/* Analise empirica para string matching
 *
 *
*/
#include<limits.h>
#include<stdio.h>
#include<fstream>
#include<string>
#include<cstring>
#include<time.h>
#include<algorithm>
#include<trie.h>
#include<QStringList>

#define NO_OF_CHARS 256
using namespace std;

double mediaVet(double* vet, int tam)
{
    double soma = 0;

    for(int i=0; i<(tam/2); i++)
        soma += vet[i] + vet[tam-i-1];

    return soma/tam;
}

vector<string> to_vector(string str){
    vector<string> stringVector;
    QStringList list = QString::fromStdString(str).replace(" - "," ").split(QRegExp("\\s+"),QString::SkipEmptyParts);
    for(long i=0; i<list.size(); i++)
        stringVector.push_back(list[i].toStdString());
    return stringVector;
}

/******************************************* String Matching - Força Bruta *********************************************/
void bruteForceStringMatch(string vetT,ulong n,string vetP,uint m){
    for(ulong i=0;i<n-m;i++){
        uint j;
        for(j=0; j<m && vetP[j]==vetT[i+j]; j++);
        if(j==m){ //return (i);
            //cout<<"achou - "<<i<<"\n";
            return;
        }
    }//return static_cast<uint>(-1);
}
/******************************************** Fim Força Bruta *********************************************/

/******************************************* Suffix Array (Naive) - Dividir e Conquistar *****************************************/

/* LIXO
int divideConquer(string txt, string pat, uint start, uint end)
{
    int min = start+((end-start)/2);
    if (txt.substr(start,pat.length()) == pat)
        return static_cast<int>(start);
    if (end - start <= 2)
        return -1;
    else
    {
        int leftPos = divideConquer(txt,  pat, start , static_cast<uint>(min-1));
        //cout<<min<<'\n';
        if (leftPos != -1)
            return leftPos;
        int rightPos = divideConquer(txt ,pat, static_cast<uint>(min+1) , end);
        //cout<<min<<'\n';
        if (rightPos != -1)
            return rightPos;
    }
    return -1;
}

int divideConquer2(string txt, string pat, uint start, uint end){
    if(start>=end)
        return -1;
    int mid=(start+end)/2;
    int left=divideConquer2(txt,pat,start,static_cast<uint>(mid));
    if(left!=-1)
        return left;
    if(static_cast<uint>(mid+1)<txt.length() && txt.substr(static_cast<uint>(mid),pat.length())==pat)
        return mid;
    int right=divideConquer2(txt,pat,static_cast<uint>(mid+1),end);
    if(right!=-1)
        return right;
    return -1;
}
*/

// A comparison function used by sort() to compare two suffixes
int cmp(pair<ulong,char *> a, pair<ulong,char *> b)
{
    return strcmp(a.second, b.second) < 0? 1 : 0;
}

ulong *buildSuffixArray(char *txt, ulong n)
{
    pair<ulong,char *> *suffixes = new pair<ulong,char *>[n];
    for (ulong i = 0; i < n; i++)
    {
        suffixes[i].first = i;
        suffixes[i].second = (txt+i);
    }
    stable_sort(suffixes, suffixes+n, cmp);
    ulong *suffixArr = new ulong[n];
    for (ulong i = 0; i < n; i++)
        suffixArr[i] = suffixes[i].first;
    return  suffixArr;
}

void suffixArraySearch(char *pat, char *txt, ulong n, ulong *suffArr)
{
    long int m = strlen(pat);
    long int l = 0, r = n-1;
    long int mid;
    while (l <= r)
    {
        mid = l + ((r - l)/2);
        long int res = strncmp(pat,txt+suffArr[mid],m);
        if (res == 0)
            return;
        if (res < 0) r = mid - 1;
        else l = mid + 1;
    }
}
/*********************************************** Fim Dividir e Conquistar *********************************************/

/******************************************************** KMP - Compromisso Espaço-Tempo ********************************************************/
/// https://www.geeksforgeeks.org/searching-for-patterns-set-2-kmp-algorithm/
// Determinar lps[] (maior prefixo e sufixo adequado) para cada pat
uint *computeLPSArray(string pat, uint M)
{
    // tamanho do maior prefixo sufixo anterior
    uint len = 0;

    uint *lps = new uint[M];
    lps[0] = 0; // lps[0] é sempre 0

    uint i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            if (len != 0)
                len = lps[len-1];
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void KMPSearch(string txt,ulong N,string pat,uint M)
{
    //Preprocessa a palavra pat (calcula lps[])
    uint *lps = computeLPSArray(pat, M);
    //long int cont=0;

    ulong i = 0;  // indice de txt[]
    uint j = 0;  // indice de pat[]
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
        if (j == M)
        {
            return;
            //cout<<"Achou no indice "<<i-j<<'\n';
            //cont++;
            //j = lps[j-1];
        }
        // impossível mais combinações depois de j combinações
        else if (i < N && pat[j] != txt[i])
        {
            // não compara lps[0..lps[j-1]] caracteres, sempre irão combinar
            if (j != 0)
                j = lps[j-1];
            else
                i++;
        }
    }
    //return cont;
}
/******************************************************** Fim Compromisso Espaço-Tempo ********************************************************/

unsigned __int32 getRandom(unsigned __int32 const& min, unsigned __int32 const& max)
{
    srand(static_cast<uint>(time(NULL)));
    return ((static_cast<unsigned __int32>(static_cast<uint>(rand())) << 16) + (static_cast<unsigned __int32>(static_cast<uint>(rand()))) % (max - min) + min);
}

int main(void)
{
    clock_t Ticks[2];

    string base = "";

    ifstream arquivo;
    arquivo.open("BaseString.txt");
    if(!arquivo.is_open())
    {
        cout<<"Arquivo não foi aberto !\n\n";
        return 0;
    }

    string linha;
    while(getline(arquivo,linha))
        base += linha+" ";
    arquivo.close();


    ulong tamBase = 1260000; //Quantidade de dados processados - Tamanho da base
    int qtdDePontos = 126; //Quantidade de pontos para construção do gráfico - Quantidade de Intervalos

    double stringMatchMelhorCaso[qtdDePontos];
    double stringMatchCasoMedio[qtdDePontos];
    double stringMatchPiorCaso[qtdDePontos];
    double DividirMelhorCaso[qtdDePontos];
    double DividirCasoMedio[qtdDePontos];
    double DividirPiorCaso[qtdDePontos];
    double DecrementarMelhorCaso[qtdDePontos];
    double DecrementarCasoMedio[qtdDePontos];
    double DecrementarPiorCaso[qtdDePontos];
    double KMPMelhorCaso[qtdDePontos];
    double KMPCasoMedio[qtdDePontos];
    double KMPPiorCaso[qtdDePontos];
    string key = "string";
    uint m = key.length();
    double tmp;
    string texto;
    ofstream fileOut;

    //--------------------------------------------------------------------------------------------------------------------------------------------
    //Analise de Força Bruta (string matching)

    cout<<"\n\nAnalise string matching força bruta!!\n\n";

    //Melhor Caso
    for(ulong i=10000; i<=tamBase ; i+=10000) //Intervalo
    {cout<<"foi! - "<<i<<"\n\n";
        texto = key+base;
        texto.resize(i);
        double temp[50];
        for(int j=0; j<50; j++) //Quantidade de vezes executado a busca p/média
        {
            Ticks[0] = clock();
            bruteForceStringMatch(texto,i,key,m);
            Ticks[1] = clock();
            temp[j] = (Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC;
        }
        stringMatchMelhorCaso[(i/10000)-1] = mediaVet(temp,50); //Média do vetor de tempo
    }

    //Arquivo de gravação do vetor de tempo do Melhor Caso

    fileOut.open("TempoFBStringMatchingMelhorCaso.txt",std::ios::out|std::ios::app);
    if(!fileOut.is_open())
    {
        cout<<"Erro: Arquivo de gravação ! - StringMatching\n\n";
        return 0;
    }

    for(int i=0; i<qtdDePontos; i++)
        fileOut<<to_string(stringMatchMelhorCaso[i]) + "\n";
    fileOut.close();

    //Caso Médio
    for(ulong i=10000; i<=tamBase ; i+=10000) //Intervalo
    {cout<<"foi! - "<<i<<"\n\n";
        texto = base;
        texto.resize(i);
        texto.insert(getRandom(0,i)%i,key);
        double temp[50];
        for(int j=0; j<50; j++) //Quantidade de vezes executado a busca p/média
        {
            Ticks[0] = clock();
            bruteForceStringMatch(texto,i,key,m);
            Ticks[1] = clock();
            temp[j] = (Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC;
        }
        stringMatchCasoMedio[(i/10000)-1] = mediaVet(temp,50); //Média do vetor de tempo
    }

    //Arquivo de gravação do vetor de tempo do Caso Médio
    fileOut.open("TempoFBStringMatchingCasoMedio.txt",std::ios::out|std::ios::app);
    if(!fileOut.is_open())
    {
        cout<<"Erro: Arquivo de gravação ! - StringMatching\n\n";
        return 0;
    }

    for(int i=0; i<qtdDePontos; i++)
        fileOut<<to_string(stringMatchCasoMedio[i]) + "\n";
    fileOut.close();

    //Pior Caso
    for(ulong i=10000; i<=tamBase ; i+=10000) //Intervalo
    {cout<<"foi! - "<<i<<"\n\n";
        texto = base;
        texto.resize(i);
        double temp[50];
        for(int j=0; j<50; j++) //Quantidade de vezes executado a busca p/média
        {
            Ticks[0] = clock();
            bruteForceStringMatch(texto,i,key,m);
            Ticks[1] = clock();
            temp[j] = (Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC;

        }
        stringMatchPiorCaso[(i/10000)-1] = mediaVet(temp,50); //Média do vetor de tempo
    }

    //Arquivo de gravação do vetor de tempo do Pior Caso
    fileOut.open("TempoFBStringMatchingPiorCaso.txt",std::ios::out|std::ios::app);
    if(!fileOut.is_open())
    {
        cout<<"Erro: Arquivo de gravação ! - StringMatching\n\n";
        return 0;
    }

    for(int i=0; i<qtdDePontos; i++)
        fileOut<<to_string(stringMatchPiorCaso[i]) + "\n";
    fileOut.close();
    //--------------------------------------------------------------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------------------------------------------------------------
    //Analise Suffix Array (Dividir e Conquistar)

    cout<<"\n\nAnalise string matching suffix array!!\n\n";

    key = "string";
    //Melhor Caso
    for(ulong i=10000; i<=tamBase ; i+=10000) //Intervalo
    {cout<<"foi! - "<<i<<"\n\n";
        texto = base;
        texto.resize(i);
        char *textoc=to_char(texto);
        Ticks[0]=clock();
        ulong *suffixArr = buildSuffixArray(textoc,i);
        Ticks[1]=clock();
        tmp = (Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC;
        char *keyc = to_char(texto.substr(suffixArr[i/2],5));
        double temp[50];
        for(int j=0; j<50; j++) //Quantidade de vezes executado a busca p/média
        {
            Ticks[0] = clock();
            suffixArraySearch(keyc,textoc,i,suffixArr);
            Ticks[1] = clock();
            temp[j] = tmp+(Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC;
        }
        DividirMelhorCaso[(i/10000)-1] = mediaVet(temp,50); //Média do vetor de tempo
    }

    //Arquivo de gravação do vetor de tempo do Melhor Caso
    fileOut.open("TempoDividirMelhorCaso.txt",std::ios::out|std::ios::app);
    if(!fileOut.is_open())
    {
        cout<<"Erro: Arquivo de gravação ! - Dividir\n\n";
        return 0;
    }

    for(int i=0; i<qtdDePontos; i++)
        fileOut<<to_string(DividirMelhorCaso[i]) + "\n";
    fileOut.close();

    //Caso Médio
    for(ulong i=10000; i<=tamBase ; i+=10000) //Intervalo
    {cout<<"foi! - "<<i<<"\n\n";
        texto = base;
        texto.resize(i);
        texto.insert(getRandom(0,i)%i,key);
        char *textoc=to_char(texto);
        char *keyc = to_char(key);
        Ticks[0]=clock();
        ulong *suffixArr = buildSuffixArray(textoc,i);
        Ticks[1]=clock();
        tmp = (Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC;
        double temp[50];
        for(int j=0; j<50; j++) //Quantidade de vezes executado a busca p/média
        {
            Ticks[0] = clock();
            suffixArraySearch(keyc,textoc,i+strlen(keyc),suffixArr);
            Ticks[1] = clock();
            temp[j] = tmp+((Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC);
        }
        DividirCasoMedio[(i/10000)-1] = mediaVet(temp,50); //Média do vetor de tempo
    }

    //Arquivo de gravação do vetor de tempo do Caso Médio
    fileOut.open("TempoDividirCasoMedio.txt",std::ios::out|std::ios::app);
    if(!fileOut.is_open())
    {
        cout<<"Erro: Arquivo de gravação ! - Dividir\n\n";
        return 0;
    }

    for(int i=0; i<qtdDePontos; i++)
        fileOut<<to_string(DividirCasoMedio[i]) + "\n";
    fileOut.close();
*/
    //Pior Caso
    for(ulong i=10000; i<=tamBase ; i+=10000) //Intervalo
    {cout<<"foi! - "<<i<<"\n\n";
        texto = base;
        texto.resize(i);
        char *textoc=to_char(texto);
        char *keyc = to_char(key);
        Ticks[0]=clock();
        ulong *suffixArr = buildSuffixArray(textoc,i);
        Ticks[1]=clock();
        tmp = (Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC;
        double temp[50];
        for(int j=0; j<50; j++) //Quantidade de vezes executado a busca p/média
        {
            Ticks[0] = clock();
            suffixArraySearch(keyc,textoc,i,suffixArr);
            Ticks[1] = clock();
            temp[j] = tmp+((Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC);
        }
        DividirPiorCaso[(i/10000)-1] = mediaVet(temp,50); //Média do vetor de tempo
    }

    //Arquivo de gravação do vetor de tempo do Pior Caso
    fileOut.open("TempoDividirPiorCaso.txt",std::ios::out|std::ios::app);
    if(!fileOut.is_open())
    {
        cout<<"Erro: Arquivo de gravação ! - Dividir\n\n";
        return 0;
    }

    for(int i=0; i<qtdDePontos; i++)
        fileOut<<to_string(DividirPiorCaso[i]) + "\n";
    fileOut.close();
    //--------------------------------------------------------------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------------------------------------------------------------
    //Analise Trie (Decrementar e Conquistar)
    //Trie *trie = nullptr;
    cout<<"\n\nAnalise string matching trie!!\n\n";
    //Melhor Caso
    key = "string";
    for(ulong i=10000; i<=tamBase ; i+=10000) //Intervalo
    {cout<<"foi! - "<<i<<"\n\n";
        texto = key+base;
        texto.resize(i);
        trie_t *trie1 = new trie_t;
        Ticks[0]=clock();
        initializer(trie1,to_vector(texto));
        Ticks[1]=clock();
        tmp = (Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC;
        double temp[50];
        for(int j=0; j<50; j++) //Quantidade de vezes executado a busca p/média
        {
            Ticks[0] = clock();
            trieSearch(trie1,to_char(key));
            Ticks[1] = clock();
            temp[j] = tmp+(Ticks[1] - Ticks[0]) *1000.0 / CLOCKS_PER_SEC;
        }
        DecrementarMelhorCaso[(i/10000)-1] = mediaVet(temp,50); //Média do vetor de tempo
    }

    //Arquivo de gravação do vetor de tempo do Melhor Caso
    fileOut.open("TempoDecrementarMelhorCaso.txt",std::ios::out|std::ios::app);
    if(!fileOut.is_open())
    {
        cout<<"Erro: Arquivo de gravação ! - KMP\n\n";
        return 0;
    }

    for(int i=0; i<qtdDePontos; i++)
        fileOut<<to_string(DecrementarMelhorCaso[i]) + "\n";
    fileOut.close();

    //Caso Médio
    for(ulong i=10000; i<=tamBase ; i+=10000) //Intervalo
    {cout<<"foi! - "<<i<<"\n\n";
        texto = base;
        texto.resize(i);
        texto.insert(getRandom(0,i)%i,key);
        trie_t *trie2 = new trie_t;
        Ticks[0]=clock();
        initializer(trie2,to_vector(texto));
        Ticks[1]=clock();
        tmp = (Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC;
        double temp[50];
        for(int j=0; j<50; j++) //Quantidade de vezes executado a busca p/média
        {
            Ticks[0] = clock();
            trieSearch(trie2,to_char(key));
            Ticks[1] = clock();
            temp[j] = tmp+(Ticks[1] - Ticks[0]) *1000.0 / CLOCKS_PER_SEC;
        }
        DecrementarCasoMedio[(i/10000)-1] = mediaVet(temp,50); //Média do vetor de tempo
    }

    //Arquivo de gravação do vetor de tempo do Caso Médio
    fileOut.open("TempoDecrementarCasoMedio.txt",std::ios::out|std::ios::app);
    if(!fileOut.is_open())
    {
        cout<<"Erro: Arquivo de gravação ! - Decrementar\n\n";
        return 0;
    }

    for(int i=0; i<qtdDePontos; i++)
        fileOut<<to_string(DecrementarCasoMedio[i]) + "\n";
    fileOut.close();

    //Pior Caso

    key = "ztring";
    for(ulong i=10000; i<=tamBase ; i+=10000) //Intervalo
    {cout<<"foi! - "<<i<<"\n\n";
        texto = base;
        texto.resize(i);
        texto.append(key);
        trie_t *trie3 = new trie_t;
        Ticks[0]=clock();
        initializer(trie3,to_vector(texto));
        Ticks[1]=clock();
        tmp = (Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC;
        double temp[50];
        for(int j=0; j<50; j++) //Quantidade de vezes executado a busca p/média
        {
            Ticks[0] = clock();
            trieSearch(trie3,to_char(key));
            Ticks[1] = clock();
            temp[j] = tmp+(Ticks[1] - Ticks[0]) *1000.0 / CLOCKS_PER_SEC;
        }
        DecrementarPiorCaso[(i/10000)-1] = mediaVet(temp,50); //Média do vetor de tempo

    }

    //Arquivo de gravação do vetor de tempo do Pior Caso
    fileOut.open("TempoDecrementarPiorCaso.txt",std::ios::out|std::ios::app);
    if(!fileOut.is_open())
    {
        cout<<"Erro: Arquivo de gravação ! - Decrementar\n\n";
        return 0;
    }

    for(int i=0; i<qtdDePontos; i++)
        fileOut<<to_string(DecrementarPiorCaso[i]) + "\n";
    fileOut.close();
    //trie->~Trie();
    //free(trie);
    //--------------------------------------------------------------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------------------------------------------------------------
    //Analise de KMP (compromisso espaço-tempo)

    cout<<"\n\nAnalise string matching KMP!!\n\n";

    key = "string";
    m = key.length();
    //Melhor Caso
    for(ulong i=10000; i<=tamBase ; i+=10000) //Intervalo
    {cout<<"foi! - "<<i<<"\n\n";
        texto = key+base;
        texto.resize(i);
        double temp[50];
        for(int j=0; j<50; j++) //Quantidade de vezes executado a busca p/média
        {
            Ticks[0] = clock();
            KMPSearch(texto,i+m,key,m);
            Ticks[1] = clock();
            temp[j] = (Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC;
        }
        KMPMelhorCaso[(i/10000)-1] = mediaVet(temp,50); //Média do vetor de tempo
    }

    //Arquivo de gravação do vetor de tempo do Melhor Caso
    fileOut.open("TempoKMPMelhorCaso.txt",std::ios::out|std::ios::app);
    if(!fileOut.is_open())
    {
        cout<<"Erro: Arquivo de gravação ! - KMP\n\n";
        return 0;
    }

    for(int i=0; i<qtdDePontos; i++)
        fileOut<<to_string(KMPMelhorCaso[i]) + "\n";
    fileOut.close();

    //Caso Médio
    for(ulong i=10000; i<=tamBase ; i+=10000) //Intervalo
    {cout<<"foi! - "<<i<<"\n\n";
        texto = base;
        texto.resize(i);
        texto.insert(getRandom(0,i)%i,key);
        double temp[50];
        for(int j=0; j<50; j++) //Quantidade de vezes executado a busca p/média
        {
            Ticks[0] = clock();
            KMPSearch(texto,i+m,key,m);
            Ticks[1] = clock();
            temp[j] = (Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC;
        }
        KMPCasoMedio[(i/10000)-1] = mediaVet(temp,50); //Média do vetor de tempo
    }

    //Arquivo de gravação do vetor de tempo do Caso Médio
    fileOut.open("TempoKMPCasoMedio.txt",std::ios::out|std::ios::app);
    if(!fileOut.is_open())
    {
        cout<<"Erro: Arquivo de gravação ! - KMP\n\n";
        return 0;
    }

    for(int i=0; i<qtdDePontos; i++)
        fileOut<<to_string(KMPCasoMedio[i]) + "\n";
    fileOut.close();

    //Pior Caso
    key = "string";
    for(ulong i=10000; i<=tamBase ; i+=10000) //Intervalo
    {cout<<"foi! - "<<i<<"\n\n";
        texto = base;
        texto.resize(i);
        texto.append(key);
        double temp[50];
        for(int j=0; j<50; j++) //Quantidade de vezes executado a busca p/média
        {
            Ticks[0] = clock();
            KMPSearch(texto,i+m,key,m);
            Ticks[1] = clock();
            temp[j] = (Ticks[1] - Ticks[0]) *1000000.0 / CLOCKS_PER_SEC;

        }
        KMPPiorCaso[(i/10000)-1] = mediaVet(temp,50); //Média do vetor de tempo
    }

    //Arquivo de gravação do vetor de tempo do Pior Caso
    fileOut.open("TempoKMPPiorCaso.txt",std::ios::out|std::ios::app);
    if(!fileOut.is_open())
    {
        cout<<"Erro: Arquivo de gravação ! - KMP\n\n";
        return 0;
    }

    for(int i=0; i<qtdDePontos; i++)
        fileOut<<to_string(KMPPiorCaso[i]) + "\n";
    fileOut.close();
    //--------------------------------------------------------------------------------------------------------------------------------------------*/
    cout<<"Fim análise !";
    return 0;
}
