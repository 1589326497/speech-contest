/*
	stl��ϰ 2023��4��6�����
*/
#include<iostream>
using namespace std;
#include"speechManager.h"
#include<ctime>
int main()
{
	//���������
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	int choice = 0;		//�����û�ѡ��
	while(true)
	{
		sm.show_Menu();	//��ʾ�˵�
		cout << "��������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:		//1.��ʼ�ݽ�����
			sm.startSpeech();
			break;
		case 2:		//2.�鿴�����¼
			sm.showRecord();
			break;
		case 3:		//3.��ձ�����¼
			sm.clearRecord();
			break;
		case 0:		//0.�˳���������
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