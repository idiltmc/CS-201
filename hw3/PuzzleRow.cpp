/**
 * İdil Atmaca 22002491 CS201 HW3
 * PuzzleRow class
 */
#include "PuzzleContainer.h"
#include <iostream>
using namespace std;


PuzzleRow::PuzzleRow( int size, int rowindex){

    this->maxSize = size;
    this-> rowindex = rowindex;
    puzzleHead = NULL;
    puzNum = 0;
    puzzleTail = NULL;
    rowNext = NULL;

}
PuzzleRow::~PuzzleRow(){
    PuzzlePiece* temp = puzzleHead;

    while (!isEmpty()){
        remove(puzzleHead->colindex);
    }

}
int PuzzleRow::getRowIndex(){
    return rowindex;
}

void PuzzleRow::setNext( PuzzleRow* next ){

    rowNext = next;
}
PuzzleRow* PuzzleRow:: getNext(){
    return rowNext;
}


bool PuzzleRow::insert( int index, char shape ){

    PuzzlePiece* temp = puzzleHead;
    PuzzlePiece* newPiece = new PuzzlePiece;


    newPiece->shape = shape;
    newPiece->rowindex = rowindex;
    newPiece->colindex = index;


    if(puzzleHead == NULL){
        puzzleHead = newPiece;
        puzzleTail = newPiece;
        newPiece->pNext = NULL;
        puzzleTail->pNext = NULL;
        puzNum++;
        cout << "A piece is added to (" << rowindex + 1 << "," << index + 1 << ")" << endl;
        return true;
    }

    if(puzzleHead->colindex == index || puzzleTail->colindex == index){
        cout << "(" << rowindex + 1 << "," << index + 1 << ")" << " has been already occupied, it cannot be added" << endl;
        delete newPiece;
        return false;
    }

    else if(puzzleHead->colindex > index){
        newPiece->pNext = puzzleHead;
        puzzleHead = newPiece;
        cout << "A piece is added to (" << rowindex + 1 << "," << index + 1 << ")" << endl;
        return true;
    }

    else if(puzzleTail->colindex < index){
        puzzleTail->pNext = newPiece;
        puzzleTail = newPiece;
        puzzleTail->pNext = NULL;
        cout << "A piece is added to (" << rowindex + 1 << "," << index + 1 << ")" << endl;
        return true;
    }

    else{

        while(temp->pNext != NULL){
            if(temp->colindex == index){
                cout << "(" << rowindex + 1 << "," << index + 1 << ")" << " has been already occupied, it cannot be added" << endl;
                delete newPiece;
                return false;
            }
            if(temp->colindex < index && temp->pNext->colindex > index){
                PuzzlePiece* temp2=  temp ->pNext;
                temp -> pNext = newPiece;
                newPiece->pNext = temp2;
                puzNum++;
                cout << "A piece is added to (" << rowindex + 1 << "," << index + 1 << ")" << endl;
                return true;
            }

            temp = temp->pNext;
        }

    }
    delete newPiece;
    return false;


    

}
bool PuzzleRow::remove( int index ){

    if(index < 0 || index >= maxSize){
        cout << "(" << rowindex + 1 << "," << index + 1 << ") " << "is out of frame, it cannot be removed" << endl;
        return false;
    }

    if(puzzleHead == NULL){
        cout << "There is no piece on " <<  "(" << rowindex + 1<< "," << index + 1 << ")" << ", it cannot be removed" << endl;;
        return false;
    }

    else{
        PuzzlePiece* temp = puzzleHead;
        PuzzlePiece* del = temp;

        if(temp->colindex == index){
            puzzleHead = temp->pNext;
            del->pNext = NULL;
            delete del;
            del = NULL;
            return true;
        }

        else{


            for(int i = 1 ; i < puzNum ; i++ ){
                if(temp->pNext->colindex == index){
                    del = temp->pNext;
                    temp->pNext = temp->pNext->pNext;
                    del->pNext = NULL;
                    delete del;
                    del = NULL;
                    return true;
                }
                temp = temp->pNext;
            }

            if(temp->pNext->colindex == index){
                del = temp->pNext;
                puzzleTail = temp;
                puzzleTail->pNext = NULL;
                del->pNext = NULL;
                delete del;
                del = NULL;
                return true;
            }


        }

    }
    cout << "There is no piece on " <<  "(" << rowindex + 1<< "," << index + 1 << ")" << ", it cannot be removed" << endl;
    return false;
}
bool PuzzleRow::isEmpty(){
   return puzzleHead == NULL;
}

bool PuzzleRow::canBePlaced(int col, unsigned char shape){

    PuzzlePiece* temp = puzzleHead;
    unsigned char shapeR = (shape / 16) % 4;
    unsigned char shapeL = shape / 64;

    if(isEmpty()){
        if(col != 0 && col != maxSize - 1){
            return true;
        }
        else{
            if(col == maxSize -1 ){
                if( shapeR == 2){
                    return true;
                }
            }

            if(col == 0){
                if(shapeL == 2){
                    return true;
                }
            }
        }
        return false;
    }

    while(temp != NULL){
        if(temp->colindex == col -1 ){

            if(!isComplementary(((temp->shape/ 16) % 4),shapeL)){
                return false;
            }

        }

        if(temp->colindex == col + 1){
            if(!isComplementary((temp->shape/ 64),shapeR)){
                return false;
            }
        }

        temp = temp->pNext;
    }

    return true;


}

bool PuzzleRow::isComplementary(int s1, int s2){
    if(s1 == 0 && s2 == 1){
        return true;
    }

    if(s1 == 1 && s2 == 0){
        return true;
    }

    return false;
}


unsigned char PuzzleRow::getPiece(int index ){

    if(puzzleHead == NULL){
        return 255;
    }

    else{

        PuzzlePiece* temp = puzzleHead;

        while(temp != NULL){
            if(temp->colindex == index){
                return temp->shape;
            }
            temp = temp->pNext;
        }

        return 255;
    }
}

int PuzzleRow::findPiece(char shape){
    PuzzlePiece* temp = puzzleHead;

    while(temp != NULL){
        if(temp->shape == shape){
            return temp->colindex;
        }
        temp = temp->pNext;
    }

    return -1;


}
void PuzzleRow::printRow(){

    if(isEmpty()){
        for(int i = 0 ; i < maxSize ; i++)
                cout << "O ";
    }

    else{


        PuzzlePiece* temp = puzzleHead;

        for(int i = 0 ; i < maxSize && temp != NULL ; i++){
            if(temp->colindex == i){
                cout << "X ";
                temp = temp->pNext;
            }
            else{
                cout << "O ";
            }

        }

        for(int i = puzzleTail->colindex + 1 ; i < maxSize ; i ++){
            cout << "O ";
        }


    }

}