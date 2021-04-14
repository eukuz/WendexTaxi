#include "PassengerGateway.h"
#include "DBShell.h"


void PassengerGateway::Login(string Name)
{
	this->passenger = DBShell::getPassenger(Name);
}
