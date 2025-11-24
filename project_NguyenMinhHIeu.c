#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1000
int n = 0;

typedef struct {
	char empId[50],name[50],position[15];
	double baseSalary;
	int workDay;
}Employee;
Employee listEmployee[MAX];

typedef struct {
	char logId[20],empId[20],date[20],status[10];
}TimeSheet;
void menu_display();
void add_employee();
int IdExisted(char empID[]);
void employeeList_display();
void employee_update();
void delete_employee();
void search_by_name();
void sort_by_baseSalary();
int validateDate(int day, int month, int year);
void timeKeeping();

int main(){
	int choose;
	do {
		system("cls");
		menu_display();
		printf("Moi ban nhap vao lua chon: ");
		scanf("%d",&choose);
		getchar();
		
		switch(choose){
			case 1: {
				menu_display();
				break;
			}
			case 2:{
				add_employee();
				printf("\nNhan Enter de tiep tuc...");
                getchar();
				break;
			}
			case 3: {
				employee_update();
				printf("\nNhan Enter de tiep tuc...");
                getchar();
				break;
			}
			case 4: {
				delete_employee();
				printf("\nNhan Enter de tiep tuc...");
                getchar();
				break;
			}
			case 5: {
				search_by_name();
				printf("\nNhan Enter de tiep tuc...");
                getchar();
				break;
			}
			case 6: {
				sort_by_baseSalary();
				printf("\nNhan Enter de tiep tuc...");
                getchar();
				break;
			}
			case 7: {
				timeKeeping();
				printf("\nNhan Enter de tiep tuc...");
                getchar();
				break;
			}
			case 8: {
				printf("\nNhan Enter de tiep tuc...");
                getchar();
				break;
			}
			case 9: {
				printf("Chuong trinh ket thuc! Cam on ban");
				break;
			}
			default :
				printf("Lua chon khong hop le");
				getchar();
		}
	} while ( choose != 9);
}
	
void menu_display(){
	printf("\n =============================================\n");
	printf("||     QUAN LY NHAN VIEN VA CHAM CONG        ||");
	printf("\n||========================================== ||\n");
	printf("|| 1.Hien thi danh sach nhan vien            ||\n");
	printf("|| 2.Them nhan vien moi                      ||\n");                 
	printf("|| 3.Cap nhat ho so nhan vien                ||\n");
	printf("|| 4.Xoa ho so nhan vien                     ||\n");
	printf("|| 5.Tim kiem nhan vien                      ||\n");
	printf("|| 6.Sap xep nhan vien                       ||\n");
	printf("|| 7.Cham cong ngay nhan vien                ||\n");
	printf("|| 8.Xem bang cong nhan vien                 ||\n");
	printf("|| 9.Thoat                                   ||\n");
	printf(" =============================================\n");
}
int IdExisted(char empId[]){
	for(int i=0;i<n;i++){
		if(strcmp(listEmployee[i].empId,empId)==0){
			return 1;
		}
	}
	return 0;
}

void employeeList_display (){
	if ( n == 0){
		printf("Khong co nhan vien nao\n");
		return;
	}
	printf("\n-----Danh sach nhan vien-----\n");
	for ( int i =0;i<=100;i++){
		printf("-");
	}
	printf("%-10s %-20s %-15s %-15s\n", "Ma NV", "Ho Ten", "Chuc Vu", "Luong Co Ban");
    for (int i = 0; i < n; i++) {
        printf("%-10s %-20s %-15s %-15.2lf\n", 
               listEmployee[i].empId, 
               listEmployee[i].name, 
               listEmployee[i].position, 
               listEmployee[i].baseSalary);
    }
}

