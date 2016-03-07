// MFCShowVideoTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCShowVideoTest.h"
#include "MFCShowVideoTestDlg.h"
#include "VideoInfo.h"
#include <string.h>
#include "PlateLocateMethod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;  
using namespace cv;  
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}




BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMFCShowVideoTestDlg 对话框




CMFCShowVideoTestDlg::CMFCShowVideoTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCShowVideoTestDlg::IDD, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCShowVideoTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, m_Edit);
}

BEGIN_MESSAGE_MAP(CMFCShowVideoTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_OpenVideo, &CMFCShowVideoTestDlg::OnBnClickedOpenvideo)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CMFCShowVideoTestDlg::OnBnClickedOk)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CloseVideo, &CMFCShowVideoTestDlg::OnBnClickedClosevideo)
	ON_BN_CLICKED(IDC_Pictrldir, &CMFCShowVideoTestDlg::OnBnClickedPictrldir)
END_MESSAGE_MAP()


// CMFCShowVideoTestDlg 消息处理程序

BOOL CMFCShowVideoTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_pVideoInfo  = new CVideoInfo();

		


	m_pPicCtlHdc = GetDlgItem(IDC_PicCtl)->GetDC()->GetSafeHdc();

	GetDlgItem(IDC_PicCtl)->GetClientRect(&m_PicCtlRect);

	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCShowVideoTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCShowVideoTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CMFCShowVideoTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCShowVideoTestDlg::OnBnClickedOpenvideo()
{


	char aviName[300]={0};
	if(m_pVideoInfo->s_Pictrldir[0]!='\0')
	{

	CFileDialog inDlg(TRUE,NULL,NULL,NULL,NULL,NULL);

	inDlg.m_ofn.lpstrFile = (LPSTR)&aviName[0];
	
	if(inDlg.DoModal() == IDOK )
	{
		m_pVideoInfo->m_pCapture = cvCreateFileCapture(aviName);

		if(m_pVideoInfo->m_pCapture)
		{
			m_pVideoInfo->m_FrameWidth = cvGetCaptureProperty(m_pVideoInfo->m_pCapture,CV_CAP_PROP_FRAME_WIDTH);
			m_pVideoInfo->m_FrameHeight = cvGetCaptureProperty(m_pVideoInfo->m_pCapture , CV_CAP_PROP_FRAME_HEIGHT);

			m_pVideoInfo->m_pFrameImage = cvCreateImage(cvSize(m_pVideoInfo->m_FrameWidth,m_pVideoInfo->m_FrameHeight),8,3);
			cvZero(m_pVideoInfo->m_pFrameImage);
            
			SetTimer(1,500,NULL);
		}
	}
	}
	else {
		AfxMessageBox(_T("没有设置保存图片目录"));
		
	}

}

