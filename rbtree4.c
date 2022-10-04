//插入
void rbtree_insert(rbtree *T, rbtree_node *z) {
	
	// 使用快慢指针遍历红黑树，慢指针是快指针的父亲
	rbtree_node *y = T->nil;
	rbtree_node *x = T->root;

	while (x != T->nil) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		} else if (z->key > x->key) {
			x = x->right;
		} else { // 已经存在key为z->key的节点，直接返回
			return ;
		}
	}

	z->parent = y;
	// 原来的树为空，新插入的节点作为根节点
	if (y == T->nil) {
		T->root = z;
	} else if (z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}

	z->left = T->nil;
	z->right = T->nil;
	// 新插入的节点默认是红色
	z->color = RED;

	// 维护红黑树的性质
	rbtree_insert_fixup(T, z);
}
