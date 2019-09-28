#include "head.h"

int login(){
	bool isSuccess;//�����û�ע��ģ�鷵��ֵ 
	int login_type = -1;//���յ�¼ģ�鷵��ֵ 
	ReadUserFile();//���ļ��ж�ȡ�û����� 
	do{
		if( datalist.Userhead == NULL ){
			cout << "ϵͳ�л�û���û�!" <<endl;
			cout << "��ע��" <<endl;
			isSuccess = Register();//ע�� 
			if(isSuccess){
				break; 
			}else{
				cout << "ע��ʧ��" <<endl;
				cout << "��ȷ���Ƿ����ע��(y/n)" <<endl;
				char is_continue = ' ';
				do{
					is_continue = getch();
					if( is_continue == 'n' ){
						break;
					}else if (is_continue != 'n' &&is_continue != 'y'){
						cout << "��������ַ��Ƿ�!" <<endl;
						cout << "����������!" << endl; 
					}
				}while(true);
			}
		}else{
			do{
				cout << "----------------------------��ѡ���¼ѡ�----------------------------" <<endl;
				cout << "|                                                                      |" <<endl;
				cout << "|1�û���¼ 2�û�ע�� 3����Ա��¼ 0�˳���¼                             |" <<endl;
				cout << "|                                                                      |" <<endl;
				cout << "------------------------------------------------------------------------" <<endl;
				int is_login = -1;
				cin >> is_login;
				if(is_login == 1){
					login_type = LoginToSystem(1);//��¼ 
					if(login_type == 1){
						cout << "��½�ɹ�" <<endl;
					}
					else{
						cout << "��½ʧ��" << endl;
						cout << "�����µ�½��" <<endl;
						login_type = -1;
					}
				}else if(is_login == 2){
					isSuccess = Register();
					if(isSuccess){
						cout << "ע��ɹ�" <<endl;
						break;
					}
					else{
						cout << "ע��ʧ��" << endl;
						cout << "������ע��!" <<endl;
					}
				}
				else if(is_login == 3){
					login_type = LoginToSystem(2);
					if(login_type == 2){
						cout << "��½�ɹ�" <<endl;
					}
					else{
						cout << "��½ʧ��" << endl;
						cout << "�����µ�½��" <<endl;
						login_type = -1;
					}
				} 
				else if(is_login == 0){
					login_type = 0;
					break;
				}else{
					cout << "�������ѡ��Ƿ�������������" <<endl;
					login_type = -1;
				}
			}while(login_type < 0);
		}
	}while( login_type < 0 );
	return login_type;
}

char* getpass(){
	char p[9];
	for(int i = 0 ;i <8 ;i++){
		p[i] = getch();
		putchar('*');
	}
	p[8] = '\0';
	cout << endl;
	char *a = (char *)malloc(sizeof(char)*9);
	strcpy(a,p);
	return a;
}

char* setId(int type){
	char id[9];
	tm* tm_ptr;
	tm_ptr = get_time();
	char a[2];
	int year = tm_ptr->tm_year+1900;
	int mon = tm_ptr->tm_mon+1;
	int day = tm_ptr->tm_mday;
	year = year%100;
	sprintf(a,"%02d",year);
	id[0] = a[0];
	id[1] = a[1];
	sprintf(a,"%02d",year);
	id[2] = a[0];
	id[3] = a[1];
	sprintf(a,"%02d",mon);
	id[4] = a[0];
	id[5] = a[1];
	id[6] = '0';
	id[7] = '0';
	id[8] = '\0';
	int num = 0;
	bool is_in = false;
	is_in = is_infile(id,2,type);
	if(is_in){
		num = get_num(id);
		if(num >= 0){
			sprintf(a,"%02d",num);
			id[6] = a[0];
			id[7] = a[1];
		}
	}
	char* is = (char *)malloc(sizeof(char)*9);
	strcpy(is,id);
	return is;
} 

