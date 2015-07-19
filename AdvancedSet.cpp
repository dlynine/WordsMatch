#include "stdafx.h"
#include "imgMatch.h"
#include "AdvancedSet.h"


AdvancedSet::AdvancedSet(CWnd* pParent)	: CDialog(AdvancedSet::IDD, pParent)
{
	bg2.LoadResource(IDB_BITMAP2);
	waitTime = 5;
	permitError = 8;
	EvoCol = 8;
	absolut = 0.65;
	balance_ratio = 0.5;
	double ssum=0;
	for(int i=0;i<ratio_num-1;i++)
	{
		ratio[i] = int(1000/ratio_num+.5)/1000.0;
		ssum += ratio[i];
	}
	ratio[ratio_num-1] = 1-ssum;
}

void AdvancedSet::DoDataExchange(CDataExchange* pDX){
	DDX_Text(pDX, IDC_wt, waitTime);
	DDV_MinMaxInt(pDX, waitTime, 1, 100000000);
	DDX_Text(pDX, IDC_EDIT1, permitError);
	DDV_MinMaxDouble(pDX, permitError, 0, 100);
	DDX_Text(pDX, IDC_EDIT2, EvoCol);
	DDV_MinMaxInt(pDX, EvoCol, 5, 25);
	DDX_Text(pDX, IDC_abs, absolut);
	DDV_MinMaxDouble(pDX, absolut, 0.01, 0.99);
	DDX_Text(pDX, IDC_ratio1, ratio[0]);
	DDX_Text(pDX, IDC_ratio2, ratio[1]);
	DDX_Text(pDX, IDC_ratio3, ratio[2]);
	DDX_Text(pDX, IDC_ratio4, ratio[3]);
	DDX_Text(pDX, IDC_ratio5, ratio[4]);
	DDX_Text(pDX, IDC_ratio6, ratio[5]);
	DDX_Text(pDX, IDC_ratio7, ratio[6]);
	for(int i=0;i<ratio_num;++i)
		DDV_MinMaxDouble(pDX, ratio[i], 0, 1);
	DDX_Text(pDX, IDC_balance_r, balance_ratio);
	DDV_MinMaxDouble(pDX, balance_ratio, 0, 1);
}

BEGIN_MESSAGE_MAP(AdvancedSet, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_help_abs, &AdvancedSet::OnHelpAbs)
	ON_EN_CHANGE(IDC_ratio1, &AdvancedSet::OnEnChangeRatio)
	ON_EN_CHANGE(IDC_ratio2, &AdvancedSet::OnEnChangeRatio)
	ON_EN_CHANGE(IDC_ratio3, &AdvancedSet::OnEnChangeRatio)
	ON_EN_CHANGE(IDC_ratio4, &AdvancedSet::OnEnChangeRatio)
	ON_EN_CHANGE(IDC_ratio5, &AdvancedSet::OnEnChangeRatio)
	ON_EN_CHANGE(IDC_ratio6, &AdvancedSet::OnEnChangeRatio)
	ON_BN_CLICKED(IDC_help_balance, &AdvancedSet::OnBnClickedhelpbalance)
END_MESSAGE_MAP()


BOOL AdvancedSet::OnEraseBkgnd(CDC* pDC) 
{
	int x,y;
	CRect rc;
	GetClientRect(&rc);
	x=0;y=0;
	while(y < rc.Height())   //rc��ʾ�Ի���Ĵ�С�ߴ�
	{
		while(x < rc.Width()) 
		{
			bg2.DrawBMP(pDC, x, y); 
			x += bg2.GetWidth(); //�õ�λͼ�Ŀ��
		}
		x = 0;
		y += bg2.GetHeight();  //�õ�λͼ�ĸ߶�
	}
	return TRUE;
}

HBRUSH AdvancedSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// ���ض��Ŀؼ����޸�
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(255,255,0)); //����������ɫ
		pDC->SetBkMode(TRANSPARENT);//���ñ���Ϊ͸��
		static HBRUSH B = (HBRUSH)GetStockObject(NULL_BRUSH);//��ȡ������ɫ��Ϻ�Ļ��ʣ����͸��
		return B; //���ػ�ˢ���
	}
	return CDialog::OnCtlColor(pDC,pWnd, nCtlColor);
}

