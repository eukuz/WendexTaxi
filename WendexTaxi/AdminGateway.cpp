#include "AdminGateway.h"
#include "DBShell.h"

void AdminGateway::Login(string Name)
{
	this->admin = DBShell::getAdmin(Name);
}
