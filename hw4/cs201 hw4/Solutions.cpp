
#include <iostream>
#include "Solutions.h"
using namespace std;



void fantabulous(string list, int length){

    Stack s;
    convertToStack(list,s,length);
    cout << "number of fantabulous subs: " << subs(s) << endl;

    while(!s.isEmpty()){
        s.pop();
    }


}

//create every subarray of the stack and check whether it is fantabolus or not
int subs(Stack& s){


    double top;
    double subTop;
    Stack subs;
    Stack second;
    Stack restore;
    Stack& fanSubs = subs;
    double secondTop;
    int fan = 0;

    //reverse the stack (we want to start creating the stacks from the first element)
    while(!s.isEmpty()){
        s.pop(top);
        second.push(top);
        //cout << "s top: " << top << endl;
    }


    while(!second.isEmpty()){
        double t;

        //starting point
        second.getTop(t);


        while(!second.isEmpty()){
            second.pop(secondTop);
            restore.push(secondTop); //this is for using the stack second again
            subs.push(secondTop); //add the item into the subarray
            double subtop;
            subs.getTop(subTop);

            //check whether the current sub stack is fantabulous, incremenet the number of fantabulous sub arrays
            if(isFantabulous(subs)){
                fan++;
            }

        }

        //put every value back to stack second
        while(!restore.isEmpty()){
            double rP;
            restore.pop(rP);
            second.push(rP);
        }


        //reset the subs
        while(!subs.isEmpty()){
            subs.pop();
        }
        //take out the top element of second which is the first element for Stack s
        second.pop();
    }

    return fan;

}

//convert the given string to a stack
void convertToStack(string list,Stack& s,int length){

    Stack nums;
    list =  list + ")";
    int i = 0;
    int len = list.length();
    int numIndex = 0;


    while(list[i] != ')' && numIndex < length){


        if(list[i] != ','){


            int num = list[i] - '0';


            //this step is for numbers with multiple decimal numbers
            while(i != len -1 && (list[i+1] != ',' && list[i+1] != ')' )){
                num = num*10 + (list[i+1]-'0');
                i++;
            }

            nums.push(num);
            numIndex++;
        }
        i++;
    }
    s = nums;

}
//checks if the given stack is fantabulous or not
bool isFantabulous(Stack& nums){
    Stack nums2;
    Stack restore;
    int largest = 0;
    int largestLeft = 0;
    int largestRight = 0;

    if(nums.getNum() < 2){
        return false;
    }

    double top = 0;
    while(!nums.isEmpty()){

        nums.pop(top);
        restore.push(top); //this is for returning to same nums stack after we are finished determining

        //if the current value is largest, ex largest value is now the at right to current value
        //keep the largestRight value for comparing with largestLeft
        if(top > largest){
            largestRight = largest;
            largest = top;
        }

        nums2.push(top);
    }


    double top2;
    nums2.pop(top2);


    //bring out everything from the stack until we reach the largest value
    //in this way, we will evaluate the left part
    //find the largestLeft
    while((!nums2.isEmpty()) && top2 != largest){
        if(top2 > largestLeft){
            largestLeft = top2;
        }
        nums2.pop(top2);
    }
    double rTop;

    while(!restore.isEmpty()){
        restore.pop(rTop);
        nums.push(rTop);
    }

    //if the largest value of the left part is larger than the largest part, this stack will be fantabolus
    if(largestLeft > largestRight){
        return true;

    }
    return false;

}

