#ifndef __NODE_H__
#define __NODE_H__

using namespace std;
#include <iostream>
// �����
template <class ElemType>
struct Node 
{
// ���ݳ�Ա:
protected:
	ElemType data;				// ������
	Node<ElemType> *next;		// ָ����

// ���캯��:
public:
	Node();						// �޲����Ĺ��캯��
	Node(ElemType item, Node<ElemType> *link = NULL);	// ��֪������Ԫ��ֵ��ָ�뽨���ṹ
};

// ������ʵ�ֲ���
template<class ElemType>
Node<ElemType>::Node()
// �������������ָ����Ϊ�յĽ��
{
   next = NULL;
}

template<class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType> *link)
// �������������һ��������Ϊitem��ָ����Ϊlink�Ľ��
{
   data = item;
   next = link;
}

#endif