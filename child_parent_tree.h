#ifndef __CHILD_PARENT_TREE_H__
#define __CHILD_PARENT_TREE_H__

#include "lk_queue.h"				// ������
#include "child_parent_tree_node.h"	// ����˫�ױ�ʾ�������
#include "assistance.h"

// ����˫�ױ�ʾ����
template <class ElemType>
class ChildParentTree
{
protected:
//  �������ݳ�Ա:
	ChildParentTreeNode<ElemType> *nodes;			// �洢�����
	int maxSize;									// ����������� 
	int root, num;									// ����λ�ü������

//	��������:
	void PreRootOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// �ȸ������
	void PostRootOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// ��������
	int HeightHelp(int r) const;					// ������rΪ���ĸ�
	int DegreeHelp(int r) const;					// ������rΪ�������Ķ�

public:
//  ���������������ر���ϵͳĬ�Ϸ�������:
	ChildParentTree();								// �޲ι��캯��
	virtual ~ChildParentTree();						// ��������
	int GetRoot() const;							// �������ĸ�
	bool Empty() const;								// �ж����Ƿ�Ϊ��
	Status GetElem(int cur, ElemType &e) const;	// ��e���ؽ��Ԫ��ֵ
	Status SetElem(int cur, const ElemType &e);	// ����cur��ֵ��Ϊe
	void PreRootOrder(void (*Visit)(const ElemType &)) const;	// �����������
	void PostRootOrder(void (*Visit)(const ElemType &)) const;	// ���ĺ������
	void LevelOrder(void (*Visit)(const ElemType &)) const;		// ���Ĳ�α���
	int NodeCount() const;							// �������Ľ�����
	int NodeDegree(int cur) const;					// ���ؽ��cur�Ķ�
	int Degree() const;								// �������Ķ�
	int FirstChild(int cur) const;					// ���ؽ��cur�ĵ�һ������
	int RightSibling(int cur) const;				// ���ؽ��cur�����ֵ�
	int Parent(int cur) const;						// ���ؽ��cur��˫��
	Status InsertChild(int cur, int i, const ElemType &e);	
		// ������Ԫ�ز���Ϊcur�ĵ�i������
	int	Height() const;								// �������ĸ�
	ChildParentTree(const ElemType &e, int size = DEFAULT_SIZE);
		// ����������Ԫ��eΪ������
	ChildParentTree(ElemType items[], int parents[], int r, int n, int size = DEFAULT_SIZE);
		// ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn����
};

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildParentTree<ElemType> &t, int r, int level);
	// �������ʾ����ʾ����levelΪ�������������Ĳ����Ϊ1
template <class ElemType>
void DisplayTWithConcaveShape(const ChildParentTree<ElemType> &t);
	// �������ʾ����ʾ��

// ����˫�ױ�ʾ�����ʵ�ֲ���
template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree()
// �������������һ������
{
	maxSize = DEFAULT_SIZE;								// �����������
	nodes = new ChildParentTreeNode<ElemType>[maxSize];	// ����洢�ռ�
	root = -1;											// ��ʾ�����ڸ�
	num = 0;											// �����Ľ�����Ϊ0
}

template <class ElemType>
ChildParentTree<ElemType>::~ChildParentTree()
// ����������ͷŴ洢�ռ�
{
    Node<int> *p;
    for (int n = 0; n < num; n++) {
       p = nodes[n].childLkList;
       while ( p!= NULL) {
          nodes[n].childLkList = p->next;
          delete p;
          p = nodes[n].childLkList;
       }
    }   
	delete []nodes;										// �ͷŴ洢�ռ�
}



template <class ElemType>
int ChildParentTree<ElemType>::GetRoot() const
// ����������������ĸ�
{
	return root;
}

template <class ElemType>
bool ChildParentTree<ElemType>::Empty() const
// ����������ж����Ƿ�Ϊ��
{
	return num == 0;
}

template <class ElemType>
Status ChildParentTree<ElemType>::GetElem(int cur, ElemType &e) const
// �����������e���ؽ��curԪ��ֵ,��������ڽ��cur,��������NOT_PRESENT,���򷵻�ENTRY_FOUND
{
	if (cur < 0 || cur >= num)		// �����ڽ��cur
		return NOT_PRESENT;			// ����NOT_PRESENT
	else {	                        // ���ڽ��cur
		e = nodes[cur].data;		// ��e����Ԫ��ֵ
		return ENTRY_FOUND;			// ����ENTRY_FOUND
	}
}

