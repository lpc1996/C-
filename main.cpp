#include "head.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

ListHead datalist;
User *this_user; 

int main(int argc, char** argv) {
//	int login_type;
//	login_type = login();
//	ReadBookFile();
//	if(login_type == 1){
//		system("cls");
//		cout << this_user->name << "��ӭ��" <<endl; 
//		Readermenu();
//	}else if( login_type == 2 ){
//		system("cls");
//		cout << this_user->name << "��ӭ��" <<endl;
//		operator_menu();
//	}
//	cout << "�ټ���" << endl;
	read_SettingFile();
	//buy_book();
	system("pause");
	return 0;
}

tm* get_time(){
	time_t date_time;
	struct tm *tm_ptr = NULL;
	time(&date_time);
	tm_ptr = gmtime(&date_time);
	tm_ptr = localtime(&date_time);
	return tm_ptr;
}

void put_data(){
	User *h;
	h = datalist.Userhead;
	cout << " ----------------------------------------" << endl;
	printf("|���    |    ����  |�Ա�|����|����Ա�ȼ�|\n"); 
	while(h != NULL ){
		printf("|%s|%10s| %s | %02d |     %d    |\n",h->user_id,h->name,h->sex,h->age,h->isoperation);
		h = h->next;
	}
	cout << " ----------------------------------------" << endl;
}
