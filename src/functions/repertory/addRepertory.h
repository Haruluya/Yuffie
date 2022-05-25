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
    @date:2022/5/16
    @author:Estrella
    @model_function:"���Լ������ز���������ȫ�ֱ�����".
    @include:[repertoryStruct.h,repertoryManageStruct.h]
    @log:purchaseTable.log

*/

#include "repertoryStruct.h"
#include "repertoryManageStruct.h"
#include "user.h"

/*
    @function:"Ҫ�����Լ��б�"
*/
ReagentItem addList[INVENTORY_LIST_MAX_SIZE];

/*
    @function:"Ҫ�����Լ��б�"
*/
int addListLen;

/*
    @function:"��ʼ���������ֿ���Լ�"
*/
Status initInventory();

/*
    @function:"��ʼ������ɹ����Լ�"
*/
Status initAddInventory();

/*
    @function:"��������"
*/
Status addMainInventory();

/*
    @function:"����¼��"
*/
Status addMainRepertoryManage();

/*
    @function:"��������档"
*/
Status createMainInventory();


Status initMainLabManage();

