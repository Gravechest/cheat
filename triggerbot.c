#include <windows.h>
#include <stdio.h>

char name[40];
char filter[] = "Cou";
INPUT inp;
COLORREF rgb[4];
COLORREF rgbbuf[4];
HANDLE outpHandle;
COORD crd;
char toggle;
char sniper;

void Windows(HWND win,LPARAM lparam){
	GetWindowTextA(win,name,40);
	if(filter[0] == name[0] && filter[1] == name[1] && filter[2] == name[2]){
		HDC cnt = GetDC(win);
		for(;;){
			if(GetAsyncKeyState(0x04) < 0){
				toggle = 1;
				rgbbuf[0] = GetPixel(cnt,960,540);
				if(GetRValue(rgbbuf[0]) == 0 && GetGValue(rgbbuf[0]) == 0 && GetBValue(rgbbuf[0]) == 0){
					rgbbuf[0] = GetPixel(cnt,962,542);
					rgbbuf[1] = GetPixel(cnt,962,538);
					rgbbuf[2] = GetPixel(cnt,958,542);
					rgbbuf[3] = GetPixel(cnt,958,538);
					sniper = 1;
				}
			}
			else{
				toggle = 0;
				sniper = 0;
			}
			if(toggle){
				if(sniper){
					rgb[0] = GetPixel(cnt,962,542);
					rgb[1] = GetPixel(cnt,962,538);
					rgb[2] = GetPixel(cnt,958,542);
					rgb[3] = GetPixel(cnt,958,538);
				}
				else{
					rgb[0] = GetPixel(cnt,960,540);
				}
				if(sniper){
					for(int i = 0;i < 4;i++){
						if(GetRValue(rgb[i]) + 20 < GetRValue(rgbbuf[i]) || GetRValue(rgb[i]) - 20 > GetRValue(rgbbuf[i])){
							inp.mi.dwFlags = 2;
							SendInput(1,&inp,sizeof(inp));
							Sleep(10);
							inp.mi.dwFlags = 4;
							SendInput(1,&inp,sizeof(inp));
							toggle = 0;
							sniper = 0;
							break;
						}
					}
				}
				else{
					if(GetRValue(rgb[0]) + 20 < GetRValue(rgbbuf[0]) || GetRValue(rgb[0]) - 20 > GetRValue(rgbbuf[0])){
						inp.mi.dwFlags = 2;
						SendInput(1,&inp,sizeof(inp));
						Sleep(10);
						inp.mi.dwFlags = 4;
						SendInput(1,&inp,sizeof(inp));
						toggle = 0;
						sniper = 0;
					}
				}
				memcpy(rgbbuf,rgb,sizeof(rgb));
			}
		}
		
	}
	return;
}

void main(){	
	outpHandle = GetStdHandle(-11);
	EnumWindows(&Windows,0);
}
                         
