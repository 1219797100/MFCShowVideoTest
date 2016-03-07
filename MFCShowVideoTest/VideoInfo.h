#pragma once

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "CvvImage.h"
class CVideoInfo
{

public:

	CvCapture* m_pCapture;
	IplImage* m_pFrameImage;
	char s_Pictrldir[200];
	double m_FrameWidth;
	double m_FrameHeight;

public:
	CVideoInfo(void);
public:
	~CVideoInfo(void);
};