void add_employee(){
	Employee e;
	e.workDay = 0 ;
	if ( n >= MAX){
		printf("Danh sach da day.Khong the them\n");
		return;
	}
	do {
		printf("Nhap ma nhan vien: ");
		fgets(e.empId,50,stdin);
		e.empId[strcspn(e.empId,"\n")]='\0';
		
		if (strcmp (e.empId," ") == 0){
			printf("Ma nhan vien khong duoc de trong\n");
		}
		if ( IdExisted(e.empId) == 1){
			printf("Ma nhan vien da ton tai trong danh sach\n");
		}
	} while ( strcmp (e.empId," ") == 0 || IdExisted(e.empId) == 1 );
	
	do {
		printf("Nhap ten nhan vien: ");
		fgets(e.name,50,stdin);
		e.name[strcspn(e.name,"\n")]='\0';
		
		if (strcmp (e.name," ") == 0 ){
			printf("Ten nhan vien khong duoc de trong\n");
		}
	} while ( strcmp (e.name," ") == 0 );
	
	do {
		printf("Nhap chuc vu nhan vien: ");
		fgets(e.position,50,stdin);
		e.position[strcspn(e.position,"\n")]='\0';
		
		if (strcmp (e.name," ") == 0 ){
			printf("Chuc vu nhan vien khong duoc de trong\n");
		}
	} while ( strcmp (e.position," ") == 0 );
	
	do {
		printf("Nhap luong co ban: ");
		scanf("%lf",&e.baseSalary);
		getchar();
		
		if (e.baseSalary <= 0 ){
			printf(" Muc luong nhap khong phu hop\n");
		}
	} while ( e.baseSalary <= 0);
	
	listEmployee[n] = e;
    n++;
    printf("Them nhan vien thanh cong!\n");
}
	
void employee_update(){
	Employee e;
	printf("Nhap ma nhan vien can cap nhat: ");
	fgets(e.empId,50,stdin);
	e.empId[strcspn(e.empId,"\n")]='\0';
	if(IdExisted(e.empId)==0){
		printf("\nMa nhan vien khong ton tai!");
	}else{
		do {
		printf("Nhap ma nhan vien: ");
		fgets(e.empId,50,stdin);
		e.empId[strcspn(e.empId,"\n")]='\0';
		
		if (strcmp (e.empId," ") == 0){
			printf("Ma nhan vien khong duoc de trong\n");
		}
		if ( IdExisted(e.empId) == 1){
			printf("Ma nhan vien da ton tai trong danh sach\n");
		}
	} while ( strcmp (e.empId," ") == 0 || IdExisted(e.empId) == 1 );
	
	do {
		printf("Nhap ten nhan vien: ");
		fgets(e.name,50,stdin);
		e.name[strcspn(e.name,"\n")]='\0';
		
		if (strcmp (e.name," ") == 0 ){
			printf("Ten nhan vien khong duoc de trong\n");
		}
	} while ( strcmp (e.name," ") == 0 );
	
	do {
		printf("Nhap chuc vu nhan vien: ");
		fgets(e.position,50,stdin);
		e.position[strcspn(e.position,"\n")]='\0';
		
		if (strcmp (e.position," ") == 0 ){
			printf("Chuc vu nhan vien khong duoc de trong\n");
		}
	} while ( strcmp (e.position," ") == 0 );
	
	do {
		printf("Nhap luong co ban: ");
		scanf("%lf",&e.baseSalary);
		getchar();
		
		if ( e.baseSalary <= 0 ){
			printf(" Muc luong nhap khong duoc am\n");
		}
	} while ( e.baseSalary <= 0);	
    }
    printf("Cap nhat thanh cong!\n");
}

void delete_employee(){
	Employee e;
	printf("Nhap ma nhan vien can xoa: ");
	fgets(e.empId,50,stdin);
	e.empId[strcspn(e.empId,"\n")]='\0';
	if(IdExisted(e.empId)==0){
		printf("\nMa nhan vien khong ton tai!");
		}else{
		for(int i=0;i<n;i++){
			if(strcmp(listEmployee[i].empId,e.empId)==0){
				for(int j=i;j<n-1;j++){
					listEmployee[j] = listEmployee[j+1];
				}
				n--;
				printf("\nDa xoa nhan vien co ma: %s",e.empId);
			}
		}
	}
}

