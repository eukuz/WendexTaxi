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

void DriverGateway::StartRide(Order* order)
{
	DBShell::StartRide(this->driver, order);
}

void DriverGateway::FinishRide(Order* order)
{
	DBShell::FinishRide(this->driver, order);
}

Car* DriverGateway::GetMyCar()
{
	return DBShell::GetCar(this->driver->CarID);
}

vector<Order*> DriverGateway::GetOrdersAvailable()
{
	return DBShell::GetOrders(this->driver);
}

void DriverGateway::SetStatus(DriverStatus status)
{
	DBShell::UpdateDriverStatus(this->driver, status);
}
