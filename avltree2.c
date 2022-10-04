avltree insert(avltree node, int key)
{
	//当根节点为NULL
	if (node == NULL)
	{
		//创建节点
		avlnode* root = create(key, NULL, NULL);
		node = root;
	}
	//如果说不为空 考虑往哪边插入
	//往左子树插入
	else if (key < node->data)
	{
		//递归去寻找待插节点的位置
		node->left = insert(node->left, key);
		//因为是左边插入 如果有失衡就一定是左边失衡
		//高度差等于2 就是最小失衡树
		if (HEIGHT(node->left) - HEIGHT(node->right) == 2)
		{
			//判断此时是属于哪一种失衡
			//如果插入的值是在节点的左子树 那么就是左子树的左子树LL的情况
			if (key < node->left->data)
			{
				left_left_rotation(node);
			}
			else
			{
				//否则就是左子树的右子树LR的情况
				left_right_rotation(node);
			}
		}
	}
	else if (key > node->data)
	{
		//递归去寻找要插入的位置
		node->right = insert(node->right, key);
		//往右边插入 如果有失衡那么一定是右边失衡
		if (HEIGHT(node->right) - HEIGHT(node->left) == 2)
		{
			//判断属于哪一种情况
			//RR
			if (key > node->right->data)
			{
				right_right_rotation(node);
			}
			//RL
			else
			{
				right_left_rotation(node);
			}
		}
	}
	//重新调整二叉树的深度
	//树的深度取决于大的那一个
	//通过这个操作把每一个节点的高度都更新了 因为上面有递归访问了每一个节点
	node->height = MAX(getNode_Height(node->left), getNode_Height(node->right)) + 1;//插入了一个新节点 所以加1
	return node;
}