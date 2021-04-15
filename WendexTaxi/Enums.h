#pragma once

enum CarTypes
{
	Economy=1, 
	Comfort, 
	ComfortPlus, 
	Business

};

enum DriverStatus {
	NotRiding = 0,
	IsRiding = 1,
	NotWorking = 3,
	IsWorking = 4
};
enum OrderStatus {
	DriverNotSet = -1,
	InProccess = 0,
	Finished = 1
};