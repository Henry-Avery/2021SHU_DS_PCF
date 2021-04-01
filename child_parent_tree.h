#ifndef __CHILD_PARENT_TREE_H__
#define __CHILD_PARENT_TREE_H__

#include "lk_queue.h"				// 链队列
#include "child_parent_tree_node.h"	// 孩子双亲表示树结点类
#include "assistance.h"

// 孩子双亲表示树类
template <class ElemType>
class ChildParentTree
{
protected:
//  树的数据成员:
	ChildParentTreeNode<ElemType> *nodes;			// 存储树结点
	int maxSize;									// 树结点最大个数 
	int root, num;									// 根的位置及结点数

//	辅助函数:
	void PreRootOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// 先根序遍历
	void PostRootOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// 后根序遍历
	int HeightHelp(int r) const;					// 返回以r为根的高
	int DegreeHelp(int r) const;					// 返回以r为根的树的度

public:
//  树方法声明及重载编译系统默认方法声明:
	ChildParentTree();								// 无参构造函数
	virtual ~ChildParentTree();						// 析构函数
	int GetRoot() const;							// 返回树的根
	bool Empty() const;								// 判断树是否为空
	Status GetElem(int cur, ElemType &e) const;	// 用e返回结点元素值
	Status SetElem(int cur, const ElemType &e);	// 将结cur的值置为e
	void PreRootOrder(void (*Visit)(const ElemType &)) const;	// 树的先序遍历
	void PostRootOrder(void (*Visit)(const ElemType &)) const;	// 树的后序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;		// 树的层次遍历
	int NodeCount() const;							// 返回树的结点个数
	int NodeDegree(int cur) const;					// 返回结点cur的度
	int Degree() const;								// 返回树的度
	int FirstChild(int cur) const;					// 返回结点cur的第一个孩子
	int RightSibling(int cur) const;				// 返回结点cur的右兄弟
	int Parent(int cur) const;						// 返回结点cur的双亲
	Status InsertChild(int cur, int i, const ElemType &e);	
		// 将数据元素插入为cur的第i个孩子
	int	Height() const;								// 返回树的高
	ChildParentTree(const ElemType &e, int size = DEFAULT_SIZE);
		// 建立以数据元素e为根的树
	ChildParentTree(ElemType items[], int parents[], int r, int n, int size = DEFAULT_SIZE);
		// 建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树
};

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildParentTree<ElemType> &t, int r, int level);
	// 按凹入表示法显示树，level为层次数，设根结点的层次数为1
template <class ElemType>
void DisplayTWithConcaveShape(const ChildParentTree<ElemType> &t);
	// 按凹入表示法显示树

// 孩子双亲表示树类的实现部分
template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree()
// 操作结果：构造一个空树
{
	maxSize = DEFAULT_SIZE;								// 树结点最大个数
	nodes = new ChildParentTreeNode<ElemType>[maxSize];	// 分配存储空间
	root = -1;											// 表示不存在根
	num = 0;											// 空树的结点个数为0
}

template <class ElemType>
ChildParentTree<ElemType>::~ChildParentTree()
// 操作结果：释放存储空间
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
	delete []nodes;										// 释放存储空间
}



template <class ElemType>
int ChildParentTree<ElemType>::GetRoot() const
// 操作结果：返回树的根
{
	return root;
}

template <class ElemType>
bool ChildParentTree<ElemType>::Empty() const
// 操作结果：判断树是否为空
{
	return num == 0;
}

template <class ElemType>
Status ChildParentTree<ElemType>::GetElem(int cur, ElemType &e) const
// 操作结果：用e返回结点cur元素值,如果不存在结点cur,函数返回NOT_PRESENT,否则返回ENTRY_FOUND
{
	if (cur < 0 || cur >= num)		// 不存在结点cur
		return NOT_PRESENT;			// 返回NOT_PRESENT
	else {	                        // 存在结点cur
		e = nodes[cur].data;		// 用e返回元素值
		return ENTRY_FOUND;			// 返回ENTRY_FOUND
	}
}

