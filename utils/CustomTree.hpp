/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomTree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:24:09 by sameye            #+#    #+#             */
/*   Updated: 2022/05/04 16:17:47 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUSTOMTREE_HPP
#define CUSTOMTREE_HPP

#include <fstream>

namespace ft
{
	template < class value_type >
	class Node
	{
		public:

		Node (int type = 0, Node* left = NULL, Node* right = NULL, Node* parent = NULL, int height = 1) :
			type(type) , left(left), right(right), parent(parent), height(height) {}
		value_type _val;
		int type; //0 data, 1 passed the begining, 2, passed the end
		Node *left;
		Node *right;
		Node *parent;
		int height;
	};

	template < class value_type, class Key, typename Compare = std::less<value_type>, class Alloc = std::allocator < ft::Node < value_type > > >
	class CustomTree
	{
		/* *******************TYPEDEF******************* */
		private:
			typedef ft::Node < value_type >					N;


		/* *******************CONSTRUCTORS******************* */
		public:
			CustomTree(void)
			{
				N *passed_begin = _newNode(value_type());
				N *passed_end = _newNode(value_type());
				passed_begin->type = 1;
				passed_begin->right = passed_end;
				passed_end->type = 2;
				passed_end->parent = passed_begin;
				_root = passed_begin;
				_size = 0;
			}

			~CustomTree(void)
			{
				_delete(_root);
			}

		/* *******************MAIN FUNCTIONS******************* */
			void insert(value_type val)
			{
				_root = _insert(_root, val);
			}

			N* at(Key key) const //a robust version of at that returns a NULL if not found
			{
				return (_at(_root, key));
			}

			void erase(Key key)
			{
				_root = _erase(_root, key);
			}

			void clear(void)
			{
				N *passed_begin = minKeyNode();
				N *passed_end = maxKeyNode();
				_clear(_root);
				passed_begin->right = passed_end;
				passed_end->parent = passed_begin;
				_root = passed_begin;
			}

			N* minKeyNode(void) const
			{
				return (_minKeyNode(_root));
			}

			N* maxKeyNode(void) const
			{
				return (_maxKeyNode(_root));
			}

			size_t getSize(void) const
			{
				return (_size);
			}

		/* *******************USEFUL PRIVATE FUNCTIONS******************* */
		private:
			void _clear(N* root)
			{
				if (root->left)
					_clear(root->left);
				if (root->right)
					_clear(root->right);
				if (root->type == 0)
					_delNode(root);
			}

			void _delete(N* root)
			{
				if (root->left)
					_delete(root->left);
				if (root->right)
					_delete(root->right);
				_delNode(root);
			}

			int _height(N *node) const
			{
				if (node == NULL)
					return 0;
				return node->height;
			}

			int _max(int a, int b) const
			{
				return (a > b)? a : b;
			}

			N* _newNode(value_type val)
			{
				N* node = _alloc.allocate(1);
				node->_val.first = val.first;
				node->_val.second = val.second;
				node->parent = NULL;
				node->left = NULL;
				node->right = NULL;
				node->height = 1; // new node is initially added at leaf
				node->type = 0;
				++_size;
				return(node);
			}


			void _delNode(N* node)
			{
				_alloc.destroy(node);
				--_size;
			}

			bool _NALessThanNB(N* A, N* B) const //compare = std::less<Key>
			{
				if (A->type == 2 || B->type == 1)
					return (false);
				if (A->type == 1 || B->type == 2)
					return (true);
				return (A->_val.first < B->_val.first);
			}

			N *_rightRotate(N *y)
			{
				N *x = y->left;
				N *T2 = x->right;
				x->right = y;
				y->left = T2;
				x->parent = y->parent;
				y->parent = x;
				if (T2)
					T2->parent = y;
				y->height = _max(_height(y->left), _height(y->right)) + 1;
				x->height = _max(_height(x->left), _height(x->right)) + 1;
				return x;
			}

			N *_leftRotate(N *x)
			{
				N *y = x->right;
				N *T2 = y->left;
				y->left = x;
				x->right = T2;
				y->parent = x->parent;
				x->parent = y;
				if (T2)
					T2->parent = x;
				x->height = _max(_height(x->left), _height(x->right)) + 1;
				y->height = _max(_height(y->left), _height(y->right)) + 1;
				return y;
			}

			int _getBalance(N *node)
			{
				if (node == NULL)
					return 0;
				return (_height(node->left) - _height(node->right));
			}

			N* _insert(N* node, value_type val)
			{
				N nval;
				nval._val.first = val.first;
				if (node == NULL)
					return(_newNode(val));
				if (_NALessThanNB(&nval, node))
				{
					node->left = _insert(node->left, val);
					node->left->parent = node;
				}
				else if (_NALessThanNB(node, &nval))
				{
					node->right = _insert(node->right, val);
					node->right->parent = node;
				}
				else
					return node; // DONT FORGET TO RAISE ERROR
				node->height = 1 + _max(_height(node->left), _height(node->right));
				int balance = _getBalance(node);
				if (balance > 1 && _NALessThanNB(&nval, node->left))
					return _rightRotate(node);
				if (balance < -1 && _NALessThanNB(node->right, &nval))
					return _leftRotate(node);
				if (balance > 1 && _NALessThanNB(node->left, &nval))
				{
					node->left = _leftRotate(node->left);
					return _rightRotate(node);
				}
				if (balance < -1 && _NALessThanNB(&nval, node->right))
				{
					node->right = _rightRotate(node->right);
					return _leftRotate(node);
				}
				return node;
			}

			N* _minKeyNode(N* node) const
			{
				N* current = node;

				while (current->left != NULL)
					current = current->left;
				return current;
			}

			N * _maxKeyNode(N* node) const
			{
				N* current = node;

				while (current->right != NULL)
					current = current->right;
				return current;
			}

			N* _erase(N* root, Key key)
			{
				N nval;
				N* tmp;
				nval._val.first = key;
				if (_NALessThanNB(&nval, root)) //not our guy, go left
				{
					tmp = root;
					root->left = _erase(root->left, key);
				}
				else if (_NALessThanNB(root, &nval)) //not our guy, go right
				{
					tmp = root;
					root->right = _erase(root->right, key);
				}
				else if (!root->left && !root->right) // our guy with no child, delete !
				{
					_delNode(root);
					return (NULL);
				}
				else //our guy and at least one child
				{
					if (root->right && root->left) //two childs, lets decide what rotation to do
					{
						if (_height(root->left) > _height(root->right))
							tmp = _erase(_rightRotate(root), key);
						else 
							tmp = _erase(_leftRotate(root), key);
					}
					else if (root->right) //only one chile, rotation imposed
						tmp = _erase(_leftRotate(root), key);
					else //only one chile, rotation imposed
						tmp = _erase(_rightRotate(root), key);
				}
				root->height = 1 + _max(_height(root->left), _height(root->right));
				return (tmp);
			}

			N* _at(N* node, Key key) const
			{
				if (!node)
					return (NULL);
				N nval;
				nval._val.first = key;
				if (_NALessThanNB(&nval, node))
					return (_at(node->left, key));
				else if (_NALessThanNB(node, &nval))
					return (_at(node->right, key));
				else
					return (node);
			}

		/* *******************USEFUL DEV FEATURES******************* */
		public:
			void print_tree(void) //TO REMOVE
			{
				std::ofstream myfile;
				myfile.open ("dotgraph.txt");
				myfile << "#########DOT GRAPH FOR https://dreampuf.github.io/############" << std::endl;
				myfile << "digraph G {" << std::endl;
				myfile << "    node [shape=plaintext fontname=\"Sans serif\" fontsize=\"8\"];" << std::endl;
				myfile.close();
				_print_tree(_root);
				myfile.open ("dotgraph.txt", std::ios_base::app);
				myfile << "}" << std::endl;
				myfile << "##############################################################" << std::endl;
				myfile.close();
			}

		private:
			void _print_tree(N* root)
			{
				std::ofstream myfile;
				myfile.open ("dotgraph.txt", std::ios_base::app);
				myfile << "    key" << root->_val.first << root->type << " [ label=<" << std::endl;
				myfile << "        <table border=\"1\" cellborder=\"0\" cellspacing=\"1\">" << std::endl;
				myfile << "            <tr><td align=\"left\"><b>" << "key " << root->_val.first << "</b></td></tr>" << std::endl;
				myfile << "            <tr><td align=\"left\"><b>" << "map \"";
				if (root->_val.second)
					myfile << root->_val.second;
				else
					myfile << "NULL";
				myfile << "\"</b></td></tr>" << std::endl;
				myfile << "            <tr><td align=\"left\"><b>" << "type " << root->type << "</b></td></tr>" << std::endl;
				myfile << "            <tr><td align=\"left\"><b>" << "height " << root->height << "</b></td></tr>" << std::endl;
				myfile << "            <tr><td align=\"left\"><font color=\"darkgreen\">";
				myfile << "parent ";
				if (root->parent)
					myfile << root->parent->_val.first;
				else
					myfile << "NULL";
				myfile << "</font></td></tr>" << std::endl;
				myfile << "        </table>>];" << std::endl;
				if (root->left)
					myfile << "    \"key" << root->_val.first << root->type << "\"->\"key" << root->left->_val.first << root->left->type << "\"";
				else
					myfile << "    \"key" << root->_val.first << root->type << "\"->\"LNULL" << root->_val.first << root->type << "\"";
				myfile << " [ label=\"l\" fontsize=\"7\" ];" << std::endl;
				if (root->right)
					myfile << "    \"key" << root->_val.first << root->type << "\"->\"key" << root->right->_val.first << root->right->type << "\"";
				else
					myfile << "    \"key" << root->_val.first << root->type << "\"->\"RNULL" << root->_val.first << root->type << "\"";
				myfile << " [ label=\"r\" fontsize=\"7\" ];" << std::endl;
				if (root->left)
					_print_tree(root->left);
				if (root->right)
					_print_tree(root->right);
				myfile.close();
			}

		public:
			void pre0rder(void) const //TO REMOVE
			{
				_preOrder(_root);
			}

		private:
			void _preOrder(N* root)
			{
				if(root)
				{
					std::cout << root->_val.first << " ";
					_preOrder(root->left);
					_preOrder(root->right);
				}
			}

		/* *******************VARIABLES******************* */
		public:
			N *_root;
			size_t _size;

		private:
			Alloc				_alloc;
	};
}
#endif