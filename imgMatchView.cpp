// imgMatchView.cpp : implementation of the CImgMatchView class
#include "stdafx.h"
#include "imgMatch.h"

#include "MainFrm.h"
#include "imgMatchDoc.h"
#include "imgMatchView.h"
#include "AdvancedSet.h"

#include "imgPro.h"
#include "targetMatch.h"
#include "adaMachineLearning.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
	void CImgMatchView::AssertValid() const
	{
		CFormView::AssertValid();
	}

	void CImgMatchView::Dump(CDumpContext& dc) const
	{
		CFormView::Dump(dc);
	}

	CImgMatchDoc* CImgMatchView::GetDocument() // non-debug version is inline
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgMatchDoc)));
		return (CImgMatchDoc*)m_pDocument;
	}
#endif //_DEBUG
	
/////////////////////////////////////////////////////////////////////////////
// CHelpDlg dialog used for App Help

class CHelpDlg : public CDialog
{
public:
	CHelpDlg() : CDialog(CHelpDlg::IDD){};
	enum { IDD = IDD_useHelp };
protected:
	virtual void DoDataExchange(CDataExchange* pDX){CDialog::DoDataExchange(pDX);};
};

/////////////////////////////////////////////////////////////////////////////
// CUpdateLogDlg dialog used for App UpdateLog

class CUpdateLogDlg : public CDialog
{
public:
	CUpdateLogDlg();
	enum { IDD = IDD_UpdateLog };
protected:
	virtual void DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Text(pDX, IDC_Update_log, m_updateLog);
	}
public:
	CString m_updateLog;
};

CUpdateLogDlg::CUpdateLogDlg() : CDialog(CUpdateLogDlg::IDD)
{
	m_updateLog = _T(
		"-->v2.0 ��ʽ�棺\r\n"
		"1.�޸����ݿ���֤ɾ�����̲����׵�bug\r\n"
		"2.�����ļ����Զ��������ǰ����ʾ\r\n"
		"3.С����������Ĳ���\r\n"
		"\r����������������������������������������������������������������\r\n"
		"\r\n"
		"-->v1.5 ��ʽ�棺\r\n"
		"1.֧�������ļ��������������,֧�ֵĸ�ʽ��.jpg/.bmp/.png/.path/.epath\r\n"
		"2.�������ݿ�洢,��Ԥ������ͼƬ���б��棬�ɼ�������ͬһͼƬ\r\n"
		"3.�޸��״δ򿪼�ⷽʽ\r\n"
		"\r����������������������������������������������������������������\r\n"
		"\r\n"
		"-->v1.4.1 ���԰棺\r\n"
		"1.���ӵ�������ѵ������ռȨ�صĲ���������ƽ��ϵ����\r\n"
		"\r����������������������������������������������������������������\r\n"
		"\r\n"
		"-->v1.4 ��ʽ�棺\r\n"
		"1.���������� bias\r\n"
		"2.��������ѵ��������Ŀ�Զ�������ռȨ��\r\n"
		"\r����������������������������������������������������������������\r\n"
		"\r\n"
		"-->v1.3.3 ���԰棺\r\n"
		"1.�޸Ĳ���bug,����ȶ���\r\n"
		"\r����������������������������������������������������������������\r\n"
		"\r\n"
		"-->v1.3.2 ���԰棺\r\n"
		"1.���������������ʶ����ȷ��\r\n"
		"2.���Ӷ��̲߳��������ӿ��ȡѵ�����Ͳ��Լ����ٶ�\r\n"
		"\r����������������������������������������������������������������\r\n"
		"\r\n"
		"-->v1.3.1 ���԰棺\r\n"
		"1.���ӽ�����ʾ����\r\n"
		"\r����������������������������������������������������������������\r\n"
		"\r\n"
		"-->v1.3 ��ʽ�棺\r\n"
		"1.�����̹߳��ܣ�ѯ���Ƿ�ֹͣʱ��̨��Ȼ�����ݻ�\r\n"
		"2.�Ż��������ϴ�ʱ������ֵļ���״̬\r\n"
		"3.�Ż��ڴ��CPUռ����\r\n"
		"4.�޸��״ζ�ȡʱż��������bug\r\n"
		"5.���û���������ϸ��¼�����������������µ��������\r\n"
		"6.��������������û��Դ����ƶ��Ĳ�������ֹ���ڻ����쳣\r\n"
		"����������������������������������������������������������������\r\n"
		"\r\n"
		"-->v1.2.2 ���԰棺\r\n"
		"1.���Ӷ�ƥ������ƫ���Եĵ������ܣ��߼����ã�\r\n"
		"2.���Ӷ�ѡ��ģ���ݻ�ʱ��ϵ���������ܣ��߼����ã�\r\n"
		"3.�Ż�ѵ�����Ͳ��Լ���ģ���ƥ�䷽ʽ\r\n"
		"����������������������������������������������������������������\r\n"
		"\r\n"
		"-->v1.2.1 �ڲ�棺\r\n"
		"1.���ӱ���Ͷ�ȡ�ݻ�·�����ܣ������´μ�����������ƥ��ʱ�����ݻ�����\r\n"
		"2.���Ӷ��ݻ�ģ��������޸ģ��߼����ã�\r\n"
		"3.���Ӹ�����־�鿴����\r\n"
		"4.�Ż����Խ����ʾ��ʽ����ͬ������Ĳ��Լ��ֿ���ʾ��ƥ����Ĳ���ʾ\r\n"
		"����������������������������������������������������������������\r\n"
		"\r\n"
		"-->v1.2 ��ʽ�棺\r\n"
		"1.���������ģ�幦�ܣ�����������ģ���������������ɵ�ϵͳ���\r\n"
		"2.���ӱ���ƥ�����Ĺ���\r\n"
		"3.���Ӹ߼�����ѡ������޸�һЩ����ʱ�ڲ����������ӷ��ϸ�������\r\n"
		"4.���Ӷ��ݻ�ѯ�ʵȴ����ʱ����ݻ����������޸ģ��߼����ã�\r\n"
		"5.���Ӷ���ʷ������ʱ��ļ�¼��ÿһ�����������¼����ʱ��\r\n"
		"6.�����״����м�⣬�״δ򿪸����ʱ���Զ�����ʹ��˵��\r\n"
		"7.�����˽��汳��ͼƬ�����ѿռ䱳������Ϊ͸����������������Ȼ\r\n"
		"����������������������������������������������������������������\r\n"
		"\r\n"
		"-->v1.1 ��ʽ�棺\r\n"
		"1.�Խ��沼�ֽ��д����������ԭ���Ĳ˵�����Ӧ���ܰ��Ⱥ�˳�򲼾ֵ�����\r\n"
		"2.��������ʾ������Ƹ������Ի�����������ͨ�û��Ĳ���ϰ��\r\n"
		"3.���뱳��ͼƬ��������������\r\n"
		"4.������ʷ��¼�ĳ�������ˢ�µ���ʾ��ʽ\r\n"
		"5.ȡ��ʹ�ð����е��ÿ���̨�Ĺ���\r\n"
		"6.���Ӷ�ѵ�����Ͳ��Լ�����˵����ģ��\r\n"
		"����������������������������������������������������������������\r\n"
		"\r\n"
		"-->v1.0 ���԰棺\r\n"
		"1.��ԭʼ�汾ʵ���˼򵥵Ŀ�ܺ���Ҫ���ܣ�����δ���κ�����\r\n"
		"2.����ȫ�����ϵ��˵���\r\n"
		"����������������������������������������������������������������");
}

//////////////////////////////////////////////////////////////////////////
// chooseType dialog used for App ChooseType when drag files to the dialog

class CChooseType : public CDialog
{
public:
	CChooseType() : CDialog(CChooseType::IDD), m_choosed(0){};
	enum { IDD = IDD_ChooseType };
protected:
	virtual void DoDataExchange(CDataExchange* pDX){
		CDialog::DoDataExchange(pDX);
		DDX_Radio(pDX, IDC_RADIO1, m_choosed);
	};
public:
	int m_choosed;
};

#pragma region Declare_MessageMap
IMPLEMENT_DYNCREATE(CImgMatchView, CFormView)

