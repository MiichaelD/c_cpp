#include <iostream> 
#include <string>
#include <type_traits> // std::is_base_from

using namespace std;

template<typename D, typename B>
struct IsDerivedFromHelper {
    struct No { }; // empty class = 1 byte
    struct Yes { No no[3]; }; // non-empty class, 3*sizeof(No) = 3 bytes
    
    // NOTE: why is this declared function with no definition not breaking ??? 
    static Yes Test( B* ); // if function receives a B* it returns a YES
    static No Test( ... ); // if function receives anything else it returns NO
public:
    static const bool value =  sizeof(Test(static_cast<D*>(nullptr))) == sizeof(Yes);
    
};


// A meta-function that return the type T if Condition is true.
template <typename C, typename P>
bool IsDerivedFrom() {
//    return std::is_base_from<P,C>::value;
    return IsDerivedFromHelper<C, P>::value;
};

class A {
    int a;
    public:
    virtual ~A(){}
};

class B : public A{
    int b;
    public:
    virtual ~B(){}
};

class C : public B{
    int c;
    public:
    virtual ~C(){}
};

class D {
    int d;
    public:
    virtual ~D(){}
};

int main(){
    cout << "sizeof(No) = " << sizeof(IsDerivedFromHelper<B, A>::No) << ". sizeof(Yes) = " << sizeof(IsDerivedFromHelper<B, A>::Yes) << endl;
    cout << "is B derived from A? " << (IsDerivedFrom<B, A>() ? "true" : "false") << endl;
    cout << "is C derived from A? " << (IsDerivedFrom<C, A>() ? "true" : "false") << endl;
    cout << "is D derived from A? " << (IsDerivedFrom<D, A>() ? "true" : "false") << endl;
}