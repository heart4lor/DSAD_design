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

int main()
{
    freopen("in.txt", "r", stdin);
    while(true)
    {
        double num;
        char oper;
        while(scanf("%lf", &num) == 1)
        {
            if(scanf("%c", &oper) == 1)
            {
                cout << num << oper;
                if(oper == '=')
                {
                    // printf("end.");
                    SeqStack operands = setStack();
                    SeqStack operators = setStack();
                }
            }
        }
    }

    return 0;
}
