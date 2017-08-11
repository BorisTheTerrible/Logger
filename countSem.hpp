//
//  countSem.hpp
//  Logger
//
//  Created by games on 8/9/17.
//  Copyright © 2017 games. All rights reserved.
//

#ifndef countSem_hpp
#define countSem_hpp

#include <stdio.h>
/*
struct counting_semaphore* counting_semaphore_alloc(int value) {
    
    struct counting_semaphore* sem = malloc(sizeof(struct counting_semaphore));
    sem->value = value;
    sem->binary_descriptor1= bsem_alloc();//locks the value
    sem->binary_descriptor2= bsem_alloc();//locks the sing of the value
    if (value <= 0) {
        bsem_down(sem->binary_descriptor2);
    }
    return sem;
}

void down(struct counting_semaphore *sem){
    bsem_down(sem->binary_descriptor2);
    bsem_down(sem->binary_descriptor1);
    sem->value--;
    if (sem->value>0){
        bsem_up(sem->binary_descriptor2);
    }
    bsem_up(sem->binary_descriptor1);
}


void up(struct counting_semaphore* sem) {
    bsem_down(sem->binary_descriptor1);
    sem->value++;
    if (sem->value == 1) {
        bsem_up(sem->binary_descriptor2);
    }
    bsem_up(sem->binary_descriptor1);
}
 */

#endif /* countSem_hpp */
