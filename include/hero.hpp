//
//  hero.hpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/11.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#ifndef hero_hpp
#define hero_hpp

#include "getch.hpp"
#include "creature.hpp"
#include "backpack.hpp"
#include "item.hpp"

const int init_backpack_capacity = 20;
const int init_hit_points = 50;
const int init_attack = 20;
const int init_defense = 16;

class Dungeon;
class Hero : public Creature{
    Backpack backpack;
    int attack_plus_bonus;
    int defense_plus_bonus;
    //HungerState hunger_state_;
public:
    Hero(Position position, double capacity = init_backpack_capacity);
    int get_money() const {return backpack.money;}
    int get_capacity() const {return backpack.capacity;}
    void PickItemUp(Item*);
    void CheckStrength(void);
    std::vector<Item*> DropItem(int which_item_to_drop, int which_floor);
    void WieldWeapon(int which_weapon_to_wield);
    void WearArmor(int which_armor_to_wear);
    void ApplyPotion(int which_potion_to_apply);
    void UnequipWeapon(void);
    void UnequipArmor(void);
    
    friend Dungeon;
};


#endif /* hero_hpp */
