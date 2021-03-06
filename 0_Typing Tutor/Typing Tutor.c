#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <string.h>

void mainmenu();
void loadFiles(void);
int userSelectMenu(void);
void createUser(void);
void ViewUserRecords(void);
int listLesson(int);
void beginSession(int, int);
void AtoZLesson(int);
void shortLesson(int);
void longLesson(int, int);
void gotoxy();
void statistics();

#define UP 72
#define DOWN 80
#define ENTER 13

#pragma pack(push, 1)
struct user {
    char Name[50];
    char Lesson_title[50];
    float Duration;
    int Gross_speed[50];
    float Accuracy;
    int Score;
    char time[50];
};
#pragma pack(pop)
struct user userList[100];
struct longLesson { //긴글연습의 데이터를 저장 
	char Lesson_title[50];
	int length_of_letters;
	char letters[1000]; //1000자 까지 
};
struct longLesson longLessonList[100];
struct shortLesson { //긴글연습의 데이터를 저장 
	int length_of_letters;
	char letters[1000]; //1000자 까지 
};
struct shortLesson shortLessonList[100];


struct record {
    char Name[50];
    char Lesson_title[50];
    float Duration;
    int Gross_speed;
    float Accuracy;
    int Score;
    char date[50];
    char time[50];
};
struct record recordList[100];


int key;
int menuNum=1; //menuNum -> 1 ~ 5


int main() {
	loadFiles();
	mainmenu();

    return 0;
}

