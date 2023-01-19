
#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <iostream>
using namespace std;
#include "Stack.h"
#include "cStack.h"


void fantabulous(string list, int length);
bool isFantabulous(Stack& nums);
void subset(string intervals, int length);
void convertToStack(string list, Stack& s,int length);
int subs(Stack& s);
string infix2prefix(string expression);
void evaluatePrefix(string expression);
bool isOperation(char op);
string reverseExpression(string expression);
int priority(char op);
bool isDigit(char op);

#endif
