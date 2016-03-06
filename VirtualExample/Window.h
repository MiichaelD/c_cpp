#pragma once
class Window{
    public:
    int num;
    Window();
    ~Window();
    Window(const Window& rhs);
    Window &operator= ( const Window &rhs);
    
    virtual void onResize();
    virtual void onReady();
};