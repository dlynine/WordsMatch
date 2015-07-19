// imgMatchView.h : interface of the CImgMatchView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGMATCHVIEW_H__1407C906_F5BC_4B19_9AEC_CA93337B164B__INCLUDED_)
#define AFX_IMGMATCHVIEW_H__1407C906_F5BC_4B19_9AEC_CA93337B164B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<cv.h>
#include<highgui.h>
#include "AdvancedSet.h"
#include "MyBitamp.h"
#include "targetMatch.h"
#include "adaMachineLearning.h"

class CImgMatchView : public CFormView
{
protected: // create from serialization only
	CImgMatchView();
	DECLARE_DYNCREATE(CImgMatchView)

public:
	enum{ IDD = IDD_IMGMATCH_FORM };

	CImgMatchDoc* GetDocument();

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

	virtual ~CImgMatchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);	//�ı䴰�ڱ���ͼƬ
	DECLARE_MESSAGE_MAP()
public:
	RECT r;						
    CMyBitmap m_bmpBackground;	//������ˢ����
	CStatusBar *pStatues;		//״̬��ָ��
	AdvancedSet Dlg;			//�߼����ö���
	static const int log_num = 10;//������¼��
	CString log, logg[log_num]	//���������ʷ��¼
		,filePath1, filePath2	//�Ա�ͼ1�ͶԱ�ͼ2��·��
		,EvoPath				//�ݻ����·��
		,matchlog				//ƥ����־�����ڵ���
		,tmp;					//����һЩ��ʱ�ַ���
	struct {
		CString path[10];
		int n;	//��ǰģ�����
	}model;		//ģ��ͼ�ṹ
	struct {
		CString p[1000], n[1000];
		int p_num, n_num;
		bool done_p[1000],done_n[1000];
	}train;		//ѵ�����ṹ
	struct {
		CString p[1000];
		int num;
		int times[10];
		bool done[1000];
	}test;		//���Լ��ṹ
	int Evolution;	//��ǰ�ݻ�״̬
	IplImage * img1,* img2, *tmpimg;//�Ա�ͼ1,2��ͼ��ָ��
	Ada_ML ml;	//������ѧϰģ�������
	Target t,t2,t3,t4;
	MSG msg;	//ȫ����Ϣ���������ڸ�����Ϣ����
	_CrtMemState cc1, cc2, cc3;//����ڴ��Ƿ�й©
	HANDLE hLogFile;//������־�ļ����
	bool runing;	//��ǵ�ǰ�Ƿ����ڽ�������
	int resetP_N;	//����Ƿ�������ѵ����
	double ratio[20];	//��ǰ�ݻ����õ��ĸ���������ϵ��
	CString DragImgPath[100];	//�ϷŽ�����ͼƬ�ļ��б�
	CString DragEvoPath;		//�ϷŽ������ݻ�·��
	CString DragModelTrainPath;	//�ϷŽ�����ģ��ѵ����·��

	CMainFrame * pMF;	//ָ�������ڣ����ڻ���״̬���Ľ�����
	RECT myr;			//��ʶ״̬���н������ľ�������
	CREATESTRUCT *pstyle;


	void updatelog();	//���²�����¼
	afx_msg void OnFileopen1();	//�򿪶Ա�ͼ1
	afx_msg void OnFileopen2();	//�򿪶Ա�ͼ2
	afx_msg void OnShowObj();	//��ʾ�Ա�ͼ2
	afx_msg void OnMatchAll();	//���Ա�ͼ1��Ա�ͼ2�Աȣ�����������
	afx_msg void OnSaveMatch();	//����Ա�ͼ1��Ա�ͼ2�Ա�surf�ǵ�����ƥ��ͼ
	afx_msg void OnClearLog();	//��ղ�����¼
	afx_msg void OnMatchSurf();	//ƥ��Ա�ͼ1��Ա�ͼ2��surf�ǵ�
	afx_msg void OnClearAll();	//������������
	afx_msg void OnTrainP();	//������ѵ����
	afx_msg void OnTrainN();	//���븺ѵ����
	afx_msg void OnShowTrainP();//��ʾ��ѵ����
	afx_msg void OnShowTrainN();//��ʾ��ѵ����
	afx_msg void OnClearP();	//�����ѵ����
	afx_msg void OnClearN();	//��ո�ѵ����
	afx_msg void OnShowModel();	//��ʾģ��ͼ
	afx_msg void OnShowObj1();	//��ʾ�Ա�ͼ1
	afx_msg void OnShowObj2();	//��ʾ�Ա�ͼ2
	afx_msg void OnShowTest();	//��ʾ���Լ�
	afx_msg void OnStartEvolution();//��ʼ�ݻ�
	afx_msg void OnAddTest();//���Ӳ��Լ�
	afx_msg void OnClearTest();	//��ղ��Լ�
	afx_msg void OnStartMatch();//��ʼƥ��
	afx_msg void OnClearTrain();//���ѵ����
	afx_msg void OnUseHelp();	//��ʹ�ð���
	afx_msg void OnOpenModelMany();//�����ģ��
	afx_msg void OnTrainHelp();	//��ѵ����������ʾ
	afx_msg void OnTestHelp();	//�Բ��Լ�������ʾ
	afx_msg void OnAdvancedSet();//���ø߼����ý���
	afx_msg void OnSavematch();	//����ƥ����
	afx_msg void OnSaveEvoPath();//�����ݻ�·��
	afx_msg void OnReadEvoPath();//��ȡ�ݻ�·��
	afx_msg void OnUpdateLog();	//��������ʷ��¼
	afx_msg void OnReadModelTrain();//��ȡģ��ͼѵ����
	afx_msg void OnSaveModelTrain();//����ģ���ѵ����
	afx_msg void OnResizeWindow();//���Ĵ���״̬���ɸ��Ĵ�С-���ɸ��Ĵ�С

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);	//�Ծ�̬�ı������ػ棬�ﵽ͸��Ч��
	afx_msg void OnEnVscrollLog();
	afx_msg void OnNcLButtonDown(UINT,CPoint);
	afx_msg void OnQuit();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};

#ifndef _DEBUG  // debug version in imgMatchView.cpp
inline CImgMatchDoc* CImgMatchView::GetDocument()
   { return (CImgMatchDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMGMATCHVIEW_H__1407C906_F5BC_4B19_9AEC_CA93337B164B__INCLUDED_)