void subset(string intervals, int length){
    Stack s;
    convertToStack(intervals,s,length);
    double top;

    Stack orig;

    //reverse the order of the stack
    while(!s.isEmpty()){
        s.pop(top);
        orig.push(top);
    }

    Stack interval;
    double rTop;

    //push the first 2 values into interval stack
    orig.pop(rTop);
    interval.push(rTop);
    orig.pop(rTop);
    interval.push(rTop);

    while(!orig.isEmpty()){

        orig.getTop(rTop);

        double interTop;
        double interTop0;
        //get the top 2 values from interval stack
        interval.pop(interTop);
        interval.getTop(interTop0);

        //if the current value is between top2 values from the interval
        if(rTop <= interTop && rTop >= interTop0){
            orig.pop();
            orig.pop(rTop);

            //current values' next is more than intervals top
            //replace current values next with intervals' top
            if(rTop > interTop){
                interval.push(rTop);
            }
            else{
                interval.push(interTop);
            }
        }

        else{
            //put the interval to stack
            interval.push(interTop);
            interval.push(rTop);
            orig.pop();
            orig.pop(rTop);
            interval.push(rTop);
        }
    }

    Stack c;
    //reverse the order
    while(!interval.isEmpty()){
        double item;
        interval.pop(item);
        c.push(item);
    }

    bool isFirst = true;


    //print out the found subsets
    cout << "Joined subset: ";
    while(!c.isEmpty()){

        if(!isFirst) {
            cout << ", ";
        }
        double item;
        c.pop(item);
        cout << "(" << item << ":";
        c.pop(item);
        cout << item << ")";
        isFirst = false;

    }
    cout << endl;






}

string infix2prefix(string expression){
    string f = expression;

    expression = reverseExpression(expression);
    string preExpression = "";
    cStack items;

    for(int i = 0 ; i < expression.length() ; i++){

        if(isDigit(expression[i])){
            preExpression = preExpression + expression[i];
        }

        else if(expression[i] == ')'){
            items.push(')');
        }

        else if(expression[i] == '('){
            char top;
            items.pop(top);
            while (top != ')') {
                preExpression = preExpression + top;
                items.pop(top);
            }
        }

        else if(isOperation(expression[i])){

            char op1 = expression[i];
            char top;
            items.getTop(top);

            if(priority(op1) > priority(top)){
                items.push(op1);
            }

            else{
                while(isOperation(top) && !(items.isEmpty()) && priority(top) > priority(op1)){
                    items.pop(top);
                    preExpression = preExpression + top;
                }
                items.push((op1));
            }
        }
    }

    char top2;


    while (!(items.isEmpty())){

        items.pop(top2);

        preExpression = preExpression + top2;

    }

    string res = reverseExpression(preExpression);

    cout << "Result of " << f << " is: ";
    return res;

}

string reverseExpression(string expression){
    int length = expression.length();
    char curC;


    for(int i = 0 ; i < expression.length() && i < length / 2; i++){

        curC = expression[i];
        char curL = expression[length-1-i];
        expression[i] = curL;
        expression[length-i-1] = curC;
    }
    return expression;

}

int priority(char op){

    if(op == '*' || op == '/'){
        return 2;
    }
    else if(op == '-' || op == '+') {
        return 1;
    }

    return 0;

}
void evaluatePrefix(string expression){

    Stack stack;
    double res;
    char newItem;
    for(int i = expression.length() - 1 ; i >= 0 ; i--){
        newItem = expression[i];
            if(isDigit(newItem)){
                stack.push(newItem-'0');
            }

            else if(isOperation(newItem)){
                double top1;
                double top2;

                stack.pop(top1);
                stack.pop(top2);

                if(newItem == '*'){
                    res = ((top1) * (top2));
                }

                if(newItem == '/'){
                    res =  ((double)(top1) / (top2));

                }
                if(newItem == '+'){
                    res = (top1) + (top2);

                }
                if(newItem == '-'){
                    res =  ((top1) - (top2));

                }

                stack.push(res);
            }


    }


    cout << "Result of " << expression << " is: "<< res << endl;



}



bool isOperation(char op){
    return ((op == '*') || (op == '-') ||(op == '+') ||(op == '/' ));
}

bool isDigit(char op){
    return ((op == '0' )||(op == '1') || (op == '2') ||(op == '3') ||(op == '4' )||
    (op == '5') || (op == '6') ||(op == '7') ||(op == '8' )||(op == '9' ));
}