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
    SOFTWARE.

    @version:0.0.1
    @date:2022/5/15
    @author:Estrella
    @model_function:"This is a file for test".
    @include:[purchaseCheck.h]    //������ͷ�ļ���
    @work:purchaseCheckTest.c       //������ͷ�ļ���Դ����
    @log:purchaseCheck.log     //������־��

*/

#include "purchaseCheck.h"

/*
    @author:Estrella
    @date:2022/5/15
    @function:"��ʼ���ɹ����뵥����"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status initList()
{
    apply = (LinkList)malloc(sizeof(Node));				//���ٿռ�
    if (!apply)
    {
        printf("�����ڴ�ʧ�ܣ�\n");
        return ERROR;
    }
    apply->next = NULL; //ʹͷ�ڵ�nextΪNULL������ʾ������
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"��ȡ���еĲɹ������ļ�"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status initApply()
{
    // ��ȡ�ɹ�����Ŀ¼�µ����������ļ�����������fileName.txt
    system("dir purchaseApply  /B > fileName.txt");

    FILE* fp;
    fileLen = 0;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("fileName.txt", "r")))
    {
        return ERROR;
    }
    while (!feof(fp))
    {

        fgets(BUFF, sizeof(BUFF), fp);
        fileName[fileLen] = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcpy(fileName[fileLen++], BUFF);
        BUFF[0] = '\0';
    }
    fclose(fp);
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"�������вɹ������ļ�����ȡ������������ʦ�ύ�Ĳɹ�����"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status createPurchaseApply()
{
    int i;
    // rΪָ��β���Ľڵ��ָ��, p�������ɵĽڵ�
    LinkList p, r;
    r = apply;

    FILE* fp;
    for (i = 0; i < fileLen - 1; i++) {
        fileName[i][12] = '\0';
        strcat(strcpy(BUFF, "./purchaseApply/"), fileName[i]);

        if (!strcmp(BUFF, "\0")) {
            continue;
        }
        /*
            @check:"�ļ��򿪴�����."
        */
        if (!(fp = fopen(BUFF, "r")))
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
 
            p = (LinkList)malloc(sizeof(Node)); //�����½ڵ�
            p->data.inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
            strcpy(p->data.inventoryName, purchaseTableInfo[0]);
            p->data.inventoryClass = atoi(purchaseTableInfo[1]);
            p->data.inventoryId = atoi(purchaseTableInfo[2]);
            p->data.inventoryNum = atoi(purchaseTableInfo[3]);
            r->next = p; //����β�ն˽ڵ��ָ��ָ���½ڵ�
            r = p;       //����ǰ���½ڵ㶨��Ϊ��β�ն˽ڵ�
            BUFF[0] = '\0';
        }
    }
    r->next = NULL;									//��ʾ���������

}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"����ɹ����뵥����ĳ���"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"�ɹ����뵥����ĳ���"
*/
int lengthList()
{
    int length = 0;
    LinkList p;
    p = apply->next;

    while (p)
    {
        length++;
        p = p->next;
    }
    return length;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"������Ԫ�ص�����������ҩƷ�ı�Ž���ð������Ϊ����ɾ���ظ�Ԫ����׼��"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status sortList()
{
    LinkList cur, tail;
    cur = apply->next;
    tail = NULL;

    if (cur == NULL || cur->next == NULL) {
        return OK;
    }

    while (cur != tail) {
        while (cur->next != tail) {
            if (cur->data.inventoryId > cur->next->data.inventoryId) {
                purchaseApplyItem tmp = cur->data;
                cur->data = cur->next->data;
                cur->next->data = tmp;
            }
            cur = cur->next;
        }
        tail = cur; // �����������źõ�ѭ��
        cur = apply->next;
    }

    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:""ɾ�������������ظ������ҩ��Ԫ��"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status deleteSameList()
{
    LinkList p, q;
    p = apply->next;

    while (p->next)
    {
        q = p->next;
        if (p->data.inventoryId == q->data.inventoryId) {
            // ɾ��
            p->next = q->next;
            free(q);
        }
        else {
            p = p->next;
        }
    }

    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"�������յĲɹ�������ͨ���Լ��ɹ���ר��ʵ�ʲɹ����ɹ����۱�"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status initPurchaseTable()
{
    LinkList p, q;
    p = apply->next;

    while (p)
    {
        if (p->data.inventoryClass == 0)
        {
            // ������Ԫ����ӵ�ͨ���Լ��ɹ���
            gPurchaseList[gPurchaseListLen++] = p->data;
        }
        else
        {
            // ������Ԫ����ӵ�ר���Լ��ɹ���
            sPurchaseList[sPurchaseListLen++] = p->data;

            // ��ר���Լ��ɹ�Ԫ����ӵ��ɹ����۱�
            PurchaseItem purchaseItem;

            //�������ʼ��.
            purchaseItem.inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
            purchaseItem.inventoryName = strcpy(purchaseItem.inventoryName, p->data.inventoryName);
            purchaseItem.inventoryId = p->data.inventoryId;
            purchaseItem.inventoryNum = p->data.inventoryNum;
            purchaseItem.inventoryPrice = 0;

            purchaseTable[purchaseTableLen++] = purchaseItem;
        }
        p = p->next;
    }

    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"�������յĲɹ�������ͨ���Լ��ɹ��ļ�"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status createGPurchaseTable()
{
    FILE* fp;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("generalReagentInventory.txt", "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < gPurchaseListLen; i++)
    {

        fprintf(fp,
            "%s %d %d\n",
            gPurchaseList[i].inventoryName,
            gPurchaseList[i].inventoryId,
            gPurchaseList[i].inventoryNum);
    }
    fclose(fp);
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"�������յĲɹ�������ר��ʵ�ʲɹ��ļ�"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status createSPurchaseTable()
{
    FILE* fp;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("specialReagentInventory.txt", "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < sPurchaseListLen; i++)
    {

        fprintf(fp,
            "%s %d %d\n",
            sPurchaseList[i].inventoryName,
            sPurchaseList[i].inventoryId,
            sPurchaseList[i].inventoryNum);
    }
    fclose(fp);
    return OK;
}


/*
    @author:Estrella
    @date:2022/5/15
    @function:"�������յĲɹ��������ɹ������ļ�"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status createPurchaseTable()
{
    FILE* fp;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("purchaseTable.txt", "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < sPurchaseListLen; i++)
    {

        //��������.txt.
        fprintf(fp,
            "%s %d %d %d\n",
            sPurchaseList[i].inventoryName,
            sPurchaseList[i].inventoryId,
            sPurchaseList[i].inventoryNum,
            0);
    }
    fclose(fp);
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"ɾ��ָ��id��ͨ���Լ�"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status deleteGPurchaseTable(int id)
{
    for (int i = 0; i < gPurchaseListLen; i++)
    {
        if (gPurchaseList[i].inventoryId == id)
        {
            for (int j = gPurchaseListLen - 1; j > i; j--)
            {
                gPurchaseList[j - 1].inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
                strcpy(gPurchaseList[j - 1].inventoryName, gPurchaseList[j].inventoryName);
                gPurchaseList[j - 1].inventoryId = gPurchaseList[j].inventoryId;
                gPurchaseList[j - 1].inventoryClass = gPurchaseList[j].inventoryClass;
            }
            gPurchaseListLen--;
            gPurchaseList[gPurchaseListLen - 1];
        }
    }
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"ɾ��ָ��id��ר���Լ�"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status deleteSPurchaseTable(int id)
{
    for (int i = 0; i < sPurchaseListLen; i++)
    {
        if (sPurchaseList[i].inventoryId == id)
        {
            for (int j = sPurchaseListLen - 1; j > i; j--)
            {
                sPurchaseList[j - 1].inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
                strcpy(sPurchaseList[j - 1].inventoryName, sPurchaseList[j].inventoryName);
                sPurchaseList[j - 1].inventoryId = sPurchaseList[j].inventoryId;
                sPurchaseList[j - 1].inventoryClass = sPurchaseList[j].inventoryClass;
            }
            sPurchaseListLen--;
            sPurchaseList[sPurchaseListLen - 1];
        }
    }
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"ɾ��ָ��id�Ĳɹ��Լ�"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status deletePurchaseTable(int id)
{
    for (int i = 0; i < purchaseTableLen; i++)
    {
        if (purchaseTable[i].inventoryId == id)
        {
            for (int j = purchaseTableLen - 1; j > i; j--)
            {
                purchaseTable[j - 1].inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
                strcpy(purchaseTable[j - 1].inventoryName, purchaseTable[j].inventoryName);
                purchaseTable[j - 1].inventoryId = purchaseTable[j].inventoryId;
                purchaseTable[j - 1].inventoryNum= purchaseTable[j].inventoryNum;
                purchaseTable[j - 1].inventoryPrice = purchaseTable[j].inventoryPrice;
            }
            purchaseTableLen--;
            purchaseTable[purchaseTableLen - 1];
        }
    }
}
