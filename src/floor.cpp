//
//  floor.cpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/10.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#include "floor.hpp"
#include <cstring>
Floor::Floor(int floor_num)
: upstairs_pos_(0,0), downstairs_pos_(0,0)
{
    switch (floor_num) {
        case 0:
        {
            char floor_input_0[kFloorHeight][kFloorLength] ={
                "                                                   -------",
                "----------    --------                             |.....|",
                "|........+####|.......######                       |.....|",
                "|........|   #|......|     #                       |.....|",
                "|.........#  #|......+#         -----------        |.....|",
                "|........|#  #------.-#         |.........|########+.....|",
                "|........|## ################   |.........|#       ---.---",
                "----+----- ##     #    #        |..........#         ##",
                "    ##      ##    #    ##       |.........|#         #",
                "     #       #    #   # #       --.--------##        #",
                "     #       #----.---  ##        ####      #       ##",
                "     #       #.......|   #           #      #       #",
                "     #        |......|#  ##          ##     ##      #",
                "     #       #+......| #####          ####   #    ###",
                "     #        |......|   #############   ### #   -.---",
                "-----+--      --------#####  -.------.-----.-####+...|",
                "|......|          #####   ###+...............# # |...|",
                "|.>....+###########          |..............|  ##...<|",
                "--------                     ----------------    -----",
            };
            ReadCharIntoFloorChar(floor_input_0);
            break;
        }
        case 1:
        {
            char floor_input_1[kFloorHeight][kFloorLength] ={
              "                                  --------",
              "  -----                          #|......+####  ---------",
              "  |Y..|                          #|......|######........|",
              "  |...|                          #|......|   #  |.......|",
              "  |...+######         #          #|......|   ###|.......|",
              "  -----      ##  -----+---      ##|......|      ------+--",
              "   ###        ###.........####### ------#-            #",
              "     #           |.......|             ##             #",
              "     #           |.......+#            #              #",
              "     ##          ---------##           #              #",
              "------.--          #        #           #             #",
              "|.......|          ###############     ##           ###",
              "|.......+##                ########## ##        #######",
              "|.......| ###               # -.------.-         --.---",
              "---------   #               ##.........|         |....|",
              "            #                 |........|         |....|",
              "            ##################.........|         |...<|",
              "                              |........|         ------",
              "                              ----------",

            };
            ReadCharIntoFloorChar(floor_input_1);
            break;
        }
        default:
            break;
    }
}
void Floor::ReadCharIntoFloorChar(char floor_input[kFloorHeight][kFloorLength]){
    for (int i = 0; i<kFloorHeight; i++) {
        for (int j = 0; j<kFloorLength; j++) {
            switch (floor_input[i][j]) {
                case '.':
                    floor[i][j] = kFloor;
                    break;
                case '#':
                    floor[i][j] = kHallway;
                    break;
                case ' ':
                    floor[i][j] = kBlank;
                    break;
                case '\0':
                    floor[i][j] = kNone;
                    break;
                case '-':
                    floor[i][j] = kHorizontalWall;
                    break;
                case '|':
                    floor[i][j] = kVerticalWall;
                    break;
                case '>':
                    floor[i][j] = kDownstairsChar;
                    downstairs_pos_ = Position(j,i);
                    break;
                case '<':
                    floor[i][j] = kUpstairsChar;
                    upstairs_pos_ = Position(j, i);
                    break;
                case '+':
                {
                    bool is_locked = RandomBool(0.25);//25% chance to be locked
                    floor[i][j] = kDoorClosedChar;
                    doors.push_back(Door(Position(j,i), is_locked));
                    
                    break;
                }
                case '`':
                    floor[i][j] = kDoorOpenedChar;
                    break;
                case 'Y':
                    floor[i][j] = kAmuletOfYendorChar;
                    break;
                    
                default:
                    break;
            }
        }
    }
}

FloorChar Floor::get_floor_char_at_pos(Position position) const{
    return this->floor[position.pos_y_][position.pos_x_];
}
void Floor::set_floor_char_at_pos(Position position, FloorChar floor_char){
    floor[position.pos_y_][position.pos_x_] = floor_char;
}


bool Floor::IsDoorLocked(Position position){
    for (std::list<Door>::iterator iter = doors.begin(); iter != doors.end(); iter++) {
        if (iter->pos==position) {
            return iter->is_locked;
        }
    }
    perror("No door!\n");
    return false;
}
bool Floor::IsEmptySpace(Position position) const{
    FloorChar floor_char_at_pos = get_floor_char_at_pos(position);
    if (floor_char_at_pos == kFloor || floor_char_at_pos == kHallway) {
        return true;
    }
    return false;
}
Position Floor::RandomPosition(void){
    int rand_x = RandomInt(0, kFloorLength-1);
    int rand_y = RandomInt(0, kFloorHeight-1);
    return Position(rand_x, rand_y);
}
Position Floor::RandomEmptySpace(void){
    Position random_pos = RandomPosition();
    while (!IsEmptySpace(random_pos)) {
        random_pos = RandomPosition();
        //  If there is no empty space, it will be a dead loop(but let's suppose there will always be an empty space).
    }
    return random_pos;
}
Door::Door(Position position, bool is_locked)
:pos(position)
{
    this->is_locked = is_locked;
}
