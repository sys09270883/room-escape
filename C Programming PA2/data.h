#pragma once
#define ROW 16
#define COL 65
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define EASY_COUNT 3e2
#define NORMAL_COUNT 5e2
#define HARD_COUNT 7e2

typedef struct _Point {
	int x, y;
} Point;

typedef struct _Log {
	int size;
	char str[7][25];
} Log;

typedef struct _Info {
	int level, state, cnt, level_flag_size, key, door, cur_key, top_level;
	char map[ROW][COL];
	char *level_flag;	/* easy, normal, hard */
	Log log;
} Info;
