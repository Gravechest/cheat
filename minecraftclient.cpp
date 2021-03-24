#include <iostream>
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")
#include <vector>
#include <WS2tcpip.h>
char yeet;
char map[100];
char buf[25555];
char inp[255];
std::vector<char> packet;

void writevarint(std::vector<char>* yeet, int val, bool status = false) {
	int i = 0;
	do {
		char temp = (char)(val & 0b01111111);
		val >>= 7;
		if (val != 0) {
			temp |= 0b10000000;
		}
		if (status == false) {
			yeet->push_back(temp);
		}
		else {
			yeet->insert(yeet->begin() + i, temp);
			i++;
		}
	} while (val != 0);
}
void sendchatpacket(char inp[], SOCKET sock) {
	packet.clear();
	packet.push_back(3);
	writevarint(&packet, strlen(inp));
	for (int i = 0; i < strlen(inp); i++) {
		packet.push_back(inp[i]);
	}
	writevarint(&packet, packet.size(), true);
	send(sock, packet.data(), packet.size(), 0);
}
void name(char inp[]) {
	writevarint(&packet, strlen(inp));
	for (int i = 0; i < strlen(inp); i++) {
		packet.push_back(inp[i]);
	}
}
int main() {
	writevarint(&packet, 0);
	writevarint(&packet, 754);
	writevarint(&packet, 0);
	packet.push_back(0);
	packet.push_back(0);
	packet.push_back(1);
	writevarint(&packet, packet.size(), true);
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	WSAStartup(ver, &data);										 
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET sock2 = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in adres;
	adres.sin_port = htons(25565);
	adres.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.2.10", &adres.sin_addr);
	connect(sock, (sockaddr*)&adres, sizeof(adres));
	send(sock, packet.data() , packet.size(), 0);
	packet.clear();
	packet.push_back(1);
	writevarint(&packet, 0);
	send(sock, packet.data(), packet.size(), 0);
	recv(sock, buf, 255, 0);
	for (int i = 0; i < 255; i++) {
		std::cout << buf[i];
	}
	connect(sock2, (sockaddr*)&adres, sizeof(adres));
	std::cin >> inp;
	memset(buf, 0, 255);
	packet.clear();
	writevarint(&packet, 0);
	writevarint(&packet, 754);
	writevarint(&packet, 0);
	packet.push_back(0);
	packet.push_back(0);
	packet.push_back(2);
	writevarint(&packet, packet.size(), true);
	send(sock2, packet.data(), packet.size(), 0);
	packet.clear();
	packet.push_back(0);
	name(inp);
	writevarint(&packet, packet.size(), true);
	send(sock2, packet.data(), packet.size(), 0);
	for (int i = 0; i < 80;i++) {
		recv(sock2, buf, 255, 0);
		for (int i = 0; i < 255; i++) {
			std::cout << buf[i];
		}
		memset(buf, 0, 255);
	}
	packet.clear();
	std::cin >> inp;
	while (true) {
		sendchatpacket(inp, sock2);
	}
}