int x=0;
void CMFCShowVideoTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	char buffer01[200];
	char buffer02[200];
	char buffer[200];
	

	int iFilterH = 3,iFilterW = 3,iFilterMX =1 ,iFilterMY = 1;

	if(nIDEvent==1)
	{
		if(m_pVideoInfo->m_pCapture)
		{
			IplImage* frame;
			IplImage* frame2;
	



           
			frame = cvQueryFrame(m_pVideoInfo->m_pCapture);

			if(frame)
			{ 
	
		
		
				cvCopy(frame,m_pVideoInfo->m_pFrameImage);
				
			
				
                strcpy_s(buffer,m_pVideoInfo->s_Pictrldir);
                sprintf_s(buffer01,"%d.bmp",x);
				strcat_s(buffer,buffer01);
				strcpy_s(buffer01,buffer);


				strcpy_s(buffer,m_pVideoInfo->s_Pictrldir);
                sprintf_s(buffer02,"车牌%d.bmp",x);
				strcat_s(buffer,buffer02);
				strcpy_s(buffer02,buffer);


				frame2=cvCreateImage(cvGetSize(m_pVideoInfo->m_pFrameImage),m_pVideoInfo->m_pFrameImage->depth,1);
				
				
                //灰度图像
				cvCvtColor(m_pVideoInfo->m_pFrameImage,frame2,CV_BGR2GRAY);
                cvEqualizeHist(frame2,frame2);//这里是用于均匀灰度化。
				

                //图像轮廓提取
             RobertDIB((LPSTR)frame2->imageData,(long)frame2->width,(long)frame2->height);
				//中值滤波
		myMedianFilter((LPSTR)frame2->imageData,(long)frame2->width,(long)frame2->height, 
						   iFilterH,iFilterW,
					   iFilterMX,iFilterMY);	
				//二值化
				cvThreshold(frame2, frame2, 0, 255, CV_THRESH_BINARY| CV_THRESH_OTSU);
				
			



	

			
	
			  IplConvKernel * element =0;
		IplConvKernel * element1 =0;
		int cols =3 ,rows = 1 , anchor_x = 1 ,anchor_y =0;
	int values[3]={1,1,1};
				int values1[3]={1,
					           1,
							   1};

        //创建结构元素
        element =        cvCreateStructuringElementEx(cols,rows,anchor_x,anchor_y,CV_SHAPE_CUSTOM,values1);//水平腐蚀
        element1 =        cvCreateStructuringElementEx(1, 3, 0, 1,CV_SHAPE_CUSTOM,values);//竖直腐蚀
    
		 cvDilate(frame2,frame2,element,5);
	
           cvErode(frame2,frame2,element,2); 
		cvErode(frame2,frame2,element1,3);

        cvDilate(frame2,frame2,element1,3);

		




CvMemStorage* storage = cvCreateMemStorage(0);  



  
 CvSeq* contours= cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), storage );
		cvFindContours( frame2, storage, &contours, sizeof(CvContour),
       CV_RETR_EXTERNAL);


		
double area;
    for (;contours;contours = contours->h_next)   
    {  
        if (contours)  
        {  
            area = fabs(cvContourArea(contours,CV_WHOLE_SEQ));  
 
         
            if (area > 100 && area<500)  
            {  
				CvRect* area_Rect = &cvBoundingRect(contours,0); 
				area_Rect->x=area_Rect->x-2;area_Rect->width=area_Rect->width+4;
				if(area_Rect->width-area_Rect->height>=18 && area_Rect->width<=40 && area_Rect->width>25&&area_Rect->height<25&&area_Rect->height>5&&(area_Rect->width/area_Rect->height==2||area_Rect->width/area_Rect->height==3||area_Rect->width/area_Rect->height==4))
				{
                 
				IplImage* plateImage=cvCreateImage(cvGetSize(m_pVideoInfo->m_pFrameImage),m_pVideoInfo->m_pFrameImage->depth,3);
				IplImage* plateImage1;

				cvCopy(m_pVideoInfo->m_pFrameImage,plateImage);
				cvSetImageROI(plateImage,*area_Rect); 
				
                plateImage1=cvCreateImage(cvGetSize(plateImage),m_pVideoInfo->m_pFrameImage->depth,1);
				cvCvtColor(plateImage,plateImage1,CV_BGR2GRAY);
                ThresholdTrans((LPSTR)plateImage1->imageData,(long)plateImage1->width,(long)plateImage1->height,128);
			
			       cvDilate(plateImage1,plateImage1,element1,30);
              

                  char *test=plateImage1->imageData;
				plateImage1->imageData=plateImage1->imageData+plateImage1->width*(plateImage1->height/2);
				int num=0;


				CvMemStorage* storage1 = cvCreateMemStorage(0);
				  
                 CvSeq* contours1=cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), storage1 );


				for(int i =0;i<plateImage1->width;i++)
				{
					
					if(*(plateImage1->imageData+i)!=*(plateImage1->imageData+i+1))
						num++;
				}
				if(num>=12)
				{       plateImage1->imageData=test;
				      
                       cvRectangle(m_pVideoInfo->m_pFrameImage,cvPoint(area_Rect->x,area_Rect->y),cvPoint(area_Rect->x+area_Rect->width,area_Rect->y+area_Rect->height),CV_RGB(0,255,0));  
					cvSaveImage((const char*)buffer02,plateImage);
					cvSaveImage((const char*)buffer01,m_pVideoInfo->m_pFrameImage);
					cvFindContours(plateImage1, storage1, &contours1,sizeof(CvContour),CV_RETR_EXTERNAL);
					     CvRect* area_Rect1;
						
			
						  for (;contours1;contours1 = contours1->h_next)
						  {
								 
							  strcpy_s(buffer,m_pVideoInfo->s_Pictrldir);
         
							  if(contours1)
							  {
								 area_Rect1= &cvBoundingRect(contours1,0);


								if(area_Rect1->width<area_Rect1->height)
								{
									 IplImage* temple;
									IplImage* temple2;
									
							temple=cvCreateImage(cvGetSize(plateImage),m_pVideoInfo->m_pFrameImage->depth,3);
								cvCopy(plateImage,temple);
								cvSetImageROI(temple,*area_Rect1);
								temple2=cvCreateImage(cvGetSize(temple),m_pVideoInfo->m_pFrameImage->depth,3);
         						cvCopy(temple,temple2);
							Findchar(temple2);
						cvReleaseImage(&temple);
						
						
								
								}
							  }	
							
								
						  }
	CMFCShowVideoTestDlg* pDlg=(CMFCShowVideoTestDlg*)AfxGetMainWnd();
   pDlg->m_Edit.ReplaceSel("\r\n");
	
  
					cvReleaseImage(&plateImage);
                   cvReleaseMemStorage(&storage1); 
				cvReleaseImage(&plateImage1);
						  cvReleaseImage(&frame2);
                     
	
				}
                    
				}
            }  
              
        }  
          
    }  

	
     cvReleaseMemStorage(&storage);

	


			x++;
				
			}
			
	
			
			
	}
	}
	
