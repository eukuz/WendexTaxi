#pragma once
#include <string>
using namespace std;
class PaymentMethod
{
public:
	int ID;
	string Method;
	PaymentMethod(int id, string method) : ID(id), Method(method) {};
};

