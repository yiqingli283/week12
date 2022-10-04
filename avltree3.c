//查找操作
avltree searchNode(avltree node, int key)
{
	//如果是空树或者要删除的值就是根节点
	if (node == NULL || node->data == key)
	{
		return node;
	}
	else if(key < node->data)
	{
		searchNode(node->left, key);
	}
	else if (key > node->data)
	{
		searchNode(node->right, key);
	}
}
 
//寻找左子树的最大值
avltree findMax(avltree tree)
{
	if (tree != NULL)
	{
		while (tree->right)
		{
			tree = tree->right;
		}
	}
	return tree;
}
 
//删除操作
avltree deleteNode(avltree tree, int key)
{
	//node是找到的要删除的那一个节点
	avlnode* node = searchNode(tree, key);
	if (node == NULL || tree == NULL)
	{
		//如果要删除的节点为空或者是空树
		return tree;
	}
	//还是要去判断属于哪一种失衡情况
	//要删除的节点在左子树
	if (key < tree->data)
	{
		tree->left = deleteNode(tree->left, key);
		//判断有没有失衡 
		//和插入正好相反！如果是在左边删除导致的失衡 那么一定是右子树高
		if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
		{
			//如果失衡且右子树的左子树存在 那么就是RL的情况
			if (tree->right->left)
			{
				tree = right_left_rotation(tree);
			}
			else
			{
				tree = right_right_rotation(tree);
			}
		}
	}
	//要删除的节点在右子树
	else if (key > tree->data)
	{
		tree->right = deleteNode(tree->right, key);
		//如果是在右边删除导致的失衡 那么一定是左子树高
		if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
		{
			//如果失衡且左子树的右子树存在 那么就是LR的情况
			if (tree->left->right)
			{
				tree = left_right_rotation(tree);
			}
			else
			{
				tree = left_left_rotation(tree);
			}
		}
	}
	//找到了待删除的节点 就删除
	else
	{
		//保证二叉排序树的有序性
		//如果左右孩子都有的情况 找左孩子的最大值替换要删除的节点
		if (tree->left && tree->right)
		{
			avlnode* left_max_node = findMax(tree->left);
			tree->data = left_max_node->data;
			//还要删除原先的最大值节点
			tree->left = deleteNode(tree->left, left_max_node->data);
		}
		else
		{
			//独子或者无子的情况
			tree = tree->left ? tree->left : tree->right;
		}
	}
	if(tree)
	{
		tree->height = MAX(getNode_Height(tree->left), getNode_Height(tree->right)) + 1;//重置每一个节点高度
	}
	return tree;
}