#include "head.h"

void Readermenu(){
	int operat_type = -1;
	do{
		cout << " ----------------------------------------------------------------------" <<endl;
		cout << "|                                                                      |" <<endl;
		cout << "|                              ͼ�����ϵͳ                            |" <<endl;
		cout << "| 1��ӡ����ͼ�鼰����Ϣ   2ͼ�����   3ͼ��黹   4��ѯ�鼮��Ϣ        |" <<endl;
		cout << "| 5ͼ�����ͳ��   6ע���˻�   0�˳�                                    |" <<endl;
		cout << "|                                                                      |" <<endl;
		cout << " ----------------------------------------------------------------------" <<endl;	
		cin >> operat_type;
		switch(operat_type){
			case 1:
				print_book();
				break;
			case 2:
				borrow_book();
				break;
			case 3:
				return_book();
				break;
			case 4:
				cout << "��ѯ�鼮��Ϣ " <<endl;
				break;
			case 5:
				cout << "ͼ�����ͳ��" << endl;
				break;
			case 6:
				cout << "ע��" <<endl;
				break; 
			case 0:
				cout << "�˳�" <<endl;
				break;
			default: 
				cout << "�������ѡ��Ƿ�������������!" <<endl;
				system("pause");
				system("cls");
				break;	
		}
	}while( operat_type != 0 );
}

void operator_menu(){
	bool is_success = false;
	int operat_type = -1;
	do{
		cout << " ----------------------------------------------------------------------" <<endl;
		cout << "|                                                                      |" <<endl;
		cout << "|                              ͼ�����ϵͳ                            |" <<endl;
		cout << "| 1��ӡ����ͼ�鼰����Ϣ   2������Ϣ����   3�鼮�����黹��¼          |" <<endl;
		cout << "| 4��ѯ�鼮��Ϣ   5ͼ�����ͳ��    6ͼ������   7ɾ��ͼ����Ϣ           |" <<endl;
		cout << "| 8�޸�ͼ����Ϣ   0�˳�                                                |" <<endl;
		cout << "|                                                                      |" <<endl;
		cout << " ----------------------------------------------------------------------" <<endl;
		cin >> operat_type;
		switch(operat_type){
			case 1:
				system("cls");
				print_book();
				break;
			case 2:
				system("cls"); 
				manage_reader();
				break;
			case 3: 
				system("cls");
				cout <<"�鼮�����黹����" <<endl;
				break;
			case 4: 
				system("cls");
				cout <<"��ѯ�鼮��Ϣ" <<endl;
				break;
			case 5:
				system("cls");
				cout << "ͼ�����ͳ��" <<endl;
				break;
			case 6: 
				system("cls");
				is_success = buy_book();
				if(is_success){
					cout << "�ɹ�" <<endl;
				}else{
					cout << "ʧ��" <<endl;
				}
				break;
			case 7 :
				system("cls");
				is_success = delete_book();
				if(is_success){
					cout << "�ɹ�" <<endl;
				}else{
					cout << "ʧ��" <<endl;
				}
				break;
			case 8:
				system("cls");
				is_success = change_book_menu(); 
				if(is_success){
					cout << "�ɹ�" <<endl;
				}else{
					cout << "ʧ��" <<endl;
				}
				break;
			case 0:
				cout << "�˳�" << endl;
				break;
			default:
				system("cls");
				cout << "�������ѡ��Ƿ�������������!" <<endl;
				system("pause");
				system("cls");
				break; 	
		}
	}while(operat_type != 0); 
}

bool buy_book(){//���ͼ�� 
	bool is_success = false;
	Book_inf pause;
//	char *is = setId();//�����鼮��� 
//	strcpy(pause.book_id,is);
//	free(is);
	cout << "������ͼ��ID��" ;
	cin >> pause.book_id;
	cout << "������ͼ������:" ;
	cin >> pause.book_name;
	cout << endl;
	cout << "������ͼ������:" ;
	cin >> pause.book_author;
	cout << endl;
	cout << "������ͼ�������:"; 
	cin >> pause.book_public; 
	cout << endl;
	cout << "�������������" << endl;
	cout << "��"; cin>>pause.d.year;
	cout << "��"; cin >>pause.d.mon;
	cout << "��"; cin >>pause.d.day;
	cout <<endl;
	cout << "������ͼ�������:";
	cin >> pause.book_type;
	cout << endl; 
	cout << "�����뵥��:";
	cin >> pause.book_price;
	cout << endl;
	cout << "�����������鼮����:";
	cin >> pause.book_number;
	cout << endl;
	is_success = add_to_book_list(pause);//����������������� 
	is_success = add_to_bookFile(pause);//���ļ���׷��������
	//system("cls"); 
	return is_success;
}

