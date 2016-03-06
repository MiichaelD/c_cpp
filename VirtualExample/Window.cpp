#include "Window.h"
#include <iostream>
#include "WindowSpecial.h"


Window::Window():num(1){
    std::cout << "Constructing Window: "<< num << std::endl;
}

Window::Window(const Window& rhs){
    std::cout << "Copy Constructing Window: "<< num << " new num: " << rhs.num << std::endl;
    num = rhs.num;
}
Window::~Window(){
    std::cout << "Destructing Window: " << num << std::endl;
}

Window& Window::operator= ( const Window &rhs){
    std::cout << "Asignment Operator Constructing Window" << std::endl;
    return *this;
}

void Window::onResize(){
    std::cout << "onResize Window: "<< num << " new num:" << 15 << std::endl;
    num = 15;
}

void Window::onReady(){
    std::cout << "onReady Window: "<< num  << std::endl;
}