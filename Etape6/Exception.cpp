#include "Exception.h"
#include <iostream>

Exception :: Exception()
{
	setMessage("Exception\n");
}

Exception::Exception(const string &MessageErreur)
{
	setMessage("MessageErreur");
}

Exception :: Exception(const Exception &exception)
{
	setMessage(exception.getMessage());
}

Exception :: ~Exception()
{

}

void Exception :: setMessage(const string &MessageErreur)
{
	this->MessageErreur = MessageErreur;
}

string Exception::getMessage() const 
{
    return MessageErreur;
}

void Exception :: Affiche()const
{
	cout <<"L'exception est : " << MessageErreur << endl;
}