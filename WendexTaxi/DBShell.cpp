#include "DBShell.h"
#include "sqlite/sqlite3.h"
#include <iostream>
#include <vector>

#pragma warning(disable : 4996)
using namespace std;
const char* path = "WendexTaxiDB.db";

int getDriversCarType(Driver* d);

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
		cout <<"Passenger "<< p->Name << " !" << endl;
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
		cout << "Driver "<<d->Name << " !" << endl;
	}
	else {
		cout << "There's no Driver " << d->Name << " in the system!" << endl;
	}

	sqlite3_close(db);
	sqlite3_finalize(stmt);


	return d;
}

Driver* DBShell::findDriver(CarTypes type)
{
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = " Select Drivers.Name FROM Drivers INNER JOIN Cars on Drivers.CarID = Cars.ID where Cars.CarTypeID = " + to_string(type);
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	Driver* d = NULL;
	if (sqlite3_step(stmt) != SQLITE_DONE)
	{
		d = getDriver(string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0))));
	}
	else {
		cout << "There's no such a type od car now" << d->Name << " in the system!" << endl;
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

void DBShell::PrintOrdersP(Passenger* passenger)
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
		time_t temp = sqlite3_column_int(stmt, 2);
		cout << "From: " << sqlite3_column_int(stmt, 0)
			<< " To:  " << sqlite3_column_int(stmt, 1)
			<< " At : " << std::asctime(localtime(&temp))
			<< " Driver: "<< sqlite3_column_text(stmt, 3)
			<< " Car type: "<< sqlite3_column_text(stmt, 4)
			<< endl;
	}
	
	sqlite3_close(db);
	sqlite3_finalize(stmt);

}

void DBShell::PrintOrdersD(Driver* driver)
{
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = " SELECT Orders.FromX, Orders.ToX, Orders.UnixTime, Passengers.Name, CarTypes.Type "
		" FROM Orders "
		" INNER JOIN Drivers ON Orders.DriverID = Drivers.ID, "
		" CarTypes ON Orders.CarTypeID = CarTypes.ID,  "
		" Passengers ON Orders.PassengerId = Passengers.ID"
		" WHERE Orders.DriverID = " + to_string(driver->ID);
	cout << driver->Name << "'s orders:" << endl;
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
	
	while (sqlite3_step(stmt) != SQLITE_DONE) {
		time_t temp = sqlite3_column_int(stmt, 2);
		cout << "From: " << sqlite3_column_int(stmt, 0)
			<< " To:  " << sqlite3_column_int(stmt, 1)
			<< " At : " << std::asctime(localtime(&temp))
			<< " Passenger: " << sqlite3_column_text(stmt, 3)
			<< " Car type: " << sqlite3_column_text(stmt, 4)
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
	
	sqlite3_close(db);
	sqlite3_finalize(stmt);
}

int DBShell::GetPassengerCoordinates(Passenger* p) {
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	char* er;
	sqlite3_stmt* stmt;
	string query = "Select Cars.X From Cars "
		"INNER JOIN Drivers on Drivers.CarID = Cars.ID "
		"INNER JOIN Orders on Orders.DriverID = Drivers.ID "
		"Where Orders.Status = 0 AND Orders.PassengerID = " + to_string(p->ID);

	int x = NULL;
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

	if (sqlite3_step(stmt) != SQLITE_DONE) 
	{
		x = sqlite3_column_int(stmt, 0);
	}

	sqlite3_close(db);
	sqlite3_finalize(stmt);
	return x;
}

vector <Order*> DBShell::GetOrders(Driver* d)
{
	vector<Order*> orders;

	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = " SELECT Orders.ID, Passengers.Rating, Orders.FromX, Orders.ToX FROM Orders "
		" INNER JOIN Passengers on Passengers.ID = Orders.PassengerID "
		" WHERE Status = -1 and CarTypeID = " + to_string(getDriversCarType(d));
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	while (sqlite3_step(stmt) != SQLITE_DONE) {

		orders.push_back(new Order(sqlite3_column_double(stmt, 0),
			sqlite3_column_int(stmt, 1),
			sqlite3_column_int(stmt, 2),
			sqlite3_column_int(stmt, 3)));
	}


	sqlite3_close(db);
	sqlite3_finalize(stmt);

	return orders;
}

int getDriversCarType(Driver* d) {
	int carType = NULL;
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = " Select CarTypeID from CarTypes INNER join Cars on CarTypes.ID = Cars.CarTypeID "
		" INNER join Drivers on Cars.ID = Drivers.ID where Drivers.ID = " + to_string(d->ID);
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	if (sqlite3_step(stmt) != SQLITE_DONE)
		carType = sqlite3_column_int(stmt, 0);
	else
		cout << "Error get car type";

	sqlite3_close(db);
	sqlite3_finalize(stmt);
	return carType;
}

void DBShell::OrderRide(Passenger* p, Driver* d, int from, int to, CarTypes type)
{
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	char* er;
	sqlite3_stmt* stmt;
	string query = "INSERT INTO Orders "
	"('PassengerID', 'DriverID', 'CarTypeID', 'FromX', 'ToX', 'UnixTime') "
	" VALUES("+to_string(p->ID)+", "+ to_string(d->ID) +", "+ to_string(type) +", "+ to_string(from) 
		+", "+ to_string(to) +", "+to_string(std::time(0))+");";

	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);

	
	sqlite3_close(db);
	sqlite3_finalize(stmt);
}
