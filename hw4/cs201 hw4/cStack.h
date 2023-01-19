//
// Created by user on 5/13/2022.
//

#ifndef HW4_CSTACK_H
#define HW4_CSTACK_H

#endif //HW4_CSTACK_H


#include <iostream>

using namespace std;

class cStack{

public:
    cStack();
    cStack(const cStack& orig);
    ~cStack();

    bool isEmpty() const;
    bool push(char newItem);
    bool pop();
    bool pop(char& top);
    bool getTop(char& top) const;
    int getNum();

private:
    struct cStackNode {
        char citem;
        cStackNode* cnextNode;
    };
    int cnum;

    cStackNode *cstackTop;
};

