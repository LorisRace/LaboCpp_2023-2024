#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

#ifndef EXCEPTION_H
#define EXCEPTION_H

class Exception
{

protected:
	string MessageErreur;

public:
	Exception();
	Exception(string MessageErreur);
	Exception(const Exception &exception);
	virtual ~Exception();
    string getMessage() const;
    void setMessage(string MessageErreur);
    void Affiche()const;
};

#endif