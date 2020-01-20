#pragma once
#ifndef __TREE_H__
#define __TREE_H__

#define MAX_NODE 1024
#define isLess(a,b) (a<b)
#define isEqual(a,b) (a==b)

typedef int ElemType;
typedef struct _Bnode {
	ElemType data;   // ¹Ø¼ü×Ö(¼üÖµ)
	struct _Bnode *lchild, *rchild;
}Bnode,*Btree;

#endif