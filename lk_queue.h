#ifndef __LK_QUEUE_H__
#define __LK_QUEUE_H__

#include "node.h"				// �����
#include <iostream>
#include "assistance.h"

// ��������

template<class ElemType>
class LinkQueue 
{
protected:
//  ������ʵ�ֵ����ݳ�Ա:
	Node<ElemType> *front, *rear;					// ��ͷ��βָָ

public:
	LinkQueue();									// �޲����Ĺ��캯��
	virtual ~LinkQueue();							// ��������
	int Length() const;								// ����г���			 
	bool Empty() const;								// �ж϶����Ƿ�Ϊ��
	void Clear();									// ���������
	void Traverse(void (*Visit)(const ElemType &)) const ;	// ��������
	Status DelQueue(ElemType &e);				// ���Ӳ���
	Status GetHead(ElemType &e) const;			// ȡ��ͷ����
	Status EnQueue(const ElemType &e);			// ��Ӳ���
	LinkQueue(const LinkQueue<ElemType> &copy);		// ���ƹ��캯��
	LinkQueue<ElemType> &operator =(const LinkQueue<ElemType> &copy);// ��ֵ�������
};

// ���������ʵ�ֲ���

template<class ElemType>
LinkQueue<ElemType>::LinkQueue()
// �������������һ���ն���
{
	rear = front = new Node<ElemType>;	// ����ͷ���
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue()
// ������������ٶ���
{
	Clear();		
}

template<class ElemType>
int LinkQueue<ElemType>::Length() const
// ������������ض��г���			 
{
	int count = 0;		// ������ 
	for (Node<ElemType> *Ptr = front->next; Ptr != NULL; Ptr = Ptr->next)
		count++;		// ��ջÿ��Ԫ�ؽ��м���
	return count;
}

template<class ElemType>
bool LinkQueue<ElemType>::Empty() const
// ��������������Ϊ�գ��򷵻�true�����򷵻�false
{
   return rear == front;
}

template<class ElemType>
void LinkQueue<ElemType>::Clear() 
// �����������ն���
{
	ElemType Elem;	// ��ʱԪ��ֵ
	while (Length() > 0)	{	// ���зǿգ������
		DelQueue(Elem);
	}
}

template <class ElemType>
void LinkQueue<ElemType>::Traverse(void (*Visit)(const ElemType &)) const 
// ������������ζԶ��е�ÿ��Ԫ�ص��ú���(*visit)
{
	for (Node<ElemType> *Ptr = front->next; Ptr != NULL; Ptr = Ptr->next)
	{	// �Զ���ÿ��Ԫ�ص��ú���(*visit)
		(*Visit)(Ptr->data);
	}
}


template<class ElemType>
Status LinkQueue<ElemType>::DelQueue(ElemType &e)
// ���������������зǿգ���ôɾ����ͷԪ�أ�����e������ֵ����������SUCCESS,
//	����������UNDER_FLOW��
{
	if (!Empty()) 	{	// ���зǿ�
		Node<ElemType> *Ptr = front->next;	// ָ�����ͷ��
		e = Ptr->data;						// ��e���ض�ͷԪ��
		front->next = Ptr->next;				// frontָ����һԪ��
		if (rear == Ptr){	// ��ʾ����ǰ������ֻ��һ��Ԫ�أ����Ӻ�Ϊ�ն���
			rear = front;
		}
		delete Ptr;							// �ͷų��ӵĽ��
		return SUCCESS;
	}
	else
		return UNDER_FLOW;
}

template<class ElemType>
Status LinkQueue<ElemType>::GetHead(ElemType &e) const
// ���������������зǿգ���ô��e���ض�ͷԪ�أ���������SUCCESS,
//	����������UNDER_FLOW��
{
	if (!Empty()) 	{	// ���зǿ�
		e = front->next->data;		// ��e���ض�ͷԪ��
		return SUCCESS;
	}
	else
		return UNDER_FLOW;
}

template<class ElemType>
Status LinkQueue<ElemType>::EnQueue(const ElemType &e)
// �������������Ԫ��eΪ�µĶ�β������SUCCESS
{
	Node<ElemType> *Ptr = new Node<ElemType>(e);	// �����½��
	rear->next = Ptr;							// �½��׷���ڶ�β
	rear = Ptr;									// rearָ���¶�β
	return SUCCESS;
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy)
// ����������ɶ���copy�����¶���--���ƹ��캯��
{
	rear = front = new Node<ElemType>;	// ����ͷ���
	for (Node<ElemType> *Ptr = copy.front->next; Ptr != NULL; Ptr = Ptr->next)
	{	// ��copy����ÿ��Ԫ�ضԵ�ǰ����������в���
		EnQueue(Ptr->data);
	}
}

template<class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator =(const LinkQueue<ElemType> &copy)
// ���������������copy��ֵ����ǰ����--��ֵ�������
{
	if (&copy != this)
	{
		Clear();
		for (Node<ElemType> *Ptr = copy.front->next; Ptr != NULL; Ptr = Ptr->next)
		{	// ��copy����ÿ��Ԫ�ضԵ�ǰ����������в���
			EnQueue(Ptr->data);
		}
	}
	return *this;
}

#endif
