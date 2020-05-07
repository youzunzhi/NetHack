//
//  position.hpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/13.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#ifndef position_hpp
#define position_hpp

#include <iostream>
enum Directions{
    LEFT = 0, DOWN, UP, RIGHT, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN,
    DEFAULT
};
struct Position{
    int pos_x_, pos_y_;
    Position(int pos_x = -1, int pos_y = -1);
    Position operator+=(Directions direction);
    int operator-(Position other); //  returns the Manhattan distance of this and other
    bool operator==(Position other);
};
Position operator+(Position position, Directions direction);
#endif /* position_hpp */
