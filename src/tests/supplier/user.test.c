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
    SOFTWARE.   //MIT证书声明，为固定部分。

    @version:0.0.1
    @date:2022/5/13
    @author:haruluya
    @model_function:"user模块测试类".  
*/


#include"user.h"

int main(void){

    // 数组切分测试。
    char* test = "高锰酸钾 1 10";
    char** test1 = yuffieSplit(test);
    assert(!strcmp(test[0],"高锰酸钾"));

    // 载入用户测试。
    initUserList();
    assert(userListLen == 5);
    assert(userList[0].userName == "haruluya");

    //设置当前用户测试.
    setPresentUser("haruluya");
    assert(presentUser.userName == "haruluya");
    setPresentUser("haruluyaxxx");
    assert(presentUser.id == -1);

    //登录验证测试。
    LoginMessage test = loginValidate("haruluya", "123456");
    assert(test.status == OK);
    LoginMessage test = loginValidate("haruluya", "123456xx");
    assert(test.status == ERROR);
    
    return 0;
}

