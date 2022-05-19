#include"reviewOfferDialog.h"

BOOL CALLBACK ReviewOfferDlgProc(HWND hDlg, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC             hdc;
    HDC             mdc;
    PAINTSTRUCT     ps;
    RECT            rect;
    static HWND hLabTitle;
    static HFONT hFont;
    static HDC hdcStatic;
    static HWND hwndList;
    static HWND selectCheapButton;
    static HWND deleteButton;
    static HWND finishButton;
    static int selectIndex;
    switch (message)
    {

    case WM_INITDIALOG:
    {
        hLabTitle = CreateWindow(TEXT("static"), TEXT("����˱��������"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
            30, 10, 220, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_REVIEW_OFFER_TITLE_LAB,
            hInst, NULL);
        hFont = CreateFont(-24, -12, 0, 0, 100, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����");



        hwndList = CreateWindow(TEXT("listbox"), NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_SORT | WS_BORDER,
            10, 60,
            400,
            300,
            hDlg, (HMENU)ID_YUFFIE_ADMIN_REVIEW_OFFER_LIST,
            hInst,
            NULL
        );

        selectCheapButton = createDefaultButton(
            TEXT("button"),
            TEXT("ȡ��ͼ۸�"),
            450, 100, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_REVIEW_OFFER_CHEAP_DELETE_BUTTON,
            hInst
        );

        deleteButton = createDefaultButton(
            TEXT("button"),
            TEXT("ɾ��ѡ����"),
            450, 160, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_REVIEW_OFFER_DELETE_BUTTON,
            hInst
        );

        finishButton = createDefaultButton(
            TEXT("button"),
            TEXT("�ύ���"),
            450, 220, 150, 50,
            hDlg,
            (HMENU)ID_YUFFIE_ADMIN_REVIEW_OFFER_FINISH_BUTTON,
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
            
        case ID_YUFFIE_ADMIN_REVIEW_OFFER_DELETE_BUTTON:
        {
            if (IDOK != MessageBox(hDlg, TEXT("��ȷ��Ҫɾ�����"),
                TEXT("Querry"),
                MB_ICONQUESTION | MB_OKCANCEL))
                break;
            if ((selectIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0)) != LB_ERR) {
                SendMessage(hwndList, LB_DELETESTRING, selectIndex, 0);
            }
            else {
                MessageBox(hDlg, TEXT("��ѡ��һ��Ԫ�أ�"), TEXT("ERROR"), MB_ICONINFORMATION);
            }
            break;
        }
        case ID_YUFFIE_ADMIN_REVIEW_OFFER_FINISH_BUTTON:
        {
            if (IDOK != MessageBox(hDlg, TEXT("��ȷ��Ҫ�ύ��ˣ�"),
                TEXT("Querry"),
                MB_ICONQUESTION | MB_OKCANCEL))
                break;
            createFinalPrice();
            MessageBox(hDlg, TEXT("�ύ��˳ɹ���"), TEXT("SUCCESS"), MB_ICONINFORMATION);
            setPurchasePlanStatus(ANNOUNCEMENT);
            EndDialog(hDlg, 0);
            break;
        }
       
        case ID_YUFFIE_ADMIN_REVIEW_OFFER_CHEAP_DELETE_BUTTON:
        {
            if (IDOK != MessageBox(hDlg, TEXT("ȫ��ѡ����ͼ۸�"),
                TEXT("Querry"),
                MB_ICONQUESTION | MB_OKCANCEL))
                break;
            selectPrice();
            finalPrice();
            SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
            SendMessage(hDlg, WM_COMMAND, CM_SHOW_LIST, 0);
            break;
        }

        case CM_SHOW_LIST:
        {
            SendMessage(hwndList, LB_INSERTSTRING, -1, "�Լ�����    �Լ�ID    �Լ�����    �Լ�����    ��Ӧ��ID");
            for (int i = 0; i < finalPurchaseLen; i++) {
                String purchaseListInfo = (String)malloc(sizeof(char) * 100);
                purchaseListInfo = strcpy(purchaseListInfo, sPurchaseList[i].inventoryName);
                String str = (String)malloc(sizeof(char) * 100);
                sprintf(str, "%d", finalPurchaseTable[i].inventoryId);
                purchaseListInfo = strcat(purchaseListInfo, "    ");
                purchaseListInfo = strcat(purchaseListInfo, str);
                sprintf(str, "%d", finalPurchaseTable[i].inventoryNum);
                purchaseListInfo = strcat(purchaseListInfo, "    ");
                purchaseListInfo = strcat(purchaseListInfo, str);
                sprintf(str, "%d", finalPurchaseTable[i].inventoryPrice);
                purchaseListInfo = strcat(purchaseListInfo, "    ");
                purchaseListInfo = strcat(purchaseListInfo, str);
                sprintf(str, "%d", finalPurchaseTable[i].userID);
                purchaseListInfo = strcat(purchaseListInfo, "    ");
                purchaseListInfo = strcat(purchaseListInfo, str);
                SendMessage(hwndList, LB_INSERTSTRING, -1, purchaseListInfo);
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