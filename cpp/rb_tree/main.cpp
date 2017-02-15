#include "rb_node.h"
//extern template class rbtree<int>;
int main(void)
{
	rbtree<int> tree(10,true); 
	tree.insert(9);
	
	tree.insert(8);
	//tree.show_preorder();
	//tree.left_child->left_rotate();
	tree.insert(7);
	tree.insert(11);
	tree.insert(12);
	
	/*
	tree.insert(12);
	tree.insert(11);
	tree.insert(13);*/
	tree.show_preorder();
	return 0;
}