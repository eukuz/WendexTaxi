#pragma once
#include <string>
using namespace std;
class Order
{
public:
	int ID;
	int Rating;
	int FromX;
	int ToX;
	

	Order(int id, int rating,int fromx, int tox) :
		ID(id), Rating(rating),FromX(fromx), ToX(tox){};
};

