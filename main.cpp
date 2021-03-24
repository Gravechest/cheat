#include <windows.h>
#include <iostream>
const int MG = 12;
const int FR = 99;
float cheatx[12] = {
	0,10,32,60,10,
	50,55,55,55,55,
	50,50
};
float cheaty[12] = {
	0,-20,-35,0,90,
	50,-50,-50,-80,-40,
	-40,0
};
int main() {
	INPUT inp;
	inp.type = INPUT_MOUSE;
	inp.mi.dwFlags = MOUSEEVENTF_MOVE;
	Sleep(1);
	while (true) {
		int i = 0;
		while (GetKeyState(VK_LBUTTON) < 0 && i <= MG) {
			inp.mi.dy = cheatx[i];
			inp.mi.dx = cheaty[i];
			SendInput(1, &inp, sizeof(inp));
			Sleep(FR);
			i++;
		}
	}
}
