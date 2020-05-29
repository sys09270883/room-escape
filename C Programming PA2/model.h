#pragma once
#pragma warning(disable:4996)
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

void shuffle_flags(Info*);
void init_map(char[ROW][COL]);
void exit_program();
void set_point(Point*, int, int);
void toggle(int*);
void set_info_state(Info*, int);
void set_info_level(Info*, int);
void init_info(Info*);
void generate_item(Info*);
void set_item_to_map(Info*);
void event_catch(Point*, Info*, int);
void clear_log(Info*);
int open_door(Info*);
void set_next_level(Info*);
void handle_event(Point*, Info*, char[25], int);
void set_obstacle(Info*);
void clear_obstacle(Info*);
int possible(Info*, int x, int y);
int check_area(Info*, int, int);
int get_result(Info*);
int check_count(Info*);
void swap(char*, char*);

void swap(char* c1, char* c2) {
	char tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

void shuffle_flags(Info* info) {
	int i, j, tx, ty, rand_cnt;
	char c;
	for (i = 0; i < ROW - 1; i++) {
		for (j = 0; j < COL - 1; j++) {
			c = info->map[i][j];
			rand_cnt = 0;
			if ('1' <= c && c <= '3') {
				while (rand_cnt < 5) {
					rand_cnt++;
					tx = rand() % (ROW - 2) + 1;
					ty = rand() % (COL - 2) + 1;
					if (info->map[tx][ty] == ' ') {
						swap(&info->map[i][j], &info->map[tx][ty]);
						break;
					}
				}
			}
		}
	}
}

int check_count(Info* info) {
	int lv = info->level, cnt = info->cnt;
	if (lv == 0) {
		if (cnt > EASY_COUNT)
			return 0;
	}
	else if (lv == 1) {
		if (cnt > NORMAL_COUNT)
			return 0;
	}
	else if (lv == 2) {
		if (cnt > HARD_COUNT)
			return 0;
	}
	return 1;
}

int get_result(Info* info) {
	int result = 0;
	switch (info->level) {
	case 0:
		result = info->cnt <= EASY_COUNT ? 1 : 0;
		break;
	case 1:
		result = info->cnt <= NORMAL_COUNT ? 1 : 0;
		break;
	case 2:
		result = info->cnt <= HARD_COUNT ? 1 : 0;
		break;
	}
	return result;
}

void clear_obstacle(Info* info) {
	int i, j;
	for (i = 1; i < ROW - 1; i++) {
		for (j = 1; j < COL - 1; j++) {
			if ('a' <= info->map[i][j] && info->map[i][j] <= 'f')
				info->map[i][j] = ' ';
		}
	}
}

int check_area(Info* info, int tx, int ty) {
	int ret = 0, i, j;
	for (i = 0; i < (info->level + 1) * 2; i++) {
		for (j = 0; j < 2; j++) {
			if (info->map[tx + i][ty + j] == ' ')
				ret++;
		}
	}
	return ret == (info->level + 1) * 4;
}

void set_obstacle(Info* info) {
	int i, j, tx = 0, ty = 0, obs_cnt = 0, chk_cnt = 0;
	while (1) {
		if (chk_cnt >= 20)
			break;
		if (obs_cnt >= (info->level + 1) * 2)
			break;
		tx = rand() % (ROW - 1) + 2;
		ty = rand() % (COL - 5) + 2;

		if (tx + (info->level + 1) * 2 >= ROW - 1)
			continue;

		if (check_area(info, tx, ty)) {
			for (i = 0; i < (info->level + 1) * 2; i++) {
				for (j = 0; j < 2; j++) {
					info->map[tx + i][ty + j] = 'f';
				}
			}

			info->map[tx][ty] = 'a';
			info->map[tx + (info->level + 1) * 2][ty] = 'b';
			info->map[tx][ty + 1] = 'c';
			info->map[tx + (info->level + 1) * 2][ty + 1] = 'd';
			obs_cnt++;
		}
		chk_cnt++;
	}
}

void set_next_level(Info *info) {
	info->level++;
	info->cnt = 0;
	info->key = 0;
	info->door = 0;
	info->top_level = max(info->top_level, info->level);
}

int possible(Info* info, int x, int y) {
	if ('a' <= info->map[x][y] && info->map[x][y] <= 'f')
		return 0;
	return 1;
}

int open_door(Info* info) {
	if (info->door)
		return 0;
	int y = 0;
	while (!y) {
		y = rand() % (COL - 1);
	}
	info->map[0][y] = 'O';
	info->door = 1;
	return 1;
}

void clear_log(Info* info) {
	info->log.size = 0;
	memset(info->log.str, 0, sizeof(info->log.str));
}

void event_catch(Point* p, Info* info, int event_num) {
	int i;
	char event_log[25] = "";
	handle_event(p, info, event_log, event_num);

	if (info->log.size >= 7) {
		for (i = 0; i < 6; i++) {
			strcpy(info->log.str[i], info->log.str[i + 1]);
		}
		strcpy(info->log.str[6], event_log);
		return;
	}

	strcpy(info->log.str[info->log.size], event_log);
	info->log.size++;
}

void handle_event(Point* p, Info* info, char event_log[25], int event_num) {
	int tmp;
	if (event_num == 1) {
		strcat(event_log, " You got a key!");
		info->key++;
	}
	else if (event_num == 2) {
		tmp = rand() % 3;
		if (tmp == 0) {
			strcat(event_log, " Divide by 2");
			info->cnt >>= 1;
		}
		else if (tmp == 1) {
			strcat(event_log, " Shuffle flags");
			shuffle_flags(info);
		}
		else if (tmp == 2) {
			strcat(event_log, " Clear all obstacles");
			clear_obstacle(info);
		}
	}
	else if (event_num == 3) {
		tmp = rand() % 3;
		if (tmp == 0) {
			strcat(event_log, " Multiply by 2");
			info->cnt <<= 1;
		}
		else if (tmp == 1) {
			strcat(event_log, " Back to starting point");
			info->map[p->x][p->y] = ' ';
			set_point(p, ROW - 2, 1);
		}
		else if (tmp == 2) {
			strcat(event_log, " Obstacles emerge");
			set_obstacle(info);
		}
	}
	else if (event_num == 4)
		strcat(event_log, " Escape!");
	else if (event_num == 5)
		strcat(event_log, " Fail to escape...");
}

void set_item_to_map(Info* info) {
	int x, y, i;
	for (i = info->level_flag_size - 1; i >= 0; i--) {
		while (1) {
			x = rand() % (ROW - 1);
			if (x != 0 && x != COL - 1)
				break;
		}
		while (1) {
			y = rand() % (COL - 1);
			if (y != 0 && y != ROW - 1)
				break;
		}

		info->map[x][y] = info->level_flag[i];
	}
}

void generate_item(Info* info) {
	if (!info->level_flag)
		free(info->level_flag);
	int i;

	if (info->level == 0) {
		info->level_flag_size = 20;
		info->level_flag = (char*)malloc(sizeof(char) * info->level_flag_size);
		for (i = 0; i < info->level_flag_size; i++) {
			if (i < 1)
				info->level_flag[i] = '1';	// 1: key
			else if (i < 7)
				info->level_flag[i] = '2';	// 2: advantage
			else
				info->level_flag[i] = '3';	// 3: penalty
		}
		/* 1/6/13 */
	}
	else if (info->level == 1) {
		info->level_flag_size = 30;
		info->level_flag = (char*)malloc(sizeof(char) * info->level_flag_size);
		for (i = 0; i < info->level_flag_size; i++) {
			if (i < 1)
				info->level_flag[i] = '1';	// 1: key
			else if (i < 8)
				info->level_flag[i] = '2';	// 2: advantage
			else
				info->level_flag[i] = '3';	// 3: penalty
		}
		/* 1/7/22 */
	}
	else if (info->level == 2) {
		info->level_flag_size = 40;
		info->level_flag = (char*)malloc(sizeof(char) * info->level_flag_size);
		for (i = 0; i < info->level_flag_size; i++) {
			if (i < 1)
				info->level_flag[i] = '1';	// 1: key
			else if (i < 4)
				info->level_flag[i] = '2';	// 2: advantage
			else
				info->level_flag[i] = '3';	// 3: penalty
		}
		/* 1/8/31 */
	}
}

void init_info(Info* info) {
	info->level = 0;
	info->state = 0;
	info->cnt = 0;
	info->key = 0;
	info->door = 0;
	info->log.size = 0;
	info->cur_key = 0;
	memset(info->log.str, 0, sizeof(info->log.str));
}

void exit_program() {
	Sleep(2000);
	exit(0);
}

void set_point(Point* p, int x, int y) {
	p->x = x;
	p->y = y;
}

void set_info_state(Info* info, int state) {
	info->state = state;
}

void set_info_level(Info* info, int diff) {
	info->level = (info->level + diff) % 3;
}

void toggle(int *select) {
	*select ^= 1;
}

void init_map(char map[ROW][COL]) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (i == 0 || i == ROW - 1)
				map[i][j] = 'e';
			else if (j == 0 || j == COL - 1)
				map[i][j] = 'f';
			else
				map[i][j] = ' ';
		}
	}
	map[0][0] = 'a';
	map[ROW - 1][0] = 'b';
	map[0][COL - 1] = 'c';
	map[ROW - 1][COL - 1] = 'd';
}
