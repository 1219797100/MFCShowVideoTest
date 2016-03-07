

#include "stdafx.h"
#include "PlateLocateMethod.h"
#include "cv.h"
#include "highgui.h"
#include <math.h>
#include <string.h>
#include <iostream>
#include "ml.h"
#include "opencv2/opencv.hpp"  
#include "fstream" 




using namespace std;  
using namespace cv;  
CString GetDirectory()
{
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
	bi.pszDisplayName = name;
	bi.lpszTitle = "ѡ���ļ���Ŀ¼";
	bi.ulFlags = BIF_RETURNFSANCESTORS;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if(idl == NULL)
		return "";
	CString strDirectoryPath;
	SHGetPathFromIDList(idl, strDirectoryPath.GetBuffer(MAX_PATH));
	strDirectoryPath.ReleaseBuffer();
	if(strDirectoryPath.IsEmpty())
		return "";
	if(strDirectoryPath.Right(1)!="\\")
		strDirectoryPath+="\\";
	
	return strDirectoryPath;
}
BOOL WINAPI RobertDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//ѭ������
	long i;
	long j;

	//����ֵ
	double result;
	unsigned char pixel[4];

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (char *)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	//ʹ��ˮƽ����ĽṹԪ�ؽ��и�ʴ
	for(j = lHeight-1; j > 0; j--)
	{
		for(i = 0;i <lWidth-1; i++)
		{
			//����ʹ��2��2��ģ�壬Ϊ��ֹԽ�磬���Բ��������±ߺ����ұߵ���������

			// ָ��Դͼ���j�У���i�����ص�ָ��			
			lpSrc = (char *)lpDIBBits + lWidth * j + i;

			// ָ��Ŀ��ͼ���j�У���i�����ص�ָ��			
			lpDst = (char *)lpNewDIBBits + lWidth * j + i;

			//ȡ�õ�ǰָ�봦2*2���������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel[0] = (unsigned char)*lpSrc;
			pixel[1] = (unsigned char)*(lpSrc + 1);
			pixel[2] = (unsigned char)*(lpSrc - lWidth);
			pixel[3] = (unsigned char)*(lpSrc - lWidth + 1);

			//����Ŀ��ͼ���еĵ�ǰ��
			 result = sqrt((float)( pixel[0] - pixel[3] )*(float)( pixel[0] - pixel[3] ) + \
				  (float)( pixel[1] - pixel[2] )*(float)( pixel[1] - pixel[2] ));
			*lpDst = (unsigned char)result;
		
		}
	}

	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
	return TRUE;
}

BOOL WINAPI myMedianFilter(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, 
						   int iFilterH, int iFilterW, 
						   int iFilterMX, int iFilterMY)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	
	// ָ����ͼ���ָ��
	LPSTR			lpNewDIBBits;
	HLOCAL			hNewDIBBits;
	
	// ָ���˲��������ָ��
	unsigned char	* aValue;
	HLOCAL			hArray;
	
	// ѭ������
	LONG			i;
	LONG			j;
	LONG			k;
	LONG			l;
	
	// ͼ��ÿ�е��ֽ���
	LONG			lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);
	
	// �ж��Ƿ��ڴ����ʧ��
	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);
	
	// ��ʼ��ͼ��Ϊԭʼͼ��
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);
	
	// ��ʱ�����ڴ棬�Ա����˲�������
	hArray = LocalAlloc(LHND, iFilterH * iFilterW);
	
	// �ж��Ƿ��ڴ����ʧ��
	if (hArray == NULL)
	{
		// �ͷ��ڴ�
		LocalUnlock(hNewDIBBits);
		LocalFree(hNewDIBBits);
		
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	aValue = (unsigned char * )LocalLock(hArray);
	
	// ��ʼ��ֵ�˲�
	// ��(��ȥ��Ե����)
	for(i = iFilterMY; i < lHeight - iFilterH + iFilterMY + 1; i++)
	{
		// ��(��ȥ��Ե����)
		for(j = iFilterMX; j < lWidth - iFilterW + iFilterMX + 1; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// ��ȡ�˲�������
			for (k = 0; k < iFilterH; k++)
			{
				for (l = 0; l < iFilterW; l++)
				{
					// ָ��DIB��i - iFilterMY + k�У���j - iFilterMX + l�����ص�ָ��
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iFilterMY - k) + j - iFilterMX + l;
					
					// ��������ֵ
					aValue[k * iFilterW + l] = *lpSrc;
				}
			}
			
			// ��ȡ��ֵ
			* lpDst = myGetMedianNum(aValue, iFilterH * iFilterW);
		}
	}
	
	// ���Ʊ任���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);
	
	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	LocalUnlock(hArray);
	LocalFree(hArray);
	
	// ����
	return TRUE;
}

unsigned char WINAPI myGetMedianNum(unsigned char * bArray, int iFilterLen)
{
	// ѭ������
	int		i;
	int		j;
	
	// �м����
	unsigned char bTemp;
	
	// ��ð�ݷ��������������
	for (j = 0; j < iFilterLen - 1; j ++)
	{
		for (i = 0; i < iFilterLen - j - 1; i ++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// ����
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}
	
	// ������ֵ
	if ((iFilterLen & 1) > 0)
	{
		// ������������Ԫ�أ������м�һ��Ԫ��
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// ������ż����Ԫ�أ������м�����Ԫ��ƽ��ֵ
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}
	
	// ������ֵ
	return bTemp;
}


BOOL WINAPI ThresholdTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// �ж��Ƿ�С����ֵ
			if ((*lpSrc) < bThre)
			{
				// ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else
			{
				// ֱ�Ӹ�ֵΪ255
				*lpSrc = 255;
			}
		}
	}
	
	// ����
	return TRUE;
}








void Findchar(IplImage* temple)
 {
	 CvSVM svm = CvSVM();  
	 svm.load("D://HOG_SVM_DATA.xml");//����ѵ���õ�xml�ļ�
    char result[200]; //���Ԥ���� 

    if (!temple)  
     {  
      MessageBox(NULL,TEXT("��Ԥ��ͼ�񲻴��ڣ�"),TEXT("��ʾ"),MB_ICONWARNING);  
       
     }  
     IplImage* trainTempImg=cvCreateImage(cvSize(28,28),8,3);  
     cvZero(trainTempImg);      
     cvResize(temple,trainTempImg);       
     HOGDescriptor *hog=new HOGDescriptor(cvSize(28,28),cvSize(14,14),cvSize(7,7),cvSize(7,7),9);        
     vector<float>descriptors;//��Ž��         
     hog->compute(trainTempImg, descriptors,Size(1,1), Size(0,0)); //Hog��������         
     CvMat* SVMtrainMat=cvCreateMat(1,descriptors.size(),CV_32FC1);     
     int n=0;      
     for(vector<float>::iterator iter=descriptors.begin();iter!=descriptors.end();iter++)      
     {      
           cvmSet(SVMtrainMat,0,n,*iter);      
           n++;      
      }     
	
      int ret =(int) svm.predict(SVMtrainMat);//�����  
      if(ret<=9&&ret>=0)
		{
        sprintf_s( result, " %d",ret );  
        
		}else
		{
		ret=(char)ret;
        sprintf_s( result, " %c",ret );  
       
		}  


   CMFCShowVideoTestDlg* pDlg=(CMFCShowVideoTestDlg*)AfxGetMainWnd();
   pDlg->m_Edit.ReplaceSel(result);
        
	
 
      cvReleaseImage(&temple);  
      cvReleaseImage(&trainTempImg);
	  	
			
 
}  