BEGIN_MESSAGE_MAP(CImgMatchView, CFormView)
	ON_COMMAND(ID_FILE_open1, &CImgMatchView::OnFileopen1)
	ON_COMMAND(ID_FILE_open2, &CImgMatchView::OnFileopen2)
	ON_COMMAND(ID_match_all, &CImgMatchView::OnMatchAll)
	ON_COMMAND(ID_Save_Match, &CImgMatchView::OnSaveMatch)
	ON_BN_CLICKED(IDC_Clear_log, &CImgMatchView::OnClearLog)
	ON_COMMAND(ID_match_surf, &CImgMatchView::OnMatchSurf)
	ON_COMMAND(ID_Clear, &CImgMatchView::OnClearLog)
	ON_COMMAND(ID_Clear_all, &CImgMatchView::OnClearAll)
	ON_COMMAND(ID_train_p, &CImgMatchView::OnTrainP)
	ON_COMMAND(ID_train_n, &CImgMatchView::OnTrainN)
	ON_COMMAND(ID_Show_Train_P, &CImgMatchView::OnShowTrainP)
	ON_COMMAND(ID_Show_Train_N, &CImgMatchView::OnShowTrainN)
	ON_COMMAND(ID_Clear_p, &CImgMatchView::OnClearP)
	ON_COMMAND(ID_Clear_N, &CImgMatchView::OnClearN)
	ON_COMMAND(ID_Show_Model, &CImgMatchView::OnShowModel)
	ON_COMMAND(ID_show_obj1, &CImgMatchView::OnShowObj1)
	ON_COMMAND(ID_show_obj2, &CImgMatchView::OnShowObj2)
	ON_COMMAND(ID_Show_Test, &CImgMatchView::OnShowTest)
	ON_COMMAND(ID_Start_Evolution, &CImgMatchView::OnStartEvolution)
	ON_COMMAND(ID_Add_Test, &CImgMatchView::OnAddTest)
	ON_COMMAND(ID_Clear_Test, &CImgMatchView::OnClearTest)
	ON_COMMAND(ID_Start_Match, &CImgMatchView::OnStartMatch)
	ON_COMMAND(ID_Clear_Train, &CImgMatchView::OnClearTrain)
	ON_COMMAND(ID_UseHelp, &CImgMatchView::OnUseHelp)
	ON_COMMAND(ID_Open_Model_many, &CImgMatchView::OnOpenModelMany)
	ON_BN_CLICKED(IDC_train_help, &CImgMatchView::OnTrainHelp)
	ON_BN_CLICKED(IDC_test_help, &CImgMatchView::OnTestHelp)
	ON_COMMAND(ID_AdvancedSet, &CImgMatchView::OnAdvancedSet)
	ON_BN_CLICKED(IDC_SaveMatch, &CImgMatchView::OnSavematch)
	ON_COMMAND(ID_saveEvoPath, &CImgMatchView::OnSaveEvoPath)
	ON_COMMAND(ID_readEvoPath, &CImgMatchView::OnReadEvoPath)
	ON_COMMAND(ID_updateLog, &CImgMatchView::OnUpdateLog)
	ON_EN_VSCROLL(IDC_log, &CImgMatchView::OnEnVscrollLog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_CLOSE()
	ON_COMMAND(ID_readModelTrain, &CImgMatchView::OnReadModelTrain)
	ON_COMMAND(ID_saveModelTrain, &CImgMatchView::OnSaveModelTrain)
	ON_COMMAND(ID_Quit, &CImgMatchView::OnQuit)
	ON_COMMAND(IDD_ResizeWindow, &CImgMatchView::OnResizeWindow)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()
#pragma endregion

//����Ƿ�ʹ�ö��̼߳���(��imgPro.h�ж���): #define b_multiThread 0/1
//֧��ͼƬ����С(��imgPro.h���Ѷ���) const int MAXSIZE = 1000;

CImgMatchView::CImgMatchView(): CFormView(CImgMatchView::IDD)
{
	m_bmpBackground.LoadResource(IDB_BITMAP1);
	ml.setML(Ch_Num,1,.75,Dlg.EvoCol);
	filePath1 = filePath2 = _T("");
	img1 = img2 = 0;
	log = "��ӭʹ�ñʼ�����ƥ��ϵͳ������������鿴ʹ�ð�������ݼ�F2��\r\n\r\n���ٶ�ȡģ���ѵ����·���밴Ctrl+R\r\n\r\n���ٶ�ȡ�ݻ�·���밴R\r\n";
	for(int i=0;i<log_num;i++)
		logg[i].Empty();
	train.p_num = train.n_num = 0;
	for(int j=0;j<10;j++)
		model.path[j].Empty();
	model.n = 0;
	test.num = 0;
	memset(test.times,0,sizeof(test.times));
	Evolution = 0;
	resetP_N = 1;
	matchlog.Empty();
	EvoPath.Empty();
	pStatues = 0;
	for(int i=0;i<100;++i)
		DragImgPath[i].Empty();
	DragEvoPath.Empty();
	DragModelTrainPath.Empty();
#ifdef _DEBUG
	//hLogFile = CreateFile("memleak.log", GENERIC_WRITE, FILE_SHARE_WRITE|FILE_SHARE_READ,\
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//������־�ļ�
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);//��warn��������ݶ�������ļ���ע��dump�ı��漶��Ϊwarning��
	_CrtSetReportFile(_CRT_WARN, hLogFile);//����־�ļ�����Ϊ�澯������ļ�
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );//���۳�����ʲô�ط��˳������Զ����� _CrtDumpMemoryLeaks

#define new  new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
	//ofstream out("log",ios::out);
	//out.close();

	CreateDirectory("Log", NULL);	//����������־�ļ����ļ���
	DeleteFile("Log\\detail-log.txt"); 
	DeleteFile("Log\\time-log.txt");
	DeleteFile("Log\\dbError-log.txt");
	DeleteFile("Log\\match-log.txt");
}

CImgMatchView::~CImgMatchView()
{
	DeleteFile("best.pth");
	DeleteFile("present.pth");
	DeleteFile("tmp.txt");
	DeleteFile("log");
}

void CImgMatchView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_log, log);
	DDV_MaxChars(pDX, log, 1000000000);
}

BOOL CImgMatchView::PreCreateWindow(CREATESTRUCT& cs)
{
	pstyle = &cs;
	return CFormView::PreCreateWindow(cs);
}

UINT first_help(void*pp){
	((CImgMatchView*)pp)->OnUseHelp();
	return 0;
}

void CImgMatchView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	CMainFrame *pFrame = (CMainFrame*)GetParent();
	pStatues = &pFrame->m_wndStatusBar;
	pStatues->SetPaneInfo(0,0,pStatues->GetPaneStyle(0),355);
	pStatues->SetPaneInfo(1,1,pStatues->GetPaneStyle(1),298);
	pStatues->SetPaneInfo(2,2,pStatues->GetPaneStyle(2),40);

	pMF = ((CMainFrame *)AfxGetMainWnd());
	pMF->m_wndStatusBar.GetItemRect(1,&myr);
	if(!pMF->m_bCreated)
	{
		pMF->m_progress.Create(WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN, myr, &pMF->m_wndStatusBar,1);
		pMF->m_progress.SetStep(1);
		pMF->m_bCreated = 1;
	}
	DB_table myDB;
	if (!PathFileExists(myDB.m_dbName))
	{
		AfxBeginThread(first_help,this);
	}
	initDB();
	GetDlgItem(IDC_many_model)->SetFocus();
}
inline CString printDateTime(CString s="���һ�β���ʱ�䣺") {
	char tmpbuf[128];
	char tmpbuf2[128];
	CString now = "",tmp,tmpName;
	time_t now_time=time(NULL);
	struct tm *newtime=localtime(&now_time);
	if(s=="time")	//���Ա��浱ǰȫ��״̬���ļ�
	{
		strftime(tmpbuf,128,"%Y%m%d",newtime);
		strftime(tmpbuf2,128,"%H%M%S",newtime);
		Screen(strcat(tmpbuf,tmpbuf2));
		return "";
	}
	strftime(tmpbuf,128,"%Y/%m/%d  ",newtime);
	strftime(tmpbuf2,128,"%H:%M:%S",newtime);
	now.Format(_T("%s%s%s"),s,tmpbuf,tmpbuf2);
	return now;
}

void CImgMatchView::updatelog(){
	InvalidateRect(&r,1);
	SetDlgItemText(IDC_log,log+printDateTime());
	CEdit* pEdit = ((CEdit*)GetDlgItem(IDC_log));
	pEdit->LineScroll(pEdit->GetLineCount());
}
#pragma region SimpleMatch
void CImgMatchView::OnShowObj1()
{
	showImg(img1,"�Ա�ͼ1","��ʾ�Ա�ͼ1����");
}

void CImgMatchView::OnShowObj2()
{
	showImg(img2,"�Ա�ͼ2","��ʾ�Ա�ͼ2����");
}

//��ղ�����ʷ��¼
void CImgMatchView::OnClearLog()
{
	log.Empty();
	for(int i=0;i<log_num;i++)
		logg[i].Empty();
	UpdateData(false);
	updatelog();
}

void CImgMatchView::OnClearAll()
{
	LOG(">>��������\n\n")
	filePath1.Empty();
	filePath2.Empty();
	EvoPath.Empty();
	train.p_num = train.n_num = 0;
	releaseImg(&img1);
	releaseImg(&img2);
	model.n = 0;
	OnClearLog();
	
	train.p_num = 0;
	train.p_num = 0;
	test.num = 0;
	memset(test.times,0,sizeof(test.times));

	DeleteFile("p_n.txt");
	DeleteFile("test.txt");
	DeleteFile("best.pth");

	for(int i=log_num-1;i>0;i--)
		logg[i] = logg[i-1];
	logg[0].Format(_T("��������������\r\n-------------�����ָ���-------------\r\n\r\n"));
	log = logg[log_num-1];
	for(int i=log_num-2;i>=0;i--)
		log += logg[i];
	UpdateData(false);
	updatelog();
}