bool addToList(User pause){
	bool is_success = false;
	User *h;
	h = datalist.Userhead;
	User *p = (User *)malloc(sizeof(User));
	strcpy(p->user_id,pause.user_id);
	strcpy(p->name,pause.name);
	strcpy(p->sex,pause.sex);
	p->age=pause.age;
	p->isoperation = pause.isoperation;
	strcpy(p->pass,pause.pass);
	if( h != NULL){
		while(h != NULL ){
			if( h->next == NULL ){
				h->next = p;
				is_success = true;
				break;
			}
			h = h->next;
		}
	}else{
		datalist.Userhead = p;
		is_success = true;	
	}
	return is_success;
}

bool Register(){
	bool is_success = false;
	int grade = 0;
	do{
		cout << "���������Ĺ���ԱȨ�޵ȼ�(0 ��ͨ�û� 1 ϵͳ����Ա -1 �˳�ע��)" << endl;
		cin >> grade;
		if(grade == 0 || grade == 1 || grade == -1){
			break;
		}else{
			cout << "������ĵȼ��Ƿ�������������" <<endl;
		}
	}while(true);
	if(grade == -1)
		return false; 
	User pause;
	cout << "������id:";
	cin >> pause.user_id; 
	cout << "�������û�����";
	cin >>pause.name ;
	cout << endl;
	cout << "�������Ա�";
	cin >> pause.sex;
	cout << endl;
	cout << "���������䣺";
	cin >> pause.age;
	pause.isoperation = grade;
	cout << endl;
	cout << "���������룺";
	char *p;
	p = getpass();
	strcpy(pause.pass,p);
	free(p);
//	char *a; 
//	a = setId(grade+1);
//	strcpy(pause.user_id,a);
//	free(a);
	is_success = addToList(pause);
	is_success = addToFile(pause);
	return is_success;  
}

int LoginToSystem(int type){//��¼ϵͳ 
	bool is_success = false;
	char name[21];
	char pass[9];
	cout << "�������û���:";
	cin >> name;
	cout << endl;
	is_success = is_infile( name,0,type );//ȷ���ļ����Ƿ�����ַ��� 
	if( !is_success ){
		cout << "��������û��������ڣ�" << endl;
		system("pause");
		return 0;
	}
	cout << "����������:";
	char *a;
	a = getpass();
	strcpy(pass,a);
	is_success = is_infile(pass,1,type);
	if( !is_success){
		cout << "�������" <<endl;
		type = 0;
	}
	return type;
}
 
bool is_infile( char *str , int ispass, int type){
	bool is_in = false;
	User *h;
	h = datalist.Userhead;
	char *pa;
	while(h != NULL){
		if(ispass == 0){
			strcpy(pa,h->name);	
		}else if(ispass == 1){
			strcpy(pa,h->pass);
		}else if(ispass == 2){
			strcpy(pa,h->user_id);
		}
		
		if( (strcmp(pa,str)) == 0 && h->isoperation == (type-1) ){
			is_in = true;
			if(ispass == 1 && is_in ){
				this_user = h;
			} 
			break;
		}
		else
			is_in = false;
		h = h->next;
	}
	return is_in;
}



int get_num(char id[9]){
	int num;
	int n[1000] = {-1};
	char a[2];
	int i = 0;
	User *h1;
	h1 = datalist.Userhead;
	while(h1 != NULL){
		if(id[0] == h1->user_id[0] && id[1] == h1->user_id[1] && id[2] == h1->user_id[2] && id[3] == h1->user_id[3] && 
		id[4] == h1->user_id[4] && id[5] == h1->user_id[5]){
			a[0] = h1->user_id[6];
			a[1] = h1->user_id[7];
			n[i] = atoi(a);
			i++;
		}
		h1 = h1->next;
	}
	i = 0;
	num = n[0];
	while(n[i] != -1){
		if(n[i] > num)
			num = n[i];
		i++;
	}
	return num; 
}
