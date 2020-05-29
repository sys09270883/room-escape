#include <stdio.h>
#include <string.h>
#include <time.h>
#include "view.h"
#include "model.h"

void catch_key_event(Point*, Info*);
void select_menu(Point*, Info*);
int select_setting(Point*, Info*);
void next_phase(Point*, Info*);
void fail(Point*, Info*);
void return_to_menu(Point*, Info*);

int main() {
	srand((unsigned int)time(NULL));
	set_console_option();

	// INIT DATA
	Point start;
	set_point(&start, ROW - 2, 1);
	Info info;
	init_info(&info);
	init_map(info.map);
	info.top_level = 0;
	
	// SHOW LAYOUT
	show_default_layout();

	// CHOICE
	show_menu(&info);
	select_menu(&start, &info);
	generate_item(&info);
	set_item_to_map(&info);

	// RUN
	show_default_layout();
	show_running(&info);
	show_map(info.map, &start);

	while (info.state) {
		if (!check_count(&info))	// exceed count
			fail(&start, &info);

		catch_key_event(&start, &info);
		show_status(&info);

		if (info.key) {	// after obtain key
			if (open_door(&info))
				show_map(info.map, &start);
		}

		if (!start.x) {	// door opened
			if (get_result(&info)) {	// success
				event_catch(&start, &info, 4);
				show_log(&info);
				next_phase(&start, &info);
			}
			else	// fail
				fail(&start, &info);
		}
		if (!info.state)	// return to menu
			return_to_menu(&start, &info);
	}

	return 0;
}

void return_to_menu(Point* p, Info* info) {
	show_status(info);
	show_log(info);
	init_info(info);
	select_menu(p, info);
	init_map(info->map);
	generate_item(info);
	set_item_to_map(info);
	clear_log(info);
	show_phase(info);
	system("cls");
	show_default_layout();
	show_running(info);
	show_map(info->map, p);
}

void fail(Point* p, Info* info) {
	event_catch(p, info, 5);
	show_log(info);
	show_fail(info);
	init_info(info);
	show_default_layout();
	show_menu(info);
	select_menu(p, info);
	init_map(info->map);
	generate_item(info);
	set_item_to_map(info);
	set_point(p, ROW - 2, 1);
	clear_log(info);
	show_running(info);
	show_map(info->map, p);
}

void catch_key_event(Point *p, Info *info) {
	char c = _getch();
	switch (c) {
	case UP:
		if (p->x > 0 && possible(info, p->x - 1, p->y)) {
			update_map(p, info, 0);
			p->x--, info->cnt++;
			update_map(p, info, 1);
		}
		if (info->cur_key != UP) {
			info->cur_key = UP;
			show_key_pressed(UP);
		}
		break;
	case LEFT:
		if (p->y > 0 && possible(info, p->x, p->y - 1)) {
			update_map(p, info, 0);
			p->y--, info->cnt++;
			update_map(p, info, 1);
		}
		if (info->cur_key != LEFT) {
			info->cur_key = LEFT;
			show_key_pressed(LEFT);
		}
		break;
	case DOWN:
		if (p->x < ROW - 1 && possible(info, p->x + 1, p->y)) {
			update_map(p, info, 0);
			p->x++, info->cnt++;
			update_map(p, info, 1);
		}
		if (info->cur_key != DOWN) {
			info->cur_key = DOWN;
			show_key_pressed(DOWN);
		}
		break;
	case RIGHT:
		if (p->y < COL - 2 && possible(info, p->x, p->y + 1)) {
			update_map(p, info, 0);
			p->y++, info->cnt++;
			update_map(p, info, 1);
		}
		if (info->cur_key != RIGHT) {
			info->cur_key = RIGHT;
			show_key_pressed(RIGHT);
		}
		break;
	case ESC:
		show_esc(info, 0);
		if (select_setting(p, info) == 1) {
			update_map(p, info, 0);
			set_point(p, ROW - 2, 1);
			update_map(p, info, 1);
		}
		break;
	case 'a': case 'A':
		if (!('1' <= info->map[p->x][p->y] && info->map[p->x][p->y] <= '3'))
			break;
		if (info->map[p->x][p->y] == '1')
			event_catch(p, info, 1);
		else if (info->map[p->x][p->y] == '2')
			event_catch(p, info, 2);
		else if (info->map[p->x][p->y] == '3')
			event_catch(p, info, 3);
		show_map(info->map, p);
		show_log(info);
		info->map[p->x][p->y] = ' ';
		break;
	}
}