void borrow_book(){//ͼ����� 
	Borrow_book cont;
	while(true){
		cout << "��������Ҫ���ĵ�ͼ���ţ�";
		char id[9];
		cin >> id;
		if(isin_bookfile(id)){
			strcpy(cont.Book_id,id);
			break;
		}
		cout << "�������ͼ���Ų����ڣ����������룡" <<endl;
	}
	cout << "������Ҫ���ĵ�������";
	cin >> cont.days;
	cout << "��������ļ�¼��ţ�";
	cin >> cont.recdor;
	strcpy(cont.User_id,this_user->user_id);
	tm* time = get_time();
	cont.Borrow_time.year=time->tm_year+1900;
	cont.Borrow_time.mon=time->tm_mon+1;
	cont.Borrow_time.day=time->tm_mday;
	cont.is_return = 0;
	if(add_to_borrow_List(cont)){
		if(add_to_borrow_file(cont)){
			cout << "��ϲ�㣬����ɹ�������" << cont.days << "������֮ǰ���飡" <<endl;
		}else{
			cout << "����ʧ�ܣ�" <<endl;
		}
	}else{
		cout << "����ʧ�ܣ�" <<endl;
	}
}

char* setId(){
	char num[9];
	tm* tm_ptr;
	tm_ptr = get_time();//��ȡϵͳ��ǰʱ�� 
	char a[2];
	int year = tm_ptr->tm_year+1900;
	int mon = tm_ptr->tm_mon+1;
	int day = tm_ptr->tm_mday;
	year = year%100;
	itoa(year,a,10);
	if(year < 10){
		num[0] = '0';
		num[1] = a[0];
	}else{
		num[0] = a[0];
		num[1] = a[1];
	}
	itoa(mon,a,10);
	if(mon < 10){
		num[2] = '0';
		num[3] = a[0];
	}else{
		num[2] = a[0];
		num[3] = a[1];
	}
	itoa(day,a,10);
	if(day < 10){
		num[4] = '0';
		num[5] = a[0];
	}else{
		num[4] = a[0];
		num[5] = a[1];
	}
	num[6] = '0';
	num[7] = '0';
	num[8] = '\0';
	bool is_in = false;
	is_in = isin_bookfile(num);//ȷ�ϸ��ַ�����û���������� 
	if(is_in){
		int n = get_booknum(num);//��ȡ��� 
		n = n+1; 
		if(n >= 0){
			itoa(n,a,10);
			if(n < 10 ){
				num[6] = '\0';
				num[7] = a[0];
			}else{
				num[6] = a[0];
				num[7] = a[1];
			}
		}
	}
	char *p = (char *)malloc(sizeof(char)*9);
	strcpy(p,num);
	return p;
}

void manage_reader(){
	int operat_type = 0;
	do{
		operat_type = 0;
		cout << " ---------------------------------------------------------------------- " <<endl;
		cout << "|                                                                      |" <<endl;  
		cout << "|                            ������Ϣ����                              |" <<endl;
		cout << "| 1��ӡ������Ϣ   2ɾ��������Ϣ   3�޸Ķ�����Ϣ   0�����ϼ��˵�        |" <<endl; 
		cout << "|                                                                      |" <<endl; 
		cout << " ---------------------------------------------------------------------- " <<endl;  
		cin >> operat_type ;
		bool is_success = false;
		switch(operat_type){
			case 1:
				put_data();
				break;
			case 2:
				is_success = delete_reader();
				if(is_success){
					cout << "�ɹ�!" <<endl; 
				}else{
					cout << "ʧ��!" <<endl; 
					operat_type = 0;
				}
				break;
			case 3:
				cout << "�޸�" <<endl;
				break;
			case 0:
				cout << "������һ��"<<endl;
				break;
			default:
				cout << "�������ѡ��Ƿ������������룡" <<endl;
				break;
		}                   
	}while(operat_type != 0);
}

