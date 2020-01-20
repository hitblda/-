

bool InsertBtree(Btree* root, Bnode* node) //ע��:Btree�Ƕ���ָ��
{
	//Btree* root�Ǹ��ڵ�,�ж��Ƿ���� 
	//Bnode* node�Ǵ�������
	Bnode* parent = NULL;

	if (!node)
	{
		return false;
	}
	else
	{
		//����½���������
		node->lchild = NULL;
		node->rchild = NULL;
	}

	if (*root==NULL)  //�����ڸ��ڵ�
	{
		*root = node;
		printf("���ڵ�������  ");
		return true;
	}
	else
	{
		parent = *root;//���游�ڵ�
		while (parent != NULL)  //���ǿ���
		{
			/*
			Լ������:����� < ���ڵ� < �Ҷ���
			*/
			if (isLess(node->data, parent->data)) //С�ھͽ������
			{
				if (parent->lchild == NULL)
				{
					parent->lchild = node;
					return true;
				}
				else //�����ж�
				{
					parent = parent->lchild;
				}

			}
			else//������Ҷ���
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
* ���ö����������������Ľ��
*/
int findMax(Btree root)
{	
	//if (!root) return NULL;
	assert(root != NULL);
	
#if 0
	//����һ:���õݹ�
	if (root->rchild == NULL)
	{
		return root->data;
	}
	return findMax(root->rchild);
#endif
	
	//������:����ѭ��
	while (root->rchild)
	{
		root = root->rchild;
	}
	return root->data;
}

/*
*���õݹ���ҽ��
*/
Bnode* queryByRec(Btree root, ElemType e,int &num)
{
	if (isEqual(root->data,e)||NULL ==root) 
	{
		//û���ѵ�,�������þ���
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
* ���÷ǵݹ���ҽ��
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
				printf("����ֵ %d < %d !!\n", e, root->data);
			}
			else
			{
				root = root->rchild;
				printf("����ֵ %d > %d !!\n", e, root->data);
			}
			
		}
		else if ( root->data == e)
		{
			printf("���� %d �ҵ�%d !!\n",e,root->data);
			return root;
		}
		(num)++;
	}

	return root;
}

//���õݹ�ɾ�����
Btree DeleteNode(Btree root, int key)
{
	if (root == NULL)
	{
		printf("û����һ���� ........");
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
	//else   //����Ϊ����keyֵ������
	else
	{
		//ɾ����㲻�������ҽ��,��Ҷ�ӽ��,ֱ��ɾ��==>ֱ�ӷ���NULL
		if ((root->lchild == NULL) && (root->rchild == NULL))
		{
			printf("Ҷ�ӽ�� ɾ���ɹ�!! ");
			return NULL;
		}
		//ɾ�����������ӽڵ�,ֱ�������ӽڵ�ȡ��
		else if ((root->lchild == NULL) && (root->rchild != NULL))
		{
			printf("���ҽڵ�Ľ�� ɾ���ɹ�!! ");
			return root->rchild;
		}
		//ɾ�����������ӽڵ�,ֱ�������ӽڵ�ȡ��
		else if ((root->lchild != NULL) && (root->rchild == NULL))
		{
			printf("����ڵ�Ľ�� ɾ���ɹ�!! ");
			return root->lchild;
		}
		//ɾ�����������ҽ��,������,ֱ�����������ֵȡ��\ɾ�����
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
/* ������С��㣺����treeΪ�����Ķ���������С��㡣
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
// * ��������㣺����treeΪ�����Ķ�����������㡣
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
// * �ҽ��(x)��ǰ����㡣��������"������������ֵС�ڸý��"��"�����"��
// */
//Bnode* bstree_predecessor(Bnode* x)
//{
//	// ���x�������ӣ���"x��ǰ�����"Ϊ "��������Ϊ���������������"��
//	if (x->lchild != NULL)
//		return bstree_maximum(x->lchild);
//
//	// ���xû�����ӡ���x���������ֿ��ܣ�
//	// (01) x��"һ���Һ���"����"x��ǰ�����"Ϊ "���ĸ����"��
//	// (01) x��"һ������"�������"x����͵ĸ���㣬���Ҹø����Ҫ�����Һ���"���ҵ������"��͵ĸ����"����"x��ǰ�����"��
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
//  * �ҽ��(x)�ĺ�̽�㡣��������"������������ֵ���ڸý��"��"��С���"��
//  */
// Bnode * bstree_successor(Bnode* x)
// {
//	 
//	 // ���x�����Һ��ӣ���"x�ĺ�̽��"Ϊ "�����Һ���Ϊ������������С���"��
//	 if (x->rchild != NULL)
//	     return bstree_minimum(x->rchild);
//	
//	 // ���xû���Һ��ӡ���x���������ֿ��ܣ�
//	 // (01) x��"һ������"����"x�ĺ�̽��"Ϊ "���ĸ����"��
//	 // (02) x��"һ���Һ���"�������"x����͵ĸ���㣬���Ҹø����Ҫ��������"���ҵ������"��͵ĸ����"����"x�ĺ�̽��"��
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
*	�������ı���
*/

/*
**ǰ���������
���������ǿգ���ִ�����²�����
(01) ���ʸ���㣻
(02) ���������������
(03) ���������������
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
**�����������
���������ǿգ���ִ�����²�����
(01) ���������������
(02) ���ʸ���㣻
(03) ���������������
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
**�����������
���������ǿգ���ִ�����²�����
(01) ���������������
(02) ���������������
(03) ���ʸ���㡣
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
		
		if (InsertBtree(&root,node))//������,1:���ڵ�,2:����Ľ��
		{
			printf("��ʼ�����%d�����  ",i);
			printf("��%d����� ��ֵ %d����ɹ�\n", i,node->data);
		}
		else
		{
			printf("��%d�����%d����BU�ɹ�!!!!!!!\n", i, node->data);
		}
	}
	printf("ǰ��������:  \n");
	preOrderRec(root);
	printf("\n");

	printf("***********************************************\n");
	e = 35;
	if (queryByRec(root, e,sT) != NULL)
	{
		Bnode* node1 = queryByRec(root, e,sT);
		if (node1->data == e)
		{
			printf("queryByRec ���  ����%d \n", node1->data);
			printf("���ҵĴ��� %d\n", sT);
		}
		else
		{
			printf("queryByRec ���%d ������\n", e);
			printf("���ҵĴ��� %d\n", sT);
		}
	}
	if (queryByLoop(root, e,sT) !=NULL)
	{
		Bnode* node2 = queryByLoop(root, e,sT);
		if (node2->data == e)
		{
			printf("queryByLoop ��� ����%d \n", node2->data);
			printf("���ҵĴ��� %d\n", sT);
		}
		else
		{
			printf("queryByLoop ���%d ������\n", e);
			printf("���ҵĴ��� %d\n", sT);
		}
	}
	
	
	
	//
	////printf("queryByRec ���15 %s\n", node1 ? "����" : "������");

	//system("pause");

	//printf("ǰ��������:  \n");
	//preOrderRec(root);
	//printf("\n");
	//printf("###############################################\n");

	//printf("ɾ����� 15 ֮�� .............................\n");
	//DeleteNode(root, e);
	//
	//printf("###############################################\n");
	//Bnode* node2 = queryByLoop(root, e);
	////printf("queryByLoop 15 %s\n", node2 ? "����" : "������");
	//if (node2 == NULL)
	//{
	//	printf("queryByLoop ���%d ������\n", e);
	//}
	//else
	//{
	//	printf("queryByLoop ���%d ����%d \n", e,node2->data);
	//}
	//system("pause");

	//printf("�ٴ�ɾ����� 15 ֮�� .............................\n");
	//DeleteNode(root, e);

	//printf("ǰ��������:  \n");
	//preOrderRec(root);
	//printf("\n");
	//Bnode* node3 = queryByRec(root,e);
	//if (node3 == NULL)
	//{
	//	printf("queryByRec ���%d ������\n", e);
	//}
	//else
	//{
	//	printf("queryByRec ���%d ����%d \n", e, node3->data);;
	//}
	//printf("###################�˳�#####################\n");

}