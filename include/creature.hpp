//
//  creature.hpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/10.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#ifndef creature_hpp
#define creature_hpp

#include <list>
#include <stdio.h>
#include <string>
#include "item.hpp"
#include "position.hpp"

enum MonsterType {
    kGiantRat = 1,
    kLichen,
    kNewt,
    kZombie
};

//class Dungeon;
class Creature {
protected:
    Position pos_;
    int which_floor_;
    std::string name_;
    char display_;
    int hit_points_;
    int attack_;
    int defense_;
public:
    Creature(Position position, int which_floor = 0, std::string name = "", char display = '?', int hit_points = 0, int attack = 0, int defense = 0);
    std::string get_name(void) const {return name_;}
    void set_name(std::string name) {name_ = name;}
    Position get_pos(void) const {return pos_;}
    void set_pos(Position position){pos_ = position;}
    int get_which_floor(void) const {return which_floor_;}
    char get_display(void) const{return display_;}
    int get_hit_points() const{return hit_points_;}
    int get_attack() const{return attack_;}
    int get_defense() const{return defense_;}

    // Moves the creature 1 step to some direction
    void Move(Directions direction);
    void Attack(Creature &other);
    void Hurt(int hurt);
    bool IsDead(void) {return hit_points_<=0;}
};

Creature RandomAnMonster(Position position, int which_floor);



#endif /* creature_hpp */