void CImgMatchView::OnFileopen1()
{
	strcpy(info,"");
	char fileFormat[] = _T("JPEG (*.jpg)|*.jpg;*.jpeg|PNG (*.png)|*.png|BMP (*.bmp)|*.bmp|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE,0,0,OFN_FILEMUSTEXIST,fileFormat);
    if(dlg.DoModal()==IDOK)
	{
		CString _filePath1 = dlg.GetPathName();
		char* _file1 = (LPSTR)(LPCTSTR)_filePath1 ;
		IplImage* _img1 = loadImg(_file1);
		if(_img1){
			for(int i=log_num-1;i>0;i--)
				logg[i] = logg[i-1];
			logg[0].Format(_T("�Ա�ͼ1:\r\n%s-------------�����ָ���-------------\r\n\r\n"),info);
			log = logg[log_num-1];
			for(int i=log_num-2;i>=0;i--)
				log += logg[i];
			UpdateData(false);
			updatelog();
			filePath1 = _filePath1;
			releaseImg(&img1);
			img1 = _img1;
		}
	}
}

void CImgMatchView::OnFileopen2()
{
	strcpy(info,"");
	char fileFormat[] = _T("JPEG (*.jpg)|*.jpg;*.jpeg|PNG (*.png)|*.png|BMP (*.bmp)|*.bmp|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE,0,0,OFN_FILEMUSTEXIST,fileFormat);
    if(dlg.DoModal()==IDOK)
	{
		CString _filePath2 = dlg.GetPathName();
		char* _file2 = (LPSTR)(LPCTSTR)_filePath2 ;
		IplImage* _img2 = loadImg(_file2);
		if(_img2){
			for(int i=log_num-1;i>0;i--)
				logg[i] = logg[i-1];
			logg[0].Format(_T("�Ա�ͼ2:\r\n%s-------------�����ָ���-------------\r\n\r\n"),info);
			log = logg[log_num-1];
			for(int i=log_num-2;i>=0;i--)
				log += logg[i];
			UpdateData(false);
			updatelog();
			filePath2 = _filePath2;
			releaseImg(&img2);
			img2 = _img2;
		}
	}
}

void CImgMatchView::OnMatchAll()
{
	strcpy(info,"");
	if(filePath1 && filePath2 && filePath1[0] && filePath2[0]){
		t.getTargetInfo(filePath1,-2,0);
		t2.getTargetInfo(filePath2,-2,0);
		t.compare(t2,0,0,0,Dlg.ratio);
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		logg[0].Format(_T("%s-------------�����ָ���-------------\r\n\r\n"),info);
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
	}else
		MessageBox("ͼ��ָ����Ч������������Чͼ�����ʹ�øù���","ƥ��ͼ�����",MB_ICONERROR);
}

void CImgMatchView::OnSaveMatch()
{
	if(find_obj_match){
		char fileFormat[] = _T("JPEG (*.jpg)|*.jpg;*.jpeg|PNG (*.png)|*.png|BMP (*.bmp)|*.bmp|All Files (*.*)|*.*||");
		CFileDialog dlg(false,"jpg",0,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,fileFormat);
		if(dlg.DoModal()==IDOK)
		{
			CString path = dlg.GetPathName();
			char *path_c = (LPSTR)(LPCTSTR)path ;
			saveImg(path_c,find_obj_match);
		}
	}else
		MessageBox("ͼ��ָ����Ч������������Чͼ���ۺ�ƥ�����ʹ�øù���","����ͼ�����",MB_ICONERROR);
}

void CImgMatchView::OnMatchSurf()
{
	strcpy(info,"");
	if(filePath1 && filePath2 && filePath1[0] && filePath2[0]){
		find_obj(filePath1,filePath2,0,1);
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		logg[0].Format(_T("%s-------------�����ָ���-------------\r\n\r\n"),info);
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
	}else
		MessageBox("ͼ��ָ����Ч������������Чͼ�����ʹ�øù���","surf�ǵ������",MB_ICONERROR);

}
#pragma endregion
void CImgMatchView::OnTrainP()
{
	LOG(">>������ѵ����\n")
	char fileFormat[] = _T("JPEG (*.jpg)|*.jpg;*.jpeg|PNG (*.png)|*.png|BMP (*.bmp)|*.bmp|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE,0,0,OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT,fileFormat);
	int check=0;
	if(DragImgPath[0]=="")
		check = (dlg.DoModal()==IDOK);
	if(DragImgPath[0][0] || check)	//�������ļ�·���б� ���� ��ȡ���ļ�
	{
		int num = train.p_num;
		POSITION pos = dlg.GetStartPosition();
		int jj=0;
		bool loop = DragImgPath[0]=="" ? pos!=0 : DragImgPath[jj][0]!=0;
		while(loop){
			if(DragImgPath[0]!=""){
				train.p[train.p_num]=DragImgPath[jj++];
				loop = DragImgPath[jj][0]!=0;
			}else{
				train.p[train.p_num]=dlg.GetNextPathName(pos);
				loop = pos!=0;
			}
			LOG(train.p[train.p_num]);
			if(!(tmpimg = loadImg(train.p[train.p_num],0,0,1,0))){
				train.p_num--;
				LOG("\t����ʧ�ܣ�������")
			}else if(tmpimg->width>MAXSIZE || tmpimg->height>MAXSIZE)
			{
				char exit_info[1000];
				sprintf(exit_info,("ͼ��%s�ߴ�������ȴ���Ϊ%d*%d���������룡\r\n\r\n���Զ�������ͼ��"),train.p[train.p_num],MAXSIZE,MAXSIZE);
				MessageBox(exit_info,"��ȡͼ����Ϣʧ��",0);
				train.p_num--;
				LOG("\t�ߴ����������");
			}
			releaseImg(&tmpimg);
			train.p_num++;
			LOG("\n");
		}
		LOG("��������ѵ������ȡ��ϡ�����\n");
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		if(train.p_num-num>0){
			tmp.Format(_T("����������%d����ѵ����:\r\n"),train.p_num-num);
			for(int i=num;i<train.p_num;i++){
				logg[0].Format(_T("%s%s\r\n"),tmp,train.p[i]);
				tmp = logg[0];
			}
			logg[0].Format(_T("%s-------------�����ָ���-------------\r\n\r\n"),tmp);
			Evolution = 0;
		}else
			logg[0].Format(_T("δ�ɹ�������ѵ������������!\r\n-------------�����ָ���-------------\r\n\r\n"));
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
	}
	LOG("<<����������ѵ����������\n\n")
}

void CImgMatchView::OnTrainN()
{
	LOG(">>���븺ѵ����\n")
	char fileFormat[] = _T("JPEG (*.jpg)|*.jpg;*.jpeg|PNG (*.png)|*.png|BMP (*.bmp)|*.bmp|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE,0,0,OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT,fileFormat);
	int check=0;
	if(DragImgPath[0]=="")
		check = (dlg.DoModal()==IDOK);
	if(DragImgPath[0][0] || check)	//�������ļ�·���б� ���� ��ȡ���ļ�
	{
		int num = train.n_num;
		POSITION pos = dlg.GetStartPosition();
		int jj=0;
		bool loop = DragImgPath[0]=="" ? pos!=0 : DragImgPath[jj][0]!=0;
		while(loop){
			if(DragImgPath[0]!=""){
				train.n[train.n_num]=DragImgPath[jj++];
				loop = DragImgPath[jj][0]!=0;
			}else{
				train.n[train.n_num]=dlg.GetNextPathName(pos);
				loop = pos!=0;
			}
			LOG(train.n[train.n_num]);
			if(!(tmpimg = loadImg(train.n[train.n_num],0,0,1,0))){
				train.n_num--;
				LOG("\t����ʧ�ܣ�������")
			}else if(tmpimg->width>MAXSIZE || tmpimg->height>MAXSIZE)
			{
				char exit_info[1000];
				sprintf(exit_info,("ͼ��%s�ߴ�������ȴ���Ϊ%d*%d���������룡\r\n\r\n���Զ�������ͼ��"),train.n[train.n_num],MAXSIZE,MAXSIZE);
				MessageBox(exit_info,"��ȡͼ����Ϣʧ��",0);
				train.n_num--;
				LOG("\t�ߴ����������")
			}
			releaseImg(&tmpimg);
			train.n_num++;
			LOG("\n")
		}
		LOG("��������ѵ������ȡ��ϡ�����\n")
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		if(train.n_num-num>0){
			tmp.Format(_T("����������%d����ѵ����:\r\n"),train.n_num-num);
			for(int i=num;i<train.n_num;i++){
				logg[0].Format(_T("%s%s\r\n"),tmp,train.n[i]);
				tmp = logg[0];
			}
			logg[0].Format(_T("%s-------------�����ָ���-------------\r\n\r\n"),tmp);
			Evolution = 0;
		}else
			logg[0].Format(_T("δ�ɹ�������ѵ������������!\r\n-------------�����ָ���-------------\r\n\r\n"));
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
	}
	LOG("<<�������븺ѵ����������\n\n")
}

void CImgMatchView::OnShowTrainP()
{
	for(int i=log_num-1;i>0;i--)
		logg[i] = logg[i-1];
	if(train.p_num>0){
		tmp.Format(_T("��ǰ������������ѵ����:\r\n"));
		for(int i=0;i<train.p_num;i++){
			logg[0].Format(_T("%s%s\r\n"),tmp,train.p[i]);
			tmp = logg[0];
		}
		logg[0].Format(_T("%s-------------�����ָ���-------------\r\n\r\n"),tmp);
	}else
	logg[0].Format(_T("��ǰ��δ������ѵ������\r\n-------------�����ָ���-------------\r\n\r\n"));
	log = logg[log_num-1];
	for(int i=log_num-2;i>=0;i--)
		log += logg[i];
	UpdateData(false);
	updatelog();
}

void CImgMatchView::OnShowTrainN()
{
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		if(train.n_num>0){
			tmp.Format(_T("��ǰ���������и�ѵ����:\r\n"));
			for(int i=0;i<train.n_num;i++){
				logg[0].Format(_T("%s%s\r\n"),tmp,train.n[i]);
				tmp = logg[0];
			}
			logg[0].Format(_T("%s-------------�����ָ���-------------\r\n\r\n"),tmp);
		}else
			logg[0].Format(_T("��ǰ��δ���븺ѵ������\r\n-------------�����ָ���-------------\r\n\r\n"));
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
}

void CImgMatchView::OnClearP()
{
	LOG(">>���������Լ�\n\n")
	if(train.p_num!=0){
		train.p_num = 0;
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		logg[0].Format(_T("����յ�ǰ���������ѵ����\r\n-------------�����ָ���-------------\r\n\r\n"));
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
	}else
		OnShowTrainP();
	resetP_N = 1;
}

void CImgMatchView::OnClearN()
{
	LOG(">>���ø����Լ�\n\n")
	if(train.n_num!=0){
		train.n_num = 0;
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		logg[0].Format(_T("����յ�ǰ������ĸ�ѵ����\r\n-------------�����ָ���-------------\r\n\r\n"));
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
	}else
		OnShowTrainN();
	resetP_N = 1;
}

void CImgMatchView::OnClearTrain()
{
	LOG(">>����ѵ����\n\n")
	if(train.p_num!=0){
		train.p_num = 0;
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		logg[0].Format(_T("����յ�ǰ���������ѵ����\r\n-------------�����ָ���-------------\r\n\r\n"));
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
	}else
		OnShowTrainP();
	if(train.n_num!=0){
		train.n_num = 0;
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		logg[0].Format(_T("����յ�ǰ������ĸ�ѵ����\r\n-------------�����ָ���-------------\r\n\r\n"));
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
	}else
		OnShowTrainN();
	resetP_N = 1;
}

void CImgMatchView::OnOpenModelMany()
{
	LOG(">>����ģ��ͼ\n");
	runing = 1;
	char fileFormat[] = _T("JPEG (*.jpg)|*.jpg;*.jpeg|PNG (*.png)|*.png|BMP (*.bmp)|*.bmp|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE,0,0,OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT,fileFormat);
	int check=0;
	if(DragImgPath[0]=="")
		check = (dlg.DoModal()==IDOK);
    if(DragImgPath[0][0] || check)	//�������ļ�·���б� ���� ��ȡ���ļ�
	{
		try{
			model.n = 0;
			POSITION pos = dlg.GetStartPosition();
			int jj=0;
			bool loop = DragImgPath[0]=="" ? pos!=0 : DragImgPath[jj][0]!=0;
			while(loop){
				if(model.n==10){		//���ֻ����10��ģ��
					MessageBox("���ֻ��������10��ģ�壬�ѽ�ǰ10����Ϊģ��","��ܰ��ʾ");
					break;
				}
				if(DragImgPath[0]!=""){
					model.path[model.n]=DragImgPath[jj++];
					loop = DragImgPath[jj][0]!=0;
				}else{
					model.path[model.n]=dlg.GetNextPathName(pos);
					loop = pos!=0;
				}
				LOG(model.path[model.n]);
				if(!(tmpimg = loadImg(model.path[model.n],0,0,1,0))){
					model.n--;
					LOG("\t����ʧ�ܣ�������");
				}else if(tmpimg->width>MAXSIZE || tmpimg->height>MAXSIZE)
				{
					char exit_info[1000];
					sprintf(exit_info,("ͼ��%s�ߴ�������ȴ���Ϊ%d*%d���������룡\r\n\r\n\r\n���Զ�������ͼ��"),model.path[model.n],MAXSIZE,MAXSIZE);
					MessageBox(exit_info,"��ȡͼ����Ϣʧ��",0);
					model.n--;
					LOG("\t�ߴ����������");
				}
				releaseImg(&tmpimg);
				model.n++;
				LOG("\n");
			}
			LOG("������ģ��ͼ��ȡ��ϡ�����\n");
		}
		catch(...)
		{
			LOG("\nERROR: ��ȡģ��ͼʱ�����쳣\n\n");
			runing = 0;
			MessageBox("�ǳ���Ǹ���ڶ�ȡģ��ͼʱ�����쳣����رպ�����","���г���",0);
			return;
		}
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		if(model.n>0){
			tmp.Format(_T("����������%d��ģ��:\r\n"),model.n);
			for(int i=0;i<model.n;i++){
				logg[0].Format(_T("%s%s\r\n"),tmp,model.path[i]);
				tmp = logg[0];
			}
			logg[0].Format(_T("%s-------------�����ָ���-------------\r\n\r\n"),tmp);
		}else
			logg[0].Format(_T("δ�ɹ�����ģ��ͼ��������!\r\n-------------�����ָ���-------------\r\n\r\n"));
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
		Evolution = 0;
		//������ǰ�����ѵ�����Ͳ��Լ�
		train.p_num = 0;
		train.n_num = 0;
		test.num = 0;
		resetP_N = 1;
	}
	runing = 0;
	LOG("<<��������ģ��ͼ������\n\n");
}

void CImgMatchView::OnShowModel()
{
	if(model.n>0){
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		tmp.Format(_T("��ǰ������ģ��ͼ:\r\n"));
		for(int i=0;i<model.n;i++){
			logg[0].Format("%s%s\r\n",tmp,model.path[i]);
			tmp = logg[0];
		}
		logg[0].Format("%s-------------�����ָ���-------------\r\n\r\n",tmp);
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
	}else{
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		logg[0].Format(_T("��ǰ��δ����ģ��ͼ��\r\n-------------�����ָ���-------------\r\n\r\n"));
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
	}
}

void CImgMatchView::OnAddTest()
{
	LOG(">>���Ӳ��Լ�\n\n");
	runing = 1;
	strcpy(info,"");
	char fileFormat[] = _T("JPEG (*.jpg)|*.jpg;*.jpeg|PNG (*.png)|*.png|BMP (*.bmp)|*.bmp|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE,0,0,OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT,fileFormat);
	int check=0;
	if(DragImgPath[0]=="")		//���û�������ļ���Ϊ���Լ���ʹ���ļ��Ի���
		check = (dlg.DoModal()==IDOK);
	if(DragImgPath[0][0] || check)	//�������ļ�·���б� ���� ��ȡ���ļ�
	{
		int num = test.num;
		POSITION pos = dlg.GetStartPosition();
		int jj=0;
		bool loop = DragImgPath[0]=="" ? pos!=0 : DragImgPath[jj][0]!=0;
		while(loop){
			if(DragImgPath[0]!=""){
				test.p[test.num]=DragImgPath[jj++];
				loop = DragImgPath[jj][0]!=0;
			}else{
				test.p[test.num]=dlg.GetNextPathName(pos);
				loop = pos!=0;
			}
			LOG(test.p[test.num]);
			if(!(tmpimg = loadImg(test.p[test.num],0,0,1,0))){
				test.num--;
				LOG("\t����ʧ�ܣ�������");
			}else if(tmpimg->width>MAXSIZE || tmpimg->height>MAXSIZE)
			{
				char exit_info[1000];
				sprintf(exit_info,("ͼ��%s�ߴ�������ȴ���Ϊ%d*%d���������룡\r\n\r\n\r\n���Զ�������ͼ��"),test.p[test.num],MAXSIZE,MAXSIZE);
				MessageBox(exit_info,"��ȡͼ����Ϣʧ��",0);
				test.num--;
				LOG("\t�ߴ����������")
			}
			releaseImg(&tmpimg);
			test.num++;
			LOG("\n")
		}
		LOG("���������Լ���ȡ��ϡ�����\n");
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		if(test.num-num>0){
			tmp.Format(_T("����������%d�����Լ�:\r\n"),test.num-num);
			for(int i=num;i<test.num;i++){
				logg[0].Format(_T("%s%s\r\n"),tmp,test.p[i]);
				tmp = logg[0];
			}
			logg[0].Format(_T("%s-------------�����ָ���-------------\r\n\r\n"),tmp);
			test.times[test.times[9]] = test.num-1;
			test.times[9]++;
		}else
			logg[0].Format(_T("δ�ɹ�������Լ���������!\r\n-------------�����ָ���-------------\r\n\r\n"));
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
	}
	runing = 0;
	LOG("<<�������Ӳ��Լ�������\n\n");
	if(Evolution==1 && test.num>0)
		if(MessageBox("���������˲��Լ����Ƿ�����ƥ�䣿","��ʼƥ������",MB_YESNO)==IDYES)
			OnStartMatch();
}

void CImgMatchView::OnShowTest()
{
	for(int i=log_num-1;i>0;i--)
		logg[i] = logg[i-1];
	if(test.num>0){
		tmp.Format(_T("��ǰ���������в��Լ�:\r\n"));
		for(int i=0;i<test.num;i++){
			logg[0].Format(_T("%s%s\r\n"),tmp,test.p[i]);
			tmp = logg[0];
		}
		logg[0].Format(_T("%s-------------�����ָ���-------------\r\n\r\n"),tmp);
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
	}else{
		logg[0].Format(_T("��ǰ��δ������Լ���\r\n-------------�����ָ���-------------\r\n\r\n"));
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
	}
	UpdateData(false);
	updatelog();
}

void CImgMatchView::OnClearTest()
{
	LOG(">>���ò��Լ�\n\n")
	if(test.num>0){
		test.num = 0;
		memset(test.times,0,sizeof(test.times));
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		logg[0].Format(_T("����յ�ǰ������Ĳ��Լ�\r\n-------------�����ָ���-------------\r\n\r\n"));
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
	}else
		OnShowTest();
}

UINT evoTrain(void* pp){
	long time1 = clock(),time2;
	CImgMatchView* pView = (CImgMatchView*)pp;
	MSG &msg = pView->msg;
	Target &t3 = pView->t3, &t4 = pView->t4;
	for(int i=0;i<pView->train.p_num;i++){		//��ѵ����
		if(pView->train.done_p[i])
			continue;
		pView->train.done_p[i]=1;
		double best = 0;
		int index = 0;
		for(int j=0;j<pView->model.n && pView->model.n>1;j++)
		{
			t3.getTargetInfo(pView->model.path[j]);
			t4.getTargetInfo(pView->train.p[i]);
			double re = t3.compare(t4,0,1,1,pView->ratio);
			if(best<re)
			{
				index = j;
				best = re;
			}
			time2 = clock();
			if (time2 - time1 > 50 && PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)){
				SendMessage(0,msg.message, msg.wParam, msg.lParam);
				time1 = time2;
				Sleep(5);
			}
			LOG("i="<<i<<" j="<<j<<">\n");
			pView->pMF->m_progress.StepIt();
		}
		t3.getTargetInfo(pView->model.path[index]);
		t4.getTargetInfo(pView->train.p[i]);
		t3.compare(t4,"p_n.txt",1,0,pView->ratio);
		pView->pMF->m_progress.StepIt();
		if(pView->model.n==1)
			pView->pMF->m_progress.StepIt();
	}
	for(int i=0;i<pView->train.n_num;i++){		//��ѵ����
		if(pView->train.done_n[i])
			continue;
		pView->train.done_n[i]=1;
		for(int j=0;j<pView->model.n;j++)
		{
			t3.getTargetInfo(pView->model.path[j]);
			t4.getTargetInfo(pView->train.n[i]);
			t3.compare(t4, "p_n.txt", 0, 0, pView->ratio);
			time2 = clock();
			if (time2 - time1 > 50 && PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)){
				SendMessage(0,msg.message, msg.wParam, msg.lParam);
				time1 = time2;
				Sleep(5);
			}
			LOG("i="<<i<<" j="<<j<<">\n");
			pView->pMF->m_progress.StepIt();
		}
	}
	pView->runing = 0;
	return 0;
}

void CImgMatchView::OnStartEvolution()
{
	LOG(">>��ʼ�ݻ�ѵ��\n");
	runing = 1;
	_CrtMemCheckpoint(&cc1);	//����ڴ�й¶
	if(model.n && train.p_num){// && train.n_num---�����Ը�ѵ������Ҫ�󣬼����Բ����븺ѵ����
		memcpy(ratio,Dlg.ratio,sizeof(Dlg.ratio));
		int nUpper=0;	//���������ֵ
		long time = clock(),time1 = time,time2=0;
		train.done_p[0]=train.done_n[0]=1;
		LOG(">>>>���ڶ�ȡѵ����...ģ�������"<<model.n<<"  ѵ�������� ����"<<train.p_num<<" ����"<<train.n_num<<endl);
		CString s1="���ڶ�ȡѵ��������ʼѵ��...",s2;
		pStatues->SetPaneText(0,s1);
		pStatues->SetPaneText(2,_T("��ȡ��"));
		static int lastp = train.p_num, lastn = train.n_num;
#pragma region Training
		try{
		if(resetP_N){					//����ѵ�������������ݻ�
			LOG("���������������������ݻ����������\n");
			DeleteFile("p_n.txt");
			resetP_N = 0;
			nUpper = train.p_num*(model.n+1)+train.n_num*model.n;
			memset(train.done_p,0,train.p_num);
			memset(train.done_n,0,train.n_num);
			LOG("���������ڶ�ȡ��ѵ����������\n");
			pMF->m_progress.SetRange(0,nUpper);
			if(b_multiThread)
				AfxBeginThread(evoTrain,this);
			for(int i=0;i<train.p_num;i++){		//��ѵ����
				if(train.done_p[i])
					continue;
				train.done_p[i]=1;
				double best = 0;
				int index = 0;
				for(int j=0;j<model.n && model.n>1;j++)
				{
					int ttt = clock();
					t.getTargetInfo(model.path[j]);
					//LOGT("getTargetInfo1:\t"<<clock()-ttt<<endl);ttt = clock();
					t2.getTargetInfo(train.p[i]);
					//LOGT("getTargetInfo2:\t"<<clock()-ttt<<endl);ttt = clock();
					double re = t.compare(t2,0,1,1,ratio);
					//LOGT("compare:\t"<<clock()-ttt<<endl);
					if(best<re)
					{
						index = j;
						best = re;
					}
					time2 = clock();
					if (time2 - time1 > 50 && PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)){
						SendMessage(msg.message, msg.wParam, msg.lParam);
						time1 = time2;
						Sleep(5);
					}
					if (PeekMessage(&msg,(HWND)NULL, 0, 0, PM_REMOVE))
						SendMessage(msg.message, msg.wParam, msg.lParam);
					LOG("i="<<i<<" j="<<j<<"\n");
					pMF->m_progress.StepIt();
					s2.Format(_T("%s �ѽ��� %.1lf %%"),s1,pMF->m_progress.GetPos()/0.01/nUpper);
					pStatues->SetPaneText(0,s2);
					s2.Format(_T("��ʱ��%.2f s"),(time2-time)/1000.0);
					pStatues->SetPaneText(3,s2);
				}
				t.getTargetInfo(model.path[index]);
				t2.getTargetInfo(train.p[i]);
				t.compare(t2,"p_n.txt",1,0,ratio);
				pMF->m_progress.StepIt();
				if(model.n==1)
					pMF->m_progress.StepIt();
				s2.Format(_T("%s �ѽ��� %.1lf %%"),s1,pMF->m_progress.GetPos()/0.01/nUpper);
				pStatues->SetPaneText(0,s2);
				s2.Format(_T("��ʱ��%.2f s"),(clock()-time)/1000.0);
				pStatues->SetPaneText(3,s2);
			}
			LOG("���������ڶ�ȡ��ѵ����������\n");
			for(int i=0;i<train.n_num;i++){		//��ѵ����
				if(train.done_n[i])
					continue;
				train.done_n[i]=1;
				for(int j=0;j<model.n;j++)
				{
					t.getTargetInfo(model.path[j]);
					t2.getTargetInfo(train.n[i]);
					t.compare(t2, "p_n.txt", 0, 0, ratio);
					time2 = clock();
					if (time2 - time1 > 50 && PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)){
						SendMessage(msg.message, msg.wParam, msg.lParam);
						time1 = time2;
						Sleep(5);
					}
					LOG("i="<<i<<" j="<<j<<"\n");
					pMF->m_progress.StepIt();
					s2.Format(_T("%s �ѽ��� %.1lf %%"),s1,pMF->m_progress.GetPos()/0.01/nUpper);
					pStatues->SetPaneText(0,s2);
					s2.Format(_T("��ʱ��%.2f s"),(time2-time)/1000.0);
					pStatues->SetPaneText(3,s2);
				}
			}
		}else if(lastp!=train.p_num || lastn != train.n_num){	//�������������ѵ������ֱ�Ӽ����µ����ݽ�ģ��
			LOG("����������������ݻ����������\n���������ڶ�ȡ��ѵ����("<<train.p_num-lastp<<")������\n");
			memset(&train.done_p[lastp],0,train.p_num-lastp);
			memset(&train.done_n[lastn],0,train.n_num-lastn);
			nUpper = (train.p_num-lastp)*(model.n+1) + (train.n_num-lastn)*model.n;
			pMF->m_progress.SetRange(0,nUpper);
			if(b_multiThread)
				AfxBeginThread(evoTrain,this);
			for(int i=lastp;i<train.p_num;i++){		//���� ��ѵ����
				if(train.done_p[i])
					continue;
				train.done_p[i]=1;
				double best = 0;
				int index = 0;
				for(int j=0;j<model.n && model.n>1;j++)
				{
					t.getTargetInfo(model.path[j]);
					t2.getTargetInfo(train.p[i]);
					double re = t.compare(t2,0,1,1,ratio);
					if(best<re)
					{
						index = j;
						best = re;
					}
					time2 = clock();
					if (time2 - time1 > 50 && PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)){
						SendMessage(msg.message, msg.wParam, msg.lParam);
						time1 = time2;
						Sleep(5);
					}
					LOG("i="<<i<<" j="<<j<<"\n");
						pMF->m_progress.StepIt();
					s2.Format(_T("%s �ѽ��� %.1lf %%"),s1,pMF->m_progress.GetPos()/0.01/nUpper);
					pStatues->SetPaneText(0,s2);
					s2.Format(_T("��ʱ��%.2f s"),(time2-time)/1000.0);
					pStatues->SetPaneText(3,s2);
				}
				t.getTargetInfo(model.path[index]);
				t2.getTargetInfo(train.p[i]);
				t.compare(t2,"p_n.txt",1,0,ratio);
				pMF->m_progress.StepIt();
				if(model.n==1)
					pMF->m_progress.StepIt();
				s2.Format(_T("%s �ѽ��� %.1lf %%"),s1,pMF->m_progress.GetPos()/0.01/nUpper);
				pStatues->SetPaneText(0,s2);
				s2.Format(_T("��ʱ��%.2f s"),(time2-time)/1000.0);
				pStatues->SetPaneText(3,s2);
			}
			LOG("���������ڶ�ȡ��ѵ����("<<train.n_num-lastn<<")������\n");
			for(int i=lastn;i<train.n_num;i++){		//���� ��ѵ����
				if(train.done_n[i])
					continue;
				train.done_n[i]=1;
				for(int j=0;j<model.n;j++)
				{
					t.getTargetInfo(model.path[j]);
					t2.getTargetInfo(train.n[i]);
					t.compare(t2, "p_n.txt", 0, 0, ratio);
					time2 = clock();
					if (time2 - time1 > 50 && PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)){
						SendMessage(msg.message, msg.wParam, msg.lParam);
						time1 = time2;
						Sleep(5);
					}
					LOG("i="<<i<<" j="<<j<<"\n");
					pMF->m_progress.StepIt();
					s2.Format(_T("%s �ѽ��� %.1lf %%"),s1,pMF->m_progress.GetPos()/0.01/nUpper);
					pStatues->SetPaneText(0,s2);
					s2.Format(_T("��ʱ��%.2f s"),(time2-time)/1000.0);
					pStatues->SetPaneText(3,s2);
				}
			}
		}
		}catch(...)
		{
			LOG("��ȡѵ����ʱ�����쳣\n\n");
			runing = 0;
			MessageBox("�ǳ���Ǹ���ڶ�ȡѵ����ʱ�����쳣����رպ�����","���г���",0);
			rename("Log","ErrorLog.txt");
			exit(0);
		}
#pragma endregion
		while(pMF->m_progress.GetPos()!=nUpper)
		{
			Sleep(5);
			if (PeekMessage(&msg,(HWND)NULL, 0, 0, PM_REMOVE))
				SendMessage(msg.message, msg.wParam, msg.lParam);
		}
		pMF->m_progress.SetPos(0);
		LOG("������ѵ������ȡ��ϡ�����\n��������ʼ�ݻ����̡�����\n");
		_CrtMemCheckpoint(&cc2);
		if(_CrtMemDifference(&cc3, &cc1, &cc2))
			_CrtMemDumpStatistics(&cc3);

		pStatues->SetPaneText(0,_T("ѵ�����Ѷ�ȡ���,���������ݻ����������ĵȴ�..."));
		pStatues->SetPaneText(2,_T("�ݻ���"));
		int dataNum = ml.loadDataFromFile("p_n.txt",-1,1,1);
		ml.setWait_Col(Dlg.waitTime,Dlg.EvoCol);
		ml.setSave(1);	//����˴��ݻ����·����Ԥ���ļ�
		ml.setModel(Dlg.absolut);
		LOG("�����������ݻ�:dataNum="<<dataNum<<"������\n");
		ml.startLearn(dataNum, pStatues, Dlg.permitError,Dlg.balance_ratio,(LPCTSTR)EvoPath);
		LOG("�������ݻ���ϡ�����\n");
		pStatues->SetPaneText(2,_T("���"));
		Evolution = 1;
		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		logg[0].Format(_T("%s\r\n-------------�����ָ���-------------\r\n\r\n"),ml_info);
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
		lastp = train.p_num, lastn = train.n_num;
	}else if(0==model.n)
		MessageBox("��������ģ��ͼ","�ݻ�����",MB_ICONERROR);
	else if(Evolution==1)
		MessageBox("��ǰδ�ҵ���ѵ������\n\n���Ѿ����ļ��ɹ���ȡ���ݻ�·��������ֱ���������ͼ����ƥ��","�ݻ�����",MB_ICONERROR);
	else
		MessageBox("����������ѵ����","�ݻ�����",MB_ICONERROR);
	runing = 0;
	LOG("<<�����ݻ�ѵ��������\n\n");
}

