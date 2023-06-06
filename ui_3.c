#include "ui.h"
#include "ui_2.h"
#include "ui_3.h"
#include "file_handle.h"
#include <time.h>
#include <math.h>


PIMAGE img_3 = newimage();
const int upper_frame = 90;
const int lower_frame = 790;
const int wida = 900;
//int tot;
int dfs_pth = 0;
int dfs_pth2 = 0;

//------------------------
tree toprint;

void draw_pic()
{
	toprint = build_tree(mathch_value, -5.0, 1.0);
	//printf("1");
	dfs_pth = 0;
	dfs_pth2 = 0;
	int totsp = 0, longgesttxt = 0;
	setfont(30, 0, "Cascadia Mono");
	for (int i = 0; i < toprint.root_size; i++)
	{
		for (int j = 0; j < toprint.size; j++)
		{
			//printf("%d %d %lf\n", toprint.left_son[j], toprint.right_son[j], toprint.edge_length[j]);
			if (toprint.left_son[j] == -1 && toprint.right_son[j] == -1)
			{
				totsp++;
				//printf("%s\n", toprint.node[j]->identifier);
				for (int k = 0; k < (int)strlen(toprint.node[j]->identifier); k++)
				{
					if (toprint.node[j]->identifier[k] == '.' && k > longgesttxt)
						longgesttxt = k;
				}
			}
		}
	}
	//toprint.left_son[5]=4;
	//toprint.right_son[5]=1;
	int need_lines = (totsp - 1) * 2 + 2;
	int ftsiz = 5;
	//printf("%d",longgesttxt);
	for (int i = 5; i <= 80; i++)
	{
		setfont(i, 0, "Cascadia Mono");
		char tx[1000] = "T";
		for (int j = 0; j < longgesttxt - 1; j++)
		{
			strcat(tx, "T");
		}
		if ((textheight("T")*need_lines) <= (lower_frame - upper_frame - 20) && textwidth(tx) <= 170)
			ftsiz = i;
	}
	setfont(ftsiz, 0, "Cascadia Mono");
	int space = ftsiz * 2;
	int halfspace = space / 2;
	int pt = halfspace + upper_frame;
	for (int i = 0; i < toprint.root_size; i++)
	{
		static int pth[10000];
		static int depthr[10000];
		static int depthl[10000];
		//static int level[10000];
		int vis[10000];
		memset(vis, 0, sizeof(vis));
		memset(depthr, -1, sizeof(depthr));
		memset(depthl, -1, sizeof(depthl));
		dfs(toprint.root[i], 0, pth, vis);
		for (int j = 0; j < dfs_pth; j++)
		{
			int search = pth[j];
			int times = 1;
			if (depthr[search] != -1 || depthl[search] != -1)
			{
				continue;
			}
			for (int k = j; k < dfs_pth; k++)
			{
				//printf("%d",search);
				if (pth[k] == search && k != j)
				{
					times++;
				}
				if (toprint.left_son[pth[k]] == -1 && times == 1)
				{
					depthl[search]++;
				}
				if (toprint.left_son[pth[k]] == -1 && times == 2)
				{
					depthr[search]++;
				}
				if (times == 3)
				{
					break;
				}
			}
		}
		for (int j = 0; j < toprint.size; j++)
		{
			depthl[j]++;
			depthr[j]++;
			//printf("%d %d\n", depthl[j], depthr[j]);
			if (depthl[j] < depthr[j] && toprint.left_son[j] != 0 && toprint.right_son[j] != 0)
			{
				int tmp = toprint.left_son[j];
				toprint.left_son[j] = toprint.right_son[j];
				toprint.right_son[j] = tmp;
			}
		}
		memset(vis, 0, sizeof(vis));
		memset(depthr, -1, sizeof(depthr));
		memset(depthl, -1, sizeof(depthl));
		memset(pth, 0, sizeof(pth));
		dfs_pth = 0;
		dfs_pth2 = 0;
		dfs(toprint.root[i], 0, pth, vis);
		for (int j = 0; j < dfs_pth; j++)
		{
			int search = pth[j];
			int times = 1;
			if (depthr[search] != -1 || depthl[search] != -1)
			{
				continue;
			}
			for (int k = j; k < dfs_pth; k++)
			{
				//printf("%d",search);
				if (pth[k] == search && k != j)
				{
					times++;
				}
				if (toprint.left_son[pth[k]] == -1 && times == 1)
				{
					depthl[search]++;
				}
				if (toprint.left_son[pth[k]] == -1 && times == 2)
				{
					depthr[search]++;
				}
				if (times == 3)
				{
					break;
				}
			}
		}

		static int middle[10000];
		memset(middle, -1, sizeof(middle));
		int starter = 0, dfm = 0;
		for (int j = 0; j < dfs_pth; j++)
		{
			//printf("%d ",pth[j]);
			if (toprint.left_son[pth[j]] == -1 && toprint.right_son[pth[j]] == -1)
			{
				char buf_tmp[10000];
				for (int k = 0; k < (int)strlen(toprint.node[pth[j]]->identifier); k++)
				{
					if (toprint.node[pth[j]]->identifier[k] == ' ')
					{
						buf_tmp[k] = '\0';
						break;
					}
					buf_tmp[k] = toprint.node[pth[j]]->identifier[k];
				}
				outtextxy(945, pt + starter * space, buf_tmp);
				dfm = pt + starter * space + (ftsiz / 2);
				middle[pth[j]] = pt + starter * space + (ftsiz / 2);
				starter++;
			}
		}
		dfs3(middle, toprint.root[i]);
		//for (int j = 0; j < toprint.size; j++)
		//	{
		//printf("%d ", middle[j]);
		//}
		static int pth2[10000];
		memset(vis, 0, sizeof(vis));
		setcolor(EGEACOLOR(0xFF, BLACK));
		setlinewidth(ftsiz * 0.05);
		dfs2(toprint.root[i], 0, pth2, vis);
		int last_up = middle[pth2[1]];
		int last_dw = dfm ;
		double last_dis = 45.0;
		ege_line(45, last_up, 45, last_dw);
		ege_line(45, last_dw, last_dis + wida * toprint.edge_length[pth2[0]], last_dw);
		ege_line(45, last_up, 45 + wida * (toprint.edge_length[pth2[0]] - toprint.edge_length[pth2[1]]), last_up);
		for (int j = 1; j < dfs_pth2 - 1; j++)
		{
			if (vis[pth2[j]] == 0 && toprint.left_son[toprint.left_son[pth2[j]]] == -1)
			{
				double dis = last_dis + wida * (toprint.edge_length[pth2[j - 1]] - toprint.edge_length[pth2[j]]);
				double upper = middle[pth2[j]] - fabs(middle[toprint.left_son[pth2[j]]] - middle[pth2[j]]);
				double lower = middle[pth2[j]] + fabs(middle[toprint.right_son[pth2[j]]] - middle[pth2[j]]);
				ege_line(dis, upper, dis, lower);
				ege_line(dis, lower, dis + wida * (toprint.edge_length[pth2[j]]), lower);
				ege_line(dis, upper, dis + wida * (toprint.edge_length[pth2[j]]), upper);
				last_dis = dis;
			}
			else if (vis[pth2[j]] == 0 && toprint.left_son[toprint.left_son[pth2[j]]] != -1
			         && toprint.left_son[toprint.right_son[pth2[j]]] == -1)
			{

				double dis = last_dis + wida * (toprint.edge_length[pth2[j - 1]] - toprint.edge_length[pth2[j]]);
				double upper = middle[pth2[j]] - fabs(middle[pth2[j + 1]] - middle[pth2[j]]);
				double lower = middle[pth2[j]] + fabs(middle[pth2[j + 1]] - middle[pth2[j]]);
				ege_line(dis, upper, dis, lower);
				ege_line(dis, lower, dis + wida * (toprint.edge_length[pth2[j]]), lower);
				ege_line(dis, upper, dis + wida * (toprint.edge_length[pth2[j]] - toprint.edge_length[pth2[j + 1]]), upper);
				last_dis = dis;
			}
		}
		ege_line(45, lower_frame - 20, 945, lower_frame - 20);
		ege_line(45, lower_frame - 20, 45, lower_frame - 25);
		ege_line(945, lower_frame - 20, 945, lower_frame - 25);
		setfont(17, 0, "Cascadia Mono");
		//xyprintf(45 - textheight("T"), lower_frame - textwidth("T") - 5, "1.000");
		for (int j = 0; j < toprint.size; j++)
		{
			if (toprint.left_son[j] != -1)
			{
				double dis = 45 + wida * (1.0 - (toprint.edge_length[j]));
				ege_line(dis, lower_frame - 20, dis, lower_frame - 25);
				setfont(17, 0, "Cascadia Mono");
				if (j % 2 != 0)
					xyprintf(dis - textheight("T"), lower_frame - textwidth("T") - 10, "%.3lf", toprint.edge_length[j]);
				else
					xyprintf(dis - textheight("T"), lower_frame - 35 - textwidth("T"), "%.3lf", toprint.edge_length[j]);
			}
		}
	}
	setfont(15, 0, "Cascadia Mono");
	free_tree(&toprint);
}

