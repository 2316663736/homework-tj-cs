#include<iostream>
#include<string.h>
#include<math.h>
#include <iomanip>

using namespace std;
typedef char  ELEMTYPE;

struct  tree {
	ELEMTYPE the_num = 0;
    tree* father = NULL;
    tree* lchild = NULL;
	tree* rchild = NULL;

	int the_x = 0;//输出所在位置的横坐标
};
char stack_oper[100] = { 0 }, stack_num[100] = { 0 };
int top_stack_oper = 0, top_stack_num = 0;

int now_tree_num = 0;


//把一个char型数据转化到int型
//如果计算消耗掉了，就把ch变为'\0'

class ch_to_int_real {
public:
    int char_int(char input)
    {        
        for (int tem = 0; tem<the_num; tem++)
            if (tran[tem].ch == input){
                int tem_return = tran[tem].i;
                for (; tem < the_num; tem++)
                    tran[tem] = tran[tem + 1];
                the_num--;
                return tem_return;
            }
        return -999;
    }

    void in_char_int(char in_ch, int in_i)
    {
        tran[the_num].ch = in_ch;
        tran[the_num].i = in_i;
        the_num++;
    }
private:
    struct ch_int {
        char ch = 0;
        int i = 0;
    };
    ch_int tran[100];
    int the_num = 0;
} char_to_int;
class char__tree {
public:
    tree* char_tree(char in)
    {
        for (int tem = 0; tem < the_num; tem++)
            if (tran[tem].ch == in) {
                tree* tem_return = tran[tem].tr;
                for (; tem < the_num; tem++)
                    tran[tem] = tran[tem + 1];
                the_num--;
                return tem_return;
            }
        return NULL;
    }

    void in_tree_ch(tree* t, char c)
    {
        tran[the_num].ch = c;
        tran[the_num].tr = t;
        the_num++;
    }
private:
    struct tree_int {
        tree* tr = NULL;
        char ch = 0;
    } tran[100];

    int the_num = 0;
}char_to_tree;


 /*规定各个符号优先级
+  - ：2
/  * ：3
 （  ：入栈前4，入栈后1
  ） ：0
*/
int get_new_pri()
{
    for (int tem_top = top_stack_oper; tem_top > 0; --tem_top)
    {
        switch (stack_oper[tem_top - 1])
        {
            case ')':
                return 0;
                break;
            case '(':
                return 1;
                break;
            case '+':
            case'-':
                return 2;
                break;
            case '*':
            case '/':
                return 3;
                break;
        }  
    }
    return 0;
}

bool push_stack(char in,int &pri)
{
    switch(in)
    {
        case ')':
            //先对栈顶可能存在的左括号进行特判
            if (stack_oper[top_stack_oper - 1] == '(')
            {
                top_stack_oper--;
                pri = get_new_pri();
            }
            else
                return false;
            break;
        case '(':
            stack_oper[top_stack_oper++] = in;
            pri=1;
            break;
        case '+':
        case '-':
            if (pri >= 2)
                return false;
            stack_oper[top_stack_oper++] = in;
            pri= 2;
            break;
        case '*':
        case '/':
            if (pri >= 3)
                return false;
            stack_oper[top_stack_oper++] = in;
            pri = 3;
            break;
        default:
            stack_num[top_stack_num++] = in;
    }
    return true;
}
void pop_stack(int& pri ,tree* all_tree)
{

    //剩下都是双目运算符，一定需要两个变量和一个符号
    char tem_out_num1 = 0, tem_out_num2 = 0, tem_out_oper = 0;
    int num_1, num_2, result;
    tree* the_now_tree_input = NULL;
    tem_out_num1 = stack_num[--top_stack_num];
    num_1 = char_to_int.char_int(tem_out_num1);
    tem_out_num2 = stack_num[--top_stack_num];
    num_2 = char_to_int.char_int(tem_out_num2);
    tem_out_oper = stack_oper[--top_stack_oper];
    if (tem_out_num1 == 'h' || tem_out_num2 == 'h')
    {
        int te;
        te = 1;
    }

    the_now_tree_input = char_to_tree.char_tree(tem_out_num1);
    if (the_now_tree_input == NULL) {
        the_now_tree_input = &all_tree[now_tree_num++];
        the_now_tree_input->the_num = tem_out_num1;
    }

    the_now_tree_input->father = &all_tree[now_tree_num++];
    the_now_tree_input->father->the_num = tem_out_oper;
    the_now_tree_input->father->rchild = the_now_tree_input;
    
    the_now_tree_input->father->lchild = char_to_tree.char_tree(tem_out_num2);
    if (the_now_tree_input->father->lchild == NULL) {
        the_now_tree_input->father->lchild = &all_tree[now_tree_num++];
        the_now_tree_input->father->lchild->the_num = tem_out_num2;
    }
    the_now_tree_input->father->lchild->father = the_now_tree_input->father;
  

    switch (tem_out_oper)
    {
        case '+':
            result = num_2 + num_1;
            break;
        case '-':
            result = num_2 - num_1;
            break;
        case '*':
            result = num_2 * num_1;
            break;
        case'/':
            result = num_2 / num_1;
            break;
        default:
            while (1)
                cout << "错误";
            break;
    }
    char_to_int.in_char_int(tem_out_num1, result);
    char_to_tree.in_tree_ch(the_now_tree_input->father, tem_out_num1);
    stack_num[top_stack_num++] = tem_out_num1;
    pri = get_new_pri();
}


