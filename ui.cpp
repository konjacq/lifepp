#include "ui.h"
#include "ui_2.h"
#include "ui_3.h"
#include "file_handle.h"
#include "connector.h"

PIMAGE img = newimage();
sys_edit editBox;
int start_status = 0;
int nowat = 1;
char butt = 'N';
int nxt = 0;

/*

void init_ui_2();
int if_butt2B(int x, int y);
void butt2B();
void butt2BB();
void clr2_cmd();
int mouse_click_2();



//editBox.setreadonly(true);
void init_ui();
void get_start();
void clr_cmd();
int if_buttL(int x, int y);
void buttL();
void buttLL();
int if_buttA(int x, int y);
void buttA();
void buttAA();
int if_buttD(int x, int y);
void buttD();
void buttDD();
int if_buttE(int x, int y);
void buttE();
void buttEE();
int if_buttU(int x, int y);
void buttU();
void buttUU();
int mouse_click();
void text_status(char *textget);
void key_handle(char *inpt);
void buttreset();
*/


void endeditbox()
{
	editBox.destroy();
	//editBox_2.destroy();
}

void init_ui()
{
	setcaption("Life++ ControlPanel");
	cleardevice();
	endeditbox_2();
	start_status = 0;
	initgraph(1200, 800, INIT_RENDERMANUAL);
	PIMAGE init_img = newimage();
	getimage(init_img, "PNG", "UI_1");
	ege_enable_aa(true);
	ege_enable_aa(true, init_img);
	setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));
	putimage(0, 0, init_img);
	delimage(init_img);
	setcolor(BLACK);
	setfont(15, 0, "Cascadia Mono");
	if (init_file())
	{
		editBox.create(true);
		editBox.move(29, 682);
		editBox.size(1162, 112);
		editBox.visible(true);
		editBox.setfont(19, 0, "Cascadia Mono");
		editBox.settext("Unable to find the previous file, please re-add the sequence!!! Each command line needs to start with a '>', press Enter to input command.");
		editBox.setreadonly(true);
		return ;
	}
	//sys_edit editBox;
	else if (nowat == 1)
	{
		editBox.create(true);
		editBox.move(29, 682);
		editBox.size(1162, 112);
		editBox.visible(true);
		editBox.setfont(19, 0, "Cascadia Mono");
		editBox.settext("Each command line needs to start with a '>', press Enter to input command.");
		editBox.setreadonly(true);
	}
	if (nowat == 2)
	{
		editBox.visible(false);
	}
	//editBox.settext("\n");
	//editBox.settext(">");

}

void get_start()
{
	//if (start_status == 1)
	//	return ;
	if (nowat == 2)
		return ;

	editBox.setreadonly(false);
	buttreset();
	start_status = 1;
	setfont(29, 0, "Cascadia Mono");
	outtextxy(8, 680, ">");
	editBox.settext("");
	setfont(15, 0, "Cascadia Mono");
	editBox.setfocus();
	return ;



}

void clr_cmd()
{
	//start_status = 0;
	setfillcolor(WHITE);
	ege_fillrect(5, 680, 20, 30);
	editBox.setreadonly(true);
	//editBox.setfocus();
	//editBox.setfocus(false);
}

int if_buttL(int x, int y)
{
	//70,569 309,598
	if (x >= 67 && x <= 306 && y >= 570 && y <= 599)
		return 1;
	else
		return 0;
}


void buttL()
{
	clr_cmd();
	setfillcolor(EGEARGB(0x73, 0xFF, 0xFF, 0xFF));
	ege_fillrect(67, 570, 240, 30);
	init_ui_2();

}

void buttLL()
{
	PIMAGE butt_img = newimage();
	getimage(butt_img, "PNG", "UI_1");
	putimage(67, 570, 240, 30, butt_img, 67, 570);
	delimage(butt_img);
}

int if_buttA(int x, int y)
{
	//70,569 309,598
	if (x >= 321 && x <= 523 && y >= 570 && y <= 599)
		return 1;
	else
		return 0;
}

void buttA()
{
	editBox.settext("[Info.A]Press Enter to input the absolute path of the .fasta file.");
	butt = 'A';
	start_status = 0;
	clr_cmd();
	setfillcolor(EGEARGB(0x73, 0xFF, 0xFF, 0xFF));
	ege_fillrect(321, 570, 202, 30);

}

void buttAA()
{
	PIMAGE butt_img = newimage();
	getimage(butt_img, "PNG", "UI_1");
	putimage(321, 570, 202, 30, butt_img, 321, 570);
	delimage(butt_img);
}


