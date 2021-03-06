#include "stdafx.h"
#include "WindowsProject1.h"
#include "Car.h"
#include "Parking.h"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

HWND hWndMain = NULL;		//Основное окно проги
HWND hWndChild = NULL;		//Любое дочернее окно (в моём примере - окно "Парковка")
MSG  msg;					//Сообщение от окна

string plate;
Parking parking;
int commandNumber;

BOOL CALLBACK ParkingProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {	//Обрабатывает сообщения от дочернего окна 
	TCHAR Buffer[16];			//Буфер будет хранить до 16 символов в поле для ввода. Например, сюда пойдёт номер машины перед тем, как перевести его в переменную "plate".
	switch (msg)
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDCANCEL:						//Если нажали Отмена, закрыть окно :)
			EndDialog(hWndChild, wParam);
			return TRUE;

			case IDOK:							//При ОК:
				SendDlgItemMessage(hWndChild,	//Считываем в буфер то, что введено в поле "Номер" - его ID IDC_EDIT1
					IDC_EDIT1,
					EM_GETLINE,
					(WPARAM)0,
					(LPARAM)Buffer);
				plate = WideCharToMultiByte(CP_UTF8, 0, Buffer, -1, NULL, 0, NULL, NULL);	//Переводим буфер из TCHAR в string
				bool washCar = false;
				if (IsDlgButtonChecked(hWndChild, WASH_YES) == BST_CHECKED) washCar = true;	//Проверяем состояние кнопок
				bool changeTires = false;
				if (IsDlgButtonChecked(hWndChild, TIRE_YES) == BST_CHECKED) changeTires = true;
				Car car(plate, washCar, changeTires);
				parking.park_car(&car);
				MessageBox(hWndChild, L"Машина припаркована!", L"Успех", MB_OK);			//Сообщаем об успехе новым окошком
				EndDialog(hWndChild, wParam);

		}
	return FALSE;
}

BOOL CALLBACK DeleteProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {	//Обрабатывает сообщения от дочернего окна 
	TCHAR Buffer[16];			//Буфер будет хранить до 16 символов в поле для ввода. Например, сюда пойдёт номер машины перед тем, как перевести его в переменную "plate".
	switch (msg)
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:						//Если нажали Отмена, закрыть окно :)
			EndDialog(hWndChild, wParam);
			return TRUE;

		case IDOK:							//При ОК:
			SendDlgItemMessage(hWndChild,	//Считываем в буфер то, что введено в поле "Номер" - его ID IDC_EDIT1
				IDC_EDIT1,
				EM_GETLINE,
				(WPARAM)0,
				(LPARAM)Buffer);
			plate = WideCharToMultiByte(CP_UTF8, 0, Buffer, -1, NULL, 0, NULL, NULL);	//Переводим буфер из TCHAR в string
			for (int i = 0; i < 20; i++)
			{
				if (parking.Parked[i]->plate.empty()==0)
				{
					if (parking.Parked[i]->plate == plate)
					{
						parking.unpark_car(plate);
						MessageBox(hWndChild, L"Машина может уезжать!!", L"Успех", MB_OK);			//Сообщаем об успехе новым окошком
						EndDialog(hWndChild, wParam);
					}
					else
					{
						MessageBox(hWndChild, L"Машина не найдена", L"Ошибка", MB_OK);			//Сообщаем об успехе новым окошком
						EndDialog(hWndChild, wParam);
					}

				}
			}
			
		}
		return FALSE;
}

BOOL CALLBACK ShowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {	//Обрабатывает сообщения от дочернего окна 
	TCHAR Buffer[16];			//Буфер будет хранить до 16 символов в поле для ввода. Например, сюда пойдёт номер машины перед тем, как перевести его в переменную "plate".
	switch (msg)
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:						//Если нажали Отмена, закрыть окно :)
			EndDialog(hWndChild, wParam);
			return TRUE;

		case IDOK:							//При ОК:
			SendDlgItemMessage(hWndChild,	//Считываем в буфер то, что введено в поле "Номер" - его ID IDC_EDIT1
				IDC_EDIT1,
				EM_GETLINE,
				(WPARAM)0,
				(LPARAM)Buffer);
			plate = WideCharToMultiByte(CP_UTF8, 0, Buffer, -1, NULL, 0, NULL, NULL);	//Переводим буфер из TCHAR в string
			for (int i = 0; i < 20; i++)
			{
				if (parking.Parked[i]->plate.empty() == 0)
				{
					if (parking.Parked[i]->plate == plate)
					{
						parking.get_car_info(plate);
						MessageBox(hWndChild, L"Машина не найдена", L"Информация по автомобилю", MB_OK);			//Сообщаем информацию по автомобилю новым окошком
						EndDialog(hWndChild, wParam);
					}
					else
					{
						MessageBox(hWndChild, L"Машина не найдена", L"Ошибка", MB_OK);			//Сообщаем об ошибке новым окошком
						EndDialog(hWndChild, wParam);
					}

				}
			}

		}
		return FALSE;
}

 BOOL CALLBACK MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		//Обрабатывает сообщения от основного окна
{
	 switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case PARK_CAR:					//Если нажата кнопка "Припарковать машину". PARK_CAR - её ID в ресурсе
			{
				hWndChild = CreateDialog(	//Делаем новое, дочернее окно по шаблону "IDD_PARK" из ресурса
					GetModuleHandle(NULL),
					MAKEINTRESOURCE(IDD_PARK),
					hWndMain,
					(DLGPROC)ParkingProc);
				CheckRadioButton(hWndChild, WASH_YES, WASH_NO, WASH_YES);	//Делаем кнопки выбранными по умолчанию
				CheckRadioButton(hWndChild, TIRE_YES, TIRE_NO, TIRE_YES);
				ShowWindow(hWndChild, SW_SHOW);
				break;
			}

			case DELETE_CAR:
			{
				hWndChild = CreateDialog(	//Делаем новое, дочернее окно по шаблону "IDD_PLATE" из ресурса
					GetModuleHandle(NULL),
					MAKEINTRESOURCE(IDD_PLATE),
					hWndMain,
					(DLGPROC)DeleteProc);
					ShowWindow(hWndChild, SW_SHOW);
				/*cout << "Enter licence plate number: ";
				cin >> plate;
				parking.unpark_car(plate);
				cout << "success" << endl;*/
				break;
			}

			case SHOW_CAR_INFO:
			{
				hWndChild = CreateDialog(	//Делаем новое, дочернее окно по шаблону "IDD_PLATE" из ресурса
					GetModuleHandle(NULL),
					MAKEINTRESOURCE(IDD_PLATE),
					hWndMain,
					(DLGPROC)ShowProc);
				ShowWindow(hWndChild, SW_SHOW);
				/*cout << "Enter licence plate number: ";
				cin >> plate;
				Car* car = parking.get_car_info(plate);
				if (car) {
					car->print_readable_time_in();
				}
				else {
					cout << "No such car" << endl;
				}*/
				break;
			}

			case CALCULATE:
			{
				/*cout << "Enter licence plate number: ";
				cin >> plate;
				cout << parking.calculate_costs(plate) << endl;*/
				break;
			}

			case TERMINATE:
			{
				/*cout << "Goodbye" << endl;*/
				PostQuitMessage(0);
				return 1;
			}
		}
	}
	 return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)

{
	hWndMain = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainProc);
	ShowWindow(hWndMain, SW_SHOW);
	UpdateWindow(hWndMain);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}