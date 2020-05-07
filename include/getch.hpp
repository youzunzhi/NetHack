//
//  getch.hpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/12.
//  There's no getch()(read a char without showing it) in Linux, so I have to implement one by myself(copy from Internet for I cannot implement it on my own).
//

#ifndef getch_hpp
#define getch_hpp

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int getch();

void AskforReturn(void);
bool AskYesOrNo(void);

#endif /* getch_hpp */
