//
// Created by user on 3/16/2022.
//

#ifndef CS201_HW1_PARKINGSYSTEM_H
#define CS201_HW1_PARKINGSYSTEM_H

#endif //CS201_HW1_PARKINGSYSTEM_H

#include "Lot.h"
#include <iostream>
using namespace std;
class ParkingSystem{

public:
    ParkingSystem();
    ~ParkingSystem();
    void createLot(int id, int rows, int columns);
    void removeLot(int id);
    void listLots();
    void lotContents(int id);
    void parkCar(int lotId, string location, string carType, int plateNumber);
    void findCar(int plateNumber);
    void removeCar(int plateNumber);
    int indexOfLot(int id);

private:
    Lot *lots;
    int numOfLots;

};

