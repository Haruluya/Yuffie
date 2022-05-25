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
    SOFTWARE.   //MIT֤��������Ϊ�̶����֡�

    @version:0.0.1
    @date:2022/5/15
    @author:Estrella
    @model_function:"�Թ�Ӧ�̱�������õ������ݽṹ����".
    @include:[global.h��user.h]
    @work:purchaseTable.c
    @log:NONE
*/

#include "global.h"

/*
    @function:"������ĳ���."
    @value:{
        inventoryName:"ҩ������",
        inventoryId:"ҩ��id",
        inventoryNum:"ҩ������",
        inventoryPrice:"����",
        userID:"��Ӧ��",
    }
*/
typedef struct finalPurchaseItem
{
    String inventoryName;
    int inventoryId;
    int inventoryNum;
    int inventoryPrice;
    int userID;
} finalPurchaseItem;

/*
    @function:"�������еı����ļ���"
*/
String priceFileName[50];

/*
    @function:"�������еı����ļ�����"
*/
int priceFileLen;

/*
    @value:�ɹ������ÿ����󳤶ȡ�
*/
#define INFO_MAXSIZE 50

/*
    @value:"�ɹ���������Ԫ������"
*/
#define PURCHASE_APPLY_LIST_MAX_SIZE 199

/*
    @function:"�ɹ�����(�ɹ�������˹���)."
    @range:[0,PURCHASE_LIST_MAX_SIZE]
*/
finalPurchaseItem finalPurchaseTable[PURCHASE_APPLY_LIST_MAX_SIZE];

/*
    @function:"�ɹ�����"
    @range:[0,PURCHASE_LIST_MAX_SIZE/2]
*/
int finalPurchaseLen;

/*
    @value:"ÿ��ҩƷ��Ӧ�����й�Ӧ�̱��۵Ķ�ά����ṹ��"
*/
int price[INFO_MAXSIZE][INFO_MAXSIZE];