UINT match(void* pp){
	MSG msg;
	long  time1 = clock(), time2;
	CImgMatchView* pView = (CImgMatchView*)pp;
	for(int i=0;i<pView->test.num;i++)
	{
		if(pView->test.done[i])
			continue;
		pView->test.done[i] = 1;
		if(pView->model.n==1)	//��ģ��
		{
			pView->t3.getTargetInfo(pView->model.path[0]);
			pView->t4.getTargetInfo(pView->test.p[i]);
			pView->t3.compare(pView->t4,"test.txt",-1,0,pView->ratio);
			pView->pMF->m_progress.StepIt();
			pView->pMF->m_progress.StepIt();
			time2 = clock();
			if (time2 - time1 > 50 && PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)){
				SendMessage(0, msg.message, msg.wParam, msg.lParam);
				time1 = time2;
				Sleep(5);
			}
		}else{			//��ģ��
			double best = 0;
			int index = 0;
			for(int j=0;j<pView->model.n;j++)
			{
				pView->t3.getTargetInfo(pView->model.path[j]);
				pView->t4.getTargetInfo(pView->test.p[i]);
				double re = pView->t3.compare(pView->t4,0,-1,1,pView->ratio);//ע��˴�����ݻ����ٵ���ratio�Ļ��ͻ����δԤ�ڵĽ��
				if(best<re)
				{
					index = j;
					best = re;
				}
				time2 = clock();
				if (time2 - time1 > 50 && PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)){
					SendMessage(0,msg.message, msg.wParam, msg.lParam);
					time1 = time2;
					Sleep(5);
				}
				pView->pMF->m_progress.StepIt();
			}
			pView->t3.getTargetInfo(pView->model.path[index]);
			pView->t4.getTargetInfo(pView->test.p[i]);
			pView->t3.compare(pView->t4,"test.txt",-1,0,pView->ratio);
			pView->pMF->m_progress.StepIt();
		}
	}
	pView->runing = 0;
	return 0;
}

