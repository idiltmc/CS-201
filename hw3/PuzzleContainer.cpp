/**
 * İdil Atmaca 22002491 CS201 HW3
 * PuzzleContainer class
 */

#include "PuzzleContainer.h"
#include <iostream>
using namespace std;

PuzzleContainer::PuzzleContainer( int h, int w){
    height = h;
    width = w;

    rowLists = NULL;
    rowTail = rowLists;

}
PuzzleContainer::~PuzzleContainer(){
   while(rowLists != NULL){
        removeRow(rowLists->getRowIndex());
   }

}
PuzzleRow* PuzzleContainer::getRow( int index ){

    if(rowLists == NULL){
        return rowLists;
    }

    else{
        PuzzleRow* temp = rowLists;

        while(temp != NULL){
            if(temp->getRowIndex() == index){
                return temp;
            }
            temp = temp->getNext();
        }

        return NULL;
    }
}
bool PuzzleContainer::insertRow( int index ){

    if(index >= height || index < 0){
        return false;
    }

    else{
        PuzzleRow* temp = rowLists;
        PuzzleRow* newRow = new PuzzleRow(width,index);

        if(rowLists == NULL){
            rowLists = newRow;
            rowTail = newRow;
            rowTail->setNext(NULL);
            return true;
        }

        if(rowLists->getRowIndex() > index){
            newRow->setNext(rowLists);
            rowLists = newRow;
            return true;
        }

        if(rowTail->getRowIndex() < index){
            rowTail->setNext(newRow);
            rowTail = newRow;
            rowTail->setNext(NULL);
            return true;
        }

        else{
            while(temp->getNext() != NULL){


                if(temp->getRowIndex() < index && (temp->getNext()->getRowIndex() > index)){
                    PuzzleRow* temp2= temp ->getNext();
                    temp ->setNext(newRow);
                    newRow->setNext(temp2);
                    return true;
                }
                temp = temp->getNext();
            }
        }



        return false;


    }
  

}
bool PuzzleContainer::removeRow( int index ){

    PuzzleRow* del = rowLists;

    if(index >= height || index < 0 ){
        return false;
    }

    if(rowLists == NULL){
        cout << "CONTAINER NULL" << endl;
        return false;
    }

    if(rowLists->getRowIndex() == index){
        rowLists = rowLists->getNext();

        del->setNext(NULL);
        delete del;
        del = NULL;
        return true;
    }

    else{
        PuzzleRow* temp = rowLists;

        while(temp->getNext() != NULL){

            if(temp->getNext() == rowTail){
                del = temp->getNext();
                rowTail = temp;
                rowTail->setNext(NULL);
                del->setNext(NULL);
                delete del;
                del = NULL;
                return true;
            }

            if(temp->getNext()->getRowIndex() == index){
                del = temp->getNext();
                temp->setNext(temp->getNext()->getNext());
                del->setNext(NULL);
                delete del;
                del = NULL;
                return true;
            }
            temp = temp->getNext();
        }

    }
    return false;
  

}
bool PuzzleContainer::addPiece( int row, int col , char shape ){
    row = row - 1;
    col = col -1;
    bool emptyF = false;


    if(row >= height || col >= width || row < 0 || width < 0){
        cout << "(" << row + 1 << "," << col + 1 << ")" << " is out of frame, it cannot be added" << endl;
        return false;
    }

    PuzzleRow* temp = getRow(row);


    if(temp == NULL) {

        (insertRow(row));
        temp = getRow(row);
        emptyF = true;
    }

    if(!canBePlaced(row,col,shape)){
        cout << "Shape doesn't fit into " << "(" << row  + 1 << "," << col + 1 << ")" << ", it cannot be added" << endl;
        if(emptyF){
            removeRow(row);
        }
        return false;
    }


    return temp->insert(col,shape);


}
bool PuzzleContainer::removePiece(int row, int col){
    row = row - 1;
    col = col -1;

    if(row < 0 || col < 0 || row >= height || col >= width){
        cout << "(" << row + 1 << "," << col + 1 << ")" << " is out of frame, it cannot be shown" << endl;
        return false;
    }


    if(getRow(row) == NULL){
        cout << "There is no piece on " <<  "(" << row + 1<< "," << col + 1 << ")" << ", it cannot be removed" << endl;
        return false;
    }

    if(getRow(row)->remove(col)){
        cout << "The piece on "  << "(" << row + 1 << "," << col + 1 << ") " <<  " is removed" << endl;
        return true;
    }


    return false;
    
}
int PuzzleContainer::getHeight(){
    return height;
}
int PuzzleContainer::getWidth(){
    return width;

}
void PuzzleContainer::showPiece(int row, int col){
    row = row - 1;
    col = col -1;
    bool found = false;
    PuzzleRow* temp = rowLists;

    if(row >= height || col >= width || row < 0 || col < 0){
        cout << "(" << row + 1 << "," << col + 1 << ")" << " is out of frame, it cannot be shown" << endl;
    }
    else{

        while(temp != NULL && !found){
            if(temp->getRowIndex() == row){
                found = true;
            }
            else{
                temp = temp->getNext();
            }
        }

        if(!found){
            cout << "There is no piece on " <<  "(" << row + 1 << "," << col + 1 << ")" << ", it cannot be shown" << endl;
        }
        else{
            if(temp->getPiece(col) == 255){
                cout << "There is no piece on " <<  "(" << row + 1 << "," << col + 1 << ")" << ", it cannot be shown" << endl;
            }
            else{

                unsigned char shape = temp->getPiece(col);
                cout << "Piece on "<<  "(" << row + 1 << "," << col + 1 << ")" <<  " as following: " << endl;
                printPiece(shape);

            }
        }


    }

}

