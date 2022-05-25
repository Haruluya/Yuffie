#include"labRepertoryDialog.h"

BOOL CALLBACK LabRepertoryDlgProc(HWND hDlg, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC             hdc;
    HDC             mdc;
    PAINTSTRUCT     ps;
    RECT            rect;
    static HWND hLabTitle;
    static HFONT hFont;
    static HDC hdcStatic;

    static HWND manageButton;
    static HWND hwndList;
    static HWND printButton;
    static HWND deleteButton;
    static HWND updateButton;
    static HWND hEditReNum;
    static HWND recButton;
    static int selectIndex;
    String num = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    switch (message)
    {

    case WM_INITDIALOG:
    {




        hLabTitle = CreateWindow(
            TEXT("static"),
            TEXT("��ʵ���ҿ������"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            30, 10, 220, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_REPERTORY_TITLE_LAB,
            hInst,
            NULL
        );
        hFont = CreateFont(-24, -12, 0, 0, 100, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����");



        hwndList = CreateWindow(
            TEXT("listbox"),
            NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_SORT | WS_BORDER,
            10, 60,
            400,
            300,
            hDlg, (HMENU)ID_YUFFIE_TEACHER_REPERTORY_LIST,
            hInst,
            NULL
        );

        hEditReNum = CreateWindow(
            TEXT("edit"),
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            450, 70, 150, 25,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_REAGENT_NUM_REID_EDIT,
            hInst,
            NULL
        );

        updateButton = createDefaultButton(
            TEXT("button"),
            TEXT("����ѡ���Լ�����"),
            450, 100, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_LAB_REPERTORY_UPDATE_BUTTON,
            hInst
        );

        manageButton = createDefaultButton(
            TEXT("button"),
            TEXT("�鿴����¼"),
            450, 160, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_LAB_REPERTORY_MANAGE_BUTTON,
            hInst
        );

        recButton = createDefaultButton(
            TEXT("button"),
            TEXT("�鿴��Һ�����¼"),
            450, 220, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_LAB_REPERTORY_REC_BUTTON,
            hInst
        );

        printButton = createDefaultButton(
            TEXT("button"),
            TEXT("��ӡ�ֿ�"),
            450, 280, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_TEACHER_LAB_PRINT_BUTTON,
            hInst
        );


        SendMessage(hDlg, WM_COMMAND, CM_SHOW_LIST, 0);

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



        case CM_SHOW_LIST:
        {
            SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
            SendMessage(hwndList, LB_INSERTSTRING, -1, "�Լ�����    �Լ�ID    �Լ�����");
            for (int i = 0; i < laborReaListLen; i++) {
                String labReInfo = (String)malloc(sizeof(char) * 100);
                labReInfo = strcpy(labReInfo, laborReaList[i].reagentName);
                String str = (String)malloc(sizeof(char) * 100);
                sprintf(str, "%d", laborReaList[i].reagentId);
                labReInfo = strcat(labReInfo, "    ");
                labReInfo = strcat(labReInfo, str);
                sprintf(str, "%d", laborReaList[i].reagentNum);
                labReInfo = strcat(labReInfo, "    ");
                labReInfo = strcat(labReInfo, str);
                SendMessage(hwndList, LB_INSERTSTRING, -1, labReInfo);
            }
            break;
        }
        case CM_SHOW_MANAGE_LIST:
        {
            SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
            SendMessage(hwndList, LB_INSERTSTRING, -1, "�Լ�����    ����ʱ��    �Լ�ID    ��������    ���·�ʽ");
            for (int i = 0; i < manageLabListLen; i++) {
                String manageLabInfo = (String)malloc(sizeof(char) * 100);
                manageLabInfo = strcpy(manageLabInfo, manageLabList[i].reagentName);
                manageLabInfo = strcat(manageLabInfo, "    ");
                manageLabInfo = strcat(manageLabInfo, manageLabList[i].time);
                String str = (String)malloc(sizeof(char) * 100);
                sprintf(str, "%d", manageLabList[i].reagentId);
                manageLabInfo = strcat(manageLabInfo, "    ");
                manageLabInfo = strcat(manageLabInfo, str);
                sprintf(str, "%d", manageLabList[i].reagentChangeNum);
                manageLabInfo = strcat(manageLabInfo, "    ");
                manageLabInfo = strcat(manageLabInfo, str);
                manageLabInfo = strcat(manageLabInfo, "    ");
                manageLabInfo = strcat(manageLabInfo, getUpdateWayName(manageLabList[i].mange));
                SendMessage(hwndList, LB_INSERTSTRING, -1, manageLabInfo);
            }
            break;
        }
        case ID_YUFFIE_TEACHER_LAB_REPERTORY_UPDATE_BUTTON:
        {
            GetWindowText(hEditReNum, num, INFO_MAXSIZE);
            if ((selectIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0)) != LB_ERR) {
                if (atoi(num) == 0) {
                    MessageBox(hDlg, TEXT("�Լ������仯����Ϊ0��"), TEXT("ERROR"), MB_ICONINFORMATION);
                    break;
                }
                updateLabRepertory(laborReaList[selectIndex - 1].reagentId, atoi(num));
                createConsumMnanageItem(selectIndex - 1,atoi(num));
                SendMessage(hDlg, WM_COMMAND, CM_SHOW_LIST, 0);
                break;
            }
            else {
                MessageBox(hDlg, TEXT("��ѡ��һ��Ԫ�أ�"), TEXT("ERROR"), MB_ICONINFORMATION);
                break;
            }
        }
        case ID_YUFFIE_TEACHER_LAB_PRINT_BUTTON:
        {
            if (IDOK != MessageBox(hDlg, TEXT("��ӡʵ���Ҳֿ��棿"),
                TEXT("Querry"),
                MB_ICONQUESTION | MB_OKCANCEL))
                break;
            printLabRepertory();
            MessageBox(hDlg, TEXT("�Ѵ�ӡ��labReperotyPrint.txt��"), TEXT("SUCCESS"), MB_ICONINFORMATION);
            break;
        }

        case ID_YUFFIE_TEACHER_LAB_REPERTORY_MANAGE_BUTTON:
        {
            String text = (String)malloc(sizeof(char) * INFO_MAXSIZE);
            GetWindowText(manageButton, text, INFO_MAXSIZE);
            if (!strcmp(text, "�鿴����¼")) {
                if (IDOK != MessageBox(hDlg, TEXT("�鿴����¼��"),
                    TEXT("Querry"),
                    MB_ICONQUESTION | MB_OKCANCEL))
                    break;
                
                ShowWindow(updateButton,FALSE);
                ShowWindow(hEditReNum, FALSE);
                SendMessage(hDlg, WM_COMMAND, CM_SHOW_MANAGE_LIST, 0);
                SetWindowText(manageButton, "�鿴���");
            }
            else if (!strcmp(text, "�鿴���")) {
                if (IDOK != MessageBox(hDlg, TEXT("�鿴��棿"),
                    TEXT("Querry"),
                    MB_ICONQUESTION | MB_OKCANCEL))
                    break;

                ShowWindow(updateButton, TRUE);
                ShowWindow(hEditReNum, TRUE);
                SendMessage(hDlg, WM_COMMAND, CM_SHOW_LIST, 0);
                SetWindowText(manageButton, "�鿴����¼");
            }
            break;

        }
        case ID_YUFFIE_TEACHER_LAB_REPERTORY_REC_BUTTON:
        {

            DialogBox(hInst, MAKEINTRESOURCE(IDD_TEACHER_RECYCLE_DIALOG), hDlg, RecycleManageDlgProc);
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