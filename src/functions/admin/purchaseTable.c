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
    @date:2022/5/13
    @author:haruluya
    @model_function:"This is a file for test".
    @include:[a.h,b.h,c.h]    //������ͷ�ļ���
    @work:interface.c       //������ͷ�ļ���Դ����
    @log:interfaces.log     //������־��

*/

#include"purchaseTable.h"
#include "globalConst.h"

/*
    @author:haruluya
    @date:2022/5/13
    @function:"ͨ��id��ȡ������"
    @input:{
        id:"������id"
    }
    @output:{
    }
    @execute:[supplierTemplate.HelloWndProc] 
    @return:"��Ӧid�Ķ�����"
*/
PurchaseItem getPurchaseItemById(int id) {

    for (int i = 0; i < purchaseListLen; i++) {

        /*
            @check:"id��ͬ�򷵻�."
        */
        if (purchaseList[i].inventoryId == id) {
            return purchaseList[i];
        }
    }
    //������.
    PurchaseItem notFound = { "NULL", -1, 0, 0 };
    return notFound;
}


/*
    @author:haruluya
    @date:2022/5/13
    @function:"���붩����������ȫ�ֱ���purchaseList.(ȫ��ֻ��ȡһ���ļ�)"
    @input:{
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"ִ��״̬"
*/
Status initPurchaseList() {
    FILE* fp;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("purchaseTable.txt", "r"))) {
        return ERROR;
    }
    while (!feof(fp)) {
        fgets(BUFF, sizeof(BUFF), fp);

        if (!strcmp(BUFF, "\0")) {
            break;
        }

        //��ȡ�Կո��зֵ���������.
        String* purchaseTableInfo = yuffieSplit(BUFF);


        PurchaseItem purchaseItem;
        //�������ʼ��.
        purchaseItem.inventoryName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        purchaseItem.inventoryName = strcpy(purchaseItem.inventoryName, purchaseTableInfo[0]);
        purchaseItem.inventoryId = atoi(purchaseTableInfo[1]);
        purchaseItem.inventoryNum = atoi(purchaseTableInfo[2]);


        //���۳�ʼΪ0.
        purchaseItem.inventoryPrice = 0;

        purchaseList[purchaseListLen++] = purchaseItem;
        BUFF[0] = '\0';
    }
    fclose(fp);
    return OK;
}


/*
    @author:haruluya
    @date:2022/5/13
    @function:"�������۱�(������Ӧ�����ļ���admin�²�ɾ��������)"
    @input:{
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"ִ��״̬"
*/
Status createOfferApply() {
    FILE* fp;

    /*
        @check:"�ļ��򿪴�����/ɾ��purchaseTale.txt."
    */
    //if (!(fp = fopen("purchaseTable.txt", "w"))) {
    //    return ERROR;
    //}
    //fclose(fp);

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("./offerApply/supplier1.txt", "w"))) {
        return ERROR;
    }
    for (int i = 0; i < purchaseListLen; i++) {

        //��������supplier1.txt.
        fprintf(fp,
            "%s %d %d %d\n",
            purchaseList[i].inventoryName,
            purchaseList[i].inventoryId,
            purchaseList[i].inventoryNum,
            purchaseList[i].inventoryPrice
        );
    }
    fclose(fp);
    if (!(fp = fopen("purchaseTable.txt", "w"))) {
        return ERROR;
    }
    for (int i = 0; i < purchaseListLen; i++) {

        //��������supplier1.txt.
        fprintf(fp,
            "%s %d %d %d\n",
            purchaseList[i].inventoryName,
            purchaseList[i].inventoryId,
            purchaseList[i].inventoryNum,
            purchaseList[i].inventoryPrice
        );
    }
    fclose(fp);


    //if (!(fp = fopen("./purchaseApply/supplier2.txt", "w"))) {
    //    return ERROR;
    //}
    //for (int i = 0; i < purchaseListLen; i++) {

    //    //��������supplier1.txt.
    //    fprintf(fp,
    //        "%s %d %d %d\n",
    //        purchaseList[i].inventoryName,
    //        purchaseList[i].inventoryId,
    //        purchaseList[i].inventoryNum,
    //        purchaseList[i].inventoryPrice
    //    );
    //}
    //fclose(fp);
    return OK;
}

