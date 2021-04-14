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
	sqlite3_finalize(stmt);

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
	sqlite3_finalize(stmt);


	return d;
}

void DBShell::MoveDriver(Driver* driver,int x) //not working?? db's locked!!
{
	sqlite3* db;
	char* er;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	
	
	string query = " UPDATE Cars SET X = '"+to_string(x)+"' WHERE ID = '"+ to_string(driver->CarID)+"'";
	
	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);

	cout << driver->Name << " moved to X= " << x << endl;;
		
	sqlite3_close(db);
	sqlite3_finalize(stmt);

	/*exit = sqlite3_exec(db, query.c_str(), NULL, 0, &er);
	if (exit != SQLITE_OK) {
		cerr << "Error upd "<<endl;
		sqlite3_free(er);
	}else*/

	//cout << driver->Name << " moved to X= " << x;
	//
	//sqlite3_close(db);
	//GetCar("123");
}

void DBShell::PrintOrders(Passenger* passenger)
{
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = " SELECT Orders.FromX, Orders.ToX, Orders.UnixTime, Drivers.Name, CarTypes.Type "
		" FROM Orders "
		" INNER JOIN Drivers ON Orders.DriverID = Drivers.ID, "
		" CarTypes ON Orders.CarTypeID = CarTypes.ID "
		" WHERE Orders.PassengerID = " + to_string(passenger->ID);
	cout << passenger->Name<<"'s orders:"<<endl;
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	while (sqlite3_step(stmt) != SQLITE_DONE) {
		cout << "From: "<< sqlite3_column_int(stmt, 0) 
			<< " To:  "<<sqlite3_column_int(stmt, 1)
			<< " At (unix time): "<< sqlite3_column_int(stmt, 2) 
			<< " Driver: "<< sqlite3_column_text(stmt, 3)
			<< " Car type: "<< sqlite3_column_text(stmt, 4)
			<< endl;
	}
	
	sqlite3_close(db);
	sqlite3_finalize(stmt);

}

void DBShell::GetCar(string Number)
{
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "SELECT * FROM Cars WHERE Number = '" + Number + "'";
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	Car* c = NULL;
	if (sqlite3_step(stmt) != SQLITE_DONE)
	{
		c = new Car(
			sqlite3_column_int(stmt, 0),
			string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))),
			sqlite3_column_int(stmt, 2),
			sqlite3_column_int(stmt, 3),
			string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))),
			string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5))));
		cout << c->Number << " Ar " << c->X << endl;
	}
	else {
		cout << "There's no Car " << c->Number << " in the system!" << endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	//return c;
}
