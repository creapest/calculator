#include <iostream>
#include "culculator_test.cpp"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main()
{

    vector<string> prim;
    vector<string> anses;
    string s;
    string path1 = "C:/Users/cmert/Desktop/ucheba/informatica/univer/plusa/calkulate/primerbl.txt";
    string path2 = "C:/Users/cmert/Desktop/ucheba/informatica/univer/plusa/calkulate/anses.txt";
    ifstream file1(path1);
    ifstream file2(path2);

    while (getline(file1, s))
    {
        prim.push_back(s);
    }
    while (getline(file2, s))
    {
        anses.push_back(s);
    }
    // for (int i = 0; i < prim.size(); i++)
    // {
    //     cout << prim[i] << endl;
    //     cout << anses[i] << endl;
    // }
    for (int i = 0; i < prim.size(); i++)
    {
        string ans = calculator(prim[i]);
        if (ans == anses[i])
        {
            cout << i + 1 << " - ый пример решён верно" << endl;
        }
    }

    return 0;
}