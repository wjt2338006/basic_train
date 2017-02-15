#include "rb_node.h"
/*
template <class node_value_class>
void rbtree<node_value_class>::insert(rbtree<node_value_class> & some_node)
{
	//������ʱNIL���������
	if (&some_node == TREE_NIL)
	{
		return;
	}

	//������ö�����NIL�����
	if (this == TREE_NIL)
	{
		//���some_node�ĸ�����ϵ
	}

	//��������some_node�Ѿ��и��ڵ㣬��ô��Ҫ�����ϵ
	if (some_node.parent != TREE_NIL)
	{

	}

	//�����
	rbtree<node_value_class> * now_node = this;		//��¼��ǰ�ڵ�

	rbtree<node_value_class> ** next_node = nullptr; //��¼��һ�ڵ��ָ��
	rbtree<node_value_class> * parent = nullptr;			//��¼���ڵ�


	while (now_node != TREE_NIL)
	{
		next_node = nullptr;
		parent = now_node;

		//���ж�ֵ��С
		if (some_node.node_value > now_node->node_value)
		{
			*next_node = now_node->right_child;

		}
		else
		{
			*next_node = now_node->left_child;

		}
		//�������һ�ڵ��ǿյ�
		if (*next_node == TREE_NIL)
		{
			*next_node = some_node;
			some_node.parent = parent;
			break;
		}
		else
			//�������һ�ڵ���Ԫ��
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