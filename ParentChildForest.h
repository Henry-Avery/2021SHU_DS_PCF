//ParentChildForest.h

#ifndef PARENTCHILDFOREST_H
#define PARENTCHILDFOREST_H
#include "child_parent_tree_node.h"
#include <iostream>
#include "lk_queue.h"
using namespace std;


template<class ElemType>
class ParentChildForest
{
protected:
    ChildParentTreeNode<ElemType>* fnodes;       //存放森林中所有结点
    ChildParentTreeNode<ElemType>* first_tree;        //指向树林中第一颗树的指针
    int first_tree_index;                     //存放树林中第一颗树的位置
    int num_of_tree;                      //森林中树的数目
    int num_of_node;                    //森林总结点个数
    int height;                         //森林中最高的树高度
    int num_of_leaf;                    //森林总叶子数
    int maxSize;                       //森林结点最大数

    //	辅助函数:
    void PreRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// 先根序遍历
    void MidRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// 中根序遍历
    void PostRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// 后根序遍历
    int HeightHelp(int r) const;					// 返回以r为根的高
    int DegreeHelp(int r) const;					// 返回以r为根的树的度
    int LeafHelp(int r) const;					// 返回以r为根的树的叶子数

public:
    ParentChildForest();                            //无参数的构造函数
//   virtual ~ParentChildForest();						// 析构函数
    int GetFirstTree() const;							// 返回第一颗树
    bool Empty() const;								// 判断森林是否为空


    void PreOrder(ChildParentTreeNode<ElemType> r);            //先根遍历r为的子树森林
    void MidOrder(ChildParentTreeNode<ElemType> r);            //中根遍历r为的子树森林
    void PostOrder(ChildParentTreeNode<ElemType> r);        //后根遍历r为的子树森林

    int TreeNum();                //求森林中树的数目
    int Height();                //求森林的高度
    int Leaf();                    //求森林的叶子数

    void Show();                   //输出森林

    int FirstChild(int cur) const;					// 返回结点cur的第一个孩子
    int RightSibling(int cur) const;				// 返回结点cur的右兄弟
    int Parent(int cur) const;						// 返回结点cur的双亲
    int NodeDegree(int cur) const;					// 返回结点cur的度


    ParentChildForest(ElemType items[], int parents[], int r, int n, int size = DEFAULT_SIZE);
    // 建立数据元素为items[],对应结点双亲为parents[],第一颗树位置为r,结点个数为n的树

//对森林中结点的增删查改

    Status GetElem(int cur, ElemType& e) const;	// 用e返回结点元素值
    Status SetElem(int cur, const ElemType& e);	// 将结cur的值置为e
    void InsertNode();
    void DeleteNode();

};

template<class ElemType>
ParentChildForest<ElemType>::ParentChildForest(ElemType items[], int parents[], int r, int n,int size)
{//构造森林
//全部存放到结点数组内
/*
    maxSize = size;													// 最大结点个数
    if (n > maxSize)
        throw Error("结点个数太多!");								// 抛出异常
    fnodes = new ChildParentTreeNode<ElemType>[maxSize];				// 分配存储空间
    for (int pos = 0; pos < n; pos++)
    {	// 依次对结点数据元素及双亲位置进行赋值
        fnodes[pos].data = items[pos];								// 数据元素值
        fnodes[pos].parent = parents[pos];							// 双亲位置
        if (parents[pos] < 0) {
            Node<int>* p, * newnode;
            newnode = new Node<int>(pos, NULL);
            if (fnodes[parents[pos]].childLkList == NULL)
                fnodes[parents[pos]].childLkList = newnode;
            else {
                p = fnodes[parents[pos]].childLkList;
                while (p->next != NULL)
                    p = p->next;
                p->next = newnode;
            }
        }
    }
    first_tree_index = r;														// 第一颗树位置
    num_of_node = n;														// 结点个数
    */
}

/*
template<class ElemType>
void ParentChildForest<ElemType>::Show()
{
    for (int i = 0; i <= num; i++) {
        cout << i;
        cout << "( " << a[i].data << ", " << a[i].parent << ", ";
        ChildParentTreeNode<ElemType>* p;
        if (a[i].childLkList == NULL) {
            cout << "^)" << endl;
        }
        else {
            p = a[i].childLkList;
            while (p) {
                cout << " )->( " << p->data << ", ";
                p = p->childLkList;
            }
            cout << "^)" << endl;
        }
    }
}
*/

#endif