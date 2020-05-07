//
//  dungeon.cpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/10.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#include "dungeon.hpp"
#include <cstdio>
#include <stdlib.h>
#include <iostream>


Dungeon::Dungeon(int number_floors)
:hero(Position(-1,-1))
{
    number_floors_ = number_floors;
    current_floor = 0;
    InitItemsOfHero();
    for (int i = 0; i<number_floors_; i++) {
        floors.push_back(Floor(i));
        InitItemsOnFloor(floors[i], i);
        InitMonstersOnFloor(floors[i], i);
    }
    hero.set_pos(floors[0].get_upstairs_pos());
    EnterHeroName();
    //hero.set_name("hero");
    SetDungeonMessage(kWelcomeMessage);
    
    turns_ = 1;
    game_end_ = false;
}

void Dungeon::InitItemsOnFloor(Floor floor, int which_floor){
    int item_number = RandomInt(least_items_number_per_floor, most_items_number_per_floor);
    Position new_item_position;
    for (int i = 0; i<item_number; i++) {
        new_item_position = floor.RandomEmptySpace();
        Item new_item = RandomAnItem(new_item_position, which_floor);
        items.push_back(new_item);
    }
}
void Dungeon::InitItemsOfHero(void){
    Item init_money(Position(hero.get_pos()), current_floor, kGold, "gold pieces", '$', 0, 0, 0, 0, 0, true, false);
    items.clear();
    items.push_back(init_money);
    hero.backpack.item_in_backpack.clear();
    std::list<Item>::iterator Item_iter = items.begin();
    hero.backpack.item_in_backpack.push_back(&*Item_iter);
    Item init_weapon(Position(hero.get_pos()), current_floor, kWeapon, "a long sword", ')', 6, 5, 3, 0, 0, true, true);
    items.push_back(init_weapon);
    Item_iter++;
    hero.backpack.item_in_backpack.push_back(&*Item_iter);
    Item init_armor(Position(hero.get_pos()), current_floor, kArmor, "a leather armor", '[', 12, 16, 0, 3, 0, true, true);
    items.push_back(init_armor);
    Item_iter++;
    hero.backpack.item_in_backpack.push_back(&*Item_iter);
    hero.CheckStrength();
}
void Dungeon::InitMonstersOnFloor(Floor floor, int which_floor){
    int monster_number = RandomInt(least_monsters_number_per_floor, most_monsters_number_per_floor);
    Position new_monster_position;
    for (int i = 0; i<monster_number; i++) {
        new_monster_position = floor.RandomEmptySpace();
        // there can't be more than one monster in one position
        while (IsThereAMonster(new_monster_position)) {
            new_monster_position = floor.RandomEmptySpace();
        }
        Creature new_monster = RandomAnMonster(new_monster_position, which_floor);
        monsters.push_back(new_monster);
    }
}

void Dungeon::EnterHeroName(void){
    std::string hero_name;
    std::cin>>hero_name;
    hero.set_name(hero_name);
    getchar(); // absorbs the return key when player keyed in the hero name, so that it won't affect the display message function when welcome
}




