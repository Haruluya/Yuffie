#include"flag.h"



Status initPurchasePlanStatus() {
    FILE* fp;
    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("flag.txt", "r"))) {
        return ERROR;
    }
    while (!feof(fp)) {
        fgets(BUFF, sizeof(BUFF), fp);
        if (!strcmp(BUFF, "\0")) {
            continue;
        }

        //��ȡ�Կո��зֵ���������.
        String* purchasePlanStatusInfo = yuffieSplit(BUFF);

        //�ɹ��ƻ�״̬��
        if (!strcmp(purchasePlanStatusInfo[0], "PurcahsePlanStatus")) {
            purchasePlanStatus = atoi(purchasePlanStatusInfo[1]);
        }
        BUFF[0] = '\0';
    }
    fclose(fp);
    return OK;
}

Status setPurchasePlanStatus(PLANSTATUS planStatus) {
    if (planStatus < ANNOUNCEMENT || planStatus > REVIEWOFFER) {
        return INFASIBLE;
    }
    FILE* fp;
    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("flag.txt", "w"))) {
        return ERROR;
    }
    purchasePlanStatus = planStatus;
    fprintf(fp,
        "PurcahsePlanStatus %d",
        purchasePlanStatus
    );
    return OK;
}