/*этот файл для автоматического теста*/

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <sstream>

using namespace std;

string del_whitespace(string to_del);
string main_calculate(string to_calc);
vector<string> dif_calculation(string _to_calc);
int simp_calculation(int num_1, int num_2, int num_1_int, int num_2_int, string oper);
string full_calculation(string _to_calc);
bool is_num(string str);
string join(vector<string> vec);
bool find(vector<string> vec, string item);
string convert(int myLongDouble);
int count(string str, int item);
string convert_div_mult(string str);

string calculator(string str);

const vector<string> main_opers = {"*", "/", "**", "//", "%", "x", "X", ":"};
const string double_lits = "/*";
const string figures = "1234567890.";
const string mult = "*xX";
const string divis = "/:";

string calculator(string str)
{
    string res = main_calculate(convert_div_mult(str));
    return res;
}

string convert_div_mult(string str)
{
    string temp_str;
    for (int i = 0; i < str.length(); i++)
    {
        if (mult.find(str[i]) < 3)
        {
            temp_str += "*";
        }
        if (divis.find(str[i]) < 2)
        {
            temp_str += "/";
        }
        if (((divis.find(str[i]) < 3) or (mult.find(str[i])) < 2) == 0)
        {
            temp_str += str[i];
        }
    }
    return temp_str;
}

//@brief считает количство данных элементов в строке
//@param str строка, в которой считются элементы
//@param item искомый элемент
//@return количество элементов item в строке
int count(string str, int item)
{
    int k = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == item)
        {
            k++;
        }
    }
    return k;
}

//@brief меняет тип элемента с string на int
//@param myLongDouble элемент, который нужно перевести в string
//@return элемент типа string
string convert(int myLongDouble)
{
    stringstream blah;
    blah << myLongDouble;

    return blah.str();
}

//@brief ищет элемент в векторе
//@param vec вектор в котором ведётся поиск
//@param item искомый элемент
//@return true если элемент есть в векторе, false если его нет
bool find(vector<string> vec, string item)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == item)
        {
            return true;
        }
    }
    return false;
}

//@brief проверяет, является ли строка числом
bool is_num(string str)
{
    int i = 0, count = 0;
    while (str[i])
    {
        if ((isdigit(str[i]) == false) and (str[i] != '.') and (str[i] != 'e'))
        {
            if (i != str.length() - 1)
            {
                if ((str[i] == '+') and (str[i - 1] == 'e'))
                {
                    i++;
                    continue;
                }
            }
            count++;
            if (str[i] != '-')
            {
                break;
            }
        }
        i++;
    }
    if ((str.length() == 1) and (str[0] == '-'))
    {
        return false;
    }
    if ((count == 0) or ((count == 1) and (str[0] == '-')))
        return true;
    else
        return false;
}

//@brief создаёт цельную строку типа string из всех эллементов вектора
string join(vector<string> vec)
{
    string temp_str = "";
    for (int i = 0; i < vec.size(); i++)
    {

        temp_str += vec[i];
    }
    return temp_str;
}

//@brief удаляет все пробелы из строки
string del_whitespace(string to_del)
{
    int index = 0;
    string temp_expr = "";
    for (int i = 0; i < to_del.length(); i++)
    {
        if (to_del[i] != ' ')
        {
            temp_expr += to_del[i];
            index++;
        }
    }
    return temp_expr;
}

//@brief основная функция счета. пока в выражении присутствуют скобки, вызывает функцию full_calculation,
//@brief определяет порядок выполнения операций находящихся в скобках
//@param to_calc начальное выражение
//@return ответ на запрос пользователя
string main_calculate(string to_calc)
{
    string ans = to_calc;
    string temp_expr = "";
    string in_brackets = "";
    bool flag = false;
    to_calc = del_whitespace(to_calc);
    while (ans.find('(') < ans.length())
    {
        for (int i = 0; i < to_calc.length(); i++)
        {
            if ((to_calc[i] != '(') and (to_calc[i] != ')') and (flag == false))
            {
                temp_expr += to_calc[i];
            }
            else
            {
                if (((to_calc[i] == '(') or (flag == true)) and ((count(in_brackets, ')') < count(in_brackets, '(')) or (to_calc[i] != ')')))
                {
                    if (flag == false)
                    {
                        flag = true;
                    }
                    else
                    {
                        if ((to_calc[i - 1] == '(') and (to_calc[i] == '-'))
                        {
                            in_brackets += '-';
                        }
                        else
                        {
                            in_brackets += to_calc[i];
                        }
                    }
                }
                else
                {
                    temp_expr += full_calculation(in_brackets);
                    in_brackets = "";
                    flag = false;
                }
            }
        }
        ans = temp_expr;
        temp_expr = "";
    }
    ans = full_calculation(del_whitespace(ans));
    return ans;
}

