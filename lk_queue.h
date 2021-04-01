#ifndef __LK_QUEUE_H__
#define __LK_QUEUE_H__

#include "node.h"				// 结点类
#include <iostream>
#include "assistance.h"

// 链队列类

template<class ElemType>
class LinkQueue 
{
protected:
//  链队列实现的数据成员:
	Node<ElemType> *front, *rear;					// 队头队尾指指

public:
	LinkQueue();									// 无参数的构造函数
	virtual ~LinkQueue();							// 析构函数
	int Length() const;								// 求队列长度			 
	bool Empty() const;								// 判断队列是否为空
	void Clear();									// 将队列清空
	void Traverse(void (*Visit)(const ElemType &)) const ;	// 遍历队列
	Status DelQueue(ElemType &e);				// 出队操作
	Status GetHead(ElemType &e) const;			// 取队头操作
	Status EnQueue(const ElemType &e);			// 入队操作
	LinkQueue(const LinkQueue<ElemType> &copy);		// 复制构造函数
	LinkQueue<ElemType> &operator =(const LinkQueue<ElemType> &copy);// 赋值语句重载
};

// 链队列类的实现部分

template<class ElemType>
LinkQueue<ElemType>::LinkQueue()
// 操作结果：构造一个空队列
{
	rear = front = new Node<ElemType>;	// 生成头结点
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue()
// 操作结果：销毁队列
{
	Clear();		
}

template<class ElemType>
int LinkQueue<ElemType>::Length() const
// 操作结果：返回队列长度			 
{
	int count = 0;		// 计数器 
	for (Node<ElemType> *Ptr = front->next; Ptr != NULL; Ptr = Ptr->next)
		count++;		// 对栈每个元素进行计数
	return count;
}

template<class ElemType>
bool LinkQueue<ElemType>::Empty() const
// 操作结果：如队列为空，则返回true，否则返回false
{
   return rear == front;
}

template<class ElemType>
void LinkQueue<ElemType>::Clear() 
// 操作结果：清空队列
{
	ElemType Elem;	// 临时元素值
	while (Length() > 0)	{	// 队列非空，则出列
		DelQueue(Elem);
	}
}

template <class ElemType>
void LinkQueue<ElemType>::Traverse(void (*Visit)(const ElemType &)) const 
// 操作结果：依次对队列的每个元素调用函数(*visit)
{
	for (Node<ElemType> *Ptr = front->next; Ptr != NULL; Ptr = Ptr->next)
	{	// 对队列每个元素调用函数(*visit)
		(*Visit)(Ptr->data);
	}
}


template<class ElemType>
Status LinkQueue<ElemType>::DelQueue(ElemType &e)
// 操作结果：如果队列非空，那么删除队头元素，并用e返回其值，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
	if (!Empty()) 	{	// 队列非空
		Node<ElemType> *Ptr = front->next;	// 指向队列头素
		e = Ptr->data;						// 用e返回队头元素
		front->next = Ptr->next;				// front指向下一元素
		if (rear == Ptr){	// 表示出队前队列中只有一个元素，出队后为空队列
			rear = front;
		}
		delete Ptr;							// 释放出队的结点
		return SUCCESS;
	}
	else
		return UNDER_FLOW;
}

template<class ElemType>
Status LinkQueue<ElemType>::GetHead(ElemType &e) const
// 操作结果：如果队列非空，那么用e返回队头元素，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
	if (!Empty()) 	{	// 队列非空
		e = front->next->data;		// 用e返回队头元素
		return SUCCESS;
	}
	else
		return UNDER_FLOW;
}

template<class ElemType>
Status LinkQueue<ElemType>::EnQueue(const ElemType &e)
// 操作结果：插入元素e为新的队尾，返回SUCCESS
{
	Node<ElemType> *Ptr = new Node<ElemType>(e);	// 生成新结点
	rear->next = Ptr;							// 新结点追加在队尾
	rear = Ptr;									// rear指向新队尾
	return SUCCESS;
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy)
// 操作结果：由队列copy构造新队列--复制构造函数
{
	rear = front = new Node<ElemType>;	// 生成头结点
	for (Node<ElemType> *Ptr = copy.front->next; Ptr != NULL; Ptr = Ptr->next)
	{	// 对copy队列每个元素对当前队列作入队列操作
		EnQueue(Ptr->data);
	}
}

template<class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator =(const LinkQueue<ElemType> &copy)
// 操作结果：将队列copy赋值给当前队列--赋值语句重载
{
	if (&copy != this)
	{
		Clear();
		for (Node<ElemType> *Ptr = copy.front->next; Ptr != NULL; Ptr = Ptr->next)
		{	// 对copy队列每个元素对当前队列作入队列操作
			EnQueue(Ptr->data);
		}
	}
	return *this;
}

#endif
