#include "stdafx.h"
#include "Parking.h"
#include "Car.h"
#include "time.h"
#include <string>
#include <ctime>
using namespace std;

Parking::Parking()
{
  rate = 5; // owners have to pay 5 rubbles a minute
  washCarPrice = 900;
  changeTiresPrice = 2700;
}

int Parking::park_car(Car* car)
{
	for (int i = 0; i < 20; i++)
	{
		if (Parked[i] == NULL)
		{
			Parked[i] = car;
			car->write_point_time_in(time(0));
			return 0;
		}
	};
  return 1;
}

void Parking::unpark_car(string plate_)
{
	for (int i = 0; i < 20; i++)
	{
		if (Parked[i]->plate == plate_) 
    {
      Parked[i] = NULL;
      break;
    }
	};
}

Car* Parking::get_car_info(string plate_)
{
	for (int i = 0; i < 20; i++)
	{
		if (Parked[i]->plate == plate_)
			return Parked[i];
	};
  return NULL;
}

int Parking::calculate_costs(string plate_)
{
  Car* car = this->get_car_info(plate_);
  time_t seconds = time(0) - car->get_time_in();
  int totalPayment = 0;
  totalPayment += this->rate * seconds;
  if (car->washCar) {
    totalPayment += washCarPrice;
  }
  if (car->changeTires) {
    totalPayment += changeTiresPrice;
  }
  // for testing purposes use seconds
  // int minutes = seconds / 60;
  return totalPayment;
}
