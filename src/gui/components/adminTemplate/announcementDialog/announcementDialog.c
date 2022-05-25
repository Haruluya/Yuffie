#include"announcementDialog.h"

BOOL CALLBACK AnnoucementDlgProc(HWND hDlg, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC             hdc;
    HDC             mdc;
    PAINTSTRUCT     ps;
    RECT            rect;
    String noticeContent;
    static HWND hLabTitle;
    static HWND hEditNoticeInpute;
    static HWND confirmButton;
    static HFONT hFont;
    static HDC hdcStatic;


    noticeContent = (String)malloc(sizeof(char) * 80);
    switch (message)
    {

    case WM_INITDIALOG:
    {
        hLabTitle = CreateWindow(
            TEXT("static"), 
            TEXT("�﷢���ɹ������"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            30, 10, 220, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_NOTICE_TITLE_LAB,
            hInst, 
            NULL
        );
        hFont = CreateFont(-24, -12, 0, 0, 100, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����");



        hEditNoticeInpute = CreateWindow(
            TEXT("edit"), 
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            60, 60, 300, 200,
            hDlg, 
            (HMENU)ID_YUFFIE_ADMIN_NOTICE_INPUTE_EDIT,
            hInst, 
            NULL
        );

        confirmButton = createDefaultButton(
            TEXT("button"),
            TEXT("ȷ�Ϸ���"),
            135, 270, 140, 40,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_NOTICE_CONFIRM_BUTTON,
            hInst


        );
        break;
    }
    case WM_CTLCOLORSTATIC:
    {
        hdcStatic = (HDC)wParam;
        if (lParam == hLabTitle) {
            SetTextColor(hdcStatic, RGB(0, 191, 255));
        }
        else {
            SetTextColor(hdcStatic, RGB(0, 191, 255));
        }

        SetBkMode(hdcStatic, TRANSPARENT);
        return (INT_PTR)GetStockObject(NULL_BRUSH);
    }
    case WM_PAINT:
    {
        SendMessage(hLabTitle, WM_SETFONT, (WPARAM)hFont, TRUE);
        hdc = BeginPaint(hDlg, &ps);
        EndPaint(hDlg, &ps);
        return 0;
    }
    
    case WM_COMMAND:
    {
        switch (LOWORD(wParam)) {
            case ID_YUFFIE_ADMIN_NOTICE_CONFIRM_BUTTON:
            {
                GetWindowText(hEditNoticeInpute, noticeContent, 80);
                if (strcmp(noticeContent,"")) {
                    createPurchaseNotice(noticeContent);
                    setPurchasePlanStatus(REVIEWAPPLY);
                    messageBoxPrintf(TEXT("SUCCESS"), TEXT("SUCCESS:  �ɹ����淢���ɹ�,��ȴ���ʦ�ύ���룡 "));
                    EndDialog(hDlg, 0);
                }
                else {
                    messageBoxPrintf(TEXT("SUCCESS"), TEXT("SUCCESS:  �����빫�棡 "));
                }
            }
        }
        break;
    }
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}