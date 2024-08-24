// Driver code
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stack>
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

// Get the nodes for creating the Parse Table
typedef enum
{
    operation,  // Operator
    identifier, // Identifier (reference to T)
    number      // Number (reference to C)
} Type;

// Get the Union Structure
typedef union
{
    char operation_type; // Operator (e.g., '+', '-', '*', '/')
    id_node *refT;       // Reference to an entry in T
    num_node *refC;      // Reference to an entry in C
} Value;

// Get the node
typedef struct Node
{
    Type type;          // Type of the node (OP/ID/NUM)
    Value value;        // Union holding the operator or reference
    struct Node *left;  // Pointer to the left child
    struct Node *right; // Pointer to the right child
    string initial;     // How many tab to be printed in the front
} Node;

// Let's write a function to init a node
Node *init(Type t, Value val, string in)
{
    // Use the new method
    Node *head = new Node();
    head->type = t;
    head->value = val;
    head->left = NULL;
    head->right = NULL;
    head->initial = in;
    return head;
}

// Function to create a node
Node *buildParseTree(Node *head, Type t, Value val, bool &flag, string in)
{

    if (!head)
    {
        Node *temp = init(t, val, in);
        flag = true;
        // if (t == operation)
        // {
        //     cout << val.operation_type << endl;
        // }
        // else if (t == number)
        // {
        //     cout << (val.refC)->value << endl;
        // }
        // else
        // {
        //     cout << (val.refT)->value << endl;
        // }

        return temp;
    }
    else
    {
        if (head->type != identifier and head->type != number)
            if (!flag)
                head->left = buildParseTree(head->left, t, val, flag, in + "\t");
        if (head->type != identifier and head->type != number)
            if (!flag)

                head->right = buildParseTree(head->right, t, val, flag, in + "\t");

        return head;
    }
}

// Function to evaluate the parsing value
int eval(Node *head)
{
    if (head->type == identifier)
    {
        // get the-reference and get the value
        int temp = ((head->value).refT)->value;
        return temp;
    }
    else if (head->type == number)
    {
        // get the reference and get the value
        int temp = ((head->value).refC)->value;
        return temp;
    }
    else
    {
        // It is an opeartion (binary)
        int left = eval(head->left);
        int right = eval(head->right);

        // check type of operation
        char ch = ((head->value).operation_type);
        switch (ch)
        {
        case '+':
            return left + right;
            break;
        case '-':
            return left - right;
            break;
        case '*':
            return left * right;
            break;
        case '/':
            return left / right;
            break;
        case '%':
            return left % right;
            break;
        }
    }
    return -1; // never executed
}
// Pre-order traversal of a tree
void preOrder(Node *head)
{
    if (!head)
        return;
    if (head->type == operation)
    {
        cout << head->initial;
        if ((head->initial) != "")
            cout << "--->";
        cout << "OP(" << (head->value).operation_type << ")" << endl;
    }
    else if (head->type == identifier)
    {
        // get the-reference and get the value
        cout << head->initial;
        int temp = ((head->value).refT)->value;
        cout << "--->ID (" << temp << ")" << endl;
    }
    else
    {
        // get the-reference and get the value
        cout << head->initial;
        int temp = ((head->value).refC)->value;
        cout << "--->NUM (" << temp << ")" << endl;
    }
    preOrder(head->left);
    preOrder(head->right);
}

// Helper function to print the Error
string help(string s)
{
    if (s == "ARG")
    {
        return "ID/NUM/LP";
    }
    if (s == "(")
        return "LP";
    if (s == ")")
        return "RP";
    return s;
}

