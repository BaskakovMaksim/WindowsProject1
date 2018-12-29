#include <iostream>
#include <list>
#include <string>
#include "Car.h"
using namespace std;

class Parking
{
public:
  int rate; // amount of rubbles in minute
  int washCarPrice;
  int changeTiresPrice;


	Car* Parked[20];

	Parking();

	int park_car(Car* car); // Добавление машины на парковку
	// void show_and_delete_car(string plate_); // Выдача машины владельцу
	Car* get_car_info(string plate_); // Просмотр информации по автомобилю
	int calculate_costs(string plate_); // Рассчитать затраты клиента
	void unpark_car(string plate_); // Выдача машины владельцу
};
