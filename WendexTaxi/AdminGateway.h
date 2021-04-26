#pragma once
#include <string>
#include "Admin.h"
using namespace std;
class AdminGateway
{
public:
	void Login(string Name);
	Admin* admin;

};

