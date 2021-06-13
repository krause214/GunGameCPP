#include "Graphics.h"
#include "GunGame.h"

using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	setlocale(LC_ALL, "rus");
	SetConsoleTitle("Graphics");
	system("mode con cols=55 lines=30"); //Установить размер окна в знакоместах
	HANDLE HandleCons = ::GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hWnd = GetConsoleWindow(); //Получить ссылку на окно

	Graphics::InitGraphics(hWnd);
	Sleep(50);

	//----------------Методы класса Graphics---------------------

	int wid = Graphics::GetWid();
	int heg = Graphics::GetHeg();

	Graphics::Osi();

	cin.get();
	
	return 0;
}