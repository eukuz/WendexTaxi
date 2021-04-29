#pragma once
#include <string>
#include "Enums.h"
using namespace std;
class Order
{
public:
	int ID;
	int Rating;
	int FromX;
	int ToX;
	CarTypes CarType;
	

	Order(int id, int rating,int fromx, int tox, CarTypes type) :
		ID(id), Rating(rating),FromX(fromx), ToX(tox), CarType(type){};
};

