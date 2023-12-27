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
//设计演讲管理类
class SpeechManager
{
public:
	//构造函数
	SpeechManager();

	//菜单展示
	void show_Menu();

	//退出功能
	void exitSystem();

	//析构函数
	~SpeechManager();

	//初始化容器和属性
	void InitSpeed();

	//创建选手
	void createSpeaker();

	//开始比赛
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示得分
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//显示往届记录
	void showRecord();

	//清空所有数据
	void clearRecord();

public:
	//成员属性
	vector<int>v1;

	//第一轮晋级选手编号容器
	vector<int>v2;

	//前三名胜出
	vector<int>vVictpry;

	//存放编号以及对具体选手容器
	map<int, Speaker>m_Speaker;

	//存放比赛轮数
	int m_Index;

	//判断文件是否为空
	bool fileIsEmpty;

	//存放往届记录的容器
	map<int, vector<string>>m_Rector;
};