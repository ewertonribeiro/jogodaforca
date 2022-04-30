
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <map>

using namespace std;

string palavra_secreta;
map<char, bool> chutes;
vector<char> chutes_errados;
vector<string> palavras;

string sortea_palavra(int total)
{
    srand(time(NULL));
    int indice_palavra = rand() % total;

    return palavras[indice_palavra];
}

void le_arquivo()
{
    ifstream arquivo;
    arquivo.open("palavras.txt");

    int total_palavras{ 0 };
    arquivo >> total_palavras;

    for (int i{ 0 }; i < total_palavras; i++)
    {
        string palavra;
        arquivo >> palavra;
        palavras.push_back(palavra);
    }

    arquivo.close();

    palavra_secreta = sortea_palavra(total_palavras);
}

void escreve_palavra()
{
    cout << "Digite a nova palavra : ";
    string palavra;
    cin >> palavra;

    ofstream arquivo;
    arquivo.open("palavras.txt");

    palavras.push_back(palavra);
    arquivo << palavras.size() << endl;

    for (string item : palavras)
    {
        arquivo << item << endl;
    }

    cout << "Nova palavra cadastrada com sucesso!" << endl;
    cout << "Jogue novamente!" << endl;

    arquivo.close();

}

void cabecalho()
{
    cout << "***************************************" << endl;
    cout << "*****  Bem Vindo Ao jodo da forca  ****" << endl;
    cout << "***************************************" << endl;

}

bool letra_esta_na_palavra(char chute)
{
    for (char letra : palavra_secreta)
    {
        if (chute == letra)
        {
            return true;
        }
    }
    return false;
}

void exibir_palavra_secreta()
{
    for (char letra : palavra_secreta)
    {
        if (chutes[letra])
        {
            cout << letra;
        }
        else
        {
            cout << "_ ";
        }
    }

    cout << endl;
}

void mostra_chutes_errados()
{
    cout << "\nSeus chutes errados : ";
    for(char chute : chutes_errados)
    {
        cout << chute;
    }
    cout << endl;
}

void processar_chute()
{
    cout << "\nQual e o seu chute?" << endl;

    char chute;
    cin >> chute;
   
    cout << "\nVoce chutou a letra : " << chute << endl;

    if (letra_esta_na_palavra(chute))
    {
        cout << "Acertou o seu chute!" << endl;
        chutes[chute] = true;
    }
    else
    {
        chutes[chute] = false;
        chutes_errados.push_back(chute);
        cout << "errou o chute!" << endl;
    }
}

bool enforcou()
{
    if (chutes_errados.size() >= 6)
    {
        return true;
    }
    return false;
}

bool acertou()
{
    for (char letra : palavra_secreta)
    {
        if (!chutes[letra])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    cabecalho();

    le_arquivo();

    while (!enforcou() && !acertou())
    {
    exibir_palavra_secreta();

    mostra_chutes_errados();

    processar_chute();
    }

    if (acertou())
    {
        cout << "Parabens voce ganhou o jogo!" << endl << endl;
        cout << "Quer cadastrar uma nova palavra no banco? (s/n)";
        char escolha;
        cin >> escolha;

        if (escolha == 's')
        {
            escreve_palavra();
        }
        else
        {
            cout << "Obrigado por jogar!" << endl;
        }
    }
    else
    {
        cout << "Sinto muito , voce enforcou!" << endl;
        cout << "A palavra secreta era " << palavra_secreta << endl;
    }

}

