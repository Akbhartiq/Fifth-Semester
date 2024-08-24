#include <iostream>
#include <cstring>
#include "lex.yy.c"

using namespace std;

// To retrieve the environment variables
char *getEnv(char *id)
{
    // dynamic memory allocation
    char *temp = (char *)malloc(strlen(id) + 1);
    int length = strlen(id) + 1;
    bool flag = 0;
    int index = 0;
    for (int i = 0; i < length; i++)
    {
        if (flag)
        {
            // if } skip
            if (i != length - 2)
                temp[index++] = id[i];
        }
        // if { , start taking characters in temp
        if (id[i] == '{')
        {
            flag = 1;
        }
    }
    return temp;
}

// command linked list
struct command
{
    char *name;
    int count;
    struct command *next;
};
typedef command *symbolTableCommand;

// Environment variable linked list
struct Env
{
    char *name;
    int count;
    struct Env *next;
};

typedef Env *symbolTableEnv;

// add to commandTable
symbolTableCommand addToCommand(symbolTableCommand T, char *id)
{
    symbolTableCommand temp = T;
    while (temp)
    {
        if (!strcmp(temp->name, id))
        {
            // if already present return by increasing count
            temp->count = temp->count + 1;
            return T;
        }
        temp = temp->next;
    }
    // create the node
    temp = (symbolTableCommand)malloc(sizeof(command));
    temp->count = 1; // init count to 1
    // copy id
    temp->name = (char *)malloc(sizeof(strlen(id) + 1));
    strcpy(temp->name, id);
    // make the link
    temp->next = T;
    T = temp;
    // return T
    return T;
}

// add to Env Table
symbolTableEnv addToEnv(symbolTableEnv T, char *id)
{
    symbolTableEnv temp = T;
    while (temp)
    {
        if (!strcmp(temp->name, id))
        {
            // if already present, increase count and return
            temp->count = temp->count + 1;
            return T;
        }
        temp = temp->next;
    }
    // create the node
    temp = (symbolTableEnv)malloc(sizeof(Env));
    temp->count = 1; // init count to 1
    temp->name = (char *)malloc(sizeof(strlen(id) + 1));
    strcpy(temp->name, id);
    // make the link
    temp->next = T;
    T = temp;
    // return T
    return T;
}

// print command Table
void printCommand(symbolTableCommand T)
{
    symbolTableCommand temp = T;
    while (temp)
    {
        cout << "\t" << temp->name << " (" << temp->count << ")" << endl;
        temp = temp->next; // next pointer
    }
}

// print Env Table
void printEnv(symbolTableEnv T)
{
    symbolTableEnv temp = T;
    while (temp)
    {
        cout << "\t" << temp->name << " (" << temp->count << ")" << endl;
        temp = temp->next; // next pointer
    }
}

int main()
{
    int Inline = 0;               // number of inline maths equation
    bool flag1 = 0;               // flag var to count the number of inline equation
    int Display = 0;              // number of display maths equation
    bool flag2 = 0;               // flag var to count the number of display equation
    int token;                    // get the token
    symbolTableCommand T1 = NULL; // command Table
    symbolTableEnv T2 = NULL;     // Env Table
    char *temp;                   // To get the env variable
    while ((token = yylex()))
    {
        switch (token)
        {
        case TD:
            // cout << "Tilda Found:" << yytext << endl;
            T1 = addToCommand(T1, yytext);
            break;
        case BK:
            // cout << "Alphabetic commands found: " << yytext << endl;
            T1 = addToCommand(T1, yytext);
            break;
        case BCM:
            // cout << "single letter command found: " << yytext << endl;
            T1 = addToCommand(T1, yytext);
            break;
        case CM:
            // cout << "Comment found: " << yytext << endl;
            // just do nothing
            break;
        case ENV:
            // cout << "Environment variable found: " << yytext << endl;
            temp = getEnv(yytext);
            T2 = addToEnv(T2, temp);
            break;
        case MT1:
            // cout << "Math1 found!!" << endl;
            flag1 = !flag1;  // invert the flag
            Inline += flag1; // and add
            break;
        case MT2:
            // cout << "Math2 found!!" << endl;
            flag2 = !flag2;   // invert the flag
            Display += flag2; // and add
            break;
        case MT3:
            // cout<<"Math2 found!!"<<endl;
            flag2 = !flag2;
            Display += flag2;
            break;
        default:
            break;
        }
    }

    // Let's print the result
    cout << "Commands Used:\n";
    printCommand(T1);

    // Let's print the Environment used
    cout << "Environment Used:\n";
    printEnv(T2);

    // Let's print the count of the Math statement
    cout << Inline << " Inline maths Equation found!!" << endl;
    cout << Display << " Display maths Equation found!!" << endl;
}