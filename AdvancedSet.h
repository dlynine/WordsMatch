#pragma once
#include "afxwin.h"
#include "MyBitamp.h"
class AdvancedSet :	public CDialog
{
public:
	AdvancedSet(CWnd* pParent = NULL);
	enum { IDD = IDD_AdvancedSet };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg int  check_redo(int check,int redo);	//�ı䴰�ڱ���ͼƬ
	afx_msg void OnHelpAbs();	//��ƫ����ϵ����˵��
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);	//�ı䴰�ڱ���ͼƬ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);//�Ծ�̬�ı������ػ棬�ﵽ͸��Ч��

	DECLARE_MESSAGE_MAP()
public:
	CMyBitmap bg2;	//������ˢ����
	int waitTime;	//�ȴ�ʱ��
	double permitError;	//�������
	int EvoCol;		//�ݻ�ģ������
	double absolut;	//ƫ��ϵ��
	static const int ratio_num = 7;//��ǰʹ�õ���������
	double ratio[ratio_num];//��������ռ����ϵ��
	afx_msg void OnEnChangeRatio();
	double balance_ratio;
	afx_msg void OnBnClickedhelpbalance();
};