int *dfs(int u, int rt, int *pth, int *vis)
{
	if (toprint.right_son[u] == -1 && toprint.left_son[u] == -1)
	{
		//printf("%d", toprint.left_son[u]);
		pth[dfs_pth++] = u;
		return pth;
	}
	if (vis[u] == 0)
	{
		pth[dfs_pth++] = u;
		vis[u] = 1;
		dfs(toprint.left_son[u], rt, pth, vis);
		pth[dfs_pth++] = u;
		dfs(toprint.right_son[u], rt, pth, vis);
		pth[dfs_pth++] = u;
		vis[u] = 0;
	}
	return NULL;
}

int *dfs2 (int u, int rt, int *pth2, int *vis)
{
	if (toprint.right_son[u] == -1 && toprint.left_son[u] == -1)
	{
		pth2[dfs_pth2++] = u;
		return pth2;
	}
	if (vis[u] == 0)
	{
		pth2[dfs_pth2++] = u;
		vis[u] = 1;
		dfs2(toprint.left_son[u], rt, pth2, vis);
		dfs2(toprint.right_son[u], rt, pth2, vis);
		vis[u] = 0;
	}
	return NULL;
}

int dfs3(int *mid, int u)
{
	if (mid[u] != -1)
		return mid[u];
	mid[u] = (dfs3(mid, toprint.left_son[u]) + dfs3(mid, toprint.right_son[u])) / 2;
	return mid[u];

}

