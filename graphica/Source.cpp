#include "Graphics.h"
#include "GunGame.h"
#include <conio.h>


using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	setlocale(LC_ALL, "rus");
	SetConsoleTitle("Graphics");
	system("mode con cols=150 lines=60"); //Установить размер окна в знакоместах
	HANDLE HandleCons = ::GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hWnd = GetConsoleWindow(); //Получить ссылку на окно

	Graphics::InitGraphics(hWnd);
	Sleep(50);
	int wid = Graphics::GetWid();
	int heg = Graphics::GetHeg();

	int amountOfEnemyBolls;
	cout << "Управление пушкой: поворот - клавиши A и D, выстрел - ПРОБЕЛ." << endl << "Введите количество вражеских шаров (от 0 до 100): ";
	do
	{
		cin >> amountOfEnemyBolls;
	} while (amountOfEnemyBolls < 0 || amountOfEnemyBolls > 100);
	//Graphics::Set_brush(RGB(0, 0, 0), 0);
	Graphics::Set_pen(RGB(0, 255, 0), 3);
	Graphics::Set_brush(RGB(0, 255, 0), 0);
	Rectangle(Graphics::dc, 0, 0, Graphics::GetWid(), Graphics::GetHeg());

	Boll boll(amountOfEnemyBolls);
	Gun gun(0, 1);
	int angle = 0;
	while (!gun.EndOfGame(&boll, amountOfEnemyBolls))
	{
		
		//cout << "Введите градус поворота: ";
		//cin >> angle;
		unsigned char key;
		key = _getch();
		if (key == 101 || key == 69)
		{
			boll.VisBoll();
			continue;
		}
		Gun gun1(angle, 0);
		if (key == 'a' || key == 'A' || key == 228 || key == 148)
			angle -= 3;
		if (key == 'd' || key == 'D' || key == 162 || key == 130)
			angle += 3;
		angle = angle % 360;
		if (angle < 0)
		{
			angle = 360 + angle;
		}
		Gun gun(angle, 1);
		if (key == ' ')
		gun.Shot(angle, &boll, amountOfEnemyBolls);


		//Graphics::Osi();
	}

	system("cls");
	//COORD cpos = { wid / 2 , heg / 2};
	//SetConsoleCursorPosition(HandleCons, cpos);
	cout << "Конец игры!";
	_getch();
	

	return 0;
}