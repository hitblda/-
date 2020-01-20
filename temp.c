

bool InsertBtree(Btree* root, Bnode* node) //注意:Btree是二级指针
{
	//Btree* root是根节点,判断是否空树 
	//Bnode* node是待插入结点
	Bnode* parent = NULL;

	if (!node)
	{
		return false;
	}
	else
	{
		//清空新结点的左右树
		node->lchild = NULL;
		node->rchild = NULL;
	}

	if (*root==NULL)  //不存在根节点
	{
		*root = node;
		printf("根节点插入完成  ");
		return true;
	}
	else
	{
		parent = *root;//保存父节点
		while (parent != NULL)  //不是空树
		{
			/*
			约束条件:左儿子 < 父节点 < 右儿子
			*/
			if (isLess(node->data, parent->data)) //小于就进左儿子
			{
				if (parent->lchild == NULL)
				{
					parent->lchild = node;
					return true;
				}
				else //继续判断
				{
					parent = parent->lchild;
				}

			}
			else//否则进右儿子
			{
				if (parent->rchild == NULL)
				{
					parent->rchild = node;
					return true;
				}
				else
				{
					parent = parent->rchild;
				}

			}
		}
	}
	return true;
}

/*
* 采用二叉树搜索树上最大的结点
*/
int findMax(Btree root)
{	
	//if (!root) return NULL;
	assert(root != NULL);
	
#if 0
	//方法一:采用递归
	if (root->rchild == NULL)
	{
		return root->data;
	}
	return findMax(root->rchild);
#endif
	
	//方法二:采用循环
	while (root->rchild)
	{
		root = root->rchild;
	}
	return root->data;
}

/*
*采用递归查找结点
*/
Bnode* queryByRec(Btree root, ElemType e,int &num)
{
	if (isEqual(root->data,e)||NULL ==root) 
	{
		//没有搜到,或者正好就是
		return root;
	} 
	else if (isLess(e, root->data))
	{
		return queryByRec(root->lchild, e,num);
	}
	else
	{
		return queryByRec(root->rchild, e,num);
	}
	num++;
}

/*
* 采用非递归查找结点
*/
Bnode* queryByLoop(Btree root, ElemType e,int &num)
{

	while (root!= NULL)
	{
		if (root->data != e)
		{

			if (e < root->data)
			{
				root = root->lchild;
				printf("输入值 %d < %d !!\n", e, root->data);
			}
			else
			{
				root = root->rchild;
				printf("输入值 %d > %d !!\n", e, root->data);
			}
			
		}
		else if ( root->data == e)
		{
			printf("输入 %d 找到%d !!\n",e,root->data);
			return root;
		}
		(num)++;
	}

	return root;
}

//采用递归删除结点
Btree DeleteNode(Btree root, int key)
{
	if (root == NULL)
	{
		printf("没有下一项了 ........");
		return NULL;
	}

	if(root->data > key)
	{
		root->lchild = DeleteNode(root->lchild, key);
		return root;
	}
	else if (root->data < key)
	{
		root->rchild = DeleteNode(root->rchild, key);
		return root;
	}
	//else   //以下为等于key值的情形
	else
	{
		//删除结点不存在左右结点,即叶子结点,直接删除==>直接返回NULL
		if ((root->lchild == NULL) && (root->rchild == NULL))
		{
			printf("叶子结点 删除成功!! ");
			return NULL;
		}
		//删除结点存在右子节点,直接用右子节点取代
		else if ((root->lchild == NULL) && (root->rchild != NULL))
		{
			printf("有右节点的结点 删除成功!! ");
			return root->rchild;
		}
		//删除结点存在左子节点,直接用左子节点取代
		else if ((root->lchild != NULL) && (root->rchild == NULL))
		{
			printf("有左节点的结点 删除成功!! ");
			return root->lchild;
		}
		//删除结点存在左右结点,都存在,直接用左结点最大值取代\删除结点
		else
		{
			int val = findMax(root->lchild);
			root->data = val;
			root->lchild = DeleteNode(root->lchild, val);
			return root;
		}		
	}
}

///////////////////////////////////////////////////////////////////////////////
/* 查找最小结点：返回tree为根结点的二叉树的最小结点。
 */
//Bnode* bstree_minimum(Btree tree)
//{
//	if (tree == NULL)
//		return NULL;
//
//	while (tree->lchild != NULL)
//		tree = tree->lchild;
//	return tree;
//}
//
///*
// * 查找最大结点：返回tree为根结点的二叉树的最大结点。
// */
//Bnode* bstree_maximum(Btree tree)
//{
//	if (tree == NULL)
//		return NULL;
//
//	while (tree->rchild != NULL)
//		tree = tree->rchild;
//	return tree;
//}
//
///*
// * 找结点(x)的前驱结点。即，查找"二叉树中数据值小于该结点"的"最大结点"。
// */
//Bnode* bstree_predecessor(Bnode* x)
//{
//	// 如果x存在左孩子，则"x的前驱结点"为 "以其左孩子为根的子树的最大结点"。
//	if (x->lchild != NULL)
//		return bstree_maximum(x->lchild);
//
//	// 如果x没有左孩子。则x有以下两种可能：
//	// (01) x是"一个右孩子"，则"x的前驱结点"为 "它的父结点"。
//	// (01) x是"一个左孩子"，则查找"x的最低的父结点，并且该父结点要具有右孩子"，找到的这个"最低的父结点"就是"x的前驱结点"。
//	Bnode* y = x;
//	while ((y != NULL) && (x == y->lchild))
//	{
//		x = y;
//		;
//	}
//
//	return y;
//}
// /*
//  * 找结点(x)的后继结点。即，查找"二叉树中数据值大于该结点"的"最小结点"。
//  */
// Bnode * bstree_successor(Bnode* x)
// {
//	 
//	 // 如果x存在右孩子，则"x的后继结点"为 "以其右孩子为根的子树的最小结点"。
//	 if (x->rchild != NULL)
//	     return bstree_minimum(x->rchild);
//	
//	 // 如果x没有右孩子。则x有以下两种可能：
//	 // (01) x是"一个左孩子"，则"x的后继结点"为 "它的父结点"。
//	 // (02) x是"一个右孩子"，则查找"x的最低的父结点，并且该父结点要具有左孩子"，找到的这个"最低的父结点"就是"x的后继结点"。
//	 Bnode* y = x;
//	 while ((y != NULL) && (x == y->rchild))
//	 {
//	     x = y;
//	    // y = y->parent;
//	 }
//	
//	 return y;
// }
//
//static Btree bstree_delete(Bnode *tree, Btree z)
//{
//	Btree x = NULL;
//	Btree y = NULL;
//
//	if ((z->lchild == NULL) || (z->rchild == NULL))
//		y = z;
//	else
//		y = bstree_successor(z);
//
//	if (y->lchild != NULL)
//		x = y->lchild;
//	else
//		x = y->rchild;
//
//	if (x != NULL)
//		x  = y;
//
//	if (y  == NULL)
//		tree = x;
//	else if (y == y->lchild)
//		y->lchild = x;
//	else
//		y->rchild = x;
//
//	if (y != z)
//		//z->data = y->data;
//
//	if (y != NULL)
//		free(y);
//
//	return tree;
//}
/////////////////////////////////////////////////////

