#include <iostream>

using namespace std;
class A{
public:
	A(){}
	virtual ~A(){ cout << "Destroying A" << endl;}
	void doStuff(){cout << "A doing stuff" << endl;}
};

class B: public A{
public:
	B(){}
	~B(){ cout << "Destroying B" << endl;} // implicitly virtual
	virtual void doStuff(){cout << "B doing stuff" << endl;}
};

class C: public B{
public:
	C(){}
	~C(){ cout << "Destroying C" << endl;}// implicitly virtual
	void doStuff(){cout << "C doing stuff" << endl;} //implicitly virtual
};

class D: public C{
public:
	D(){}
	~D(){ cout << "Destroying D" << endl;}// implicitly virtual
	void doStuff(){cout << "D doing stuff" << endl;} // implicitly virtual
};

int main(){
	A *ptrA = new D;
	B *ptrB = new D;
	C *ptrC = new D;
	D *ptrD = new D;

	ptrA->doStuff();
	delete ptrA;
	cout << endl;
	ptrB->doStuff();
	delete ptrB;
	cout << endl;
	ptrC->doStuff();
	delete ptrC;
	cout << endl;
	ptrD->doStuff();
	delete ptrD;
	return 0;
}