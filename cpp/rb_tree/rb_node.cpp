#include "rb_node.h"
/*
template <class node_value_class>
void rbtree<node_value_class>::insert(rbtree<node_value_class> & some_node)
{
	//处理传入时NIL的特殊情况
	if (&some_node == TREE_NIL)
	{
		return;
	}

	//处理调用对象是NIL的情况
	if (this == TREE_NIL)
	{
		//解除some_node的父级关系
	}

	//如果传入的some_node已经有父节点，那么需要解除关系
	if (some_node.parent != TREE_NIL)
	{

	}

	//这里的
	rbtree<node_value_class> * now_node = this;		//记录当前节点

	rbtree<node_value_class> ** next_node = nullptr; //记录下一节点的指针
	rbtree<node_value_class> * parent = nullptr;			//记录父节点


	while (now_node != TREE_NIL)
	{
		next_node = nullptr;
		parent = now_node;

		//先判断值大小
		if (some_node.node_value > now_node->node_value)
		{
			*next_node = now_node->right_child;

		}
		else
		{
			*next_node = now_node->left_child;

		}
		//如果其下一节点是空的
		if (*next_node == TREE_NIL)
		{
			*next_node = some_node;
			some_node.parent = parent;
			break;
		}
		else
			//如果其下一节点有元素
		{
			now_node = *next_node;
		}
	}
};
template <class node_value_class>
void rbtree<node_value_class>::insert(node_value_class v)
{
	rbtree<node_value_class> *node = new  rbtree<node_value_class>(v);
	insert(*node);
};



template <class node_value_class>
void rbtree<node_value_class>::show_preorder()
{

	std::vector<std::pair< rbtree<node_value_class> *, std::string> > p_list;
	std::string pre("|-");
	p_list.push_back(std::make_pair(this, pre));

	while (!p_list.empty())
	{
		//std::pair< rbtree<node_value_class> *, std::string> node_pair;
		auto node_pair = p_list.back();
		p_list.pop_back();

		rbtree<int> * now = node_pair.first;
		std::string  pre = node_pair.second;
		string color = is_black ? " B " : " R ";
		cout << pre << node_value << "(" << color << ")";


		if (now->left_child != TREE_NIL)
		{
			p_list.push_back(std::make_pair(now->left_child, pre + "-"));

		}

		if (now->right_child != TREE_NIL)
		{
			p_list.push_back(std::make_pair(now->right_child, pre + "-"));
		}

	}
};
*/