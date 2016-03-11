//https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern#Static_polymorphism

#include <iostream>
#include <typeinfo>

using namespace std;
template <typename T>
struct counter
{
private:
    void incrementCounters(){
        ++objects_created;
        ++objects_alive;
    }
protected:
    static int objects_created;
    static int objects_alive;

public:
    counter() {
        incrementCounters();
    }
    
    counter(const counter&) {
        incrementCounters();
    }

    static void printCounters(){
        cout << typeid(T).name() << " Objects. created: " << objects_created << ", alive: " << objects_alive << endl;
    }

protected:
    ~counter(){ // objects should never be removed through pointers of this type
        --objects_alive;
    }
};
template <typename T> int counter<T>::objects_created( 0 );
template <typename T> int counter<T>::objects_alive( 0 );

class X : public counter<X> {
    int m_int;
};

class Y : public counter<Y> {
    char m_char;
};


void printAllCounters(const string &msg = ""){
    bool haveMessage = !msg.empty();
    if (haveMessage){
        cout << msg <<":"<<endl <<"\t";
    }
    X::printCounters();
    if(haveMessage){
        cout << "\t";
    }
    Y::printCounters();
}


int main(){
    int MAX_ELEMENTS = 5;
    X **arr1 = new X*[MAX_ELEMENTS];
    Y **arr2 = new Y*[MAX_ELEMENTS];

    for(int i = 0; i < MAX_ELEMENTS; ++i ){
        if (i%2)
            arr1[i] = new X;
        else 
            arr2[i] = new Y;
    }
    printAllCounters("After instantiation");




    for(int i = 0; i < MAX_ELEMENTS; ++i ){
        if (i%2)
            delete arr1[i];
        else 
            delete arr2[i];
    }
    printAllCounters("After deleting objects");


    delete[] arr1;
    delete[] arr2; 
    printAllCounters("After deleting arrays");

    return 0;
}