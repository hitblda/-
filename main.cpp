/*
	�����������Cʵ��
(01) ������ڵ�����������գ��������������н���ֵ��С�����ĸ�����ֵ��
(02) ����ڵ�����������գ��������������н���ֵ���������ĸ�����ֵ��
(03) ����ڵ����������Ҳ�ֱ�Ϊ�����������
(04) û�м�ֵ��ȵĽڵ㣨no duplicate nodes����
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
	else {//����½ڵ����������
		node->lchild = NULL;
		node->rchild = NULL;
	}
	if (*root) {//���ڸ��ڵ�
		tmp = *root;
	}
	else { //�����ڸ��ڵ�
		*root = node;
		return true;
	}
	while (tmp != NULL) {
		parent = tmp;//���游�ڵ�
		//printf("���ڵ㣺 %d\n", parent->data);
		if (isLess(node->data, tmp->data)) {
			tmp = tmp->lchild;
		}
		else {
			tmp = tmp->rchild;
		}
	}

	if (isLess(node->data, parent->data)) {//�ҵ���λ�ú󣬽��в���
		parent->lchild = node;
	}
	else {
		parent->rchild = node;
	}
	return true;
}

/************************
* ���ö��������������Ľ��

*************************/
int findMax(Btree& root)
{
	if (root->rchild == NULL) {
		return root->data;
	}
	return findMax(root->rchild);
}

/************************
* ���õݹ鷽ʽ���ҽ��
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
	//ɾ���ڵ㲻���������ӽڵ㣬��ΪҶ�ӽڵ㣬ֱ��ɾ��
	if (root->lchild == NULL && root->rchild == NULL)return NULL;
	//ɾ���ڵ�������ӽڵ㣬ֱ�������ӽڵ�ȡ��ɾ���ڵ�
	if (root->lchild == NULL && root->rchild != NULL)return root->rchild;
	//ɾ���ڵ�������ӽڵ㣬ֱ�������ӽڵ�ȡ��ɾ���ڵ�
	if (root->lchild != NULL && root->rchild == NULL)return root->lchild;
	////ɾ���ڵ���������ӽڵ㣬ֱ�������ӽڵ����ֵȡ��ɾ���ڵ�
	int val = findMax(root->lchild);
	root->data = val;
	root->lchild = DeleteNode(root->lchild, val, deletedNode);
	return root;
}
/************************
* ���õݹ鷽ʽ���ҽ��
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
* ʹ�÷ǵݹ鷽ʽ���ҽ��
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
* ���õݹ鷽ʽʵ��ǰ�����
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
* ����ջʵ��ǰ�����
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
	PushStack(stack, *root); //ͷ�ڵ�����ջ
	while (!(IsEmpty(stack))) //ջΪ�գ����нڵ���Ѵ���
	{
		PopStack(stack, cur); //Ҫ�����Ľڵ�
		printf("- %d -", cur.data);
		if (cur.rchild != NULL)
		{
			PushStack(stack, *(cur.rchild)); //���ӽڵ�����ջ������
		}
		if (cur.lchild != NULL)
		{
			PushStack(stack, *(cur.lchild)); //���ӽڵ����ջ���������ȴ���
		}
	}
	DestroyStack(stack);
}

int main(void) {
	int test[] = { 19, 7, 25, 5, 11, 15, 21, 61 };
	Bnode* root = NULL, * node = NULL;
	node = new Bnode;
	node->data = test[0];
	InsertBtree(&root, node);//������ڵ�
	for (int i = 1; i < sizeof(test) / sizeof(test[0]); i++) {
		node = new Bnode;
		node->data = test[i];
		if (InsertBtree(&root, node)) {
			printf("�ڵ� %d ����ɹ�\n", node->data);
		}
		else {
		}
	}
	printf("ǰ���������� \n");
	PreOrderRec(root);
	printf("\n");
	system("pause");
	//����������ɾ��
	printf("ɾ���ڵ� 15\n");
	Bnode* deletedNode = NULL;
	root = DeleteNode(root, 15, deletedNode);
	printf("----------------------------------------\n");
	printf("����������ɾ���ڵ� 15, %s\n", deletedNode ? "ɾ���ɹ�" : "ɾ�����ɹ����ڵ㲻����");
	if (deletedNode) delete deletedNode;
	printf("ɾ�����ٴ�ǰ���������� \n");
	PreOrderRec(root);
	printf("\n");
	printf("----------------------------------------\n");
	//�������������ҽڵ�
	Bnode* node1 = QueryByRec(root, 20);
	printf("�����������������ڵ� 20 %s\n", node1 ? "����" : "������");
	Bnode* node2 = QueryByLoop(root, 15);
	printf("�����������������ڵ� 1 %s\n", node2 ? "����" : "������");
	system("pause");
	return 0;
}