/*
*	二叉树的遍历
*/

/*
**前序遍历代码
若二叉树非空，则执行以下操作：
(01) 访问根结点；
(02) 先序遍历左子树；
(03) 先序遍历右子树。
*/
void preOrderRec(Btree root)  
{
	if (root == NULL)
	{
		return;
	}
	printf("-%d-", root->data);
	preOrderRec(root->lchild);
	preOrderRec(root->rchild);
}

/*
**中序遍历代码
若二叉树非空，则执行以下操作：
(01) 中序遍历左子树；
(02) 访问根结点；
(03) 中序遍历右子树。
*/
void inorder_bstree(Btree tree)  
{
	if (tree != NULL)
	{
		inorder_bstree(tree->lchild);
		printf("-%d-", tree->data);
		inorder_bstree(tree->rchild);
	}
}
/*
**后序遍历代码
若二叉树非空，则执行以下操作：
(01) 后序遍历左子树；
(02) 后序遍历右子树；
(03) 访问根结点。
*/
void postorder_bstree(Btree tree)
{
	if (tree != NULL)
	{
		postorder_bstree(tree->lchild);
		postorder_bstree(tree->rchild);
		printf("-%d-", tree->data);
	}
}


int main(void)
{
	int test[] = { 29,7,25,5,11,15,21,61,9,13 };
	int e = 0;
	Bnode* root = NULL, * node = NULL;
	printf("********************************************\n");
	int sT=0;

	for (int i=0;i<sizeof(test)/sizeof(test[0]);i++)
	{
		node = new Bnode;
		node->data = test[i];
		
		if (InsertBtree(&root,node))//插入树,1:根节点,2:插入的结点
		{
			printf("开始插入第%d个结点  ",i);
			printf("第%d个结点 数值 %d插入成功\n", i,node->data);
		}
		else
		{
			printf("第%d个结点%d插入BU成功!!!!!!!\n", i, node->data);
		}
	}
	printf("前序遍历结果:  \n");
	preOrderRec(root);
	printf("\n");

	printf("***********************************************\n");
	e = 35;
	if (queryByRec(root, e,sT) != NULL)
	{
		Bnode* node1 = queryByRec(root, e,sT);
		if (node1->data == e)
		{
			printf("queryByRec 结点  存在%d \n", node1->data);
			printf("查找的次数 %d\n", sT);
		}
		else
		{
			printf("queryByRec 结点%d 不存在\n", e);
			printf("查找的次数 %d\n", sT);
		}
	}
	if (queryByLoop(root, e,sT) !=NULL)
	{
		Bnode* node2 = queryByLoop(root, e,sT);
		if (node2->data == e)
		{
			printf("queryByLoop 结点 存在%d \n", node2->data);
			printf("查找的次数 %d\n", sT);
		}
		else
		{
			printf("queryByLoop 结点%d 不存在\n", e);
			printf("查找的次数 %d\n", sT);
		}
	}
	
	
	
	//
	////printf("queryByRec 结点15 %s\n", node1 ? "存在" : "不存在");

	//system("pause");

	//printf("前序遍历结果:  \n");
	//preOrderRec(root);
	//printf("\n");
	//printf("###############################################\n");

	//printf("删除结点 15 之后 .............................\n");
	//DeleteNode(root, e);
	//
	//printf("###############################################\n");
	//Bnode* node2 = queryByLoop(root, e);
	////printf("queryByLoop 15 %s\n", node2 ? "存在" : "不存在");
	//if (node2 == NULL)
	//{
	//	printf("queryByLoop 结点%d 不存在\n", e);
	//}
	//else
	//{
	//	printf("queryByLoop 结点%d 存在%d \n", e,node2->data);
	//}
	//system("pause");

	//printf("再次删除结点 15 之后 .............................\n");
	//DeleteNode(root, e);

	//printf("前序遍历结果:  \n");
	//preOrderRec(root);
	//printf("\n");
	//Bnode* node3 = queryByRec(root,e);
	//if (node3 == NULL)
	//{
	//	printf("queryByRec 结点%d 不存在\n", e);
	//}
	//else
	//{
	//	printf("queryByRec 结点%d 存在%d \n", e, node3->data);;
	//}
	//printf("###################退出#####################\n");

}