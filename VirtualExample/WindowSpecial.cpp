#include "WindowSpecial.h"
#include <iostream>

WindowSpecial::WindowSpecial(){
    std::cout << "Constructing WindowSpecial: "<< num << " new num: " << 8 << std::endl;
    num = 8;
}

WindowSpecial::~WindowSpecial(){
    std::cout << "Destructing WindowSpecial: " << num << std::endl;
}

WindowSpecial::WindowSpecial(const WindowSpecial& rhs){
    std::cout << "Copy Constructing WindowSpecial: " << num << " new num: "<< rhs.num << std::endl;
}

WindowSpecial &WindowSpecial::operator= ( const WindowSpecial &rhs){
    std::cout << "Asignment Operator Constructing WindowSpecial!!" << std::endl;
    return *this;
}


void WindowSpecial::onResize(){
    static_cast<Window>(*this).onResize(); // this creates a new copy!!
    // static_cast<Window&>(*this).onResize(); // this calls base class onResize, but since its virtual it will call this function, calling a infinite loop.!!
    // Window::onResize(); // this executes the base class onResize();
    std::cout << "onResize WindowSpecial: " << num  << " new num: " << num*2<< std::endl;
    num *= 2;
}

void WindowSpecial::onScreen(){
    std::cout << "onScreen WindowSpecial: " << num << std::endl;
}