void CImgMatchView::OnStartMatch()
{
	LOG(">>��ʼƥ��\n");
	runing = 1;
	if(Evolution==1){
		if(test.num>0){
			long time = clock(),time1 = time,time2=0;
			memset(test.done,0,test.num);
			CString s1="���ڶ�ȡ���Լ�...",s2;
			pStatues->SetPaneText(0,_T(s1));
			pStatues->SetPaneText(2,_T("��ȡ��"));
			DeleteFile("test.txt");
			try{
				if(b_multiThread)
					AfxBeginThread(match,this);
				int nUpper = test.num*(model.n+1);
				pMF->m_progress.SetRange(0,nUpper);
				for(int i=0;i<test.num;i++)
				{
					if(test.done[i])
						continue;
					test.done[i] = 1;
					if(model.n==1)	//��ģ��
					{
						t.getTargetInfo(model.path[0]);
						t2.getTargetInfo(test.p[i]);
						t.compare(t2,"test.txt",-1,0,ratio);
						pMF->m_progress.StepIt();
						pMF->m_progress.StepIt();
						s2.Format(_T("%s �ѽ��� %.1lf %%"),s1,pMF->m_progress.GetPos()/0.01/nUpper);
						pStatues->SetPaneText(0,s2);
						time2 = clock();
						s2.Format(_T("��ʱ��%.2g s"),(time2-time)/1000.0);
						pStatues->SetPaneText(3,s2);
						if (time2 - time1 > 50 && PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)){
							SendMessage(msg.message, msg.wParam, msg.lParam);
							time1 = time2;
							Sleep(5);
						}
					}else{			//��ģ��
						double best = 0;
						int index = 0;
						for(int j=0;j<model.n;j++)
						{
							t.getTargetInfo(model.path[j]);
							t2.getTargetInfo(test.p[i]);
							double re = t.compare(t2,0,-1,1,ratio);
							if(best<re)
							{
								index = j;
								best = re;
							}
							pMF->m_progress.StepIt();
							s2.Format(_T("%s �ѽ��� %.1lf %%"),s1,pMF->m_progress.GetPos()/0.01/nUpper);
							pStatues->SetPaneText(0, s2);
							time2 = clock();
							s2.Format(_T("��ʱ��%.2g s"),(time2-time)/1000.0);
							pStatues->SetPaneText(3, s2);
							if (time2 - time1 > 50 && PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)){
								SendMessage(msg.message, msg.wParam, msg.lParam);
								time1 = time2;
								Sleep(5);
							}
						}
						t.getTargetInfo(model.path[index]);
						t2.getTargetInfo(test.p[i]);
						t.compare(t2,"test.txt",-1,0,ratio);
						pMF->m_progress.StepIt();
						s2.Format(_T("%s �ѽ��� %.1lf %%"),s1,pMF->m_progress.GetPos()/0.01/nUpper);
						pStatues->SetPaneText(0,s2);
						s2.Format(_T("��ʱ��%.2g s"),(clock()-time)/1000.0);
						pStatues->SetPaneText(3,s2);
					}
				}
				while (pMF->m_progress.GetPos()!=nUpper)
				{
					Sleep(5);
					if (PeekMessage(&msg,(HWND)NULL, 0, 0, PM_REMOVE))
						SendMessage(msg.message, msg.wParam, msg.lParam);
				}
			}catch(...)
			{
				MessageBox("�ǳ���Ǹ���ڶ�ȡѵ����ʱ�����쳣����رպ�����","���г���",0);
				return;
			}
			LOG("��������ȡ���Լ���ɡ�����\n");
			ml.getTestOut("test.txt",-1,1);
			
			for(int i=log_num-1;i>0;i--)
				logg[i] = logg[i-1];
			tmp.Empty();
			int yes = 0;
			for(int i=0,j=0;i<test.num;i++){
				CString s;
				if(testOut[i]==0)
					s = _T("(��ƥ��)");
				else if(testOut[i]==1)
				{
					s = _T("(ƥ��)");
					yes ++ ;
				}
				if(j<test.times[9] && i==test.times[j])
				{
					Sleep(1);
					++j;
					logg[0].Format(_T("%s%s    \t%s\r\n\r\n"),tmp,test.p[i],s);
				}else
					logg[0].Format(_T("%s%s    \t%s\r\n"),tmp,test.p[i],s);
				tmp = logg[0];
			}
			s2.Format(_T("���Լ��Ĳ��Խ������(ƥ��/���� = %d/%d):\r\n%s"),yes,test.num,tmp);
			tmp = s2;
			//����ƥ����־
			CString tmp2;
			matchlog.Format(_T("%s\r\n"),printDateTime("���β���ʱ�䣺"));
			tmp2.Format(_T("%s��ǰģ��ͼ:\r\n"),matchlog);
			for(int i=0;i<model.n;i++){
				matchlog.Format("%s%s\r\n",tmp2,model.path[i]);
				tmp2 = matchlog;
			}
			matchlog.Format(_T("%s\r\n%s\r\n\r\n"),tmp2,tmp);

			LOG("������ƥ����ɡ�����\n"<<matchlog);
			s2.Format(_T("ƥ����� !  ƥ��/���� = %d/%d(ƥ���� %.3g%%)"),yes,test.num,100.0*yes/test.num);

			logg[0].Format(_T("%s-------------�����ָ���-------------\r\n\r\n"),tmp);
			log = logg[log_num-1];
			for(int i=log_num-2;i>=0;i--)
				log += logg[i];
			UpdateData(false);
			updatelog();
			test.num = 0;
			memset(test.times,0,sizeof(test.times));
			pStatues->SetPaneText(0,s2);
			pStatues->SetPaneText(2,_T("���"));
			//pStatues->SetPaneText(3,_T(""));
			pMF->m_progress.SetPos(0);
		}else
			MessageBox("����������Լ����ٽ���ƥ��","ƥ�����",MB_ICONERROR);
	}else
		MessageBox("�����ݻ���ɺ��ٽ���ƥ��","ƥ�����",MB_ICONERROR);
	runing = 0;
	LOG(">>����ƥ��\n\n");
}

