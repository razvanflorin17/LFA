/*
    Potcoveanu Florin-Razvan
    Grupa 132

    Automat finit nedeterminist fara lambda tranzitii (NFA)

*/

#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

ifstream f("graf.in");
ofstream g("graf.out");

int n, m, nod_start, nod_final, numar_noduri_final, index_1, index_2, numar_teste;

stack<int> stari;

int NFA(int start, int stop, int n, int m, char graf[][101], string cuv, int index)
{
    stari.push(start);
    int ok_NFA = 0;
    for(int i = start; i < n; i++)
    {
        if(graf[start][i] == cuv[index])
        {
            NFA(i, stop, n, m, graf, cuv, index+1);
            ok_NFA = 1;
        }

    }
    if(ok_NFA == 1)
    {
        if(stari.size() == cuv.length())
            return 1;
        else
            stari.pop();
    }
    else
        stari.pop();
    if(stari.empty())
        return 0;
}

void afisare()
{
    while(!stari.empty())
    {
        int x = stari.top();
        stari.pop();
        afisare();
        g<<x<<" ";
    }
}

int main()
{
    f>>n>>m;

    char matrice[101][101];

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            matrice[i][j] = '#';

    for(int i = 0; i < m; i++)
        f>>index_1>>index_2>>matrice[index_1][index_2];

    f>>nod_start;

    f>>numar_noduri_final;

    int noduri_final[numar_noduri_final + 1];

    for(int i = 0; i < numar_noduri_final; i++)
        f>>noduri_final[i];

    string cuvant;

    f>>numar_teste;

    for(int i = 0; i < numar_teste; i++)
    {
        f>>cuvant;
        g<<cuvant<<endl;
        int ok = 0;
        for(int j = 0; j < numar_noduri_final; j++)
        {
            nod_final = noduri_final[j];
            if(NFA(nod_start, nod_final, n, m, matrice, cuvant, 0))
                ok = 1;
        }
        if(ok)
        {
            g<<"DA : ";
            afisare();
            g<<nod_final<<endl;
        }
        else g<<"NU"<<endl;
    }

    return 0;
}
