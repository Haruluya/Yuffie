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
    @model_function:"�ɹ���������õ������ݽṹ����".
    @include:[global.h]
    @work:purchaseTable.c
    @log:NONE
*/

#include "global.h"
#include "user.h"

/*
    @function:"ҩƷ����ĳ���."
    @value:{
        GENERAL:ͨ���Լ�;
        SPECIAL:ר���Լ�;
    }
*/
typedef enum inventoryClass
{
    GENERAL,
    SPECIAL,
} inventoryClass;

/*
    @function:"�ɹ�������ĳ���."
    @value:{
        inventoryName:"ҩ������",
        inventoryClass:"ҩ�����"��
        inventoryId:"ҩ��id",
    }
*/
typedef struct purchaseApplyItem
{
    String inventoryName;
    inventoryClass inventoryClass;
    int inventoryId;
} purchaseApplyItem;

/*
    @function:"�ɹ���������."
    @value:{
        data:�ɹ�������;
        next:��һ�ɹ�������
    }
*/
typedef struct Node
{
    purchaseApplyItem data;
    struct Node* next;
} Node;
typedef struct Node* LinkList;

/*
    @function:"������ĳ���."
    @value:{
        inventoryName:"ҩ������",
        inventoryId:"ҩ��id",
        inventoryNum:"ҩ������",
        inventoryPrice:"����"
    }
*/
//typedef struct PurchaseItem
//{
//    String inventoryName;
//    int inventoryId;
//    int inventoryNum;
//    int inventoryPrice;
//} PurchaseItem;

/*
    @function:"������洢���еĲɹ�����"
*/
LinkList apply;

/*
    @value:�ɹ������ÿ����󳤶ȡ�
*/
#define INFO_MAXSIZE 50

/*
    @value:"�ɹ���������Ԫ������"
*/
#define PURCHASE_APPLY_LIST_MAX_SIZE 199

/*
    @function:"�ɹ�������������ͨ���Լ���ר���Լ��ɹ������(�ɹ�������˹���)."
    @range:[0,PURCHASE_LIST_MAX_SIZE]
*/
purchaseApplyItem gPurchaseList[PURCHASE_APPLY_LIST_MAX_SIZE];
purchaseApplyItem sPurchaseList[PURCHASE_APPLY_LIST_MAX_SIZE];

/*
    @function:"�ɹ�����(�ɹ�������˹���)."
    @range:[0,PURCHASE_LIST_MAX_SIZE]
*/
PurchaseItem purchaseTable[PURCHASE_APPLY_LIST_MAX_SIZE];

/*
    @function:"ͨ���Լ���ר���Լ��ɹ���Ͳɹ��������"
    @range:[0,PURCHASE_LIST_MAX_SIZE/2]
*/
int gPurchaseListLen;
int sPurchaseListLen;
int purchaseTableLen;
