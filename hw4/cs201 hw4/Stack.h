//
// Created by user on 5/9/2022.
//

#include <iostream>

using namespace std;

class Stack{

public:
    Stack();
    Stack(const Stack& orig);
    ~Stack();

    bool isEmpty() const;
    bool push(double newItem);
    bool pop();
    bool pop(double& top);
    bool getTop(double& top) const;
    int getNum();

private:
    struct StackNode {
        double item;
        StackNode* nextNode;
    };
    int num;

    StackNode *stackTop;
};
