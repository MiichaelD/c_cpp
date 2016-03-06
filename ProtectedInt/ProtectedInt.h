#ifndef __PROTECTEDINT_H__
#define __PROTECTEDINT_H__

class ProtectedInt
{
public:
	ProtectedInt();

	void set( int v );
	const int get();

	// assigning
	ProtectedInt& operator = ( int v );
	ProtectedInt& operator += ( int v );
	ProtectedInt& operator -= ( int v );		

	// logic
	bool operator == ( int v );
	bool operator <= ( int v );
	bool operator < ( int v );
	bool operator >= ( int v );
	bool operator > ( int v );

	int operator - ();

	ProtectedInt& operator--();
	ProtectedInt& operator--( int );

	ProtectedInt& operator++();
	ProtectedInt& operator++( int );

	// return int
	int operator * ( int v );	
	int operator / ( int v );
	int operator + ( int v );
	int operator - ( int v );

	// self's operation
	int operator * ( ProtectedInt& v );	
	int operator / ( ProtectedInt& v );
	int operator + ( ProtectedInt& v );
	int operator - ( ProtectedInt& v );

	// casting
	operator char() { return (char)get(); }	
	operator short() { return (short)get(); }	
	operator int() { return (int)get(); }
	operator unsigned char() { return (unsigned char)get(); }	
	operator unsigned short() { return (unsigned short)get(); }	
	operator unsigned int() { return (unsigned int)get(); }
	operator float() { return (float)get(); }	

	static void init();
	static int leftSecret;
	static int rightSecret;

private:
	int left;
	int right;

#ifdef _DEBUG
	int debug;
#endif
};

int operator - ( int a, ProtectedInt& b );
int operator + ( int a, ProtectedInt& b );
int operator * ( int a, ProtectedInt& b );
int operator / ( int a, ProtectedInt& b );


class ProtectedIntMAX
{
public:
	ProtectedIntMAX();
	
	void set( int v );
	const int get();
	
	// assigning
	ProtectedIntMAX& operator = ( int v );
	ProtectedIntMAX& operator += ( int v );
	ProtectedIntMAX& operator -= ( int v );
	
	// logic
	bool operator == ( int v );
	bool operator <= ( int v );
	bool operator < ( int v );
	bool operator >= ( int v );
	bool operator > ( int v );
	
	int operator - ();
	
	ProtectedIntMAX& operator--();
	ProtectedIntMAX& operator--( int );
	
	ProtectedIntMAX& operator++();
	ProtectedIntMAX& operator++( int );
	
	// return int
	int operator * ( int v );
	int operator / ( int v );
	int operator + ( int v );
	int operator - ( int v );
	
	// self's operation
	int operator * ( ProtectedIntMAX& v );
	int operator / ( ProtectedIntMAX& v );
	int operator + ( ProtectedIntMAX& v );
	int operator - ( ProtectedIntMAX& v );
	
	// casting
	operator char() { return (char)get(); }
	operator short() { return (short)get(); }
	operator int() { return (int)get(); }
	operator unsigned char() { return (unsigned char)get(); }
	operator unsigned short() { return (unsigned short)get(); }
	operator unsigned int() { return (unsigned int)get(); }
	operator float() { return (float)get(); }
	
	static void init();
	static int leftSecret;
	static int rightSecret;
	
private:
	int left;
	int right;
	
#ifdef _DEBUG
	int debug;
#endif
};

int operator - ( int a, ProtectedIntMAX& b );
int operator + ( int a, ProtectedIntMAX& b );
int operator * ( int a, ProtectedIntMAX& b );
int operator / ( int a, ProtectedIntMAX& b );

#endif // __PROTECTEDINT_H__
