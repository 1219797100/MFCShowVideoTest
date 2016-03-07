

#pragma once

#include "VideoInfo.h"
#include "MFCShowVideoTest.h"
#include "afxwin.h"
// CMFCShowVideoTestDlg �Ի���
class CMFCShowVideoTestDlg : public CDialog
{
// ����
public:
	CMFCShowVideoTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
enum { IDD = IDD_MFCSHOWVIDEOTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	
	CVideoInfo* m_pVideoInfo;

	HDC m_pPicCtlHdc;
	CRect m_PicCtlRect;

	CvvImage m_CvvImage;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenvideo();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnClose();
public:
	afx_msg void OnBnClickedClosevideo();
	afx_msg void OnBnClickedPictrldir();

	CEdit m_Edit;
};
