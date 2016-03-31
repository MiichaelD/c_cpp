#include <iostream>
#include <typeinfo>
#include <vector>

//What are rvalues, lvalues, xvalues, glvalues, and prvalues?
//http://stackoverflow.com/questions/3601602/what-are-rvalues-lvalues-xvalues-glvalues-and-prvalues
/*

lvalue -- 	from practical point of view, something from left hand side of the equal operator.
			You can think that it is something from which you can take the address (variables,
			or lvalue reference). But it is not rigorous definition, e.g. as mentioned in comments
			bit field is also lvalue, but can not be addressable.

rvalue -- 	from practical point of view it is something from right hand side of the equal operator. 
			You can think that it is something from which you can not take the address (unnamed
			temporary variables). Temporary objects can be pass to functions only by const reference.
			A good counter example what is rvalue, but has a name - this

By the way -- constructor of copy for auto_ptr has some strange signature in sense that it is not
			allowable to pass temporary auto_ptr to it. But you can. It is feature for most compilers,
			so you can safely use it. But with C++2003 you can not do it legaly!

xvalue -- 	temporary object will soon be destroyed. You should take data from it, because it will die
			very soon. Such reference in C++11 has && signature.

			Overload function with xvalue Reference (A&&) has priority under constant reference (const A&)

prvalue -- 	pure rvalue. Real object.

glvalue -- 	it is lvalue or xvalue.

*/
using namespace std;

int i = 7;

class A {
	string m_name;
public:
	A(string name):m_name(name){ cout << "Constructing " << m_name << endl;}
	~A(){ cout << "Destructing " << m_name << endl;}

	A(A const &a){
		cout << "Copying " << a.getName() << endl;	
		m_name = a.getName() + "copy";
	}
	
	A(A const &&a){
		cout << "Const Moving " << a.getName() << endl;
		m_name = a.getName() + "move";
	}

	A(A &&a){// for r-value params
		cout << "Moving " << a.getName() << endl;
		m_name = a.getName() + "move";
	}

	A& operator=(A const &a){
		cout << "Copying by assigning operator" << a.getName() << endl;	
		m_name = a.getName() + "copyAssignment";
		return *this;
	}
	
	A& operator=(A const &&a){
		cout << "Const Moving by assigning operator " << a.getName() << endl;
		m_name = a.getName() + "moveAssignment";
		return *this;
	}

	A& operator=(A &&a){ // for r-value params
		cout << "Moving by const assigning operator " << a.getName() << endl;
		m_name = a.getName() + "moveAssignment";
		return *this;
	}
	

	void doStuff() const { cout << m_name << " doing stuff" << endl; }

	const string &getName() const { return m_name;}
};

A &&func(){
	static int repetitions = 0;
	return A("func_" + to_string(++repetitions));
}

A func1(){
	static int repetitions = 0;
	return A("func1_" + to_string(++repetitions));
}


int&& f(){
    return 3;
}

void printVector(vector<int> &vec){
	for(auto i : vec){
		cout << i <<", ";
	}
	cout << endl;
}

int main(){
	{
		cout << "moving a container"<<endl;
		vector<int> vec{1,2,3,4,5};
		cout << "vec: ";
		printVector(vec);

		auto moved = move(vec);
		//vec now is in an valid bu unspecified state, we could use it if we call functions
		//that require no pre-condition, i.e. vec.clear() would put it in a specified state.
		cout << "vec: ";
		printVector(vec);
		cout << "moved: ";
		printVector(moved);
		cout << endl << endl;


		// named rvalue references are lvalues;
		// now a, holds a reference to a dead object
		A &&a = func();
		cout << typeid(a).name() << endl;
		a.doStuff();
		cout << endl << endl;

		//moving an unnamed temporary object (prvalue)
		A aa = func();
		cout << typeid(aa).name() << endl;
		aa.doStuff();
		cout << endl << endl;

		//copying a named object (lvalue)
		A aaa{aa};
		cout << typeid(aaa).name() << endl;
		aaa.doStuff();
		cout << endl << endl;

		//invoking a member function from an unnamed object (lvalue)
		func1().doStuff();
	}


	cout << endl << endl << "TESTS:"<< endl;
	//TESTS:
	//lvalues:
	std::cout<<&"www"<<std::endl; // This address ...
    std::cout<<&"www"<<std::endl; // ... and this address are the same.
    "www"; // The expression "www" in this row is an lvalue expression, because it refers to the same entity ...
    "www"; // ... as the entity the expression "www" in this row refers to.

    i; // The expression i in this row is an lvalue expression, because it refers to the same entity ...
    i; // ... as the entity the expression i in this row refers to.

    int* p_i=new int(7);
    *p_i; // The expression *p_i in this row is an lvalue expression, because it refers to the same entity ...
    *p_i; // ... as the entity the expression *p_i in this row refers to.

    const int& r_I=7;
    r_I; // The expression r_I in this row is an lvalue expression, because it refers to the same entity ...
    r_I; // ... as the entity the expression r_I in this row refers to.

    f(); // The expression f() in this row is an lvalue expression, because it refers to the same entity ...
    i; // ... as the entity the expression f() in this row refers to.



	//xvalues: The expression E belongs to the xvalue category if and only if it is
	
	//— the result of calling a function, whether implicitly or explicitly, whose return type is an rvalue reference to the type of object being returned, or
    f(); // The expression f() belongs to the xvalue category, because f() return type is an rvalue reference to object type.

    //— a cast to an rvalue reference to object type, or
    static_cast<int&&>(7); // The expression static_cast<int&&>(7) belongs to the xvalue category, because it is a cast to an rvalue reference to object type.
    std::move(7); // std::move(7) is equivalent to static_cast<int&&>(7).

    //— a class member access expression designating a non-static data member of non-reference type in which the object expression is an xvalue, or
    func1().doStuff();


}