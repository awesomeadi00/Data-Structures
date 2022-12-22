#include<iostream>
#include<string>
#include<exception>
#include<math.h>
#include<ctype.h>
using namespace std;

bool isOperator(char); //Function which checks if the input char is an operator
bool isleq(char, char); //Compares two operators, returns True if Op1 is <= Op2.
int convertOpToInt (char); //Function which converts operators into int so their precdence can be compared
string infix2postfix(string);   //Function which converts an infix notaiton into a postfix notation.
float evaluate(string postfix);     //Function which will evaluate a PostfixExpression and return the result
bool isBalanced(string expression); // Funciton which will check for balanced parentheses

//===============================================CSTACK CLASS=====================================================
//Class CStack which structures the Stack through the implementation of the Singly Linked List
template <typename E>
class CStack {
    enum {DEF_CAPACITY = 100};
private:
    E *A; //String pointer 'A' which points to an array of strings.
    int capacity; //Stack's maximum capacity (DEF_CAPACITY)
    int t; //Index at the top of the stack.
    
public:
    CStack(int cap = DEF_CAPACITY);
    int size() const;
    bool empty() const;
    void push(const E& e);
    void pop();
    const E& top() const;
};

//Constructor: Creates an array with cap size, capacity has a value of cap and the top is empty.
template <typename E> CStack<E>::CStack(int cap) : A(new E[cap]), capacity(cap), t(-1) {}

//Size function: Returns the number of elements in the stack.
template <typename E> int CStack<E>::size() const {return t+1; }

//Empty function: Returns true if the stack is empty.
template <typename E> bool CStack<E>::empty() const {return(t < 0); }

//Top function: Returns the top element of the stack.
template <typename E> const E& CStack<E>::top() const{
    if(empty()) {throw runtime_error("Pop from Empty Stack"); }
    return A[t];
}

//Push function: Adds an element onto the top of the stack.
template <typename E> void CStack<E>::push(const E& e) {
    if(size() == capacity) {throw runtime_error("Stack is full"); }
    A[++t] = e;
}

//Pop function: Removes an element from the top of the stack.
template <typename E> void CStack<E>::pop() {
    if(empty()) {throw runtime_error("Pop from Empty Stack"); }
    --t;
}

//===============================================MAIN FUNCTION===================================================
int main() {
    
    while(true) {
        string infix; //Infix expression

        cout << "Enter an Infix Expression: ";
        cin >> infix;
        
        try {
            if(infix == "exit")
                break;
            
            else if(!isBalanced(infix)) {
                cout << "Expression is not Balanced!" << endl;
                cout << endl;
                continue;
            }


            string postfix = infix2postfix(infix);  //Postfix Expression
            
            cout << "The Postfix Form is: " << postfix << endl;
            float ans = evaluate(postfix);          //Evaluate the postfix Expresion
            cout << infix << " = " << ans << endl;        //Print the final answer
            cout << endl;
        }

        catch(exception &e) {
            cout << "Exception: "<< e.what() << endl;
        }
    }
    return EXIT_SUCCESS;
}

