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
    @model_function:"�û����������".
    @include:user.h    
    @log:user.log     
    @functions:{
        yuffieSplit:"�Զ�����ַ����зֺ���(�Կո�)",
        initUserList:"�����û���" ,
        setPresentUser:"���õ�ǰ�û�",
        loginValidate:"��¼��֤"
    }
*/
#pragma once
#include"user.h"
#pragma warning(disable : 4996)


/*
    @author:haruluya
    @date:2022/5/13
    @function:"�Զ�����ַ����зֺ���(�Կո�)"
    @input:{
        buff:"������".
    }
    @output:{
    }
    @execute:[loginDialog.loginDialogProc] 
    @return:"�зֺ���ַ�������"
*/
String* yuffieSplit(String buff) {
    String info = strtok(buff, " ");
    String* infoArray = (String*)malloc(sizeof(String) * INFO_MAXSIZE);
    int len = 0;
    while (info) {
        infoArray[len++] = info;
        info = strtok(NULL, " ");
    }
    return infoArray;
}


/*
    @author:haruluya
    @date:2022/5/13
    @function:"�����û�����"
    @input:{
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"ִ��״̬"
*/
Status initUserList() {
    FILE* fp;

    /*
        @value:"�ļ��򿪴�����".
    */
    if (!(fp = fopen("user.txt", "r"))) {
        return ERROR;
    }

    while (!feof(fp)) {
        fgets(BUFF, sizeof(BUFF), fp);
        if (!strcmp(BUFF, "\0")) {
            break;
        }
        String* userInfo = yuffieSplit(BUFF);

        //��ʼ��user��.
        User user;
        user.userName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        user.password = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        user.userName = strcpy(user.userName, userInfo[0]);
        user.password = strcpy(user.password, userInfo[1]);
        user.identity = atoi(userInfo[2]);
        user.id = atoi(userInfo[3]);

        //����list��
        userList[userListLen++] = user;
        BUFF[0] = '\0';
    }
    fclose(fp);
    return OK;
}


/*
    @author:haruluya
    @date:2022/5/13
    @function:"���õ�ǰ�û�"
    @input:{
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"ִ��״̬"
*/
Status setPresentUser(String userName) {

    /*
        @check:"�����Ƿ����"��
    */
    if (!userName) {
        return INFASIBLE;
    }
    for (int i = 0; i < userListLen; i++) {

        /*
            @check:"usernam�ҵ�����"��
        */
        if (strcmp(userList[i].userName, userName) == 0) {
            presentUser = userList[i];
            return OK;
        }
    }
    return NOT_FOUND;
}



/*
    @author:haruluya
    @date:2022/5/13
    @function:"��¼��֤"
    @input:{
        userName:"�û���"��
        password:"�û�����"
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"��¼״̬"
*/
LoginMessage loginValidate(String userName, String password) {
    LoginMessage message;

    /*
        @check:"username����Ϊ��"��
    */
    if (!userName) {
        message.status = INFASIBLE; message.message = "Input error!";
        return message;
    }

    //�û������ڡ�
    message.status = NOT_FOUND; message.message = "User not found!";

    for (int i = 0; i < userListLen; i++) {

        /*
            @check:"�û�����"��
        */
        if (strcmp(userList[i].userName, userName) == 0) {

            /*
                @check:"�û�������ȷ"��
            */
            if (strcmp(userList[i].password, password) == 0) {
                message.status = OK; message.message = "Login success!";
            }
            else {
                message.status = ERROR; message.message = "Password wrong!";
            }
            break;
        }
    }
    return message;
}


String getIdentity(IDENTITY identity) {
    switch (identity)
    {
    case ADMIN:return "admin";
    case TEACHER:return "teacher";
    case SUPPLIER:return "supplier";
    default:
        return INFASIBLE;
    }
}



/*
    @author:haruluya
    @date:2022/5/13
    @function:"������û�"
    @input:{
        User:"�û��ṹ��"
    }
    @output:{
    }
    @return:"���״̬"
*/
Status addUser(User u)
{
    //����list��
    userList[userListLen++] = u;
    printUser();
    return OK;
}


Status printUser() {
    FILE* fp;

    /*
        @check:"�ļ��򿪴�����."
    */
    if (!(fp = fopen("user.txt", "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < userListLen; i++)
    {

        fprintf(fp,
            "%s %s %d %d\n",
            userList[i].userName,
            userList[i].password,
            userList[i].identity,
            userList[i].id);
    }
    fclose(fp);
    return OK;
}

/*
    @author:haruluya
    @date:2022/5/13
    @function:"ɾ��ָ���û����û�"
    @input:{
        id:"�û����"
    }
    @output:{
    }
    @return:"ɾ��״̬"
*/
Status deleteUser(int id)
{
    for (int i = 0; i < userListLen; i++)
    {
        if (userList[i].id == id)
        {
            for (int j = userListLen - 1; j > i; j--)
            {
                userList[j - 1].userName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
                userList[j - 1].password = (String)malloc(sizeof(char) * INFO_MAXSIZE);
                strcpy(userList[j - 1].userName, userList[i].userName);
                strcpy(userList[j - 1].password, userList[i].password);
                userList[j - 1].id = userList[i].id;
                userList[j - 1].identity = userList[i].identity;
            }
            userListLen--;
            userList[userListLen - 1];
        }
    }
    printUser();

    return OK;
}