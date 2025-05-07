#include<iostream>
#include<string>

using namespace std;
typedef char ELEMTYPE;

struct  tree{
	ELEMTYPE the_num=0;
	tree* lchild=NULL;
	tree* rchild=NULL;
};

int input_tree(tree* &the_tree, int& num_left)
{
	if (num_left == 0)
		return 0;
	string input_;
	cin >> input_;
	if (input_ == "push")
	{
		the_tree = new tree;
		if (the_tree == NULL)
			return OVERFLOW;
		cin >> the_tree->the_num;
		num_left--;
		input_tree(the_tree->lchild, num_left);
		input_tree(the_tree->rchild, num_left);
	}
	else
		the_tree = NULL;

	return 0;
}
int output(tree* &the_tree, tree* stack[], int& top_stack)
{
	if (the_tree == NULL)
		return OVERFLOW;

	tree* tem_p = NULL;
	do
	{
		while (the_tree&&the_tree != tem_p )//&& the_tree->lchild!=tem_p)
		{			
			stack[top_stack++] = the_tree;
			the_tree = the_tree->lchild;
		}
		if(top_stack>0)
		{
			the_tree = stack[--top_stack];
			if (the_tree->rchild != NULL && the_tree != tem_p && the_tree->rchild != tem_p)
			{	
				stack[top_stack++] = the_tree;
				the_tree = the_tree->rchild;			
			}
			else
			{
				putchar(the_tree->the_num);
				tem_p = the_tree;
			}
		}
	}while (top_stack > 0);

	return 0;
}
int main()
{
	int max_num = 0;
	tree* the_tree_first=NULL;
	tree* stack[1000] = { NULL };
	int top_stack = 0;
	cin >> max_num;
	input_tree(the_tree_first, max_num);

	output(the_tree_first, stack, top_stack);
	
	return 0;
}






