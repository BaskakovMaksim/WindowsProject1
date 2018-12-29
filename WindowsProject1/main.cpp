#include "Car.h"
#include "Parking.h"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

enum Menu
{
	PARK_CAR = 1,
	DELETE_CAR = 2,
	SHOW_CAR_INFO = 3,
	CALCULATE = 4,
  TERMINATE = 5
};

int main()
{
	string plate;
	Parking parking;
	int commandNumber;
	cout << PARK_CAR << " - park car" << endl;
	cout << DELETE_CAR << " - return car to it's owner" << endl;
	cout << SHOW_CAR_INFO << " - show car info" << endl;
	cout << CALCULATE << " - calculate costs" << endl;
  cout << TERMINATE << " - terminate" << endl;
	
  while (true) 
  {
    cout << "Please enter the command number: ";
    cin >> commandNumber;
    switch (commandNumber)
    {
      case PARK_CAR:
      {
        cout << "Enter licence plate number: ";
        cin >> plate;
        
        string answer;
        bool washCar = false;
        cout << "Do you want to wash it? (y/n)" << endl;
        cin >> answer;
        if (answer == "y") {
          washCar = true;
        }
        bool changeTires = false;
        cout << "Do you want to change tires? (y/n)" << endl;
        cin >> answer;
        if (answer == "y") {
          changeTires = true;
        }

        Car car(plate, washCar, changeTires);
        parking.park_car(&car);
        cout << "the car is parked" << endl;
        break;
      }
      
      case DELETE_CAR:
      {
        cout << "Enter licence plate number: ";
        cin >> plate;
        parking.unpark_car(plate);
        cout << "success" << endl;
        break;
      }

      case SHOW_CAR_INFO:
      {
        cout << "Enter licence plate number: ";
        cin >> plate;
        Car* car = parking.get_car_info(plate);
        if (car) {
          car->print_readable_time_in();
        } else {
          cout << "No such car" << endl;
        }
        break;
      }

      case CALCULATE:
      {
        cout << "Enter licence plate number: ";
        cin >> plate;
        cout << parking.calculate_costs(plate) << endl;
        break;
      }

      case TERMINATE:
      {
        cout << "Goodbye" << endl;
        return 0;
      }

      default: 
      {
        cout << "Goodbye" << endl;
        return 0;
      }
    }
  }
   
	return 0;
}