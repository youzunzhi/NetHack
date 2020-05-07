//
//  item.cpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/10.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#include "item.hpp"

Item::Item(Position position,int which_floor, ItemType item_type, std::string name, char display, int value, int weight, int attack_bonus, int defense_bonus, int hp_bonus, bool belong_to_hero, bool equipped)
:pos_(position)
{
    which_floor_ = which_floor;
    item_type_ = item_type;
    name_ = name;
    display_ = display;
    value_ = value;
    weight_ = weight;
    attack_bonus_ = attack_bonus;
    defense_bonus_ = defense_bonus;
    hp_bonus_ = hp_bonus;
    belong_to_hero_ = belong_to_hero;
    equipped_ = equipped;
}

Item RandomAnItem(Position position, int which_floor){
    const double chance_each_item_type[4] = {0.2, 0.2, 0.2, 0.4};
    ItemType item_type = (ItemType)RandomChoice(4, chance_each_item_type);
    switch (item_type) {
        case kGold:
            return RandomGold(position, which_floor);
            break;
        case kWeapon:
            return RandomWeapon(position, which_floor);
            break;
        case kArmor:
            return RandomArmor(position, which_floor);
            break;
        case kPotion:
            return RandomPotion(position, which_floor);
            break;
            
        default:
            perror("Random choice error!");
            break;
    }
    
}
Item RandomGold(Position position, int which_floor){
    int value = 0;
    value = RandomInt(1, 10);
    std::string gold_name;
    if (value == 1) {
        gold_name = "gold piece";
    }
    else {
        gold_name = "gold pieces";
    }
    return Item(position, which_floor, kGold, gold_name, '$', value);
}
Item RandomWeapon(Position position, int which_floor){
    const double chance_each_weapon_type[4] = {0.3, 0.3, 0.2, 0.2};
    WeaponType weapon_type = (WeaponType)RandomChoice(4, chance_each_weapon_type);
    std::string name = "";
    int weight = 0;
    int attack_bonus = 0;
    int defense_bonus = 0;
    int value = 0; //can be useful if there's a transaction system
    switch (weapon_type) {
        case kLongSword:
            name = "a long sword";
            weight = RandomInt(3, 7);
            attack_bonus = RandomInt(1, 5);
            value = attack_bonus + 3;
            break;
        case kShortSword:
            name = "a short sword";
            weight = RandomInt(2, 5);
            attack_bonus = RandomInt(1, 3);
            value = attack_bonus + 2;
            break;
        case kClub:
            name = "a club";
            weight = RandomInt(6, 9);
            attack_bonus = RandomInt(2, 4);
            value = attack_bonus + 1;
            break;
        case kShield:
            name = "a shield";
            weight = RandomInt(7, 10);
            defense_bonus = RandomInt(3, 6);
            value = attack_bonus + 4;
            break;
        default:
            perror("Random weapon error!");
            break;
    }
    return Item(position, which_floor, kWeapon, name, ')', value, weight, attack_bonus, defense_bonus, 0);
}
Item RandomArmor(Position position, int which_floor){
    const double chance_each_armor_type[3] = {0.6, 0.3, 0.1};
    ArmorType armor_type = (ArmorType)RandomChoice(4, chance_each_armor_type);
    std::string name = "";
    int weight = 0;
    int attack_bonus = 0;
    int defense_bonus = 0;
    int value = 0; //can be useful if there's a transaction system
    switch (armor_type) {
        case kLeatherArmor:
            name = "a leather armor";
            weight = RandomInt(14, 20);
            defense_bonus = RandomInt(1, 5);
            value = defense_bonus + 10;
            break;
        case kRingMail:
            name = "a ring mail";
            weight = RandomInt(25, 40);
            defense_bonus = RandomInt(4, 7);
            value = defense_bonus + 8;
            break;
        case kDragonScaleMail:
            name = "a dragon scale mail";
            weight = RandomInt(15, 21);
            attack_bonus = RandomInt(5, 10);
            defense_bonus = RandomInt(15, 20);
            value = 100;
            break;
        default:
            perror("Random armor error!");
            break;
    }
    return Item(position, which_floor, kArmor, name, '[', value, weight, attack_bonus, defense_bonus, 0);
}
Item RandomPotion(Position position, int which_floor){
    const double chance_each_potion_type[3] = {0.6, 0.3, 0.1};
    PotionType potion_type = (PotionType)RandomChoice(4, chance_each_potion_type);
    std::string name = "";
    int weight = 0;
    int attack_bonus = 0;
    int defense_bonus = 0;
    int hp_bonus = 0;
    int value = 0; //can be useful if there's a transaction system
    switch (potion_type) {
        case kHealing:
            name = "a potion of healing";
            weight = RandomInt(1, 3);
            hp_bonus = RandomInt(10, 40);
            value = hp_bonus/10 + 2;
            break;
        case kExtraStrength:
            name = "a potion of extra strength";
            weight = RandomInt(1, 3);
            attack_bonus = RandomInt(1, 3);
            defense_bonus = RandomInt(1, 3);
            value = defense_bonus + attack_bonus;
            break;
        case kWater:
            name = "a bottle of water";
            weight = RandomInt(2, 5);
            break;
        default:
            perror("Random armor error!");
            break;
    }
    return Item(position, which_floor, kPotion, name, '!', value, weight, attack_bonus, defense_bonus, hp_bonus);
}

