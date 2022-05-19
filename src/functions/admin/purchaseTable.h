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
    @date:2022/5/9
    @author:haruluya
    @model_function:"�Զ�����ز���������ȫ�ֱ�����".
    @include:[purchaseTableStruct.h,user.h]   
    @work:[purchaseTable.c,yuffie.h]       
    @log:purchaseTable.log     

*/

#include"purchaseTableStruct.h"
#include"user.h"



/*
    @function:"��¼��֤��"
*/
LoginMessage loginValidate(String userName);

/*
    @function:"ͨ��������id��ȡ������"
*/
PurchaseItem getPurchaseItemById(int id);

/*
    @function:"���붩�������ݡ�"
*/
Status initPurchaseList();


/*
    @function:"��ɳ��۴������۵���"
*/
Status createOfferApply();


