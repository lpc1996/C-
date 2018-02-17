#include "head.h"

void print_book(){
	Book_inf *h;
	h = datalist.Bookhead;
	if(h != NULL){
		cout << " -----------------------------------------------------------------------------------------------------------" <<endl;
		printf("| 编号   |             名称   |        作者        |        出版社      | 出版日期 |  类型 | 价格| 在库数量 |\n"); 
		while(h != NULL){
			printf("|%s|%20s|%20s|%20s|%d-%02d-%02d|   %02d  |%05.2f|%8d  |\n", h->book_id , h->book_name , h->book_author, h->book_public,h->d.year,h->d.mon,
			h->d.day,h->book_type, h->book_price, h->book_number );
			h = h->next;
		}
		cout << " -----------------------------------------------------------------------------------------------------------" <<endl;
	}else{
		cout << "书库中暂时没有书籍，请稍后再来！" <<endl;
	}
}

bool isin_bookfile(char id[9]){
	Book_inf *h;
	bool is_in = false;
	h = datalist.Bookhead;
	if( h == NULL ){
		is_in = false;
	}else{
		while( h != NULL ){
			if( (strcpy(id,h->book_id)) == 0 ){
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