void Dungeon::SetDungeonMessage(MessageType message_type){
    switch (message_type) {
        case kNoMessage:
            dungeon_message = "";
            break;
        case kWelcomeMessage:
            dungeon_message = hero.get_name() + ", welcome to NetHack!\nBe careful!  New moon tonight.";
            break;
        case kAskDirection:
            dungeon_message = "In what direction?";
            break;
        case kOpenDoorMessage:
            dungeon_message = "The door opens.";
            break;
        case kCloseDoorMessage:
            dungeon_message = "The door is closed.";
            break;
        case kKickDoorMessage:
            dungeon_message = "As you kick the door, it crashes open!";
            break;
        case kDoorLockedMessage:
            dungeon_message = "The door is locked!";
            break;
        case kCloseEmptyMessage:
            dungeon_message = "You see no open door there.";
            break;
        case kKickEmptyMessage:
            dungeon_message = "You kick at empty space.";
            break;
        case kInvalidMessage:
            dungeon_message = "Invalid Operation.";
            break;
        case kDownstairsError:
            dungeon_message = "You can't go down here.";
            break;
        case kUpstairsError:
            dungeon_message = "You can't go up here.";
            break;
        case kUpstairsMessage:
            dungeon_message = "You climb up the stairs.";
            break;
        case kDownstairsMessage:
            dungeon_message = "You descend the stairs.";
            break;
        case kAskLeaveDungeon:
            dungeon_message = "Beware, there will be no return! Still climb? [yn] (n) ";
            break;
        case kPickUpError:
            dungeon_message = "There is nothing here to pick up.";
            break;
        case kTooHeavyMessage:
            dungeon_message = "Your backpack is too heavy!";
            break;
        default:
            perror("Set message error!");
            break;
    }
}
void Dungeon::SetDungeonMessage(MessageType message_type, std::vector<Item*> items_vector){
    std::string pre_message;
    switch (message_type) {
        case kSeeItemMessage:
            pre_message = "You see here ";
            break;
        case kPickUpItemMessage:
            pre_message = "You pick up ";
            break;
            
        default:
            perror("Set message error!");
            break;
    }
    //  if there are zero items
    if (items_vector.size()==0) {
        SetDungeonMessage(kNoMessage);
        return;
    }
    if (items_vector[0]->item_type_ == kGold) {
        dungeon_message = pre_message + std::to_string(items_vector[0]->value_) + " " + items_vector[0]->name_;
    }else{
        dungeon_message = pre_message + items_vector[0]->name_;
    }
    //  if there are not only one item
    for (int i = 1; i<items_vector.size(); i++) {
        if (items_vector[i]->item_type_ == kGold) {
            dungeon_message = dungeon_message + "\nand " + std::to_string(items_vector[0]->value_) + " " + items_vector[i]->name_;

        }else{
            dungeon_message = dungeon_message + "\nand " +items_vector[i]->name_;
        }
    }
    dungeon_message += ".";
}
void Dungeon::SetDungeonMessage(MessageType message_type, Item item){
    std::string pre_message;
    switch (message_type) {
        case kDropItemMessage:
            pre_message = "You drop ";
            break;
        case kWieldWeaponMessage:
            pre_message = "Now you are wielding ";
            break;
        case kWearArmorMessage:
            pre_message = "Now you are wearing ";
            break;
        case kApplyPotionMessage:
            pre_message = "You apply ";
            break;
            
        default:
            perror("Set message error!");
            break;
    }
    if (item.item_type_ == kGold) {
        dungeon_message = pre_message + std::to_string(item.value_) + " " + item.name_;
    }else{
        dungeon_message = pre_message + item.name_;
    }
    dungeon_message += ".";
}
void Dungeon::SetDungeonMessage(MessageType message_type, Creature creature){
    if (message_type == kBiteMessage) {
        dungeon_message += "\n" + creature.get_name() + " bites!";
    }else{
        std::string pre_message;
        switch (message_type) {
            case kKillMessage:
                pre_message = "You kill ";
                break;
            case kHitMessage:
                pre_message = "You hit ";
                break;
            case kMissMessage:
                pre_message = "You miss ";
                break;
                
            default:
                perror("Set message error!");
                break;
        }
        dungeon_message = pre_message + creature.get_name() + ".";
    }
}

