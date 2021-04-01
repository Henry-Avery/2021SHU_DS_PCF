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
    ChildParentTreeNode<ElemType>* fnodes;       //���ɭ�������н��
    ChildParentTreeNode<ElemType>* first_tree;        //ָ�������е�һ������ָ��
    int first_tree_index;                     //��������е�һ������λ��
    int num_of_tree;                      //ɭ����������Ŀ
    int num_of_node;                    //ɭ���ܽ�����
    int height;                         //ɭ������ߵ����߶�
    int num_of_leaf;                    //ɭ����Ҷ����
    int maxSize;                       //ɭ�ֽ�������

    //	��������:
    void PreRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// �ȸ������
    void MidRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// �и������
    void PostRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// ��������
    int HeightHelp(int r) const;					// ������rΪ���ĸ�
    int DegreeHelp(int r) const;					// ������rΪ�������Ķ�
    int LeafHelp(int r) const;					// ������rΪ��������Ҷ����

public:
    ParentChildForest();                            //�޲����Ĺ��캯��
//   virtual ~ParentChildForest();						// ��������
    int GetFirstTree() const;							// ���ص�һ����
    bool Empty() const;								// �ж�ɭ���Ƿ�Ϊ��


    void PreOrder(ChildParentTreeNode<ElemType> r);            //�ȸ�����rΪ������ɭ��
    void MidOrder(ChildParentTreeNode<ElemType> r);            //�и�����rΪ������ɭ��
    void PostOrder(ChildParentTreeNode<ElemType> r);        //�������rΪ������ɭ��

    int TreeNum();                //��ɭ����������Ŀ
    int Height();                //��ɭ�ֵĸ߶�
    int Leaf();                    //��ɭ�ֵ�Ҷ����

    void Show();                   //���ɭ��

    int FirstChild(int cur) const;					// ���ؽ��cur�ĵ�һ������
    int RightSibling(int cur) const;				// ���ؽ��cur�����ֵ�
    int Parent(int cur) const;						// ���ؽ��cur��˫��
    int NodeDegree(int cur) const;					// ���ؽ��cur�Ķ�


    ParentChildForest(ElemType items[], int parents[], int r, int n, int size = DEFAULT_SIZE);
    // ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],��һ����λ��Ϊr,������Ϊn����

//��ɭ���н�����ɾ���

    Status GetElem(int cur, ElemType& e) const;	// ��e���ؽ��Ԫ��ֵ
    Status SetElem(int cur, const ElemType& e);	// ����cur��ֵ��Ϊe
    void InsertNode();
    void DeleteNode();

};

template<class ElemType>
ParentChildForest<ElemType>::ParentChildForest(ElemType items[], int parents[], int r, int n,int size)
{//����ɭ��
//ȫ����ŵ����������
/*
    maxSize = size;													// ��������
    if (n > maxSize)
        throw Error("������̫��!");								// �׳��쳣
    fnodes = new ChildParentTreeNode<ElemType>[maxSize];				// ����洢�ռ�
    for (int pos = 0; pos < n; pos++)
    {	// ���ζԽ������Ԫ�ؼ�˫��λ�ý��и�ֵ
        fnodes[pos].data = items[pos];								// ����Ԫ��ֵ
        fnodes[pos].parent = parents[pos];							// ˫��λ��
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
    first_tree_index = r;														// ��һ����λ��
    num_of_node = n;														// ������
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