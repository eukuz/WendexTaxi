#include "DriverGateway.h"
#include "DBShell.h"

void DriverGateway::Login(string Name)
{
	this->driver = DBShell::getDriver(Name);
}

void DriverGateway::Move(int x)
{
	DBShell::MoveDriver(this->driver,x);
}

void DriverGateway::PrintOrderHistory()
{
	DBShell::PrintOrdersD(this->driver);
}
