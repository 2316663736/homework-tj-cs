#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;
typedef char ELEMTYPE;

struct  tree {
	ELEMTYPE the_num = 0;
	unsigned short high = 1;//深度
	tree* father = NULL;
	tree* lchild = NULL;
	tree* rchild = NULL;
	tree* brother = NULL;

};

tree * cin_and_generate_tree(tree* start, int the_num)
{
	char left[50];
	char right[50];
	int le, ri;

	for (int i = 0; i < the_num; i++)
	{
		cin >> start[i].the_num >> left >> right;
	
		le = atoi(left);
		ri = atoi(right);
		if (left[0] == '-')
			start[i].lchild = NULL;
		else
		{
			start[le].father = &start[i];
			start[le].brother = (ri == 0) ? NULL : &start[ri];
			start[i].lchild = &start[le];
		}
		if (right[0] == '-')
			start[i].rchild = NULL;
		else
		{
			start[ri].father = &start[i];
			start[ri].brother = (le == 0) ? NULL : &start[le];
			start[i].rchild = &start[ri];
		}
	}
	int max_high = 0;
	tree* the_root = start;
	while (the_root->father != NULL)
		the_root = the_root->father;
	the_root->high = 1;


	return the_root;
}
void the_high(tree* the_root, int& max_high)
{
	if (the_root->lchild != NULL)
	{
		the_root->lchild->high = the_root->high + 1;
		max_high = max(max_high, int(the_root->lchild->high));
		the_high(the_root->lchild, max_high);
	}
	if (the_root->rchild != NULL)
	{
		the_root->rchild->high = the_root->high + 1;
		max_high = max(max_high, int(the_root->rchild->high));
		the_high(the_root->rchild, max_high);
	}

}
//stack中存放左右孩子值相同的节点
//flag用来标记，默认为0，如果为1则是进行交换元素后的判断
int cmp(tree* first_tree, tree* second_tree, tree *(*the_same_stack)[2], int& top_stack,int flag = 0)
{
	if (first_tree == NULL && second_tree == NULL)
		return 0;
	else if (first_tree == NULL || second_tree == NULL)
		return -1;
	else if (first_tree->the_num != second_tree->the_num)
		return -1;

	int goto_the_lab = 0;

	if (first_tree->lchild == NULL && second_tree->lchild == NULL) {
		if (first_tree->rchild == NULL && second_tree->rchild == NULL) {
			return 0;
		}
		else if (first_tree->rchild == NULL || second_tree->rchild == NULL) {
			goto_the_lab = 1;
		}
		else if (first_tree->rchild->the_num == second_tree->rchild->the_num){
			if (cmp(first_tree->rchild, second_tree->rchild, the_same_stack, top_stack) == -1)
				return -1;
		}
		else {
			goto_the_lab = 1;
		}
	}
	else if (first_tree->lchild == NULL || second_tree->lchild == NULL) {
		goto_the_lab = 1;
	}
	else if (first_tree->lchild->the_num == second_tree->lchild->the_num) {
		if (first_tree->rchild == NULL && second_tree->rchild == NULL) {
			if (cmp(first_tree->lchild, second_tree->lchild, the_same_stack, top_stack) == -1)
				return -1;
		}
		else if (first_tree->rchild == NULL || second_tree->rchild == NULL) {
			goto_the_lab = 1;
		}
		else if (first_tree->rchild->the_num == second_tree->rchild->the_num) {
			//左右孩子元素相同，这里可能要交换，可能不要，所以把它入栈
//这里暂时直接入栈，是否判断孙节点后面再看
			if (first_tree->lchild->the_num == first_tree->rchild->the_num && flag != 1)
			{
				the_same_stack[top_stack][0] = first_tree;
				the_same_stack[top_stack][1] = second_tree;
				top_stack++;
			}
			if (cmp(first_tree->lchild, second_tree->lchild, the_same_stack, top_stack) == -1)
				return -1;
			if (cmp(first_tree->rchild, second_tree->rchild, the_same_stack, top_stack) == -1)
				return -1;
		}
		else {
			goto_the_lab = 1;
		}
	}
	else {
		goto_the_lab = 1;
	}



	if (goto_the_lab == 1)
	{
		if (flag == 1)
			return -1;
		tree* tem = first_tree->lchild;
		first_tree->lchild = first_tree->rchild;
		first_tree->rchild = tem;
		if (cmp(first_tree, second_tree, the_same_stack, top_stack, 1) == -1)
		{
			if (top_stack > 0)
			{
				--top_stack;
				first_tree = the_same_stack[top_stack][0];
				tree* tem = first_tree->lchild;
				first_tree->lchild = first_tree->rchild;
				first_tree->rchild = tem;
				second_tree = the_same_stack[top_stack][1];
				if (cmp(first_tree, second_tree, the_same_stack, top_stack, 1) == -1)
					return -1;
			}
			else
				return -1;
		}
	}
	return 0;
}

int main()
{
	int tree_num_1, tree_num_2;
	int high_1=0, high_2=0;
	tree* root_1, * root_2;


	cin >> tree_num_1;
	tree* the_first_tree = new(nothrow) tree[tree_num_1 + 1];
	if (the_first_tree == NULL)
		return OVERFLOW;
	root_1 = cin_and_generate_tree(the_first_tree, tree_num_1);
	the_high(root_1, high_1);

	cin >> tree_num_2;

	tree* the_second_tree = new(nothrow) tree[tree_num_2 + 1];
	if (the_second_tree == NULL)
		return OVERFLOW;
	root_2 = cin_and_generate_tree(the_second_tree, tree_num_2);
	the_high(root_2, high_2);

	if (tree_num_1 != tree_num_2||high_1!=high_2)
		cout << "No" << endl << high_1 << endl << high_2 << endl;
	else 
	{

		tree* (*the_same_stack)[2];
		int top_stack = 0;
		the_same_stack = new(nothrow) tree*[(tree_num_1) / 2][2];

		if (the_same_stack == NULL )
			return -1;

		if (cmp(root_1, root_2, the_same_stack, top_stack)==-1)		
			cout << "No" << endl << high_1 << endl << high_2 << endl;
		else 
			cout << "Yes" << endl << high_1 << endl << high_2 << endl;
		delete[] the_same_stack;
	}
	delete[]the_first_tree;
	delete[]the_second_tree;
	return 0;
}

