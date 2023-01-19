//
// Created by user on 3/16/2022.
//
#include "Lot.h"
#include <iostream>
using namespace std;

// default constructor
Lot::Lot(){
    lotId = 0;
    row = 0;
    column = 0;
}
//constructor
Lot::Lot(int id, int column, int row){

    this-> column = column;
    this -> row = row;
    // using two-dimensional array for parking spaces

    // one dimensional array for every row in the lot
    parkingLots = new Car*[row];
    lotId = id;

    for(int i = 0 ; i < row ; i++){
        //all the rows in the lot, points to a column
        parkingLots[i] = new Car[column];
    }
}

//assignment operator
//if the given array does not equal to the one we created, initialize the new array with same values
Lot &Lot::operator=(const Lot &right) {

    if(this != &right){
        this-> column = right.column;
        this -> row = right.row;
        this -> lotId = right.lotId;

        parkingLots = new Car*[row];

        for(int i = 0 ; i < row ;i ++){
            parkingLots[i] = new Car[column];
        }

        for(int i = 0 ; i < row ; i++){
            for(int j = 0 ; j < column ; j++){
                parkingLots[i][j] = right.parkingLots[i][j];
            }
        }

    }

    return *this;


}

Lot:: ~Lot(){

    for(int i = 0 ; i < row ; i++){
        delete[] parkingLots[i];
    }

    delete parkingLots;
}

//go through every element in the array, return the number of empty spaces
int Lot::getEmptyPlaces(){
    int empty = 0;
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < column ; j++){
            if(parkingLots[i][j].getType() == 'x'){
                empty++;
            }
        }
    }
    return empty;
}
void Lot::emptyLot(){
    //remove every car int the lot
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < column ; j++){

            if(parkingLots[i][j].getType() != 'x'){
                removeCar(parkingLots[i][j].getId());
            }
        }
    }
};
int Lot::findCarRow(int plateNum){

    for(int i = 0 ; i < row; i++){

        for(int j = 0 ; j < column ; j++){

            if(parkingLots[i][j].getId() == plateNum){
                return i;
            }
        }
    }
    return -1;
}

int Lot::findCarColumn(int plateNum){
    int rowIndex = findCarRow(plateNum);
    for(int i = 0 ; i < column ; i ++){
        if(parkingLots[rowIndex][i].getId() == plateNum){
            return i;
        }
    }
    return -1;
}

//find the index of the given car, return to its string location
string Lot::getLocation(int plateNum){

    int r = findCarRow(plateNum);
    int c = findCarColumn(plateNum);


    return parkingLots[r][c].getPosition();
}

void Lot::removeCar(int plateNumber){
    string type = "";
    string location = "";


    int i = findCarRow(plateNumber);
    int j = findCarColumn(plateNumber);
    location = parkingLots[i][j].getPosition();

    //if the car is heavy-duty, we have to remove the car from two slots
    //since findColumn() returns to the top index of the car, remove the one under it too
    if( parkingLots[i][j].getType() == 'b'){
        type = "Heavy-duty car";
        parkingLots[i + 1][j].setId(0);
        parkingLots[i + 1][j].setPosition("");
        parkingLots[i + 1][j].setType('x');


    }

    else{
        type = "Light-duty car";
    }

    //remove the car from only one index
    parkingLots[i][j].setId(0);
    parkingLots[i][j].setPosition("");
    parkingLots[i][j].setType('x');



    cout << type << " with number plate " << plateNumber << " car has been removed from slot "
         << location << ",lot " << lotId << endl;

}


//park the car at the given location
void Lot::addCar( int lotID, string location, string carType, int plateNumber){

    int r = location[0] - 'A';
    int c = location[1] - '1';

    //if there is no car at the slot
    if(parkingLots[r][c].getType() == 'x') {


        //if the type is a, park the car at that location
        if (carType.compare("a") == 0) {

            carType = "Light-duty car";

            parkingLots[r][c].setId(plateNumber);
            parkingLots[r][c].setType('a');
            parkingLots[r][c].setPosition(location);

            cout << carType << " with number plate " << plateNumber << " has been parked at location "
                 << location << ", lot " << lotID << endl;;
        }
        //if the car type is b, park the car at the given location and its top location (ex: c6 and b6)
        if(carType.compare("b") == 0){

            carType = "Heavy-duty car";

            if( r != 0 && parkingLots[r-1][c].getType() == 'x'){

                parkingLots[r][c].setId(plateNumber);
                parkingLots[r][c].setType('b');
                parkingLots[r][c].setPosition(location);
                parkingLots[r-1][c].setId(plateNumber);
                parkingLots[r-1][c].setType('b');
                parkingLots[r-1][c].setPosition(location);

                cout << carType << " with number plate " << plateNumber << " has been parked at location "
                     << location << ", lot " << lotID << endl;;
            }
            else{
                cout << "Cannot park " << carType << " with number plate " << plateNumber << " at location "
                     << location << ", not enough space" << endl;
            }
        }
    } else{
        if(carType.compare("a") == 0){
            carType = "Light-duty car";
        }
        else{
            carType = "Heavy-duty car";
        }
        cout << "Cannot park " << carType << " with number plate " << plateNumber << " at location "
             << location << ", already occupied" << endl;
    }



}


char Lot::getCarType(int plateNum){

    int i = findCarRow(plateNum);
    int j = findCarColumn(plateNum);


    return parkingLots[i][j].getType();
}


int Lot::getLotId(){
    return lotId;
}
//parked cars' list for a certain lot
string Lot::parkedCars(){
    bool fullHeavy = true; //this is used for not including a type b car twice in the list
    bool firstIndex = true; // this is used for determining whether to use a comma before or not
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < column ; j++){
            if(parkingLots[i][j].getType() != 'x'){

                if(parkingLots[i][j].getType() == 'b'){
                    fullHeavy = !fullHeavy;
                    if(fullHeavy){
                        if(firstIndex){
                            firstIndex = false;
                            cout << parkingLots[i][j].getId();
                        }
                        else{
                            cout <<  ", " << parkingLots[i][j].getId() ;
                        }
                    }
                }
                else{
                    if(firstIndex){
                        firstIndex = false;
                        cout << parkingLots[i][j].getId();
                    }
                    else{
                        cout << ", " << parkingLots[i][j].getId();
                    }
                }

            }
        }
    }
    if(firstIndex){
        return "no cars yet";
    }
    return "";
}

void Lot::printLot(){
    for(int i = 0 ; i <= row ; i ++){
        for(int j = 0 ; j <= column ; j++){
            if(i == 0){
                if(j == 0){
                    cout << "  ";
                }
                else{
                    cout << j;
                    cout << "  ";
                }

            }
            else if(j == 0){
                cout << (char)('A'+ (i - 1));
            }

            else{
                if(parkingLots[i-1][j-1].getType() == 'x'){
                    cout<< " + ";
                }
                else{
                    cout << " " << parkingLots[i-1][j-1].getType() << " ";
                }
            }
        }
        cout << endl;
    }

}

void Lot::getDimensions(){
    cout << "(" << row << "," << column << ")";
}


