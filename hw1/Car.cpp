//
// Created by user on 3/16/2022.
//
#include "Car.h"
#include <iostream>
using namespace std;

Car::Car(){
    plateNumber = 0;
    position = "";
    type = 'x';
}

Car::Car(int id, string pos, char type){
    plateNumber = id;
    position = pos;
    this-> type = type;
}

int Car::getId(){
    return plateNumber;
}

string Car::getPosition(){
    return position;
}

char Car::getType(){
    return type;
}

void Car::setId(int id){
    plateNumber = id;
}

void Car::setPosition(string pos){
    position = pos;
}

void Car::setType(char t){
    type = t;
}





