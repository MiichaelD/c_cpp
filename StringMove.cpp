#include <iostream>
#include <string>

int main(){
	using namespace std;
	string * str = new string("15");
	string str2 = *str;

	cout << "\tCopying str to str2; "<< endl;
	cout << "str address: " << str << ".\tvalue: " << *str << ".\tstr2: " << str2 << endl;

	string str3;
	str3 = std::move(*str);
	cout << "\tMoving str to str3; "<< endl;
	cout << "str address: " << str << ".\tvalue: " << *str << ".\tstr2: " << str2 << "\tstr3: "<< str3<<endl;

	string str4 = "hello world";
	cout << "\tCreating str4; "<< endl;
	cout << "str address: " << str << ".\tvalue: " << *str << ".\tstr2: " << str2 << "\tstr3: "<< str3 << "\tstr4: "<< str4<<endl;

	*str = std::move(str4);
	cout << "\tMoving str4 to str "<< endl;
	cout << "str address: " << str << ".\tvalue: " << *str << ".\tstr2: " << str2 << "\tstr3: "<< str3 << "\tstr4: "<< str4<<endl;

	delete str;
	cout << "\tDeleting str; "<< endl;
	cout << "str address: " << str << ".\tvalue: " << *str << ".\tstr2: " << str2 << "\tstr3: "<< str3 << "\tstr4: "<< str4<<endl;


	string &strRef = str2;
	cout << "\n\tstrRef referencing str2; "<< endl;
	cout << "str2 addess: " << &str2 << ".\tvalue:" << str2<< ".\tstrRef address: "<< &strRef << ".\tvalue: " << strRef<< endl;

	string str5 = std::move(strRef);
	cout << "\tMoving strRef to str5; "<< endl;
	cout << "str2 addess: " << &str2 << ".\tvalue:" << str2<< ".\tstrRef address: "<< &strRef << ".\tvalue: " << strRef<< ".\tstr5: "<< str5 << endl;


	return 0;
}