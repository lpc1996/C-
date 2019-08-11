#include "head.h"

void print_book(){
	Book_inf *h;
	h = datalist.Bookhead;
	if(h != NULL){
		cout << " -----------------------------------------------------------------------------------------------------------" <<endl;
		printf("| ���   |             ����   |        ����        |        ������      | �������� |  ���� | �۸�| �ڿ����� |\n"); 
		while(h != NULL){
			printf("|%s|%20s|%20s|%20s|%d-%02d-%02d|   %02d  |%05.2f|%8d  |\n", h->book_id , h->book_name , h->book_author, h->book_public,h->d.year,h->d.mon,
			h->d.day,h->book_type, h->book_price, h->book_number );
			h = h->next;
		}
		cout << " -----------------------------------------------------------------------------------------------------------" <<endl;
	}else{
		cout << "�������ʱû���鼮�����Ժ�������" <<endl;
	}
}

bool isin_bookfile(char id[]){
	Book_inf *h;
	bool is_in = false;
	h = datalist.Bookhead;
	if( h == NULL ){
		is_in = false;
	}else{
		while( h != NULL ){
			if( (strcmp(id,h->book_id)) == 0 ){
				is_in = true;
				break;
			}
			h = h->next; 
		}
	}
	return is_in;
}

int get_booknum( char id[9] ){
	Book_inf *h;
	h = datalist.Bookhead;
	int num[1000] = {-1};
	int n = 0;
	int j = 0;
	char a[2];
	char b[7];
	char c[7];
	for(int i = 0 ; i < 6 ; i++){
		b[i] = id[i];
	}
	b[6] = '\0';
	while(h != NULL){
		for(int i = 0 ; i < 6 ; i++){
			c[i] = h->book_id[i];
		}
		c[6] = '\0';
		if(strcmp(c,b) == 0){
			a[0] = h->book_id[6];
			a[1] = h->book_id[7]; 
			num[j] = atoi(a);
			j++;
		}
		h = h->next;
	} 
	n = num[0];
	for(int i = 0; i < 1000  && num[i] != -1 ; i++){
		if( n<num[i] &&num[i] != -1 ){
			n = num[i];
		}
	} 
	n = n+1;
	return n;
}

bool add_to_book_list(Book_inf pause){
	bool is_success = false;
	Book_inf *h = datalist.Bookhead;
	Book_inf *p = (Book_inf *)malloc(sizeof(Book_inf));
	strcpy(p->book_id,pause.book_id);
	strcpy(p->book_name,pause.book_name);
	strcpy(p->book_author,pause.book_author);
	strcpy(p->book_public,pause.book_public);
	p->d.year = pause.d.year;
	p->d.mon = pause.d.mon;
	p->d.day = pause.d.day;
	p->book_type = pause.book_type;
	p->book_price = pause.book_price;
	p->book_number = pause.book_number;
	p->next = NULL;
	if(h != NULL){
		while( h != NULL ){
			if( h ->next == NULL ){
				h->next = p;
				is_success = true;
				break;
			}
			h = h->next;
		}
	}else{
		datalist.Bookhead = p;
		is_success = true;
	}
	return is_success;
}

bool add_to_borrow_List(Borrow_book borrow){
	bool is_success = false;
	Borrow_book *h = datalist.BorrowHead;
	Borrow_book *p = (Borrow_book *)malloc(sizeof(Borrow_book));
	p->recdor=borrow.recdor;
	strcpy(p->User_id,borrow.User_id);
	strcpy(p->Book_id,borrow.Book_id);
	p->Borrow_time.year = borrow.Borrow_time.year;
	p->Borrow_time.mon = borrow.Borrow_time.mon;
	p->Borrow_time.day = borrow.Borrow_time.day;
	p->days=borrow.days;
	p->is_return=borrow.is_return;
	p->next = NULL;
	if( h != NULL){
		while( h != NULL ){
			if( h->next == NULL ){
				h->next = p;
				is_success = true;
				break;
			}
			h = h->next;
		}
	}else{
		datalist.BorrowHead=p;
		is_success = true;
	}
	return is_success;	
}

bool change_book_menu(){
	bool is_success = false;
	int is_continue = -1;
	char str[100];
	cout << " ---------------------------------------------------------------------- " <<endl;
	cout << "|                                                                      |" <<endl; 
	cout << "|                             ɾ��������Ϣ                             |" <<endl;
	cout << "| 1ͼ����   2ͼ������   0�˳�                                        |" <<endl;
	cout << "|                                                                      |" <<endl;
	cout << " ---------------------------------------------------------------------- " <<endl;
	cin >> is_continue;
	if(is_continue == 1){
		cout << "������Ҫ�޸ĵ�ͼ����:";
	}else if(is_continue == 2){
		cout << "������Ҫ�޸ĵ�ͼ������:";
	}else{
		return false; 
	}
	cin >> str;
	is_success = change_book(is_continue,str);
	return is_success;
}

