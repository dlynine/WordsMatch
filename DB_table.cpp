// DB_table.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DB_table.h"
#include "afxdialogex.h"
#include <fstream>
using namespace std;

UINT message(void* pp){
	MessageBox(0, (const char*)(pp), "��ܰ��ʾ", 0);
	return 0;
}

// DB_table �Ի���

IMPLEMENT_DYNAMIC(DB_table, CDialog)

DB_table::DB_table(CWnd* pParent /*=NULL*/)
: m_dbName("source.dbf"), DBName("Provider=Microsoft.JET.OLEDB.4.0;Data source=" + m_dbName), LogDir("Log\\dbError-log.txt")
{
	memset(source,0,sizeof(source));
	strcpy(source,"ImgSource");
	table[0].tableName = "fileList";
	table[0].tvalueName[0] = "md5";
	table[0].tvalueName[1] = "srcName";
	table[0].tvalueName[2] = "fileName";
}

CString DB_table::findData(const char* s1,int re_i){
	ADODB::_ConnectionPtr m_pConnection;
	_variant_t RecordsAffected;
	ADODB::_RecordsetPtr m_pRecordset;

	try{
		m_pConnection.CreateInstance(__uuidof(ADODB::Connection));
		m_pConnection->Open(DBName, "", "", ADODB::adModeUnknown);
	}catch(_com_error e){
		CString errormessage;
		errormessage.Format("�������ݿ�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
#ifdef _DUBUG
		AfxBeginThread(message, (void*)(LPCTSTR)errormessage);
#else
		ofstream DBLog(LogDir, ios::out | ios::app);
		DBLog << __DATE__ <<"  " __TIME__ <<"\t"<<__FILE__<<"--line:"<<__LINE__<<endl<<errormessage<<"\n\n";
		DBLog.close();
#endif
		if (m_pConnection && m_pConnection->State)
			m_pConnection->Close();
		return "";//exit(-1);
	}

	try{
		_bstr_t strCmd="select * from "+table[0].tableName+" where "+table[0].tvalueName[0]+"='"+s1+"'";
		m_pRecordset=m_pConnection->Execute(strCmd,&RecordsAffected,ADODB::adCmdText);
		if (!m_pRecordset->adoEOF && re_i < TValueNums && re_i >= 0)
			return (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect(_variant_t((long)re_i));
		else
			return "";
	}catch(_com_error &e){
		if (m_pRecordset)
			m_pRecordset->Close();
		if (m_pConnection && m_pConnection->State)
			m_pConnection->Close();
		CString errormessage;
		errormessage.Format("����ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
#ifdef _DUBUG
		AfxBeginThread(message, (void*)(LPCTSTR)errormessage);
#else
		ofstream DBLog(LogDir, ios::out | ios::app);
		DBLog << __DATE__ << "  " __TIME__ << "\t" << __FILE__ << "--line:" << __LINE__ << endl << errormessage << "\n\n";
		DBLog.close();
#endif
		return "";//exit(-1);
	}
	if (m_pConnection && m_pConnection->State)
		m_pConnection->Close();
}

void DB_table::addRow(const char* s1, CString s2, CString s3){
	ADODB::_ConnectionPtr m_pConnection;
	_variant_t RecordsAffected;

	try{
		m_pConnection.CreateInstance(__uuidof(ADODB::Connection));
		m_pConnection->Open(DBName,"","",ADODB::adModeUnknown);
	}catch(_com_error e){
		CString errormessage;
		errormessage.Format("�������ݿ�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
#ifdef _DUBUG
		AfxBeginThread(message, (void*)(LPCTSTR)errormessage);
#else
		ofstream DBLog(LogDir, ios::out | ios::app);
		DBLog << __DATE__ << "  " __TIME__ << "\t" << __FILE__ << "--line:" << __LINE__ << endl << errormessage << "\n\n";
		DBLog.close();
#endif
		if (m_pConnection && m_pConnection->State)
			m_pConnection->Close();
		return;//exit(-1);
	}
	try{
		_bstr_t strCmd="INSERT INTO "+table[0].tableName+" values ('"+s1+"','"+s2+"','"+s3+"');";
		m_pConnection->Execute(strCmd,&RecordsAffected,ADODB::adCmdText);
	}catch(_com_error &e){
		CString errormessage;
		errormessage.Format("¼��ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
#ifdef _DUBUG
		AfxBeginThread(message, (void*)(LPCTSTR)errormessage);
#else
		ofstream DBLog(LogDir, ios::out | ios::app);
		DBLog << __DATE__ << "  " __TIME__ << "\t" << __FILE__ << "--line:" << __LINE__ << endl << errormessage << "\n\n";
		DBLog.close();
#endif
		if (m_pConnection && m_pConnection->State)
			m_pConnection->Close();
		return;//exit(-1);
	}
	if (m_pConnection && m_pConnection->State)
		m_pConnection->Close();
}


DB_table::~DB_table()
{
}

void DB_table::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DB_table, CDialog)
END_MESSAGE_MAP()


// DB_table ��Ϣ�������
