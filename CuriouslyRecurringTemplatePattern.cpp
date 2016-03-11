//https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern#Static_polymorphism
#include <iostream>

using namespace std;
template <class T> 
class Base {
public:
	string name;
	Base():name("Base"){
		cout << "Constructing Base..." << endl;
	}

	~Base(){
		cout << "Destructing Base..." << endl;
	}


    void interface() {
        static_cast<T*>(this)->implementation();
    }

    static void static_func() {
        T::static_sub_func();
    }

    string &getName(){return name;}

    void talk(){ cout << "Hello World from Base" << endl;}
};

class Derived : public Base<Derived> {
public:
	Derived(){
		name = "Derived";
		cout << "Constructing Derived..." << endl;
	}

	~Derived(){
		cout << "Destructing Derived..." << endl;
	}

    void implementation(){
    	cout << "Hello implementation from Derived" << endl;

    }
    static void static_sub_func(){
    	cout << "Hello static_sub_func from Derived" << endl;    	
    }

    void printName(){
    	cout << getName() << endl;
    }

    void talk(){ cout << "Hello World from Derived" << endl;}
};

int main(){
	Base<Derived> *d = new Derived;
	Derived *dd = static_cast<Derived*>(d);
	d->interface();
	d->static_func();
	d->talk();
	dd->printName();

	// delete the subclass* since destructor is not virtual in base class
	// and if we deleted the base class* it wouldn't destroy the subclass's region of memory.
	delete dd; 
	return 0;
}