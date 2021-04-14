#pragma once
#include <string>
using namespace std;
class Car
{
public:
	int ID;
	string Model;
    int CarTypeID;
    int X;
    string Color;
    string Number;
	
    Car(int id, string model, int cartypeid, int x, string color, string number)
        :ID(id), Model(model), CarTypeID(cartypeid), X(x), Color(color), Number(number) {};
};