template <class ElemType>
Status ChildParentTree<ElemType>::SetElem(int cur, const ElemType &e)
// �����������������ڽ��cur,�򷵻�FAIL,���򷵻�SUCCESS,�������cur��ֵ����Ϊe
{
	if (cur < 0 || cur >= num)		// �����ڽ��cur
		return FAIL;				// ����FAIL
	else	{	                    // ���ڽ��cur
		nodes[cur].data = e;		// �����cur��ֵ����Ϊe
		return SUCCESS;	  		    // ����SUCCESS
	}
}

template <class ElemType>
int ChildParentTree<ElemType>::NodeCount() const
// ����������������Ľ�����
{
	return num;
}

template <class ElemType>
int ChildParentTree<ElemType>::FirstChild(int cur) const
// �����������cur�޺���,�򷵻�-1,���򷵻������cur�ĵ�һ������,
{
    Node<int> *p;
	if (cur < 0 || cur >= num)	
		return -1;						// ���cur������,����-1��ʾ�޺���
	
	if (nodes[cur].childLkList == NULL)	// �޺���
		return -1;
	else
		return nodes[cur].childLkList->data;	// ȡ����һ������
}

template <class ElemType>
int ChildParentTree<ElemType>::RightSibling(int cur) const
// ���������������cur�����ֵ�,�򷵻�-1,���򷵻�cur�����ֵ�
{
	if (cur < 0 || cur >= num)						
		return -1;						// ���cur������,����-1��ʾ�޺���

	int pt = nodes[cur].parent;			// cur��˫��
    Node<int> * p = nodes[pt].childLkList;
    while (p != NULL && p->data != cur)
       p = p->next;
    if ( p == NULL || p->next == NULL)
		return -1;				// �������ֵ�
	else
		return p->next->data;	// ��ʾ�����ֵ�
}

template <class ElemType>
int ChildParentTree<ElemType>::Parent(int cur) const
// ������������������cur��˫��
{
	if (cur < 0 || cur >= num)						
		return -1;						// ���cur������,����-1��ʾ��˫��
	return nodes[cur].parent;
}

template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree(ElemType items[], int parents[], int r, int n, int size)
// �����������������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn����
{
	maxSize = size;													// ��������
	if (n > maxSize)	
	    throw Error("������̫��!");								// �׳��쳣
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// ����洢�ռ�
	for (int pos = 0; pos < n; pos++)
	{	// ���ζԽ������Ԫ�ؼ�˫��λ�ý��и�ֵ
		nodes[pos].data = items[pos];								// ����Ԫ��ֵ
		nodes[pos].parent = parents[pos];							// ˫��λ��
		if (parents[pos] != -1)		{
           Node<int> *p, *newnode;
	       newnode = new Node<int>(pos, NULL);
	       if (nodes[parents[pos]].childLkList == NULL)
	          nodes[parents[pos]].childLkList = newnode;
           else {
              p =  nodes[parents[pos]].childLkList;  
	          while (p->next != NULL)
	             p = p->next;
	          p->next = newnode;
            }   
		}
	}
	root = r;														// ��
	num = n;														// ������
}

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildParentTree<ElemType> &t, int r, int level)
// ����������������ʾ����ʾ����levelΪ���������������Ĳ����Ϊ1
{
	if (r >= 0 && r < t.NodeCount())
	{	// ���ڽ��r,����ʾr����Ϣ
		cout<<endl;													//��ʾ����	
		for(int i = 0; i< level - 1; i++)
			cout<<"   ";												//ȷ���ڵ�level����ʾ���
		ElemType e;
		t.GetElem(r, e);											// ȡ�����r��Ԫ��ֵ
		cout << e;													// ��ʾ���Ԫ��ֵ
		for (int child = t.FirstChild(r); child != -1; child = t.RightSibling(child))
		{	// ������ʾ��������
			DisplayTWithConcaveShapeHelp(t, child, level + 1);
		}
	}
}

template <class ElemType>
void DisplayTWithConcaveShape(const ChildParentTree<ElemType> &t)
// ����������������ʾ����ʾ��
{
	DisplayTWithConcaveShapeHelp(t, t.GetRoot(), 1);				// ���ø�������ʵ�ְ������ʾ����ʾ��
	cout << endl;													// ����
}

#endif
