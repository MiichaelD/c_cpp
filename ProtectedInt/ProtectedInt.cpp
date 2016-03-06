#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ProtectedInt.h"

int ProtectedInt::leftSecret;
int ProtectedInt::rightSecret;

void ProtectedInt::init()
{
	srand( time(0) );
	leftSecret = rand();
	rightSecret = rand();
}

ProtectedInt::ProtectedInt()
{
	left = 0;
	right = 0;

#ifdef _DEBUG
	debug = 0;
#endif
}

void ProtectedInt::set( int v )
{
	left = v ^ leftSecret;
	right = v ^ rightSecret;

#ifdef _DEBUG
	debug = v;
#endif
}

const int ProtectedInt::get()
{
	int leftV = left ^ leftSecret;
	int rightV = right ^ rightSecret;
	if( leftV != rightV )
	{
		left = 0;
		right = 0;
		return 0;
	}

	return leftV;
}

ProtectedInt& ProtectedInt::operator += ( int v )
{
	const int temp = get() + v;
	set( temp );
	return *this;
}

ProtectedInt& ProtectedInt::operator -= ( int v )
{
	const int temp = get() - v;
	set( temp );
	return *this;
}

ProtectedInt& ProtectedInt::operator = ( int v )
{
	set( v );
	return *this;
}

bool ProtectedInt::operator == ( int v )
{
	return get() == v;
}

bool ProtectedInt::operator <= ( int v )
{
	return get() <= v;
}

bool ProtectedInt::operator < ( int v )
{
	return get() < v;
}

bool ProtectedInt::operator >= ( int v )
{
	return get() >= v;
}

bool ProtectedInt::operator > ( int v )
{
	return get() > v;
}

int ProtectedInt::operator * ( int v )
{
	return get() * v;
}

int ProtectedInt::operator / ( int v )
{
	return get() / v;
}

int ProtectedInt::operator + ( int v )
{
	return get() + v;
}

int ProtectedInt::operator - ( int v )
{
	return get() - v;
}

int ProtectedInt::operator * ( ProtectedInt& v )
{
	return get() * v.get();
}

int ProtectedInt::operator / ( ProtectedInt& v )
{
	return get() / v.get();
}

int ProtectedInt::operator + ( ProtectedInt& v )
{
	return get() + v.get();
}

int ProtectedInt::operator - ( ProtectedInt& v )
{
	return get() - v.get();
}

int ProtectedInt::operator - ()
{
	return -get();
}

ProtectedInt& ProtectedInt::operator--()
{
	const int x = get() - 1;
	set( x );
	return *this;
}

ProtectedInt& ProtectedInt::operator--( int )
{
	const int x = get() - 1;
	set( x );
	return *this;
}

ProtectedInt& ProtectedInt::operator++()
{
	const int x = get() + 1;
	set( x );
	return *this;
}

ProtectedInt& ProtectedInt::operator++( int )
{
	const int x = get() + 1;
	set( x );
	return *this;
}

///////////////////////////////////////////////
int operator - ( int a, ProtectedInt& b )
{
	return a - b.get();
}

int operator + ( int a, ProtectedInt& b )
{
	return a + b.get();
}

int operator * ( int a, ProtectedInt& b )
{
	return a * b.get();
}

int operator / ( int a, ProtectedInt& b )
{
	return a / b.get();
}

//PROTECTED INT MAX

int ProtectedIntMAX::leftSecret;
int ProtectedIntMAX::rightSecret;

void ProtectedIntMAX::init()
{
	srand( time(0) );
	leftSecret = rand();
	rightSecret = rand();
}

ProtectedIntMAX::ProtectedIntMAX()
{
	left = INT_MAX/3;
	right = INT_MAX/3;
	
#ifdef _DEBUG
	debug = INT_MAX/3;
#endif
}

void ProtectedIntMAX::set( int v )
{
	left = v ^ leftSecret;
	right = v ^ rightSecret;
	
#ifdef _DEBUG
	debug = v;
#endif
}

const int ProtectedIntMAX::get()
{
	int leftV = left ^ leftSecret;
	int rightV = right ^ rightSecret;
	if( leftV != rightV )
	{
		left = INT_MAX/3;
		right = INT_MAX/3;
		return INT_MAX/5;
	}
	
	return leftV;
}

ProtectedIntMAX& ProtectedIntMAX::operator += ( int v )
{
	const int temp = get() + v;
	set( temp );
	return *this;
}

ProtectedIntMAX& ProtectedIntMAX::operator -= ( int v )
{
	const int temp = get() - v;
	set( temp );
	return *this;
}

ProtectedIntMAX& ProtectedIntMAX::operator = ( int v )
{
	set( v );
	return *this;
}

bool ProtectedIntMAX::operator == ( int v )
{
	return get() == v;
}

bool ProtectedIntMAX::operator <= ( int v )
{
	return get() <= v;
}

bool ProtectedIntMAX::operator < ( int v )
{
	return get() < v;
}

bool ProtectedIntMAX::operator >= ( int v )
{
	return get() >= v;
}

bool ProtectedIntMAX::operator > ( int v )
{
	return get() > v;
}

int ProtectedIntMAX::operator * ( int v )
{
	return get() * v;
}

int ProtectedIntMAX::operator / ( int v )
{
	return get() / v;
}

int ProtectedIntMAX::operator + ( int v )
{
	return get() + v;
}

int ProtectedIntMAX::operator - ( int v )
{
	return get() - v;
}

int ProtectedIntMAX::operator * ( ProtectedIntMAX& v )
{
	return get() * v.get();
}

int ProtectedIntMAX::operator / ( ProtectedIntMAX& v )
{
	return get() / v.get();
}

int ProtectedIntMAX::operator + ( ProtectedIntMAX& v )
{
	return get() + v.get();
}

int ProtectedIntMAX::operator - ( ProtectedIntMAX& v )
{
	return get() - v.get();
}

int ProtectedIntMAX::operator - ()
{
	return -get();
}

ProtectedIntMAX& ProtectedIntMAX::operator--()
{
	const int x = get() - 1;
	set( x );
	return *this;
}

ProtectedIntMAX& ProtectedIntMAX::operator--( int )
{
	const int x = get() - 1;
	set( x );
	return *this;
}

ProtectedIntMAX& ProtectedIntMAX::operator++()
{
	const int x = get() + 1;
	set( x );
	return *this;
}

ProtectedIntMAX& ProtectedIntMAX::operator++( int )
{
	const int x = get() + 1;
	set( x );
	return *this;
}

///////////////////////////////////////////////
int operator - ( int a, ProtectedIntMAX& b )
{
	return a - b.get();
}

int operator + ( int a, ProtectedIntMAX& b )
{
	return a + b.get();
}

int operator * ( int a, ProtectedIntMAX& b )
{
	return a * b.get();
}

int operator / ( int a, ProtectedIntMAX& b )
{
	return a / b.get();
}
