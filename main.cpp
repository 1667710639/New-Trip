#include"CardCtrl.h"
using namespace std;

//回调函数
LRESULT WINAPI WindowsProc(HWND hWnd,UINT nMsgID,WPARAM wParam,LPARAM lParam);

//创建纸牌类
CCardCtrl g_oCardCtrl;
HINSTANCE g_hIns;
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR lpCmdLine,int nShowCmd)
{
	//创建窗口结构体
	WNDCLASSEX wc;
	MSG mSg;
	HWND hWnd;
	g_hIns = hInstance;

	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor (NULL,MAKEINTRESOURCE(IDC_ARROW));
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowsProc;
	wc.lpszClassName = "PaperCard";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	
	//注册
	RegisterClassEx(&wc);
	//创建窗口
	 hWnd = CreateWindow("PaperCard","纸牌",WS_OVERLAPPEDWINDOW,200,200,752,636,NULL,NULL,hInstance,NULL);
	
	 //显示窗口
	 ShowWindow(hWnd,nShowCmd);
	 
	 //消息循环
	while (GetMessage(&mSg, NULL,0,0))
	{
		TranslateMessage(&mSg);
		DispatchMessage(&mSg);
	}


	
	return 0;
}
LRESULT WINAPI WindowsProc(HWND hWnd,UINT nMsgID,WPARAM wParam,LPARAM lParam)
{	POINT pt;
	switch(nMsgID)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		
		case WM_CREATE:
			g_oCardCtrl.SetDataValue(hWnd,g_hIns);
			g_oCardCtrl.InitGameData();
			break;
		
		case WM_KEYDOWN:
			g_oCardCtrl.OnKeyDown((UINT)wParam);
			break;
		
		case WM_TIMER:	
			g_oCardCtrl.OnTimer((UINT)wParam);

			break;
		
		case WM_PAINT:
			g_oCardCtrl.OnPaintWnd();


			break;
		
		case WM_LBUTTONDOWN:
			//POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam); 
			g_oCardCtrl.OnLButtonDown(pt);
			break;
		
		case WM_RBUTTONDOWN:
			//POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam); 
			g_oCardCtrl.OnRButtonDown(pt);
			break;
		
		case WM_LBUTTONUP:
			
			//POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam); 
			g_oCardCtrl.OnLButtonUp(pt);

			break;
		case WM_RBUTTONUP:
			
			//POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			g_oCardCtrl.OnRButtonUp(pt);
			

			break;
		case WM_MOUSEMOVE:
			
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			g_oCardCtrl.OnMouseMove(pt);
			

			break;


	}
	

	return DefWindowProc(hWnd,nMsgID,wParam,lParam);
}