#include"speechManager.h"

//构造函数
SpeechManager::SpeechManager()
{
	//初始化容器和属性
	this->InitSpeed();
	//创建选手
	this->createSpeaker();
	//加载文件
	this->loadRecord();
}
//菜单展示
void SpeechManager::show_Menu()
{
	cout << "************************************************* " << endl;
	cout << "************** 欢迎参加演讲比赛 ***************** " << endl;
	cout << "************** 1.开始演讲比赛   ***************** " << endl;
	cout << "************** 2.查看往届记录   ***************** " << endl;
	cout << "************** 3.清空比赛记录   ***************** " << endl;
	cout << "************** 0.退出比赛程序   ***************** " << endl;
	cout << "************************************************* " << endl;
	cout << endl;
}
//退出功能
void SpeechManager:: exitSystem()
{
	cout << "欢迎下次使用"<<endl;
	system("pause");
	exit(0);
}
//初始化
void SpeechManager::InitSpeed()
{
	//容器都置空
	this->v1.clear();
	this->v2.clear();
	this->vVictpry.clear();
	this->m_Speaker.clear();
	this->m_Rector.clear();
	//比赛轮数
	this->m_Index = 1;
}
//创建12个选手
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;  //初始选手的分数
		}
		
		//12名选手的编号
		this->v1.push_back(i + 10001);

		//将选手编号和容器放到map中
		this->m_Speaker.insert(pair<int, Speaker>(i + 10001, sp));


	}
}
//开始比赛
void SpeechManager::startSpeech()
{
	for (int i=m_Index; i <= 2; i++)
	{
		//开始比赛
		//1.抽签
		this->speechDraw();

		//2.比赛
		this->speechContest();

		//3.显示晋级
		this->showScore();
		m_Index++;
	}
	//保存文件
	saveRecord();

	//重置比赛
	//初始化容器和属性
	this->InitSpeed();
	//创建选手
	this->createSpeaker();
	//加载文件
	this->loadRecord();

	cout << "本届比赛完成！" << endl;
	system("pause");
	system("cls");

}
//抽签
void SpeechManager::speechDraw()
{
	cout << "第" << this->m_Index << "轮比赛选手正在抽签" << endl;
	cout << "-------------------------" << endl;
	cout << "抽签后演讲的顺序：" << endl;

	if (this->m_Index == 1)
	{
		// 第一轮
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it=v1.begin();it!=v1.end();it++)
		{
			cout << *it << endl;
		}
		cout << "-------------------------" << endl;
	}
	else
	{
		// 第二轮
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << endl;
		}
		cout << "-------------------------" << endl;
		system("pause");
		cout << endl;
	}
}

//比赛
void SpeechManager::speechContest()
{
	cout << "---------------------第" << this->m_Index << "轮比赛正式开始---------------------" << endl;
	//临时容器，存放小组容器成绩
	multimap<double, int, greater<double>> groupScore;

	int num = 0;	//记录人员个数

	vector<int>v_Src; //比赛选手容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//遍历所有的选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600 )/ 10.f;		//600-1000
			//cout << score << " ";
			d.push_back(score);
		}
		sort(d.begin(), d.end(),greater<double>());	//排序
		d.pop_front();	//去除最高分
		d.pop_back();	//去除最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);	//总分
		double avg = sum / (double)d.size();	//平均分

		//打印平均分
		//cout << "编号：" << *it << "选手：" << this->m_Speaker[*it].m_Name << " 平均分：" << avg << endl;
		//将平均分放到map容器中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg; //放入第一轮分数
		

		//将打分数据 放到临时小组容器中
		groupScore.insert(make_pair(avg, *it)); //key是得分 value是具体选手编号

		//每六人取出前三人
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "组比赛名次如下" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号： " << it->second << "姓名： " << this->m_Speaker[it->second].m_Name << "比赛成绩： " << this->m_Speaker[it->second].m_Score[this->m_Index-1];
				cout << endl;
			}
			//取走前三名晋级 放入到v2中
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					this->vVictpry.push_back((*it).second);
				}
			}

			groupScore.clear();	//小组的容器清空
			cout << endl;
		}
		
	}
	cout << "-------------------第" << this->m_Index << "轮比赛结束------------------" << endl;
	system("pause");
}
//显示得分
void SpeechManager::showScore()
{
	cout << "-------------------第" << this->m_Index << "轮选手信息如下------------------" << endl;
	vector<int> v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = this->vVictpry;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号： " << *it << "姓名： " << this->m_Speaker[*it].m_Name << "比赛成绩： " << this->m_Speaker[*it].m_Score[this->m_Index - 1]<<endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

//保存记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); //追加的方式写文件
	//将每个人的数据写入文件中
	for (vector<int>::iterator it=this->vVictpry.begin();it!= vVictpry.end();it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ","; //csv文件用，分开
	}
	ofs << endl;
	ofs.close();
	cout << "文件保存完成" << endl;

	//更新文件标志位
	this->fileIsEmpty = false;
}

//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);	//读文件
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//文件是否清空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
	}
	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch); //将ch放回去

	string data;

	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;//存放6个字符串
		int pos = -1;//查到‘,’位置的变量
		int start = 0;
		while (1)
		{
			pos = data.find(',', start);
			if (pos == -1)
			{
				//没有找到
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		//每六个字符串为一届得奖者数据
		this->m_Rector.insert(pair<int, vector<string>>(index, v));
		index++;
	}
	ifs.close();
}

//显示往届记录
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件为空" << endl;
	}
	for (int i = 0; i < this->m_Rector.size(); i++)
	{
		cout << "第" << i + 1 << "届" << endl;
		cout << "冠军编号：" << this->m_Rector[i].at(0) << "得分：" << this->m_Rector[i].at(1) << endl;
		cout << "亚军编号：" << this->m_Rector[i].at(2) << "得分：" << this->m_Rector[i].at(3) << endl;
		cout << "季军编号：" << this->m_Rector[i].at(4) << "得分：" << this->m_Rector[i].at(5) << endl;
	}
	system("pause");
	system("cls");
}

//清空所有数据
void SpeechManager::clearRecord()
{
	cout << "确定清空？" << endl;
	cout << "1,确定" << endl;
	cout << "2,返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//trunc打开方式 如果存在文件 删除并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//初始化
		this->InitSpeed();
		//创建选手
		this->createSpeaker();
		//加载文件
		this->loadRecord();

		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}

//析构函数
SpeechManager::~SpeechManager()
{

}