//main.cpp

#include "ParentChildForest.h"
#include "assistance.h"					// 辅助软件包
#include "child_parent_tree.h"			// 孩子双亲表示树类

int main(void)
{
	try									// 用try封装可能出现异常的代码
	{
        char items[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P' };
        int parents[] = { -1,-2,1,0,4,5,0,7,7,7,8,8,10,10,10,13 };      //-1表示每棵树的根节点
		int r = 0, n = 8;//第一颗树根节点位置是r，总共n个结点，默认值构造最大数量100
        ParentChildForest<char> forest(items, parents,r,n);
		cout << "树:" << endl;
        forest.Show();
//		DisplayTWithConcaveShape(t);
        /*
        forest.Show();//输出森林的双亲孩子结构
        cout << "输入任意值以继续:";
        char c;
        cin >> c;
        cout << "先根遍历: ";
        forest.PreOrder(forest.a[0]);
        cout << endl;
        cout << "中根遍历: ";
        forest.MidOrder(forest.a[0]);
        cout << endl;
        cout << "后根遍历: ";
        forest.PostOrder(forest.a[0]);
        cout << endl;
        */
        cout << "该森林中树的数目为: " << forest.GetTreeNum() << endl;
//        cout << "该森林的高度为: " << forest.Height() << endl;
//        cout << "该森林的叶子数目为: " << forest.Leaf() << endl;
        
		cout << endl;
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

