#include "DBShell.h"
#include "sqlite/sqlite3.h"
#include <iostream>
#include <vector>
#include "PaymentMethod.h"
#include "Admin.h"


#pragma warning(disable : 4996)
using namespace std;
const char* path = "WendexTaxiDB.db";

int getDriversCarType(Driver* d);
void ClearPayments(Passenger* p);
void ClearAddresses(Passenger* p);
bool CheckIsBlocked(Passenger* p);
bool CheckIsBlocked(Driver* d);
bool CheckIsValidated(int CarID);
bool CheckIsInARide(Passenger* p);
static int Callback(void*, int count, char** argv, char** columns);

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
		cout << "Passenger " << p->Name << " !" << endl;
	}
	else {
		cout << "There's no Passenger " << p->Name << " in the system!" << endl;
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
		cout << "Driver " << d->Name << " !" << endl;
	}
	else {
		cout << "There's no Driver " << d->Name << " in the system!" << endl;
	}

	sqlite3_close(db);
	sqlite3_finalize(stmt);


	return d;
}

Admin* DBShell::getAdmin(string Name)
{
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "SELECT * FROM Admins WHERE Name = '" + Name + "'";
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	Admin* a = NULL;
	if (sqlite3_step(stmt) != SQLITE_DONE)
	{
		a = new Admin(sqlite3_column_int(stmt, 0), Name);
		cout << "Admin " << a->Name << " !" << endl;
	}
	else {
		cout << "There's no Admin " << a->Name << " in the system!" << endl;
	}

	sqlite3_close(db);
	sqlite3_finalize(stmt);

	return a;
}

Driver* DBShell::findDriver(CarTypes type)
{
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = " SELECT Drivers.Name FROM Drivers INNER JOIN Cars on Drivers.CarID = Cars.ID WHERE"
		" isWorking = 1 AND isRiding = 0 AND isBlocked = 0 AND"
		" Cars.CarTypeID = " + to_string(type);
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	Driver* d = NULL;
	if (sqlite3_step(stmt) != SQLITE_DONE)
	{
		d = getDriver(string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0))));
	}
	else {
		cout << "There's no such a type of car now available in the system, please wait or change the type!" << endl;
	}

	sqlite3_close(db);
	sqlite3_finalize(stmt);


	return d;
}

int getNumberOfWaterBottles(int carID) {
	int nBottels = -1;
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = " SELECT WaterBottles FROM Cars WHERE CarTypeID = 2 AND ID = "+to_string(carID);
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	if (sqlite3_step(stmt) != SQLITE_DONE) nBottels = sqlite3_column_int(stmt, 0);

	sqlite3_close(db);
	sqlite3_finalize(stmt);

	return nBottels;
};
void updateNumberOfWaterBottles(int carID) {
	int n = getNumberOfWaterBottles(carID);
	if (n > 1) {

		bool decrease = !(bool)(rand() % 100); // 1/100 chance to decrease
		if (decrease)
		{
			sqlite3* db;
			int exit = sqlite3_open(path, &db);
			sqlite3_stmt* stmt;
			string query = "UPDATE Cars SET WaterBottles = " + to_string(--n)
				+ " WHERE CarTypeID = 2 AND ID = " + to_string(carID);
			sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

			if (sqlite3_step(stmt) == SQLITE_DONE)
				cout << "Water bottles left in this car: " + to_string(n)<<endl;

			sqlite3_close(db);
			sqlite3_finalize(stmt);
		}
	}

};

void DBShell::MoveDriver(Driver* driver, int x) 
{
	sqlite3* db;
	char* er;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;


	string query = " UPDATE Cars SET X = '" + to_string(x) + "' WHERE ID = '" + to_string(driver->CarID) + "'";

	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);

	cout << driver->Name << " moved to X= " << x << endl;;

	sqlite3_close(db);
	sqlite3_finalize(stmt);
	updateNumberOfWaterBottles(driver->CarID);
}