void search_by_name(){
	char keyword[50];
	int found = 0;
	printf("Moi nhap ten nhan vien ban muon tim: ");
	fgets(keyword,50,stdin);
	keyword[strcspn(keyword,"\n")]='\0';
	for(int i =0 ; i< n ;i++){
	if ( strstr(listEmployee[i].name,keyword) != NULL ){
	    printf("ID: %s | Ten: %s | Chuc vu: %s | Luong: %.2lf\n",
                   listEmployee[i].empId, 
                   listEmployee[i].name, 
                   listEmployee[i].position, 
                   listEmployee[i].baseSalary);
            found = 1;
	}
    }
	if (found == 0 ){
		printf("Khong tim thay nhan vien!");
	}
}
void sort_by_salaryBase(){
	Employee e;
	if(n == 0 ){
		printf("Danh sach trong!");
		return;
	}
	int choice;
	do{
		printf("Moi ban nhap vao lua chon(1.Tang dan 2.Giam dan): ");
		scanf("%d",&choice);
		getchar();
		if ( choice != 1 && choice != 2){
			printf("Lua chon khong hop le.");
		}
	} while ( choice != 1 && choice != 2);
	if ( choice == 1){
		for ( int i = 0 ;i<n;i++){
			for ( int j = 0;j<n-i-1;j++){
				if(listEmployee[j].baseSalary > listEmployee[j+1].baseSalary){
				   e = listEmployee[j];
				   listEmployee[j] = listEmployee[j+1];
				   listEmployee[j+1] = e;
				}
			}
		}
	}
	
	if ( choice == 2){
		for ( int i = 0 ;i<n;i++){
			for ( int j = 0;j<n-i-1;j++){
				if(listEmployee[j].baseSalary < listEmployee[j+1].baseSalary){
				   e = listEmployee[j];
				   listEmployee[j] = listEmployee[j+1];
				   listEmployee[j+1] = e;
				}
			}
		}
	}
    printf("\nDa sap xep xong!\n");
    employeeList_display();	
}

int validateDate(int day, int month, int year){
	int success = 1;
	if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12){
		if(day<1 || day>31){
			success = 0;
			printf("\nNgay cham cong khong hop le!");
		}
	}
	if(month==4 || month==6 || month==9 || month==11){
		if(day<1 || day>30){
			success = 0;
			printf("\nNgay cham cong khong hop le!");
		}
	}
	
	if(month==2){
		if((year%4==0 && year%100 !=0) || year%400==0){
			if(day<1 || day>29){
				success = 0;
				printf("\nNgay cham cong khong hop le!");
			}
		}else{
			if(day<1 || day>28){
				success = 0;
				printf("\nNgay sinh khong hop le!");
			}
		}
		
	}
	if(month<1 || month>12){
		success = 0;
		printf("\nThang cham cong khong hop le!");
	}
	if(year<1900 || year>2025){
		success = 0;
		printf("\nNam cham cong khong hop le");
	}
	return success;
} 

void timeKeeping(){
	Employee e;
	char InputId[50];
	int index = -1;
	
	do {
	printf("Nhap ma nhan vien can cham cong: ");
	fgets(InputId,50,stdin);
	InputId[strcspn(InputId,"\n")]='\0';
	for ( int i =0 ; i<n ;i++){
		if(strcmp(listEmployee[i].empid,InputId)==0){
			index = i ;
		}
	}
	if (index == -1 ){
		printf("Khong co nhan vien trong danh sach.Vui long nhap lai\n");
	}
	} while ( index == -1);
	printf("\n=== THONG TIN NHAN VIEN ===\n");
    printf("Ma nhan vien: %s\n", listEmployee[index].empId);
    printf("Ho ten: %s\n", listEmployee[index].name);
    printf("Chuc vu: %s\n", listEmployee[index].position);
    printf("==========================\n");

	int d,m,y;
	do {
	printf("Moi nhap ngay cham cong ( dinh dang dd/mm/yyyy): ");
	scanf("%d/%d/%d",&d,&m,&y);
	getchar();
	if(scanf("%d/%d/%d",&d,&m,&y) != 3){
		printf("")
	} while (validateDate(d, m, y) == 0); 

    listEmployee[index].workDay++; 
    
    printf("\n Cham cong THANH CONG ngay %02d/%02d/%d!\n", d, m, y);
    printf(" Tong so ngay cong moi: %d\n", listEmployee[index].workDay);
    getchar();
	}
}



	




