#include <iostream>
#include <vector>

using namespace std;

void sagHallo(int &alter);
void einlesen(int &zahl);
void add(int &zahl_0, int &zahl_1);

int main()
{
    int zahl[10];
    int ergeb = 0;
    char kk = 'c';

    vector<int> meineNoten;
    meineNoten.emplace_back(10);

    for (int i = 1; i < 3; i++)
    {
        cout << "Gib die " << i << " Zahl ein ";
        cin >> zahl[i];
        ergeb = ergeb + zahl[i];
    }
    cout << "Das Ergebniss von " << zahl[1] << " und " << zahl[2] << " ist " << ergeb << endl;

    sagHallo(ergeb);

    einlesen(zahl[5]);
    einlesen(zahl[6]);
    add(zahl[5], zahl[6]);

    return 0;
}
void sagHallo(int &alter) // pass by reference dadurch muss kein Poiter genommen werden
{
    alter = 666;
    cout << "Hallo alter " << alter << endl;
}
void einlesen(int &zahl)
{
    cin >> zahl;
}
void add(int &zahl_0, int &zahl_1)
{
    zahl_0 = zahl_0 + zahl_1;
    cout << "Das sit das ergebnis haha :D" << zahl_0;
}