template <class ElemType>
Status ChildParentTree<ElemType>::SetElem(int cur, const ElemType &e)
// 操作结果：如果不存在结点cur,则返回FAIL,否则返回SUCCESS,并将结点cur的值设置为e
{
	if (cur < 0 || cur >= num)		// 不存在结点cur
		return FAIL;				// 返回FAIL
	else	{	                    // 存在结点cur
		nodes[cur].data = e;		// 将结点cur的值设置为e
		return SUCCESS;	  		    // 返回SUCCESS
	}
}

template <class ElemType>
int ChildParentTree<ElemType>::NodeCount() const
// 操作结果：返回树的结点个数
{
	return num;
}

template <class ElemType>
int ChildParentTree<ElemType>::FirstChild(int cur) const
// 操作结果：如cur无孩子,则返回-1,否则返回树结点cur的第一个孩子,
{
    Node<int> *p;
	if (cur < 0 || cur >= num)	
		return -1;						// 结点cur不存在,返回-1表示无孩子
	
	if (nodes[cur].childLkList == NULL)	// 无孩子
		return -1;
	else
		return nodes[cur].childLkList->data;	// 取出第一个孩子
}

template <class ElemType>
int ChildParentTree<ElemType>::RightSibling(int cur) const
// 操作结果：如果结点cur无右兄弟,则返回-1,否则返回cur的右兄弟
{
	if (cur < 0 || cur >= num)						
		return -1;						// 结点cur不存在,返回-1表示无孩子

	int pt = nodes[cur].parent;			// cur的双亲
    Node<int> * p = nodes[pt].childLkList;
    while (p != NULL && p->data != cur)
       p = p->next;
    if ( p == NULL || p->next == NULL)
		return -1;				// 反回右兄弟
	else
		return p->next->data;	// 表示无右兄弟
}

template <class ElemType>
int ChildParentTree<ElemType>::Parent(int cur) const
// 操作结果：返回树结点cur的双亲
{
	if (cur < 0 || cur >= num)						
		return -1;						// 结点cur不存在,返回-1表示无双亲
	return nodes[cur].parent;
}

template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree(ElemType items[], int parents[], int r, int n, int size)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树
{
	maxSize = size;													// 最大结点个数
	if (n > maxSize)	
	    throw Error("结点个数太多!");								// 抛出异常
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// 分配存储空间
	for (int pos = 0; pos < n; pos++)
	{	// 依次对结点数据元素及双亲位置进行赋值
		nodes[pos].data = items[pos];								// 数据元素值
		nodes[pos].parent = parents[pos];							// 双亲位置
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
	root = r;														// 根
	num = n;														// 结点个数
}

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildParentTree<ElemType> &t, int r, int level)
// 操作结果：按凹入表示法显示树，level为层次数，可设根结点的层次数为1
{
	if (r >= 0 && r < t.NodeCount())
	{	// 存在结点r,才显示r的信息
		cout<<endl;													//显示新行	
		for(int i = 0; i< level - 1; i++)
			cout<<"   ";												//确保在第level列显示结点
		ElemType e;
		t.GetElem(r, e);											// 取出结点r的元素值
		cout << e;													// 显示结点元素值
		for (int child = t.FirstChild(r); child != -1; child = t.RightSibling(child))
		{	// 依次显示各棵子树
			DisplayTWithConcaveShapeHelp(t, child, level + 1);
		}
	}
}

template <class ElemType>
void DisplayTWithConcaveShape(const ChildParentTree<ElemType> &t)
// 操作结果：按凹入表示法显示树
{
	DisplayTWithConcaveShapeHelp(t, t.GetRoot(), 1);				// 调用辅助函数实现按凹入表示法显示树
	cout << endl;													// 换行
}

#endif
