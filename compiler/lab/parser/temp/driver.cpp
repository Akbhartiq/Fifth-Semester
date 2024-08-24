#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "lex.yy.c"
using namespace std;

// Get the Node to store the ID
struct id_node
{
    char *name;
    struct id_node *next;
    int value;
    bool flag; // whether got the value or not
};
typedef id_node *T;

// Get the Node to store the Number
struct num_node
{
    int value;
    struct num_node *next;
};
typedef num_node *C;

// Two important Global nodes
T global_id_node;
C global_num_node;

// add to T
T addT(T head, char *id)
{
    T temp = head;
    while (temp)
    {
        if (!strcmp(temp->name, id))
        {
            global_id_node = temp;
            printf("Identifier %s is already there\n", id);
            return head;
        }
        temp = temp->next;
    }

    temp = (T)malloc(sizeof(id_node));
    temp->name = (char *)malloc(strlen(id) + 1);
    strcpy(temp->name, id);
    temp->flag = false;
    temp->next = head;
    global_id_node = temp;
    return temp;
}

// Insert value for the identifier
void insertValue(T head, int val)
{
    T temp = head;
    while (temp->next)
    {
        if (temp->next->flag)
        {
            temp->value = val;
            temp->flag = true;
            return;
        }
        else
        {
            temp = temp->next;
        }
    }
    if (temp->next == NULL)
    {
        temp->value = val;
        temp->flag = true;
        return;
    }
    cout << "Seems like you have more integer value than Identifier(Latters are ignored)" << endl;
}

// add to C
C addC(C head, int val)
{
    C temp = head;
    while (temp)
    {

        if (temp->value == val)
        {
            global_num_node = temp;
            printf("Number %d is already there\n", val);
            return head;
        }
        temp = temp->next;
    }

    temp = (C)malloc(sizeof(num_node));
    temp->value = val;
    temp->next = head;
    global_num_node = temp;
    return temp;
}

int main()
{
    int token;
    stack<string> st;
    string tos; // top of stack
    st.push("E");
    // Get the vector of string
    vector<pair<int, string>> tok;
    while ((token = yylex()))
    {
        switch (token)
        {
        case ADD:
        case MUL:
        case NUM:
        case LP:
        case RP:
            tok.push_back({token, yytext});
        default:
            break;
        }
    }
    int ip = 0;
    while (ip < tok.size())
    {

        switch (tok[ip].first)
        {
        case LP:
            // cout << "LP found" << endl;
            tos = st.top();
            if (tos == "(")
            {
                st.pop();
                ip++;
            }
            else if (tos == "E")
            {
                st.pop();
                st.push("E`");
                st.push("T`");
                st.push(")");
                st.push("E");
                ip++;
            }
            else if (tos == "T")
            {
                st.pop();
                st.push("T`");
                st.push(")");
                st.push("E");
                ip++;
            }
            else if (tos == "F")
            {
                st.pop();
                st.push(")");
                st.push("E");
                ip++;
            }
            else
            {
                cout << "Error1" << endl;
                exit(0);
            }
            break;
        case RP:
            // cout << "RP found" << endl;
            tos = st.top();
            if (tos == ")")
            {
                st.pop();
                ip++;
            }
            else if (tos == "E`")
            {
                st.pop();
            }
            else if (tos == "T`")
            {
                st.pop();
            }
            else
            {
                cout << "Error2" << endl;
                exit(0);
            }
            break;
        case NUM:
            // cout << "NUM found" << endl;
            tos = st.top();

            if (tos == "E")
            {
                st.pop();
                st.push("E`");
                st.push("T`");
                ip++;
            }
            else if (tos == "T")
            {
                st.pop();
                st.push("T`");
                ip++;
            }
            else if (tos == "F")
            {
                st.pop();
                ip++;
            }
            else
            {
                // cout << "Tos was " << tos << endl;
                // cout << "tok[ip] was " << tok[ip].second << endl;
                cout << "Error3" << endl;
                exit(0);
            }
            break;
        case ADD:
            tos = st.top();
            if (tos == "E`")
            {
                st.pop();
                st.push("E`");
                st.push("T");
                ip++;
            }
            else if (tos == "T`")
            {
                st.pop();
            }
            else
            {
                cout << "Error4" << endl;
                exit(0);
            }
            // cout << "ADD found" << endl;
            break;
        case MUL:
            tos = st.top();
            if (tos == "T`")
            {
                st.pop();
                st.push("T`");
                st.push("F");
                ip++;
            }
            else
            {
                cout << "Error5" << endl;
                exit(0);
            }
            // cout << "MUL found" << endl;
            break;
        default:
            cout << "Error6" << endl;
            break;
        }
    }

    // Finally stack can only contains E` and T`
    while (!st.empty())
    {
        if (st.top() == "E`" or st.top() == "T`")
        {
            st.pop();
            continue;
        }
        else
        {
            cout << "Error7" << endl;
            exit(0);
        }
    }

    cout << "Parsing is SuccessFul" << endl;
}