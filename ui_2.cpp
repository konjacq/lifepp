#include "ui.h"
#include "ui_2.h"
#include "file_handle.h"

PIMAGE img_2 = newimage();
sys_edit editBox_2;
sys_edit editBox_3;

int start_status_2 = 0;

void init_ui_2()
{
	cleardevice();
	setcaption("Life++ Explorer");
	//cr_file();
	initgraph(1200, 800, INIT_RENDERMANUAL);
	PIMAGE init_img = newimage();
	getimage(init_img, "PNG", "UI_2");
	ege_enable_aa(true);
	ege_enable_aa(true, init_img);
	setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));
	putimage(0, 0, init_img);
	delimage(init_img);
	setcolor(BLACK);
	setfont(15, 0, "Cascadia Mono");
	//sys_edit editBox;
	editBox_2.create(true);
	editBox_2.move(9, 129);
	editBox_2.size(1180, 320);
	editBox_2.visible(true);
	endeditbox();
	editBox_2.setfont(19, 0, "Cascadia Mono");
	editBox_2.setreadonly(true);


	editBox_3.create(true);
	editBox_3.move(9, 465);
	editBox_3.size(1180, 320);
	editBox_3.visible(true);
	endeditbox();
	editBox_3.setfont(19, 0, "Cascadia Mono");
	editBox_3.setreadonly(true);

	//for (hash_node *i = hash_table_begin(); i != NULL; i = hash_table_next(i))
	//	if (i->modified != 4)
	//		printf("%d %d %s %s\n", i->number, i->modified, i->node->identifier, i->node->sequence);
	//editBox.settext("\n");
	//editBox.settext(">");
	char ott[100000] =
	    "Sequences Identifier__________________________________________________________________________________________________________________________";
	int k = 0;
	for (hash_node *i = hash_table_begin(); i != NULL; i = hash_table_next(i))
	{
		if (i->modified != 4)
		{
			//printf("%s\n", all_sp[i].sequence);
			char bf[10000];
			sprintf(bf, "(%d)", i->number);
			strcat(ott, bf);
			strcat(ott, i->node->identifier);
			if (k != tot - 1)
				strcat(ott, "__________");
			k++;
		}
	}
	editBox_2.settext(ott);
	char ottt[100000] = "";
	strcat(ottt,
	       "File Name____________________________________________________________________________________________________________________________________");
	k = 0;
	for (hash_node *i = hash_table_begin(); i != NULL; i = hash_table_next(i))
	{
		if (i->modified != 4)
		{
			char bbf[10000];
			sprintf(bbf, "(%d)", i->number);
			strcat(ottt, bbf);
			strcat(ottt, all_file[trans_table[(i->number)]]);
			//printf("%s", all_file[(i->number) - 1]);
			if (k != tot - 1)
				strcat(ottt, "__________");
			k++;
		}
	}
	editBox_3.settext(ottt);
	//for (hash_node *i=hash_table_begin();i!=NULL;i=hash_table_next(i)) if (i->modified!=4)
	//printf("%d %s %s\n",i->number,i->node->identifier,i->node->sequence);

}

void endeditbox_2()
{
	editBox_2.destroy();
	editBox_3.destroy();
	//editBox_2.destroy();
}


void clr2_cmd()
{
	start_status_2 = 0;
	editBox_2.setreadonly(true);
	editBox_3.setreadonly(true);
	//editBox.setfocus(false);
}

int if_butt2B(int x, int y)
{
	if (x >= 1096 && x <= 1200 && y >= 35 && y <= 65)
		return 1;
	else
		return 0;
}

void butt2B()
{
	init_ui();
	clr2_cmd();
	//setfillcolor(EGEARGB(0x73, 0xFF, 0xFF, 0xFF));
	//ege_fillrect(1096, 35, 104, 30);
}

void text_status_2(char *textget)
{
	const int buffSize = 100000;
	char strBuff[100000];
	//int now = 0;
	while (kbmsg())
	{
		key_msg msg = getkey();
		if ((msg.key == key_enter) && (msg.msg == key_msg_up))
		{
			editBox_2.gettext(buffSize, strBuff);
			/*printf("%d", strlen(strBuff));
			printf("%s\n", strBuff);*/
			for (int i = 0; i < (int)strlen(strBuff) ; i++)
			{
				textget[i] = strBuff[i];
			}
			textget[strlen(strBuff)] = '\0';
			editBox_2.setfocus();
			editBox_2.settext("");
		}
		flushkey();
	}

}

void butt2BB()
{
	PIMAGE butt_img = newimage();
	getimage(butt_img, "PNG", "UI_2");
	putimage(1096, 35, 104, 30, butt_img, 1096, 35);
	delimage(butt_img);
}


void butt2BBB()
{
	PIMAGE butt_img = newimage();
	getimage(butt_img, "PNG", "UI_1");
	putimage(1096, 35, 104, 30, butt_img, 1096, 35);
	delimage(butt_img);
}

