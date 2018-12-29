#include "stdafx.h"
#include "Car.h"
#include "Parking.h"
#include <time.h>
#include <ctime>
#include <iterator>
#include <iostream>
#include <string>
using namespace std;


Car::Car(string plate_, bool washCar_, bool changeTires_)
{
  plate = plate_;
  changeTires = changeTires_;
  washCar = washCar_;
}

void Car::write_point_time_in(time_t time_in_)
{
	time_in = time_in_;
}

time_t Car::get_time_in()
{
	return time_in;
}


void Car::print_readable_time_in()
{
/*	tm* local = localtime(&time_in);
	cout << (local->tm_year + 1900) << '-' 
        << (local->tm_mon + 1) << '-'
        << local->tm_mday
        << " "
        << local->tm_hour
        << ":"
        << local->tm_min
        << "\n";*/
}
