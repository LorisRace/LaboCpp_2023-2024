#include "Exception.h"
#include <iostream>

Exception :: Exception()
{
	setMessage("Exception");
}

Exception::Exception(string m)
{
	setMessage(m);
}

Exception :: Exception(const Exception &exception)
{
	setMessage(exception.getMessage());
}

Exception :: ~Exception()
{

}

void Exception :: setMessage(string m)
{
	MessageErreur = m;
}

string Exception::getMessage() const 
{
    return MessageErreur;
}

void Exception :: Affiche()const
{
	cout <<"L'exception est : " << MessageErreur << endl;
}