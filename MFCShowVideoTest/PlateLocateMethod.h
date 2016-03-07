#include "DIBAPI.h"
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include <stdio.h>
#include "MFCShowVideoTestDlg.h"

#ifndef _INC_SUANFA1
#define _INC_SUANFA1

// º¯ÊýÔ­ÐÍ

BOOL WINAPI RobertDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
CString GetDirectory();
unsigned char WINAPI myGetMedianNum(unsigned char * bArray, int iFilterLen);
BOOL WINAPI myMedianFilter(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, 
						   int iFilterH, int iFilterW, 
						   int iFilterMX, int iFilterMY);


double angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 );

void Findchar(IplImage* temple);
BOOL WINAPI ThresholdTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre);

 void drawSquares( IplImage* img, CvSeq* squares );



#endif //!_INC_SUANFA1