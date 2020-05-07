//
//  main.cpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/10.
//  Copyright © 2018年 尤大智. All rights reserved.
//  plays a role of UI

#include <iostream>
#include "getch.hpp"
#include "creature.hpp"
#include "hero.hpp"
#include "item.hpp"
#include "floor.hpp"
#include "dungeon.hpp"

const int current_version_dungeon_level = 2;

void StartPage(void){
    system("clear && printf '\e[3J'");
    std::cout<<"\tSimple Nethack\n\t16336212 You Zunzhi\n\n";
    std::cout<<"\tPlease Enter your name:";
}
void EndPage(std::string hero_name){
    std::cout<<std::endl;
    system("clear && printf '\e[3J'");
    std::cout<<"Farewell, "<<hero_name<<"!\n\n\n\n\n\n";
}

int main(int argc, const char * argv[]) {
    int input;
    StartPage();
    Dungeon dungeon(current_version_dungeon_level);
    dungeon.Display();
    while (!dungeon.IsGameEnd()) {
        int turns = dungeon.get_turns();
        input = getch();
        switch (input) {
            case 'h':
                dungeon.OperationMove(LEFT);
                break;
            case 'j':
                dungeon.OperationMove(DOWN);
                break;
            case 'k':
                dungeon.OperationMove(UP);
                break;
            case 'l':
                dungeon.OperationMove(RIGHT);
                break;
            case 'y':
                dungeon.OperationMove(LEFT_UP);
                break;
            case 'u':
                dungeon.OperationMove(RIGHT_UP);
                break;
            case 'b':
                dungeon.OperationMove(LEFT_DOWN);
                break;
            case 'n':
                dungeon.OperationMove(RIGHT_DOWN);
                break;
            case 'K':
                dungeon.OperationKickDoor();
                break;
            case 'c':
                dungeon.OperationCloseDoor();
                break;
            case '\r':
                dungeon.SetDungeonMessage(kNoMessage);
                break;
            case '.':
                dungeon.OperationRest();
                break;
            case '>':
                dungeon.OperationDownstairs();
                break;
            case '<':
                dungeon.OperationUpstairs();
                break;
            case ',':
                dungeon.OperationPickUp();
                break;
            case 'i':
                dungeon.OperationShowBackpack();
                break;
            case 'd':
                dungeon.OperationDrop();
                break;
            case 'w':
                dungeon.OperationWieldWeapon();
                break;
            case 'W':
                dungeon.OperationWearArmor();
                break;
            case 'a':
                dungeon.OperationApply();
                system("clear && printf '\e[3J'");
                break;
                
            case 'q':
                dungeon.EndGame();
                break;
    
            default:
                break;
        }
        if (turns<dungeon.get_turns()) {
            dungeon.OperateEveryMonster();
            dungeon.CheckDeath();
            if (turns%5==0) {
                dungeon.CreateMonster();
                dungeon.RecoverHero();
            }
        }
        dungeon.Display();
    }
    EndPage(dungeon.get_hero_name());
    
    return 0;
}
