#include <iostream>
#include <cctype>
#include <cstring>
#include <stack>
#include <stdlib.h>
#include <cmath>
using namespace std;

// Define the structure of a node in the stack
struct Node {
    char data;  // Stores a character (operator or parenthesis)
    Node* next; // Points to the next node
};

// Implement a stack using a linked list
class Stack {
private:
    Node* top; // Points to the top of the stack
    int size;
public:
    Stack() { top = nullptr; size = 0; } // Initialize the stack

    // Push operation: Add an element to the stack
    void push(char ch) {
        Node* newNode = new Node();  // Create a new node
        newNode->data = ch;   // Store the data
        newNode->next = nullptr;  // Initially points to null
        if (top == nullptr) {  // If the linked list is empty
            top = newNode;  // Set the new node as the top
        } else {
            Node* nowNode = top;  // Traverse the linked list to find the last node
            while (nowNode->next != nullptr) {
                nowNode = nowNode->next;
            }
            nowNode->next = newNode; // Add the new node
        }
        size++; // Increment the size
    }

    // Pop operation: Remove and return the top element
    char pop() {
        if (isEmpty()) { // Error: The linked list is empty
            cout << "Linked List is empty" << endl;
            return '\0';
        }
        Node* nowNode = top, *deledNode; // Find the node before the target node
        if (size != 1) { // If there are multiple nodes
            for (int i = 0; i < (size - 2); i++) {  // Traverse the linked list
                nowNode = nowNode->next;
            }
            deledNode = nowNode->next; // Find the target node
            nowNode->next = nullptr; // Disconnect the node
        } else { // If there is only one node
            deledNode = top; // Find the target node
            top = nullptr; // Disconnect the node
        }
        char ans = deledNode->data; // Retrieve the data
        delete deledNode; // Delete the node
        size--; // Decrement the size
        return ans;
    }

    // Peek operation: Get the top element without removing it
    char peek() {
        if (isEmpty()) { // Error: The linked list is empty
            cout << "Linked List is empty" << endl;
            return '\0';
        }
        Node* nowNode = top; // Find the target node
        for (int i = 0; i < size - 1; i++) {
            nowNode = nowNode->next;
        }
        return nowNode->data; // Return the data
    }

    // Check if the stack is empty
    bool isEmpty() {
        return (size == 0);
    }
};

// Determine the precedence of operators (+, -, *, /, %, ^)
int precedence(char op) {
    if ((op >= '0' && op <= '9') || (op >= 'A' && op <= 'Z') || op == '.') {  // Numbers have the lowest precedence, identified by ASCII
        return 5;
    } else if (op == '(') { // Left parenthesis has the second lowest precedence
        return 4;
    } else if (op == '+' || op == '-') { // Addition and subtraction have the third lowest precedence
        return 3;
    } else if (op == '*' || op == '/' || op == '%') { // Multiplication, division, and modulus have the fourth lowest precedence
        return 2;
    } else if (op == '^') { // Exponentiation has the highest precedence
        return 1;
    } else if (op == ')') { // Right parenthesis has the highest precedence
        return 0;
    } else { // Invalid symbol
        return -1;
    }
}

// Convert an infix expression to a postfix expression
void InfixToPostfix(const char* infix, char* postfix) {
    Stack stack;
    char back;
    int infixIndex = 0, postIndex = 0;
    while (infix[infixIndex] != '\0') {
        switch (precedence(infix[infixIndex])) {
            case 5: // General numbers, use spaces to distinguish different numbers
                postfix[postIndex++] = ' ';
                while (precedence(infix[infixIndex]) == 5) {
                    postfix[postIndex++] = infix[infixIndex++];
                }
                postfix[postIndex++] = ' ';
                infixIndex--;
                break;
            case 4: // Left parenthesis '('
                stack.push(infix[infixIndex]);
                break;
            case 3: // Addition and subtraction '+' '-'
                while (!stack.isEmpty()) { 
                    back = stack.peek();  // Get the top element
                    if (precedence(back) <= 3) { // If the precedence is higher, pop it
                        postfix[postIndex++] = stack.pop();
                    } else break; // Otherwise, stop checking precedence
                }
                stack.push(infix[infixIndex]); // Push the current operator
                break;
            case 2: // Multiplication, division, and modulus '*' '/' '%'
                while (!stack.isEmpty()) { 
                    back = stack.peek();  // Get the top element
                    if (precedence(back) <= 2) { // If the precedence is higher, pop it
                        postfix[postIndex++] = stack.pop();
                    } else break; // Otherwise, stop checking precedence
                }
                stack.push(infix[infixIndex]); // Push the current operator
                break;
            case 1:  // Exponentiation '^'
                // Handle right-associativity by checking if the top of the stack is also '^'
                while (!stack.isEmpty() && precedence(stack.peek()) == 1) {
                    postfix[postIndex++] = stack.pop();
                }
                stack.push(infix[infixIndex]);
                break;
            case 0: // Right parenthesis ')'
                back = stack.pop();
                while (precedence(back) != 4) { // Pop until a left parenthesis (4) is found
                    postfix[postIndex++] = back;
                    back = stack.pop();
                }
                break;
            default:
                break;
        }
        infixIndex++; // Process the next character
    }
    while (!stack.isEmpty()) { // After processing, pop all remaining elements
        char back = stack.pop();
        postfix[postIndex++] = back;
    }
    postfix[postIndex++] = '\0'; // Add null terminator
}

// Evaluate a postfix expression
double calculator(char* postfix) {
    stack<double> NumStack;
    int index = 0;
    while (postfix[index] != '\0') {
        if (postfix[index] == ' ') { // Skip spaces
            index++;
            continue;
        }
        if (precedence(postfix[index]) == 5) { // If it's a number, convert it to double and push it onto the stack
            char tmp[10]; int t_index = 0;
            while (precedence(postfix[index]) == 5) tmp[t_index++] = postfix[index++]; // Read multi-digit numbers
            tmp[t_index++] = '\0'; // Add null terminator
            double num = atof(tmp);
            NumStack.push(num);
        } else {
            double Num1 = NumStack.top(); // Retrieve the top number from the stack
            NumStack.pop();
            double Num2 = NumStack.top(); // Retrieve the second number from the stack
            NumStack.pop();
            switch (postfix[index]) { // Perform calculation based on the operator
                case '+': NumStack.push(Num2 + Num1); break;
                case '-': NumStack.push(Num2 - Num1); break;
                case '*': NumStack.push(Num2 * Num1); break;
                case '/': NumStack.push(Num2 / Num1); break;
                case '%': NumStack.push((int)Num2 % (int)Num1); break; // Modulus
                case '^': NumStack.push(pow(Num2, Num1)); break; // Exponentiation
                default: break;
            }
        }
        index++;
    }
    return NumStack.top();
}

int main() {
    char infix[100], postfix[100];
    cout << "Enter an Infix expression: ";
    cin.getline(infix, 100); // Input infix expression

    InfixToPostfix(infix, postfix); // Convert to postfix expression
    cout << "Postfix expression: " << postfix << endl; // Output postfix expression
    cout << "ans:" << calculator(postfix) << endl; // Output the result
    return 0;
}