//=================================================FUNCTIONS=====================================================
//Function which checks if the input char is an operator.
bool isOperator(char ch) {
    if( ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        return true;
    else
        return false;
}

//============================
//Function which converts operators into int so their precdence can be compared
int convertOpToInt (char ch) {
    if (ch=='+' || ch=='-') {return 1; }
    if (ch=='*' || ch=='/') {return 2; }
    if (ch=='^') {return 3; }
    return 0;
}

//============================
//Helper Function which compare two operators and returns "True" if first operator has less or equal predence than the right operator
bool isleq(char opA, char opB) {
    return (convertOpToInt(opA) <= convertOpToInt(opB));
}

//============================
//Function which will check for balanced parentheses
bool isBalanced(string expression) {

    CStack<char> stq; //Created empty stack (stq)
    int len(0);
    
    //For loop to receive the total number of characters inside the expression.
    for(int l = 0; expression[l] != '\0'; l++) {
        len++;
    }
    
    //For loop to cycle through the expression to see if it is balanced.
    for (int i = 0; i < len; i++) {
        if(isdigit(expression[i])) { //If there is a digit, it will continue the loop.
            continue;
        }
        
        else if(isOperator(expression[i])) { //If there is an operator, it will continue the loop.
            continue;
        }
        
        else if(expression[i] == '(') { //If there is a '(', push it into the stack.
            stq.push(expression[i]);
            //If there is a '()' in the expression, it is considered invalid and therefore unbalanced.
            if(expression[i+1] == ')') {
                return false;
            }
        }
        
        //If there is a ')', it will check if the stack has '(' inside. If it does, then it will push it into the stack. Otherwise, it is an unbalanced expression, hence it will return false.
        else if(expression[i] == ')') {
            if(stq.top() == '(') {
                stq.push(expression[i]);
            }
            
            else
                return false;
        }
    }
    
    //It checks if there is a ')' at the top of the stack (implying a valid expression), then it returns true. Otherwise, it is a false expression.
    if(stq.top() == ')') {
        return true;
    }
    
    else
        return false;
    
    return true; //Return true by default
}

//============================
//Function which converts an Infix Notaiton to a Postfix notation
string infix2postfix(string infix) {

    CStack<char> stq; //Creates an empty stack (stq).
    string postfix = ""; //Creates a postfix expression which is initially empty.
    
    //Step 1: Push '(' into the stack and add ')' to the end of the infix expression.
    stq.push('(');
    infix += ")";
    
    //Step 2: For loop to scan through the infix expression to form the postfix expression.
    for(int i = 0; i < infix.length(); i++) {
        if(isdigit(infix[i])) { //Step 3: If an operand is found, add it to postfix.
            postfix += infix[i];
        }
        
        else if(infix[i] == '(') { //Step 4: If a '(' is found, push it into the stack.
            stq.push(infix[i]);
        }
        
        //Step 5: If an operator is found:
        else if(isOperator(infix[i])) {
            //It checks if the top of the stack is an operator. If so, check if it has higher prescendence than the one currently found. If it does, then it repeatedly pops the operators from the stack and adds it to postfix until '(' is found.
            if(isOperator(stq.top())) {
                if(isleq(infix[i], stq.top())) {
                    while(stq.top() != '(') {
                        postfix += stq.top();
                        stq.pop();
                    }
                    stq.push(infix[i]); //When everything is popped, we add the operator found in the stack.
                }
            }
            
            //If there is no operator at the top of the stack, then it simply pushes it onto the stack.
            else if(stq.top() == '(') {
                stq.push(infix[i]);
            }
        }
        
        //Step 6: If an ')' is found, then it pops all the operators from the top and adds it to postfix until '(' is found.
        else if(infix[i] == ')') {
            while(stq.top() != '(') {
                postfix += stq.top();
                stq.pop();
            }
            stq.pop(); //Pops the '('
        }
    }
    return(postfix); //Returns the final postfix expression.
}

//============================
//Function which will evaluate a PostfixExpression and return the result
float evaluate(string postfix) {
    
    CStack<char> stq; //Step 1: Create a stack to store all of the operands for calaculations.
        
    //Step 2: For loop to scan the entire postfix function:
    float x, y, z;
    for(int i = 0; i < postfix.length(); i++) {
        //Part a) If an operand is found, pushes it into the stack and converts char ASCII value to numeric float.
        if(isdigit(postfix[i])) {
            postfix[i] = (float)postfix[i] - 48;
            stq.push(postfix[i]);
        }
        
        //Part b) If an operator is found, pop the 2 elements from the stack and execute the operation on them and return them back into the stack.
        else if(isOperator(postfix[i])) {
            y = stq.top();
            stq.pop();
            
            x = stq.top();
            stq.pop();
            
            if(postfix[i] == '+') { //If the operator is a +, execute addition.
                z = x + y;
                stq.push(z);
            }
            
            else if(postfix[i] == '-') { //If the operator is a -, execute subtraction.
                z = x - y;
                stq.push(z);
            }
            
            else if(postfix[i] == '*') { //If the operator is a *, execute multiplication.
                z = x * y;
                stq.push(z);
            }
            
            else if(postfix[i] == '/') { //If the operator is a /, execute division.
                z = x / y;
                stq.push(z);
            }
            
            else if(postfix[i] == '^') { //If the operator is a ^, execute power(x^y)
                z = pow(x, y);
                stq.push(z);
            }
        }
    }
    
    return(stq.top()); //Returns the final operated value which is at the top of the stack.
}
