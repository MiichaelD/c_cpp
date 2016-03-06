#include <iostream>

using namespace std;
class Dog{
public:
	string name;
	Dog(){
        cout << "\t\t\tConstructing a Dog \n";
        name = "yoggy";
    }
	~Dog(){
        cout << "\t\t\tDestroying Dog \n";
    }
};

class A{
public:
    int a;
    Dog *dogg;
    A(){
    	cout << "constructing A \n";
    }
    virtual ~A(){ 
    	cout << "Destroying A \n";
    	if (dogg){
    		delete dogg;
    		dogg = NULL;
    	}
    }
};

class B : public A{
public:
    int bb;
    B(){
    	cout << "\tConstructing B \n";
    }
    ~B(){ 
    	cout << "\tDestroying B \n";
    }
};

class C : public B{
public:
    int ccc;
    C(){
    	cout << "\t\tConstructing C \n";
    	dogg = new Dog();
    }
    ~C(){ 
    	cout << "\t\tDestroying C \n";
	}
};

class Z {
    public:
    int z;
    Z(C *c){
        cout << "\t\tConstructing Z \n";
    }
    ~Z(){ 
        cout << "\t\tDestroying Z\n";
    }
};

int main(){
    B *objc = new C;
    // delete static_cast<C*>(objc);
    Z littleZ(objc);
    delete objc;
    return 0;
}