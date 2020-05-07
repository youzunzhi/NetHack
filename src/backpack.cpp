//
//  backpack.cpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/15.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#include "backpack.hpp"
Backpack::Backpack(double capacity){
    this->capacity = capacity;
    money = 0;
//    number = 0;
}

void Backpack::PutItemIn(Item * item_in) {
//    item_in_backpack.push_back(item_in);
    if (item_in->item_type_==kGold) {
        money+=item_in->value_;
    }
    else {
        item_in_backpack.push_back(item_in);
        capacity -= item_in->weight_;
    }
}
void Backpack::ShowBackPack(void){
    std::cout<<"0 - "<<money<<" gold pieces\n";
    for (int i = 1; i<item_in_backpack.size(); i++) {
        std::cout<<i<<" - "<<item_in_backpack[i]->name_;
        if (item_in_backpack[i]->equipped_) {
            std::cout<<" (equipped)";
        }
        std::cout<<std::endl;
    }
    std::cout<<"(end)\n";
}
void Backpack::ShowWeapon(void){
    for (int i = 0; i<item_in_backpack.size(); i++) {
        if (item_in_backpack[i]->item_type_ == kWeapon) {
            std::cout<<i<<" - "<<item_in_backpack[i]->name_;
            if (item_in_backpack[i]->equipped_) {
                std::cout<<" (equipped)";
            }
            std::cout<<std::endl;
        }
    }
    std::cout<<"(end)\n";
}
void Backpack::ShowArmor(void){
    for (int i = 0; i<item_in_backpack.size(); i++) {
        if (item_in_backpack[i]->item_type_ == kArmor) {
            std::cout<<i<<" - "<<item_in_backpack[i]->name_;
            if (item_in_backpack[i]->equipped_) {
                std::cout<<" (equipped)";
            }
            std::cout<<std::endl;
        }
    }
    std::cout<<"(end)\n";
}
void Backpack::ShowPotion(){
    for (int i = 0; i<item_in_backpack.size(); i++) {
        if (item_in_backpack[i]->item_type_ == kPotion) {
            std::cout<<i<<" - "<<item_in_backpack[i]->name_;
            std::cout<<std::endl;
        }
    }
    std::cout<<"(end)\n";
}
Item Backpack::WeaponWielding(){
    for (int i = 0; i<item_in_backpack.size(); i++) {
        if (item_in_backpack[i]->item_type_==kWeapon&&item_in_backpack[i]->equipped_) {
            return *item_in_backpack[i];
        }
    }
    return Item(Position(-1,-1), -1, kWeapon);
}
Item Backpack::ArmorWearing(){
    for (int i = 0; i<item_in_backpack.size(); i++) {
        if (item_in_backpack[i]->item_type_==kArmor&&item_in_backpack[i]->equipped_) {
            return *item_in_backpack[i];
        }
    }
    return Item(Position(-1,-1), -1, kArmor);
}
