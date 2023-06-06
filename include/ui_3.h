#ifndef UI_3_H
#define UI_3_H

#include <graphics.h>
#include <ege/sys_edit.h>
#include <stdio.h>
#include <string.h>
#include "connector.h"
//#include <connector.h>



void init_ui_3();
int if_butt3B(int x, int y);
void butt3B();
void butt3BB();
void butt3BBB();
int if_butt3S(int x, int y);
void butt3S();
void butt3SS();
void draw_pic();
int *dfs(int u, int rt, int *pth, int *vis);
int *dfs2(int u, int rt, int *pth, int *vis);
int dfs3(int *mid, int u);
#endif
