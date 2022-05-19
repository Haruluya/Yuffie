
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
    @date:2022/5/13
    @author:haruluya
    @model_function:"���û�����ز���������ȫ�ֱ�����".
    @include:global.h    
    @work:[user.c,yuffie.h]       
    @log:user.log     

*/

#pragma once
#include"global.h"

/*
    @value:user��ÿ����󳤶ȡ�
*/
#define INFO_MAXSIZE 50

/*
    @value:"user�����Ԫ������"
*/
#define USER_LIST_MAX_SIZE 199
#pragma warning(disable : 4996)


/*
    @function:"��¼״̬�ķ�װ��"
    @value:{
        Status:"��¼״̬.",
        String:"��¼��Ϣ"
    }
*/
typedef struct LoginMessage {
    Status status;
    String message;
}LoginMessage;


/*
    @function:"�û����ö�١�"
    @value:{
        ADMIN:"����Ա"��
        SUPPLIER:"��Ӧ��",
        TEACHER:"��ʦ",
        NONE:"δ��¼"
    }
*/
typedef enum IDENTITY
{
    ADMIN,
    SUPPLIER,
    TEACHER,
    NONE,
}IDENTITY;

/*
    @function:"�û�ʵ�塣"
    @value:{
        userName:"�û�����",
        password:"�û�����",
        identity:"�û����",
        id:"��ǰ���id"
    }
*/
typedef struct User {
    String userName;
    String password;
    IDENTITY identity;
    int    id;
}User;



/*
    @function:"ȫ�ִ���������û����ݣ������ζ�ȡ�ļ���"
    @range:[0,USER_LIST_MAX_SIZE]
*/
User userList[USER_LIST_MAX_SIZE];

/*
    @function:"�û����ݳ��ȡ�"
    @range:[0,USER_LIST_MAX_SIZE]
*/
int userListLen;

/*
    @function:"��ǰ�û���"
    @range:[NULL|user]
*/
User presentUser;

/*
    @function:"��¼��֤��"
*/
LoginMessage loginValidate(String,String);

/*
    @function:"���õ�ǰ�û���"
*/
Status setPresentUser(String userName);


/*
    @function:"����user���ݡ�"
*/
Status initUserList();


/*
    @function:"�Զ����split������"
*/
String* yuffieSplit(String);

/*
    @function:"��ȡ�����Ϣ��"
*/
String getIdentity(IDENTITY);


/*
    @function:"������û���"
*/
Status addUser(User);

/*
    @function:"ɾ��ָ���û���"
*/
Status deleteUser(int);

Status printUser();