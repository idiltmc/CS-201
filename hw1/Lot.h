//
// Created by user on 3/16/2022.
//

#ifndef CS201_HW1_LOT_H
#define CS201_HW1_LOT_H

#endif //CS201_HW1_LOT_H
#include "Car.h"
#include <iostream>
using namespace std;

class Lot{

public:
    Lot();
    Lot(int lotId, int column, int row);
    Lot(const Lot &lot);
    ~Lot();
    Lot &operator=( const Lot& lot );

    int getLotId();
    void emptyLot();
    int getEmptyPlaces();
    void getDimensions();
    int findCarRow(int plateNum);
    int findCarColumn( int plateNum);
    string getLocation(int plateNum);
    char getCarType(int plateNum);
    void removeCar(int plateNumber);
    void addCar( int lotId, string location, string carType, int plateNumber);
    string parkedCars();
    void printLot();

private:
    int lotId;
    int column;
    int row;
    Car** parkingLots;

};