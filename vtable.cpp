/* 

	To see the layout in mac, run clang -cc1 -fdump-record-layouts myfile.cpp.
	compile:	g++ -fdump-class-hierarchy vtable.com -o main
	example:

	*** Dumping AST Record Layout
   0 | class B2
   0 |   (B2 vtable pointer)
   8 |   int int_in_b2
     | [sizeof=16, dsize=12, align=8
     |  nvsize=12, nvalign=8]

*** Dumping AST Record Layout
   0 | class B1
   0 |   (B1 vtable pointer)
   8 |   int int_in_b1
     | [sizeof=16, dsize=12, align=8
     |  nvsize=12, nvalign=8]

*** Dumping AST Record Layout
   0 | class D
   0 |   class B1 (primary base)
   0 |     (B1 vtable pointer)
   8 |     int int_in_b1
  16 |   class B2 (base) // B2 should start at offset 12, but due to mem is 8-byte aligned, next object starts at next multiple of 8
  16 |     (B2 vtable pointer)
  24 |     int int_in_b2
  28 |   int int_in_d
     | [sizeof=32, dsize=32, align=8
     |  nvsize=32, nvalign=8]
1 error generated.
*/

#include <iostream>

using namespace std;
class B1 {
public:
	virtual ~B1(){cout << "B1::~B1" << endl;}
 	void f0() {cout << "B1::f0" << endl;}
 	virtual void f1() {cout << "B1::f1" << endl;}
 	int int_in_b1;
};

class B2 {
public:
	virtual ~B2(){cout << "B2::~B2" << endl;}
	virtual void f2() {cout << "B2::f2" << endl;}
	int int_in_b2;
};

class D : public B1, public B2 {
public:
	virtual ~D(){cout << "D::~D" << endl;}
	void d() {cout << "D::d" << endl;}
	void f2() {cout << "D::f2" << endl;} // override B2::f2()
	int int_in_d;
};


int main(){
	B2 *bb = new B2();
/*  32-bit memory layout for object b2
b2:
  +0: pointer to virtual method table of B2 (pointers are 8 bytes in x64 bit architectures)
  +8: value of int_in_b2

virtual method table of B2:
  +0: B2::f2()   
*/

	D  *d  = new D();
/*	layout for object d
d:
  +0: pointer to virtual method table of D (for B1)
  +8: value of int_in_b1
  +16: pointer to virtual method table of D (for B2) (since int_in_b1 offset is 8 bytes + 4 bytes in size,
  													  this pointer should start at offset 12-byte, but as
  													  this computer's mem alignment is 8 bytes, next object
  													  starts at next multiple of 8 which is 16)
 +24: value of int_in_b2
 +28: value of int_in_d

Total size: 32 Bytes.

virtual method table of D (for B1):
  +0: B1::f1()  // B1::f1() is not overridden

virtual method table of D (for B2):
  +0: D::f2()   // B2::f2() is overridden by D::f2()

*/

  	//inheritance thunks
	B1 *b1 = static_cast<B1*>(d); // b1 and d points to the same memory location
	B2 *b2 = static_cast<B2*>(d); // b2 points to location d+8, region within d which "looks like" an instance of B2

	cout << "B1 size: " << sizeof(B1) << ", D size: " << sizeof(D) << endl;

	uintptr_t address_d = reinterpret_cast<uintptr_t>(d); // address of d
	unsigned offset_int = offsetof(B1, int_in_b1); // offset of int_in_b1 within B1 = 8
	int *int_b1 = reinterpret_cast<int*>(address_d+offset_int); // Because B1 is at the same address as D.
	B2 *b3 = reinterpret_cast<B2*>(address_d+sizeof(B1)); // since B2 is allocated right after B1

	*int_b1 = 88; // accessed to member via memory offset
	b3->int_in_b2 = 44; //accessed to base class via memory offset

	cout << "Address of d: "<< d <<". "<< endl;
	cout << "Addresses of int_b1: "<<int_b1<<" = "<< &d->int_in_b1<<". Value of int_b1: "<< *int_b1<<" = "<< d->int_in_b1 << endl;
	cout << "Addresses of b2: "<< b2<<" = b3 "<< b3<<". Value of int_b2: "<<b2->int_in_b2<<" = "<< b3->int_in_b2 << endl << endl;


	//invocation
	// (*(*(d[+0]/*pointer to virtual method table of D (for B1))[0]))(d)   /* Call d->f1() */
	// (*(*(d[+8]/*pointer to virtual method table of D (for B2)*/)[0]))(d+8) /* Call d->f2() */
	// (*B1::f0)(d) // Call d->f0()

	// ((*(b2[0]))(b2))
	delete d;
	delete bb;
	return 0;
}