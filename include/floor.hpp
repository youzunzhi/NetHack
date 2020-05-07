//
//  floor.hpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/10.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#ifndef floor_hpp
#define floor_hpp

#include <stdio.h>
#include <random>
#include <list>
#include "random.hpp"
#include "position.hpp"


const int kFloorHeight = 20;
const int kFloorLength = 60;


enum FloorChar{
    kFloor = '.',
    kHallway = '#',
    kBlank = ' ',
    kNone = '\0',
    kHorizontalWall = '-',
    kVerticalWall = '|',
    kDownstairsChar = '>',
    kUpstairsChar = '<',
    kDoorClosedChar = '+',
    kDoorOpenedChar = '`',
    kAmuletOfYendorChar = 'Y'
};

struct Door {
    Position pos;
    bool is_locked;
    Door(Position position,bool is_locked);
};
class Floor {
    FloorChar floor[kFloorHeight][kFloorLength];
    std::list<Door> doors;
    Position upstairs_pos_;
    Position downstairs_pos_;
public:
    Floor(int floor_num);
    void ReadCharIntoFloorChar(char[kFloorHeight][kFloorLength]);
    
    FloorChar get_floor_char_at_pos(Position position) const;
    void set_floor_char_at_pos(Position position, FloorChar floor_char);
    Position get_upstairs_pos(void) const {return upstairs_pos_;}
    Position get_downstairs_pos(void) const {return downstairs_pos_;}
    bool IsDoorLocked(Position position);
    bool IsEmptySpace(Position) const;
    Position RandomPosition(void);
    Position RandomEmptySpace(void);
};
#endif /* floor_hpp */
