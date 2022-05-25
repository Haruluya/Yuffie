/*
  @license:
    MIT License

    Copyright (c) 2022 Estrella

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
    @model_function:"�Թ�Ӧ�̱�����˲�������".
    @include:user.h
    @log:user.log
*/

#include "finalPurchase.h"
#include<Windows.h>
/*
    @author:Estrella
    @date:2022/5/15
    @function:"�������ն���������"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status initFinalPurchaseList(String path,int userId)
{
    FILE* fp;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen(path, "r")))
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

        finalPurchaseItem finalPurchaseItem;
        //�������ʼ��.
        finalPurchaseItem.inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcpy(finalPurchaseItem.inventoryName, purchaseTableInfo[0]);
        finalPurchaseItem.inventoryId = atoi(purchaseTableInfo[1]);
        finalPurchaseItem.inventoryNum = atoi(purchaseTableInfo[2]);
        finalPurchaseItem.inventoryPrice = atoi(purchaseTableInfo[3]);
        finalPurchaseItem.userID = userId;
        finalPurchaseTable[finalPurchaseLen++] = finalPurchaseItem;
        BUFF[0] = '\0';
    }
    fclose(fp);
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"��ȡ���еĹ�Ӧ�̱����ļ�"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status initOfferApply()
{
    // ��ȡ�ɹ�����Ŀ¼�µ����������ļ�����������fileName.txt
    system("dir offerApply  /B > priceFileName.txt");

    FILE* fp;
    priceFileLen = 0;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("priceFileName.txt", "r")))
    {
        return ERROR;
    }

    while (!feof(fp))
    {
        fgets(BUFF, sizeof(BUFF), fp);
        if (!strcmp(BUFF, "\0")) {
            continue;
        }
        priceFileName[priceFileLen] = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcpy(priceFileName[priceFileLen++], BUFF);
        BUFF[0] = '\0';
    }
    fclose(fp);
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"����ÿ��ҩƷ��Ӧ�����й�Ӧ�̱�������"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status initPrice()
{
    int i;
    FILE* fp;
    for (i = 0; i < priceFileLen; i++)
    {
        priceFileName[i][14] = '\0';
        strcat(strcpy(BUFF, "./offerApply/"), priceFileName[i]);
        int userId = priceFileName[i][0] - '0';
        String path = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        strcpy(path, BUFF);
        initFinalPurchaseList(path,userId);
        /*
            @check:"�ļ��򿪴�����."
        */
        if (!(fp = fopen(path, "r")))
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
            if (!strcmp(BUFF, "\r\n")) {
                continue;
            }
            // ������費����10����Ӧ�� 
            price[atoi(purchaseTableInfo[1])][priceFileName[i][0] - '0'] = atoi(purchaseTableInfo[3]);

            BUFF[0] = '\0';
        }
    }
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"��ÿ��ҩƷ��Ӧ�����й�Ӧ�̱�������ѡ�񱨼����ٵ�"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status selectPrice()
{
    for (int i = 1; i < INFO_MAXSIZE; i++) {
        int min = 1000000;
        for (int j = 1; j < INFO_MAXSIZE; j++) {
            if (price[i][j] < min && price[i][j] != 0)
            {
                // 0�ŵ�Ԫ���湩Ӧ�̵�id
                price[i][0] = j;
                min = price[i][j];
            }
        }
    }
    return OK;
}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"����ÿ��ҩƷ����ѡ��ı��ۺ͹�Ӧ������"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status finalPrice()
{

}

/*
    @author:Estrella
    @date:2022/5/15
    @function:"��ɱȼ۲��������յĹ����"
    @input:{
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc]
    @return:"����ִ��״̬"
*/
Status createFinalPrice()
{
    FILE* fp;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("finalPurchaseInventory.txt", "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < finalPurchaseLen - 1; i++)
    {

        //��������supplier1.txt.
        fprintf(fp,
            "%s %d %d %d %d\n",
            finalPurchaseTable[i].inventoryName,
            finalPurchaseTable[i].inventoryId,
            finalPurchaseTable[i].inventoryNum,
            finalPurchaseTable[i].inventoryPrice,
            finalPurchaseTable[i].userID);
    }
    fclose(fp);
    return OK;
}