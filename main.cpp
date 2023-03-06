#include <iostream>
#include <Windows.h>
#include <Tlhelp32.h>
#include <vector>
#include <string>
#include <wchar.h>
#include <thread>

#include "Offsets.h"
#include "memory.h"


bool godmode = false;
bool roundskip = false;
bool unlimited_points = false;
bool inf_ammo = false;
bool inf_grenades = false;

void print_features()
{
	if (godmode) std::cout << "[1] GODMODE | ON\n"; else std::cout << "[1] GODMODE | OFF\n";
	if (roundskip) std::cout << "[2] ROUND SKIP | ON\n"; else std::cout << "[2] ROUND SKIP | OFF\n";
	if (unlimited_points) std::cout << "[3] UNLIMITED POINTS | ON\n"; else std::cout << "[3] UNLIMITED POINTS | OFF\n";
	if (inf_ammo) std::cout << "[4] INFINITE AMMO | ON\n"; else std::cout << "[4] INFINITE AMMO | OFF\n";
	if (inf_grenades) std::cout << "[5] INFINITE GRENADES | ON\n"; else std::cout << "[5] INFINITE GRENADES | OFF\n";
}

void cheat()
{
	const auto mem = Memory("plutonium-bootstrapper-win32.exe");
	const auto baseadd = mem.GetModuleAddress("plutonium-bootstrapper-win32.exe");

	while (true)
	{
		if (godmode)
		{
			// Crashes game
			//const char patch[1] = { 0x90 };
			//mem.Write<char[1]>(baseadd + offsets::godmode, patch);
			godmode = false;
		}
		//else
		//{
		//	//const char op[6] = { 0x29, 0xB7, 0xA8, 0x01, 0x00, 0x00 };
		//	//mem.Write<char[6]>(baseadd + offsets::godmode, op);
		//}

		if (roundskip)
		{
			// This shit is so bad
			// Not even a real round skip lol its just visually changing the round
			const auto round = mem.Read<std::int32_t>(baseadd + offsets::roundskip);
			// Very shitty method but it works
			Sleep(5000);
			mem.Write<std::int32_t>(baseadd + offsets::roundskip, round + 1);
		}

		if (unlimited_points)
		{
			mem.Write<std::int32_t>(baseadd + offsets::points, 133700);
		}

		if (inf_ammo)
		{
			// Could have just found a base near 'weapon1_ammo' and used a for loop since theyre all 4-8 bytes apart from each other
			// But im too lazy
			mem.Write<std::int32_t>(baseadd + offsets::weapon1_ammo, 999);
			mem.Write<std::int32_t>(baseadd + offsets::weapon2_ammo, 999);
			mem.Write<std::int32_t>(baseadd + offsets::weapon3_ammo, 999);
		}

		if (inf_grenades)
		{
			mem.Write<std::int32_t>(baseadd + offsets::grenades, 2);
		}
		Sleep(100);
	}
}

void tool()
{
	while (true)
	{
		system("CLS");
		std::cout << "Bo2 Plutonium Zombies Tool | By Siv#3400\n\n";
		print_features();

		std::cout << "\nSelect: ";
		int selected = 0;
		std::cin >> selected;

		switch (selected)
		{
		case 1:
		{
			godmode = !godmode;
			break;
		}
		case 2:
		{
			roundskip = !roundskip;
			break;
		}
		case 3:
		{
			unlimited_points = !unlimited_points;
			break;
		}
		case 4:
		{
			inf_ammo = !inf_ammo;
			break;
		}
		case 5:
		{
			inf_grenades = !inf_grenades;
			break;
		}
		}
	}
}

int main()
{
	SetConsoleTitle("issa parade inside my city yeaahh");

	std::thread cheat_thread(cheat);
	std::thread tool_thread(tool);

	cheat_thread.detach();
	tool_thread.detach();

	while (true)
	{
		Sleep(1000);
	}
	return 0;
}