void Dungeon::OperationMove(Directions direction){
    SetDungeonMessage(kNoMessage);
    ObjectsOfDungeon object_hero_direction = ObjectsOnDirection(direction, hero);
    Position hero_next_position = hero.get_pos() + direction;
    if (IsThereAMonster(hero_next_position)) {
        Creature* monster_there = WhichMonsterIsThere(hero_next_position);
        hero.Attack(*monster_there);
        if (monster_there->IsDead()) {
            SetDungeonMessage(kKillMessage, *monster_there);
            for (std::list<Creature>::iterator iter = monsters.begin(); iter != monsters.end(); iter ++) {
                if (&*iter == monster_there) {
                    monsters.erase(iter);
                    break;
                }
            }
        }else{
            if (RandomBool(0.25)) { //  If one didn't kill the other, he can hardly tell if he miss or hit
                SetDungeonMessage(kHitMessage, *monster_there);
            }else{
                SetDungeonMessage(kMissMessage, *monster_there);
            }
        }
        NextTurn();
    }
    else if (object_hero_direction==kEmptySpace||
             object_hero_direction==kDoorOpened||
        object_hero_direction==kDownstairs||
        object_hero_direction==kUpstairs) {
        hero.Move(direction);
        NextTurn();
        if (IsThereAnItem(hero.get_pos())) {
            SetDungeonMessage(kSeeItemMessage, WhatItemsAreThere(hero.get_pos()));
        }
        
    }
    else if (object_hero_direction==kDoorClosed) {
        OpenDoor(direction);
        SetDungeonMessage(kOpenDoorMessage);
    }
    else if (object_hero_direction==kDoorLocked) {
        SetDungeonMessage(kDoorLockedMessage);
    }
    else if (object_hero_direction==kAmuletOfYendor){
        DisplayGameWin();
        AskforReturn();
        EndGame();
    }
}

