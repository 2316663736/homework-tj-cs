#include<iostream>
#include<string>
using namespace std;

int main()
{
	string the_input_stack = "", the_out_stack = "";
	cin >> the_input_stack;
	while (cin >> the_out_stack)
	{
		char* tem_stack = new(nothrow) char[the_input_stack.size()] {0};
		if (tem_stack == NULL)
			return -1;
		//this_input和this_output都是指向当前元素，top_tem_stack指向栈顶下一个
		int this_input = 0, this_output = 0, top_tem_stack = 0;
		bool yes_or_no = true;


		//列车没有全部从出口出去，或没有全部离开入口前不结束
		while (the_input_stack[this_input] && the_out_stack[this_output])
		{//前面那个判断条件防止越界
			if (the_input_stack[this_input] == the_out_stack[this_output])
			{
				this_output++;
				this_input++;
			}
			else if (top_tem_stack - 1 >= 0 && tem_stack[top_tem_stack - 1] == the_out_stack[this_output])
			{
				tem_stack[top_tem_stack - 1] = '\0';//去除栈顶元素
				this_output++;
				top_tem_stack--;
			}
			else
			{
				tem_stack [top_tem_stack] = the_input_stack[this_input];
				//cout << tem_stack << endl;
				this_input++;
				top_tem_stack++;
			}
		}
		//可能存在部分车还在车站里，这里进行出站
		while (top_tem_stack - 1 >= 0 && tem_stack[top_tem_stack - 1] == the_out_stack[this_output])
		{
			tem_stack[top_tem_stack - 1] = '\0';//去除栈顶元素
			this_output++;
			top_tem_stack--;
		}
		if (this_input == this_output && top_tem_stack == 0)
			yes_or_no = true;
		else
			yes_or_no = false;
		if (yes_or_no)
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}


	return 0;
}


