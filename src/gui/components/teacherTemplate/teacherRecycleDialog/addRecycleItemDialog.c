#include"addRecycleItemDialog.h"

BOOL CALLBACK RecycleItemAddDlgProc(HWND hDlg, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC             hdc;
    HDC             mdc;
    PAINTSTRUCT     ps;
    RECT            rect;

    int userId;
    IDENTITY identity;

    static HWND hLabTitle;
    static HFONT hFont;
    static HDC hdcStatic;

    static HWND hLabReName;
    static HWND hLabReId;
    static HWND hLabReNum;
    static HWND hEditReName;
    static HWND hEditReId;
    static HWND hEditReNum;

    static HWND finishButton;

    String reName = (String)malloc(sizeof(char) * INFO_MAXSIZE), reId = (String)malloc(sizeof(char) * INFO_MAXSIZE),
        reNum = (String)malloc(sizeof(char) * INFO_MAXSIZE);

    switch (message)
    {

    case WM_INITDIALOG:
    {
        hLabTitle = CreateWindow(
            TEXT("static"),
            TEXT("����ӷ�Һ�������"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            30, 10, 280, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_RECYCLE_ADD_TITLE_LAB,
            hInst,
            NULL
        );
        hFont = CreateFont(-24, -12, 0, 0, 100, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����");//��������


        hLabReName = CreateWindow(
            TEXT("static"),
            TEXT("���ƣ�"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            40, 100, 70, 26,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_RECYCLE_ADD_NAME_LAB,
            hInst,
            NULL
        );

        hEditReName = CreateWindow(
            TEXT("edit"),
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            120, 100, 200, 25,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_RECYCLE_ADD_NAME_EDIT,
            hInst,
            NULL
        );

        hLabReId = CreateWindow(
            TEXT("static"),
            TEXT("Id��"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            40, 150, 70, 26,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_RECYCLE_ADD_ID_LAB,
            hInst,
            NULL
        );

        hEditReId = CreateWindow(
            TEXT("edit"),
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            120, 150, 200, 25,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_RECYCLE_ADD_ID_EDIT,
            hInst,
            NULL
        );

        hLabReNum = CreateWindow(
            TEXT("static"),
            TEXT("������"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            40, 200, 70, 26,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_RECYCLE_ADD_NUM_LAB,
            hInst,
            NULL
        );

        hEditReNum = CreateWindow(
            TEXT("edit"),
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            120, 200, 200, 25,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_RECYCLE_ADD_NUM_EDIT,
            hInst,
            NULL
        );

        finishButton = createDefaultButton(
            TEXT("button"),
            TEXT("���"),
            130, 250, 120, 40,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_RECYCLE_ADD_FINISH_BUTTON,
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
        switch (LOWORD(wParam))
        {
        case ID_YUFFIE_TEACHER_RECYCLE_ADD_FINISH_BUTTON:
        {
            GetWindowText(hEditReId, reId, 80);
            GetWindowText(hEditReName, reName, 80);
            GetWindowText(hEditReNum, reNum, 80);
            if (!strcmp(reId, "") || !strcmp(reName, "") || !strcmp(reNum, "")) {
                MessageBox(hDlg, TEXT("���벻Ϊ�գ����������룡"), TEXT("ERROR"), MB_ICONINFORMATION);
                break;
            }
            String reNameCp = (String)malloc(sizeof(char) * INFO_MAXSIZE);
            strcpy(reNameCp, reName);
            manageItem item = { reNameCp,"0",atoi(reId),atoi(reNum),ADD };
            addManageRecycleItem(item);
            MessageBox(hDlg, TEXT("��ӷ�Һ������ɹ���"), TEXT("SUCCESS"), MB_ICONINFORMATION);
            SendMessage(GetParent(hDlg), WM_COMMAND, CM_SHOW_LIST, 0);
            EndDialog(hDlg, 0);
            break;
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