void next_phase(Point *p, Info* info) {
	Sleep(2000);
	if (info->level < 2) {
		// next level
		set_next_level(info);
		show_default_layout();
		init_map(info->map);
		generate_item(info);
		set_item_to_map(info);
		set_point(p, ROW - 2, 1);
		clear_log(info);
		show_default_layout();
		show_status(info);
		show_map(info->map, p);
		show_log(info);
		show_level(&info->level);
		show_phase(info);
		system("cls");
		show_default_layout();
		show_status(info);
		show_log(info);
		show_level(&info->level);
		show_map(info->map, p);
	}
	else {	// ending
		show_ending();
		system("cls");
		init_info(info);
		show_default_layout();
		show_menu(info);
		select_menu(p, info);
		init_map(info->map);
		generate_item(info);
		set_item_to_map(info);
		set_point(p, ROW - 2, 1);
		show_map(info->map, p);
	}
}

void select_menu(Point *p, Info *info) {
	int c, i, next_level;
	int coord[3][2] = { {4, 14}, {4, 19}, {4, 24} };

	while (1) {
		for (i = 0; i < 3; i++) {
			gotoxy(coord[i][0], coord[i][1]);
			if (info->level == i) {
				if (info->top_level >= info->level)
					printf("▶");
				show_menu(info);
			}
			else
				printf("  ");
		}
		
		c = _getch();
		switch (c) {
		case UP:
			next_level = (info->level + 2) % 3;
			if (info->top_level < next_level)
				break;
			else {
				set_info_level(info, 2);
				if (info->cur_key != UP) {
					info->cur_key = UP;
					show_key_pressed(UP);
				}
			}
			break;
		case RIGHT:
			next_level = (info->level + 2) % 3;
			if (info->top_level < next_level)
				break;
			else {
				set_info_level(info, 2);
				if (info->cur_key != RIGHT) {
					info->cur_key = RIGHT;
					show_key_pressed(RIGHT);
				}
			}
			break;
		case DOWN:
			next_level = (info->level + 1) % 3;
			if (info->top_level < next_level)
				break;
			else {
				set_info_level(info, 1);
				if (info->cur_key != DOWN) {
					info->cur_key = DOWN;
					show_key_pressed(DOWN);
				}
			}
			break;
		case LEFT:
			next_level = (info->level + 1) % 3;
			if (info->top_level < next_level)
				break;
			else {
				set_info_level(info, 1);
				if (info->cur_key != LEFT) {
					info->cur_key = LEFT;
					show_key_pressed(LEFT);
				}
			}
			break;
		case ESC:
			show_esc(info, 0);
			select_setting(p, info);
			break;
		case 'A': case 'a':
			set_info_state(info, 1);
			show_phase(info);
			system("cls");
			show_default_layout();
			show_running(info);
			return;
		}
	}
}

int select_setting(Point* p, Info* info) {
	int i, c, select = 0;
	int coord[2][2] = { {40, 21}, {59, 21} };

	while (1) {
		for (i = 0; i < 3; i++) {
			if (select == i) {
				show_esc(info, select);
				gotoxy(coord[i][0], coord[i][1]);
				printf("▲");
			}
			else {
				printf("  ");
			}
		}

		c = _getch();
		switch (c) {
		case UP:
			toggle(&select);
			show_key_pressed(UP);
			break;
		case DOWN:
			toggle(&select);
			show_key_pressed(DOWN);
			break;
		case RIGHT:
			toggle(&select);
			show_key_pressed(RIGHT);
			break;
		case LEFT:
			toggle(&select);
			show_key_pressed(LEFT);
			break;
		case 'A': case 'a':
			if (!select) {
				if (!info->state) {
					show_exit();
					exit_program();
				}
				else {
					update_map(p, info, 0);
					init_info(info);
					init_map(info->map);
					show_default_layout();
					show_menu(info);
					select_menu(p, info);
					generate_item(info);
					set_item_to_map(info);
					show_map(info->map, p);
					//set_info_state(info, 1);
					info->key = 0;
					return 1;
				}
			}
			else {
				if (!info->state) {
					// selecting
					init_info(info);
					show_default_layout();
					show_menu(info);
					return 0;
				}
				else {
					// running
					set_info_state(info, 1);
					show_default_layout();
					show_running(info);
					show_map(info->map, p);
					return 0;
				}
			}
			break;
		case ESC:
			if (!info->state) {
				// selecting
				init_info(info);
				show_default_layout();
				show_menu(info);
				return 0;
			}
			else {
				// running
				set_info_state(info, 1);
				show_default_layout();
				show_running(info);
				show_map(info->map, p);
				return 0;
			}
		}
	}
	return 0;
}