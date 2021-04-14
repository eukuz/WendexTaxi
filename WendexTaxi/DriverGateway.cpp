#include "DriverGateway.h"
#include "DBShell.h"

void DriverGateway::Login(string Name)
{
	this->driver = DBShell::getDriver(Name);
}