int main()
{
    // Get the 2  Symbol Tables for the ID and the NUM
    T idtable = NULL;
    C numtable = NULL;

    // Get the Stack for parsing
    stack<string> st;
    // Init the Parsing process
    st.push("EXPR");

    // tos
    string tos;

    int token;

    // temporary string
    string temporary;

    // get the root of the binary tree
    Node *root = NULL;
    // get the value
    Value value_temp;
    // get the flag variable for building the tree
    bool flag = false;
    // get the string for the initials during printing
    string in = "";

    while ((token = yylex()))
    {
        switch (token)
        {
        case LP:
            // printf("LP found\n");
            // check the top of stack
            if (st.empty())
            {
                cout << "Error -> Seems like you want 2 Fnctions" << endl;
                exit(0);
            }
            tos = st.top();
            if (tos == "(")
            {
                // Good
                st.pop();
            }
            else
            {
                if (tos == "EXPR" or tos == "ARG")
                {
                    st.pop();
                    //(OP ARG ARG)
                    st.push(")");
                    st.push("ARG");
                    st.push("ARG");
                    st.push("OP");
                    // st.push("("); -matched
                }
                else
                {
                    cout << "Error!! -> Expected " << help(tos) << " Instead of (" << endl;
                    exit(0);
                }
            }
            break;
        case RP:
            if (st.empty())
            {
                cout << "Error -> Seems like you want 2 Fnctions" << endl;
                exit(0);
            }
            // printf("RP found\n");
            // check the top of stack
            tos = st.top();
            if (tos == ")")
            {
                // Good
                st.pop();
            }
            else
            {
                cout << "Error!! -> Expected " << help(tos) << " Instead of )" << endl;
                exit(0);
            }
            break;
        case ADD:
            if (st.empty())
            {
                cout << "Error -> Seems like you want 2 Fnctions" << endl;
                exit(0);
            }
            // create the ParseTree
            value_temp.operation_type = '+';
            root = buildParseTree(root, operation, value_temp, flag, in);
            flag = false;
            // printf("Add found\n");
            // check the top of stack
            tos = st.top();
            if (tos == "+")
            {
                // Good
                st.pop();
            }
            else
            {
                if (tos == "OP")
                {
                    st.pop();
                }
                else
                {
                    cout << "Error!! -> Expected " << help(tos) << " Instead of +" << endl;
                    exit(0);
                }
            }
            break;
        case SUB:
            if (st.empty())
            {
                cout << "Error -> Seems like you want 2 Fnctions" << endl;
                exit(0);
            }
            // create the ParseTree
            value_temp.operation_type = '-';
            root = buildParseTree(root, operation, value_temp, flag, in);
            flag = false;
            // printf("Sub found\n");
            // check the top of stack
            tos = st.top();
            if (tos == "-")
            {
                // Good
                st.pop();
            }
            else
            {
                if (tos == "OP")
                {
                    st.pop();
                }
                else
                {
                    cout << "Error!! -> Expected " << help(tos) << " Instead of -" << endl;
                    exit(0);
                }
            }
            break;
        case MUL:
            if (st.empty())
            {
                cout << "Error -> Seems like you want 2 Fnctions" << endl;
                exit(0);
            }
            // create the ParseTree
            value_temp.operation_type = '*';
            root = buildParseTree(root, operation, value_temp, flag, in);
            flag = false;
            // printf("Mul found\n");
            // check the top of stack
            tos = st.top();
            if (tos == "*")
            {
                // Good
                st.pop();
            }
            else
            {
                if (tos == "OP")
                {
                    st.pop();
                }
                else
                {
                    cout << "Error!! -> Expected " << help(tos) << " Instead of *" << endl;
                    exit(0);
                }
            }
            break;
        case DIV:
            if (st.empty())
            {
                cout << "Error -> Seems like you want 2 Fnctions" << endl;
                exit(0);
            }
            // create the ParseTree
            value_temp.operation_type = '/';
            root = buildParseTree(root, operation, value_temp, flag, in);
            flag = false;
            // printf("Div found\n");
            // check the top of stack
            tos = st.top();
            if (tos == "/")
            {
                // Good
                st.pop();
            }
            else
            {
                if (tos == "OP")
                {
                    st.pop();
                }
                else
                {
                    cout << "Error!! -> Expected " << help(tos) << " Instead of /" << endl;
                    exit(0);
                }
            }
            break;
        case MOD:
            if (st.empty())
            {
                cout << "Error -> Seems like you want 2 Fnctions" << endl;
                exit(0);
            }
            // create the ParseTree
            value_temp.operation_type = '%';
            root = buildParseTree(root, operation, value_temp, flag, in);
            false;
            // printf("Mod found\n");
            // check the top of stack
            tos = st.top();
            if (tos == "%")
            {
                // Good
                st.pop();
            }
            else
            {
                if (tos == "OP")
                {
                    st.pop();
                }
                else
                {
                    cout << "Error!! -> Expected " << help(tos) << " Instead of %" << endl;
                    exit(0);
                }
            }
            break;
        case ID:
            if (st.empty())
            {
                cout << "Error -> Seems like you want 2 Fnctions" << endl;
                exit(0);
            }
            // printf("Id found\n");
            // check the top of stack
            tos = st.top();
            if (tos == "ARG")
            {
                st.pop();
            }
            else
            {
                cout << "Error!! -> Expected " << help(tos) << " Instead of " << yytext << endl;
                exit(0);
            }
            // add it to symbol Table
            idtable = addT(idtable, yytext);
            // now global_id_node contains my target values
            value_temp.refT = global_id_node;
            root = buildParseTree(root, identifier, value_temp, flag, in);
            flag = false;
            break;
        case NUM:
            if (st.empty())
            {
                cout << "Reading Variables from the input: " << yytext << endl;
                insertValue(idtable, stoi(yytext));
                continue;
            }
            // printf("Num found\n");
            // check the top of stack
            tos = st.top();
            if (tos == "ARG")
            {
                st.pop();
            }
            else
            {
                cout << "Error!! -> Expected " << help(tos) << " Instead of " << yytext << endl;
                exit(0);
            }
            // add it to symbol Table
            numtable = addC(numtable, stoi(yytext));
            // now global_num_node contains my value
            value_temp.refC = global_num_node;
            root = buildParseTree(root, number, value_temp, flag, in);
            flag = false;
            break;
        case SP: // space
            continue;
            break;
        default:
            // Keep getting the next-token until space found
            temporary = yytext;
            // cout << yytext << "here is" << endl;
            while (token = yylex())
            {
                if (token == SP)
                {
                    break;
                }
                temporary = temporary + yytext;
            }
            cout << "Error!!  Invalid Operator " << temporary << " Found" << endl;
            exit(0);
        }
    }
    if (!st.empty())
    {
        cout << "Error!! Incomplete Statment" << endl;
        exit(0);
    }

    // Let's print the tree
    cout << "\n\nParsing is SuccessFul\n\nTree Looks like" << endl;
    preOrder(root);
    cout << endl;
    // Now we are done with building the Tree
    int result = eval(root);
    cout << "Result: " << result << endl;
}