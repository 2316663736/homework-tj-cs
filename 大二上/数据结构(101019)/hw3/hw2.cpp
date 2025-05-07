#include<iostream>
using namespace std;

int get_new_pri(char* operator_bool_stack, int top_operator_stack)
{
	for (int tem_top = top_operator_stack; tem_top > 0; --tem_top)
	{
		if (operator_bool_stack[tem_top - 1] != 'F' && operator_bool_stack[tem_top - 1] != 'V')
		{
			switch (operator_bool_stack[tem_top - 1])
			{
				case '!':
					return 4;
					break;
				case '&':
					return 3;
					break;
				case '|':
					return 2;
					break;
				case '(':
					return 1;
					break;
			}
		}
	}
	return 0;
}
/*返回值为1代表成功入栈，可继续读入，反之则入栈失败，其中元素需要出栈进行运算*/
bool into_the_stack(char input, char* operator_bool_stack, int& top_operator_stack, bool &bool_or_not,int & pri_of_operate)
{
	if (input == 'F' || input == 'V')
	{
		operator_bool_stack[top_operator_stack++] = input;
		bool_or_not = true;
	}
	else
	{
		switch (input)
		{
			case '!'://这个一定是能入栈的，即使前面是！或者（
				operator_bool_stack[top_operator_stack++] = input;
				pri_of_operate = 4;
				bool_or_not = false;
				break;
			case '('://一定能入栈
				operator_bool_stack[top_operator_stack++] = input;
				pri_of_operate = 1;
				bool_or_not = false;
				break;
			case '&':
				if (pri_of_operate >= 3)
				  	return false;
				operator_bool_stack[top_operator_stack++] = input;
				pri_of_operate = 3;
				bool_or_not = false;
				break;
			case '|':
				if (pri_of_operate >= 2)
					return false;
				operator_bool_stack[top_operator_stack++] = input;
				pri_of_operate = 2;
				bool_or_not = false;
				break;
			case ')':
				if (operator_bool_stack[top_operator_stack - 1] == '(')
				{
					operator_bool_stack[--top_operator_stack] = '\0';
					bool_or_not = false;
					pri_of_operate = get_new_pri(operator_bool_stack, top_operator_stack);
				}
				else if ((operator_bool_stack[top_operator_stack - 1] == 'F' || operator_bool_stack[top_operator_stack - 1] == 'V')&&top_operator_stack >= 2 && operator_bool_stack[top_operator_stack - 2] == '(')
				{
					operator_bool_stack[top_operator_stack-2] = operator_bool_stack[top_operator_stack-1];
					top_operator_stack--;
					bool_or_not = true;
					pri_of_operate = get_new_pri(operator_bool_stack, top_operator_stack);
				}
				else 
					return false;
				//如果是右括号，则左右括号结合，消去

				break;
		}

	}
	return true;
}

void out_the_stack(char* operator_bool_stack, int& top_operator_stack, bool& bool_or_not, int& pri_of_operate)
{
	char tem_operator, tem_bool_1, tem_bool_2;
	bool tem_1, tem_2,result=0;
	tem_bool_1 = operator_bool_stack[--top_operator_stack];
	if (tem_bool_1 == 'F')
		tem_1 = false;
	else
		tem_1 = true;
	tem_operator = operator_bool_stack[--top_operator_stack];
	if (tem_operator == '!')
	{
		result = !tem_1;
	}
	else if (tem_operator == '&')
	{
		tem_bool_2 = operator_bool_stack[--top_operator_stack];
		if (tem_bool_2 == 'F')
			tem_2 = false;
		else
			tem_2 = true;
		result = tem_1 && tem_2;
	}
	else if (tem_operator == '|')
	{
		tem_bool_2 = operator_bool_stack[--top_operator_stack];
		if (tem_bool_2 == 'F')
			tem_2 = false;
		else
			tem_2 = true;
		result = tem_1 || tem_2;
	}
	else {//理论上来说不可能是其他的，括号排除了，F/V/！不可能，如果为其他值则代表程序错误
		cout << "错误";
		getchar();
	}
	char the_in;
	if (result)
		the_in = 'V';
	else
		the_in = 'F';
	operator_bool_stack[top_operator_stack++] = the_in;
	bool_or_not = true;
	pri_of_operate = get_new_pri(operator_bool_stack, top_operator_stack);

}

int main()
{
	int expression_no = 0;
	char operator_bool_stack[200] = { 0 };      //认为运算符和F/V最多有100个
	bool bool_or_not = false;                 //记录前一个是不是F/V,如果这个为true，且后面为F/V/(/!，则代表本行结束，可以输出expression
	int top_operator_stack = 0;           //指向栈的栈顶的下一个元素
	int pri_of_operator = 0;                //运算符栈的栈顶元素优先级，这里进行简化
	//'('入栈前优先级为5，入栈后为1,'('优先级为0，一定要和左括号结合才行，无法入栈，'!'优先级为4,'&'优先级为3,'|'优先级为2

	char tem_input;                   //临时储存读入的字符

	while (1)
	{
		if (cin >> tem_input)
		{
			if (bool_or_not && (tem_input == 'F' || tem_input == 'V'||tem_input=='!'||tem_input=='('))
			{
				//本行结束，全部进行计算
				while(top_operator_stack>1)
					out_the_stack(operator_bool_stack, top_operator_stack, bool_or_not, pri_of_operator);
			}
			else
			{
				while (!into_the_stack(tem_input, operator_bool_stack, top_operator_stack, bool_or_not, pri_of_operator))
				{
					out_the_stack(operator_bool_stack, top_operator_stack, bool_or_not, pri_of_operator);
				}
				continue;

			}
		}
		else //输入为EOF，退出循环
			break;

		cout << "Expression " << ++expression_no << ": " << operator_bool_stack[--top_operator_stack] << endl;
		into_the_stack(tem_input, operator_bool_stack, top_operator_stack, bool_or_not, pri_of_operator);
	}
	//退出循环后，进行计算，并输出结果
	while (top_operator_stack > 1)
		out_the_stack(operator_bool_stack, top_operator_stack, bool_or_not, pri_of_operator);
	cout << "Expression " << ++expression_no << ": " << operator_bool_stack[--top_operator_stack] << endl;

	return 0;
}
