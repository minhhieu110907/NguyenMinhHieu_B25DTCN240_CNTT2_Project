
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<windows.h>
#define MAX 1000

typedef struct {
	char empId[50],name[50],position[15];
	double baseSalary;
	int workDay;
}Employee;

typedef struct {
	char logId[20],empId[20],date[20],status[10];
}TimeSheet;

void menu_display();
void employeeList_display();
void addSampleList();
void add_employee();
int IdExisted(char empID[]);
void employeeList_display();
void employee_update();
void delete_employee();
void search_by_name();
void sort_by_baseSalary();
int getDaysInMonth(int i,int j);
int validateDate(int day, int month, int year);
int isFutureDate(int d, int m, int y);
int isCheckedIn(char id[], int d, int m, int y);
void timeKeeping();
void ViewPersonalTimeSheet();
void setColor(int color);
void clearScreen();
void loadingBar(int length, int color);


int n = 0;
Employee listEmployee[MAX];
TimeSheet listTimeSheet[MAX * 30];
int logCount = 0;
char inputBuffer[50];
int main(){
	int choose;
	addSampleList();
	do {
		system("cls");
		menu_display();
        printf("Moi ban nhap vao lua chon: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';
        trimString(inputBuffer);

        if (strlen(inputBuffer) == 0) {
            printf("\n=> Loi: Khong duoc de trong! Enter de nhap lai...");
            getchar(); continue;
        }
        char checkChar; 
        if (sscanf(inputBuffer, "%d%c", &choose, &checkChar) != 1) {
            printf("\n=> Loi: Lua chon phai la so nguyen! Enter de nhap lai...");
            getchar(); continue;
        }
		
		switch(choose){
			case 1: {
				add_employee();
				printf("\nNhan Enter de tiep tuc...");
				getchar();
				break;
			}
			case 2:{
				employee_update();
				printf("\nNhan Enter de tiep tuc...");
                getchar();
				break;
			}
			case 3: {
				delete_employee();
				printf("\nNhan Enter de tiep tuc...");
                getchar();
				break;
			}
			case 4: {
				employeeList_display();
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
				ViewPersonalTimeSheet();
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
	return 0;
}

void addSampleList() {  
    Employee e1 = {"ID01", "Tran Minh Duc", "Quan li", 2000, 5};
    Employee e2 = {"ID02", "Phung Duy Dat", "Nhan vien", 1000, 3};
    Employee e3 = {"ID03", "Nguyen Minh Hieu", "Chu tich", 20000, 8};
    Employee e4 = {"ID04", "Tang Hieu Thanh", "Lao cong", 10000 , 11};
    
    listEmployee[n++] = e1;
    listEmployee[n++] = e2;
    listEmployee[n++] = e3;
    listEmployee[n++] = e4;

    // 2. Tu dong tao du lieu Cham cong 
    for (int i = 0; i < n; i++) {
        // Giai doan 1: Tao ngay DI LAM (dua theo workDay cua tung nguoi)
        for (int j = 1; j <= listEmployee[i].workDay; j++) {
            strcpy(listTimeSheet[logCount].empId, listEmployee[i].empId);
            strcpy(listTimeSheet[logCount].status, "Di lam");
            
            // Tao ngay di lam: Ngay 1, 2, 3... thang 11
            sprintf(listTimeSheet[logCount].date, "%02d/%02d/%d", j, 11, 2025);
            logCount++;
        }
    }
}
	
void menu_display(){
	
	setColor(36);
    printf("\n+----------Danh sach quan ly nhan vien va cham cong--------+\n");
    printf("|1. Them moi nhan vien                                     |\n");
    printf("|2. Cap nhat ho so nhan vien                               |\n");
    printf("|3. Sa thai / nghi viec                                    |\n");
    printf("|4. Hien thi danh sach nhan vien                           |\n");
    printf("|5. Tra cuu thong tin nhan vien                            |\n");
    printf("|6. Sap xep danh sach nhan vien theo luong co ban          |\n");
    printf("|7. Cham ngay cong                                         |\n");
    printf("|8. Xem bang cong                                          |\n");
    printf("|9. Thoat                                                  |\n");
    printf("+----------------------------------------------------------+\n");
    setColor(0); // Reset color
}

int IdExisted(char empId[]){
	for(int i=0;i<n;i++){
		if(strcmp(listEmployee[i].empId,empId)==0){
			return i;
		}
	}
	return -1;
}

void employeeList_display() {
    // 1. Kiem tra danh sach rong
    if (n == 0) {
        setColor(31);
        printf("\nDanh sach trong! Khong co gi de hien thi.\n");
        setColor(0);
        return;
    }

    int perPage = 2; // So nhan vien tren 1 trang
    int totalPage = (n + perPage - 1) / perPage;
    int currentPage = 1; 
    int action;
    
    char navBuffer[50]; 

    do {
        system("cls"); 

        // Tinh toan vi tri
        int start = (currentPage - 1) * perPage;
        int end = start + perPage;
        if (end > n) end = n;

        printf("\n=== DANH SACH NHAN VIEN (Trang %d / %d) ===\n", currentPage, totalPage);
        printf("+----+------------+----------------------+---------------+------------+----------+\n");
        printf("| STT| Ma NV      | Ten NV               | Chuc vu       | Luong      | Ngay cong|\n");
        printf("+----+------------+----------------------+---------------+------------+----------+\n");
        
        for (int i = start; i < end; i++) {
            printf("| %2d | %-10s | %-20s | %-10s    | %10.2lf | %8d |\n",
                i + 1,
                listEmployee[i].empId,
                listEmployee[i].name,
                listEmployee[i].position,
                listEmployee[i].baseSalary,
                listEmployee[i].workDay);
        }
        printf("+----+------------+----------------------+---------------+------------+----------+\n");

        // Menu Dieu Huong
        printf("\n[Dieu huong]: ");
        if (currentPage < totalPage) printf(" [1] Trang sau  ");
        if (currentPage > 1)         printf(" [2] Trang truoc  ");
        printf(" [3] Den trang cu the  [0] Thoat ra Menu");
        
        printf("\nLua chon cua ban: ");
        fgets(navBuffer, sizeof(navBuffer), stdin);
        
        if (sscanf(navBuffer, "%d", &action) != 1) {
            action = -1; 
        }

        switch(action) {
            case 1: // Trang sau
                if (currentPage < totalPage) {
                    currentPage++;
                } else {
                    printf("\n=> Day la trang cuoi cung roi!\n"); Sleep(800);
                }
                break;

            case 2: // Trang truoc
                if (currentPage > 1) {
                    currentPage--;
                } else {
                    printf("\n=> Day la trang dau tien roi!\n"); Sleep(800);
                }
                break;

            case 3: // Nhay trang
                printf("Nhap so trang muon den (1-%d): ", totalPage);
                int targetPage;
                // Tai su dung navBuffer de nhap so trang luon
                fgets(navBuffer, sizeof(navBuffer), stdin);
                if (sscanf(navBuffer, "%d", &targetPage) == 1) {
                    if (targetPage >= 1 && targetPage <= totalPage) {
                        currentPage = targetPage;
                    } else {
                        setColor(31); printf("=> So trang khong hop le!\n"); setColor(0); Sleep(1000);
                    }
                }
                break;

            case 0: // Thoat
                return; 

            default:
                printf("\nLua chon khong hop le!\n"); Sleep(500);
        }

    } while (1);
}

void trimString(char str[]) {
    int start = 0, end = strlen(str) - 1;
    while (isspace(str[start])) start++;
    if (str[start] == '\0') {
        str[0] = '\0';
        return;
    }
    while (end > start && isspace(str[end])) end--;
    int i;
    for (i = 0; i <= end - start; i++) {
        str[i] = str[start + i];
    }
    str[i] = '\0';
}

void add_employee(){
	int choice;
	Employee e;
	char input [100];
	char salaryinput[100];
	if ( n >= MAX){
		printf("Danh sach da day.Khong the them\n");
		return;
	}
	do {
        printf("Nhap ma nhan vien: ");
        fgets(e.empId, 50, stdin);
        e.empId[strcspn(e.empId, "\n")] = '\0';
        
        trimString(e.empId);
        if (strcmp(e.empId, "") == 0) {
            setColor(31);
            printf("Ma nhan vien khong duoc de trong\n");
            setColor(0);
            continue; 
        }
        
        int isSpecial = 0;
        for (int i = 0; i < strlen(e.empId); i++) {
            if (!isalnum(e.empId[i])) { 
                isSpecial = 1;
                break;
            }
        }
        if (isSpecial) {
            setColor(31);
            printf("Ma nhan vien khong duoc chua ky tu dac biet hoac khoang trang o giua!\n");
            setColor(0);
            continue;
        }
        if (IdExisted(e.empId) != -1) {
            setColor(31);
            printf("Ma nhan vien da ton tai\n");
            setColor(0);
            continue;
        }
        
        break;
    } while (1);
	do {
		printf("Nhap ten nhan vien: ");
		fgets(e.name,50,stdin);
		e.name[strcspn(e.name,"\n")]='\0';
		
		if (strcmp (e.name,"") == 0 ){
			setColor(31);
			printf("Ten nhan vien khong duoc de trong\n");
			setColor(0);
		}
	} while ( strcmp (e.name,"") == 0 );
	
	do {
		printf("Nhap chuc vu nhan vien: ");
		fgets(e.position,15,stdin);
		e.position[strcspn(e.position,"\n")]='\0';
		
		if (strcmp (e.position,"") == 0 ){
			setColor(31);
			printf("Chuc vu nhan vien khong duoc de trong\n");
			setColor(0);
		}
	} while ( strcmp (e.position,"") == 0 );
	
	double baseSalary;


    do {
    printf("Nhap luong co ban: ");

    fgets(salaryinput, sizeof(salaryinput), stdin);
    salaryinput[strcspn(salaryinput, "\n")] = '\0'; // Xoa ky tu enter

    // Kiem tra trong
    if (strlen(salaryinput) == 0) {
    	setColor(31);
        printf("Khong duoc de trong! Vui long nhap lai.\n");
        setColor(0);
        continue;
    }

    // Kiem tra dinh dang
    if (sscanf(salaryinput, "%lf", &baseSalary) != 1) {
    	setColor(31);
        printf("Luong phai la so! Vui long nhap lai.\n");
        setColor(0);
        continue;
    }

    // Kiem tra so duong
    if (baseSalary <= 0) {
    	setColor(31);
        printf("Luong phai la so duong! Vui long nhap lai.\n");
        setColor(0);
        continue;
    }
    break; 

    } while (1);

    do {
    printf("Ngay cong (1. Bang 0  2. Nhap tu ban phim): ");
    fgets(salaryinput, sizeof(salaryinput), stdin);
    salaryinput[strcspn(salaryinput, "\n")] = '\0';

    if (strlen(salaryinput) == 0) {
    	setColor(31);
        printf("Khong duoc de trong! Vui long nhap lai.\n");
        setColor(0);
        continue;
    }

    if (sscanf(salaryinput, "%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Lua chon khong hop le! Vui long nhap 1 hoac 2.\n");
        continue;
    }
    break;
    } while (1);
    
    if (choice == 1) {
    e.workDay = 0;
    printf("Workday = 0\n");
    }  
    if (choice == 2) {
    char buf[50];
    do {
        printf("Moi ban nhap vao so ngay cong: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';

        if (strlen(buf) == 0) {
        	setColor(31);
            printf("Khong duoc de trong!\n");
            setColor(0);
            continue;
        }

        if (sscanf(buf, "%d", &e.workDay) != 1 || e.workDay <= 0 || e.workDay >31 ) {
        	setColor(31);
            printf("Ngay cong phai la so nguyen duong va nho hon 32!\n");
            setColor(0);
            continue;
        }

        break;
    } while (1);
}
	
	listEmployee[n] = e;
    n++;
    loadingBar(50, 32);
    printf("\nThem nhan vien thanh cong!\n");
}
	
void employee_update(){
    Employee e;
    int targetIndex = -1;
    char targetId[50];
    double baseSalary;
    char salaryinput [100];
    do {
        printf("Nhap ma nhan vien can update: ");
        fgets(targetId, 50, stdin);
        targetId[strcspn(targetId, "\n")] = '\0';
        
        trimString(targetId);
        
        // Kiem tra rong
        if (strcmp(targetId, "") == 0) {
            setColor(31);
            printf("Ma nhan vien khong duoc de trong\n");
            setColor(0);
            continue; 
        }
        
        // Kiem tra ky tu dac biet
        int isSpecial = 0;
        for (int i = 0; i < strlen(targetId); i++) {
            if (!isalnum(targetId[i])) { 
                isSpecial = 1;
                break;
            }
        }
        if (isSpecial) {
            setColor(31);
            printf("Ma nhan vien khong duoc chua ky tu dac biet!\n");
            setColor(0);
            continue;
        }
        
        // Kiem tra ton tai
        targetIndex = IdExisted(targetId);
        if (targetIndex == -1){
            loadingBar(50, 32);
            setColor(31);
            printf("\nKhong tim thay nhan vien co ma [%s]. Vui long nhap lai.\n", targetId);
            setColor(0);
            continue; 
        }
        break; 
    } while (1);
  
    e = listEmployee[targetIndex];
    printf("-----DANG CAP NHAT THONG TIN CHO ID: %s -----\n", e.empId);

    
    do {
        printf("Nhap chuc vu: ");
        fgets(e.position,15,stdin);
        e.position[strcspn(e.position,"\n")]='\0';
    } while (strcmp(e.position,"") == 0); 
    
    do {
    printf("Nhap luong co ban: ");

    fgets(salaryinput, sizeof(salaryinput), stdin);
    salaryinput[strcspn(salaryinput, "\n")] = '\0'; // Xoa ky tu enter

    // Kiem tra trong
    if (strlen(salaryinput) == 0) {
        printf("\nKhong duoc de trong! Vui long nhap lai.\n");
        continue;
    }

    // Kiem tra dinh dang
    if (sscanf(salaryinput, "%lf", &baseSalary) != 1) {
    	setColor(31);
        printf("\nLuong phai la so! Vui long nhap lai.\n");
        setColor(0);
        continue;
    }

    // Kiem tra so duong
    if (baseSalary <= 0) {
    	setColor(31);
        printf("\nLuong phai la so duong! Vui long nhap lai.\n");
        setColor(0);
        continue;
    }
    break; 

    } while (1); 
    
    char buf[50];
    do {
        printf("Moi ban nhap vao so ngay cong: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';

        if (strlen(buf) == 0) {
        	setColor(31);
            printf("Khong duoc de trong!\n");
            setColor(0);
            continue;
        }

        if (sscanf(buf, "%d", &e.workDay) != 1 || e.workDay <= 0 || e.workDay > 31) {
        	setColor(31);
            printf("Ngay cong phai la so nguyen duong va nho hon 32!\n");
            setColor(0);
            continue;
        }

        break;
    } while (1);
    
    listEmployee[targetIndex] = e;
    loadingBar(50, 32);
    setColor(32);
    printf("\nCap nhat ho so nhan vien thanh cong!\n");
}

void delete_employee(){
    char deleteId[50]; 
    char confirm;
    int index = -1;
    
    	do {
        printf("Nhap ma nhan vien: ");
        fgets(deleteId, 50, stdin);
        deleteId[strcspn(deleteId, "\n")] = '\0';
        
        trimString(deleteId);
        if (strcmp(deleteId, "") == 0) {
            setColor(31);
            printf("Ma nhan vien khong duoc de trong\n");
            setColor(0);
            continue; 
        }
        
        int isSpecial = 0;
        for (int i = 0; i < strlen(deleteId); i++) {
            if (!isalnum(deleteId[i])) { 
                isSpecial = 1;
                break;
            }
        }
        if (isSpecial) {
            setColor(31);
            printf("Ma nhan vien khong duoc chua ky tu dac biet hoac khoang trang o giua!\n");
            setColor(0);
            continue;
        }
        index = IdExisted(deleteId);
        if (index == -1) {
            setColor(31);
            printf("Khong tim thay nhan vien co ma [%s]. Vui long nhap lai.\n", deleteId);
            setColor(0);
            continue; 
        }
        break;
    } while (1);
    
    printf("\n========================================");
    printf("\n   XAC NHAN XOA NHAN VIEN");
    printf("\n========================================");
    printf("\n Ma NV     : %s", listEmployee[index].empId);
    printf("\n Ho va Ten : %s", listEmployee[index].name);
    printf("\n Chuc vu   : %s", listEmployee[index].position);
    printf("\n========================================");
    
    setColor(31); 
    printf("\nCANH BAO: Hanh dong nay khong the hoan tac!");
    setColor(0);  
    printf("\nBan co chac chan muon xoa nhan vien nay? (Y/N): ");
    
    scanf("%c", &confirm);
    while(getchar() != '\n'); 
    
    if (confirm == 'y' || confirm == 'Y') {
        for(int j = index; j < n - 1; j++){
            listEmployee[j] = listEmployee[j+1];
        }
        n--; 
        loadingBar(50, 33); 
        setColor(32);
        printf("\n[Thanh cong] Da xoa nhan vien ma: %s\n", deleteId);
    } else {
        printf("\nDa huy thao tac xoa!\n");
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
		setColor(31);
		printf("\nKhong tim thay nhan vien!");
		setColor(0);
	}
}

void sort_by_baseSalary(){
	Employee e;
	if(n == 0 ){
		clearScreen();
		printf("\nDanh sach trong!");
		return;
	}
	int choice;
	do{
		printf("Moi ban nhap vao lua chon(1.Tang dan 2.Giam dan): ");
		scanf("%d",&choice);
		getchar();
		if ( choice != 1 && choice != 2){
			setColor(31);
			printf("\nLua chon khong hop le.");
			setColor(0);
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
	clearScreen();
    printf("\nDa sap xep xong!\n");
    employeeList_display();	
}

int getDaysInMonth(int m, int y) {
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    if (m == 2) return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) ? 29 : 28;
    return 31;
}

int validateDate(int day, int month, int year){
    // 1. Kiem tra thang nam co ban
    if (month < 1 || month > 12) {
        setColor(31); printf("\nThang khong hop le!"); 
		return 0;
    }
    if (year < 1900 || year > 2100) {
        setColor(31); printf("\nNam khong hop le"); 
		return 0;
    }

    // 2. Goi ham getDaysInMonth de lay so ngay toi da cua thang do
    int maxDay = getDaysInMonth(month, year);

    // 3. So sanh
    if (day < 1 || day > maxDay) {
        setColor(31); 
		printf("\nNgay khong hop le (Thang %d chi co %d ngay)!", month, maxDay);
        setColor(0);
        return 0;
    }
    
    return 1; 
}

int isFutureDate(int d, int m, int y) {
	time_t t = time(NULL);
    struct tm current = *localtime(&t);

    int curDay = current.tm_mday;
    int curMonth = current.tm_mon + 1;
    int curYear = current.tm_year + 1900;

    if (y > curYear) {
	    return 1;
    }
    if (y == curYear && m > curMonth){
	    return 1;
    }
    if (y == curYear && m == curMonth && d > curDay) {
    	return 1;
	}

    return 0; 
}

int isCheckedIn(char id[], int d, int m, int y) {
    char dateToCheck[20];
    sprintf(dateToCheck, "%02d/%02d/%d", d, m, y); 

    for (int i = 0; i < logCount; i++) {
        if (strcmp(listTimeSheet[i].empId, id) == 0 && strcmp(listTimeSheet[i].date, dateToCheck) == 0) {
            return 1; 
        }
    }
    return 0;
}

void timeKeeping() { 
    char InputId[50];
    int index = -1;
  
    do {
        printf("Nhap ma nhan vien can cham cong: ");
        fgets(InputId, 50, stdin);
        InputId[strcspn(InputId, "\n")] = '\0';
        
        trimString(InputId);
        
        if (strcmp(InputId, "") == 0) {
            setColor(31);
            printf("Ma nhan vien khong duoc de trong! Vui long nhap lai.\n");
            setColor(0); 
            continue;
        }

        int isSpecial = 0;
        for (int i = 0; i < strlen(InputId); i++) {
            if (!isalnum(InputId[i])) { 
                isSpecial = 1;
                break;
            }
        }
        if (isSpecial) {
            setColor(31);
            printf("Ma nhan vien khong duoc chua ky tu dac biet!\n");
            setColor(0); 
            continue;
        }

        index = IdExisted(InputId);
        if (index == -1) {
            loadingBar(50, 31);
            setColor(31);
            printf("\nKhong tim thay nhan vien co ma [%s]. Vui long nhap lai.\n", InputId);
            setColor(0); 
        }
    } while (index == -1);

    printf("\n=== THONG TIN NHAN VIEN ===\n");
    printf("Ma nhan vien: %s\n", listEmployee[index].empId);
    printf("Ho ten: %s\n", listEmployee[index].name);
    printf("==========================\n");

   printf("\n=== XAC NHAN CHAM CONG (DI LAM) ===\n");
    printf("Nhan vien: %s - %s\n", listEmployee[index].empId, listEmployee[index].name);

    int d, m, y;
    char dateInput[100]; // 1. Khai bao them bien luu chuoi nhap ngay

    do {
        printf("Moi nhap ngay cham cong (dd/mm/yyyy): ");
        fgets(dateInput, sizeof(dateInput), stdin);
        dateInput[strcspn(dateInput, "\n")] = '\0';
        
        trimString(dateInput); 

        if (sscanf(dateInput, "%d/%d/%d", &d, &m, &y) != 3) {
            loadingBar(50, 31);
            printf("\n Sai dinh dang. Moi ban nhap lai.\n");
            setColor(0);
            continue;
        }
        
    } while (validateDate(d, m, y) == 0);

    if (isFutureDate(d, m, y)) {
        loadingBar(50, 32); 
		printf("\n[LOI] Khong the cham cong tuong lai!\n"); return;
    }

    if (isCheckedIn(InputId, d, m, y) == 1) {
        setColor(31); printf("\n[LOI] Ngay nay da cham cong roi!\n"); setColor(0); return;
    }

    strcpy(listTimeSheet[logCount].empId, InputId);
    sprintf(listTimeSheet[logCount].date, "%02d/%02d/%d", d, m, y);
    strcpy(listTimeSheet[logCount].status, "Di lam");
    
    listEmployee[index].workDay++; 

    logCount++; 
    loadingBar(50, 32);
    printf("\n[Thanh cong] Da cham cong DI LAM cho ngay %02d/%02d/%d!\n", d, m, y);
}

void ViewPersonalTimeSheet() {
    char InputId[50];
    int index = -1;
    int viewMonth, viewYear;
    do {
        printf("\nNhap ID nhan vien: ");
        fgets(InputId, 50, stdin);
        InputId[strcspn(InputId, "\n")] = '\0';
        trimString(InputId);

        if (strcmp(InputId, "") == 0) { 
            setColor(31); 
            printf("Ma nhan vien khong duoc de trong!\n"); 
            setColor(0); 
            continue; 
        }
        int isSpecial = 0;
        for (int i = 0; i < strlen(InputId); i++) {
            if (!isalnum(InputId[i])) { 
                isSpecial = 1; 
                break; 
            }
        }
        if (isSpecial) {
            setColor(31); 
            printf("Ma nhan vien khong duoc chua ky tu dac biet!\n"); 
            setColor(0); 
            continue; 
        }

        index = IdExisted(InputId);
        if (index == -1) {
            setColor(31); 
            printf("Khong tim thay nhan vien [%s]!\n", InputId); 
            setColor(0); 
        }
    } while (index == -1);
    printf("Nhap THANG va NAM muon xem (mm yyyy): ");
    scanf("%d %d", &viewMonth, &viewYear);
    getchar(); // Xoa bo nho dem

    loadingBar(30, 34); 
    
    printf("\n============================================\n");
    printf(" BANG CHAM CONG THANG %02d/%d\n", viewMonth, viewYear);
    printf(" Nhan vien: %s (%s)\n", listEmployee[index].name, listEmployee[index].empId);
    printf("============================================\n");
    printf("| %-12s | %-20s |\n", "NGAY", "TRANG THAI");
    printf("|--------------|----------------------|\n");

    int daysInMonth = getDaysInMonth(viewMonth, viewYear); 
    int countWork = 0;
    int countOff = 0;

    // Vong lap quet tung ngay
    for (int d = 1; d <= daysInMonth; d++) {
        if (isFutureDate(d, viewMonth, viewYear)) {
            break; // Dung vong lap ngay lap tuc
        }

        // Kiem tra du lieu cham cong
        if (isCheckedIn(InputId, d, viewMonth, viewYear)) {
            // Co cham cong -> DI LAM
            printf("| %02d/%02d/%d   | ", d, viewMonth, viewYear);
            setColor(32); printf("%-20s", "Di lam"); setColor(0);
            printf(" |\n");
            countWork++;
        } else {
            // Khong cham cong -> NGHI LAM
            printf("| %02d/%02d/%d   | ", d, viewMonth, viewYear);
            setColor(31); printf("%-20s", "Nghi lam"); setColor(0);
            printf(" |\n");
            countOff++;
        }
    }

    printf("--------------------------------------------\n");
    printf(" TONG KET THANG %02d:\n", viewMonth);
    printf(" - So ngay di lam : %d\n", countWork);
    printf(" - So ngay nghi   : %d\n", countOff);
    printf("============================================\n");
}

void loadingBar(int length, int color) {
    system("cls");
    printf("Dang tai du lieu...\n\n");

    for (int i = 0; i <= length; i++) {
        int percent = (i * 100) / length;

        printf("\r[");  // quay ve dau dong

        setColor(color);
        for (int j = 0; j < i; j++) printf("=");
        
        // Phan chua tai
        setColor(32);
        for (int j = i; j < length; j++) printf(" ");

        // In % bên ngoài
        setColor(35);
        printf("] %d%%", percent);

        fflush(stdout);
        Sleep(30);  // toc do tai
    }
}

void clearScreen() {
	setColor(36);
    printf("Loading");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        Sleep(400);
    }
    printf("\033[2J\033[1;1H");
}

void setColor(int color) {
    printf("\033[1;%dm", color);
}
	






