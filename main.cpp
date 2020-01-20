/*
	二叉查找树的C实现
(01) 若任意节点的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
(02) 任意节点的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
(03) 任意节点的左、右子树也分别为二叉查找树。
(04) 没有键值相等的节点（no duplicate nodes）。
*/


#include <stdio.h>
#include <assert.h>
#include <string>
#include <iostream>
#include "stack.h"

bool InsertBtree(Btree* root, Bnode* node) {
	Bnode* tmp = NULL;
	Bnode* parent = NULL;
	if (!node) {
		return false;
	}
	else {//清空新节点的左右子树
		node->lchild = NULL;
		node->rchild = NULL;
	}
	if (*root) {//存在根节点
		tmp = *root;
	}
	else { //不存在根节点
		*root = node;
		return true;
	}
	while (tmp != NULL) {
		parent = tmp;//保存父节点
		//printf("父节点： %d\n", parent->data);
		if (isLess(node->data, tmp->data)) {
			tmp = tmp->lchild;
		}
		else {
			tmp = tmp->rchild;
		}
	}

	if (isLess(node->data, parent->data)) {//找到空位置后，进行插入
		parent->lchild = node;
	}
	else {
		parent->rchild = node;
	}
	return true;
}

/************************
* 采用二叉搜索树上最大的结点

*************************/
int findMax(Btree& root)
{
	if (root->rchild == NULL) {
		return root->data;
	}
	return findMax(root->rchild);
}

/************************
* 采用递归方式查找结点
*************************/
Btree DeleteNode(Btree root, int key, Bnode* deletedNode) {
	if (root == NULL)return NULL;
	if (root->data > key)
	{
		root->lchild = DeleteNode(root->lchild, key, deletedNode);
		return root;
	}
	if (root->data < key)
	{
		root->rchild = DeleteNode(root->rchild, key, deletedNode);
		return root;
	}
	deletedNode = root;
	//删除节点不存在左右子节点，即为叶子节点，直接删除
	if (root->lchild == NULL && root->rchild == NULL)return NULL;
	//删除节点存在右子节点，直接用右子节点取代删除节点
	if (root->lchild == NULL && root->rchild != NULL)return root->rchild;
	//删除节点存在左子节点，直接用左子节点取代删除节点
	if (root->lchild != NULL && root->rchild == NULL)return root->lchild;
	////删除节点存在左右子节点，直接用左子节点最大值取代删除节点
	int val = findMax(root->lchild);
	root->data = val;
	root->lchild = DeleteNode(root->lchild, val, deletedNode);
	return root;
}
/************************
* 采用递归方式查找结点
*************************/
Bnode* QueryByRec(Btree root, ElemType e) {

	if (NULL == root || isEqual(root->data, e) ) {
		return root;
	}
	else if (isLess(e, root->data)) {
		return QueryByRec(root->lchild, e);
	}
	else {
		return QueryByRec(root->rchild, e);
	}
}

/**
* 使用非递归方式查找结点
*/
Bnode* QueryByLoop(Bnode* root, int e) {
	while (NULL != root && !isEqual(root->data, e)) {
		if (isLess(e, root->data)) {
			root = root->lchild;
		}
		else {
			root = root->rchild;
		}
	}
	return root;
}

/************************
* 采用递归方式实现前序遍历
*************************/
void PreOrderRec(Btree root)
{
	if (root == NULL)
	{
		return;
	}
	printf("- %d -", root->data);
	PreOrderRec(root->lchild);
	PreOrderRec(root->rchild);
}
/************************
* 借助栈实现前序遍历
*************************/
void PreOrder(Btree& root)
{
	Bnode cur;
	if (root == NULL)
	{
		return;
	}
	SqStack stack;
	InitStack(stack);
	PushStack(stack, *root); //头节点先入栈
	while (!(IsEmpty(stack))) //栈为空，所有节点均已处理
	{
		PopStack(stack, cur); //要遍历的节点
		printf("- %d -", cur.data);
		if (cur.rchild != NULL)
		{
			PushStack(stack, *(cur.rchild)); //右子节点先入栈，后处理
		}
		if (cur.lchild != NULL)
		{
			PushStack(stack, *(cur.lchild)); //左子节点后入栈，接下来先处理
		}
	}
	DestroyStack(stack);
}

int main(void) {
	int test[] = { 19, 7, 25, 5, 11, 15, 21, 61 };
	Bnode* root = NULL, * node = NULL;
	node = new Bnode;
	node->data = test[0];
	InsertBtree(&root, node);//插入根节点
	for (int i = 1; i < sizeof(test) / sizeof(test[0]); i++) {
		node = new Bnode;
		node->data = test[i];
		if (InsertBtree(&root, node)) {
			printf("节点 %d 插入成功\n", node->data);
		}
		else {
		}
	}
	printf("前序遍历结果： \n");
	PreOrderRec(root);
	printf("\n");
	system("pause");
	//二叉搜索树删除
	printf("删除节点 15\n");
	Bnode* deletedNode = NULL;
	root = DeleteNode(root, 15, deletedNode);
	printf("----------------------------------------\n");
	printf("二叉搜索树删除节点 15, %s\n", deletedNode ? "删除成功" : "删除不成功，节点不存在");
	if (deletedNode) delete deletedNode;
	printf("删除后，再次前序遍历结果： \n");
	PreOrderRec(root);
	printf("\n");
	printf("----------------------------------------\n");
	//二叉搜索树查找节点
	Bnode* node1 = QueryByRec(root, 20);
	printf("搜索二叉搜索树，节点 20 %s\n", node1 ? "存在" : "不存在");
	Bnode* node2 = QueryByLoop(root, 15);
	printf("搜索二叉搜索树，节点 1 %s\n", node2 ? "存在" : "不存在");
	system("pause");
	return 0;
}





