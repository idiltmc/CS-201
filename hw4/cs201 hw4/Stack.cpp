
#include <iostream>
#include "Stack.h"
using namespace std;


Stack::Stack(){
    stackTop = NULL;
    num = 0 ;
}
Stack::Stack(const Stack& orig){

    if(num == 0){
        stackTop = NULL;
    }
    else{

        //creating the first node
        stackTop = new StackNode;
        stackTop->item = orig.stackTop->item;

        StackNode* newItem = stackTop;

        for (StackNode *origPtr = orig.stackTop->nextNode;
             origPtr != NULL;
             origPtr = origPtr->nextNode){
            newItem->nextNode = new StackNode;
            newItem = newItem->nextNode;
            newItem->item = origPtr->item;
        }
        newItem->nextNode = NULL;
    }


}
Stack::~Stack(){

    //while(!isEmpty()){
      //  pop();
    //}

}

bool Stack::isEmpty() const{
    //cout << "empty mi " << (stackTop->item) << endl ;
    return stackTop == NULL;

}
bool Stack::push(double newItem){
    StackNode* newNode = new StackNode;
    newNode->item = newItem;

    newNode->nextNode=stackTop;
    stackTop=newNode;

    num++;

    return true;

}
bool Stack::pop(){

    if(isEmpty()){
        return false;
    }

    StackNode* top = stackTop;
    stackTop = stackTop->nextNode;

    top->nextNode = NULL;
    num--;
    delete top;
    return true;

}


bool Stack::pop(double& top){
    if(isEmpty()){
        return false;
    }

    top = stackTop->item;
    StackNode* temp = stackTop;
    stackTop = stackTop->nextNode;

    temp->nextNode = NULL;
    num--;
    delete temp;
    return true;

}

bool Stack::getTop(double& top) const{

    if(isEmpty()){
        return false;
    }

    top = stackTop->item;
    return true;

}

int Stack::getNum(){
    return num;
}




