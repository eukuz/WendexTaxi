# Introduction to Programming 2
## Assignment #1
### Eugene Kuzyakhmetov

#### How to set up?

1. Download 
2. Open it in your favorite c++ compiler
3. Compile
4. Run

#### How does it work?

There are 3 types of gateways:
* Passenger
* Driver
* Admin
Users of corresponding types communicate with the system through them.
	
There  are  4  car  types:  Economy,  Comfort, ComfortPlus, Business.

A Passenger can:
* login (via their name)
* see order history
* see payment methods available in the system and updete theit pinned ones
* see and update their pinned addresses
* select any two addresses (from,  to) and carType to check the time and  price  of  the  ride
* order the ride and change pick a payment method for this particular ride
* ask for the current coordinates of the car during the ride
* see the ride in the order history after the end of the ride and ask for the bill of that ride
* A passenger can have multiple mobile devices
    * from any of them they can ask for the current coordinates of the car during the ride
    * a passenger cannot start a ride during another one

A Driver can:
* login (via their name)
* see order history
* see a car
* update status
* check available orders, accept or just don't them.
* have multiple cars
    * Implemented via many-to-many relationship in DB, so the driver actyally have them but cannot switch them at the moment (since it wasn't requested)

An Admin can:
* Print the main tables of DB
* Block ability for passengers to make orders.
* Block ability for drivers to take orders.
* Validate a car (driver cannot take orders while the car they picked is not validated)

