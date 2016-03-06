#pragma once
#include "Window.h"
class WindowSpecial : public Window{
    public:
    WindowSpecial();
    ~WindowSpecial();
    WindowSpecial(const WindowSpecial& rhs);
    WindowSpecial& operator= ( const WindowSpecial &rhs);

    virtual void onResize() override;
    void onScreen();
};