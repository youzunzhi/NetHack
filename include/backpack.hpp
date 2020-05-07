//
//  backpack.hpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/15.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#ifndef backpack_hpp
#define backpack_hpp

#include <iostream>
#include <vector>
#include <list>

#include "item.hpp"


struct Backpack {
//    double weight;
    double capacity;
    int money;
//    int number;
    std::vector<Item*> item_in_backpack;
    Backpack(double capacity);
    void PutItemIn(Item * item_in);
    void ShowBackPack(void);
    void ShowWeapon(void);
    void ShowArmor(void);
    void ShowPotion(void);
    Item WeaponWielding(void);
    Item ArmorWearing(void);

//    void TakeItemOut(Item * item_out) {item_in_backpack.remove(item_out);}
};
#endif /* backpack_hpp */
