/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomTree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:24:09 by sameye            #+#    #+#             */
/*   Updated: 2022/04/23 21:21:21 by sameye           ###   ########.fr       */
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
			CustomTree(void) : _root(NULL) {}

			void insert(value_type val)
			{
				_root = _insert(_root, val);
			}

			void erase(Key key)
			{
				_root = _erase(_root, key);
			}

			N* at(Key key)
			{
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
					}
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
				/* 1. Perform the normal BST rotation */
				if (node == NULL)
					return(_newNode(val));

				//replace _key by val.first
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
					return _rightRotate(node);

				// Right Right Case
				if (balance < -1 && val.first > node->right->_val.first)
					return _leftRotate(node);

				// Left Right Case
				if (balance > 1 && val.first > node->left->_val.first)
				{
					node->left = _leftRotate(node->left);
					return _rightRotate(node);
				}

				// Right Left Case
				if (balance < -1 && val.first < node->right->_val.first)
				{
					node->right = _rightRotate(node->right);
					return _leftRotate(node);
				}

				/* return the (unchanged) node pointer */
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
					if( (root->left == NULL) ||
						(root->right == NULL) )
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

		private:
			N *_root;

	};
}
#endif

// Thanks to rathbhupendra : https://www.geeksforgeeks.org/avl-tree-set-2-deletion/