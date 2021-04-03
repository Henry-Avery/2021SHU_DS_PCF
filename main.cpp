//main.cpp

#include "ParentChildForest.h"
#include "assistance.h"					// ���������
#include "child_parent_tree.h"			// ����˫�ױ�ʾ����

int main(void)
{
	try									// ��try��װ���ܳ����쳣�Ĵ���
	{
        char items[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P' };
        int parents[] = { -1,-2,1,0,4,5,0,7,7,7,8,8,10,10,10,13 };      //-1��ʾÿ�����ĸ��ڵ�
		int r = 0, n = 8;//��һ�������ڵ�λ����r���ܹ�n����㣬Ĭ��ֵ�����������100
        ParentChildForest<char> forest(items, parents,r,n);
		cout << "��:" << endl;
        forest.Show();
//		DisplayTWithConcaveShape(t);
        /*
        forest.Show();//���ɭ�ֵ�˫�׺��ӽṹ
        cout << "��������ֵ�Լ���:";
        char c;
        cin >> c;
        cout << "�ȸ�����: ";
        forest.PreOrder(forest.a[0]);
        cout << endl;
        cout << "�и�����: ";
        forest.MidOrder(forest.a[0]);
        cout << endl;
        cout << "�������: ";
        forest.PostOrder(forest.a[0]);
        cout << endl;
        */
        cout << "��ɭ����������ĿΪ: " << forest.GetTreeNum() << endl;
//        cout << "��ɭ�ֵĸ߶�Ϊ: " << forest.Height() << endl;
//        cout << "��ɭ�ֵ�Ҷ����ĿΪ: " << forest.Leaf() << endl;
        
		cout << endl;
	}
	catch (Error err)					// ��׽�������쳣
	{
		err.Show();						// ��ʾ�쳣��Ϣ
	}

	system("PAUSE");					// ���ÿ⺯��system()
	return 0;							// ����ֵ0, ���ز���ϵͳ
}

