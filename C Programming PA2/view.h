#pragma once
#include <Windows.h>
#include <conio.h>
#include "data.h"

void set_console_option();
void show_default_layout();
void show_map(char[ROW][COL], Point*);
void show_title();
void show_border();
void show_status(Info*);
void show_manual();
void show_rudder();
void show_level(int*);
void show_menu(Info*);
void show_exit();
void show_esc(Info*, int);
void show_key_pressed(int);
void show_item(Info*);
void show_log(Info*);
void show_ending();
void show_fail(Info*);
void show_running(Info*);
void gotoxy(int, int);
void show_phase(Info*);
void update_map(Point*, Info*, int);

void update_map(Point* p, Info* info, int flag) {
	int mx = 3 + p->y, my = 12 + p->x;
	gotoxy(mx, my);
	if (flag)
		printf("!");
	else {
		if (info->map[p->x][p->y] != ' ')
			printf("$");
		else
			printf("%c", info->map[p->x][p->y]);
	}
}

void show_running(Info* info) {
	show_log(info);
	show_level(&info->level);
	show_status(info);
}

void show_fail(Info* info) {
	Sleep(2000);
	int setx = 27, sety = 10, i, ret = 0;

	gotoxy(setx, sety++);
	printf("¦£");
	for (i = 0; i < 45; i++) {
		printf("¦¡");
	}
	printf("¦¤");
	gotoxy(setx, sety++);
	printf("¦¢");
	printf("%-45s", "");
	printf("¦¢");
	for (i = 0; i < 10; i++) {
		gotoxy(setx, sety++);
		printf("¦¢");
		printf("%47s", "¦¢");
	}
	gotoxy(setx, sety++);
	printf("¦¦");
	for (i = 0; i < 45; i++) {
		printf("¦¡");
	}
	printf("¦¥");

	setx += 11;
	sety -= 9;
	gotoxy(setx, sety++);
	printf(" ____    __    ____  __   ");
	gotoxy(setx, sety++);
	printf("( ___)  /__\\  (_  _)(  )  ");
	gotoxy(setx, sety++);
	printf(" )__)  /(__)\\  _)(_  )(__ ");
	gotoxy(setx, sety++);
	printf("(__)  (__)(__)(____)(____)");

	Sleep(2000);
}

void show_log(Info* info) {
	int lx = 68, ly = 12, i;

	if (info->state) {
		gotoxy(lx, ly++);
		printf("¦£");
		for (i = 0; i < 29; i++) {
			printf("¦¡");
		}
		printf("¦¤");
		for (i = 0; i < 7; i++) {
			gotoxy(lx, ly++);
			printf("¦¢");
			printf("%31s", "¦¢");
		}
		gotoxy(lx, ly++);
		printf("¦¦");
		for (i = 0; i < 29; i++) {
			printf("¦¡");
		}
		printf("¦¥");

		lx = 69;
		ly = 13;
		for (i = 0; i < 7; i++) {
			gotoxy(lx, ly++);
			if (info->log.str[i])
				printf("%-25s", info->log.str[i]);
		}
		return;
	}
	for (i = 0; i < 9; i++) {
		gotoxy(lx, ly++);
		printf("                               ");
	}
}

