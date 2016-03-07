

#pragma once

#include "VideoInfo.h"
#include "MFCShowVideoTest.h"
#include "afxwin.h"
// CMFCShowVideoTestDlg 对话框
class CMFCShowVideoTestDlg : public CDialog
{
// 构造
public:
	CMFCShowVideoTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
enum { IDD = IDD_MFCSHOWVIDEOTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
	
	CVideoInfo* m_pVideoInfo;

	HDC m_pPicCtlHdc;
	CRect m_PicCtlRect;

	CvvImage m_CvvImage;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
