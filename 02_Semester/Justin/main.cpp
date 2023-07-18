#include <iostream>

// g++

using namespace std;

int main(int argc, char *argv[])
{
    int meineZAHL = 42;
    bool s = true;
    string name;
    std::string test = "dsafsdadada";
    printf("%d\n", meineZAHL);

    std::cout << "Hallo"; //ausgabe Shell
    cout << meineZAHL;    //printf
    cin >> meineZAHL;     //scanf
    cout << "meine neue Zahl" << meineZAHL << "haha\n"
         << "haha" << endl; //endl == \n
    cin >> name;
    cout << name;

    return 0;
}