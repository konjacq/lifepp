#ifndef UI_H
#define UI_H

#include <graphics.h>
#include <ege/sys_edit.h>
#include <stdio.h>
#include <string.h>

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
void endeditbox();

#endif