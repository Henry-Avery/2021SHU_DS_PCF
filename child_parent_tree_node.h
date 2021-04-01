#ifndef __CHILD_PARENT_TREE_NODE_H__
#define __CHILD_PARENT_TREE_NODE_H__

#include "node.h"				// ��������
#include <iostream>

// ����˫����ʾ�������
template <class ElemType>
struct ChildParentTreeNode 
{
// ���ݳ�Ա:
	ElemType data;					// ������
	Node<int> *childLkList;		    // ��������	
	int parent;						// ˫��λ���򣬸�����ʾ�ýڵ���ĳ�����ĸ��ڵ�
									//��-n��Ӧ��n����㣩
									//���ýڵ�parent��Ҳ�Ǹ�������ʾ����ɭ������һ����


// ���캯��:
	ChildParentTreeNode();			// �޲����Ĺ��캯��
	ChildParentTreeNode(ElemType item, int pt = -1, Node<int> *childlk = NULL);// ��֪������ֵ��˫��λ�ý����ṹ
};

// ����˫����ʾ��������ʵ�ֲ���
template<class ElemType>
ChildParentTreeNode<ElemType>::ChildParentTreeNode()
// �������������˫����Ϊ-1�Ľ��
{
	parent = -1;
	childLkList = NULL;
}

template<class ElemType>
ChildParentTreeNode<ElemType>::ChildParentTreeNode(ElemType item, int pt, Node<int> *childlk)
// �������������һ��������Ϊitem��˫����Ϊpt�Ľ��
{
	data = item;					// ����Ԫ��ֵ
	parent = pt;					// ˫��
	childLkList = childlk;	
}

#endif