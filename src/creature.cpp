//
//  creature.cpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/10.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#include "creature.hpp"

Creature::Creature(Position position, int which_floor, std::string name, char display, int hit_points, int attack, int defense)
{
    pos_ = position;
    which_floor_ = which_floor;
    name_ = name;
    display_ = display;
    hit_points_ = hit_points;
    attack_ = attack;
    defense_ = defense;
}

void Creature::Move(Directions direction){
    this->set_pos(this->get_pos()+direction);
}
void Creature::Attack(Creature &other){
    int hurt = this->attack_ - other.defense_;
    if (hurt>0) {
        other.Hurt(hurt);
    }
}
void Creature::Hurt(int hurt){
    if (hurt>0) {
        hit_points_ -= hurt;
    }
}
Creature RandomAnMonster(Position position, int which_floor){
    const double chance_each_monster_type[4] = {0.3, 0.3, 0.2, 0.2};
    MonsterType monster_type = (MonsterType)RandomChoice(4, chance_each_monster_type);
    std::string name;
    char display;
    int hit_points;
    int attack;
    int defense;
    switch (monster_type) {
        case kGiantRat:
            name = "the giant rat";
            display = 'R';
            hit_points = RandomInt(16, 24);
            attack = RandomInt(12, 18);
            defense = RandomInt(3, 6);
            break;
        case kLichen:
            name = "the lichen";
            display = 'L';
            hit_points = RandomInt(20, 28);
            attack = RandomInt(5, 9);
            defense = RandomInt(7, 10);
            break;
        case kNewt:
            name = "the newt";
            display = 'N';
            hit_points = RandomInt(10, 18);
            attack = RandomInt(20, 24);
            defense = RandomInt(2, 5);
            break;
        case kZombie:
            name = "the zombie";
            display = 'Z';
            hit_points = RandomInt(14, 22);
            attack = RandomInt(12, 18);
            defense = RandomInt(6, 10);
            break;
            
        default:
            perror("Random choice error!");
            break;
    }
    return Creature(position, which_floor, name, display, hit_points, attack, defense);
}
