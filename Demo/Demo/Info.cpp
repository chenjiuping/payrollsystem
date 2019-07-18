// Info.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Demo.h"
#include "Info.h"
#include "afxdialogex.h"
#include "MainTest.h"

// Info �Ի���

IMPLEMENT_DYNAMIC(Info, CDialog)

Info::Info(CWnd* pParent /*=NULL*/)
	: CDialog(Info::IDD, pParent)
{

}

Info::~Info()
{
}

void Info::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(Info, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Info::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON2, &Info::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Info::OnBnClickedButton1)
END_MESSAGE_MAP()


// Info ��Ϣ�������


BOOL Info::OnInitDialog()
{
	CDialog::OnInitDialog();
	DWORD style = m_list.GetExtendedStyle();
	m_list.SetExtendedStyle(style | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	

	
	m_list.InsertColumn(0,_T("����"),LVCFMT_LEFT,100,-1);
	m_list.InsertColumn(1,_T("����"),LVCFMT_LEFT,100,-1);
	m_list.InsertColumn(2,_T("����"),LVCFMT_LEFT,100,-1);
	m_list.InsertColumn(3,_T("ְ��"),LVCFMT_LEFT,100,-1);
	m_list.InsertColumn(4,_T("����"),LVCFMT_LEFT,100,-1);
	m_list.InsertColumn(5,_T("��������˰��"),LVCFMT_LEFT,100,-1);
	
	//��ȡ�ļ�
	CString number,name,age,work,salary,result;   //����һ��CString�������ڱ����ı���ؼ��ڵ��ı�
    
	//��ȡ�ļ�����������Ӧ�û��������Ƿ�ƥ�䣬ƥ������������棬���򵯳�����
	
	CFileFind fileFind;//�����ļ��Ƿ����
	CString strFileName;
	strFileName = _T("res/file/info.txt");
	if(!fileFind.FindFile(strFileName) )
	{
		::MessageBox(NULL,TEXT("��ȡ�û���Ϣ�ļ�ʧ��"),NULL,MB_OK);
	}

	CStdioFile file;
	file.Open(strFileName,CFile::modeRead);
	CString strText,shuijin;
	CString strTemp;
	int k=0,p=0,s=0,j=0,shui=0;
	m_list.DeleteAllItems();
	while(file.ReadString(strTemp))
	{
		//���ж�ȡ���ú��������ַ���
		strText += strTemp;
		AfxExtractSubString ( number, strTemp, 0, ' ');
		AfxExtractSubString ( name, strTemp, 1, ' ');
		AfxExtractSubString ( age, strTemp, 3, ' ');
		AfxExtractSubString ( work, strTemp, 4, ' ');
		AfxExtractSubString ( salary, strTemp, 5, ' ');
		k=0;
		if (!number.IsEmpty()) {
			m_list.InsertItem(k, number);
			m_list.SetItemText(k, 1, name);
			m_list.SetItemText(k, 2, age);
			m_list.SetItemText(k, 3, work);
			m_list.SetItemText(k, 4, salary);
			p++;
		}
		
		shui=_ttof(salary);
		s+=shui;
		//˰��������
		if(shui<1500)
		{
			shui=0;
		}
		if(shui<=2500&&shui>=1500)
		{
			shui=(shui-1500)*0.1;
		}
		if(shui<=3500&&shui>2500)
		{
			shui=(shui-2500)*0.15;
		}
		if(shui<=5000&&shui>3500)
		{
			shui=(shui-3500)*0.2;
		}
		if(shui<=10000&&shui>5000)
		{
			shui=(shui-5000)*0.3;
		}
		if(shui>10000)
		{
			shui=(shui-10000)*0.4;
		}
		shuijin.Format(_T("%d"), shui);
		m_list.SetItemText(k,5,shuijin);
		j+=shui;
		
	}
	CString peo,sum,jok;
	peo.Format(_T("%d"), p);
	sum.Format(_T("%d"), s);
	jok.Format(_T("%d"), j);
	GetDlgItem(IDC_PEOPLE)->SetWindowText(peo);
	GetDlgItem(IDC_SUM)->SetWindowText(sum);
	GetDlgItem(IDC_SHUI)->SetWindowText(jok);
	
	
	file.Close();
	return TRUE;  // return TRUE unless you set the focus to a control

}


void Info::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	
}


void Info::OnBnClickedButton2()
{
	Info:OnOK();
}


void Info::OnBnClickedButton1()
{
	POSITION p=m_list.GetFirstSelectedItemPosition();    //��ȡ��ѡ����λ��
	int po = 0;
	CString peo;
	CString sum, jok;
	CString salary, shui;

	while (p) 
     {
       int  nSelected=m_list.GetNextSelectedItem(p); //��ȡѡ���е�����
	   salary = m_list.GetItemText(nSelected, 5);    //��ȡѡ���еĹ��ʲ���
	   shui = m_list.GetItemText(nSelected, 5);      //��ȡѡ���е�˰�ղ���

       GetDlgItem(IDC_PEOPLE)->GetWindowText(peo);   //��ȡ�ܵ�����
	   GetDlgItem(IDC_SUM)->GetWindowText(sum);   //��ȡ�ܵĹ��ʲ���
	   GetDlgItem(IDC_SHUI)->GetWindowText(jok);   //��ȡ�ܵ�˰�ղ���
       
	   sum.Format(_T("%d"), _ttoi(sum)- _ttoi(salary));  //�µĹ��ʲ���
	   jok.Format(_T("%d"), _ttoi(jok) - _ttoi(shui));   //�µ�˰�ղ���

	   po=_ttoi(peo);                                    

       m_list.DeleteItem(nSelected); //��������ɾ��
	   po--;                         //������һ
	   peo.Format(_T("%d"), po);

	   GetDlgItem(IDC_PEOPLE)->SetWindowText(peo); //��������������˰�գ�����
	   GetDlgItem(IDC_SUM)->SetWindowText(sum);
	   GetDlgItem(IDC_SHUI)->SetWindowText(jok);

       p  = m_list.GetFirstSelectedItemPosition();  
     }
}