void mainmenu() {
	int i;
	//printf("\n");
	
	
	while(1){ 
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=초록, 5=자주, 연한노랑14
	    printf("\t\t\t\t▶  T  Y  P  I  N  G   T  E  S  T  E  R  ◀\n\n");
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	    printf("≫ Press the arrow keys: ↑ or ↓ to navigate the options.\n");
	    printf("≫ Press <ENTER> key to accept an option.\n");
	    printf("≫ [or] Press the number keys to slelect your choice\n");
	    printf("\n"); 
	    printf("\n");
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	    printf("\n\t\t\t\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	    printf("\n\t\t\t\t┃\t***MAIN MENU***\t\t\t┃");
	    printf("\n\t\t\t\t┃\t\t\t\t\t┃");
	   
	   for(i=1; i<6; i++){
	   	printf("\n\t\t\t\t┃");
	   		switch (i){
	   			case 1: 
	   				if(menuNum==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					printf("   <1> Select User\t\t\t");
	   				break;
	   			case 2: 
	   				if(menuNum==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					printf("   <2> Statistics\t\t\t");
	   				break;
	   			case 3: 
	   				if(menuNum==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					printf("   <3> View User Records\t\t");
	   				break;
	   			case 4: 
	   				if(menuNum==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					printf("   <4> About\t\t\t\t");
	   				break;
	   			case 5: 
	   				if(menuNum==5) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					printf("   <5> Quit\t\t\t\t");
	   			break;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	   	printf("┃");
	   	printf("\n\t\t\t\t┃\t\t\t\t\t┃");
	   }
	   
	    printf("\n\t\t\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
		
		key = getch();
		if(key==224){
			key = getch(); //224값 버림 
		}
		if(key == UP){ //위 방향키 
			if(menuNum>1){ menuNum--; } 
		} else if(key == DOWN){ //아래 방향키
			if(menuNum<5){ menuNum++; } 
		} else if(key == ENTER) {
			switch (menuNum){
				case 1: //select user
					system("cls");
					userSelectMenu();
					break;
				case 2: //statistics
					system("cls"); //화면 지우기 
					statistics();
					break;
				case 3: //view user records
					system("cls");
					ViewUserRecords();
					break;
				case 4: //about
					system("cls"); //화면 지우기 
	    			printf("\n\t\t\t\t▶  a  b  o  u  t  ◀\n\n\n");
					printf("\t\t\t타자연습을 할 수 있는 프로그램\n\n\n");
					printf("\t\t\tatoz - a부터 z까지 타자를 연습\n\n");
					printf("\t\t\t짦은글 연습 - 한 줄 단위의 타자를 연습\n\n"); 
					printf("\t\t\t긴글 연습 - 여러 줄 단위의 타자를 연습\n\n"); 
					while (!kbhit()); //키 입력 대기 
					fflush(stdin);
					menuNum = 1;
					break;
				case 5: //quit
					system("cls"); //화면 지우기 
					printf("타자연습을 종료합니다");
					exit(0);
					break;
			}
		}
		system("cls"); //화면 지우기 
		printf("키 : %d , 메뉴 : %d \n", key, menuNum);
	}//end of while
}

void loadFiles(void){
	//미리 전체 파일 불러옴 
	int i, j, length = 0; 
	int c; //read 용 
	FILE *fpr = NULL;
	fpr = fopen("longtestList.txt", "r"); //read 모드로 file open
	if( fpr == NULL ) {
		printf("longtestList 파일 읽기 실패\n");
	}
	
	do { 
		fscanf(fpr, "%s", 
		&longLessonList[i].Lesson_title //저장된 Lesson_title을 읽어들임 
		);
		i++; //size
	}while((c = fgetc(fpr)) != EOF); //End Of File 까지 
	
	printf("파일 읽기 실행\n");

	for(j = 0; j < i; j++) {
		length = 0;
		//printf("긴글불러오기\n");
		fpr = fopen(strcat(longLessonList[j].Lesson_title, ".txt"), "rt"); //Lesson_title로 불러오기 
		if( fpr == NULL ) {
		printf("파일 읽기 실패\n");
		}
		
		while((c = fgetc(fpr)) != EOF) {
		 	longLessonList[j].letters[length] = c;
		 	length++; //글자 수 
			/*fscanf(fpr, "%c", 
			&longLessonList[j].letters[length]
			);
			length++; //글자 수 */
		} //End Of File 까지 
		longLessonList[j].length_of_letters = length;
	}	
	
	
	fclose(fpr);
	//printf("파일 읽기 완료\n\n");
	
	strcpy(shortLessonList[0].letters, "Pursuit of truth");
	strcpy(shortLessonList[1].letters, "the university's fundamental mission.");
	strcpy(shortLessonList[2].letters, "Preservation of traditional culture");
	strcpy(shortLessonList[3].letters, "Provision of leading services");
	strcpy(shortLessonList[4].letters, "for the development of the local community.");
	
	shortLessonList[0].length_of_letters = strlen(shortLessonList[0].letters);
	shortLessonList[1].length_of_letters = strlen(shortLessonList[1].letters);
	shortLessonList[2].length_of_letters = strlen(shortLessonList[2].letters);
	shortLessonList[3].length_of_letters = strlen(shortLessonList[3].letters);
	shortLessonList[4].length_of_letters = strlen(shortLessonList[4].letters);
} //+save파일 함수? 

void statistics() {
	FILE *fpr = NULL;
	int i=0, j=0, c;
	//char serch_word[50];
	fpr = fopen("record.txt", "r"); //read 모드로 file open
	if( fpr == NULL ) {
		printf("파일 읽기 실패\n");
	}
	
	int recordSize=0;
	do { 
		fscanf(fpr, "%s %s %f %d %f %d %s %s", 
		&recordList[recordSize].Name, 
		&recordList[recordSize].Lesson_title,
		&recordList[recordSize].Duration,
		&recordList[recordSize].Gross_speed,
		&recordList[recordSize].Accuracy,
		&recordList[recordSize].Score,
		&recordList[recordSize].date,
		&recordList[recordSize].time
		);
		recordSize++; //size
	}while((c = fgetc(fpr)) != EOF); //End Of File 까지 
	printf("%d 파일 읽기 완료", recordSize);
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("\n\t\t\t\t▶  player Statistics  ◀\n\n");
    printf("     Name       Lesson    WPM   Accuracy Score     Date       Time\n");
    printf("-------------------------------------------------------------------------\n");
    //printf("enter user name : ");
    for(j=0;j<recordSize-1;j++) {
		printf("%10s %12s %5d %5.1f％ %6d  %11s  [%8s] \n", 
		recordList[j].Name, 
		recordList[j].Lesson_title,
		recordList[j].Gross_speed,
		recordList[j].Accuracy,
		recordList[j].Score,
		recordList[j].date,
		recordList[j].time
		);
    }
	
	/*
    scanf_s("%s", &serch_word); //검색할 유저 
    
	for(j = 0; j < i; j++){ //i는 총 등록된 유저의 수 
		if(strcmp(serch_word, userList[j].Name) == 0) {
			break;
		}
	}
	if(j==i) {
		printf("일치 데이터 없음 \n");
	} else {
		system( "cls" ); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("\n\t\t\t\t▶  player Statistics  ◀\n\n");
		
		printf("Name : \n", userList[j].Name);
		printf("Lesson title : \n", userList[j].Lesson_title);
		printf("Gross Speed  : %.f WPM\n", userList[j].Gross_speed);
		printf("Accuracy : %.1f \n", userList[j].Accuracy);
		printf("Score : \n", userList[j].Score);
		printf("날짜 : %d, %d, %d\n");
		printf("Time [hh:mm:ss] = [%d:%d:%d]\n");
	}*/
	menuNum=1; 
	key=0;
	while (!kbhit()); //키 입력 대기 
	fflush(stdin);
}


int userSelectMenu(void) {
    int menuNum1 = 1;
    int key;
   
    struct user u1;
	printf("\n");
    FILE* fp = fopen("profile.bin", "a+b");
    fseek(fp, 0, SEEK_SET);
	   while(1){
        int i = 1;
		printf("\t\t\t\t\t▶  Select User  ◀\n\n");
        printf("\n\t\t\t\t\n\n\n");
        while (1) {
            if (fread(&u1, sizeof(u1), 1, fp) == 0)
                break;
            printf("\n\t\t\t\t\t");
            if (menuNum1 == i) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
           
			strcpy(userList[i].Name, u1.Name);
            printf("%s\n", u1.Name);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            i++; 
        }
        if (menuNum1 == i)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
        printf("\n\t\t\t\t\tadd a new profile\n");
        //i++;
        //if (menuNum1 == i+1)
        //printf("\n\t\t\t\t\t뒤로가기\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("\n\t\t\t\t==============================================");

        key = _getch();
        if (key == 224) {
            key = _getch(); //224媛� 踰꾨┝ 
            fseek(fp, 0, SEEK_SET);
        }
        system("cls"); //�솕硫� 吏��슦湲� 
        if (key == 27) {
        	break;
		}
        if (key == UP) { //�쐞 諛⑺뼢�궎 
            if (menuNum1 > 1) { menuNum1--; }
        }
        else if (key == DOWN) { //�븘�옒 諛⑺뼢�궎
            if (menuNum1 < i) { menuNum1++; }
        } //menuNum -> 1 ~ i
        else if (key == 13)
        {
            fseek(fp, 0, SEEK_SET);
            if (menuNum1 == i){
            	createUser();
			} else {
				listLesson(menuNum1);
			}
			// else if(menuNum1 == i+1) {
			//	break;
			//}
        }
    printf("키 : %d , 메뉴 : %d \n", key, menuNum1);
    }//end of while
    
    fclose(fp);
}

void createUser(void) {
    time_t t;
    struct tm* lt;
    struct user u1;
    lt = localtime(&t);
    FILE* fp = fopen("profile.bin", "ab");
    memset(&u1, 0, sizeof(u1));
    
    printf("\n\t\t\t\t▶  add a new profile  ◀\n\n");
    printf("\n\t\t\t\t");
    printf("\n\t\t\t\t");
    printf("name:");
    scanf("%s", u1.Name);
    //strcpy(u1.time, asctime(lt));
    //printf("asctime() : %s", asctime(lt));
    fwrite(&u1, sizeof(u1), 1, fp);
    fclose(fp);
    printf("\n\t\t\t\t");
    printf("sucsses");
    printf("\n\t\t\t\t==============================================");

    system("cls");

}

void ViewUserRecords() {
	int recordSize=0;
	FILE *fpr = NULL;
	int i=0, j=0, c;
	//char serch_word[50];
	fpr = fopen("record.txt", "r"); //read 모드로 file open
	if( fpr == NULL ) {
		printf("파일 읽기 실패\n");
	}
	
	do { 
		fscanf(fpr, "%s %s %f %d %f %d %s %s", 
		&recordList[recordSize].Name, 
		&recordList[recordSize].Lesson_title,
		&recordList[recordSize].Duration,
		&recordList[recordSize].Gross_speed,
		&recordList[recordSize].Accuracy,
		&recordList[recordSize].Score,
		&recordList[recordSize].date,
		&recordList[recordSize].time
		);
		recordSize++; //size
	}while((c = fgetc(fpr)) != EOF); //End Of File 까지 
	//printf("%d 파일 읽기 완료", recordSize);
	
    //struct user u1;
    //memset(&u1, 0, sizeof(u1));
    //FILE* fp = fopen("profile.bin", "a+b");
    //fseek(fp, 0, SEEK_SET);
    

    printf("\n\t\t\t\t\t");
    printf("\n\t\t\t\t\tEnter the name you want to find.");
    printf("\n\t\t\t\t\tName: ");
    char Name[50];
    scanf("%s", Name);
    
    system("cls");
    printf("\n\t\t\t\t\t▶  R E S U L T  ◀\n\n");
    //printf("\n\t\t\t\t             ***R E S U L T***                \n");
    //while (1)
    //{
    	printf("\t\t\t\t----------------------------------------------\n");
        //fread(&u1, sizeof(u1), 1, fp);
        c = 0;
        for (i = 0; i < recordSize; i++){
	        if ( strcmp(Name, recordList[i].Name) == 0 ){
	        	
	            printf("\n\t\t\t\t\tName: %s", recordList[i].Name);
		        printf("\n\t\t\t\t\tLesson_title: %s", recordList[i].Lesson_title);
		        printf("\n\t\t\t\t\tDuration: %.1f", recordList[i].Duration);
		        printf("\n\t\t\t\t\tGross_speed: %d", recordList[i].Gross_speed);
		        printf("\n\t\t\t\t\tAccuracy: %.1f", recordList[i].Accuracy);
		        printf("\n\t\t\t\t\tScore: %d", recordList[i].Score);
		        printf("\n\t\t\t\t\tDate: %s", recordList[i].time);
		        printf("\n\t\t\t\t\tTime: %s\n", recordList[i].time);
		        c = -1;
				
			}
        }
        
     if (c == 0) {
         //   printf("\n\t\t\t\t\t");
            printf("\n\t\t\t\tnot found");
         //   break;
    }
    //}
    
    /*
    printf("\n\t\t\t\t             ***R E S U L T***                ");

        printf("\n\t\t\t\t\tName: ");
        printf(u1.Name);
        printf("\n\t\t\t\t\tLesson_title: ");
        printf(u1.Lesson_title);
        printf("\n\t\t\t\t\tDuration: ");
        printf("%f", u1.Duration);
        printf("\n\t\t\t\t\tGross_speed: ");
        printf("%d", u1.Gross_speed);
        printf("\n\t\t\t\t\tAccuracy: ");
        printf("%f", u1.Accuracy);
        printf("\n\t\t\t\t\tScore: ");
        printf("%d", u1.Score);
        printf("\n\t\t\t\t\ttime: ");
        printf(u1.time);
       
    
    printf("\n\t\t\t\t==============================================");
    */
    if (_getch() == 13);
    system("cls");
}




int listLesson(int curruntUser) {
		int i;
		printf("\n");
	
		do { 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=초록, 5=자주, 연한노랑14
	    printf("\t\t\t\t▶  L  e  s  s  o  n   선  택  ◀\n\n");
	    printf("\n\n\n\n\n");
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	    printf("\n\t\t\t\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	    printf("\n\t\t\t\t┃\t***Lesson list***\t\t┃");
	    printf("\n\t\t\t\t┃\t\t\t\t\t┃");
	   
	   for(i=1; i<5; i++){
	   	printf("\n\t\t\t\t┃");
	   		switch (i){
	   			case 1: 
	   				if(menuNum==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					printf("   <1> A to Z\t\t\t\t");
	   				break;
	   			case 2: 
	   				if(menuNum==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					printf("   <2> 짧은글 연습\t\t\t");
	   				break;
	   			case 3: 
	   				if(menuNum==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					printf("   <3> 긴글 연습\t\t\t");
					break;
				case 4: 
	   				if(menuNum==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					printf("   <4> 뒤로가기\t\t\t");
	   				break;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	   	printf("┃");
	   	printf("\n\t\t\t\t┃\t\t\t\t\t┃");
	   }
	    printf("\n\t\t\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	    
	    key = getch();
		if(key==224){
			key = getch(); //224값 버림 
			//system("cls"); //화면 지우기 
		}
		if(key == UP){ //위 방향키 
			if(menuNum>1){ menuNum--; } 
		} else if(key == DOWN){ //아래 방향키
			if(menuNum<4){ menuNum++; } 
		} else if(key == ENTER && menuNum != 4) {
			system("cls");
			beginSession(menuNum, curruntUser); //menuNum 넘겨줌 
		}
		system("cls");
		printf("키 : %d , 메뉴 : %d , user : %s\n", key, menuNum, userList[curruntUser].Name);
	} while(!(key == ENTER && menuNum == 4)); //end of while  뒤로가기 
	system("cls");
	menuNum = 1;
}

void beginSession(int menu, int curruntUser){
		int i;
		menuNum = 1;
		key = 0; 
		
		switch (menu){
   			case 1: // A to Z
   				AtoZLesson(curruntUser);
   				break; 
   			case 2: //짧은글 연습 
   				shortLesson(curruntUser);
   				break;
   			case 3: //긴 글 연습
   				printf("\n");
			
				do { 
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=초록, 5=자주, 연한노랑14
				    printf("\t\t\t\t▶  글   선  택   ◀\n\n");
				    printf("\n\n\n\n\n");
				    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				    printf("\n\t\t\t\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
				    printf("\n\t\t\t\t┃\t***글 list***\t\t\t┃");
				    printf("\n\t\t\t\t┃\t\t\t\t\t┃");
				   
				   for(i=1; i<5; i++){
				   	printf("\n\t\t\t\t┃");
				   		switch (i){
				   			case 1: 
				   				if(menuNum==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
								printf("   <%d> %s\t\t\t", i, longLessonList[i-1].Lesson_title);
				   			break;
				   			case 2: 
				   				if(menuNum==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
								printf("   <%d> %s\t\t\t", i, longLessonList[i-1].Lesson_title);
				   			break;
				   			case 3: 
				   				if(menuNum==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
								printf("   <%d> %s\t\t\t", i, longLessonList[i-1].Lesson_title);
				   			break;
				   			case 4: 
				   				if(menuNum==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
								printf("   <%d> 뒤로가기\t\t\t", i);
				   			break;
						}
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				   	printf("┃");
				   	printf("\n\t\t\t\t┃\t\t\t\t\t┃");
				   }
				    printf("\n\t\t\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
				    
				    key = getch();
					if(key==224){
						key = getch(); //224값 버림 
					}
					if(key == UP){ //위 방향키 
						if(menuNum>1){ menuNum--; } 
					} else if(key == DOWN){ //아래 방향키
						if(menuNum<4){ menuNum++; } 
					}
					system("cls"); //화면 지우기 
					printf("키 : %d , 메뉴 : %d , user : %s\n", key, menuNum, userList[curruntUser].Name);
				} while(key != ENTER);//end of while 
				system("cls");
				
				if (menuNum != 4){
					longLesson(menuNum, curruntUser);
				} else {
					menuNum=1;
				}

   				break;
   		}//end of switch

}

void AtoZLesson(int currntUser){
	srand(time(NULL)); 
	int index = rand()%5;
	
	float dura, score;
	int m, d, yy, h, mm, s;
	int i, j, n = 0, y = 6;
	char user[50];
	float Duration = 0; //연습시간?? 
	float Gross_speed = 0; //타자수 
	float Accuracy = 0; //정확도 
	int AccuracyCount = 0; //틀린 글자 수 
	int Score = 0; //점수 
	clock_t start, end;
	struct tm *t;
	time_t timer;
	char date[50];
	
	char line[80]="";
	char alpha[27] ="abcdefghijklmnopqrxtuvwxyz";
	
	strcpy(user, userList[currntUser].Name);
	    
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=초록, 5=자주, 연한노랑14
    printf("\n \t\t\t\t▶  A to Z  ◀\n\n");
    printf("user : %s", user);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //2=초록, 5=자주, 연한노랑14
	printf("\n\n%s", alpha);
	
	start = clock();
	gotoxy(0, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gets(line);
	end = clock();
	Gross_speed =  ((float)(strlen(line)-AccuracyCount) / (float)(end-start)*60)*100;
	
	//정확도 계산하기
	AccuracyCount = 0;
	for(i = 0; i < strlen(line) ; i++){
		if (alpha[i]!=line[i]) {
			AccuracyCount++;
		}
	}
	//정확도 
	Accuracy = (1-((float)AccuracyCount/(float)strlen(line))) * 100;
		
	timer = time(NULL);
	t = localtime(&timer);
	//date = 
	
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //2=초록, 5=자주, 연한노랑14
	printf("\n \t\t\t\t▶  타자연습 결과  ◀\n\n");
	printf("Name : %s\n", user);
	printf("Lesson title : AtoZ\n");
	dura = ((end - start) / (double)1000);
	printf("Duration : %.1f seconds\n", dura);
	printf("Gross Speed : %.f WPM\n", Gross_speed);
	printf("Accuracy : %.1f \n", Accuracy);
	score = (Gross_speed + Accuracy)*10;
	printf("Score : %.f \n",  score);
	printf("날짜 : %d, %d, %d\n", mm = t->tm_mon+1, d = t->tm_mday, yy = t->tm_year + 1900);
	printf("time [hh:mm:ss] = [%d:%d:%d]\n", h = t->tm_hour, m = t->tm_min, s = t->tm_sec);
	
	FILE *fpw = NULL;
	fpw = fopen("record.txt", "a");
	fprintf(fpw, "%s AtoZ %.1f %.f %.1f %.f %d/%d/%d %d:%d:%d", 
				user, dura, Gross_speed, Accuracy, score, mm, d, yy, h, m, s);
	fprintf(fpw, "\n");
	printf("\n파일 쓰기 성공\n");
	fclose(fpw);
	
	while (!kbhit()); //키 입력 대기 
	fflush(stdin);
    	
	
    
}

void shortLesson(int currntUser){
	srand(time(NULL)); 
	int index = rand()%5;
	
	float dura, score;
	int m, d, yy, h, mm, s;
	int i, j, n = 0, y = 6;
	char user[50];
	float Duration = 0; //연습시간?? 
	float Gross_speed = 0; //타자수 
	float Accuracy = 0; //정확도 
	int AccuracyCount = 0; //틀린 글자 수 
	int Score = 0; //점수 
	clock_t start, end;
	struct tm *t;
	time_t timer;
	char date[50];
	
	char line[80]="";
	
	strcpy(user, userList[currntUser].Name);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=초록, 5=자주, 연한노랑14
    printf("\n \t\t\t\t▶  짧  은  글    연  습  ◀\n\n");
    printf("user : %s, ", user);
    printf("글자수 : %d \n\n", shortLessonList[index].length_of_letters);
    //printf("user : %s,\t\t Gross speed : %.f,\t Accuracy : %.1f% \n\n\n", user, Gross_speed, Accuracy);
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //2=초록, 5=자주, 연한노랑14
	printf("%s", shortLessonList[index].letters);
	
	start = clock();
	gotoxy(0, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gets(line);
	end = clock();
	Gross_speed =  ((float)(strlen(line)-AccuracyCount) / (float)(end-start)*60)*100;
	
	//정확도 계산하기
	AccuracyCount = 0;
	for(i = 0; i < strlen(line) ; i++){
		if (shortLessonList[index].letters[i]!=line[i]) {
			AccuracyCount++;
		}
	}
	//정확도 
	Accuracy = (1-((float)AccuracyCount/(float)strlen(line))) * 100;
		
	timer = time(NULL);
	t = localtime(&timer);
	//date = 
	
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //2=초록, 5=자주, 연한노랑14
	printf("\n \t\t\t\t▶  타자연습 결과  ◀\n\n");
	printf("Name : %s\n", user);
	printf("Lesson title : 짧은글연습\n");
	dura = ((end - start) / (double)1000);
	printf("Duration : %.1f seconds\n", dura);
	printf("Gross Speed : %.f WPM\n", Gross_speed);
	printf("Accuracy : %.1f \n", Accuracy);
	score = (Gross_speed + Accuracy)*10;
	printf("Score : %.f \n",  score);
	printf("날짜 : %d, %d, %d\n", mm = t->tm_mon+1, d = t->tm_mday, yy = t->tm_year + 1900);
	printf("time [hh:mm:ss] = [%d:%d:%d]\n", h = t->tm_hour, m = t->tm_min, s = t->tm_sec);
	
	FILE *fpw = NULL;
	fpw = fopen("record.txt", "a");
	fprintf(fpw, "%s 짧은글연습 %.1f %.f %.1f %.f %d/%d/%d %d:%d:%d", 
				user, dura, Gross_speed, Accuracy, score, mm, d, yy, h, m, s);
	fprintf(fpw, "\n");
	printf("\n파일 쓰기 성공\n");
	fclose(fpw);

   // saveRecord(user, "짧은글연습", dura, Gross_speed, Accuracy, score, mm, d, yy, h, m, s);
    
    
	while (!kbhit()); //키 입력 대기 
	fflush(stdin);
    	
   // 	printf("\n %s 짧은글연습 %f %f %f %f %d/%d/%d %d:%d:%d", 
//		user, dura, Gross_speed, Accuracy, score, mm, d, yy, h, m, s);
   // saveRecord(user, "짧은글연습", dura, Gross_speed, Accuracy, score, mm, d, yy, h, m, s);

}

void longLesson(int index, int currntUser){
	index--;
	//CONSOLE_SCREEN_BUFFER_INFO cursor;
	float dura, score;
	int m, d, yy, h, mm, s;
	int i, j, n = 0, y = 8;
	char user[50];
	float Duration = 0; //연습시간?? 
	float Gross_speed = 0; //타자수 
	float Accuracy = 0; //정확도 
	int AccuracyCount = 0; //틀린 글자 수 
	int Score = 0; //점수 
	clock_t start, end;
	struct tm *t;
	time_t timer;
	char date[50];
	
	char line[80]="";
	char typing[1000]="";
	//char Date[50];
	//int Start_time[3];
	//while(1){
		strcpy(user, userList[currntUser].Name);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=초록, 5=자주, 연한노랑14
	    printf("\n \t\t\t\t▶  긴  글  연  습  ◀\n\n");
	    printf("제목 : %s, 글자수 : %d \n", longLessonList[index].Lesson_title, longLessonList[index].length_of_letters);
	    printf("user : %s,\t\t Gross speed : %.f,\t Accuracy : %.1f% \n\n\n", user, Gross_speed, Accuracy);
	    
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //2=초록, 5=자주, 연한노랑14
    	for(i = 0; i < longLessonList[index].length_of_letters; i++) {
    		printf("%c", longLessonList[index].letters[i]);
    		
    		if(i!=0 && i%80==0) {
				printf("\n\n");
			}
		}
	
	start = clock();
	while(1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		//printf("%d, \n", y);
		gotoxy(0, y);
		
		//GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
		//if(cursor.dwCursorPosition.X>=80) gotoxy(80, y);
		//if(key == 27) {
		//	break;
		//}

		gets(line);
		strcat(typing, line);
		if(key == ENTER) {
			y += 2;
		}
		
		//타수 계산하기
		end = clock();
		Gross_speed =  ((float)(strlen(typing)-AccuracyCount) / (float)(end-start)*60)*100;
		
		//정확도 계산하기
		AccuracyCount = 0;
		for(i = 0; i < strlen(typing) ; i++){
			//if(i%81==0){ i++; } 
			if (longLessonList[index].letters[i]!=typing[i]) {
				AccuracyCount++;
			}
		}
		
		//정확도 
		Accuracy = (1-((float)AccuracyCount/(float)strlen(typing))) * 100;

		gotoxy(0, 4);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=초록, 5=자주, 연한노랑14
		printf("user : %s ,\t\t Gross speed : %.f,\t Accuracy : %.1f% \n\n\n", user, Gross_speed, Accuracy);
		
		
		gotoxy(0, 28);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("키 : %d, 입력길이 : %d ", key, strlen(typing));
		printf("틀린글자 : %d 개. ", AccuracyCount);
		//printf("\n %s", typing);
		if(strlen(typing)>=longLessonList[index].length_of_letters){
			break;
		}
		

		//system("cls");
	}
	system("cls");
	end = clock();
	
	timer = time(NULL);
	t = localtime(&timer);
	//date = 
	
	//if(key != 27) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //2=초록, 5=자주, 연한노랑14
		printf("\n \t\t\t\t▶  타자연습 결과  ◀\n\n");
		printf("Name : %s\n", user);
		printf("Lesson title : 긴글연습\n");
		dura = ((end - start) / (double)1000);
		printf("Duration : %.1f seconds\n", dura);
		printf("Gross Speed : %.f WPM\n", Gross_speed);
		printf("Accuracy : %.1f \n", Accuracy);
		score = (Gross_speed + Accuracy)*10;
		printf("Score : %.f \n",  score);
		printf("날짜 : %d, %d, %d\n", mm = t->tm_mon+1, d = t->tm_mday, yy = t->tm_year + 1900);
		printf("time [hh:mm:ss] = [%d:%d:%d]\n", h = t->tm_hour, m = t->tm_min, s = t->tm_sec);
		
		FILE *fpw = NULL;
		fpw = fopen("record.txt", "a");
		fprintf(fpw, "%s 긴글연습 %.1f %.f %.1f %.f %d/%d/%d %d:%d:%d", 
					user, dura, Gross_speed, Accuracy, score, mm, d, yy, h, m, s);
		fprintf(fpw, "\n");
		printf("\n 파일 쓰기 성공. 종료\n");
		fclose(fpw);
		while (!kbhit()); //키 입력 대기 
		fflush(stdin);
	//}
} 

void gotoxy(int x, int y) {
	COORD POS;
	POS.X = x;
	POS.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
}


