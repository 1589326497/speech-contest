#include"speechManager.h"

//���캯��
SpeechManager::SpeechManager()
{
	//��ʼ������������
	this->InitSpeed();
	//����ѡ��
	this->createSpeaker();
	//�����ļ�
	this->loadRecord();
}
//�˵�չʾ
void SpeechManager::show_Menu()
{
	cout << "************************************************* " << endl;
	cout << "************** ��ӭ�μ��ݽ����� ***************** " << endl;
	cout << "************** 1.��ʼ�ݽ�����   ***************** " << endl;
	cout << "************** 2.�鿴�����¼   ***************** " << endl;
	cout << "************** 3.��ձ�����¼   ***************** " << endl;
	cout << "************** 0.�˳���������   ***************** " << endl;
	cout << "************************************************* " << endl;
	cout << endl;
}
//�˳�����
void SpeechManager:: exitSystem()
{
	cout << "��ӭ�´�ʹ��"<<endl;
	system("pause");
	exit(0);
}
//��ʼ��
void SpeechManager::InitSpeed()
{
	//�������ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictpry.clear();
	this->m_Speaker.clear();
	this->m_Rector.clear();
	//��������
	this->m_Index = 1;
}
//����12��ѡ��
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;  //��ʼѡ�ֵķ���
		}
		
		//12��ѡ�ֵı��
		this->v1.push_back(i + 10001);

		//��ѡ�ֱ�ź������ŵ�map��
		this->m_Speaker.insert(pair<int, Speaker>(i + 10001, sp));


	}
}
//��ʼ����
void SpeechManager::startSpeech()
{
	for (int i=m_Index; i <= 2; i++)
	{
		//��ʼ����
		//1.��ǩ
		this->speechDraw();

		//2.����
		this->speechContest();

		//3.��ʾ����
		this->showScore();
		m_Index++;
	}
	//�����ļ�
	saveRecord();

	//���ñ���
	//��ʼ������������
	this->InitSpeed();
	//����ѡ��
	this->createSpeaker();
	//�����ļ�
	this->loadRecord();

	cout << "���������ɣ�" << endl;
	system("pause");
	system("cls");

}
//��ǩ
void SpeechManager::speechDraw()
{
	cout << "��" << this->m_Index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------------" << endl;
	cout << "��ǩ���ݽ���˳��" << endl;

	if (this->m_Index == 1)
	{
		// ��һ��
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it=v1.begin();it!=v1.end();it++)
		{
			cout << *it << endl;
		}
		cout << "-------------------------" << endl;
	}
	else
	{
		// �ڶ���
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

//����
void SpeechManager::speechContest()
{
	cout << "---------------------��" << this->m_Index << "�ֱ�����ʽ��ʼ---------------------" << endl;
	//��ʱ���������С�������ɼ�
	multimap<double, int, greater<double>> groupScore;

	int num = 0;	//��¼��Ա����

	vector<int>v_Src; //����ѡ������
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//�������е�ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600 )/ 10.f;		//600-1000
			//cout << score << " ";
			d.push_back(score);
		}
		sort(d.begin(), d.end(),greater<double>());	//����
		d.pop_front();	//ȥ����߷�
		d.pop_back();	//ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f);	//�ܷ�
		double avg = sum / (double)d.size();	//ƽ����

		//��ӡƽ����
		//cout << "��ţ�" << *it << "ѡ�֣�" << this->m_Speaker[*it].m_Name << " ƽ���֣�" << avg << endl;
		//��ƽ���ַŵ�map������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg; //�����һ�ַ���
		

		//��������� �ŵ���ʱС��������
		groupScore.insert(make_pair(avg, *it)); //key�ǵ÷� value�Ǿ���ѡ�ֱ��

		//ÿ����ȡ��ǰ����
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "�������������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ� " << it->second << "������ " << this->m_Speaker[it->second].m_Name << "�����ɼ��� " << this->m_Speaker[it->second].m_Score[this->m_Index-1];
				cout << endl;
			}
			//ȡ��ǰ�������� ���뵽v2��
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

			groupScore.clear();	//С����������
			cout << endl;
		}
		
	}
	cout << "-------------------��" << this->m_Index << "�ֱ�������------------------" << endl;
	system("pause");
}
//��ʾ�÷�
void SpeechManager::showScore()
{
	cout << "-------------------��" << this->m_Index << "��ѡ����Ϣ����------------------" << endl;
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
		cout << "��ţ� " << *it << "������ " << this->m_Speaker[*it].m_Name << "�����ɼ��� " << this->m_Speaker[*it].m_Score[this->m_Index - 1]<<endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

//�����¼
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); //׷�ӵķ�ʽд�ļ�
	//��ÿ���˵�����д���ļ���
	for (vector<int>::iterator it=this->vVictpry.begin();it!= vVictpry.end();it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ","; //csv�ļ��ã��ֿ�
	}
	ofs << endl;
	ofs.close();
	cout << "�ļ��������" << endl;

	//�����ļ���־λ
	this->fileIsEmpty = false;
}

//��ȡ��¼
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);	//���ļ�
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	//�ļ��Ƿ����
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
	}
	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch); //��ch�Ż�ȥ

	string data;

	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;//���6���ַ���
		int pos = -1;//�鵽��,��λ�õı���
		int start = 0;
		while (1)
		{
			pos = data.find(',', start);
			if (pos == -1)
			{
				//û���ҵ�
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		//ÿ�����ַ���Ϊһ��ý�������
		this->m_Rector.insert(pair<int, vector<string>>(index, v));
		index++;
	}
	ifs.close();
}

//��ʾ�����¼
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ�Ϊ��" << endl;
	}
	for (int i = 0; i < this->m_Rector.size(); i++)
	{
		cout << "��" << i + 1 << "��" << endl;
		cout << "�ھ���ţ�" << this->m_Rector[i].at(0) << "�÷֣�" << this->m_Rector[i].at(1) << endl;
		cout << "�Ǿ���ţ�" << this->m_Rector[i].at(2) << "�÷֣�" << this->m_Rector[i].at(3) << endl;
		cout << "������ţ�" << this->m_Rector[i].at(4) << "�÷֣�" << this->m_Rector[i].at(5) << endl;
	}
	system("pause");
	system("cls");
}

//�����������
void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1,ȷ��" << endl;
	cout << "2,����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//trunc�򿪷�ʽ ��������ļ� ɾ�������´���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//��ʼ��
		this->InitSpeed();
		//����ѡ��
		this->createSpeaker();
		//�����ļ�
		this->loadRecord();

		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

//��������
SpeechManager::~SpeechManager()
{

}