m_CvvImage.CopyOf(m_pVideoInfo->m_pFrameImage);
	m_CvvImage.DrawToHDC(m_pPicCtlHdc,m_PicCtlRect);



	CDialog::OnTimer(nIDEvent);
}

void CMFCShowVideoTestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	if(m_pVideoInfo->m_pCapture)
	{
		cvReleaseCapture(&m_pVideoInfo->m_pCapture);
		m_pVideoInfo->m_pCapture = NULL;
	}

	if(m_pVideoInfo->m_pFrameImage)
	{
		cvReleaseImage(&m_pVideoInfo->m_pFrameImage);
		m_pVideoInfo->m_pFrameImage = NULL;
	}

	KillTimer(1);

	OnOK();
}

void CMFCShowVideoTestDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(m_pVideoInfo->m_pCapture)
	{
		cvReleaseCapture(&m_pVideoInfo->m_pCapture);
		m_pVideoInfo->m_pCapture = NULL;
	}

	if(m_pVideoInfo->m_pFrameImage)
	{
		cvReleaseImage(&m_pVideoInfo->m_pFrameImage);
		m_pVideoInfo->m_pFrameImage = NULL;
	}

	KillTimer(1);

	CDialog::OnClose();
}

void CMFCShowVideoTestDlg::OnBnClickedClosevideo()
{
	// TODO: 在此添加控件通知处理程序代码
	static int count = 0 ;

	if(count % 2  == 0)
	{
		SetDlgItemTextA(IDC_CloseVideo,"开始");

		KillTimer(1);

		count = 1;
	}
	else
	{
		SetDlgItemTextA(IDC_CloseVideo,"暂停");

		SetTimer(1,500,NULL);

		count = 0 ;
	}
}

void CMFCShowVideoTestDlg::OnBnClickedPictrldir()
{
	CString FileDir;
	FileDir=GetDirectory();
strcpy_s(m_pVideoInfo->s_Pictrldir,FileDir);
		
		
	

}

