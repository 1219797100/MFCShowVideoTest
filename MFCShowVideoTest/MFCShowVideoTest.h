// MFCShowVideoTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCShowVideoTestApp:
// �йش����ʵ�֣������ MFCShowVideoTest.cpp
//

class CMFCShowVideoTestApp : public CWinApp
{
public:
	CMFCShowVideoTestApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCShowVideoTestApp theApp;