void show_esc(Info* info, int select) {
	int setx = 27, sety = 11, i, ret = 0, tmpy;

	gotoxy(setx, sety++);
	printf("¦£");
	for (i = 0; i < 45; i++) {
		printf("¦¡");
	}
	printf("¦¤");
	gotoxy(setx, sety++);
	printf("¦¢");
	printf("%-45s", "        Are you sure you want to exit?");
	printf("¦¢");
	for (i = 0; i < 10; i++) {
		gotoxy(setx, sety++);
		printf("¦¢");
		printf("%47s", "¦¢");
	}
	gotoxy(setx, sety++);
	printf("¦¦");
	for (i = 0; i < 45; i++) {
		printf("¦¡");
	}
	printf("¦¥");

	setx += 8;
	sety -= 10;

	if (select == 0) {
		tmpy = sety - 1;
		gotoxy(setx, tmpy);
		printf(" ____  ____  ");
		gotoxy(setx, tmpy + 1);
		printf("|_  _||_  _| ");
		gotoxy(setx, tmpy + 2);
		printf("  \\ \\  / /   ");
		gotoxy(setx, tmpy + 3);
		printf("   \\ \\/ /    ");
		gotoxy(setx, tmpy + 4);
		printf("   _|  |_    ");
		gotoxy(setx, tmpy + 5);
		printf("  |______|   ");
		gotoxy(setx, tmpy + 6);
		printf("             ");
	}
	else {
		gotoxy(setx, sety);
		printf(" ____  ____  ");
		gotoxy(setx, sety + 1);
		printf("|_  _||_  _| ");
		gotoxy(setx, sety + 2);
		printf("  \\ \\  / /   ");
		gotoxy(setx, sety + 3);
		printf("   \\ \\/ /    ");
		gotoxy(setx, sety + 4);
		printf("   _|  |_    ");
		gotoxy(setx, sety + 5);
		printf("  |______|   ");
	}

	setx += 18;
	if (select == 1) {
		tmpy = sety - 1;
		gotoxy(setx, tmpy);
		printf(" ____  _____  ");
		gotoxy(setx, tmpy + 1);
		printf("|_   \\|_   _| ");
		gotoxy(setx, tmpy + 2);
		printf("  |   \\ | |   ");
		gotoxy(setx, tmpy + 3);
		printf("  | |\\ \\| |   ");
		gotoxy(setx, tmpy + 4);
		printf(" _| |_\\   |_  ");
		gotoxy(setx, tmpy + 5);
		printf("|_____|\\____| ");
		gotoxy(setx, tmpy + 6);
		printf("               ");
	}
	else {
		gotoxy(setx, sety);
		printf(" ____  _____  ");
		gotoxy(setx, sety + 1);
		printf("|_   \\|_   _| ");
		gotoxy(setx, sety + 2);
		printf("  |   \\ | |   ");
		gotoxy(setx, sety + 3);
		printf("  | |\\ \\| |   ");
		gotoxy(setx, sety + 4);
		printf(" _| |_\\   |_  ");
		gotoxy(setx, sety + 5);
		printf("|_____|\\____| ");
	}
}

void show_phase(Info *info) {
	int setx = 27, sety = 11, i, ret = 0;

	gotoxy(setx, sety++);
	printf("¦£");
	for (i = 0; i < 45; i++) {
		printf("¦¡");
	}
	printf("¦¤");
	gotoxy(setx, sety++);
	printf("¦¢");
	printf("%-45s", "");
	printf("¦¢");
	for (i = 0; i < 10; i++) {
		gotoxy(setx, sety++);
		printf("¦¢");
		printf("%47s", "¦¢");
	}
	gotoxy(setx, sety++);
	printf("¦¦");
	for (i = 0; i < 45; i++) {
		printf("¦¡");
	}
	printf("¦¥");

	setx += 11;
	sety -= 9;

	if (info->level == 0) {
		gotoxy(setx, sety++);
		printf(" ____    __    ___  _  _ ");
		gotoxy(setx, sety++);
		printf("( ___)  /__\\  / __)( \\/ )");
		gotoxy(setx, sety++);
		printf(" )__)  /(__)\\ \\__ \\ \\  / ");
		gotoxy(setx, sety++);
		printf("(____)(__)(__)(___/ (__) ");
	}
	else if (info->level == 1) {
		setx -= 5;
		gotoxy(setx, sety++);
		printf(" _  _ _____ ____ __  __   __   __   ");
		gotoxy(setx, sety++);
		printf("( \\( (  _  (  _ (  \\/  ) /__\\ (  )  ");
		gotoxy(setx, sety++);
		printf(" )  ( )(_)( )   /)    ( /(__)\\ )(__ ");
		gotoxy(setx, sety++);
		printf("(_)\\_(_____(_)\\_(_/\\/\\_(__)(__(____)");
	}
	else if (info->level == 2) {
		setx--;
		gotoxy(setx, sety++);
		printf(" _   _    __    ____  ____  ");
		gotoxy(setx, sety++);
		printf("( )_( )  /__\\  (  _ \\(  _ \\ ");
		gotoxy(setx, sety++);
		printf(" ) _ (  /(__)\\  )   / )(_) )");
		gotoxy(setx, sety++);
		printf("(_) (_)(__)(__)(_)\\_)(____/ ");
	}

	Sleep(2000);
}

void set_console_option() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, FALSE };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	system("mode con cols=102 lines=30 | title RoomEscape");
}

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void show_ending() {
	int ex = 10, ey = 14, i, j;
	show_border();
	show_title();
	gotoxy(ex, ey++);
	printf("  _______ _    _ ______   ______ _   _ _____       ");
	gotoxy(ex, ey++);
	printf(" |__   __| |  | |  ____| |  ____| \\ | |  __ \\      ");
	gotoxy(ex, ey++);
	printf("    | |  | |__| | |__    | |__  |  \\| | |  | |     ");
	gotoxy(ex, ey++);
	printf("    | |  |  __  |  __|   |  __| | . ` | |  | |     ");
	gotoxy(ex, ey++);
	printf("    | |  | |  | | |____  | |____| |\\  | |__| | _ _ ");
	gotoxy(ex, ey);
	printf("    |_|  |_|  |_|______| |______|_| \\_|_____(_|_|_)");

	ex = 66;
	for (i = 0; i < 4; i++) {
		gotoxy(ex, ey);
		printf("return to beginning.");
		for (j = 0; j < i; j++) {
			printf(".");
		}
		Sleep(700);
	}
}

