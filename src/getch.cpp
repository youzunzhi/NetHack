//
//  getch.cpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/12.
//

#include "getch.hpp"
//  Copied from https://blog.csdn.net/HES_C/article/details/65440797
int getch()
{
    struct termios tm,tm_old;
    int fd=0,ch;
    if(tcgetattr(fd,&tm)<0){//保存现在的终端设置
        return -1;
    }
    tm_old=tm;
    cfmakeraw(&tm);//更改终端为原始模式，该模式数据以字节为单位处理
    if(tcsetattr(fd,TCSANOW,&tm)<0){
        return -1;
    }
    ch=getchar();
    if(tcsetattr(fd,TCSANOW,&tm_old)<0){//更改最初的样子
        
        return -1;
    }
    return ch;
}

void AskforReturn(void){
    int input = getch();
    while (input!='\r'&&input!=' ') {
        input = getch();
    }
}
bool AskYesOrNo(void){
    int input = getch();
    while (input!='y'&&input!='n') {
        input = getch();
    }
    if (input == 'y') {
        return true;
    }
    return false;
}
