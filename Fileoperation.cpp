#include "head.h"

void ReadUserFile(){//���û��ļ��ж�ȡ�û����� 
	FILE *fp;
	if( fp = fopen(User_url,"rt") ){
		User *h;
		h = datalist.Userhead = NULL;
		User pause;
		while( fscanf(fp,"%s %s %s %d %d %s",pause.user_id,pause.name,pause.sex,&pause.age,&pause.isoperation,pause.pass) != EOF ){
			User *p = (User *)malloc(sizeof(User));
			strcpy(p->user_id,pause.user_id);
			strcpy(p->name,pause.name);
			strcpy(p->sex,pause.sex);
			p->age = pause.age;
			p->isoperation = pause.isoperation;
			strcpy(p->pass,pause.pass);
			p->next = NULL;
			if(h == NULL){
				datalist.Userhead = p;
				h = datalist.Userhead;
			}else{
				h->next = p;
				h = h->next;
			} 
		}
		fclose(fp);
	}else{
		cout << "ʧ�ܣ�" <<endl; 
	}
}

void ReadBookFile(){//���鼮�ļ��ж�ȡ�鼮���� 
	FILE *fp;
	if( fp = fopen(Book_url,"rt") ){
		Book_inf *h = datalist.Bookhead = NULL;
		Book_inf pause;
		while( fscanf(fp,"%s %s %s %s %d-%d-%d %d %f %d",pause.book_id,pause.book_name,pause.book_author,
		pause.book_public,&pause.d.year,&pause.d.mon,&pause.d.day,&pause.book_type,&pause.book_price,&pause.book_number) != EOF ){
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
			if(h == NULL){
				datalist.Bookhead = p;
				h = datalist.Bookhead;
			}else{
				h->next = p;
				h = h->next;
			} 
		}
		
	}else{
		cout << "ʧ��"<<endl;
	}
} 

bool addToFile(User pause){//���û��ļ����������� 
	bool is_success = false ;
	FILE *fp;
	if( fp = fopen(User_url,"at") ){
		fprintf(fp,"%s %s %s %d %d %s\n",pause.user_id,pause.name,pause.sex,pause.age,pause.isoperation,pause.pass);
		is_success = true;
	}else{
		cout << "д���ļ�ʧ��!" << endl;
	}
	return is_success;
}

bool add_to_bookFile(Book_inf pause){
	bool is_success = false;
	FILE *fp;
	if( fp = fopen(Book_url,"at") ){
		fprintf(fp,"%s %s %s %s %d-%d-%d %d %.2f %d\n",pause.book_id,pause.book_name,pause.book_author,pause.book_public,
		pause.d.year,pause.d.mon,pause.d.day,pause.book_type,pause.book_price,pause.book_number);
		is_success = true;
	}
	return is_success;
}

bool delete_from_file(){
	FILE *fp;
	bool is_success = false;
	if( fp = fopen(User_url,"wt") ){
		User *h = datalist.Userhead; 
		while(h != NULL){
			fprintf(fp,"%s %s %s %d %d %s\n",h->user_id,h->name,h->sex,h->age,h->isoperation,h->pass);
			h = h->next;
		}
		fclose(fp);
		is_success = true;
	}else{
		is_success = false;
	}
	return is_success;	
}