void show_exit() {
	int ex = 7, ey = 14;
	show_border();
	show_title();
	gotoxy(ex, ey++);
	printf(" _________   __                          __          ____  ____                      _  ");
	gotoxy(ex, ey++);
	printf("|  _   _  | [  |                        [  |  _     |_  _||_  _|                    | | ");
	gotoxy(ex, ey++);
	printf("|_/ | | \\_|  | |--.    ,--.    _ .--.    | | / ]      \\ \\  / /     .--.    __   _   | | ");
	gotoxy(ex, ey++);
	printf("    | |      | .-. |  `'_\\ :  [ `.-. |   | '' <        \\ \\/ /    / .'`\\ \\ [  | | |  | | ");
	gotoxy(ex, ey++);
	printf("   _| |_     | | | |  // | |,  | | | |   | |`\\ \\       _|  |_    | \\__. |  | \\_/ |, |_| ");
	gotoxy(ex, ey++);
	printf("  |_____|   [___]|__] \\'-;__/ [___||__] [__|  \\_]     |______|    '.__.'   '.__.'_/ (_) ");
	gotoxy(ex, ey++);
}

void show_title() {
	int tx = 17, ty = 3;
	gotoxy(tx, ty++);
	printf(" ____   ___   ___  ___ ___        ___ _____   __  ____ ____   ___ \n");
	gotoxy(tx, ty++);
	printf("|    \\ /   \\ /   \\|   |   |      /  _] ___/  /  ]/    |    \\ /  _]\n");
	gotoxy(tx, ty++);
	printf("|  D  )     |     | _   _ |     /  [(   \\_  /  /|  o  |  o  )  [_ \n");
	gotoxy(tx, ty++);
	printf("|    /|  O  |  O  |  \\_/  |    |    _]__  |/  / |     |   _/    _]\n");
	gotoxy(tx, ty++);
	printf("|    \\|     |     |   |   |    |   [_/  \\ /   \\_|  _  |  | |   [_ \n");
	gotoxy(tx, ty++);
	printf("|  .  \\     |     |   |   |    |     \\    \\     |  |  |  | |     |\n");
	gotoxy(tx, ty++);
	printf("|__|\\_|\\___/ \\___/|___|___|    |_____|\\___|\\____|__|__|__| |_____|\n");
	printf("\n");
}

void show_border() {
	int i, j;
	gotoxy(1, 1);
	printf("¦£");
	for (i = 0; i < 97; i++) {
		printf("¦¡");
	}
	printf("¦¤");
	for (i = 2; i < 28; i++) {
		gotoxy(1, i);
		for (j = 0; j < 99; j++) {
			if (j == 0 || j == 98)
				printf("¦¢");
			else
				printf(" ");
		}
	}
	gotoxy(1, i);
	printf("¦¦");
	for (i = 0; i < 97; i++) {
		printf("¦¡");
	}
	printf("¦¥");
}

void show_key_pressed(int dir) {
	show_rudder();
	switch (dir) {
	case UP:
		gotoxy(90, 22);
		printf("¡á¡á");
		gotoxy(90, 23);
		printf("¡á¡á");
		break;
	case LEFT:
		gotoxy(85, 25);
		printf("¡á¡á");
		gotoxy(85, 26);
		printf("¡á¡á");
		break;
	case DOWN:
		gotoxy(90, 25);
		printf("¡á¡á");
		gotoxy(90, 26);
		printf("¡á¡á");
		break;
	case RIGHT:
		gotoxy(95, 25);
		printf("¡á¡á");
		gotoxy(95, 26);
		printf("¡á¡á");
		break;
	}
}

void show_status(Info *info) {
	gotoxy(70, 22);
	if (info->state) {
		if (info->level == 0)
			printf("%4s: %-d/%-4d", "MOVE", info->cnt, (int)EASY_COUNT);
		else if (info->level == 1)
			printf("%4s: %-d/%-4d", "MOVE", info->cnt, (int)NORMAL_COUNT);
		else if (info->level == 2)
			printf("%4s: %-d/%-4d", "MOVE", info->cnt, (int)HARD_COUNT);
	}
	else
		printf("                  ");

	gotoxy(70, 23);
	if (info->state)
		printf("%-4s: %c", "KEY", info->key ? 'O' : 'X');
	else
		printf("              ");
}