void DBShell::PrintOrdersP(Passenger* passenger)
{
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = " SELECT Orders.FromX, Orders.ToX, Orders.UnixTime, Drivers.Name, CarTypes.Type, Orders.ID "
		" FROM Orders "
		" INNER JOIN Drivers ON Orders.DriverID = Drivers.ID, "
		" CarTypes ON Orders.CarTypeID = CarTypes.ID "
		" WHERE Orders.PassengerID = " + to_string(passenger->ID) +
		" AND Orders.Status = 1";
	cout << passenger->Name << "'s orders:" << endl;
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	while (sqlite3_step(stmt) != SQLITE_DONE) {
		time_t temp = sqlite3_column_int(stmt, 2);
		cout << "ID: " << sqlite3_column_int(stmt, 5)
			<< " From: " << sqlite3_column_int(stmt, 0)
			<< " To:  " << sqlite3_column_int(stmt, 1)
			<< " At : " << std::asctime(localtime(&temp))
			<< " Driver: " << sqlite3_column_text(stmt, 3)
			<< " Car type: " << sqlite3_column_text(stmt, 4)
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
		" WHERE Orders.DriverID = " + to_string(driver->ID) +
		" AND Orders.Status = 1";
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

Car* DBShell::GetCar(int carId)
{
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "SELECT * FROM Cars WHERE ID = " + to_string(carId);
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
	}
	else {
		cout << "There's no Car with the id= " << carId << " in the system!" << endl;
	}

	sqlite3_close(db);
	sqlite3_finalize(stmt);
	return c;
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
	string query = " SELECT Orders.ID, Passengers.Rating, Orders.FromX, Orders.ToX, Orders.CarTypeID FROM Orders "
		" INNER JOIN Passengers on Passengers.ID = Orders.PassengerID "
		" WHERE Status = -1 and CarTypeID = " + to_string(getDriversCarType(d));
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	while (sqlite3_step(stmt) != SQLITE_DONE) {

		orders.push_back(new Order(sqlite3_column_double(stmt, 0),
			sqlite3_column_int(stmt, 1),
			sqlite3_column_int(stmt, 2),
			sqlite3_column_int(stmt, 3),
			((CarTypes)sqlite3_column_int(stmt, 4))));
	}


	sqlite3_close(db);
	sqlite3_finalize(stmt);

	return orders;
}


void UpdateOrderStatus(int driverID, Order* o, OrderStatus status) {
	sqlite3* db;
	char* er;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "UPDATE ORDERS Set Status = " + to_string(status)
		+ ", DriverID = " + to_string(driverID) + " WHERE ID = " + to_string(o->ID);

	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);

	sqlite3_close(db);
	sqlite3_finalize(stmt);
}

void DBShell::UpdateDriverStatus(Driver* d, DriverStatus status) {

	sqlite3* db;
	char* er;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query;

	switch (status)
	{
	case NotRiding:
		query = "UPDATE Drivers Set IsRiding = 0 WHERE ID = " + to_string(d->ID);
		break;
	case IsRiding:
		query = "UPDATE Drivers Set IsRiding = 1 WHERE ID = " + to_string(d->ID);
		break;
	case NotWorking:
		query = "UPDATE Drivers Set IsWorking = 0 WHERE ID = " + to_string(d->ID);
		break;
	case IsWorking:
		query = "UPDATE Drivers Set IsWorking = 1 WHERE ID = " + to_string(d->ID);
		break;
	}

	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);

	sqlite3_close(db);
	sqlite3_finalize(stmt);

}

void DBShell::StartRide(Driver* d, Order* o)
{
	if (CheckIsBlocked(d))
		throw new exception("Driver is blocked");
	if (!CheckIsValidated(d->CarID))
		throw new exception("Car is not validated");
	UpdateDriverStatus(d, IsRiding);
	UpdateOrderStatus(d->ID, o, InProccess);
}

void DBShell::FinishRide(Driver* d, Order* o)
{
	UpdateDriverStatus(d, NotRiding);
	UpdateOrderStatus(d->ID, o, Finished);
}


vector<PaymentMethod*> DBShell::GetListOfPayments()
{
	vector <PaymentMethod*> payments;
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = " SELECT * FROM PaymentMethods";

	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	while (sqlite3_step(stmt) != SQLITE_DONE) {
		payments.push_back(new PaymentMethod(sqlite3_column_int(stmt, 0),
			string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)))));
	}

	sqlite3_close(db);
	sqlite3_finalize(stmt);
	return payments;
}

void  DBShell::SetListOfPayments(Passenger* p, vector<PaymentMethod*> payments)
{
	ClearPayments(p);

	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "INSERT INTO PaymentsPassengers (PassengerID, PaymentID) VALUES";
	for (PaymentMethod* payment : payments)
	{
		query += "(" + to_string(p->ID) + ", " + to_string(payment->ID) + "),";
	}
	query.at(query.length() - 1) = ';';
	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);

	sqlite3_close(db);
	sqlite3_finalize(stmt);
}

vector<int> DBShell::GetListOfPinnedAdresses(Passenger* p)
{
	vector <int> addresses;
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = " SELECT X FROM PinnedAddresses where PassengerID = " + to_string(p->ID);

	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	while (sqlite3_step(stmt) != SQLITE_DONE)
		addresses.push_back(sqlite3_column_int(stmt, 0));

	sqlite3_close(db);
	sqlite3_finalize(stmt);
	return addresses;
}

void DBShell::SetListOfPinnedAdresses(Passenger* p, vector<int> addresses)
{
	ClearAddresses(p);

	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "INSERT INTO PinnedAddresses (PassengerID, X) VALUES ";
	for (int address : addresses)
	{
		query += "(" + to_string(p->ID) + ", " + to_string(address) + "),";
	}
	query.at(query.length() - 1) = ';';
	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);

	sqlite3_close(db);
	sqlite3_finalize(stmt);
}

