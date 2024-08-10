// Project 3 Alex Jun (885103481)
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

class Stack {
private:
    std::vector<char> charStack;

public:
    void validPara(const std::string& expression);
    int indexError(const std::string& expression);
    void minPara(const std::string& expression);
    void scorePara(const std::string& expression);
};

void Stack::validPara(const std::string& expression) {
    charStack.clear();

    for (char ch : expression) {
        if (ch == '(' || ch == '[' || ch == '{') {
            charStack.push_back(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (charStack.empty() || !((ch == ')' && charStack.back() == '(') ||
                                        (ch == ']' && charStack.back() == '[') ||
                                        (ch == '}' && charStack.back() == '{'))) {
                std::cout << "Invalid" << std::endl;
                return;
            } else {
                charStack.pop_back();
            }
        }
    }

    if (charStack.empty()) {
        std::cout << "Valid" << std::endl;
    } else {
        std::cout << "Invalid" << std::endl;
    }
}


int Stack::indexError(const std::string& expression) {
    std::stack<int> indexStack;

    for (int i = 0; i < expression.size(); ++i) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            indexStack.push(i);
        } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (indexStack.empty()) {
                return i;
            } else {
                if (expression[i] == ')' && expression[indexStack.top()] == '(' ||
                    expression[i] == ']' && expression[indexStack.top()] == '[' ||
                    expression[i] == '}' && expression[indexStack.top()] == '{') {
                    indexStack.pop();
                } else {
                    return i;  
                }
            }
        }
    }

    return indexStack.empty() ? -1 : indexStack.top(); 
}




void Stack::minPara(const std::string& expression) {
    charStack.clear();
    int count = 0;

    for (char ch : expression) {
        if (ch == '(' || ch == '[' || ch == '{') {
            charStack.push_back(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (charStack.empty() || !((ch == ')' && charStack.back() == '(') ||
                                        (ch == ']' && charStack.back() == '[') ||
                                        (ch == '}' && charStack.back() == '{'))) {
                ++count;
                charStack.pop_back();
            } else {
                charStack.pop_back();
            }
        }
    }

    count += charStack.size();
    if (count > 1)
    {
        count -= 1;
    }

    std::cout << count << std::endl;
}


void Stack::scorePara(const std::string& expression) {
    charStack.clear();
    int count = 0;

    for (char ch : expression) {
        if (ch == '(' || ch == '[' || ch == '{') {
            charStack.push_back(ch);
            ++count;
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (!charStack.empty() &&
                ((ch == ')' && charStack.back() == '(') ||
                 (ch == ']' && charStack.back() == '[') ||
                 (ch == '}' && charStack.back() == '{'))) {
                charStack.pop_back();
            } else {
                --count;
                charStack.pop_back();
            }
        }
    }

    std::cout << count << std::endl;
}

class Queue {
private:
    std::queue<std::string> messageQueue;

public:
    void enqueue(const std::string& message);
    void processMsg();
};

void Queue::enqueue(const std::string& message) {
    std::string reversedChunk;
    for (char ch : message) {
        reversedChunk = ch + reversedChunk;
    }

    messageQueue.push(reversedChunk);
}

void Queue::processMsg() {
    while (!messageQueue.empty()) {
        std::string chunk = messageQueue.front();
        messageQueue.pop();

        std::reverse(chunk.begin(), chunk.end());

        std::cout << chunk;
    }
    std::cout << std::endl;
}

int main(){
Stack s1;
s1.validPara("(([]))");
s1.minPara("(([]))");
s1.scorePara("(([]))");
s1.validPara("(([])");
std::cout<<s1.indexError("(([))")<<std::endl;
s1.minPara("(([])");
s1.validPara("(([{}))");
std::cout<<s1.indexError("(([[}])")<<std::endl;
s1.minPara("(([{}))");
s1.scorePara("(([{}))");
std::cout<<s1.indexError("({}[]()[)")<<std::endl;
s1.validPara("(([))");
s1.minPara("(([))");
std::cout<<s1.indexError("[({)]")<<std::endl;
s1.validPara("(([{[{({})}]}]))");
s1.minPara("(([{[{({})}]}]))");
s1.scorePara("(([{[{({})}]}]))");
s1.validPara("(([[{[{({})}]))");
s1.validPara("(([[{[{({})}]}])]))");
s1.scorePara("(([[{[{({})}]}])]))");
std::cout<<s1.indexError("(([[{{({})]}])]))")<<std::endl;
s1.validPara("(())");
s1.validPara("(())");
s1.validPara("void function(){}");
s1.scorePara("void function(){}");
s1.validPara("void function(");
s1.minPara("void function(");
s1.validPara("void function(std::string expre){if(expre){return 1;}else{return 0;}}");
s1.scorePara("void function(std::string expre){if(expre){return 1;}else{return 0;}}");
s1.validPara("void function(std::string expre){if(expre){return 1;}else{return 0;}");
s1.validPara("void function(std::string expre){if(expre){return 1;else{return 0;");
s1.minPara("void function(std::string expre){if(expre){return 1;else{return 0;");
std::cout<<s1.indexError("void function(std::string expre){if(expre){return 1;else{return 0;")<<std::endl;
Queue q1;
q1.enqueue("This is a secure message.");
q1.processMsg();
q1.enqueue("The product I received is damaged. What should I do?");
q1.processMsg();
q1.enqueue("I need assistance with setting up my new device");
q1.processMsg();
q1.enqueue("The website is not loading properly on my browser.");
q1.processMsg();
q1.enqueue("I accidentally placed the wrong order. Can it be canceled?");
q1.processMsg();
q1.enqueue("This is your project3. Have a happy thanksgiving!!! Hahaha");
q1.processMsg();
q1.enqueue("I forgot my password and can't reset it. Help, please! Do you provide technical support for mobile devices?");
q1.processMsg();
q1.enqueue("The software update is causing issues on my computer. The response time on your website is very slow.");
q1.processMsg();
return 0;
}
