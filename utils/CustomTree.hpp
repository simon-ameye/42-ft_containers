/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomTree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:24:09 by sameye            #+#    #+#             */
/*   Updated: 2022/04/05 18:10:45 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUSTOMTREE_HPP
#define CUSTOMTREE_HPP

//template <typename PairValue>
class TreeNode
{
	public:
	TreeNode	*_Left;
	TreeNode	*_Right;
	int			_value;
	int			_key;
	int			_height;
};



//template <typename PairValue, class KeyCompare>
class CustomTree
{
	public:

	int CustomTree::min(int a, int b);

	int CustomTree::height(TreeNode *N)
	{
		if (N == NULL)
			return 0;
		return N->_height;
	}

	TreeNode* CustomTree::newNode(int key, int val)
	{
		TreeNode* Node = new TreeNode();
		Node->_key = key;
		Node->_value = val;
		Node->_Left = NULL;
		Node->_Right = NULL;
		Node->_height = 1;
		return(Node);
	}

	private:
	TreeNode _first;
};

#endif