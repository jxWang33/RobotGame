#include <windows.h>
#include <tchar.h>			//使用swprintf_s函数所需的头文件
#include"resource.h"
#include"things.h"
#include"gui.h"
#include"MapEdit.h"
#include"Q.h"
#include"W.h"
#include"E.h"
#include"change.h"
//依赖项
#pragma comment(lib,"winmm.lib")			//调用PlaySound函数所需库文件
#pragma  comment(lib,"Msimg32.lib")			//添加使用TransparentBlt函数所需的库文件

//窗口宏
#define WINDOW_WIDTH			800
#define WINDOW_HEIGHT			600
int			   core_w=WINDOW_WIDTH;
int			   core_h=WINDOW_HEIGHT;

#define WINDOW_TITLE			L"Robot"

//全局变量
DWORD		    g_tPre=0,g_tNow=0;																//时间变量 控制帧数
int				mouse_x=0, mouse_y =0;
bool			updated=false,edited=false;
extern Tag		TGame,PT;
//全局函数
void						FinalRes(UINT mes,LPARAM lp,WPARAM);//最终交互
LRESULT CALLBACK			WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );//窗口过程
VOID						Game_Paint( HWND hwnd);												
void						ShowMousePos();

void SetClientSize(HWND hWnd,int width, int height)
{
	RECT  rectProgram,rectClient;
	GetWindowRect(hWnd, &rectProgram);
	GetClientRect(hWnd, &rectClient);//获得客户区坐标
	int nWidth = rectProgram.right - rectProgram.left -(rectClient.right - rectClient.left);
	int nHeiht = rectProgram.bottom - rectProgram.top -(rectClient.bottom - rectClient.top);
	nWidth += width;
	nHeiht += height;
	rectProgram.right = nWidth;
	rectProgram.bottom =  nHeiht;
	int showToScreenx = GetSystemMetrics(SM_CXSCREEN)/2-nWidth/2;//居中处理
	int showToScreeny = GetSystemMetrics(SM_CYSCREEN)/2-nHeiht/2;
	MoveWindow(hWnd, showToScreenx, showToScreeny, rectProgram.right, rectProgram.bottom, false);
}
void ShowMousePos()
{
	wchar_t			posString[20];
	swprintf(posString,sizeof(posString),L"%d  %d", mouse_x, mouse_y);
	PicEdit::GetInstance()->TextL(0,0, posString,20,FT_WRYH,COLOR(0,0,0,1));
}
//窗口
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd)
{
	//设计窗口类
	WNDCLASSEX wndClass = { 0 };								
	wndClass.cbSize = sizeof( WNDCLASSEX ) ;	
	wndClass.style = CS_HREDRAW | CS_VREDRAW |CS_DBLCLKS;				//设置窗口的样式
	wndClass.lpfnWndProc = WndProc;															//设置指向窗口过程函数的指针
	wndClass.cbClsExtra		= 0;							
	wndClass.cbWndExtra		= 0;						
	wndClass.hInstance = hInstance;																//指定包含窗口过程的程序的实例句柄。
	wndClass.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );								//指定窗口类的光标句柄。
	wndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);   //指定一个白色画刷
	wndClass.lpszMenuName = NULL;	
	wndClass.lpszClassName = WINDOW_TITLE;												//窗口类的名字
//对窗口类进行注册
	if( !RegisterClassEx( &wndClass ) )return -1;		
//创建窗口
	HWND hwnd = CreateWindow( WINDOW_TITLE,WINDOW_TITLE,WS_CAPTION|WS_SYSMENU|WS_SIZEBOX, 
														CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
														WINDOW_HEIGHT, NULL, NULL, hInstance, NULL );
	SetClientSize(hwnd,WINDOW_WIDTH,WINDOW_HEIGHT);
	ShowWindow( hwnd, nShowCmd );															//显示窗口

//初始化
	All_Init(hwnd);
	Loading(else_GUIInit);
	updated=true;
//主循环
	MSG msg = { 0 };			
	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )  
		{
			TranslateMessage( &msg );						//将虚拟键消息转换为字符消息
			DispatchMessage( &msg );						//分发一个消息给窗口程序。
		}
		else
		{
			DELAY(10);
			PicEdit::GetInstance()->Begin();
			Game_Paint(hwnd);
			csrset(mouse_x, mouse_y);
			PicEdit::GetInstance()->End();
			updated=true;
		}

	}
	UnregisterClass(WINDOW_TITLE, wndClass.hInstance);  //注销窗口类
	return 0;  
}



//窗口过程函数WndProc,对窗口消息进行处理
LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )      
{
	if(TGame!=WAIT)FinalRes(message,lParam,wParam);
	switch( message )					
	{
	case WM_KEYDOWN:	//按键消息
		if(wParam==VK_ESCAPE)//Esc
			PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		mouse_y =HIWORD(lParam);
		mouse_x =LOWORD(lParam);
		break;
	case WM_DESTROY:							
		PostQuitMessage( 0 );//终止线程请求
		break;
	default:
		return DefWindowProc( hwnd, message, wParam, lParam );//缺省窗口过程
	}
	return 0;//正常退出
}

VOID Game_Paint( HWND hwnd )
{
if(TGame==WAIT){TGame=PT;PT=WAIT;}

//	if(TGame==SWITCH){GKedit->show();}
	if(TGame==GUI){GUI_Paint();}
	else if(TGame==Q){Q_Paint();}
	else if(TGame==W){W_Paint();}
	else if(TGame==E){E_Paint();}
	else if(TGame==MAPEDIT){GodMap->EMap_Paint();}
	else if(TGame==OVER||TGame==WIN)
	{
		switch(PT)
		{
		case Q:
			Q_Paint();break;
		case W:
			W_Paint();break;
		case E:
			E_Paint();break;
		}
	}
if(PT==WAIT){PT=TGame;TGame=WAIT;}
	//ShowMousePos();//显示坐标
	return;
}

void FinalRes(UINT mes,LPARAM lp,WPARAM wp)
{
   if(mes==WM_KEYDOWN&&wp==VK_F5&&TGame!=OVER&&TGame!=WIN)
	{
		if(!edited){PT=TGame;TGame=MAPEDIT;edited=true;}
		else if(edited){GodMap->EMap_Save();TGame=PT;edited=false;}
	}
	if(TGame==OVER&&mes==WM_KEYDOWN&&wp==0x52){TGame=PT;}

	if(TGame==GUI&&updated){GUI_Res(mes,lp,wp);}
//	if(TGame==SWITCH&&updated){GKedit->res(mes,lp);}
	if(TGame==Q&&updated){Q_Res(mes,lp,wp);}
	if(TGame==W&&updated){W_Res(mes,lp,wp);}
	if(TGame==E&&updated){E_Res(mes,lp,wp);}
	if(TGame==MAPEDIT){GodMap->EMap_Res(mes,lp,wp);}
}