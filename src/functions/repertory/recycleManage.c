#include"recycleManage.h"


//��ʼ�����շ�Һ��¼��
Status initManageRecycleList() {
    FILE* fp;
    String fileName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    String str = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    sprintf(str, "%d", presentUser.id);
    fileName = strcat(strcat(strcat(strcpy(fileName, "./teacher"), str), "/"), "recycleManage.txt");
    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen(fileName, "r")))
    {
        return ERROR;
    }
    while (!feof(fp))
    {
        fgets(BUFF, sizeof(BUFF), fp);

        if (!strcmp(BUFF, "\0")) {
            break;
        }
        //��ȡ�Կո��зֵ���������.
        String* recycleManageInfo = yuffieSplit(BUFF);

        manageItem item;
        item.reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        item.reagentName = strcpy(item.reagentName, recycleManageInfo[0]);
        item.time = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        item.time = strcpy(item.time, recycleManageInfo[1]);
        item.reagentId = atoi(recycleManageInfo[2]);
        item.reagentChangeNum = atoi(recycleManageInfo[3]);
        item.mange = atoi(recycleManageInfo[4]);
        manageRecyleList[manageRecyleListLen++] = item;
        BUFF[0] = '\0';
    }

    fclose(fp);
    return OK;
}

//ʵʱ���»��շ�Һ��¼��
Status updateManageRecycleList() {
    FILE* fp;
    String fileName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    String str = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    sprintf(str, "%d", presentUser.id);
    fileName = strcat(strcat(strcat(strcpy(fileName, "./teacher"), str), "/"), "recycleManage.txt");
    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen(fileName, "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < manageRecyleListLen; i++)
    {

        fprintf(fp,
            "%s %s %d %d %d\n",
            manageRecyleList[i].reagentName,
            manageRecyleList[i].time,
            manageRecyleList[i].reagentId,
            manageRecyleList[i].reagentChangeNum,
            manageRecyleList[i].mange
        );
    }
    fclose(fp);
    return OK;
}

//��¼��Һ���ա�
Status addManageRecycleItem(manageItem item) {
    if (!item.reagentName) {
        return INFASIBLE;
    }

    // ��ȡ��ǰʱ��
    char nowTime[20] = { 0 };
    time_t timep;
    time(&timep);
    struct tm* p;
    p = gmtime(&timep);
    snprintf(nowTime, 20, "%d-%d-%d_%d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
    item.time = (String)malloc(sizeof(char) * INFO_MAXSIZE);
    item.time = strcpy(item.time,nowTime);
    manageRecyleList[manageRecyleListLen++] = item;
    updateManageRecycleList();
    return OK;
}
