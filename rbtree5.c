//删除
rbtree_node *rbtree_delete(rbtree *T, rbtree_node *z) {

	rbtree_node *y = T->nil;
	rbtree_node *x = T->nil;

	if ((z->left == T->nil) || (z->right == T->nil)) {
		// 儿子节点没有孩子或者只有一个孩子，直接指向这个节点
		y = z;
	} else {
		// 儿子节点有两个孩子，用后继节点替换待删除的节点，问题转化为删除这个后继节点
		y = rbtree_successor(T, z);
	}

	// 如果儿子节点有独生子，那么这个独生子直接继承它爹的位置
	if (y->left != T->nil) {
		x = y->left;
	} else if (y->right != T->nil) {
		x = y->right;
	}

	// 调节继位节点的parent指针指向
	x->parent = y->parent;
	// 调节父节点的孩子指针指向
	if (y->parent == T->nil) {
		// 根节点将被删除，更新根节点
		T->root = x;
	} else if (y == y->parent->left) {
		y->parent->left = x;
	} else {
		y->parent->right = x;
	}
	
	// 如果y是右子树的最小节点，就将y放到z的位置，然后删除原来的z
	if (y != z) {
		z->key = y->key;
		z->value = y->value;
	}

	// 如果删除的节点是黑色的，就要维护一下红黑树的性质
	if (y->color == BLACK) {
		rbtree_delete_fixup(T, x);
	}

	return y;
}

// 找右子树中的最小节点
rbtree_node *rbtree_mini(rbtree *T, rbtree_node *x) {
	while (x->left != T->nil) {
		x = x->left;
	}
	return x;
}

// 找左子树中的最大节点
rbtree_node *rbtree_maxi(rbtree *T, rbtree_node *x) {
	while (x->right != T->nil) {
		x = x->right;
	}
	return x;
}

rbtree_node *rbtree_successor(rbtree *T, rbtree_node *x) {
	rbtree_node *y = x->parent;
	// 后继节点就是中序遍历时右子树的第一个节点
	if (x->right != T->nil) {
		return rbtree_mini(T, x->right);
	}

	// 这里应该不会被执行到，因为此时的待删除节点必然有两个孩子节点
	// 如果没有右子树，那就是作为左子树时的根节点
	while ((y != T->nil) && (x == y->right)) {
		x = y;
		y = y->parent;
	}
	return y;
}