void Dungeon::OperationCloseDoor(void){
    SetDungeonMessage(kAskDirection);
    Display();
    Directions direction = DEFAULT;
    int input = getch();
    switch (input) {
        case 'h':
            direction = LEFT;
            break;
        case 'j':
            direction = DOWN;
            break;
        case 'k':
            direction = UP;
            break;
        case 'l':
            direction = RIGHT;
            break;
        case 'y':
            direction = LEFT_UP;
            break;
        case 'u':
            direction = RIGHT_UP;
            break;
        case 'b':
            direction = LEFT_DOWN;
            break;
        case 'n':
            direction = RIGHT_DOWN;
            break;
        default:
            SetDungeonMessage(kInvalidMessage);
            return;
            break;
    }
    CloseDoor(direction);
}
void Dungeon::OperationKickDoor(void){
    SetDungeonMessage(kAskDirection);
    Display();
    Directions direction = DEFAULT;
    int input = getch();
    switch (input) {
        case 'h':
            direction = LEFT;
            break;
        case 'j':
            direction = DOWN;
            break;
        case 'k':
            direction = UP;
            break;
        case 'l':
            direction = RIGHT;
            break;
        case 'y':
            direction = LEFT_UP;
            break;
        case 'u':
            direction = RIGHT_UP;
            break;
        case 'b':
            direction = LEFT_DOWN;
            break;
        case 'n':
            direction = RIGHT_DOWN;
            break;
        default:
            SetDungeonMessage(kInvalidMessage);
            return;
            break;
    }
    KickDoor(direction);
}
void Dungeon::OperationRest(){
    turns_++;
}
void Dungeon::OperationDownstairs(void){
    if (ObjectsOnPosition(hero.get_pos())!=kDownstairs) {
        SetDungeonMessage(kDownstairsError);
        return;
    }
    SetDungeonMessage(kDownstairsMessage);
    current_floor ++;
    hero.set_pos(floors[current_floor].get_upstairs_pos());
    NextTurn();
}
void Dungeon::OperationUpstairs(void){
    if (ObjectsOnPosition(hero.get_pos())!=kUpstairs) {
        SetDungeonMessage(kUpstairsError);
        return;
    }
    SetDungeonMessage(kUpstairsMessage);
    if (current_floor==0) {
        SetDungeonMessage(kAskLeaveDungeon);
        Display();
        if (AskYesOrNo()) {
            EndGame();
        }else{
            SetDungeonMessage(kNoMessage);
        }
    }
    else{
        current_floor --;
        hero.set_pos(floors[current_floor].get_downstairs_pos());
        NextTurn();
    }
}
void Dungeon::OperationPickUp(void){
    if (!IsThereAnItem(hero.get_pos())) {
        SetDungeonMessage(kPickUpError);
        return;
    }
    else{
        std::vector<Item*> item_ptrs_vector = WhatItemsAreThere(hero.get_pos());
        int max_weight = item_ptrs_vector[0]->weight_;
        for (int i = 1; i<item_ptrs_vector.size(); i++) {
            if (item_ptrs_vector[i]->weight_>max_weight) {
                max_weight = item_ptrs_vector[i]->weight_;
            }
        }
        //  hero cannot choose which one to pick if there're more than one items on the position in current version
        //  so if he can't lift the heaviest item he can't lift them all
        if (hero.get_capacity()<max_weight) {
            SetDungeonMessage(kTooHeavyMessage);
            return;
        }
        SetDungeonMessage(kPickUpItemMessage, item_ptrs_vector);
        for (int i = 0; i < item_ptrs_vector.size(); i++) {
//            hero.PickItemUp(item_ptrs_vector[i]);
            item_ptrs_vector[i]->belong_to_hero_ = true;
//            hero.backpack.PutItemIn(item_ptrs_vector[i]);
            if (item_ptrs_vector[i]->item_type_==kGold) {
                hero.backpack.money+=item_ptrs_vector[i]->value_;
                hero.backpack.item_in_backpack[0]->value_ = hero.backpack.money;
                for (std::list<Item>::iterator iter = items.begin(); iter != items.end();iter++) {
                    if (&*iter == item_ptrs_vector[i]) {
                        items.erase(iter);
                        break;
                    }
                }
            }
            else {
                hero.backpack.item_in_backpack.push_back(item_ptrs_vector[i]);
                hero.backpack.capacity -= item_ptrs_vector[i]->weight_;
            }
        }
        
    }
    
}
void Dungeon::OperationShowBackpack(void){
    system("clear && printf '\e[3J'");
    hero.backpack.ShowBackPack();
    AskforReturn();
}
void Dungeon::OperationDrop(void){
    system("clear && printf '\e[3J'");
    std::cout<<"What do you want to drop?\n";
    hero.backpack.ShowBackPack();
    int which_item_to_drop;
    std::cin>>which_item_to_drop;
    if (which_item_to_drop == 0 && hero.get_money() == 0) {
        SetDungeonMessage(kNoMessage);
        return;
    } //  can't drop zero money
    Item item_drop(hero.get_pos(), current_floor);
    if (which_item_to_drop == 0) { //  when dropping money
        std::string gold_name;
        if (hero.backpack.money == 1) {
            gold_name = "gold piece";
        }
        else {
            gold_name = "gold pieces";
        }
        item_drop = Item(hero.get_pos(), current_floor, kGold, gold_name, '$', hero.backpack.money);
        items.push_back(item_drop);
        hero.backpack.money = 0;
        hero.backpack.item_in_backpack[0]->value_ = 0;
    }
    else {
        if (which_item_to_drop>hero.backpack.item_in_backpack.size()-1||which_item_to_drop<0) {
            return;
        }
        hero.backpack.item_in_backpack[which_item_to_drop]->belong_to_hero_ = false;
        hero.backpack.item_in_backpack[which_item_to_drop]->equipped_ = false;
        hero.backpack.item_in_backpack[which_item_to_drop]->pos_ = hero.get_pos();
        hero.backpack.item_in_backpack[which_item_to_drop]->which_floor_ = current_floor;
        hero.backpack.capacity += hero.backpack.item_in_backpack[which_item_to_drop]->weight_;
        item_drop = *hero.backpack.item_in_backpack[which_item_to_drop];
        hero.backpack.item_in_backpack.erase(hero.backpack.item_in_backpack.begin()+which_item_to_drop);
    }
    hero.CheckStrength();
    SetDungeonMessage(kDropItemMessage, item_drop);
}
void Dungeon::OperationWieldWeapon(void){
    system("clear && printf '\e[3J'");
    std::cout<<"What do you want to wield? (Key in the corresponding number)\n";
    hero.backpack.ShowWeapon();
    int which_weapon_to_wield;
    std::cin>>which_weapon_to_wield;
    if (which_weapon_to_wield>hero.backpack.item_in_backpack.size()-1||which_weapon_to_wield<0||hero.backpack.item_in_backpack[which_weapon_to_wield]->item_type_!=kWeapon){
        SetDungeonMessage(kNoMessage);
    }else{
        hero.WieldWeapon(which_weapon_to_wield);
        SetDungeonMessage(kWieldWeaponMessage, *hero.backpack.item_in_backpack[which_weapon_to_wield]);
    }
}
void Dungeon::OperationWearArmor(void){
    system("clear && printf '\e[3J'");
    std::cout<<"What do you want to wear? (Key in the corresponding number)\n";
    hero.backpack.ShowArmor();
    int which_armor_to_wear;
    std::cin>>which_armor_to_wear;
    if (which_armor_to_wear>hero.backpack.item_in_backpack.size()-1||which_armor_to_wear<0||hero.backpack.item_in_backpack[which_armor_to_wear]->item_type_!=kArmor){
        SetDungeonMessage(kNoMessage);
    }else{
        hero.WearArmor(which_armor_to_wear);
        SetDungeonMessage(kWearArmorMessage, *hero.backpack.item_in_backpack[which_armor_to_wear]);
    }
}
void Dungeon::OperationApply(void){
    system("clear && printf '\e[3J'");
    std::cout<<"What do you want to apply? (Key in the corresponding number)\n";
    hero.backpack.ShowPotion();
    int which_potion_to_apply;
    std::cin>>which_potion_to_apply;
    if (which_potion_to_apply>hero.backpack.item_in_backpack.size()-1||which_potion_to_apply<0||hero.backpack.item_in_backpack[which_potion_to_apply]->item_type_!=kPotion){
        SetDungeonMessage(kNoMessage);
    }else{
        hero.ApplyPotion(which_potion_to_apply);
        for (std::list<Item>::iterator iter = items.begin(); iter != items.end();iter++) {
            if (&*iter == hero.backpack.item_in_backpack[which_potion_to_apply]) {
                items.erase(iter);
                break;
            }
        }
        SetDungeonMessage(kApplyPotionMessage, *hero.backpack.item_in_backpack[which_potion_to_apply]);
        hero.backpack.item_in_backpack.erase(hero.backpack.item_in_backpack.begin()+which_potion_to_apply);
    }
}

