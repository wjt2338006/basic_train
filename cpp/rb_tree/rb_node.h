#pragma once
#include <vector>
#include <utility>
#include <iostream>
#include <string>
#define TREE_NIL  nullptr
using namespace std;

template <class node_value_class>
class rbtree
{
public:
	static const int LEFT = 1;
	static const int RIGHT = 2;
	
	rbtree(node_value_class nv, bool ib = false)
	{
		node_value = nv;
		is_black = ib;
		left_child = TREE_NIL;
		right_child = TREE_NIL;
		parent = TREE_NIL;
		if (ib == true)
		{
			is_root = true;
		}
		else
		{
			is_root = false;
		}

	};

	
	rbtree(const rbtree &r)
	{
		node_value = r.node_value;
		is_black = r.ib;
		left_child = TREE_NIL;
		right_child = TREE_NIL;
		parent = TREE_NIL;
		is_root = is_root;
	}
	rbtree& operator=(const  rbtree &r)
	{
		node_value = r.node_value;
		is_black = r.ib;
		left_child = TREE_NIL;
		right_child = TREE_NIL;
		parent = TREE_NIL;
		is_root = is_root;
	}



	~rbtree()
	{

	};


	//����һ���ڵ㵽һ��λ��
	void insert(rbtree<node_value_class> & some_node)
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
				next_node = &now_node->right_child;

			}
			else
			{
				next_node = &now_node->left_child;

			}
			//�������һ�ڵ��ǿյ�
			if (*next_node == TREE_NIL)
			{
				*next_node = &some_node;
				some_node.parent = parent;
				now_node = &some_node;
				break;
			}
			else
				//�������һ�ڵ���Ԫ��
			{
				now_node = *next_node;
			}
		}

		//�����������һ��ƽ���λ��
		now_node->fix_up();


	};
	

	void insert(node_value_class v)
	{
		rbtree<node_value_class> *node = new  rbtree<node_value_class>(v);
		insert(*node);
		
	};
	
	void fix_up()
	{
		rbtree<node_value_class> * now = this;
		
		while (! rbtree<node_value_class>::is_black_node(now->parent) )
		{
			rbtree<node_value_class> * p = now->parent;
			rbtree<node_value_class> * p_brother = nullptr;

			if (p == p->parent->left_child)
			{
				p_brother = p->parent->right_child;
				//�����ɫ
				if (!rbtree<node_value_class>::is_black_node(p_brother))
				{
					p_brother->is_black = true;
					p->is_black = true;
					p->parent->is_black = false;
					now = p->parent;
				}
				
				else 
				{
					//�����ɫ�������ڸ����ұ�
					if (now == p->right_child)
					{
						now = p;
						p_brother = nullptr;
						now->left_rotate();
						//now = now->parent;
					}

					p = now->parent;
					
					//�����ɫ�������ڸ������
					p->is_black = true;
					p->parent->is_black = false;
					p->right_rotate();
				}
				
			}
			else
			{
				p_brother = p->parent->left_child;
				//�����ɫ
				if (!rbtree<node_value_class>::is_black_node(p_brother))
				{
					p_brother->is_black = true;
					p->is_black = true;
					p->parent->is_black = false;
					now = p->parent;
				}
				
				else
				{
					//�����ɫ�������ڸ������
					if (now == p->left_child)
					{
						now = p;
						p_brother = nullptr;
						now->left_child->right_rotate();
					}

					
					p = now->parent;

					//�����ɫ�������ڸ������
					p->is_black = true;
					p->parent->is_black = false;
					p->parent->left_rotate();
					
				}
				
			}
			
			
		}
		rbtree<node_value_class> * root = now;
		while (!root->is_root)
		{
			root = root->parent;
		}
		root->is_black = true;

	}
	static bool is_black_node(rbtree<node_value_class> * node)
	{
		if (node == TREE_NIL)
		{
			return true;
		}
		else
		{
			return node->is_black;
		}
	}

	//��ʾ�Ե�ǰ�ڵ�Ϊ��ʼ�����
	void show_preorder()
	{
		rbtree<node_value_class> * root = this;
		while (!root->is_root)
		{
			root = root->parent;
		}

		std::vector<std::pair< rbtree<node_value_class> *, std::string> > p_list;
		std::string pre("|-");
		p_list.push_back(std::make_pair(root, pre));

		while (!p_list.empty())
		{
			//std::pair< rbtree<node_value_class> *, std::string> node_pair;
			auto node_pair = p_list.back();
			p_list.pop_back();

			rbtree<node_value_class> * now = node_pair.first;
			std::string  pre = node_pair.second;
			string color = now->is_black ? " B " : " R ";
			cout << pre << now->node_value<< "( " << color << " ) " << endl;;

			

			if (now->right_child != TREE_NIL)
			{
				p_list.push_back(std::make_pair(now->right_child, pre + "-"));
			}
			if (now->left_child != TREE_NIL)
			{
				p_list.push_back(std::make_pair(now->left_child, pre + "-"));

			}

		}
		cout << "_____" << endl;
		return;
	};

	inline void del()
	{
		
	};

private:
	//����ת,������Ϊ���Ͻڵ㣬��Ҫ�½�
	void left_rotate()
	{
		//ȷ�������ұ߽ڵ㲻�ǿ�
		if (right_child == TREE_NIL)
		{
			return;
		}
		if (parent == TREE_NIL)
		{
			return;
		}
		rbtree * x = this;
		rbtree * y = right_child;
		rbtree * y_l = y->left_child;
		rbtree * x_p = x->parent;

		//x y ��ϵ�ؽ�
		y->build_connect(x, LEFT);

		//x y_l��ϵ�ؽ�
		x->build_connect(y_l, RIGHT);

		//y x_p��ϵ�ؽ�
		if (x_p == TREE_NIL)
		{
			y->parent = TREE_NIL;
			y->is_root = true;
			x->is_root = false;
		}
		else
		{
			if (x_p->right_child == x)
			{
				x_p->build_connect(y, RIGHT);
			}
			else
			{
				x_p->build_connect(y, LEFT);
			}
		}
		
		

	};
	//����ת��������Ϊ���½ڵ㣬��Ҫ����
	void right_rotate()
	{
		if (left_child == TREE_NIL)
		{
			return;
		}
		if (parent == TREE_NIL)
		{
			return;
		}
		rbtree *y = parent;
		rbtree *x = this;
		rbtree *y_p = y->parent;
		rbtree *x_r = x->right_child;

		//x y��ϵ�ؽ�
		x->build_connect(y,RIGHT);

		//y x_r��ϵ�ؽ�
		y->build_connect(x_r, LEFT);

		//x y_p ��ϵ�ؽ�
		if (y_p == TREE_NIL)
		{
			x->parent = TREE_NIL;
			x->is_root = true;
			y->is_root = false;
		}
		else
		{
			if (y_p->right_child == x)
			{
				y_p->build_connect(x, RIGHT);
			}
			else
			{
				y_p->build_connect(x, LEFT);
			}
		}
		

		
	};

	//����һ�����ӹ�ϵ����
	void build_connect(rbtree *son,int position)
	{
		if (son != TREE_NIL)
		{
			son->parent = this;
		}
		if (this == TREE_NIL)
		{
			return;
		}

		if (position == rbtree::LEFT)
		{
			left_child = son;
			
		}
		if (position == rbtree::RIGHT)
		{
			right_child = son;
		}
	}

	rbtree *parent;
	node_value_class node_value;
	rbtree *left_child;
	rbtree *right_child;
	bool is_black;
	bool is_root;

};

