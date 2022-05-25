#include"reviewOfferDialog.h"

BOOL CALLBACK MainLabDlgProc(HWND hDlg, UINT message,
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
    static int selectIndex;
    switch (message)
    {

    case WM_INITDIALOG:
    {
        hLabTitle = CreateWindow(
            TEXT("static"), 
            TEXT("��������"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            30, 10, 220, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_LAB_TITLE_LAB,
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
            hDlg, (HMENU)ID_YUFFIE_ADMIN_LAB_LIST,
            hInst,
            NULL
        );

        deleteButton = createDefaultButton(
            TEXT("button"),
            TEXT("�ɹ����"),
            450, 100, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_LAB_PURCHASE_BUTTON,
            hInst
        );

        manageButton = createDefaultButton(
            TEXT("button"),
            TEXT("�鿴����¼"),
            450, 160, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_LAB_MANAGE_BUTTON,
            hInst
        );


        printButton = createDefaultButton(
            TEXT("button"),
            TEXT("��ӡ�ֿ�"),
            450, 220, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_LAB_PRINT_BUTTON,
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
                for (int i = 0; i < inventoryListLen; i++) {
                    String mainLabInfo = (String)malloc(sizeof(char) * 100);
                    mainLabInfo = strcpy(mainLabInfo, inventoryList[i].reagentName);
                    String str = (String)malloc(sizeof(char) * 100);
                    sprintf(str, "%d", inventoryList[i].reagentId);
                    mainLabInfo = strcat(mainLabInfo, "    ");
                    mainLabInfo = strcat(mainLabInfo, str);
                    sprintf(str, "%d", inventoryList[i].reagentNum);
                    mainLabInfo = strcat(mainLabInfo, "    ");
                    mainLabInfo = strcat(mainLabInfo, str);
                    SendMessage(hwndList, LB_INSERTSTRING, -1, mainLabInfo);
                }
                break;
            }
            case CM_SHOW_MANAGE_LIST:
            {
                SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
                SendMessage(hwndList, LB_INSERTSTRING, -1, "�Լ�����    ����ʱ��    �Լ�ID    ��������    ���·�ʽ");
                for (int i = 0; i < manageInventoryLen; i++) {
                    String manageLabInfo = (String)malloc(sizeof(char) * 100);
                    manageLabInfo = strcpy(manageLabInfo, manageInventoryList[i].reagentName);
                    manageLabInfo = strcat(manageLabInfo, "    ");
                    manageLabInfo = strcat(manageLabInfo, manageInventoryList[i].time);
                    String str = (String)malloc(sizeof(char) * 100);
                    sprintf(str, "%d", manageInventoryList[i].reagentId);
                    manageLabInfo = strcat(manageLabInfo, "    ");
                    manageLabInfo = strcat(manageLabInfo, str);
                    sprintf(str, "%d", manageInventoryList[i].reagentChangeNum);
                    manageLabInfo = strcat(manageLabInfo, "    ");
                    manageLabInfo = strcat(manageLabInfo, str);
                    sprintf(str, "%d", manageInventoryList[i].mange);
                    manageLabInfo = strcat(manageLabInfo, "    ");
                    manageLabInfo = strcat(manageLabInfo, str);
                    SendMessage(hwndList, LB_INSERTSTRING, -1, manageLabInfo);
                }
                break;
            }
            case ID_YUFFIE_ADMIN_LAB_PURCHASE_BUTTON: {
                if (IDOK != MessageBox(hDlg, TEXT("��ɲɹ�����������"),
                    TEXT("Querry"),
                    MB_ICONQUESTION | MB_OKCANCEL))
                    break;
                addMainInventory();
                createMainInventory();
                SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
                SendMessage(hDlg, WM_COMMAND, CM_SHOW_LIST, 0);
                break;
            }
            case ID_YUFFIE_ADMIN_LAB_PRINT_BUTTON:
            {
                if (IDOK != MessageBox(hDlg, TEXT("��ӡ�ֿ��棿"),
                    TEXT("Querry"),
                    MB_ICONQUESTION | MB_OKCANCEL))
                    break;
                PrintMainLab();
                MessageBox(hDlg, TEXT("�Ѵ�ӡ��print.txt��"), TEXT("SUCCESS"), MB_ICONINFORMATION);
                break;
            }

            case ID_YUFFIE_ADMIN_LAB_MANAGE_BUTTON:
            {
                String text = (String)malloc(sizeof(char) * INFO_MAXSIZE);
                GetWindowText(manageButton, text, INFO_MAXSIZE);
                if (!strcmp(text, "�鿴����¼")) {
                    if (IDOK != MessageBox(hDlg, TEXT("�鿴����¼��"),
                        TEXT("Querry"),
                        MB_ICONQUESTION | MB_OKCANCEL))
                        break;
                    initMainLabManage();
                    SendMessage(hDlg, WM_COMMAND, CM_SHOW_MANAGE_LIST, 0);
                    SetWindowText(manageButton, "�鿴���");
                }
                else if (!strcmp(text, "�鿴���")) {
                    if (IDOK != MessageBox(hDlg, TEXT("�鿴��棿"),
                        TEXT("Querry"),
                        MB_ICONQUESTION | MB_OKCANCEL))
                        break;
                    SendMessage(hDlg, WM_COMMAND, CM_SHOW_LIST, 0);
                    SetWindowText(manageButton, "�鿴����¼");
                }
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