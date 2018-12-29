#ifndef CAR_H
#define CAR_H
#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <time.h>
using namespace std;

class Car
{
public:
  string plate;
  bool washCar;
  bool changeTires;
	time_t time_in;
  
  Car(string plate_, bool washCar_, bool changeTires_);
	void write_point_time_in(time_t time_in);
  time_t get_time_in();
  void print_readable_time_in();
};

#endif