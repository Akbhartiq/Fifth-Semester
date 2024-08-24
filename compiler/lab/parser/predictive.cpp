// Let's implement the Predictive Parser
#include <bits/stdc++.h>
using namespace std;

// Function to convert the char to corresponding string
string char_to_string(char ch)
{
    string st = "";
    st = st + ch;
    return st;
}

// To check terminal and non-terminal
bool isnonTerminal(char ch)
{

    if (ch <= 'Z' and ch >= 'A')
        return true;
    return false;
}

// Hard-code the grammar
vector<pair<string, vector<string>>> gm = {{"A", {"BC"}}, {"C", {"+BC", "z"}}, {"B", {"DE"}}, {"E", {"*DE", "z"}}, {"D", {"(A)", "i"}}};

// Terminals
vector<string> term = {"i", "+", "*", "(", ")"};

// Non-terminals
vector<string> nonterm = {"A", "B", "C", "D", "E"};

// First of the grammar
unordered_map<string, set<string>> first;

// Follow of the grammar
unordered_map<string, set<string>> follow;

// compute the first
set<string> compFirst(string val)
{
    char ch = val[0];
    bool flag = isnonTerminal(ch);
    cout << "Compute first is called for: " << val << endl;

    if (flag)
    {
        // If it is non-terminal
        set<string> ret;
        for (int i = 0; i < val.size(); i++)
        {
            char it1 = val[i];
            set<string> get = compFirst(char_to_string(it1));
            // check if "z" is also there
            auto temp = get.find("z");
            if (temp == get.end())
            {
                // combine ret and get
                for (auto it2 : get)
                {
                    ret.insert(it2);
                }
                return ret;
            }
            else
            {
                // Insert everything except the "z"
                for (auto it2 : get)
                {
                    if (it2 != "z" or i == val.size())
                    {
                        ret.insert(it2);
                    }
                }
            }
        }
        return ret;
    }
    else
    {
        set<string> ret;
        ret.insert(char_to_string(ch));
        return ret;
    }
}

void precomputeFirst()
{
    // Let' precompute
    for (auto it : gm)
    {
    }
}

void precomputeFollow()
{
    // This is the tricky one
    follow["A"] = {")", "$"};
    auto temp = compFirst(char_to_string('C'));
    auto it = temp.find("z");
    if (it != temp.end())
        temp.erase(it);
    follow["B"] = temp;
    follow["C"] = follow["A"];
    temp = compFirst(char_to_string('E'));
    it = temp.find("z");
    if (it != temp.end())
        temp.erase(it);
    follow["D"] = temp;

    follow["E"] = follow["B"];
}

// Let's declare the parsing table
unordered_map<string, string> parseTable;

// Function to fill the parseTable
void fillTable()
{
    // Traverse each of the productions
    for (int i = 0; i < gm.size(); i++)
    {
        string left = gm[i].first;
        vector<string> right = gm[i].second;
        for (int j = 0; j < right.size(); j++)
        {
            // compute the first of right-side and check if it dervies epsilan or not
            set<string> temp_first = compFirst(right[j]);
            auto flag = temp_first.find("z"); // epsilan
            if (flag != temp_first.end())
            {
                // get the follow of left
                auto temp_follow = follow[left];
                // traverse and put the production
                for (auto firstchar : temp_follow)
                {
                    string str = left + firstchar;
                    parseTable[str] = right[j];
                }
            }
            else
            {
                // Traverse the whole first
                for (auto firstchar : temp_first)
                {
                    // get the string
                    string str = left + firstchar;
                    parseTable[str] = right[j];
                }
            }
        }
    }
}

int main()
{

    precomputeFollow();
    for (auto it : follow["A"])
    {
        cout << it << endl;
    }
    fillTable();
    // All Non-terminals are capital and all terminals are lower-case
    // Now get a string and try to parse it
    string input = "i$";

    // We need to maintain a stack
    stack<string> st;
    st.push("$");
    st.push("A");

    // get the alog initiated
    int ip = 0;
    while (!st.empty())
    {
        // get the top of stack
        string tos = st.top();

        // [check if it is nonTerminal]
        bool flag = isnonTerminal(tos[0]);

        if (flag)
        {
            // get the corresponding production
            string str = tos + char_to_string(input[ip]);
            string prod = parseTable[str];
            cout << "Value of str" << str << endl;
            cout << "Value of prod" << prod << endl;
            st.pop();
            reverse(prod.begin(), prod.end());
            for (auto ch : prod)
            {
                st.push(char_to_string(ch));
            }
        }
        else
        {
            // terminal
            if (tos[0] == input[ip])
            {
                ip++;
                st.pop();
            }
            else
            {
                cout << "Error" << endl;
                exit(0);
            }
        }
    }
    cout << "Matched" << endl;
}