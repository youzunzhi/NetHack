//
//  random.cpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/17.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#include "random.hpp"
int RandomInt(int min, int max){
    if (min>max) {
        perror("RandomInt : min>max");
    }
    std::random_device random_device;
    std::uniform_int_distribution<int> distribution(min,max);
    return distribution(random_device);
}
bool RandomBool(double chance){
    std::random_device random_device;
    std::uniform_real_distribution<double> distribution(0,1);
    double d = distribution(random_device);
    if (d<chance) {
        return true;
    }
    return false;
}
int RandomChoice(int number_choice, const double chance_array[]){
    std::random_device random_device;
    std::uniform_real_distribution<double> distribution(0,1);
    double d = distribution(random_device);
    double sum_chance = 0;
    for (int i = 0; i<number_choice-1; i++) {
        sum_chance +=chance_array[i];
        if (d<sum_chance) {
            return i+1;
        }
    }
    return number_choice;
}
