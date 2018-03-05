#include "head.h"

void ReadUserFile(){//从用户文件中读取用户数据 
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
		cout << "失败！" <<endl; 
	}
}

void ReadBookFile(){//从书籍文件中读取书籍数据 
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
		fclose(fp);
	}else{
		cout << "失败"<<endl;
	}
} 

bool addToFile(User pause){//往用户文件中添加数据 
	bool is_success = false ;
	FILE *fp;
	if( fp = fopen(User_url,"at") ){
		fprintf(fp,"%s %s %s %d %d %s\n",pause.user_id,pause.name,pause.sex,pause.age,pause.isoperation,pause.pass);
		is_success = true;
		fclose(fp); 
	}else{
		cout << "写入文件失败!" << endl;
	}
	return is_success;
}

bool add_to_bookFile(Book_inf pause){
	bool is_success = false;
	FILE *fp;
	if( fp = fopen(Book_url,"at") ){
		fprintf(fp,"%s %20s %20s %20s %d-%02d-%02d %d %.2f %02d\n",pause.book_id,pause.book_name,pause.book_author,pause.book_public,
		pause.d.year,pause.d.mon,pause.d.day,pause.book_type,pause.book_price,pause.book_number);
		is_success = true;
		fclose(fp);
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
bool delete_from_bookfile(){
	FILE *fp;
	bool is_success = false;
	if( fp = fopen(Book_url,"wt") ){
		Book_inf *h = datalist.Bookhead; 
		while(h != NULL){
			fprintf(fp,"%s %20s %20s %20s %d-%02d-%02d %d %.2f %02d\n",h->book_id,h->book_name,h->book_author,h->book_public,
		h->d.year,h->d.mon,h->d.day,h->book_type,h->book_price,h->book_number);
			h = h->next;
		}
		fclose(fp);
		is_success = true;
	}else{
		is_success = false;
	}
	return is_success;	
}

