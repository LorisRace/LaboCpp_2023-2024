#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include <stdexcept>
using namespace std;
using std :: string;


#ifndef EXCEPTION_H
#define EXCEPTION_H

class Exception
{

protected:
	string MessageErreur;

public:
	Exception();
	Exception(const string &MessageErreur);
	Exception(const Exception &exception);
	virtual ~Exception();
    string getMessage() const;
    void setMessage(const string &MessageErreur);
    void Affiche()const;
};

#endif