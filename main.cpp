#include "ui.h"
#include "ui_2.h"
#include "file_handle.h"
#include <windows.h>
species all_sp[2];
char all_id[2][1000];
//extern char all_seq[10000][10000];
int tot;
char all_file[10000][1000];
//char true_file[10000][1000];
int trans_table[10000];
int nw = 0;
int newpro = 1;

int main()
{
	HWND hwnd;
	hwnd = GetForegroundWindow();
	if (hwnd)
	{
		ShowWindow(hwnd, SW_HIDE);
	}
	matit();
	init_ui();
	newpro = 0;
	//species_remove_by_number(1000);
	static char text[100000];
	for (; is_run(); delay_fps(144))
	{
		mouse_click();
		text_status(text);
		key_handle(text);
		//get_start();

	}
	endeditbox();
	endeditbox_2();
	closegraph();
	//fclose(cof);
	return 0;
}