void CImgMatchView::OnUseHelp()
{
	CHelpDlg help;
	help.DoModal();
}

void CImgMatchView::OnTrainHelp()
{
	MessageBox(_T("ѵ������ָ����ѵ���Զ�ƥ���׼�����ݼ���\n\n��ѵ�����Ǻ�ģ��ͼ��������ݼ���"
				  "��ģ��ͼ�ܹ�ƥ�䣻\n\n��ѵ�����ǲ�ͬ��ģ��ͼ���������ݼ������ܹ���ģ��ͼƥ��"),
				  "ʲô��ѵ����",0);
}

void CImgMatchView::OnTestHelp()
{
	MessageBox(_T("���Լ���ָ��Ҫ�ж�����ģ���Ƿ�ƥ������ݼ���\n\n�Զ�ƥ����ɺ󽫸���ƥ����߲�ƥ�����ʾ")
		,"ʲô�ǲ��Լ�",0);
}

void CImgMatchView::OnAdvancedSet()
{
	LOG(">>�߼�����\n");
	Dlg.DoModal();
	ml.wait = Dlg.waitTime*1000;
	ml.permitError = Dlg.permitError;
	LOG("������ģ������:"<<Dlg.EvoCol<<"   �������:"<<Dlg.permitError<<"%������\n");
	LOG(">>�����߼�����\n\n");
}

