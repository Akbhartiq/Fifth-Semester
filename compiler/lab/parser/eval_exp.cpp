#include <bits/stdc++.h>
using namespace std;

// To check if invalid char
bool invalidChar(char ch)
{
    if ((ch <= '9' and ch >= '0') or (ch == ' ') or (ch == '*') or (ch == '+') or ch == '(' or ch == ')')
    {
        return false;
    }
    else
    {
        return true;
    }
}

// To remove extra brackets like ((((3+4))))
string remove_extra_bracket(string exp)
{
    string temp;
    for (auto it : exp)
    {
        if (it != '(' or it != ')')
        {
            temp += it;
        }
    }
    return temp;
}

// To get rid of redundant spaces
string modify(string exp)
{
    string temp;
    for (int i = 0; i < exp.size(); i++)
    {
        if (exp[i] != ' ')
        {
            temp += exp[i];
        }
        else
        {
            if (temp.size())
            {
                if (temp[temp.size() - 1] != ' ')
                {
                    temp += exp[i];
                }
            }
        }
    }
    return temp;
}

// checking the validity of string
bool isvalid(string exp)
{
    stack<char> st;
    for (auto it : exp)
    {
        if (it == '(')
        {
            st.push(it);
        }
        else if (it == ')')
        {
            if (st.empty())
            {
                return false;
            }
            st.pop();
        }
    }
    if (st.size())
        return false;
    char prev = 'a';
    char pre_prev = 'b';
    for (int i = 0; i < exp.size(); i++)
    {
        if (exp[i] <= '9' and exp[i] >= '0')
        {
            if (prev == ' ' and (pre_prev <= '9' and pre_prev >= '0'))
            {
                return false;
            }
        }
        if ((prev == '*' or prev == '+') and (exp[i] == '*' or exp[i] == '+' or exp[i] == ')'))
        {
            return false;
        }
        if ((prev == '(') and (exp[i] == '*' or exp[i] == '+'))
        {
            return false;
        }
        pre_prev = prev;
        prev = exp[i];
    }
    return true;
}

// to get rid of all space after sure that exp is valid
string remove_space(string exp)
{
    string temp = "";
    for (auto it : exp)
    {
        if (it != ' ')
        {
            temp += it;
        }
    }
    return temp;
}

long long int evalsum(string exp);

long long int evalterm(string exp)
{

    cout << "Exp in term is " << exp << endl;
    string temp;
    long long int res = 1;
    stack<char> st;
    int idx = 0;
    int numOfoperator = 0;
    for (int i = 0; i < exp.size(); i++)
    {
        if (exp[i] != ' ')
        {
            if (exp[i] == '+')
            {
                numOfoperator++;
                // ch = '+';
            }
            if (exp[i] == '*')
            {
                numOfoperator++;
                // ch = '*';
            }
            if (exp[i] == '(')
            {
                temp += exp[i];
                st.push(exp[i]);
            }
            else if (exp[i] == ')')
            {
                temp += exp[i];
                st.pop();
            }
            else if (exp[i] == '*' and st.empty())
            {
                res *= evalsum(temp);
                temp = "";
            }
            else
            {
                temp += exp[i];
            }
        }
    }
    if (!numOfoperator)
    {
        try
        {
            long long int val = stoll(exp);
            return val;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            cout << "Invalid Expression" << endl;
            exit(0);
        }
    }
    if (temp.size())
    {
        temp = remove_extra_bracket(temp);
        res *= evalsum(temp);
    }
    return res;
}

long long int evalsum(string exp)
{
    // cout << "Exp in sum is " << exp << endl;
    string temp;
    long long int res = 0;
    stack<char> st;
    bool flag = false;
    int idx = 0;
    while (exp[idx] == '(' and exp[exp.size() - idx - 1] == ')')
    {
        exp.erase(exp.size() - 1, 1);
        exp.erase(0, 1);
        if (!isvalid(exp))
        {
            exp += ')';
            exp.insert(0, 1, '(');
            break;
        }
    }
    int numOfoperator = 0;
    // char ch = 'a';
    for (int i = 0; i < exp.size(); i++)
    {
        if (exp[i] != ' ')
        {
            if (exp[i] == '+')
            {
                numOfoperator++;
                // ch = '+';
            }
            if (exp[i] == '*')
            {
                numOfoperator++;
                // ch = '*';
            }
            if (exp[i] == '(')
            {
                temp += exp[i];
                st.push(exp[i]);
            }
            else if (exp[i] == ')')
            {
                temp += exp[i];
                st.pop();
            }
            else if (exp[i] == '+' and st.empty())
            {
                res += evalterm(temp);
                cout << "Res is " << res << endl;
                temp = "";
            }
            else
            {
                temp += exp[i];
            }
        }
    }
    if (!numOfoperator)
    {
        try
        {
            long long int val = stoll(exp);
            return val;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            cout << "Invalid Expression" << endl;
            exit(0);
        }
    }
    if (temp.size())
    {
        res += evalterm(temp);
    }
    return res;
}

int main()
{
    string exp;
    cout << "Enter the string:" << endl;
    getline(cin, exp);
    exp = modify(exp);
    cout << "Modified exp is " << exp << endl;
    bool flag = isvalid(exp);
    if (!flag)
    {
        cout << "Expression is Invalid" << endl;
        exit(0);
    }
    for (auto it : exp)
    {
        flag = invalidChar(it);
        if (flag)
        {
            cout << "Invalild expression" << endl;
            exit(0);
        }
    }
    exp = remove_space(exp);
    long long int ans = evalsum(exp);
    cout << ans << endl;
}
