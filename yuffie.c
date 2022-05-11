#include"src/gui/guiTools.h"
#include"src/globalConst.h"
#include"src/gui/components/loginDialog/loginDialog.h"

#define IDM_DIALOG1     101
#define IDM_DIALOG2     102
#define IDM_HELP        201
#define IDM_ABOUT       202

/*
	@function:"�������¼���������"
*/
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;

/*
    @author:haruluya
    @date:2022/5/9
    @model_function:"�����������������ڹ��캯����"
    @input:{
        hInstance:"�����ִ��ģ��ľ����",
        hPrevInstance:"��ʷ����������ʼ��ΪNULL��",
		szCmdLine:"�����в�����",
		iCmdShow:"������ʾ��ʽ��"
    }
    @output:{  
    }
    @execute:[yuffie.WinMain] 
    @return:"status code."
*/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
	/*
		@value:"������������"
	*/
	static TCHAR szAppName[] = TEXT ("Yuffie") ;

	/*
		@value:"�����ھ����"
	*/
	HWND         hwnd ;

	/*
		@value:"��Ϣ������Ϣ��"
	*/
	MSG          msg ;

	/*
		@value:"�����ࡣ"
	*/
	WNDCLASS     wndclass ;

	hInst = hInstance;

	//������������ơ�
	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance		= hInstance;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;
    wndclass.hIcon  = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
	
	/*
		@Check:"������ע��ʧ�ܴ���"
	*/
	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
					szAppName, MB_ICONERROR) ;
		return 0 ;
	}

	// ���ڴ�����
	hwnd = CreateWindow (szAppName,                
						TEXT ("Yuffie"), 
						WS_OVERLAPPEDWINDOW^WS_THICKFRAME,        
						YUFFIE_WINDOW_X,             
						YUFFIE_WINDOW_Y,              
						YUFFIE_WINDOW_NWIDTH,             
						YUFFIE_WINDOW_NHEIGHT,             
						NULL,                       
						NULL,                    
						hInstance,                 
						NULL) ;                    

	// �����ܲ˵���
	HMENU hMenu = CreateMenu();

	// ���������˵��
	HMENU hSubMenu = CreatePopupMenu();
	AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

	hSubMenu = CreatePopupMenu();
	AppendMenu(hSubMenu, MF_STRING, ID_STUFF_GO, "&Go");
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Stuff");

	SetMenu(hwnd, hMenu);

	// ��ʾ�����´��ڡ�
	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;
	
	// ��Ϣ����ѭ����
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}


/*
    @author:haruluya
    @date:2022/5/9
    @function:"�������¼���������"
    @input:{
        hwnd:"�����ھ����",
        message:"�¼���Ϣ��",
		wParam:"�¼����������",
		lParam:"�¼����������"
    }
    @output:{
    }
    @execute:[haruluya.WinMain] 
    @return:"����״̬��"
*/
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*
		@value:""
	*/
	HDC         hdc ;

	/*
		@value:"����״̬��Ϣ��"
	*/
	PAINTSTRUCT ps ;
	
	/*
		@value:"title����"
	*/
	RECT titleRect ;
	static HFONT titleFont;

	static HWND beginButton;
	static RECT beginButtonRect;
	static int  beginButtonCxChar, beginButtonCyChar ;
    static int      cxClient, cyClient ;


	static HINSTANCE hInstance ;


	/*
		@check:"��Ϣ����"
	*/
	switch (message)
	{

	case WM_CREATE:
	{
		hInstance = ((LPCREATESTRUCT) lParam)->hInstance ;
		loadYuffieIcon(hwnd,YUFFIE_ICON_FILENAME);

		beginButtonCxChar = 100 ;
		beginButtonCyChar = 100;
		beginButton = CreateWindow( 
				TEXT("button"), 
                TEXT("Enter System"),
				WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,  
				300,         
				350,        
				200,        
				50,        
				hwnd,    
				(HMENU)IDI_BEGIN_BUTTON,      
				hInst,
				NULL);
		return 0 ;
	}
	case WM_SIZE:
		cxClient = 750 ;
		cyClient = 350 ;
		return 0 ;

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;
 		PaintRoutine (hwnd, hdc, cxClient, cyClient) ;
		EndPaint (hwnd, &ps) ;
		return 0 ;


	case WM_COMMAND:
	{
		YUFFIE_COM_ID commandComID;
		commandComID = LOWORD(wParam);
		switch (commandComID){
			case IDI_BEGIN_BUTTON: 
			{
				loginDialog(hwnd,hInst);
				return DefWindowProc (hwnd, message, wParam, lParam) ;
			}
			case ID_FILE_EXIT:
			{
				return DefWindowProc (hwnd, message, wParam, lParam) ;

			}
			default:
				return DefWindowProc (hwnd, message, wParam, lParam) ;
		}
	}
		
	case WM_DESTROY:
		PostQuitMessage (0) ;
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;

}




