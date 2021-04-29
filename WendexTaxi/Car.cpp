#include "Car.h"
#include <iostream>

void Car::ParkInFrontOfTheEntrance() {
    if (CarTypeID == Business) cout << "OK!\n";
    else  cout << "Sorry it's not a business car!\n";
}
