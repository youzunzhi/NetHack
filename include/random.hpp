//
//  random.hpp
//  SimpleNethack
//
//  Created by 尤大智 on 2018/5/17.
//  Copyright © 2018年 尤大智. All rights reserved.
//

#ifndef random_hpp
#define random_hpp

#include <iostream>
#include <random>

//  return an integer i, min<=i<=max
int RandomInt(int min, int max);
//  return true by some chance
bool RandomBool(double chance);
//  return the choice from 1 to number_choice by chance in chance array
int RandomChoice(int number_choice, const double chance_array[]);
#endif /* random_hpp */
