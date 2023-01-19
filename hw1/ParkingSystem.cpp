//
// Created by user on 3/16/2022.
//

#include "ParkingSystem.h"
#include <iostream>
using namespace std;


//constructor
ParkingSystem::ParkingSystem(){

    lots = NULL;
    numOfLots = 0;

}

//destructor
ParkingSystem::~ParkingSystem(){
    if(lots != NULL){
        delete [] lots;
    }
}



void ParkingSystem::createLot(int lotId , int row, int column){

    if(indexOfLot(lotId) != -1){
        cout << "Cannot create the parking lot " << lotId  << ", a lot with this ID already exists" <<endl;
    }

    else if(row > 12 || column > 12 ){
        cout << "Cannot create the parking lot "<< lotId << ", dimensions exceed acceptable bounds" <<endl;
    }

    else{

        //if there are no lots at the array, initializes the 0th index
        if(numOfLots == 0){
            lots = new Lot[1];
            lots[0] = Lot(lotId , column, row);
        }


        else{
            //create another dynamically allocated Lot array whose size will be 1 more than the original
            Lot* tempLot = new Lot[numOfLots + 1];

            //add all the elements in the original array to the temp
            for(int i = 0 ; i < numOfLots ; i++){
                tempLot[i] = lots[i];
            }
            //add the last element to the temp
            tempLot[numOfLots] = Lot(lotId , column, row);
            //delete the connection of the lots to the original, make it point to the temp
            delete[] lots;
            lots = tempLot;

        }

        numOfLots++;

        cout << "Parking lot with ID "<< lotId << " and dimensions (" << row
             << "," << column << ") has been added to the system" <<endl;
    }



}
void ParkingSystem::listLots(){
    if(lots == NULL){
        cout << "There are no lots in the system" << endl;
    }
    else{
        cout << "List of lots:" << endl;
        for(int i = 0 ; i < numOfLots ; i++){
            cout << "ID: " << lots[i].getLotId() << ", Dim: " ;
            lots[i].getDimensions();
            cout << ", number of empty parking spaces: " << lots[i].getEmptyPlaces()<<endl;
        }
    }
}

void ParkingSystem::parkCar(int lotId, string location, string carType, int plateNumber){
    int index = indexOfLot(lotId);
    if(index == -1){
        cout << "Lot " <<  lotId << " is not in the system" << endl;
    }
    else{

        if(!(carType.compare("a") == 0 || carType.compare("b") == 0)) {
            cout << "Invalid car type!" << endl;
            return;
        }

        if(lots[index].getEmptyPlaces() == 0){
            cout << "Parking lot is full" << endl;
            return;
        }

        if(lots[index].findCarRow(plateNumber) != -1 ){
            cout << "Plate number is not unique" << endl;
            return;
        }


        else{
            lots[index].addCar(lotId, location, carType, plateNumber);
        }
    }
}

void ParkingSystem::findCar(int plateNumber){

    int i = 0;
    bool isFound = false;
    string type = "";


    while (!isFound && i < numOfLots){
        if(lots[i].findCarRow(plateNumber) != -1){
            isFound = true;
        }
        else{
            i++;
        }

    }


    if(isFound){
        if(lots[i].getCarType(plateNumber) == 'a'){
            type = "Light-duty car";
        }

        else if(lots[i].getCarType(plateNumber) == 'b'){
            type = "Heavy-duty car";
        }

        cout << type << " with number plate " << plateNumber << " is at location "
             << lots[i].getLocation(plateNumber) << ",lot " << lots[i].getLotId()<< endl;
    }

    else{
        cout << "Car with plate number " << plateNumber << " is not in the system" <<  endl;
    }


}

void ParkingSystem::lotContents(int id){
    int index = indexOfLot(id);

    if(index == -1){
        cout << "Lot with id " << id << "does not exists";
    }

    else{
        cout << "ID: " << id << ", ";
        lots[index].getDimensions();
        cout << ", empty slots: " << lots[index].getEmptyPlaces() << ", parked cars: " ;
        cout << lots[index].parkedCars() << endl;
        cout << endl;
        lots[index].printLot();


    }


}

void ParkingSystem::removeCar(int plateNumber){

    for(int i = 0 ; i < numOfLots ; i++){
        if(lots[i].findCarRow(plateNumber) != -1){

            lots[i].removeCar(plateNumber);

            return;

        }
    }
    cout << "The car with number plate " << plateNumber << " is not in the system" << endl;

}


void ParkingSystem::removeLot(int id){
    int lotIndex = indexOfLot(id);
    if(numOfLots == 0){
        cout << "There is no lots in the system" << endl;
    }

    else if(lotIndex == -1){
        cout << "Lot " << id << " is not in the system" << endl;
    }

    else{
        //remove all the cars in the lot
        lots[lotIndex].emptyLot();

        //create a Lot array pointer which points to an array of size (numOfLots -1)
        Lot* tempLot = new Lot[numOfLots  -1];

        //add all the elements to the temp array until the element we want to delete
        for(int i = 0 ; i < lotIndex ; i++){
            tempLot[i] = lots[i];
        }
        //add all the elements to temp array after the element we want to delete
        for(int i = lotIndex ; i < numOfLots - 1 ; i ++){
            tempLot[i] = lots[i + 1];
        }

        //update the size and make lots point to the new array
        numOfLots--;

        //break off the connection of lots to the original array

        delete[] lots;


        lots = tempLot;

        cout << "Lot " << id  << " has been successfully removed from the system" << endl;

    }


}

//finds the index of the given lot in the array
int ParkingSystem::indexOfLot(int lotId){
    for(int i = 0 ; i < numOfLots ; i++){

        if(lots[i].getLotId() == lotId){
            return i;
        }
    }

    return -1;
}







