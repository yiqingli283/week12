#define HEIGHT(node) ((node == NULL) ? 0 : (((avlnode*)(node))->height))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
//获取节点高度
int getNode_Height(avlnode* node)
{
	return HEIGHT(node);
}
 
//右旋LL
avltree left_left_rotation(avltree node)//node是失衡节点
{
	avlnode* k2 = node->left;
	node->left = k2->right;
	k2->right = node;
	//所有的旋转操作都要改变树的高度
	node->height = MAX(getNode_Height(node->left), getNode_Height(node->right)) + 1;
	k2->height = MAX(getNode_Height(node->left), getNode_Height(node->right)) + 1;
	return k2;
}
 
//左旋RR
avltree right_right_rotation(avltree node)//node是失衡节点
{
	avlnode* k2 = node->right;
	node->right = k2->left;
	k2->left = node;
	//所有的旋转操作都要改变树的高度
	node->height = MAX(getNode_Height(node->left), getNode_Height(node->right)) + 1;
	k2->height = MAX(getNode_Height(node->left), getNode_Height(node->right)) + 1;
	return k2;
}
 
//先左旋再右旋LR
avltree left_right_rotation(avltree node)
{
	node->left = right_right_rotation(node->left);
	node = left_left_rotation(node);
	return node;
}
 
//先右旋再左旋RL
avltree right_left_rotation(avltree node)
{
	node->right = left_left_rotation(node->right);
	node = right_right_rotation(node);
	return node;
}