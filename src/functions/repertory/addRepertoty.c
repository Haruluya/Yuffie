/*
    @license:
    MIT License

    Copyright (c) 2022 Haruluya

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.   //MIT֤��������Ϊ�̶����֡�

    @version:0.0.1
    @date:2022/5/15
    @author:Estrella
    @model_function:"���Լ������ز���������ȫ�ֱ�����".
    @include:[purchaseTableStruct.h,user.h]
    @work:[purchaseTable.c,yuffie.h]
    @log:purchaseTable.log

*/

#include "addRepertory.h"

/*
    @function:"��ʼ������ɹ����Լ�"
*/
Status initAddInventory()
{
    FILE* fp;
    addListLen = 0;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("specialReagentInventory.txt", "r")))
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
        String* purchaseTableInfo = yuffieSplit(BUFF);

        ReagentItem ReagentItem;

        //�������ʼ��.
        ReagentItem.reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        ReagentItem.reagentName = strcpy(ReagentItem.reagentName, purchaseTableInfo[0]);
        ReagentItem.reagentId = atoi(purchaseTableInfo[1]);
        ReagentItem.reagentNum = atoi(purchaseTableInfo[2]);

        addList[addListLen++] = ReagentItem;
        BUFF[0] = '\0';
    }
    fclose(fp);

    if (!(fp = fopen("generalReagentInventory.txt", "r")))
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
        String* purchaseTableInfo = yuffieSplit(BUFF);
        ReagentItem ReagentItem;

        //�������ʼ��.
        ReagentItem.reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        ReagentItem.reagentName = strcpy(ReagentItem.reagentName, purchaseTableInfo[0]);
        ReagentItem.reagentId = atoi(purchaseTableInfo[1]);
        ReagentItem.reagentNum = atoi(purchaseTableInfo[2]);

        addList[addListLen++] = ReagentItem;
        BUFF[0] = '\0';
    }
    fclose(fp);

    return OK;
}

/*
    @function:"��ʼ���������ֿ���Լ�"
*/
Status initInventory()
{

    FILE* fp;
    inventoryListLen = 0;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("mainRepertory.txt", "r")))
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
        String* inventory = yuffieSplit(BUFF);

        ReagentItem ReagentItem;

        //�������ʼ��.
        ReagentItem.reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        ReagentItem.reagentName = strcpy(ReagentItem.reagentName, inventory[0]);
        ReagentItem.reagentId = atoi(inventory[1]);
        ReagentItem.reagentNum = atoi(inventory[2]);

        inventoryList[inventoryListLen++] = ReagentItem;
        BUFF[0] = '\0';
    }

    fclose(fp);
}

/*
    @function:"����¼��"
*/
Status addMainRepertoryManage()
{
    FILE* fp;

    // ��ȡ��ǰʱ��
    char nowTime[20] = { 0 };
    time_t timep;
    time(&timep);
    struct tm* p;
    p = gmtime(&timep);
    snprintf(nowTime, 20, "%d-%d-%d %d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("mainRepertoryManage.txt", "a")))
    {
        return ERROR;
    }

    for (int i = 0; i < addListLen; i++)
    {

        fprintf(fp,
            "%s %s %d %d 0\n",
            addList[i].reagentName,
            nowTime,
            addList[i].reagentId,
            addList[i].reagentNum);
    }
    fclose(fp);
    return OK;
}


/*
    @function:"��������"
*/
Status addMainInventory()
{
    int new_list[200] = { 0 };
    for (int i = 0; i < inventoryListLen; i++)
    {
        for (int j = 0; j < addListLen; j++)
        {
            if (inventoryList[i].reagentId == addList[j].reagentId)
            {
                inventoryList[i].reagentNum += addList[j].reagentNum;
                new_list[j] = 1;
            }
        }
    }


    for (int i = 0; i < addListLen; i++)
    {
        if (new_list[i] == 0)
        {
            inventoryList[inventoryListLen++] = addList[i];
        }
    }
    return OK;
}

/*
    @function:"��������档"
*/
Status createMainInventory()
{
    FILE* fp;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("mainRepertory.txt", "a")))
    {
        return ERROR;
    }

    for (int i = 0; i < inventoryListLen; i++)
    {

        fprintf(fp,
            "%s %d %d\n",
            addList[i].reagentName,
            addList[i].reagentId,
            addList[i].reagentNum);
    }
    fclose(fp);

    // д���������
    addMainRepertoryManage();

    return OK;
}



Status PrintMainLab() {
    FILE* fp;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("print.txt", "w")))
    {
        return ERROR;
    }
    for (int i = 0; i < inventoryListLen; i++)
    {

        fprintf(fp,
            "%s %d %d\n",
            addList[i].reagentName,
            addList[i].reagentId,
            addList[i].reagentNum);
    }
    fclose(fp);
    return OK;
}



Status initMainLabManage() {
    FILE* fp;
    if (!(fp = fopen("mainRepertoryManage.txt", "r")))
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
        String* labManangeItemInfo = yuffieSplit(BUFF);
        manageItem manageItem;

        //�������ʼ��.
        manageItem.reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        manageItem.reagentName = strcpy(manageItem.reagentName, labManangeItemInfo[0]);
        manageItem.time = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        manageItem.time = strcat(strcpy(manageItem.time, labManangeItemInfo[1]),labManangeItemInfo[2]);
        manageItem.reagentId = atoi(labManangeItemInfo[3]);
        manageItem.reagentChangeNum = atoi(labManangeItemInfo[4]);
        manageItem.mange = atoi(labManangeItemInfo[5]);
        manageInventoryList[manageInventoryLen++] = manageItem;
        BUFF[0] = '\0';
    }
    fclose(fp);

    return OK;
}