//@brief разделяет сплошную строку на числа и знаки операций
//@param to_calc строка, которую нужно разделить
//@return вектор в котором хранятся числа и операции
vector<string> dif_calculation(string to_calc)
{
    vector<string> vec_str;
    string temp_str = "";
    for (int i = 0; i < to_calc.length(); i++) // проход по всему переданному выражению
    {
        if (figures.find(to_calc[i]) < figures.length()) // если цифра
        {
            if (temp_str.length() == 0) // если цифра и темп пустой
            {
                temp_str += to_calc[i];
            }
            else // если цифра и темп не пустой
            {
                if (figures.find(temp_str[temp_str.length() - 1]) < figures.length()) // если цифра и в темпе цифpа/число
                {
                    temp_str += to_calc[i];
                }
                else // если цифра и в темпе знак
                {
                    if (temp_str[0] == '-') // если цифра и в темпе минус
                    {
                        if (vec_str.size() != 0)
                        {
                            if (figures.find(vec_str[vec_str.size() - 1][0]) < figures.length()) // если цифра и в темпе минус и предыдущее значение - цифра
                            {
                                vec_str.push_back(temp_str);
                                temp_str = to_calc[i];
                            }
                            else // если цифра и в темпе минус и предыдущее значение - знак
                            {
                                temp_str += to_calc[i];
                            }
                        }
                        else
                        {
                            temp_str += to_calc[i]; // если цифра и в темпе минус и предыдущего нет
                        }
                    }
                    else
                    {
                        vec_str.push_back(temp_str);
                        temp_str = to_calc[i];
                    }
                }
            }
        }
        else // если знак
        {
            if (temp_str.length() == 0) // если знак и в темпе пусто
            {
                temp_str += "-";
            }
            else // если знак и в темпе не пусто
            {
                if (figures.find(temp_str[temp_str.length() - 1]) < figures.length()) // если знак и в темпе цифра/число
                {
                    vec_str.push_back(temp_str);
                    temp_str = to_calc[i];
                }
                else // если знак и в темпе знак
                {
                    if (to_calc[i] == '-') // если число отрицательное
                    {
                        {
                            vec_str.push_back(temp_str);
                            temp_str = '-';
                        }
                    }
                    else // если знак и в темпе знак
                    {
                        vec_str.push_back(temp_str + temp_str);
                        temp_str = "";
                    }
                }
            }
        }
    }
    if (temp_str.length() != 0)
    {
        vec_str.push_back(temp_str);
    }
    return vec_str;
}

//@brief выполняет простые математические операции
//@param num_1 число слева с остатком
//@param num_2 число справа с остатком
//@param num_1_int число слева без остатка
//@param num_2_int число справа без остатка
//@param oper математическая операция
//@return результат операции
int simp_calculation(int num_1, int num_2, int num_1_int, int num_2_int, string oper)
{
    int res;
    if ((oper == "*") or (oper == "x") or (oper == "X"))
    {
        res = num_1 * num_2;
    }
    if ((oper == "/") or (oper == ":"))
    {
        res = num_1 / num_2;
    }
    if (oper == "+")
    {
        res = num_1 + num_2;
    }
    if (oper == "-")
    {
        res = num_1 - num_2;
    }
    if (oper == "**")
    {
        if (((num_1 < 0) and (num_2 != num_2_int)) == 0)
        {
            res = pow(num_1, num_2);
        }
        else
        {
            throw "Hельзя возводить отрицательные числа в действительную степень(";
        }
    }
    if (oper == "%")
    {
        if ((num_1 == num_1_int) and (num_2 == num_2_int))
        {
            res = num_1_int % num_2_int;
        }
        else
        {
            throw "Недопустимые значения для %";
        }
    }
    if (oper == "//")
    {
        int _res = num_1 / num_2;
        res = _res;
    }
    return res;
}

//@brief определяет порядок выполнения операций не находящихся в скобках, вызывает функцию simp_calculation
//@param _to_calc часть выражения, которую нужно решить
//@return результат одной или более мат операции
string full_calculation(string _to_calc)
{
    if (_to_calc.find('(') < _to_calc.length())
    {
        return main_calculate(_to_calc);
    }
    vector<string> to_calc = dif_calculation(_to_calc);
    int to_calc_len = to_calc.size();
    if (find(to_calc, "("))
    {
        return main_calculate(join(to_calc));
    }

    while (is_num(join(to_calc)) == 0)
    {
        if ((to_calc[0][0] == '-') and (to_calc[1][0] == '-'))
        {
            int num_1 = stold(to_calc[0]);
            int num_2 = stold(to_calc[1]);
            int num_1_int = stoi(to_calc[0]);
            int num_2_int = stoi(to_calc[1]);
            int res = simp_calculation(num_1, num_2, num_1_int, num_2_int, "+");
            return convert(res);
        }
        for (int i = 1; i < to_calc_len - 1; i++)
        {
            if (is_num(to_calc[i]) == false)
            {
                int k1 = 0, k2 = 0;
                for (int k = 0; k < main_opers.size(); k++)
                {
                    if (find(to_calc, main_opers[k]) == 0)
                    {
                        k2++;
                    }
                }

                for (int j = 0; j < main_opers.size(); j++)
                {
                    if ((to_calc[i] == main_opers[j]) or (k2 == 8))
                    {
                        k1++;
                        break;
                    }
                }
                if (k1 != 0)
                {
                    if ((join(to_calc).find("*") > join(to_calc).find("/")) and (find(to_calc, "*") < i) and (join(to_calc).find("*") < join(to_calc).length()) and (to_calc[i] != "*"))
                    {
                        i++;
                        continue;
                    }
                    int num_1, num_2, res;
                    num_1 = stold(to_calc[i - 1]);
                    num_2 = stold(to_calc[i + 1]);
                    int num_1_int = stoi(to_calc[i - 1]);
                    int num_2_int = stoi(to_calc[i + 1]);
                    res = simp_calculation(num_1, num_2, num_1_int, num_2_int, to_calc[i]);

                    to_calc.erase(to_calc.begin() + i - 1, to_calc.begin() + i + 1);
                    if (to_calc.size() == 0)
                    {
                        to_calc.push_back(convert(res));
                    }
                    else
                    {
                        to_calc[i - 1] = convert(res);
                    }
                    to_calc_len -= 2;
                    break;
                }
            }
        }
    }
    return to_calc[0];
}
