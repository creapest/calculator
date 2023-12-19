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
    string path1 = "C:/Users/cmert/Desktop/ucheba/informatica/univer/plusa/calkulate/test_2.txt";
    string path2 = "C:/Users/cmert/Desktop/ucheba/informatica/univer/plusa/calkulate/test_2_ans.txt";
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
    for (int i = 0; i < prim.size(); i++)
    {
        string ans = calculator(prim[i]);
        string temp = anses[i];
        if (stold(ans) == stold(temp))
        {
            cout << i + 1 << " - ый пример решён верно" << endl;
        }
        else
        {
            cout << i + 1 << " - ый пример решён неверно" << endl;
            cout << fixed << stold(ans) << endl;
            cout << fixed << stold(temp) << endl;
        }
    }

    return 0;
}