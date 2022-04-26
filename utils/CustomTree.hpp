/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomTree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:24:09 by sameye            #+#    #+#             */
/*   Updated: 2022/04/26 01:41:18 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUSTOMTREE_HPP
#define CUSTOMTREE_HPP

namespace ft
{
	// An AVL tree node
	template < class value_type >
	class Node
	{
		public:
		value_type _val;
		//Key _key;
		//T _map;
		Node *left;
		Node *right;
		Node *parent;
		int height;
	};

	template < class value_type, class Key, class Compare, class Alloc = std::allocator < ft::Node < value_type > > >
	class CustomTree
	{
		public:
			typedef ft::Node < value_type >					N;
			//typedef typename value_type::first						Key;

		private:
			Alloc				_alloc; //copy of allocator

		public:

			void print_tree(void)
			{
				std::cout << "#########DOT GRAPH FOR https://dreampuf.github.io/############" << std::endl;
				std::cout << "digraph G {" << std::endl;
				std::cout << "    node [shape=plaintext fontname=\"Sans serif\" fontsize=\"8\"];" << std::endl;
				_print_tree(_root);
				std::cout << "}" << std::endl;
				std::cout << "##############################################################" << std::endl;
			}

			CustomTree(void) : _root(NULL) {}

			void insert(value_type val)
			{
				_root = _insert(_root, val);
			}

			N* get_passed_the_end(void)
			{
				return (&_passed_the_end);
			}


			void erase(Key key)
			{
				_root = _erase(_root, key);
			}

			N* at(Key key)
			{
				//std::cout << "at" << std::endl;
				return (_at(_root, key));
			}

			N* next(N *node)
			{
				if (node->right)
					return (_minKeyNode(node->right));
				else
					while (node->parent)
					{
						if (node->parent->left == node)
							return (node->parent);
						node = node->parent;
						std::cout << std::endl;
					}
				return (&_passed_the_end);
			}

			N* minKeyNode(void)
			{
				return (_minKeyNode(_root));
			}

			N* maxKeyNode(void)
			{
				return (_maxKeyNode(_root));
			}

		private:
			int _height(N *node)
			{
				if (node == NULL)
					return 0;
				return node->height;
			}

			int _max(int a, int b)
			{
				return (a > b)? a : b;
			}

			N* _newNode(value_type val)
			{
				//std::allocator < N > Alloc;
				N* node = _alloc.allocate(1);
				//node->_key = key;
				//node->_map = map;
				node->_val.first = val.first;
				node->_val.second = val.second;
				node->parent = NULL;
				node->left = NULL;
				node->right = NULL;
				node->height = 1; // new node is initially added at leaf
				return(node);
			}

			N *_rightRotate(N *y)
			{
				N *x = y->left;
				N *T2 = x->right;

				// Perform rotation
				x->right = y;
				y->left = T2;

				x->parent = y->parent;
				y->parent = x;
				if (T2)
					T2->parent = y;

				// Update heights
				y->height = _max(_height(y->left), _height(y->right)) + 1;
				x->height = _max(_height(x->left), _height(x->right)) + 1;

				// Return new root
				return x;
			}

			N *_leftRotate(N *x)
			{
				N *y = x->right;
				N *T2 = y->left;

				// Perform rotation
				y->left = x;
				x->right = T2;

				y->parent = x->parent;
				x->parent = y;
				if (T2)
					T2->parent = x;

				// Update heights
				x->height = _max(_height(x->left), _height(x->right)) + 1;
				y->height = _max(_height(y->left), _height(y->right)) + 1;

				// Return new root
				return y;
			}

			int _getBalance(N *node)
			{
				if (node == NULL)
					return 0;
				return _height(node->left) - _height(node->right);
			}

			N* _insert(N* node, value_type val)
			{
				//std::cout << "Lets insert !" << std::endl;
				/* 1. Perform the normal BST rotation */
				if (node == NULL)
				{
					//std::cout << "return NULL node" << std::endl;
					return(_newNode(val));
				}

				if (val.first < node->_val.first)
				{
					node->left = _insert(node->left, val);
					node->left->parent = node;
				}
				else if (val.first > node->_val.first)
				{
					node->right = _insert(node->right, val);
					node->right->parent = node;
				}
				else // Equal keys not allowed
					return node; // DONT FORGET TO RAISE ERROR

				/* 2. Update height of this ancestor node */
				node->height = 1 + _max(_height(node->left), _height(node->right));

				/* 3. Get the balance factor of this
					ancestor node to check whether
					this node became unbalanced */
				int balance = _getBalance(node);

				// If this node becomes unbalanced,
				// then there are 4 cases

				// Left Left Case
				if (balance > 1 && val.first < node->left->_val.first)
				{
					//std::cout << "return left left case" << std::endl;
					return _rightRotate(node);
				}

				// Right Right Case
				if (balance < -1 && val.first > node->right->_val.first)
				{
					//std::cout << "return right right case" << std::endl;
					return _leftRotate(node);
				}

				// Left Right Case
				if (balance > 1 && val.first > node->left->_val.first)
				{
					node->left = _leftRotate(node->left);
					//std::cout << "return left right case" << std::endl;
					return _rightRotate(node);
				}

				// Right Left Case
				if (balance < -1 && val.first < node->right->_val.first)
				{
					node->right = _rightRotate(node->right);
					//std::cout << "return right left case" << std::endl;
					return _leftRotate(node);
				}

				/* return the (unchanged) node pointer */
				//std::cout << "return unchanged case" << std::endl;
				return node;
			}

			N* _minKeyNode(N* node)
			{
				N* current = node;

				/* loop down to find the leftmost leaf */

				while (current->left != NULL)
					current = current->left;
				return current;
			}

			N * _maxKeyNode(N* node)
			{
				N* current = node;

				/* loop down to find the leftmost leaf */
				while (current->right != NULL)
					current = current->right;

				return current;
			}

			N* _erase(N* root, Key key)
			{
				//std::cout << "erase is evaluating key " << root->_val.first << " val " << root->_val.second << std::endl;
				// STEP 1: PERFORM STANDARD BST DELETE
				if (root == NULL)
					return root;

				// If the _key to be deleted is smaller
				// than the root's _key, then it lies
				// in left subtree
				if ( key < root->_val.first )
					root->left = _erase(root->left, key);

				// If the _key to be deleted is greater
				// than the root's _key, then it lies
				// in right subtree
				else if( key > root->_val.first )
					root->right = _erase(root->right, key);

				// if _key is same as root's _key, then
				// This is the node to be deleted
				else
				{
					// node with only one child or no child
					if( (root->left == NULL) || (root->right == NULL) )
					{
						N *temp = root->left ? root->left : root->right;

						// No child case
						if (temp == NULL)
						{
							temp = root;
							root = NULL;
						}
						else // One child case
							*root = *temp; // Copy the contents of
									// the non-empty child
						free(temp);
					}
					else
					{
						// node with two children: Get the inorder
						// successor (smallest in the right subtree)
						N* temp = _minKeyNode(root->right);

						// Copy the inorder successor's
						// data to this node
						root->_val.first = temp->_val.first;
						root->_val.second = temp->_val.second;

						// Delete the inorder successor
						root->right = _erase(root->right, temp->_val.first);
					}
				}

				// If the tree had only one node
				// then return
				if (root == NULL)
				return root;

				// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
				root->height = 1 + _max(_height(root->left), _height(root->right));

				// STEP 3: GET THE BALANCE FACTOR OF
				// THIS NODE (to check whether this
				// node became unbalanced)
				int balance = _getBalance(root);

				// If this node becomes unbalanced,
				// then there are 4 cases

				// Left Left Case
				if (balance > 1 &&
					_getBalance(root->left) >= 0)
					return _rightRotate(root);

				// Left Right Case
				if (balance > 1 &&
					_getBalance(root->left) < 0)
				{
					root->left = _leftRotate(root->left);
					return _rightRotate(root);
				}

				// Right Right Case
				if (balance < -1 &&
					_getBalance(root->right) <= 0)
					return _leftRotate(root);

				// Right Left Case
				if (balance < -1 &&
					_getBalance(root->right) > 0)
				{
					root->right = _rightRotate(root->right);
					return _leftRotate(root);
				}

				return root;
			}

			N* _at(N* node, Key key)
			{
				//std::cout << "_at" << std::endl;
				if (key < node->_val.first)
				{
					return (_at(node->left, key));
				}
				else if (key > node->_val.first)
				{
					return (_at(node->right, key));
				}
				else
				{
					return (node);
				}
			}

			void _print_tree(N* root)
			{
				std::cout << "    key" << root->_val.first << " [ label=<" << std::endl;
				std::cout << "        <table border=\"1\" cellborder=\"0\" cellspacing=\"1\">" << std::endl;
				std::cout << "            <tr><td align=\"left\"><b>" << root->_val.first << "</b></td></tr>" << std::endl;
				std::cout << "            <tr><td align=\"left\"><b>" << root->_val.second << "</b></td></tr>" << std::endl;
				std::cout << "            <tr><td align=\"left\"><font color=\"darkgreen\">";
				if (root->parent)
					std::cout << root->parent->_val.first;
				else
					std::cout << "NULL";
				std::cout << "</font></td></tr>" << std::endl;
				std::cout << "        </table>>];" << std::endl;
				if (root->left)
					std::cout << "    key" << root->_val.first << "->key" << root->left->_val.first;
				else
					std::cout << "    key" << root->_val.first << "->LNULL" << root->_val.first;
				std::cout << " [ label=\"l\" fontsize=\"7\" ];" << std::endl;
				if (root->right)
					std::cout << "    key" << root->_val.first << "->key" << root->right->_val.first;
				else
					std::cout << "    key" << root->_val.first << "->RNULL" << root->_val.first;
				std::cout << " [ label=\"r\" fontsize=\"7\" ];" << std::endl;
				if (root->left)
					_print_tree(root->left);
				if (root->right)
					_print_tree(root->right);
			}

		private:
			N *_root;
			N _passed_the_end;

	};
}
#endif

// Thanks to rathbhupendra : https://www.geeksforgeeks.org/avl-tree-set-2-deletion/