void PuzzleContainer::printPiece(unsigned char shape){
    int down,up,right,left;
    shapeConverter(shape, down,up,right,left);
    cout << "Down: " << binaryToString(down) << endl;
    cout << "Up: " << binaryToString(up) << endl;
    cout << "Right: " << binaryToString(right) << endl;
    cout << "Left: " << binaryToString(left) << endl;


}


string PuzzleContainer::binaryToString(int a){
    if(a == 0){
        return "Hole";
    }
    if(a == 1){
        return "Knob";
    }
    if(a == 2){
        return "Border";
    }
    return " ";
}
bool PuzzleContainer::canBePlaced(int row, int col, unsigned char shape){

    int down, up,right,left;
    unsigned char sU;
    unsigned char sD;
    bool emptyF = false;
    shapeConverter(shape,down,up,right,left);

    if(getRow(row) == NULL){
        emptyF = true;
        insertRow(row);
    }

    if(!getRow(row)->canBePlaced(col,shape)){
        return false;
    }

        PuzzleRow* temp = rowLists;

        if(col == 0){
            if(up != 2){
                if(emptyF){
                    removeRow(row);
                }
                return false;
            }

        }
        if(col == height -1){
            if(down != 2){
                if(emptyF){
                    removeRow(row);
                }
                return false;
            }
        }

        else{
            while(temp != NULL){

                //check the up part of the piece
                if(temp->getRowIndex() == row -1){
                    sU = temp->getPiece(col);

                    if(!isComplemantary((sU % 4 ), up)){
                        if(sU != 255){
                            if(emptyF){
                                removeRow(row);
                            }
                            return false;
                        }

                    }
                }

                //check the down part of the piece
                if(temp->getRowIndex() == row + 1){
                    sD = temp->getPiece(col);
                    if(!isComplemantary(((sD / 4) % 4), down)){
                        if(sD != 255){
                            if(emptyF){
                                removeRow(row);
                            }
                            return false;
                        }

                    }
                }

                temp = temp->getNext();
            }


        }



    return true;



}

bool PuzzleContainer::isComplemantary(int s1, int s2){
    if(s1 == 0 && s2 == 1){
        return true;
    }

    if(s1 == 1 && s2 == 0){
        return true;
    }

    return false;
}


void PuzzleContainer::displayContainer(){

    cout << "Container " << height  << "x" << width << ":" << endl;

    cout << "  ";

    for(int i = 1 ; i <= width ; i++){
        cout << i << " ";
    }
    cout << endl;


    for(int i = 0 ; i < height ; i++){
        cout << i + 1 << " ";
        PuzzleRow* r = getRow(i);
        if(r != NULL){
            r->printRow();
        }
        else{
            for(int i = 0 ; i < width ; i++)
                cout << "O ";
        }
        cout << endl;
    }

}
void PuzzleContainer::showColumn(int col){
    col = col-1;

    if(col < 0 || col >= width){
        cout << "Column " << col + 1 << " is out of border" << endl;
    }

    else{
        cout << "Column " << col + 1 << ":" << endl;
        PuzzleRow* temp = rowLists;
        if(temp == NULL){
            for(int i = 0 ; i < height ; i++){
                cout << "O " << endl;
            }
        }
        else{

            for(int i = 0 ; i < height; i++){

                if(temp == NULL){
                    cout << "O" << endl;
                }

                else{
                    if(temp->getRowIndex()== i){
                        if(temp->getPiece(col) == 255){
                            cout << "O " << endl;
                        }
                        else{
                            cout << "X " << endl;
                        }
                        temp = temp->getNext();
                    }
                    else{
                        cout << "O " << endl;
                    }
                }
        }

        }
    }




}
void PuzzleContainer::showRow(int row){
    row = row - 1;

    if(row < 0 || row >= height){
        cout << "Row " << row + 1<< " is out of border" << endl;
    }

    else{
        PuzzleRow* r = getRow(row);
        cout << "Row " << row + 1 << ":" << endl;
        if(r != NULL){
            r->printRow();
        }
        else{
            for(int i = 0 ; i < width ; i++)
                cout << "O ";
        }
    }


}
void PuzzleContainer::findPiece(char shape){
    PuzzleRow* temp = rowLists;
    int col;
    bool found = false;
    bool first = true;

    while(temp != NULL){
        col = temp->findPiece(shape);
        if(col != -1 ){
            found = true;
            if(first){
                cout << "(" << temp->getRowIndex() + 1 << "," << col + 1 << ")";
                first = false;
            }
            else{
                cout << ",(" << temp->getRowIndex() + 1 << "," << col + 1 << ")";
            }

        }
        temp = temp->getNext();
    }

    if(found){
        cout << " contain the piece that has shape" << endl;
        printPiece(shape);
    }
    else{
        cout << "There is no piece that has shape" << endl;
        printPiece(shape);
    }
    


}