int if_buttD(int x, int y)
{
	//70,569 309,598
	if (x >= 538 && x <= 765 && y >= 570 && y <= 598)
		return 1;
	else
		return 0;
}

void buttD()
{
	butt = 'D';
	editBox.settext("[Info.D]Press Enter to input the no. of the sequences you want to delete, separated by commas.");
	start_status = 0;
	clr_cmd();
	setfillcolor(EGEARGB(0x73, 0xFF, 0xFF, 0xFF));
	ege_fillrect(538, 570, 223, 30);

}

void buttDD()
{
	PIMAGE butt_img = newimage();
	getimage(butt_img, "PNG", "UI_1");
	putimage(538, 570, 223, 30, butt_img, 538, 570);
	delimage(butt_img);
}



int if_buttE(int x, int y)
{
	//70,569 309,598
	if (x >= 538 && x <= 765 && y >= 604 && y <= 634)
		return 1;
	else
		return 0;
}

void buttE()
{
	butt = 'E';
	editBox.settext("ButtE has been kicked.");
	clr_cmd();
	setfillcolor(EGEARGB(0x73, 0xFF, 0xFF, 0xFF));
	ege_fillrect(538, 604, 223, 30);
	exit(0);

}

void buttEE()
{
	PIMAGE butt_img = newimage();
	getimage(butt_img, "PNG", "UI_1");
	putimage(538, 604, 223, 30, butt_img, 538, 604);
	delimage(butt_img);
}



int if_buttU(int x, int y)
{
	//70,569 309,598
	if (x >= 67 && x <= 523 && y >= 605 && y <= 633)
		return 1;
	else
		return 0;
}

void buttU()
{
	butt = 'U';
	clr_cmd();
	setfillcolor(EGEARGB(0x73, 0xFF, 0xFF, 0xFF));
	ege_fillrect(67, 523, 456, 29);
	init_ui_3();
}

void buttUU()
{
	PIMAGE butt_img = newimage();
	getimage(butt_img, "PNG", "UI_1");
	putimage(67, 523, 456, 29, butt_img, 67, 523);
	delimage(butt_img);
}


int mouse_click()
{
	while (mousemsg())

	{
		//printf("1");
		mouse_msg mouseMsg = getmouse();
		if (mouseMsg.is_left())
		{
			if (mouseMsg.is_down())
			{
				if (if_buttL(mouseMsg.x, mouseMsg.y) && nowat == 1 )
				{
					nowat = 2;
					buttL();
				}
				if (if_buttA(mouseMsg.x, mouseMsg.y) && nowat == 1 )
				{
					buttA();
				}
				if (if_buttD(mouseMsg.x, mouseMsg.y) && nowat == 1)
				{
					buttD();
				}
				if (if_buttE(mouseMsg.x, mouseMsg.y) && nowat == 1)
				{
					buttE();
				}
				if (if_buttU(mouseMsg.x, mouseMsg.y) && nowat == 1)
				{
					nowat = 3;
					buttU();
				}
				if (if_butt2B(mouseMsg.x, mouseMsg.y) && nowat == 2)
				{
					nowat = 1;
					butt2B();
				}
				if (if_butt3B(mouseMsg.x, mouseMsg.y) && nowat == 3)
				{
					nowat = 1;
					butt3B();
				}
				if (if_butt3S(mouseMsg.x, mouseMsg.y) && nowat == 3)
				{
					butt3S();
				}
			}
			if (mouseMsg.is_up())
			{
				if (if_buttL(mouseMsg.x, mouseMsg.y) && nowat == 1)
				{
					buttLL();
				}
				if (if_buttA(mouseMsg.x, mouseMsg.y) && nowat == 1)
				{
					buttAA();
				}
				if (if_buttD(mouseMsg.x, mouseMsg.y) && nowat == 1)
				{
					buttDD();
				}
				if (if_buttE(mouseMsg.x, mouseMsg.y) && nowat == 1)
				{
					buttEE();
				}
				if (if_butt2B(mouseMsg.x, mouseMsg.y))
				{
					if (nowat == 2)
						butt2BB();
					if (nowat == 1)
						butt2BBB();
				}
				if (if_butt3B(mouseMsg.x, mouseMsg.y))
				{
					if (nowat == 3)
						butt3BB();
					if (nowat == 1)
						butt3BBB();
				}
				if (if_butt3S(mouseMsg.x, mouseMsg.y))
				{
					if (nowat == 3)
						butt3SS();
				}
			}
		}
	}
	return 0;
}

