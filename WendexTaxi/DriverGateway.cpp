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

void DriverGateway::StartRide(Order order)
{
}

void DriverGateway::FinishRide(Order order)
{
}

vector<Order*> DriverGateway::GetOrdersAvailable()
{
	return DBShell::GetOrders(this->driver);
}
