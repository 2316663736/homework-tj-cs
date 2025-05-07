#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>

using namespace std;

typedef char  ELEMTYPE[63];

struct  tree {
	ELEMTYPE the_num = { 0 };
	tree* lchild = NULL;
	tree* rchild = NULL;
};

char input_fro[63] = { 0 };
int now_top_input_fro = 0;
int now_tree_num = 1;


int string_search(const char *str ,const char ch)
{
	int max_len = strlen(str);
	for (int i = 0; i < max_len; i++)
		if (str[i] == ch)
			return i;
	return -1;
}

int divide(tree* now_divide_tree,tree* all_tree)
{
	if (strlen(now_divide_tree->the_num) == 1) {
		if (now_divide_tree->the_num[0] == input_fro[now_top_input_fro++])
			return 0;
		else
			return -1;
	}
	else {

		int the_place = string_search(now_divide_tree->the_num, input_fro[now_top_input_fro++]);
		if (the_place == -1)
			return -1;
		if(the_place!=0){
			now_divide_tree->lchild = &all_tree[now_tree_num++];
			strncat(now_divide_tree->lchild->the_num, now_divide_tree->the_num, the_place);
			if(divide(now_divide_tree->lchild, all_tree)==-1)
				return -1;
		}
		if (the_place != (strlen(now_divide_tree->the_num) - 1)) {
			now_divide_tree->rchild = &all_tree[now_tree_num++];
			strncpy(now_divide_tree->rchild->the_num, &now_divide_tree->the_num[the_place+1], strlen(now_divide_tree->the_num)-1 - the_place);
			if (divide(now_divide_tree->rchild, all_tree) == -1)
				return -1;
		}
		now_divide_tree->the_num[0] = now_divide_tree->the_num[the_place];
		now_divide_tree->the_num[1] = '\0';
	}
	return 0;
}
void output_lat(tree* all_tree)
{
	tree** stack = new(nothrow) tree * [100];
	if (stack == NULL)
		return ;
	int top_stack = 0;
	//stack[top_stack++] = all_tree;

	tree* now_tree = all_tree;
	tree* tem_tree = NULL;

	do
	{
		while (now_tree&&now_tree!=tem_tree)
		{
			stack[top_stack++] = now_tree;
			now_tree = now_tree->lchild;
		}
		if (top_stack > 0) {
			now_tree = stack[--top_stack];
			if (now_tree->rchild&&now_tree->rchild!=tem_tree) {
				stack[top_stack++] = now_tree;
				now_tree = now_tree->rchild;
			}
			else {
				cout << now_tree->the_num;
				tem_tree = now_tree;
			}
		}
	}	while (top_stack);
}
int main()
{
	while (cin >> input_fro)
	{
		tree* all_tree = new tree[100];
		if (all_tree == NULL)
			return -1;
		cin >> all_tree->the_num;

		now_top_input_fro = 0;
		now_tree_num = 1;
		if (divide(all_tree, all_tree) == -1)
			cout << "Error" ;
		else
			output_lat(all_tree);
		cout << endl;
		
	}
}