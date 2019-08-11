#include "head.h"

void Readermenu(){
	int operat_type = -1;
	do{
		cout << " ----------------------------------------------------------------------" <<endl;
		cout << "|                                                                      |" <<endl;
		cout << "|                              图书管理系统                            |" <<endl;
		cout << "| 1打印现有图书及其信息   2图书借阅   3图书归还   4查询书籍信息        |" <<endl;
		cout << "| 5图书分类统计   6注销账户   0退出                                    |" <<endl;
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
				cout << "查询书籍信息 " <<endl;
				break;
			case 5:
				cout << "图书分类统计" << endl;
				break;
			case 6:
				cout << "注销" <<endl;
				break; 
			case 0:
				cout << "退出" <<endl;
				break;
			default: 
				cout << "你输入的选项非法，请重新输入!" <<endl;
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
		cout << "|                              图书管理系统                            |" <<endl;
		cout << "| 1打印现有图书及其信息   2读者信息管理   3书籍借出与归还记录          |" <<endl;
		cout << "| 4查询书籍信息   5图书分类统计    6图书买入   7删除图书信息           |" <<endl;
		cout << "| 8修改图书信息   0退出                                                |" <<endl;
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
				cout <<"书籍借出与归还管理" <<endl;
				break;
			case 4: 
				system("cls");
				cout <<"查询书籍信息" <<endl;
				break;
			case 5:
				system("cls");
				cout << "图书分类统计" <<endl;
				break;
			case 6: 
				system("cls");
				is_success = buy_book();
				if(is_success){
					cout << "成功" <<endl;
				}else{
					cout << "失败" <<endl;
				}
				break;
			case 7 :
				system("cls");
				is_success = delete_book();
				if(is_success){
					cout << "成功" <<endl;
				}else{
					cout << "失败" <<endl;
				}
				break;
			case 8:
				system("cls");
				is_success = change_book_menu(); 
				if(is_success){
					cout << "成功" <<endl;
				}else{
					cout << "失败" <<endl;
				}
				break;
			case 0:
				cout << "退出" << endl;
				break;
			default:
				system("cls");
				cout << "你输入的选项非法，请重新输入!" <<endl;
				system("pause");
				system("cls");
				break; 	
		}
	}while(operat_type != 0); 
}

bool buy_book(){//添加图书 
	bool is_success = false;
	Book_inf pause;
//	char *is = setId();//生成书籍编号 
//	strcpy(pause.book_id,is);
//	free(is);
	cout << "请输入图书ID：" ;
	cin >> pause.book_id;
	cout << "请输入图书名称:" ;
	cin >> pause.book_name;
	cout << endl;
	cout << "请输入图书作者:" ;
	cin >> pause.book_author;
	cout << endl;
	cout << "请输入图书出版社:"; 
	cin >> pause.book_public; 
	cout << endl;
	cout << "请输入出版日期" << endl;
	cout << "年"; cin>>pause.d.year;
	cout << "月"; cin >>pause.d.mon;
	cout << "日"; cin >>pause.d.day;
	cout <<endl;
	cout << "请输入图书类别编号:";
	cin >> pause.book_type;
	cout << endl; 
	cout << "请输入单价:";
	cin >> pause.book_price;
	cout << endl;
	cout << "请输入买入书籍数量:";
	cin >> pause.book_number;
	cout << endl;
	is_success = add_to_book_list(pause);//想链表中添加新数据 
	is_success = add_to_bookFile(pause);//向文件中追加新数据
	//system("cls"); 
	return is_success;
}

void borrow_book(){//图书借阅 
	Borrow_book cont;
	while(true){
		cout << "请输入你要借阅的图书编号：";
		char id[9];
		cin >> id;
		if(isin_bookfile(id)){
			strcpy(cont.Book_id,id);
			break;
		}
		cout << "你输入的图书编号不存在，请重新输入！" <<endl;
	}
	cout << "请输入要借阅的天数：";
	cin >> cont.days;
	cout << "请输入借阅记录序号：";
	cin >> cont.recdor;
	strcpy(cont.User_id,this_user->user_id);
	tm* time = get_time();
	cont.Borrow_time.year=time->tm_year+1900;
	cont.Borrow_time.mon=time->tm_mon+1;
	cont.Borrow_time.day=time->tm_mday;
	cont.is_return = 0;
	if(add_to_borrow_List(cont)){
		if(add_to_borrow_file(cont)){
			cout << "恭喜你，借书成功，请于" << cont.days << "日期限之前还书！" <<endl;
		}else{
			cout << "借书失败！" <<endl;
		}
	}else{
		cout << "借书失败！" <<endl;
	}
}

char* setId(){
	char num[9];
	tm* tm_ptr;
	tm_ptr = get_time();//获取系统当前时间 
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
	is_in = isin_bookfile(num);//确认该字符串有没有在链表中 
	if(is_in){
		int n = get_booknum(num);//获取序号 
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
		cout << "|                            读者信息管理                              |" <<endl;
		cout << "| 1打印读者信息   2删除读者信息   3修改读者信息   0返回上级菜单        |" <<endl; 
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
					cout << "成功!" <<endl; 
				}else{
					cout << "失败!" <<endl; 
					operat_type = 0;
				}
				break;
			case 3:
				cout << "修改" <<endl;
				break;
			case 0:
				cout << "返回上一级"<<endl;
				break;
			default:
				cout << "你输入的选项非法，请重新输入！" <<endl;
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
	cout << "|                             删除读者信息                             |" <<endl;
	cout << "| 1读者编号   2读者姓名   0退出                                        |" <<endl;
	cout << "|                                                                      |" <<endl;
	cout << " ---------------------------------------------------------------------- " <<endl;
	cin >> is_continue;
	if(is_continue == 1){
		cout << "请输入要删除的读者编号：";
	}else if(is_continue == 2){
		cout << "请输入要删除的读者姓名：";
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
	cout << "|                              删除图书信息                            |" <<endl;
	cout << "| 1图书编号   2图书名称   0返回上级菜单                                |" <<endl;
	cout << "|                                                                      |" <<endl;
	cout << " ---------------------------------------------------------------------- " <<endl;
	int is_continue = -1;
	cin >> is_continue;
	if(is_continue == 1){
		cout << "请输入要删除的图书编号："; 
	}else if(is_continue == 2){
		cout << "请输入要删除的图书名称：";
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
	cout << "请输入要归还的图书ID：";
	char id[9];
	cin >> id;
	if(change_borrow_List(id)){
		change_borrow_file(); 
		delete_from_bookfile();
		cout << "还书成功！" <<endl;
	}else{
		cout << "还书失败！" <<endl;
	}
}