void output_lat(tree* all_tree)
{
    tree** stack = new(nothrow) tree * [100];
    if (stack == NULL)
        return;
    int top_stack = 0;
    
    tree* now_tree = all_tree;
    tree* tem_tree = NULL;

    do
    {
        while (now_tree && now_tree != tem_tree)
        {
            stack[top_stack++] = now_tree;
            now_tree = now_tree->lchild;
        }
        if (top_stack > 0) {
            now_tree = stack[--top_stack];
            if (now_tree->rchild && now_tree->rchild != tem_tree) {
                stack[top_stack++] = now_tree;
                now_tree = now_tree->rchild;
            }
            else {
                cout << now_tree->the_num;
                tem_tree = now_tree;
            }
        }
    } while (top_stack);
    cout << endl;
}

tree* get_root_and_high(tree* all_tree ,int& high)
{
    tree* root = all_tree;
    while (root->father)
        root = root->father;

    tree** queue = new(nothrow) tree * [100];
    if (queue == NULL)
        return NULL;
    int start = 0, end = 0;
    queue[end++] = root;

    high = -1;

    while (start != end)
    {
        high++;
        int tem_queue_num = end - start;

        for (int i_cycle = 0; i_cycle < tem_queue_num; i_cycle++)
        {
            tree* now_tree = queue[start++];

            if (now_tree->lchild)
                queue[end++] = now_tree->lchild;

            if (now_tree->rchild)
                queue[end++] = now_tree->rchild;
        }
    }
    delete[]queue;
    return root;
}
void out_tree(tree* root,const int high)
{
    int tem_high = high+1;
    tree** queue = new(nothrow) tree * [100];
    if (queue == NULL)
        return;
    int start = 0, end = 0;
    queue[end++] = root;
    root->the_x = static_cast<int> (pow(2, high));
    while (start != end)
    {
        tem_high--;
        int tem_queue_num = end - start;
         
        int num_of_have_space=0;
        for (int i_cycle = 0; i_cycle < tem_queue_num; i_cycle++)
        {
            tree* now_tree = queue[start+i_cycle];
            if (now_tree->father) {
                if (now_tree->father->lchild == now_tree) {
                    now_tree->the_x = now_tree->father->the_x - static_cast<int>(pow(2, tem_high));
                }
                else {
                    now_tree->the_x = now_tree->father->the_x + static_cast<int>(pow(2, tem_high));
                }
            }
            cout << setw(now_tree->the_x - num_of_have_space) << now_tree->the_num;
            num_of_have_space = now_tree->the_x;             
        }
        cout <<endl;
        num_of_have_space = 0;
        for (int i_cycle = 0; i_cycle < tem_queue_num; i_cycle++)
        {
            tree* now_tree = queue[start++];

            if (now_tree->lchild) {
                queue[end++] = now_tree->lchild;
                cout << setw(now_tree->the_x - num_of_have_space-1) << "/";
                num_of_have_space = now_tree->the_x - 1;
            }

            if (now_tree->rchild) {
                queue[end++] = now_tree->rchild;
                cout << setw(now_tree->the_x - num_of_have_space + 1) << "\\";
                num_of_have_space = now_tree->the_x + 1;
            }
        }
        if (tem_high != 0)
            cout << endl;
    }
}
int main()
{
    tree* all_tree = new tree[100];
    string input;
    int tem_input_char_int_num;
    cin >> input>>tem_input_char_int_num;

    for(int tem_IIIII=0;tem_IIIII<tem_input_char_int_num;tem_IIIII++)
    {
        char in_ch;
        int in_i;
        cin >> in_ch >> in_i;
        char_to_int.in_char_int(in_ch, in_i);
    }

    int pri = 0;

    for (int tem_iiiii = 0; input[tem_iiiii]; tem_iiiii++)
    {
        while (!push_stack(input[tem_iiiii], pri))
            pop_stack(pri, all_tree);
    }
    while (top_stack_oper > 0)
        pop_stack(pri,  all_tree);

    int high = 0;
    tree* root = get_root_and_high(all_tree, high);

    output_lat(root);

    out_tree(root, high);

    cout << char_to_int.char_int(stack_num[top_stack_num]);

    return 0;
}


