Order* DBShell::GetOrderByID(int orderID)
{
	Order* order = NULL;
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = " SELECT Orders.ID, Passengers.Rating, Orders.FromX, Orders.ToX, Orders.CarTypeID FROM Orders "
		" INNER JOIN Passengers on Passengers.ID = Orders.PassengerID "
		" WHERE Orders.ID = " + to_string(orderID);
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

	if (sqlite3_step(stmt) != SQLITE_DONE) {

		order = new Order(sqlite3_column_double(stmt, 0),
			sqlite3_column_int(stmt, 1),
			sqlite3_column_int(stmt, 2),
			sqlite3_column_int(stmt, 3),
			((CarTypes)sqlite3_column_int(stmt, 4)));
	}

	sqlite3_close(db);
	sqlite3_finalize(stmt);

	return order;
}

void DBShell::Block(Driver* driver, bool block)
{
	sqlite3* db;
	char* er;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "UPDATE Drivers SET IsBlocked = " + to_string((int)block) + " WHERE ID = " + to_string(driver->ID);

	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);

	sqlite3_close(db);
	sqlite3_finalize(stmt);
}

void DBShell::Block(Passenger* passenger, bool block)
{
	sqlite3* db;
	char* er;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "UPDATE Passengers SET IsBlocked = " + to_string((int)block) + " WHERE ID = " + to_string(passenger->ID);

	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);

	sqlite3_close(db);
	sqlite3_finalize(stmt);
}

void DBShell::Validate(Car* car, bool validate)
{
	sqlite3* db;
	char* er;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "UPDATE Cars SET IsValidated = " + to_string((int)validate) + " WHERE ID = " + to_string(car->ID);

	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);

	sqlite3_close(db);
	sqlite3_finalize(stmt);
}


void PrintAll(string tableName) {
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	cout << "TABLE \"" << tableName << "\" :" << endl;
	string query = " SELECT * FROM " + tableName;
	sqlite3_exec(db, query.c_str(), Callback, NULL, NULL);

	sqlite3_close(db);
}

void DBShell::ShowDB()
{
	PrintAll("Drivers");
	PrintAll("Passangers");
	PrintAll("Cars");
	PrintAll("Orders");
}
static int Callback(void*, int count, char** argv, char** columns) {

	for (int i = 0; i < count; i++)
	{
		cout << columns[i] << ": " << (argv[i] == NULL ? " " : argv[i]) << endl;
	}
	cout << endl;
	return 0l;

}
void ClearPayments(Passenger* p) {

	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "DELETE FROM PaymentsPassengers WHERE PassengerID = " + to_string(p->ID);

	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);

	sqlite3_close(db);
	sqlite3_finalize(stmt);
}

void ClearAddresses(Passenger* p) {

	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "DELETE FROM PinnedAddresses WHERE PassengerID = " + to_string(p->ID);

	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);

	sqlite3_close(db);
	sqlite3_finalize(stmt);
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

void DBShell::OrderRide(Passenger* p, int from, int to, CarTypes type)
{
	if (CheckIsBlocked(p))
		throw new exception("Passenger is blocked"); 
	if (CheckIsInARide(p))
			throw new exception("Passenger is in a Ride already");

	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	char* er;
	sqlite3_stmt* stmt;
	string query = "INSERT INTO Orders "
		"('PassengerID', 'CarTypeID', 'FromX', 'ToX', 'UnixTime') "
		" VALUES(" + to_string(p->ID) + ", " + to_string(type) + ", " + to_string(from)
		+ ", " + to_string(to) + ", " + to_string(std::time(0)) + ");";

	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);


	sqlite3_close(db);
	sqlite3_finalize(stmt);
}

bool CheckIsBlocked(Passenger* p) {
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "SELECT isBlocked FROM Passengers WHERE ID = " + to_string(p->ID);
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
	bool b = true;
	if (sqlite3_step(stmt) != SQLITE_DONE) b = sqlite3_column_int(stmt, 0);
	else throw new exception("Passenger doesn't exist");

	sqlite3_close(db);
	sqlite3_finalize(stmt);

	return b;
};
bool CheckIsInARide(Passenger* p) {
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = " SELECT * FROM Orders WHERE Status = 0 and PassengerID =" + to_string(p->ID);
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
	bool b = false;
	if (sqlite3_step(stmt) != SQLITE_DONE) b = true;

	sqlite3_close(db);
	sqlite3_finalize(stmt);

	return b;
};
bool CheckIsBlocked(Driver* p) {
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "SELECT isBlocked FROM Drivers WHERE ID = " + to_string(p->ID);
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
	bool b = true;
	if (sqlite3_step(stmt) != SQLITE_DONE) b = sqlite3_column_int(stmt, 0);
	else throw new exception("Driver doesn't exist");

	sqlite3_close(db);
	sqlite3_finalize(stmt);

	return b;
};
bool CheckIsValidated(int CarID) {
	sqlite3* db;
	int exit = sqlite3_open(path, &db);
	sqlite3_stmt* stmt;
	string query = "SELECT IsValidated FROM Cars WHERE ID = " + to_string(CarID);
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
	bool b = true;
	if (sqlite3_step(stmt) != SQLITE_DONE) b = sqlite3_column_int(stmt, 0);
	else throw new exception("Car doesn't exist");

	sqlite3_close(db);
	sqlite3_finalize(stmt);

	return b;
};