void text_status(char *textget)
{
	if (nowat == 2)
		return ;
	const int buffSize = 100000;
	char strBuff[100000];
	//int now = 0;
	while (kbmsg())
	{
		key_msg msg = getkey();
		if ((msg.key == key_enter) && (msg.msg == key_msg_up))
		{
			if (start_status == 0)
			{
				get_start();
				//return ;
			}
			//editBox.setreadonly(true);
			editBox.gettext(buffSize, strBuff);
			/*printf("%d", strlen(strBuff));
			printf("%s\n", strBuff);*/
			for (int i = 0; i < (int)strlen(strBuff) ; i++)
			{
				textget[i] = strBuff[i];
			}
			textget[strlen(strBuff)] = '\0';
			//editBox.setreadonly(false);
			//editBox.setfocus();
			//printf("%s", textget);
			editBox.setfocus();
			editBox.settext("");
		}
		flushkey();
	}

}

void key_handle(char *inpt)
{
	if (butt == 'A' && strlen(inpt) > 0)
	{
		char mid[100000];
		int nn = 0;
		//printf("%s%d\n", inpt, strlen(inpt));
		for (int i = 0; i < (int)strlen(inpt) + 4; i++)
		{
			if (inpt[i] == '\n' || inpt[i] == '\r')
				continue;
			if (inpt[i] == '\\')
			{
				mid[nn++] = '/';
			}
			else
				mid[nn++] = inpt[i];
		}

		mid[nn - 1] = '\0';
		//inpt[strlen(inpt) - 2] = '\0';

		char *dir = file_copy(mid, tot++);
		//Sprintf("%d", tot);
		FILE *st = fopen(dir, "r");
		handle_seq(st, tot - 1);
		//printf("1");
		//printf("%s", all_sp[tot - 1].sequence);
		char opt[100000];
		opt[0] = '\0';
		//printf("%s", all_sp[tot - 1].identifier);
		strcpy(opt, all_sp[nw].identifier);
		//printf("1");
		strcat(opt, ">");
		//strcat(opt, all_sp[tot - 1].sequence);
		strcat(opt, ">Import Success ! Press Enter to continue.");
		editBox.settext(opt);
		clr_cmd();
		start_status = 0;
		fclose(st);
		butt = 'N';
	}
	if (butt == 'D' && strlen(inpt) > 0)
	{
		//char mid[100000];
		int num[100000];
		//printf("%s", inpt);
		int nn = 0;
		for (int i = 0; i < (int)strlen(inpt) - 2 ; i++)
		{
			if (inpt[i] == ',')
				nn++;
			num[nn] = inpt[i] - 48;
			//printf("%d",num[nn]);
		}
		int su = 1;
		//if (nn == 0)
		for (int i = 0; i <= nn; i++)
		{

			if (seq_del(trans_table[num[i]]) != 0 || species_remove_by_number(num[i]) == -1)
			{
				su = 0;
			}
			//printf("%d\n", num[i]);
		}
		//printf("%d", trans_table[num[i]]);
		cr_file();
		if (su == 1)
			editBox.settext("Success!");
		else
			editBox.settext("Fail!");
		clr_cmd();
		start_status = 0;
		butt = 'N';
	}
	else if (inpt[0] == 'L' && strlen(inpt) == 3 && butt == 'N')
	{
		buttL();
	}
	//inpt[0] = '\0';
	else if (inpt[0] == 'A' && strlen(inpt) == 3 && butt == 'N')
	{
		buttA();
	}
	//inpt[0] = '\0';
	else if (inpt[0] == 'D' && strlen(inpt) == 3 && butt == 'N')
	{
		buttD();
	}
	//inpt[0] = '\0';
	else if (inpt[0] == 'U' && strlen(inpt) == 3 && butt == 'N')
	{
		buttU();
	}
	//inpt[0] = '\0';
	else if (inpt[0] == 'E' && strlen(inpt) == 3 && butt == 'N')
	{
		buttE();
	}
	inpt[0] = '\0';
}

void buttreset()
{
	buttLL();
	buttAA();
	buttDD();
	buttEE();
	buttUU();

}


int mouse_click_2()
{
	while (mousemsg())

	{
		//printf("1");
		mouse_msg mouseMsg = getmouse();
		if (mouseMsg.is_left())
		{
			if (mouseMsg.is_down())
			{
				if (if_butt2B(mouseMsg.x, mouseMsg.y) )
				{
					butt2B();
				}
			}
			if (mouseMsg.is_up())
			{
				if (if_butt2B(mouseMsg.x, mouseMsg.y) )
				{
					butt2BB();
				}
			}
		}
	}
	return 0;
}