void init_ui_3()
{
	setcaption("Life++ PhylogeneticTree");
	cleardevice();
	initgraph(1200, 800, INIT_RENDERMANUAL);
	PIMAGE init_img = newimage();
	getimage(init_img, "PNG", "UI_3");
	ege_enable_aa(true);
	ege_enable_aa(true, init_img);
	setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));
	putimage(0, 0, init_img);
	delimage(init_img);
	setcolor(BLACK);
	setfont(15, 0, "Cascadia Mono");
	//sys_edit editBox;
	endeditbox();
//_________________

	draw_pic();


}

int if_butt3B(int x, int y)
{
	if (x >= 1096 && x <= 1200 && y >= 10 && y <= 40)
		return 1;
	else
		return 0;

}


int if_butt3S(int x, int y)
{
	if (x >= 1096 && x <= 1200 && y >= 55 && y <= 85)
		return 1;
	else
		return 0;
}

void butt3S()
{
	setfillcolor(EGEARGB(0x73, 0xFF, 0xFF, 0xFF));
	ege_fillrect(1096, 55, 104, 30);
	PIMAGE save_img = newimage();
	getimage(save_img, 40, 90, 1120, 700);
	char op[100000] = "tree_";
	time_t timer;
	time(&timer);
	strcat(op, ctime(&timer));
	op[strlen(op) - 1] = '.';
	strcat(op, "bmp");
	for (int i = 0; i < (int) strlen(op); i++)
	{
		if (op[i] == ':')
			op[i] = '.';
	}
	//printf("%s", op);
	saveimage(save_img, op);
	delimage(save_img);

}


void butt3SS()
{
	PIMAGE butt_img = newimage();
	getimage(butt_img, "PNG", "UI_3");
	putimage(1096, 55, 104, 30, butt_img, 1096, 55);
	delimage(butt_img);
}


void butt3B()
{
	init_ui();
	//setfillcolor(EGEARGB(0x73, 0xFF, 0xFF, 0xFF));
	//ege_fillrect(1096, 35, 104, 30);
}



void butt3BB()
{
	PIMAGE butt_img = newimage();
	getimage(butt_img, "PNG", "UI_3");
	putimage(1096, 10, 104, 30, butt_img, 1096, 10);
	delimage(butt_img);
}


void butt3BBB()
{
	PIMAGE butt_img = newimage();
	getimage(butt_img, "PNG", "UI_1");
	putimage(1096, 35, 104, 30, butt_img, 1096, 35);
	delimage(butt_img);

}