/*--------------------------------------------------------*/
void Dungeon::Display(void) const{
    system("clear && printf '\e[3J'");
    DisplayMessage();
    DisplayDungeon();
    DisplayHeroState();
}

void Dungeon::DisplayMessage(void) const{
    unsigned long nextline_char_pos = dungeon_message.find("\n");
    std::string rest_line = dungeon_message.substr(nextline_char_pos+1);
    while (nextline_char_pos!=-1) {
        std::string current_line = dungeon_message.substr(0, nextline_char_pos);
        //SetDungeonMessage(current_line);
        std::cout<<current_line<<"--More--\n\n";
        DisplayDungeon();
        DisplayHeroState();
        AskforReturn();
        nextline_char_pos = rest_line.find("\n");
        rest_line = rest_line.substr(nextline_char_pos+1);
    }
    system("clear && printf '\e[3J'");
    std::cout<<rest_line;
    std::cout<<std::endl<<std::endl;
}

void Dungeon::DisplayDungeon(void) const{
    char dungeon_display[kFloorHeight][kFloorLength];
    for (int i = 0; i<kFloorHeight; i++) {
        for (int j = 0; j<kFloorLength; j++) {
            dungeon_display[i][j] = (char)floors[current_floor].get_floor_char_at_pos(Position(j,i));
        }
    }
    for (std::list<Item>::const_iterator iter = items.begin(); iter!=items.end(); iter++) {
        if (iter->which_floor_==current_floor&&iter->belong_to_hero_==false) {
            dungeon_display[iter->pos_.pos_y_][iter->pos_.pos_x_] = iter->display_;
        }
    }
    for (std::list<Creature>::const_iterator iter = monsters.begin(); iter!=monsters.end(); iter++) {
        if (iter->get_which_floor() == current_floor) {
            dungeon_display[iter->get_pos().pos_y_][iter->get_pos().pos_x_] = iter->get_display();
        }
    }
    dungeon_display[hero.get_pos().pos_y_][hero.get_pos().pos_x_] = hero.get_display();
    for (int i = 0; i<kFloorHeight; i++) {
        for (int j = 0; j<kFloorLength; j++) {
            printf("%c", dungeon_display[i][j]);
        }
        printf("\n");
    }
}

