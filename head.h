#ifndef _HEAD_H_INCLUDED
#define _HEAD_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define User_url "D:\\workspace\\dev-c++\\����\\ͼ�����ϵͳ\\�û�.txt"
#define Book_url "D:\\workspace\\dev-c++\\����\\ͼ�����ϵͳ\\book_info.txt" 
#define Booktype_url "D:\\workspace\\dev-c++\\����\\ͼ�����ϵͳ\\book_type.txt" 

using namespace std;

typedef struct _user{
    char user_id[9];
    char name[21];
    char sex[4];
    int age;
    int isoperation;
    char pass[9];
    struct _user *next;
}User;

typedef struct _day{
	int year;
	int mon;
	int day;
}date;

typedef struct _book{
	char book_id[9];//�鼮��� 
	char book_name[51];//���� 
	char book_author[100];//���� 
	char book_public[50];//������ 
	date d;//�������� 
	int book_type;//�鼮���� 
	float book_price;//�鼮�۸� 
	int book_number;//�鼮���� 
	struct _book *next;
}Book_inf;

typedef struct _list{
    User *Userhead;
    Book_inf *Bookhead;
}ListHead;

extern void ReadUserFile();
extern int login();
extern char* getpass();
extern bool addToList(User pause);
extern bool addToFile(User pause);
extern char* setId(int type);
extern bool Register();
extern bool is_infile( char str[] , int ispass ,int type);
extern int LoginToSystem(int type);
extern int get_num(char id[9]);
extern void Readermenu();
extern void operator_menu();
extern bool buy_book();
extern void ReadBookFile();
extern void put_data();
extern void print_book();
extern bool isin_bookfile(char id[9]);
extern char *set_bookid();
extern int get_booknum( char id[9] );
extern bool add_to_book_list(Book_inf pause);
extern bool add_to_bookFile(Book_inf pause); 
extern tm* get_time();
extern void manage_reader();
extern bool delete_from_datalist(int type,char str[21]);
extern bool delete_reader();
extern bool delete_from_file(); 

extern ListHead datalist;

#endif
