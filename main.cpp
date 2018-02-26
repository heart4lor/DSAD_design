#include <bits/stdc++.h>
using namespace std;
const int MAXLEN = 100;

union Data
{
    double numbers;
    char operators;
};

struct SeqStack
{
    Data data[MAXLEN];
    int top;
};

SeqStack* setStack()
{
    SeqStack* s = (SeqStack*)malloc(sizeof(SeqStack));
    s->top = -1;
    return s;
}

bool isEmpty(SeqStack* s)
{
    return s->top == -1;
}

bool isFull(SeqStack* s)
{
    return s->top == MAXLEN-1;
}

Data getTop(SeqStack* s)
{
    if(!isFull(s) && !isEmpty(s))
        return s->data[s->top];
    else
        printf("Error: Stack full or empty\n");
}

void push(SeqStack* s, Data x)
{
    if(!isFull(s))
        s->data[++s->top] = x;
    else
        printf("Error: Stack is full\n");
}

void pop(SeqStack* s)
{
    if(!isEmpty(s))
        s->top--;
    else
        printf("Error: Stack is empty\n");
}

double calc(double a, char b, double c)
{
    switch(b)
    {
        case '+': return a+c;
        case '-': return a-c;
        case '*': return a*c;
        case '/': return a/c;
        case '%': return a%c;
    }
}

bool cmp(char opt1, char opt2) // opt1 < opt2
{
    switch(opt1)
    {
        case '+': return (opt2=='*' || opt2=='/' || opt2='%' || opt2=='(');
        case '-': return (opt2=='*' || opt2=='/' || opt2='%' || opt2=='(');
        case '*': return (opt2=='(');
        case '/': return (opt2=='(');
        case '%': return (opt2=='(');
    }
}

bool isNumber(char x)
{
    return x>='0' && x<='9';
}

int main()
{
    freopen("in.txt", "r", stdin);
    while(true)
    {
        double sum = 0;
        double num;
        char oper;
        char in;
        int brackets = 0;
        SeqStack operands = setStack();
        SeqStack operators = setStack();
        while(scanf("%c", &in) == 1)
        {
            if(in == '=')
                break;
            if(isNumber(in))
                push(operators, in-'0');
            else
            {
                if(isEmpty(operands))
                    push(operands, in);
                else
                {
                    char 
                }
            }
        }
    }

    return 0;
}