Book_inf* search_book_list(int type,char str[100]){
	bool is_success = false;
	Book_inf *h = datalist.Bookhead;
	while(h){
		if(type == 1){
			if( strcmp(str,h->book_id) == 0 ){
				is_success = true;
				break;
			}
		}else if(type == 2){
			if( strcmp(str,h->book_name) == 0){
				is_success = true;
				break;
			}
		}
		if(is_success){
			printf("| ���   |             ����   |        ����        |        ������      | �������� |  ���� | �۸�| �ڿ����� |\n"); 
			printf("|%s|%20s|%20s|%20s|%d-%02d-%02d|   %02d  |%05.2f|%8d  |\n", h->book_id , h->book_name , h->book_author, h->book_public,h->d.year,h->d.mon,
			h->d.day,h->book_type, h->book_price, h->book_number );
		}
		h = h->next;
	}
	return h;
}

bool change_book(int type,char str[100]){
	bool is_success = false;
	Book_inf* p = NULL;
	p = search_book_list(type,str);
	if(p != NULL){
		printf("| ���   |             ����   |        ����        |        ������      | �������� |  ���� | �۸�| �ڿ����� |\n"); 
		printf("|%s|%20s|%20s|%20s|%d-%02d-%02d|   %02d  |%05.2f|%8d  |\n", p->book_id , p->book_name , p->book_author, p->book_public,p->d.year,p->d.mon,
		p->d.day,p->book_type, p->book_price, p->book_number );
		int is_continue = -1;
		char c;
		do{
			cout << " ---------------------------------------------------------------------- " <<endl;
			cout << "|                                                                      |" <<endl; 
			cout << "|                           Ҫ�޸ĵ�ͼ����Ϣ                           |" <<endl;
			cout << "| 1ͼ������   2ͼ������   3ͼ�������   4��������    5����   6�۸�     |" <<endl;
			cout << "| 7�ڿ�����   0�˳�                                                    |" <<endl;
			cout << "|                                                                      |" <<endl;
			cout << " ---------------------------------------------------------------------- " <<endl;
			cin >> is_continue;
			switch(is_continue){
				case 1:
					cout << "������ͼ������:" ;
					cin >> p->book_name;
					break;
				case 2:
					cout << "������ͼ������:" ;
					cin >> p->book_author;
					break;
				case 3:
					cout << "������ͼ�������:";
					cin >> p->book_public;
					break;
				case 4:
					cout << "������ͼ���������:";
					scanf("%d",&p->d.year);cout << "�� ";
					scanf("%d",&p->d.mon); cout << "�� ";
					scanf("%d",&p->d.day);cout << "��"<<endl;
					break;
				case 5:
					cout << "���������ͱ��:";
					cin >> p->book_type;
					break;
				case 6:
					cout << "������۸�:";
					cin >> p->book_price;
					break;
				case 7:
					cout << "�������ڿ�����:";
					cin >> p->book_number;
					break;
				case 0:
					cout << "�˳�" <<endl;
					is_success = false;
					break;
				default:
					cout << "�������ѡ��Ƿ�,���������룡"<<endl;
					break;
			}
			cout << "��ȷ���Ƿ�����޸�(y/n):";
			do{
				cin >> c;
				if(c != 'y' && c != 'n'){
					cout << "�������ѡ����������������!"<<endl;
				}
				if(c == 'n'){
					break;
				}
			}while(c != 'n' && c != 'y');
			if(c == 'n'){
				break;
			}
		}while(is_continue != 0 || c != 'n');
		cout << "��ȷ�����Ƿ�Ҫ�޸��Ȿͼ�����Ϣ(y/n):";
		do{
			cin >> c;
			if( c == 'y' ){
				is_success = delete_from_bookfile(); 
				break;
			}else if(c == 'n'){
				is_success = false;
				break;
			}else{
				cout << "�������ѡ����������������!" <<endl; 
			}
		}while(c != 'y' || c != 'n');
	}else{
		cout << "��������Ҳ���ͼ��" << str << endl;
		is_success = false; 
	}
	return is_success;
}

bool change_borrow_List(char *book_id){
	bool is_success = false;
	Borrow_book *h = datalist.BorrowHead;
	while(h != NULL){
		if( strcmp(h->User_id ,this_user->user_id) == 0 && strcmp(h->Book_id,book_id) == 0){
			h->recdor = 1;
			is_success = true;
			break;
		}
		h = h->next;
	}
	Book_inf *bh = datalist.Bookhead;
	if(is_success){
		 while(bh != NULL){
		 	if(strcmp(bh->book_id,book_id) == 0){
		 		bh->book_number++;
		 		is_success = true;
		 		break;
			 }
			 bh = bh->next;
		 }
	}
	return is_success;
}
