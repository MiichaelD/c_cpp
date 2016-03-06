#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Foo{
public:
    vector<int> m_vector;
    Foo(){
        cout << "default constructor\n";
    }

    Foo(int y){
        m_vector.push_back(y);
        cout << "parameter-init constructor w/ ";
        printValues();
    }

    Foo(const Foo &other):m_vector{other.m_vector}{
        cout << "copy constructor w/"<< m_vector.size() <<"-values: "<< endl<<"\t";
        printValues();
    }

    Foo& operator=(const Foo& other){
        m_vector = other.m_vector;
        cout << "assignment operator w/"<< m_vector.size() <<"-values: "<<"\t";
        printValues();
        return *this;
    }

    Foo(initializer_list<Foo> list){
        cout << "initializer "<< list.size() << "-list: \n";

        size_t index = 0;
        for (const Foo &it : list){
            cout << "\titem " << index++ << " ";
            it.printValues();
        }

        cout << endl << "\tcopying values from first element of init_list.\n\t";
        *this = *list.begin();
        cout << endl;
    }

    void printValues() const{
        cout << "Total values: " << m_vector.size() << ". Values: ";
        for (int val : m_vector){
            cout << val << " ";
        }
        cout << endl;
    }
};

int main(){
    // Foo a; // calls default constructor;
    // Foo b(5);
    Foo bb{5};
    
    /* next line creates 3 new objects using the parameter-init constructor
       then it calls the initializer list constructor*/
    Foo c{6, 7, 8};

    cout << "Foo c : "<< endl;
    c.printValues();

    // Foo d(a);
    // Foo e{b};
    return 0;
}