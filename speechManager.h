#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"speaker.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<fstream>
//����ݽ�������
class SpeechManager
{
public:
	//���캯��
	SpeechManager();

	//�˵�չʾ
	void show_Menu();

	//�˳�����
	void exitSystem();

	//��������
	~SpeechManager();

	//��ʼ������������
	void InitSpeed();

	//����ѡ��
	void createSpeaker();

	//��ʼ����
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�÷�
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//��ʾ�����¼
	void showRecord();

	//�����������
	void clearRecord();

public:
	//��Ա����
	vector<int>v1;

	//��һ�ֽ���ѡ�ֱ������
	vector<int>v2;

	//ǰ����ʤ��
	vector<int>vVictpry;

	//��ű���Լ��Ծ���ѡ������
	map<int, Speaker>m_Speaker;

	//��ű�������
	int m_Index;

	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	//��������¼������
	map<int, vector<string>>m_Rector;
};