void show_level(int* lv) {
	gotoxy(84, 9);
	switch (*lv) {
	case 0:
		printf("EASY");
		break;
	case 1:
		printf("NORMAL");
		break;
	case 2:
		printf("HARD");
		break;
	}
}

void show_manual() {
	gotoxy(70, 25);
	printf("%-4s: SELECT", "A");
	gotoxy(70, 26);
	printf("%-4s: ESCAPE", "ESC");
}

void show_rudder() {
	// UP
	gotoxy(90, 22);
	printf("¡à¡à");
	gotoxy(90, 23);
	printf("¡à¡à");

	// LEFT
	gotoxy(85, 25);
	printf("¡à¡à");
	gotoxy(85, 26);
	printf("¡à¡à");

	// DOWN
	gotoxy(90, 25);
	printf("¡à¡à");
	gotoxy(90, 26);
	printf("¡à¡à");

	// RIGHT
	gotoxy(95, 25);
	printf("¡à¡à");
	gotoxy(95, 26);
	printf("¡à¡à");
}

void show_default_layout() {
	show_border();
	show_title();
	show_manual();
	show_rudder();
}

void show_map(char map[ROW][COL], Point* p) {
	for (int i = 0; i < ROW; i++) {
		gotoxy(3, 12 + i);
		for (int j = 0; j < COL; j++) {
			if (i == p->x && j == p->y)
				printf("!");
			else if ('1' <= map[i][j] && map[i][j] <= '3')
				printf("$");
			else if (map[i][j] == 'a')
				printf("¦£");
			else if (map[i][j] == 'b')
				printf("¦¦");
			else if (map[i][j] == 'c')
				printf("¦¤");
			else if (map[i][j] == 'd')
				printf("¦¥");
			else if (map[i][j] == 'e')
				printf("¦¡");
			else if (map[i][j] == 'f')
				printf("¦¢");
			else
				printf("%c", map[i][j]);
		}
	}
}

void show_menu(Info *info) {
	int setx = 8, sety = 12, i, tmpx, tmpy;
	
	if (info->level == 0) {
		tmpx = setx;
		tmpy = sety;
		for (i = 0; i < 4; i++) {
			gotoxy(tmpx, tmpy++);
			printf("  ");
		}
		setx += 2;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(setx, sety++);
	printf(" ____    __    ___  _  _   ");
	gotoxy(setx, sety++);
	printf("( ___)  /__\\  / __)( \\/ )  ");
	gotoxy(setx, sety++);
	printf(" )__)  /(__)\\ \\__ \\ \\  /   ");
	gotoxy(setx, sety++);
	printf("(____)(__)(__)(___/ (__)   ");
	if (info->level == 0)
		setx -= 2;

	if (info->top_level < 1)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	sety++;
	if (info->level == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		tmpx = setx;
		tmpy = sety;
		for (i = 0; i < 4; i++) {
			gotoxy(tmpx, tmpy++);
			printf("  ");
		}
		setx += 2;
	}
	gotoxy(setx, sety++);
	printf(" _  _ _____ ____ __  __   __   __     ");
	gotoxy(setx, sety++);
	printf("( \\( (  _  (  _ (  \\/  ) /__\\ (  )    ");
	gotoxy(setx, sety++);
	printf(" )  ( )(_)( )   /)    ( /(__)\\ )(__   ");
	gotoxy(setx, sety++);
	printf("(_)\\_(_____(_)\\_(_/\\/\\_(__)(__(____)  ");
	if (info->level == 1) {
		setx -= 2;
	}

	if (info->top_level < 2)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	sety++;
	if (info->level == 2) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		tmpx = setx;
		tmpy = sety;
		for (i = 0; i < 4; i++) {
			gotoxy(tmpx, tmpy++);
			printf("  ");
		}
		setx += 2;
	}
	gotoxy(setx, sety++);
	printf(" _   _    __    ____  ____    ");
	gotoxy(setx, sety++);
	printf("( )_( )  /__\\  (  _ \\(  _ \\   ");
	gotoxy(setx, sety++);
	printf(" ) _ (  /(__)\\  )   / )(_) )  ");
	gotoxy(setx, sety++);
	printf("(_) (_)(__)(__)(_)\\_)(____/   ");
	if (info->level == 2)
		setx -= 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}