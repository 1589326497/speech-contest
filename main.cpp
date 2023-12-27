/*
	stl练习 2023年4月6日完成
*/
#include<iostream>
using namespace std;
#include"speechManager.h"
#include<ctime>
int main()
{
	//随机数种子
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	int choice = 0;		//接收用户选择
	while(true)
	{
		sm.show_Menu();	//显示菜单
		cout << "输入您的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:		//1.开始演讲比赛
			sm.startSpeech();
			break;
		case 2:		//2.查看往届记录
			sm.showRecord();
			break;
		case 3:		//3.清空比赛记录
			sm.clearRecord();
			break;
		case 0:		//0.退出比赛程序
			sm.exitSystem();
			break;

		default:
			system("cls");
			break;
		}

	}
	system("pause");
	return 0;
}