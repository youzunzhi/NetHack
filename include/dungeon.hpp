//
//  dungeon.hpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/10.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#ifndef dungeon_hpp
#define dungeon_hpp

#include <vector>
#include <list>
#include "getch.hpp"
#include "random.hpp"
#include "position.hpp"
#include "floor.hpp"
#include "creature.hpp"
#include "hero.hpp"
#include "item.hpp"

const int least_items_number_per_floor = 20;
const int most_items_number_per_floor = 26;
const int least_monsters_number_per_floor = 6;
const int most_monsters_number_per_floor = 10;
enum ObjectsOfDungeon{
    kObstacles,
    kDoorClosed,
    kDoorLocked,
    kDoorOpened,
    kEmptySpace,
    kDownstairs,
    kUpstairs,
    kAmuletOfYendor,
    kUnknown
};
enum MessageType{
    kNoMessage = 0,
    kWelcomeMessage,
    kAskDirection,
    kOpenDoorMessage,
    kDoorLockedMessage,
    kCloseDoorMessage,
    kCloseEmptyMessage,
    kKickDoorMessage,
    kKickEmptyMessage,
    kDownstairsError,
    kUpstairsError,
    kDownstairsMessage,
    kUpstairsMessage,
    kAskLeaveDungeon,
    kPickUpError,
    kTooHeavyMessage,
    kSeeItemMessage,
    kPickUpItemMessage,
    kDropItemMessage,
    kWieldWeaponMessage,
    kWearArmorMessage,
    kApplyPotionMessage,
    kKillMessage,
    kHitMessage,
    kMissMessage,
    kBiteMessage,
    kInvalidMessage
};


class Dungeon {
    int number_floors_;
    int current_floor;
    std::vector<Floor> floors;
    Hero hero;
    std::list<Item> items;
    std::list<Creature> monsters;
    std::string dungeon_message;
    int turns_;
    bool game_end_;
public:
    Dungeon(int number_floors);
    void EnterHeroName(void);
    std::string get_hero_name(void) {return hero.get_name();}
    int get_turns(void) const {return turns_;}
    void InitItemsOnFloor(Floor, int);
    void InitItemsOfHero(void);
    void InitMonstersOnFloor(Floor, int);
    
    void SetDungeonMessage(MessageType);
    void SetDungeonMessage(MessageType, std::vector<Item*>);
    void SetDungeonMessage(MessageType, Item);
    void SetDungeonMessage(MessageType, Creature);
    
    void OperationMove(Directions);
    void OperationCloseDoor(void);
    void OperationKickDoor(void);
    void OperationRest(void);
    void OperationDownstairs(void);
    void OperationUpstairs(void);
    void OperationPickUp(void);
    void OperationShowBackpack(void);
    void OperationDrop(void);
    void OperationWieldWeapon(void);
    void OperationWearArmor(void);
    void OperationApply(void);
    
    void Display(void) const;
    void DisplayMessage(void) const;
    void DisplayDungeon(void) const;
    void DisplayHeroState(void) const;
    void DisplayGameWin(void) const;
    void DisplayGameLost(void) const;
    
    FloorChar get_current_floor_char_at_pos(Position);
    void NextTurn(void){turns_ ++;}
    ObjectsOfDungeon ObjectsOnPosition(Position);
    ObjectsOfDungeon ObjectsOnDirection(Directions, Creature);
    void OpenDoor(Directions);
    void CloseDoor(Directions);
    void KickDoor(Directions);
    bool IsThereAnItem(Position);
    std::vector<Item*> WhatItemsAreThere(Position);
    bool IsThereAMonster(Position);
    Creature* WhichMonsterIsThere(Position);
    void OperateEveryMonster(void);
    void CheckDeath(void);
    void CreateMonster(void);
    void RecoverHero(void);
    
    bool IsGameEnd(void) {return game_end_;}
    void EndGame(void){game_end_ = true;}
};



#endif /* dungeon_hpp */
