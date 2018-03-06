# 数据结构课程设计报告

*author: syf* ![build status](https://travis-ci.org/heart4lor/DSAD_design.svg?branch=master)

## 题目：**算术表达式的求解**

问题描述：给定一个算术表达式，通过程序求出最后的结果。

## 一、问题分析和任务定义

### 1.1 问题分析

**这个问题有以下基本要求：**

1. 从键盘输入要求解的算术表达式；
2. 采用栈结构进行算术表达式的求解过程；
3. 能够判断算术表达式正确与否；
4. 对于错误表达式给出提示；
5. 对于正确的表达式给出最后的结果；

### 1.2 任务

本任务要求实现一个计算器，能对输入的表达式求值。应考虑到表达式是否包含小数，是否包含括号，是否包含多层括号等等问题。最终呈现的应该是一个命令行的计算器，用户输入表达式后可以返回一个结果。

## 二、数据结构的选择和概要设计

### 2.1 数据结构

考虑到表达式中运算符的优先级，本任务选择顺序栈作为存储数据的结构，程序分为数字栈和运算符栈。

### 2.2 概要设计

顺序栈部分使用 c++ 的模板编程，因为数字栈和运算符栈中存储的类型是不同的，如果为其开两个结构体，写两份 push/pop 函数，代码就显得十分冗长，实现起来也不够优雅。所以使用模板编程，为数字栈和运算符栈指定不同的类型。程序运行时进入一个死循环，然后进入另一个循环持续读取用户输入的字符，如果是数字就继续读入，处理成整数或小数；如果是运算符的话就把之前的数字存入数字栈，并和运算符栈的栈顶运算符比较优先级，如果栈顶元素优先的话就取出该运算符和数字栈里的两个数字做运算，并把结果存入数字栈，否则直接将运算符入栈。如果处理到“=”字符，说明表达式结束，就将栈内没有运算的元素取出运算，直到运算符栈空，数字栈中仅有一个元素为止，这个元素就是用户输入的表达式的答案。

本程序可能涉及如下几个运算符：  
`+， -， *， /， %， (, ), =`  

其中优先级最高的是 `(` 括号运算符，因为遇见括号意味着括号里的先算。其次是 `*, /, %` 运算符，在之后是 `+, -` 运算符，优先级最低的是 `=` 运算符。

## 三、详细设计和编码

### 3.1 数据结构

顺序栈结构体：
```cpp
template <typename T>
struct SeqStack
{
	T data[MAXLEN];
	int top;
};
```
T 表示数据类型，因为本任务栈中需要存储 double 和 char 两种类型的数据，写两份结构体和函数显得代码很冗长，很不优雅，所以使用 template，实现对多种数据类型的支持。MAXLEN 常量限制顺序栈的容量。top 成员表示栈顶。

### 3.2 数据结构相关函数

初始化栈：
```cpp
template <typename T>
SeqStack<T>* setStack()
{
	SeqStack<T>* s = (SeqStack<T>*)malloc(sizeof(SeqStack<T>));
	s->top = -1;
	return s;
}
```
初始化栈的过程：申请一段内存，把 top 赋值为初始值 -1。

判断栈是否为空：
```cpp
template <typename T>
bool isEmpty(SeqStack<T>* s)
{
	return s->top == -1;
}
```

判断栈是否已满：
```cpp
template <typename T>
bool isFull(SeqStack<T>* s)
{
	return s->top == MAXLEN-1;
}
```

获取栈顶元素：
```cpp
template <typename T>
T getTop(SeqStack<T>* s)
{
	if(!isFull(s) && !isEmpty(s))
		return s->data[s->top];
	else
		printf("Error: Stack full or empty\n");
}
```
获取元素前先判断栈是否满或空。

获取栈内元素的个数：
```cpp
template <typename T>
T getSize(SeqStack<T>* s)
{
	return s->top+1;
}
```
元素个数为 top+1。

入栈：
```cpp
template <typename T>
void push(SeqStack<T>* s, T x)
{
	if(!isFull(s))
		s->data[++s->top] = x;
	else
		printf("Error: Stack is full\n");
}
```
入栈前判断栈是否已满。

出栈：
```cpp
template <typename T>
void pop(SeqStack<T>* s)
{
	if(!isEmpty(s))
		s->top--;
	else
		printf("Error: Stack is empty\n");
}
```
出栈前判断栈是否为空。

### 3.3 其他函数

计算函数：
```cpp
double calc(double a, char b, double c)
{
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
```
传入两个 double 类型和一个 char 类型变量，计算简单表达式的值。

错误提示：
```cpp
void err()
{
	char errinfo[10][1024] = {
		"",
		"you can not divide 0",
		"mod is only allowed between integers"
	};
	printf("\nerror: %s\n", errinfo[errid]);
	errid = 0;
}
```
存储并输出错误信息。

比较两运算符优先级：
```cpp
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
```

判断字符是否为数字
```cpp
bool isNumber(char x)
{
	return x>='0' && x<='9';
}
```
### 3.4 主函数逻辑

程序运行时进入一个死循环，然后进入另一个循环持续读取用户输入的字符，如果是数字就继续读入，处理成整数或小数；如果是运算符的话就把之前的数字存入数字栈，并和运算符栈的栈顶运算符比较优先级，如果栈顶元素优先的话就取出该运算符和数字栈里的两个数字做运算，并把结果存入数字栈，否则直接将运算符入栈。如果处理到“=”字符，说明表达式结束，就将栈内没有运算的元素取出运算，直到运算符栈空，数字栈中仅有一个元素为止，这个元素就是用户输入的表达式的答案。


## 四、上机调试过程

看到这个任务时我想实现一个完全可用的计算器，即支持四则运算、求余、括号，并支持浮点计算。实现时还是有一些坑点的。

### 值得注意的问题及解决办法

#### 4.1 括号和运算符的输入
##### 问题描述
用户可能会输入这样的式子：`2*(3+4）=`  
这里的 `*(` 是两个连在一起的运算符，所以不能认为输入是 `%d%c%d%c` 这样的格式。
##### 解决办法
一律按 `%c` 逐位读取输入字符，如果当前是数字字符，就将其加到 `num` 变量中；如果当前是运算符，就把 `num`，即上一个数字存入数字栈，并将 `num` 重置为0，当前字符存入运算符栈。

#### 4.2 浮点数的输入
##### 问题描述
浮点数输入的格式是这样的：`1.1+2.2=`
##### 解决办法
设置一个 bool 类型变量 `isDouble`，遇到 `.` 字符就将其设为 true，后面读入的数字按照小数处理和前面相加即可。

#### 4.3 结束时的处理
##### 问题描述
需求应该是，读取到用户输入 `=` 字符时结束本次运算。
##### 解决办法
具体实现时有个坑点，结束时栈里可能还有一部分表达式没有被运算，需要加一个 while 循环继续计算，直到数字栈中只有一个数（即答案），运算符栈中没有元素为止。

## 五、测试结果及其分析

### 5.1 终端输出

```bash
[sunyongfei@sunyongfei-manjaro DSAD_design]$ g++ main.cpp -o main
[sunyongfei@sunyongfei-manjaro DSAD_design]$ ./main
1+1=
2
2*(3+4)=
14
1.1/(2.2-3.3)=
-1
666%555-4=
107
3.14*((2.85+87.2)/1.717)=
164.681
```

### 5.2 结果分析
经过测试，此程序工作正常，目前没有发现 bug。

## 六、用户使用说明
本程序包含一个可执行文件，执行后屏幕上不会有任何提示，请输入您要计算的表达式，并以 `=` 号结束，按下回车程序将在下一行显示本条表达式结果。表达式中可以包含整数、浮点数、四则运算、多重括号和取余符号。

## 七、参考文献

[1]: 网昆仑,李红. 数据结构与算法. 北京：中国铁道出版社,2006年5月


## 八、附录

https://github.com/heart4lor/DSAD_design
  
源码：
```cpp
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
	if(!isFull(s))
		s->data[++s->top] = x;
	else
		printf("Error: Stack is full\n");
}

template <typename T>
void pop(SeqStack<T>* s)
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
	printf("\nerror: %s\n", errinfo[errid]);
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
		while(scanf("%c", &in) == 1 && !end)
		{
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
				if(sum != 0)
					push<double>(numbers, (double)num1+num2);
				num1 = 0;
				num2 = 0;
				cnt = 0;
				isDouble = 0;
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
```