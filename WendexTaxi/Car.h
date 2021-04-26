#pragma once

#include <string>
#include "Enums.h"
using namespace std;

class Car
{
private:
    int WaterBottels;

public:
	int ID;
	string Model;
    int CarTypeID;
    int X;
    string Color;
    string Number;
    
    void ParkInFrontOfTheEntrance();

	
    Car(int id, string model, int cartypeid, int x, string color, string number)
        :ID(id), Model(model), CarTypeID(cartypeid), X(x), Color(color), Number(number) {};
};