void CImgMatchView::OnSavematch()
{
	if(matchlog[0])
	{
		FILE *fp1 = fopen("Log\\match-log.txt","a+");
		fprintf(fp1,"%s",matchlog);
		fclose(fp1);
		MessageBox("ƥ���¼�ѱ��浽�ļ� Log\\match-log.txt �У�","����ɹ�",MB_ICONINFORMATION);
	}else
	{
		MessageBox("����ƥ��֮����ʹ�øù���","����ʧ��",MB_ICONERROR);
	}
}

void CImgMatchView::OnSaveEvoPath()
{
	if(PathFileExists("best.pth")){			//��ǰ���·���ѱ���
		char fileFormat[] = _T("�ݻ�·���ļ� EvoPath (*.epath)|*.epath|All Files (*.*)|*.*||");
		CFileDialog dlg(false,"epath","Evo_path",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,fileFormat);
		if(dlg.DoModal()==IDOK)
		{
			ofstream file1(dlg.GetPathName().GetBuffer());
			//����ģ������
			file1<<model.n<<endl;
			for(int i=0;i<model.n;++i)
				file1<<model.path[i]<<endl;
			//�����ݻ�����
			file1<<"\n"<<Dlg.absolut<<"\t"<<Dlg.balance_ratio<<"\t";
			for(int i=0;i<Dlg.ratio_num;i++)
				file1<<"\t"<<ratio[i];
			//�����ݻ���Ϣ(ģ�峤�Ⱥ�·��)
			file1<<endl<<endl<<ml.getCol()<<endl;
			ifstream file2("best.pth");
			char ch;
			while(file2.get(ch) && ch!='\n' && ch!='\r')	//��ȡ�ı��е�����	
				file1.put(ch);		//д�����ݵ��ļ�
			file1.close();
			file2.close();			//�ر��ļ���
			MessageBox("�ѱ����ݻ���·��","�����ݻ�·���ɹ�",MB_ICONINFORMATION);
		}
	}else
		MessageBox("��ǰδ���ֿɱ����·�������Ƚ����ݻ�����ʹ�øù���","�����ݻ�·������",MB_ICONERROR);
}

void CImgMatchView::OnReadEvoPath()
{
	LOG(">>��ȡ�ݻ�·��\n");
	char fileFormat[] = _T("�ݻ�·���ļ� EvoPath (*.epath)|*.epath|All Files (*.*)|*.*||");
	CFileDialog dlg(true, "epath", "Evo_path", OFN_FILEMUSTEXIST, fileFormat);
	int check = 0;
	if (DragEvoPath == "")
		check = (dlg.DoModal() == IDOK);
	if (DragEvoPath[0] || check)	//�������ļ�·�� ���� ��ȡ���ļ�
	{
		CString EvoPath = DragEvoPath[0] ? DragEvoPath : dlg.GetPathName();
		char path[512];
		freopen((LPSTR)(LPCTSTR)EvoPath.GetBuffer(),"r",stdin);
		cin>>model.n;
		getchar();
		int flag = 1;
		for(int i=0;i<model.n;++i){
			gets(path);
			model.path[i] = path;
			if(!(tmpimg = loadImg(model.path[i],0,0,1,0)))
			{
				MessageBox("��·���л�ȡģ��ͼʧ�ܣ���ȷ��·����Ч��ģ��ͼ����","�����ݻ���Ϣʧ��");
				releaseImg(&tmpimg);
				model.n = 0;
				break;
			}
			releaseImg(&tmpimg);
		}
		if(model.n>0){
			cin>>Dlg.absolut>>Dlg.balance_ratio;
			for(int i=0;i<Dlg.ratio_num;i++)
			{
				cin>>Dlg.ratio[i];
				ratio[i] = Dlg.ratio[i];
			}
			cin>>ml.getCol();
			Dlg.EvoCol = ml.getCol();
			ml.setWait_Col(Dlg.waitTime,Dlg.EvoCol);
			for(int i=0;i<ml.getChromlen();++i)
				cin>>ml.getBest().chrom[i];
			if(flag){
				Evolution = 1;
				//������ǰ�����ѵ�����Ͳ��Լ�
				train.p_num = 0;
				train.n_num = 0;
				test.num = 0;
				resetP_N = 1;
				LOG("ģ��������"<<Dlg.EvoCol<<"ƫ����ϵ����"<<Dlg.absolut<<"\n");
				for(int i=log_num-1;i>0;i--)
					logg[i] = logg[i-1];
				if(model.n>0){
					tmp.Format(_T("�ѳɹ������ݻ�·����Ϣ����������Լ���ʼƥ�䣡\r\n���а�������%d��ģ��:\r\n"),model.n);
					for(int i=0;i<model.n;i++){
						logg[0].Format(_T("%s%s\r\n"),tmp,model.path[i]);
						tmp = logg[0];
					}
					LOG(tmp);
					logg[0].Format(_T("%s-------------�����ָ���-------------\r\n\r\n"),tmp);
				}
				log = logg[log_num-1];
				for(int i=log_num-2;i>=0;i--)
					log += logg[i];
				UpdateData(false);
				updatelog();
			}
		}else
			flag = 0;
		if(flag==0)
			logg[0].Format(_T("δ�ɹ�����·����Ϣ��������!\r\n-------------�����ָ���-------------\r\n\r\n"));
		freopen("CON","r",stdin);
	}
	LOG(">>������ȡ�ݻ�·��\n\n");
}

void CImgMatchView::OnUpdateLog()
{
	CUpdateLogDlg uplog;
	uplog.DoModal();
}

//������Ϣ���
BOOL CImgMatchView::OnEraseBkgnd(CDC* pDC) 
{
	int x,y;
	CRect rc;
	GetClientRect(&rc);
	x=0;y=0;
	while(y < rc.Height()) 
	{
		//rc��ʾ�Ի���Ĵ�С�ߴ�
		while(x < rc.Width()) 
		{
			m_bmpBackground.DrawBMP(pDC, x, y); 
			x += m_bmpBackground.GetWidth(); //�õ�λͼ�Ŀ��
		}
		x = 0;
		y += m_bmpBackground.GetHeight();  //�õ�λͼ�ĸ߶�
	}
	return TRUE;
}

HBRUSH CImgMatchView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	static bool first = 1;
	if(first){
		GetDlgItem(IDC_log)->GetWindowRect(&r);//��ȡ�ؼ��������Ļ��λ��
		ScreenToClient(&r);//ת��Ϊ�Ի����ϵ����λ��
		first = 0;
	}
	static int t = clock();
	if(!runing && clock()-t>500)
	{
		/*
		((CEdit*)(GetDlgItem(IDC_log)))->ShowWindow(SW_HIDE);
		((CEdit*)(GetDlgItem(IDC_log)))->SetWindowText(log);
		((CEdit*)(GetDlgItem(IDC_log)))->ShowWindow(SW_SHOW);*/
		InvalidateRect(&r,1);
		t = clock();
	}
    // ���ض��Ŀؼ����޸�
	if (nCtlColor == CTLCOLOR_STATIC)
    {
        pDC->SetTextColor(RGB(0,0,255)); //����������ɫ
        pDC->SetBkMode(TRANSPARENT);//���ñ���Ϊ͸��
		static HBRUSH B = (HBRUSH)GetStockObject(NULL_BRUSH);//��ȡ������ɫ��Ϻ�Ļ��ʣ����͸��
		return B; //���ػ�ˢ���
	}
	return CFormView::OnCtlColor(pDC,pWnd, nCtlColor);
}

