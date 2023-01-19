//
// Created by user on 5/13/2022.
//


#include <iostream>
#include "cStack.h"
using namespace std;


cStack::cStack(){
    cstackTop = NULL;
    cnum = 0 ;
}
cStack::cStack(const cStack& orig){

    if(orig.isEmpty()){
        cstackTop = NULL;
    }
    else{

        //creating the first node
        cstackTop = new cStackNode;
        cstackTop->citem = orig.cstackTop->citem;

        cStackNode* newItem = cstackTop;

        for (cStackNode *origPtr = orig.cstackTop->cnextNode;
             origPtr != NULL;
             origPtr = origPtr->cnextNode){
            newItem->cnextNode = new cStackNode;
            newItem = newItem->cnextNode;
            newItem->citem = origPtr->citem;
        }
        newItem->cnextNode = NULL;
    }


}
cStack::~cStack(){

    while(!isEmpty()){
        pop();
    }

}

bool cStack::isEmpty() const{
    return cnum==0;

}
bool cStack::push(char newItem){
    cStackNode* newNode = new cStackNode;
    newNode->citem = newItem;

    if(isEmpty()){
        cstackTop = newNode;
    }
    else{
        newNode->cnextNode = cstackTop;
        cstackTop = newNode;
    }

    cnum++;

    return true;

}
bool cStack::pop(){

    if(isEmpty()){
        return false;
    }

    cStackNode* top = cstackTop;
    cstackTop = cstackTop->cnextNode;

    top->cnextNode = NULL;
    cnum--;
    delete top;
    return true;

}
bool cStack::pop(char& top){
    if(isEmpty()){
        return false;
    }
    top = cstackTop->citem;
    cStackNode* temp = cstackTop;
    cstackTop = cstackTop->cnextNode;

    temp->cnextNode = NULL;
    cnum--;
    delete temp;
    return true;

}

bool cStack::getTop(char& top) const{

    if(isEmpty()){
        return false;
    }

    top = cstackTop->citem;
    return true;

}

int cStack::getNum(){
    return cnum;
}





