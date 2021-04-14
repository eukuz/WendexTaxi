#include "DBShell.h"
#include "sqlite/sqlite3.h"
#include <iostream>
using namespace std;
const char* path = "WendexTaxiDB.db";

Passenger* DBShell::getPassenger(string Name)
{
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "SELECT * FROM Passengers WHERE Name = '" + Name + "'";
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	Passenger* p = NULL;
	if (sqlite3_step(stmt) != SQLITE_DONE)
	{
		p = new Passenger(
			sqlite3_column_int(stmt, 0),
			string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))),
			sqlite3_column_double(stmt, 2));
		cout << p->Name << " " << "Logged!" << endl;
	}
	else {
		cout << "There's no Passenger "<<p->Name << " in the system!" << endl;
	}
	sqlite3_close(db);

	return p;
}

Driver* DBShell::getDriver(string Name)
{
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "SELECT * FROM Drivers WHERE Name = '" + Name + "'";
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	Driver* d = NULL;
	if (sqlite3_step(stmt) != SQLITE_DONE)
	{
		d = new Driver(
			sqlite3_column_int(stmt, 0),
			string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))),
			sqlite3_column_int(stmt, 2),
			sqlite3_column_int(stmt, 3),
			sqlite3_column_int(stmt, 4),
			sqlite3_column_double(stmt, 5));
		cout << d->Name << " " << "Logged!" << endl;
	}
	else {
		cout << "There's no Driver " << d->Name << " in the system!" << endl;
	}
	sqlite3_close(db);

	return d;
}