bool delete_reader(){
	int is_continue = -1;
	bool is_success = false;
	char str[21];
	cout << " ---------------------------------------------------------------------- " <<endl;
	cout << "|                                                                      |" <<endl; 
	cout << "|                             ɾ��������Ϣ                             |" <<endl;
	cout << "| 1���߱��   2��������   0�˳�                                        |" <<endl;
	cout << "|                                                                      |" <<endl;
	cout << " ---------------------------------------------------------------------- " <<endl;
	cin >> is_continue;
	if(is_continue == 1){
		cout << "������Ҫɾ���Ķ��߱�ţ�";
	}else if(is_continue == 2){
		cout << "������Ҫɾ���Ķ���������";
	}else{
		return false;
	}
	cin >> str;
	is_success = delete_from_datalist(is_continue,str); 
	is_success = delete_from_file();
	return is_success;
} 

bool delete_from_datalist(int type,char str[21]){
	bool is_success = false;
	User *h;
	h = datalist.Userhead;
	User *q = NULL; 
	while( h != NULL ){
		if(type == 1){
			if( strcmp(h->user_id ,str) == 0 ){
				is_success = true;
			}
		}else if(type == 2){
			if(strcmp(h->name,str) == 0){
				is_success = true;
			}
		}
		if(is_success){
			if( h == datalist.Userhead){
				User *p = datalist.Userhead;
				datalist.Userhead = datalist.Userhead->next;
				h = datalist.Userhead; 
				free(p);
				is_success = true;
			}else{
				User *p = h;
				q->next = h->next;
				free(p);
				is_success = true;
			}
		}
		q = h;
		h = h->next;
	}
	return is_success;
}

bool delete_book(){
	bool is_success = false;
	char str[100];
	cout << " ---------------------------------------------------------------------- " <<endl;
	cout << "|                                                                      |" <<endl;
	cout << "|                              ɾ��ͼ����Ϣ                            |" <<endl;
	cout << "| 1ͼ����   2ͼ������   0�����ϼ��˵�                                |" <<endl;
	cout << "|                                                                      |" <<endl;
	cout << " ---------------------------------------------------------------------- " <<endl;
	int is_continue = -1;
	cin >> is_continue;
	if(is_continue == 1){
		cout << "������Ҫɾ����ͼ���ţ�"; 
	}else if(is_continue == 2){
		cout << "������Ҫɾ����ͼ�����ƣ�";
	}else{
		return false;
	}
	cin >> str;
	is_success = delete_from_booklist(is_continue,str);
	is_success = delete_from_bookfile();
	return is_success;
 }
 
bool delete_from_booklist(int type,char str[100]){
	bool is_success = false;
	Book_inf* h = datalist.Bookhead;
	Book_inf* q = NULL;
	while( h!=NULL ){
		if( type == 1 ){
			if( strcmp(h->book_id,str) ==0 ){
				is_success = true;
			}
		}else if(type == 2){
			if( strcmp(h->book_name,str) ==0 ){
				is_success = true;
			}
		}
		
		if( is_success ){
			if(h == datalist.Bookhead ){
				q = datalist.Bookhead;
				datalist.Bookhead = datalist.Bookhead->next;
				h = datalist.Bookhead;
				free(q);
				is_success = true;
			}else{
				Book_inf *p = h;
				q->next = h->next;
				free(p);
				is_success = true; 
			}
			break;
		}
		q = h;
		h = h->next;
	}
	return is_success;
}

void return_book(){
	cout << "������Ҫ�黹��ͼ��ID��";
	char id[9];
	cin >> id;
	if(change_borrow_List(id)){
		change_borrow_file(); 
		delete_from_bookfile();
		cout << "����ɹ���" <<endl;
	}else{
		cout << "����ʧ�ܣ�" <<endl;
	}
}