BOOL AdvancedSet::OnInitDialog(){
	UpdateData(FALSE);
	CDialog::OnInitDialog();
	return TRUE;
}

int  AdvancedSet::check_redo(int check,int redo)
{
	static int lastWT, lastEC;
	static double lastPE, lastAB;
	static double r[ratio_num];
	static double lastBR;
	int i;
	if(check==0 && redo==0){		//��Ϊ0
		lastWT = waitTime, lastEC = EvoCol;
		lastPE = permitError, lastAB = absolut;
		lastBR = balance_ratio;
		for(i=0;i<ratio_num;++i)
			r[i] = ratio[i];
	}else if(check){				//check��Ϊ0
		if( lastWT !=waitTime || lastPE !=permitError || lastEC != EvoCol  || lastAB != absolut || lastBR != balance_ratio)
			return 1;
		for(i=0;i<ratio_num;i++)
			if(fabs(r[i]-ratio[i])>1e-3)
				return 1;
		return 0;
	}else{							//redo��Ϊ0
		waitTime = lastWT;
		EvoCol = lastEC;
		permitError = lastPE;
		absolut = lastAB;
		balance_ratio = lastBR;
		for(i=0;i<ratio_num;i++)
			ratio[i] = r[i];
		UpdateData(0);
		RedrawWindow();
	}
	return 0;
}

void AdvancedSet::OnOK(){
	check_redo(0,0);
	if(UpdateData(1)==0){
		check_redo(0,1);
		return;
	}
	if(check_redo(1,0)){
		int re = MessageBox("��⵽��������ֵ���Ƿ��޸����ݣ�","ȷ���޸�",MB_YESNOCANCEL);
		if(re==IDCANCEL){
			check_redo(0,1);
			return;
		}else if(re==IDNO){
			MessageBox("δ�����κ��޸�","��������");
			check_redo(0,1);
		}else if(re==IDYES)
			MessageBox("�����޸ĳɹ�","��������");
	}else
		MessageBox("δ�����κ��޸�","��������");
	CDialog::OnOK();
}

void AdvancedSet::OnHelpAbs()
{
	MessageBox("����������һ����Χ�ڣ���ϵ��Խ�ӽ�1��Ѳ�ƥ����Ϊƥ��Ŀ�����ԽС��ƥ����Ϊ��ƥ�������Խ�󣻷�֮��Ȼ","ƫ����ϵ��");
}

void AdvancedSet::OnBnClickedhelpbalance()
{
	MessageBox("�����ݻ�����������ѵ�����ڸ������ϴ�ʱƽ������ϵ������ֵΪ1���ʾʹ����ѵ����ռ��ͬ��Ӱ������Ϊ0��ʾ��ԭ�и���������","����ƽ��ϵ��",1);
}

void AdvancedSet::OnEnChangeRatio()
{
	double ra[ratio_num];
	CString temp;
	GetDlgItem(IDC_ratio1)->GetWindowText(temp);
	ra[0] = _ttof(temp.GetBuffer());
	GetDlgItem(IDC_ratio2)->GetWindowText(temp);
	ra[1] = _ttof(temp.GetBuffer());
	GetDlgItem(IDC_ratio3)->GetWindowText(temp);
	ra[2] = _ttof(temp.GetBuffer());
	GetDlgItem(IDC_ratio4)->GetWindowText(temp);
	ra[3] = _ttof(temp.GetBuffer());
	GetDlgItem(IDC_ratio5)->GetWindowText(temp);
	ra[4] = _ttof(temp.GetBuffer());
	GetDlgItem(IDC_ratio6)->GetWindowText(temp);
	ra[5] = _ttof(temp.GetBuffer());
	ra[ratio_num-1] = 1;
	for(int i=0;i<ratio_num-1;i++)
		ra[ratio_num-1] -= ra[i];
	temp.Format(_T("%.3g"),ra[ratio_num-1]);
	GetDlgItem(IDC_ratio7)->SetWindowText(0);
	GetDlgItem(IDC_ratio7)->SetWindowText(temp);
	RedrawWindow();
}
