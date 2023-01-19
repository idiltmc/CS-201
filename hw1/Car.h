//
// Created by user on 3/16/2022.
//

#ifndef CS201_HW1_CAR_H
#define CS201_HW1_CAR_H

#endif //CS201_HW1_CAR_H
#include <iostream>
using namespace std;

class Car{
public:
    Car();
    Car(int id, string pos, char type);

    int getId();
    char getType();
    string getPosition();

    void setId(int id);
    void setPosition(string pos);
    void setType(char t);


private:
    int plateNumber;
    string position;
    char type;

};