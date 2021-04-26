#include "AdminGateway.h"
#include "DBShell.h"

void AdminGateway::Login(string Name)
{
	this->admin = DBShell::getAdmin(Name);
}

void AdminGateway::Block(Driver* driver,bool block)
{
	DBShell::Block(driver, block);
}

void AdminGateway::Block(Passenger* passenger, bool block)
{
	DBShell::Block(passenger, block);
}

void AdminGateway::Validate(Car* car, bool validate)
{
	DBShell::Validate(car,validate);
}

void AdminGateway::ShowDB()
{
	DBShell::ShowDB();
}
