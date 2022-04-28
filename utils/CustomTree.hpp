/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomTree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:24:09 by sameye            #+#    #+#             */
/*   Updated: 2022/04/28 20:36:19 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUSTOMTREE_HPP
#define CUSTOMTREE_HPP

#include <fstream>

namespace ft
{
	// An AVL tree node
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
		public:
			typedef ft::Node < value_type >					N;
			//typedef typename value_type::first						Key;

		private:
			Alloc				_alloc; //copy of allocator

		public:

			void pre0rder(void)
			{
				_preOrder(_root);
			}

			void print_tree(void)
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

			CustomTree(void) : _root(&_passed_begin), _passed_begin(N()), _passed_end(N())
			{
				std::cout << "constructor begin" << std::endl << std::flush;
				_passed_begin.type = 1;
				_passed_begin.right = &_passed_end;
				_passed_end.type = 2;
				_passed_end.parent = &_passed_begin;
				//_root = &_passed_begin;
				std::cout << "constructor end" << std::endl << std::flush;
			}

			void insert(value_type val)
			{
				_root = _insert(_root, val);
			}

			//N* get_passed_the_end(void)
			//{
			//	return (&_passed_the_end);
			//}


			void erase(Key key)
			{
				_root = _erase(_root, key);
			}

			N* at(Key key)
			{
				//std::cout << "at" << std::endl;
				return (_at(_root, key));
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
				node->type = 0;
				return(node);
			}

			bool _NALessThanNB(N* A, N* B) //compare = std::less<Key>
			{
				if (A->type == 2 || B->type == 1)
					return (false);
				if (A->type == 1 || B->type == 2)
					return (true);
				return (A->_val.first < B->_val.first);
			}

			//bool _NAMoreThanNB(N* A, N* B)
			//{
			//	return (!_NALessThanNB(A, B));
			//}

			//bool _ALessThanB(N* A, N* B)
			//{
			//	return (_NALessThanNB(A, B));
			//}
//
			//bool _ALessThanB(Key A, Key B)
			//{
			//	N tA, tB;
			//	tA._val.first = A;
			//	tB._val.first = B;
			//	return (_NALessThanNB(&tA, &tB));
			//}
//
			//bool _ALessThanB(N* A, Key B)
			//{
			//	N tB;
			//	tB._val.first = B;
			//	return (_NALessThanNB(A, &tB));
			//}
//
			//bool _ALessThanB(Key A, N* B)
			//{
			//	N tA;
			//	tA._val.first = A;
			//	return (_NALessThanNB(&tA, B));
			//}

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
				return (_height(node->left) - _height(node->right));
			}

			N* _insert(N* node, value_type val)
			{
				//std::cout << "Lets insert !" << std::endl;
				std::cout << "insert begin" << std::endl << std::flush;
				N nval;
				nval._val.first = val.first;

				/* 1. Perform the normal BST rotation */
				if (node == NULL)
				{
					//std::cout << "return NULL node" << std::endl;
					return(_newNode(val));
				}

				//if (val.first < node->_val.first);
				if (_NALessThanNB(&nval, node))
				{
					node->left = _insert(node->left, val);
					node->left->parent = node;
				}
				//else if (val.first > node->_val.first)
				else if (_NALessThanNB(node, &nval))
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
				//if (balance > 1 && val.first < node->left->_val.first)
				if (balance > 1 && _NALessThanNB(&nval, node->left))
				{
					//std::cout << "return left left case" << std::endl;
					return _rightRotate(node);
				}

				// Right Right Case
				//if (balance < -1 && val.first > node->right->_val.first)
				if (balance < -1 && _NALessThanNB(node->right, &nval))
				{
					//std::cout << "return right right case" << std::endl;
					return _leftRotate(node);
				}

				// Left Right Case
				//if (balance > 1 && val.first > node->left->_val.first)
				if (balance > 1 && _NALessThanNB(node->left, &nval))
				{
					node->left = _leftRotate(node->left);
					//std::cout << "return left right case" << std::endl;
					return _rightRotate(node);
				}

				// Right Left Case
				//if (balance < -1 && val.first < node->right->_val.first)
				if (balance < -1 && _NALessThanNB(&nval, node->right))
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

				while (current->right != NULL)
					current = current->right;

				return current;
			}
/*
			N* _erase(N* root, Key key)
			{
				N nval;
				nval._val.first = key;
				//std::cout << "erase is evaluating key " << root->_val.first << " val " << root->_val.second << std::endl;
				// STEP 1: PERFORM STANDARD BST DELETE
				if (root == NULL)
					return root;

				// If the _key to be deleted is smaller
				// than the root's _key, then it lies
				// in left subtree
				if (_NALessThanNB(&nval, root)) //if ( key < root->_val.first )
					root->left = _erase(root->left, key);

				// If the _key to be deleted is greater
				// than the root's _key, then it lies
				// in right subtree
				else if (_NALessThanNB(root, &nval)) //else if( key > root->_val.first )
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

///////////////////////////////// to replace !!
						// Copy the inorder successor's
						// data to this node
						root->_val.first = temp->_val.first;
						root->_val.second = temp->_val.second;
						root->type = temp->type;

						// Delete the inorder successor
						root->right = _erase(root->right, temp->_val.first);


////////////////////////////////////

						//free(root);



//////////////////////////////////



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
*/
			N* _erase(N* root, Key key) // my earse
			{
				N nval;
				nval._val.first = key;
				if (_NALessThanNB(&nval, root)) //not our guy
					root->left = _erase(root->left, key);
				else if (_NALessThanNB(root, &nval)) //not our guy
					root->right = _erase(root->right, key);
				else if (!root->left && !root->right) // our guy with no child, delete !
				{
					free(root);
					return (NULL);
				}
				else //at least one child (our guy)
				{
					if (root->right)
					{
						return (_erase(_leftRotate(root), key));
					}
					else
					{
						return (_erase(_rightRotate(root), key));
					}
				}
				return (root);
			}

			N* _at(N* node, Key key)
			{
				std::cout << "_at call" << std::endl << std::flush;
				N nval;
				nval._val.first = key;
				if (_NALessThanNB(&nval, node)) //if (key < node->_val.first)
				{
					return (_at(node->left, key));
				}
				else if (_NALessThanNB(node, &nval)) //else if (key > node->_val.first)
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

			void _preOrder(N* root)
			{
				if(root)
				{
					std::cout << root->_val.first << " ";
					_preOrder(root->left);
					_preOrder(root->right);
				}
			}

		private:
			N *_root;
			//Compare _compare;
			N _passed_begin, _passed_end;

	};
}
#endif

// Thanks to rathbhupendra : https://www.geeksforgeeks.org/avl-tree-set-2-deletion/