#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 100;
int errid = 0;

template <typename T>
struct SeqStack
{
	T data[MAXLEN];
	int top;
};

template <typename T>
SeqStack<T>* setStack()
{
	SeqStack<T>* s = (SeqStack<T>*)malloc(sizeof(SeqStack<T>));
	s->top = -1;
	return s;
}

template <typename T>
bool isEmpty(SeqStack<T>* s)
{
	return s->top == -1;
}

template <typename T>
bool isFull(SeqStack<T>* s)
{
	return s->top == MAXLEN-1;
}

template <typename T>
T getTop(SeqStack<T>* s)
{
	if(!isFull(s) && !isEmpty(s))
		return s->data[s->top];
	else
		printf("Error: Stack full or empty\n");
}

template <typename T>
T getSize(SeqStack<T>* s)
{
	return s->top+1;
}

template <typename T>
void push(SeqStack<T>* s, T x)
{
//	cout << "pushed " << x << endl;
	if(!isFull(s))
		s->data[++s->top] = x;
	else
		printf("Error: Stack is full\n");
}

template <typename T>
void pop(SeqStack<T>* s)
{
//	cout << "poped " << getTop(s) << endl;
	if(!isEmpty(s))
		s->top--;
	else
		printf("Error: Stack is empty\n");
}

double calc(double a, char b, double c)
{
//	cout << "caled " << a << b << c << endl;
	switch(b)
	{
		case '+': return a+c;
		case '-': return a-c;
		case '*': return a*c;
		case '/':
		{
			if(c == 0)
			{
				errid = 1;
				return 0;
			}
			else
				return a/c;
		}
		case '%':
		{
			if(a==(int)a && c==(int)c)
				return (int)a%(int)c;
			else
			{
				errid = 2;
				return 0;
			}
		}
	}
}

void err()
{
	char errinfo[10][1024] = {
		"",
		"you can not divide 0",
		"mod is only allowed between integers"
	};
	printf("error: %s\n\n", errinfo[errid]);
	errid = 0;
}

bool cmp(char opt1, char opt2) // opt1 < opt2
{
	switch(opt1)
	{
		case '+': return (opt2=='*' || opt2=='/' || opt2=='%' || opt2=='(');
		case '-': return (opt2=='*' || opt2=='/' || opt2=='%' || opt2=='(');
		case '*': return (opt2=='(');
		case '/': return (opt2=='(');
		case '%': return (opt2=='(');
		case '=': return 0;
	}
}

bool isNumber(char x)
{
	return x>='0' && x<='9';
}

int main()
{
//	freopen("in.txt", "r", stdin);
	while(true)
	{
		int num1 = 0;
		double num2 = 0;
		int cnt = 0;
		bool isDouble = 0;
		char in;
		SeqStack<double>* numbers = setStack<double>();
		SeqStack<char>* operators = setStack<char>();
		bool end = 0;
		bool isZero = 0;
		while(scanf("%c", &in) == 1 && !end)
		{
			if(in == '0')
				isZero = 1;
			if(in == '=')
			{
				while(getSize(numbers)!=1 && getSize(operators)!=0)
				{
					double c = getTop(numbers);
					pop<double>(numbers);
					char b = getTop(operators);
					while(b == '(' || b == ')')
					{
						pop<char>(operators);
						b = getTop(operators);
					}
					pop<char>(operators);
					double a = getTop(numbers);
					pop<double>(numbers);
					double result = calc(a, b, c);
					if(!errid)
						push<double>(numbers, result);
					else
						break;
				}
				end = 1;
			}
			if(isNumber(in))
			{
				if(!isDouble)
				{
					num1 *= 10;
					num1 += in-'0';
				}
				else	
				{
					cnt++;
					num2 += 1.0*(in-'0')/(pow(10,cnt));
				}
			}
			else if(in == '.')
				isDouble = 1;
			else
			{
				double sum = (double)num1 + num2;
				if(sum || isZero)
					push<double>(numbers, (double)num1+num2);
				num1 = 0;
				num2 = 0;
				cnt = 0;
				isDouble = 0;
				isZero = 0;
				if(isEmpty(operators) && in!='(' && in!=')')
					push<char>(operators, in);
				else if(cmp(getTop(operators), in))
					push<char>(operators, in);
				else
				{
					double c = getTop(numbers);
					pop<double>(numbers);
					char b = getTop(operators);
					while(b == '(' || b == ')')
					{
						pop<char>(operators);
						b = getTop(operators);
					}
					pop<char>(operators);
					double a = getTop(numbers);
					pop<double>(numbers);
					double result = calc(a, b, c);
					if(in!='=' && in!='(' && in!=')')
						push(operators, in);
					if(!errid)
						push<double>(numbers, result);
					else
						break;
				}
			}
		}
		if(errid)
			err();
		else
			cout << getTop(numbers) << endl;
	}

	return 0;
}
