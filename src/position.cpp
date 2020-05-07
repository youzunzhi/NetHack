//
//  position.cpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/13.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#include "position.hpp"
Position::Position(int pos_x, int pos_y){
    this->pos_x_ = pos_x;
    this->pos_y_ = pos_y;
}
Position Position::operator+=(Directions direction){
    switch (direction) {
        case LEFT:
            pos_x_ -= 1;
            break;
        case DOWN:
            pos_y_ += 1;
            break;
        case UP:
            pos_y_ -= 1;
            break;
        case RIGHT:
            pos_x_ += 1;
            break;
        case LEFT_UP:
            pos_x_ -= 1;
            pos_y_ -= 1;
            break;
        case LEFT_DOWN:
            pos_x_ -= 1;
            pos_y_ += 1;
            break;
        case RIGHT_UP:
            pos_x_ += 1;
            pos_y_ -= 1;
            break;
        case RIGHT_DOWN:
            pos_x_ += 1;
            pos_y_ += 1;
            break;
        default:
            break;
    }
    return *this;
}
Position operator+(Position position, Directions direction){
    return position += direction;
}
int Position::operator-(Position other){
    return abs(pos_x_-other.pos_x_)+abs(pos_y_-other.pos_y_);
}
bool Position::operator==(Position other){
    if (pos_x_ == other.pos_x_ && pos_y_ == other.pos_y_) {
        return true;
    }
    return false;
}
