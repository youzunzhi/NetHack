//
//  hero.cpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/11.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#include "hero.hpp"


Hero::Hero(Position position, double capacity)
    :Creature(position),
     backpack(capacity)
{
    display_ = '@';
    hit_points_ = init_hit_points;
    attack_ = init_attack;
    defense_ = init_defense;
    //hunger_state_ = kSatiated;
}

//void Hero::PickItemUp(Item* item_ptr){
//    item_ptr->belong_to_hero_ = true;
//    backpack.PutItemIn(item_ptr);
//}



void Hero::CheckStrength(){
    attack_plus_bonus = attack_ +  backpack.WeaponWielding().attack_bonus_ + backpack.ArmorWearing().attack_bonus_;
    defense_plus_bonus = defense_ +  backpack.WeaponWielding().defense_bonus_ + backpack.ArmorWearing().defense_bonus_;
}
//std::vector<Item*> Hero::DropItem(int which_item_to_drop, int which_floor){
//    std::vector<Item*> item_drop_ptr;
//    if (which_item_to_drop == 0) { //  when dropping money
//        backpack.money = 0;
//        for (int i = 0; i < backpack.item_in_backpack.size(); i++) {
//            if (backpack.item_in_backpack[i]->item_type_ == kGold) {
//                backpack.item_in_backpack[i]->belong_to_hero_ = false;
//                backpack.item_in_backpack[i]->pos_ = pos_;
//                backpack.item_in_backpack[i]->which_floor_ = which_floor;
//                item_drop_ptr.push_back(backpack.item_in_backpack[i]);
//                backpack.item_in_backpack.erase(backpack.item_in_backpack.begin()+i);
//                i--;
//            }
//        }
//    }
//    else {
//        if (which_item_to_drop>backpack.item_in_backpack.size()||which_item_to_drop<0) {
//            return item_drop_ptr;
//        }
//        backpack.item_in_backpack[which_item_to_drop-1]->belong_to_hero_ = false;
//        backpack.item_in_backpack[which_item_to_drop-1]->equipped_ = false;
//        backpack.item_in_backpack[which_item_to_drop-1]->pos_ = pos_;
//        backpack.item_in_backpack[which_item_to_drop-1]->which_floor_ = which_floor;
//        item_drop_ptr.push_back(backpack.item_in_backpack[which_item_to_drop-1]);
//        backpack.item_in_backpack.erase(backpack.item_in_backpack.begin()+which_item_to_drop-1);
//    }
//    return item_drop_ptr;
//}
void Hero::WieldWeapon(int which_weapon_to_wield){
    if (which_weapon_to_wield>backpack.item_in_backpack.size()-1||which_weapon_to_wield<0||backpack.item_in_backpack[which_weapon_to_wield]->item_type_!=kWeapon) {
        return;
    }
    else{
        UnequipWeapon();
        backpack.item_in_backpack[which_weapon_to_wield]->equipped_ = true;
    }
    CheckStrength();
}
void Hero::WearArmor(int which_armor_to_wear){
    if (which_armor_to_wear>backpack.item_in_backpack.size()-1||which_armor_to_wear<0||backpack.item_in_backpack[which_armor_to_wear]->item_type_!=kArmor) {
        return;
    }
    else{
        UnequipArmor();
        backpack.item_in_backpack[which_armor_to_wear]->equipped_ = true;
    }
    CheckStrength();
}
void Hero::ApplyPotion(int which_potion_to_apply){
    if (which_potion_to_apply>backpack.item_in_backpack.size()-1||which_potion_to_apply<0||backpack.item_in_backpack[which_potion_to_apply]->item_type_!=kPotion) {
        return;
    }
    else{
        attack_ += backpack.item_in_backpack[which_potion_to_apply]->attack_bonus_;
        defense_ += backpack.item_in_backpack[which_potion_to_apply]->defense_bonus_;
        hit_points_ += backpack.item_in_backpack[which_potion_to_apply]->hp_bonus_;
        backpack.capacity += backpack.item_in_backpack[which_potion_to_apply]->weight_;
    }
    CheckStrength();
}
void Hero::UnequipWeapon(void){
    for (int i = 0; i<backpack.item_in_backpack.size(); i++) {
        if (backpack.item_in_backpack[i]->item_type_==kWeapon&&backpack.item_in_backpack[i]->equipped_) {
            backpack.item_in_backpack[i]->equipped_ = false;
        }
    }
    CheckStrength();
}
void Hero::UnequipArmor(void){
    for (int i = 0; i<backpack.item_in_backpack.size(); i++) {
        if (backpack.item_in_backpack[i]->item_type_==kArmor&&backpack.item_in_backpack[i]->equipped_) {
            backpack.item_in_backpack[i]->equipped_ = false;
        }
    }
    CheckStrength();
}
