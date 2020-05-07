//
//  item.hpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/10.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#ifndef item_hpp
#define item_hpp

#include "position.hpp"
#include "random.hpp"

enum ItemType {
    kGold = 1,
    kWeapon,
    kArmor,
    kPotion
};
enum WeaponType {
    kLongSword = 1,
    kShortSword,
    kClub,
    kShield,
};
enum ArmorType{
    kLeatherArmor = 1,
    kRingMail,
    kDragonScaleMail
};
enum PotionType{
    kHealing = 1,
    kExtraStrength,
    kWater,
};
struct Item {
    Position pos_;
    int which_floor_;
    ItemType item_type_;
    std::string name_;
    char display_;
    int value_;
    int weight_;
    int attack_bonus_;
    int defense_bonus_;
    int hp_bonus_;
    bool belong_to_hero_;
    bool equipped_;
    Item(Position position,int which_floor, ItemType item_type = kGold, std::string name = "", char display_ = '$', int value = 0, int weight = 0, int attack_bonus = 0, int defense_bonus = 0, int hp_bonus = 0, bool belong_to_hero = false, bool equipped = false);
};
Item RandomAnItem(Position position, int which_floor);
Item RandomGold(Position position, int which_floor);
Item RandomWeapon(Position position, int which_floor);
Item RandomArmor(Position position, int which_floor);
Item RandomPotion(Position position, int which_floor);


#endif /* item_hpp */