void Dungeon::DisplayHeroState(void) const{
    std::cout<<hero.get_name()<<"    Strength:"<<hero.attack_plus_bonus<<" Defense:"<<hero.defense_plus_bonus<<std::endl;
    std::cout<<"Dlvl:"<<current_floor+1<<"  $:"<<hero.get_money()<<"  HP:"<<hero.get_hit_points()<<" T:"<<turns_<<std::endl;
}
void Dungeon::DisplayGameWin(void) const{
    system("clear && printf '\e[3J'");
    std::cout<<"Congratulations. You find the Amulet of Yendor.\n";
    std::cout<<"Now you can offer it to your god to become immortal.\n";
    std::cout<<"(Press ENTER to quit)\n";
}
void Dungeon::DisplayGameLost(void) const{
    system("clear && printf '\e[3J'");
    char output[15][50] = {
        "                  ----------",
        "                 /          \\",
        "                /    REST    \\",
        "               /      IN      \\",
        "              /     PEACE      \\",
        "             /                  \\",
        "             |                  |",
        "             |                  |",
        "             |                  |",
        "             |                  |",
        "             |                  |",
        "             |                  |",
        "             |       2018       |",
        "            *|     *  *  *      | *",
        "   _________)/\\\\_//(\\/(/\\)/\\//\\/|_)_______"
    };
    int tomb_middle_x = 22;
    int tomb_middle_y = 6;
    int tomb_start = tomb_middle_x - (int)hero.get_name().length()/2;
    for (int i = 0; i<hero.get_name().length(); i++) {
        output[tomb_middle_y][tomb_start+i] = hero.get_name()[i];
    }
    for (int i = 0; i<15; i++) {
        for (int j = 0; j<50; j++) {
            std::cout<<output[i][j];
        }
        std::cout<<"\n";
    }
    std::cout<<"\n(Press ENTER to quit)";
}

FloorChar Dungeon::get_current_floor_char_at_pos(Position position){
    return floors[current_floor].get_floor_char_at_pos(position);
}
ObjectsOfDungeon Dungeon::ObjectsOnPosition(Position position){
    FloorChar floor_char_at_pos =  get_current_floor_char_at_pos(position); //suppose creatures not in current floor do not move
    if (floor_char_at_pos == kHorizontalWall ||
        floor_char_at_pos == kVerticalWall ||
        floor_char_at_pos == kBlank ||
        floor_char_at_pos == kNone){
        return kObstacles;
    }
    if (floor_char_at_pos == kDoorClosedChar) {
        if (floors[current_floor].IsDoorLocked(position)) {
            return kDoorLocked;
        }else
            return kDoorClosed;
    }
    if (floor_char_at_pos == kDoorOpenedChar) {
        return kDoorOpened;
    }
    if (floor_char_at_pos == kFloor || floor_char_at_pos == kHallway) {
        return kEmptySpace;
    }
    if (floor_char_at_pos == kDownstairsChar) {
        return kDownstairs;
    }
    if (floor_char_at_pos == kUpstairsChar) {
        return kUpstairs;
    }
    if (floor_char_at_pos == kAmuletOfYendorChar) {
        return kAmuletOfYendor;
    }
    return kUnknown;
}
ObjectsOfDungeon Dungeon::ObjectsOnDirection(Directions direction, Creature creature){
    Position new_pos = hero.get_pos() + direction;
    return ObjectsOnPosition(new_pos);
}

