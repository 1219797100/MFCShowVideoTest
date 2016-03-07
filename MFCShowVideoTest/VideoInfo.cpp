#include "StdAfx.h"
#include "VideoInfo.h"

CVideoInfo::CVideoInfo(void)
{
		 m_pCapture = NULL;
	 m_pFrameImage = NULL;
	 s_Pictrldir[0]='\0';
	 
}

CVideoInfo::~CVideoInfo(void)
{
}
