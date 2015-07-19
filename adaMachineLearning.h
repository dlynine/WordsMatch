/** ��������Ӧ����ѧϰ����ģ��
	���༭ʱ��: 2014.6.8  22:00
    �ĵ�˵��: ����Ҫ��������ݼ������ݻ�,���ҵ����ʵ�·��ʵ�ֻ���ѧϰ
    ��������: mlDimension��������ģ�������ά��;num_per_col����ģ��ÿ�и���,
        ����Dimension�������Զ�����;chromlength�������峤��,��·������;
        popsize����ͬʱ�����ݻ�����Ⱥ��С��MaxChromLength���������峤��;
        MaxGen��������ݻ�����;Exp����������ָ��;dataLen���ݼ�����(����);
        bestChrom������ø���;peout����������ͨ��·��������ֵ;data�������ݼ�
    ���θ�������:
		(6.08)��ΪC++�����ʽ��װ
		(5.14)��������,����Ӧ��ͬ����µĻ���ѧϰ
		(4.10)�������߳�,�ڳ���ѯ�ʶԻ���ʱ��̨��Ȼ�ݻ�
		(3.24)����ݻ��ٶ���ʱ����,�޷����û�����ֹͣ������
    @Author: �Ų�(webary)
**/
#ifndef  _ADAMACHINELEARNING_H_
#define  _ADAMACHINELEARNING_H_

#include <iostream>
#include <cstdlib>		//rand()����
#include <cmath>		//��ѧ����
#include <windows.h>
#include <ctime>
#include <string>		//getline()����
#include <fstream>		//getline()����
#include <process.h>	//_beginthread()����
using namespace std;
typedef const char cchar;

#ifdef __AFXWIN_H__
extern int testOut[100];
extern char ml_info[10000];
#endif

class Ada_ML {
#ifdef __AFXWIN_H__
	CStatusBar *pS;
#endif
    int mlDimension, num_per_col, col, chromlength;
    const static int MaxDimension = 150;	//�����������ά��Ϊ150ά
	const static int MaxCol = 25;
    const static int popsize = 10, MaxChromLength = (MaxDimension+23)/24*8*3*MaxCol+3;
	const static int MaxGen = 300000;
	const static int Exp = 2;	//����ָ��
	int best;	//��ø��������
	int dataLen,bestChrom[MaxChromLength], **peout;	//���ݼ�����,��ø���,ģ���������
	int artiTimes, mustEqual;	//�˹���ִ���,�Ƿ�������
	int data[500][151], dataTest[500][150];	//���ݼ������Լ�
	double f,cr,absolut;	//����ϵ��,��������,ƫ����ϵ��:absolutԽ��,���Ϊ1(ƥ��)�ĸ���ԽС
    struct individual {
        int chrom[MaxChromLength];
        double fitness;
    } pop[popsize], cBest;
	struct N_P
	{
		int n, p;			//�ֱ��ʾ������ѵ��������
		double n_err, p_err;//�ֱ��ʾ������ѵ�������д�ĸ�����ƽ��֮��ģ�
		double n_div_p,		//��ѵ��������������ѵ����
			balance_ratio;	//ƽ��ϵ��,�����ȡ��Ӧֵʱʹ����ѵ����ƽ���ϵ��
	}n_p;
    bool b_saveTmp, b_savePre, b_saveBest;//��¼�Ƿ񱣴����и���������浱ǰ���·�����������·��
public:
	double wait,permitError;	//�ȴ�ʱ��
	inline individual& getBest(){ return cBest;} 
	inline int& getCol(){ return col; }
	inline int getChromlen()const{ return chromlength; }
    Ada_ML(int MLDimension=5,int _mustEqual=1,double _absolut=.95,int _col=6,const int* p_artiTimes=0);
	void setML(int MLDimension=1,int _mustEqual=1,double _absolut=.95,int _col=6,const int* p_artiTimes=0);
    void setModel(double _absolut=.75,int _mustEqual=1,const int* p_artiTimes=0);
    void setWait_Col(double wt,int _col=0);
    int  saveToArr(const char *filePath,int* dataarr,int Dimension,bool strict = true);
    void init(const char *readFromFile = 0,bool b_saveData = false);
    int  getPEOut(individual * indiv, int *datarow);
    void fitnessvalue(individual * indiv, int ii);
    int  findbest();
    void demute(int i);	//������Ҫ3������
    void startLearn(int len,double permit_error=8,double balance_r=.5,const char *readFromFile=0,bool b_saveData=false);
#ifdef __AFXWIN_H__
    void startLearn(int len,CStatusBar *p,double permit_error=8,double balance_r=.5,cchar* readFromFile="",bool b_saveData=false);
#endif
    int  loadDataFromFile(const char* fileName, int len = -1, double transFrom1=255, double transFrom2=255);
	int  loadTestData(string fileName, int len, double transFrom);
    void getTestOut(string fileName, int len = -1, double transFrom=255);
    template<class T1,class T2>						//ת��ģ�桪��������һ������
    T1 trans(T2 num,T2 max_T2,T1 stand) {
        return  T1((double)num / max_T2 * stand + .5);
    }
    void setSave(bool saveBest = 0,bool saveTmp = 0,bool savePre = 0){
		b_saveBest = saveBest, b_saveTmp = saveTmp, b_savePre = savePre;
    }
};

#endif // _ADAMACHINELEARNING_H_