void Dungeon::OpenDoor(Directions direction){
    Position door_pos = hero.get_pos() + direction;
    floors[current_floor].set_floor_char_at_pos(door_pos, kDoorOpenedChar);
    NextTurn();
}
void Dungeon::CloseDoor(Directions direction){
    Position door_pos = hero.get_pos() + direction;
    if (get_current_floor_char_at_pos(door_pos) != kDoorOpenedChar) {
        SetDungeonMessage(kCloseEmptyMessage);
    }
    else{
        SetDungeonMessage(kCloseDoorMessage);
        floors[current_floor].set_floor_char_at_pos(door_pos, kDoorClosedChar);
    }
    NextTurn();
}
void Dungeon::KickDoor(Directions direction){
    Position door_pos = hero.get_pos() + direction;
    if (get_current_floor_char_at_pos(door_pos) != kDoorClosedChar) {
        SetDungeonMessage(kKickEmptyMessage);
    }
    else{
        SetDungeonMessage(kKickDoorMessage);
        floors[current_floor].set_floor_char_at_pos(door_pos, kFloor);
    }
    NextTurn();
}
bool Dungeon::IsThereAnItem(Position position){
    for (std::list<Item>::iterator iter = items.begin(); iter!=items.end(); iter++) {
        if (iter->pos_ == position && iter->which_floor_==current_floor&&iter->belong_to_hero_==false) {
            return true;
        }
    }
    return false;
}
std::vector<Item*> Dungeon::WhatItemsAreThere(Position position){
    std::vector<Item*> item_ptrs_vector;
    for (std::list<Item>::iterator iter = items.begin(); iter!=items.end(); iter++) {
        if (iter->pos_ == position && iter->which_floor_==current_floor&&iter->belong_to_hero_==false) {
            item_ptrs_vector.push_back(&*iter);
        }
    }
    return item_ptrs_vector;
}
bool Dungeon::IsThereAMonster(Position position){
    for (std::list<Creature>::iterator iter = monsters.begin(); iter!=monsters.end(); iter++) {
        if (iter->get_pos() == position && iter->get_which_floor() == current_floor) {
            return true;
        }
    }
    return false;
}
Creature* Dungeon::WhichMonsterIsThere(Position position){
    Creature* monster_ptr = nullptr;
    for (std::list<Creature>::iterator iter = monsters.begin(); iter!=monsters.end(); iter++) {
        if (iter->get_pos() == position && iter->get_which_floor() == current_floor) {
            monster_ptr = &*iter;
            return monster_ptr;
        }
    }
    perror("No monster here!");
    return monster_ptr;
}
void Dungeon::OperateEveryMonster(){
    for (std::list<Creature>::iterator iter = monsters.begin(); iter!=monsters.end(); iter++) {
        if (iter->get_which_floor() == current_floor) {
            Position monster_next_pos = iter->get_pos() + (Directions)0;
            int min_distance_from_hero = monster_next_pos - hero.get_pos();
            Directions min_distance_direction = (Directions)0;
            for (int i = 1; i<8; i++) {
                monster_next_pos = iter->get_pos() + (Directions)i;
                if (min_distance_from_hero>monster_next_pos-hero.get_pos()) {
                    min_distance_direction = (Directions)i;
                    min_distance_from_hero = monster_next_pos-hero.get_pos();
                }
            }
            monster_next_pos = iter->get_pos() + min_distance_direction;
            if (monster_next_pos==hero.get_pos()) {
                iter->Attack(hero);
                SetDungeonMessage(kBiteMessage, *iter);
            }
            else{
                ObjectsOfDungeon object_monster_next_pos = ObjectsOnPosition(monster_next_pos);
                if (object_monster_next_pos == kEmptySpace||object_monster_next_pos == kDoorOpened||object_monster_next_pos == kDownstairs||object_monster_next_pos == kUpstairs) {
                    iter->Move(min_distance_direction);
                }
            }
        }
    }
}
void Dungeon::CheckDeath(){
    if (hero.get_hit_points()<=0) {
        DisplayGameLost();
        AskforReturn();
        EndGame();
    }
}
void Dungeon::CreateMonster(void){
    Position new_monster_position = floors[current_floor].RandomEmptySpace();
    // there can't be more than one monster in one position
    while (IsThereAMonster(new_monster_position)) {
        new_monster_position = floors[current_floor].RandomEmptySpace();
    }
    Creature new_monster = RandomAnMonster(new_monster_position, current_floor);
    monsters.push_back(new_monster);
}
void Dungeon::RecoverHero(void){
    hero.hit_points_ += 5;
}
