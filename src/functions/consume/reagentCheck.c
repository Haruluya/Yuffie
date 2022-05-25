#include"reagentCheck.h"






//��ȡ����apply�ļ�����
Status initReagentApplyFiles() {
    // ��ȡ�ɹ�����Ŀ¼�µ����������ļ�����������fileName.txt
    system("dir reagentApply  /B > reagentApplyFileName.txt");

    FILE* fp;
    reagentApplyFileLen = 0;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("reagentApplyFileName.txt", "r")))
    {
        return ERROR;
    }
    while (!feof(fp))
    {

        fgets(BUFF, sizeof(BUFF), fp);
        reagentApplyFileName[reagentApplyFileLen] = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcpy(reagentApplyFileName[reagentApplyFileLen++], BUFF);
        BUFF[0] = '\0';
    }
    fclose(fp);
    return OK;
}

//��ʼ���������б�
Status initReagentApplyList() {
    int i;
    FILE* fp;
    for (i = 0; i < reagentApplyFileLen; i++)
    {
        reagentApplyFileName[i][13] = '\0';
        String str = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcat(strcpy(str, "./reagentApply/"), reagentApplyFileName[i]);

        /*
            @check:"�ļ��򿪴�����."
        */
        if (!(fp = fopen(str, "r")))
        {
            return ERROR;
        }
        int teacherId = reagentApplyFileName[i][0] - '0';
     

        while (!feof(fp))
        {
            fgets(BUFF, sizeof(BUFF), fp);
            if (!strcmp(BUFF, "\0")) {
                break;
            }
            //��ȡ�Կո��зֵ���������.
            String* reagentApplyInfo = yuffieSplit(BUFF);
            if (!strcmp(BUFF, "\r\n")) {
                continue;
            }
            String* applyName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
            strcpy(applyName, reagentApplyInfo[0]);
            ReagentCheckItem item = {
                applyName,
                atoi(reagentApplyInfo[1]),
                atoi(reagentApplyInfo[2]),
                teacherId
            };
            addReagentCheckItem(item);
            BUFF[0] = '\0';
        }
    }
    return OK;
}



//��������
Status addReagentCheckItem(ReagentCheckItem item) {
    if (!item.reagentName) {
        return INFASIBLE;
    }
    reagentCheckList[reagentCheckListLen++] = item;
    return OK;
}

//ɾ�������
Status deleteReagentCheckItemById(int id) {
    if (id <= 0) {
        return INFASIBLE;
    }
    for (int i = 0; i < reagentCheckListLen; i++) {
        if (reagentCheckList[i].reagentId == id) {
            for (int j = i; j < reagentCheckListLen - 1; j++) {
                reagentCheckList[i] = reagentCheckList[i + 1];
            }
            reagentCheckListLen--;
            return OK;
        }
    }
    return NOT_FOUND;
}

//�ύ�����
Status commitReagentCheck() {
    FILE* fp;
    /*
       @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("reagentAuditResult.txt", "w")))
    {
        return ERROR;
    }
    for (int i = 0; i < reagentCheckListLen; i++)
    {

        //����Լ������admin��
        fprintf(fp,
            "%s %d %d %d\n",
            reagentCheckList[i].reagentName,
            reagentCheckList[i].reagentId,
            reagentCheckList[i].reagentNum,
            reagentCheckList[i].teacherId
        );
    }
    fclose(fp);
    return OK;
}