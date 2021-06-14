#include "Graphics.h"
#include "GunGame.h"

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
	cout << "Введите количество вражеских шаров: ";
	cin >> amountOfEnemyBolls;

	Boll boll(amountOfEnemyBolls);
	Gun gun(0, &boll, amountOfEnemyBolls);

	while (!gun.EndOfGame(&boll, amountOfEnemyBolls))
	{
		int angle;
		cout << "Введите градус поворота: ";
		cin >> angle;
		angle = angle % 360;
		if (angle < 0)
		{
			angle = 360 + angle;
		}

		Gun gun(0, &boll, amountOfEnemyBolls);
		gun.Shot(angle, &boll, amountOfEnemyBolls);


		Graphics::Osi();
	}

	cout << "Конец игры!";
	

	return 0;
}