void CImgMatchView::OnEnVscrollLog()
{
	RedrawWindow();
}

UINT warn(void*){
	MessageBox(0,"������æ�Ÿ�����㣬���һ������ƶ��Ұ�^_^","��ǰ�벻Ҫ�ƶ�����",0);
	return 0;
}
void CImgMatchView::OnNcLButtonDown(UINT u,CPoint cp)
{
	if (runing)
	{
		AfxBeginThread(warn, 0);
		return;
	}
	CFormView::OnNcLButtonDown(u,cp);
	RedrawWindow();
}
//����Ϊ������Ϣ���

void CImgMatchView::OnSaveModelTrain()
{
	if(model.n && train.p_num)			//��ǰ������ģ��ͼ����ѵ����
	{
		char fileFormat[] = _T("·���ļ� Path (*.path)|*.path|All Files (*.*)|*.*||");
		CFileDialog dlg(false,"path","path",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,fileFormat);
		if(dlg.DoModal()==IDOK)
		{
			ofstream file1(dlg.GetPathName());
			//����ģ�������ѵ������������������
			file1<<model.n<<"\t"<<train.p_num<<"\t"<<train.n_num<<endl;
			//����ģ��·��
			for(int i=0;i<model.n;++i)
				file1<<model.path[i]<<endl;
			//����ѵ����
			file1<<endl;
			for(int i=0;i<train.p_num;++i)
				file1<<train.p[i]<<endl;
			file1<<endl;
			for(int i=0;i<train.n_num;++i)
				file1<<train.n[i]<<endl;
			file1.close();
			MessageBox("�ѱ���ģ��ͼ��ѵ����·��","����ģ���ѵ����·���ɹ�",MB_ICONINFORMATION);
		}
	}else
		MessageBox("��ǰ��δ��ȫ����ģ��ͼ��ѵ����������������������ʹ�øù���","����ģ���ѵ��������",MB_ICONERROR);
}

void CImgMatchView::OnReadModelTrain()
{
	LOG(">>��ȡģ���ѵ����\n");
	char fileFormat[] = _T("·���ļ� Path (*.path)|*.path|All Files (*.*)|*.*||");
	CFileDialog dlg(true, "path", "path", OFN_FILEMUSTEXIST, fileFormat);
	int check = 0;
	if (DragModelTrainPath == "")
		check = (dlg.DoModal() == IDOK);
	if (DragModelTrainPath[0] || check)	//�������ļ�·�� ���� ��ȡ���ļ�
	{
		CString PathName = DragModelTrainPath[0] ? DragModelTrainPath : dlg.GetPathName();
		char path[512];
		int n[4];
		freopen((LPSTR)(LPCTSTR)PathName.GetBuffer(),"r",stdin);
		cin>>n[0]>>n[1]>>n[2];
		n[3] = n[0]+n[1]+n[2];
		if(n[0]>0 && n[1]>0)
		{
			for(int i=0;i<n[3];++i)
			{
				if(i==0 || i==n[0] || i==n[0]+n[1])	//�������
					getchar();
				gets(path);
				if(!(tmpimg = loadImg(path,0,0,1,0)))
				{
					MessageBox("��·���л�ȡģ���ѵ����ʧ�ܣ���ȷ�ϸ�·���ļ���Ч","����ģ��ͼ��ѵ����ʧ��");
					LOG(">>�ж϶�ȡģ���ѵ����\n\n");
					return;
				}
				releaseImg(&tmpimg);
			}
		}else
		{
			MessageBox("��·���л�ȡģ���ѵ����ʧ�ܣ���ȷ�ϸ�·���ļ�������ȷ","����ģ��ͼ��ѵ����ʧ��");
			LOG(">>�ж϶�ȡģ���ѵ����\n\n");
			return;
		}
		freopen("CON","r",stdin);
		model.n=n[0];
		train.p_num=n[1];
		train.n_num=n[2];
		freopen((LPSTR)(LPCTSTR)PathName.GetBuffer(),"r",stdin);
		gets(path); //����ʹ��gets����������cin����scanf���������������ո�ֹͣ����
		//����ģ��·��
		for(int i=0;i<model.n;++i)
		{
			gets(path);
			model.path[i] = path;
		}
		//����ѵ����
		getchar();
		for(int i=0;i<train.p_num;++i)
		{
			gets(path);
			train.p[i] = path;
		}
		getchar();
		for(int i=0;i<train.n_num;++i)
		{
			gets(path);
			train.n[i] = path;
		}
		freopen("CON","r",stdin);

		for(int i=log_num-1;i>0;i--)
			logg[i] = logg[i-1];
		if(model.n>0){
			tmp.Format(_T("�ѳɹ�����ģ��ͼ��ѵ������Ϣ���ɿ�ʼ�ݻ�������ѵ������\r\n���а�������%d��ģ��:\r\n"),model.n);
			for(int i=0;i<model.n;i++)
			{
				logg[0].Format(_T("%s%s\r\n"),tmp,model.path[i]);
				tmp = logg[0];
			}
			logg[0].Format("%s\r\n��������%d����ѵ����:\r\n",tmp,train.p_num);
			for(int i=0;i<train.p_num;i++)
			{
				tmp.Format(_T("%s%s\r\n"),logg[0],train.p[i]);
				logg[0] = tmp;
			}
			if(train.n_num)
				tmp.Format("%s\r\n��������%d����ѵ����:\r\n",logg[0],train.n_num);
			for(int i=0;i<train.n_num;i++)
			{
				logg[0].Format(_T("%s%s\r\n"),tmp,train.n[i]);
				tmp = logg[0];
			}
			LOG(tmp);
			logg[0].Format(_T("%s-------------�����ָ���-------------\r\n\r\n"),tmp);
		}else
			logg[0].Format(_T("δ�ɹ�����·����Ϣ�����Ժ�����!\r\n-------------�����ָ���-------------\r\n\r\n"));
		log = logg[log_num-1];
		for(int i=log_num-2;i>=0;i--)
			log += logg[i];
		UpdateData(false);
		updatelog();
		test.num = 0;
		resetP_N = 1;
	}
	LOG(">>������ȡģ���ѵ����\n\n");
}

void CImgMatchView::OnQuit()
{
	if(::MessageBox(0,"���Ƿ�Ҫ�˳��������","�˳�����",1)==1)
		PostQuitMessage(0);
}

void CImgMatchView::OnResizeWindow()
{
	//LONG style = ::GetWindowLong(this->GetSafeHwnd(),GWL_STYLE);
	pstyle->style |= WS_THICKFRAME;//ʹ�����������ı��С
	//::SetWindowLong(this->GetSafeHwnd(),GWL_STYLE,pstyle->style);
	/*
	static int enable = 0;
	LONG style = ::GetWindowLong(*this,GWL_STYLE);
	if(!enable)
		style |=  WS_THICKFRAME;//ʹ�����������ı��С
	else
		style &= ~WS_THICKFRAME;
	int a = ::SetWindowLong(*this,GWL_STYLE,style);
	CString ss;ss.Format("%d",a);
	MessageBox(ss);
	enable = !enable;
	*/
}

void CImgMatchView::OnDropFiles(HDROP hDropInfo)
{
	if (runing)
		return;
	int  nFileCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 256);   //��ȡ������ļ�����
	char filepath[256]="";
	int i=0,j=0;
	bool otherFiles = 0;
	SetForegroundWindow();		//���ô����ö���ʾ
	for (i = 0; i<nFileCount; i++){
		DragQueryFile(hDropInfo,i,filepath,256);	// ��ȡ�Ϸŵ�i���ļ��������ļ���
		if(GetFileAttributes(filepath)!=FILE_ATTRIBUTE_DIRECTORY	//��һ����Ч�ļ�
			&& ((!strcmp(PathFindExtension(filepath),".jpg") || !strcmp(PathFindExtension(filepath),".bmp")
			|| !strcmp(PathFindExtension(filepath),".png"))))		//��һ����ʽ֧�ֵ�ͼ���ļ�
		{
			DragImgPath[j++] = filepath;
		}
		else if (GetFileAttributes(filepath) != FILE_ATTRIBUTE_DIRECTORY
			&& !strcmp(PathFindExtension(filepath), ".epath")){
			DragEvoPath = filepath;
			OnReadEvoPath();
		}
		else if (GetFileAttributes(filepath) != FILE_ATTRIBUTE_DIRECTORY
			&& !strcmp(PathFindExtension(filepath), ".path")){
			DragModelTrainPath = filepath;
			OnReadModelTrain();
		}
		else{
			otherFiles = 1;
			continue;
		}
	}
	if(j>0){
		CChooseType ct;
		if (ct.DoModal() == IDOK){
			switch (ct.m_choosed)
			{
			case 0:OnOpenModelMany(); break;
			case 1:OnTrainP(); break;
			case 2:OnTrainN(); break;
			case 3:OnAddTest(); break;
			default:break;
			}
		}
		for(int i=0;i<j;++i)
			DragImgPath[i].Empty();
	}
	if (DragEvoPath[0])
		DragEvoPath.Empty();
	if (DragModelTrainPath[0])
		DragModelTrainPath.Empty();
	if (otherFiles)
		MessageBox("��֧������jpg,bmp,png��ʽ��ͼ���ļ���.path/.epath��ʽ��·���ļ��������ļ����Զ�����","ɸѡ��ʾ");
	DragFinish(hDropInfo);   // ע����������٣������ͷ�Windows Ϊ�����ļ��ϷŶ�������ڴ�
}

