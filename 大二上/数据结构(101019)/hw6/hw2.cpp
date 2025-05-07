#include<iostream>

using namespace std;

 struct  Node {
	int key;
	int count;
	Node* left;
	Node* right;
 
};

 class BST {
 private:
	 Node* root=nullptr;//空间由操作系统释放（不标准）
	 void  insert();
	 void delete_num();
	 void count_num();
	 void cout_min();
	 void cout_pri();
 public:
	 void dispose(const int n);
 };
 void BST::insert()
 {
	 int num;
	 cin >> num;
	 if (num == 10)
		 num = 10;
	 Node* now = root;
	 Node* p=nullptr;

	 while (1)
	 {
		 if (now == nullptr)
		 {
			 now = new(nothrow)  Node ;
			 if (!now)
				 exit(-1);
			 now->count = 1;
			 now->key = num;
			 now->left = nullptr;
			 now->right = nullptr;
			 if (!p)
				 root = now;
			 else if (p->key > num)
				 p->left = now;
			 else
				 p->right = now;
			 break;
		 }
		 else if (now->key == num)
		 {
			 ++now->count;
			 break;
		 }
		 else if (now->key > num)
		 {
			 p = now;
			 now = now->left;
		 }
		 else
		 {
			 p = now;
			 now = now->right;
		 }
	 }
 }

 void BST::delete_num()
 {
	 int num;
	 cin >> num;
	 Node* now = root;
	 Node* parent=nullptr;
	 if (num == 11848)
		 num = num;
	 while (1)
	 {
		 if (now == nullptr)
		 {
			 cout << "None" << endl;
			 return ;
		 }
		 else if (now->key == num)
		 {
			 --now->count;
			 break;
		 }
		 else if (now->key > num)		 
		 {
			 parent = now;
			 now = now->left;			
		 }
		 else		 
		 {
			 parent = now;
			 now = now->right;
		 }
	 }//end of while
	
	 if (!now->count)
	 {	 
		 if (now->left == nullptr && now->right == nullptr)
		 {
			 if (parent == nullptr)//删除根节点
				 root = nullptr;
			 else if (parent->key > now->key)
				 parent->left = nullptr;
			 else
				 parent->right = nullptr;
			 return  ;
		 }
		 else if (now->left == nullptr)
		 {
			 if (parent == nullptr)//删除根节点
				 root = now->right;
			 else if (parent->key > now->key)
				 parent->left = now->right;
			 else
				 parent->right = now->right;
		 }
		 else if (now->right == nullptr)
		 {
			 if (parent == nullptr)//删除根节点
				 root = now->left;
			 else if (parent->key > now->key)
				 parent->left = now->left;
			 else
				 parent->right = now->left;
		 }
		 else
		 {
			 Node* tem = now->left;
			 Node* p = now;
			 while (tem->right)
				 tem = (p=tem)->right;

			 if (tem == now->left)
				 tem->right = now->right;
			 else
			 {

				 p->right = tem->left;
				 tem->right = now->right;
				 tem->left = now->left;
			 }

			 if (parent == nullptr)
				 root = tem;
			 else
				 if (parent->key > now->key)
					 parent->left = tem;
				 else
					 parent->right = tem;
		 }
		 delete now;
	 }
 }
 void BST::count_num()
 {
	 int num ;
	 cin >> num;
	 Node* now = root;

	 while (1)
	 {
		 if (now == nullptr) 
			 break;	 
		 else if (now->key == num)	 
			 break;
		 else if (now->key > num)		 
			 now = now->left;
		 else
			 now = now->right;
	 }
	 if (now == nullptr)
		 cout << "0" << endl;
	 else
		 cout << now->count << endl;
 }
 void BST::cout_min()
 {
	 Node* now = root;
	 while (now!=nullptr && now->left!=nullptr)
		 now = now->left;
	 cout << now->key << endl;
 }
 void BST::cout_pri()
 {
	 int num,out=-999;
	 cin >> num;
	 if (num == 23660)
		 num = num;
	 Node* now = root;
	 Node* par = nullptr;

	 while (1)
	 {
		 if (now == nullptr)
			 break;
		 if (now->key < num)
			 out = max(out, now->key);

		 if (now->key >= num )
			 now = (par = now)->left;
		 else
			 now = (par = now)->right;
 
	 }
	 if (out != -999)
		 cout << out << endl;
	 else
		 cout << "None" << endl;
 }
 void BST::dispose(const int n)
 {
	 int tem_input;
	 void (BST:: * fun[])(void) = { &BST::insert, &BST::delete_num, &BST::count_num, &BST::cout_min, &BST::cout_pri };
	 for (int i = 0; i < n; i++)
	 {
		 cin >> tem_input;
		 (this->*fun[tem_input - 1])();
	 }
 }
 int main()
 {
	 int n;
	 cin >> n;
	 BST slove;
	 slove.dispose(n);
 }