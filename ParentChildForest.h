//ParentChildForest.h

#ifndef PARENTCHILDFOREST_H
#define PARENTCHILDFOREST_H
#include "child_parent_tree_node.h"
#include "node.h"

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
    friend class  ChildParentTreeNode<ElemType>;
//   friend class Node<int>;        //�����޷�����node->next��ֱ�ӹ������ݳ�Ա
    ParentChildForest();                            //�޲����Ĺ��캯��
    virtual ~ParentChildForest();						// ��������
    int GetFirstTree() const;							// ���ص�һ����
    bool Empty() const;								// �ж�ɭ���Ƿ�Ϊ��

//TODO
    void PreOrder(ChildParentTreeNode<ElemType> r);            //�ȸ�����rΪ������ɭ��
    void MidOrder(ChildParentTreeNode<ElemType> r);            //�и�����rΪ������ɭ��
    void PostOrder(ChildParentTreeNode<ElemType> r);        //�������rΪ������ɭ��
//TODO
    int GetTreeNum();                //��ɭ����������Ŀ
    int Height();                //��ɭ�ֵĸ߶�
    int Leaf();                    //��ɭ�ֵ�Ҷ����

    void Show();                   //���ɭ�� 

//TODO
    int FirstChild(int cur) const;					// ���ؽ��cur�ĵ�һ������
    int RightSibling(int cur) const;				// ���ؽ��cur�����ֵ�
    int Parent(int cur) const;						// ���ؽ��cur��˫��
    int NodeDegree(int cur) const;					// ���ؽ��cur�Ķ�

//Done
    ParentChildForest(ElemType items[], int parents[], int r, int n, int size = DEFAULT_SIZE);
    // ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],��һ����λ��Ϊr,������Ϊn����

//��ɭ���н�����ɾ���
//TODO
    Status GetElem(int cur, ElemType& e) const;	// ��e���ؽ��Ԫ��ֵ
    Status SetElem(int cur, const ElemType& e);	// ����cur��ֵ��Ϊe
    void InsertNode();
    void DeleteNode();

};
//TODO
//add show functions
/*
template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildParentTree<ElemType>& t, int r, int level);
// �������ʾ����ʾ����levelΪ�������������Ĳ����Ϊ1
template <class ElemType>
void DisplayTWithConcaveShape(const ChildParentTree<ElemType>& t);
// �������ʾ����ʾ��
*/

template<class ElemType>
int ParentChildForest<ElemType>::GetTreeNum()
{
    return num_of_tree;
}

template<class ElemType>
ParentChildForest<ElemType>::ParentChildForest(ElemType items[], int parents[], int r, int n,int size)
{//����ɭ��
//ȫ����ŵ����������
    num_of_tree = 0;
    maxSize = size;													// ��������
    if (n > maxSize)
        throw Error("������̫��!");								// �׳��쳣
    fnodes = new ChildParentTreeNode<ElemType>[maxSize];				// ����洢�ռ�
    for (int pos = 0; pos < n; pos++)
    {	// ���ζԽ������Ԫ�ؼ�˫��λ�ý��и�ֵ
        fnodes[pos].data = items[pos];								// ����Ԫ��ֵ
        fnodes[pos].parent = parents[pos];							// ˫��λ��
        if (parents[pos] < 0)
            num_of_tree++;      //ֱ�����������Ŀ
        if (parents[pos] > 0) {

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
}

template <class ElemType>
ParentChildForest<ElemType>::~ParentChildForest()
// ����������ͷŴ洢�ռ�
{
    Node<int>* p;
    for (int n = 0; n < num_of_node; n++) {
        p = fnodes[n].childLkList;
        while (p != NULL) {
            fnodes[n].childLkList = p->next;
            delete p;
            p = fnodes[n].childLkList;
        }
    }
    delete[]fnodes;										// �ͷŴ洢�ռ�
}

template<class ElemType>
void ParentChildForest<ElemType>::Show()
{
    for (int i = 0; i < num_of_node; i++) {
        cout << i;
        cout << "( " << fnodes[i].data << ", " << fnodes[i].parent << ", ";
        Node<int>* p;
        if (fnodes[i].childLkList == NULL) {
            cout << "^)" << endl;
        }
        else {
            p = fnodes[i].childLkList;
            while (p) {
                cout << " )->( " << p->data << ", ";
                p = p->next;
            }
            cout << "^)" << endl;
        }
    }
}


#endif