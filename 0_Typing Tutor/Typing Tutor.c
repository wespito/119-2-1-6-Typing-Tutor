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
struct longLesson { //��ۿ����� �����͸� ���� 
	char Lesson_title[50];
	int length_of_letters;
	char letters[1000]; //1000�� ���� 
};
struct longLesson longLessonList[100];
struct shortLesson { //��ۿ����� �����͸� ���� 
	int length_of_letters;
	char letters[1000]; //1000�� ���� 
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
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=�ʷ�, 5=����, ���ѳ��14
	    printf("\t\t\t\t��  T  Y  P  I  N  G   T  E  S  T  E  R  ��\n\n");
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	    printf("�� Press the arrow keys: �� or �� to navigate the options.\n");
	    printf("�� Press <ENTER> key to accept an option.\n");
	    printf("�� [or] Press the number keys to slelect your choice\n");
	    printf("\n"); 
	    printf("\n");
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	    printf("\n\t\t\t\t����������������������������������������������������������������������������������");
	    printf("\n\t\t\t\t��\t***MAIN MENU***\t\t\t��");
	    printf("\n\t\t\t\t��\t\t\t\t\t��");
	   
	   for(i=1; i<6; i++){
	   	printf("\n\t\t\t\t��");
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
	   	printf("��");
	   	printf("\n\t\t\t\t��\t\t\t\t\t��");
	   }
	   
	    printf("\n\t\t\t\t����������������������������������������������������������������������������������");
		
		key = getch();
		if(key==224){
			key = getch(); //224�� ���� 
		}
		if(key == UP){ //�� ����Ű 
			if(menuNum>1){ menuNum--; } 
		} else if(key == DOWN){ //�Ʒ� ����Ű
			if(menuNum<5){ menuNum++; } 
		} else if(key == ENTER) {
			switch (menuNum){
				case 1: //select user
					system("cls");
					userSelectMenu();
					break;
				case 2: //statistics
					system("cls"); //ȭ�� ����� 
					statistics();
					break;
				case 3: //view user records
					system("cls");
					ViewUserRecords();
					break;
				case 4: //about
					system("cls"); //ȭ�� ����� 
	    			printf("\n\t\t\t\t��  a  b  o  u  t  ��\n\n\n");
					printf("\t\t\tŸ�ڿ����� �� �� �ִ� ���α׷�\n\n\n");
					printf("\t\t\tatoz - a���� z���� Ÿ�ڸ� ����\n\n");
					printf("\t\t\t�F���� ���� - �� �� ������ Ÿ�ڸ� ����\n\n"); 
					printf("\t\t\t��� ���� - ���� �� ������ Ÿ�ڸ� ����\n\n"); 
					while (!kbhit()); //Ű �Է� ��� 
					fflush(stdin);
					menuNum = 1;
					break;
				case 5: //quit
					system("cls"); //ȭ�� ����� 
					printf("Ÿ�ڿ����� �����մϴ�");
					exit(0);
					break;
			}
		}
		system("cls"); //ȭ�� ����� 
		printf("Ű : %d , �޴� : %d \n", key, menuNum);
	}//end of while
}

void loadFiles(void){
	//�̸� ��ü ���� �ҷ��� 
	int i, j, length = 0; 
	int c; //read �� 
	FILE *fpr = NULL;
	fpr = fopen("longtestList.txt", "r"); //read ���� file open
	if( fpr == NULL ) {
		printf("longtestList ���� �б� ����\n");
	}
	
	do { 
		fscanf(fpr, "%s", 
		&longLessonList[i].Lesson_title //����� Lesson_title�� �о���� 
		);
		i++; //size
	}while((c = fgetc(fpr)) != EOF); //End Of File ���� 
	
	printf("���� �б� ����\n");

	for(j = 0; j < i; j++) {
		length = 0;
		//printf("��ۺҷ�����\n");
		fpr = fopen(strcat(longLessonList[j].Lesson_title, ".txt"), "rt"); //Lesson_title�� �ҷ����� 
		if( fpr == NULL ) {
		printf("���� �б� ����\n");
		}
		
		while((c = fgetc(fpr)) != EOF) {
		 	longLessonList[j].letters[length] = c;
		 	length++; //���� �� 
			/*fscanf(fpr, "%c", 
			&longLessonList[j].letters[length]
			);
			length++; //���� �� */
		} //End Of File ���� 
		longLessonList[j].length_of_letters = length;
	}	
	
	
	fclose(fpr);
	//printf("���� �б� �Ϸ�\n\n");
	
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
} //+save���� �Լ�? 

void statistics() {
	FILE *fpr = NULL;
	int i=0, j=0, c;
	//char serch_word[50];
	fpr = fopen("record.txt", "r"); //read ���� file open
	if( fpr == NULL ) {
		printf("���� �б� ����\n");
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
	}while((c = fgetc(fpr)) != EOF); //End Of File ���� 
	printf("%d ���� �б� �Ϸ�", recordSize);
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("\n\t\t\t\t��  player Statistics  ��\n\n");
    printf("     Name       Lesson    WPM   Accuracy Score     Date       Time\n");
    printf("-------------------------------------------------------------------------\n");
    //printf("enter user name : ");
    for(j=0;j<recordSize-1;j++) {
		printf("%10s %12s %5d %5.1f�� %6d  %11s  [%8s] \n", 
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
    scanf_s("%s", &serch_word); //�˻��� ���� 
    
	for(j = 0; j < i; j++){ //i�� �� ��ϵ� ������ �� 
		if(strcmp(serch_word, userList[j].Name) == 0) {
			break;
		}
	}
	if(j==i) {
		printf("��ġ ������ ���� \n");
	} else {
		system( "cls" ); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("\n\t\t\t\t��  player Statistics  ��\n\n");
		
		printf("Name : \n", userList[j].Name);
		printf("Lesson title : \n", userList[j].Lesson_title);
		printf("Gross Speed  : %.f WPM\n", userList[j].Gross_speed);
		printf("Accuracy : %.1f \n", userList[j].Accuracy);
		printf("Score : \n", userList[j].Score);
		printf("��¥ : %d, %d, %d\n");
		printf("Time [hh:mm:ss] = [%d:%d:%d]\n");
	}*/
	menuNum=1; 
	key=0;
	while (!kbhit()); //Ű �Է� ��� 
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
		printf("\t\t\t\t\t��  Select User  ��\n\n");
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
        //printf("\n\t\t\t\t\t�ڷΰ���\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("\n\t\t\t\t==============================================");

        key = _getch();
        if (key == 224) {
            key = _getch(); //224값 버림 
            fseek(fp, 0, SEEK_SET);
        }
        system("cls"); //화면 지우기 
        if (key == 27) {
        	break;
		}
        if (key == UP) { //위 방향키 
            if (menuNum1 > 1) { menuNum1--; }
        }
        else if (key == DOWN) { //아래 방향키
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
    printf("Ű : %d , �޴� : %d \n", key, menuNum1);
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
    
    printf("\n\t\t\t\t��  add a new profile  ��\n\n");
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
	fpr = fopen("record.txt", "r"); //read ���� file open
	if( fpr == NULL ) {
		printf("���� �б� ����\n");
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
	}while((c = fgetc(fpr)) != EOF); //End Of File ���� 
	//printf("%d ���� �б� �Ϸ�", recordSize);
	
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
    printf("\n\t\t\t\t\t��  R E S U L T  ��\n\n");
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=�ʷ�, 5=����, ���ѳ��14
	    printf("\t\t\t\t��  L  e  s  s  o  n   ��  ��  ��\n\n");
	    printf("\n\n\n\n\n");
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	    printf("\n\t\t\t\t����������������������������������������������������������������������������������");
	    printf("\n\t\t\t\t��\t***Lesson list***\t\t��");
	    printf("\n\t\t\t\t��\t\t\t\t\t��");
	   
	   for(i=1; i<5; i++){
	   	printf("\n\t\t\t\t��");
	   		switch (i){
	   			case 1: 
	   				if(menuNum==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					printf("   <1> A to Z\t\t\t\t");
	   				break;
	   			case 2: 
	   				if(menuNum==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					printf("   <2> ª���� ����\t\t\t");
	   				break;
	   			case 3: 
	   				if(menuNum==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					printf("   <3> ��� ����\t\t\t");
					break;
				case 4: 
	   				if(menuNum==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					printf("   <4> �ڷΰ���\t\t\t");
	   				break;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	   	printf("��");
	   	printf("\n\t\t\t\t��\t\t\t\t\t��");
	   }
	    printf("\n\t\t\t\t����������������������������������������������������������������������������������");
	    
	    key = getch();
		if(key==224){
			key = getch(); //224�� ���� 
			//system("cls"); //ȭ�� ����� 
		}
		if(key == UP){ //�� ����Ű 
			if(menuNum>1){ menuNum--; } 
		} else if(key == DOWN){ //�Ʒ� ����Ű
			if(menuNum<4){ menuNum++; } 
		} else if(key == ENTER && menuNum != 4) {
			system("cls");
			beginSession(menuNum, curruntUser); //menuNum �Ѱ��� 
		}
		system("cls");
		printf("Ű : %d , �޴� : %d , user : %s\n", key, menuNum, userList[curruntUser].Name);
	} while(!(key == ENTER && menuNum == 4)); //end of while  �ڷΰ��� 
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
   			case 2: //ª���� ���� 
   				shortLesson(curruntUser);
   				break;
   			case 3: //�� �� ����
   				printf("\n");
			
				do { 
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=�ʷ�, 5=����, ���ѳ��14
				    printf("\t\t\t\t��  ��   ��  ��   ��\n\n");
				    printf("\n\n\n\n\n");
				    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				    printf("\n\t\t\t\t����������������������������������������������������������������������������������");
				    printf("\n\t\t\t\t��\t***�� list***\t\t\t��");
				    printf("\n\t\t\t\t��\t\t\t\t\t��");
				   
				   for(i=1; i<5; i++){
				   	printf("\n\t\t\t\t��");
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
								printf("   <%d> �ڷΰ���\t\t\t", i);
				   			break;
						}
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				   	printf("��");
				   	printf("\n\t\t\t\t��\t\t\t\t\t��");
				   }
				    printf("\n\t\t\t\t����������������������������������������������������������������������������������");
				    
				    key = getch();
					if(key==224){
						key = getch(); //224�� ���� 
					}
					if(key == UP){ //�� ����Ű 
						if(menuNum>1){ menuNum--; } 
					} else if(key == DOWN){ //�Ʒ� ����Ű
						if(menuNum<4){ menuNum++; } 
					}
					system("cls"); //ȭ�� ����� 
					printf("Ű : %d , �޴� : %d , user : %s\n", key, menuNum, userList[curruntUser].Name);
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
	float Duration = 0; //�����ð�?? 
	float Gross_speed = 0; //Ÿ�ڼ� 
	float Accuracy = 0; //��Ȯ�� 
	int AccuracyCount = 0; //Ʋ�� ���� �� 
	int Score = 0; //���� 
	clock_t start, end;
	struct tm *t;
	time_t timer;
	char date[50];
	
	char line[80]="";
	char alpha[27] ="abcdefghijklmnopqrxtuvwxyz";
	
	strcpy(user, userList[currntUser].Name);
	    
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=�ʷ�, 5=����, ���ѳ��14
    printf("\n \t\t\t\t��  A to Z  ��\n\n");
    printf("user : %s", user);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //2=�ʷ�, 5=����, ���ѳ��14
	printf("\n\n%s", alpha);
	
	start = clock();
	gotoxy(0, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gets(line);
	end = clock();
	Gross_speed =  ((float)(strlen(line)-AccuracyCount) / (float)(end-start)*60)*100;
	
	//��Ȯ�� ����ϱ�
	AccuracyCount = 0;
	for(i = 0; i < strlen(line) ; i++){
		if (alpha[i]!=line[i]) {
			AccuracyCount++;
		}
	}
	//��Ȯ�� 
	Accuracy = (1-((float)AccuracyCount/(float)strlen(line))) * 100;
		
	timer = time(NULL);
	t = localtime(&timer);
	//date = 
	
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //2=�ʷ�, 5=����, ���ѳ��14
	printf("\n \t\t\t\t��  Ÿ�ڿ��� ���  ��\n\n");
	printf("Name : %s\n", user);
	printf("Lesson title : AtoZ\n");
	dura = ((end - start) / (double)1000);
	printf("Duration : %.1f seconds\n", dura);
	printf("Gross Speed : %.f WPM\n", Gross_speed);
	printf("Accuracy : %.1f \n", Accuracy);
	score = (Gross_speed + Accuracy)*10;
	printf("Score : %.f \n",  score);
	printf("��¥ : %d, %d, %d\n", mm = t->tm_mon+1, d = t->tm_mday, yy = t->tm_year + 1900);
	printf("time [hh:mm:ss] = [%d:%d:%d]\n", h = t->tm_hour, m = t->tm_min, s = t->tm_sec);
	
	FILE *fpw = NULL;
	fpw = fopen("record.txt", "a");
	fprintf(fpw, "%s AtoZ %.1f %.f %.1f %.f %d/%d/%d %d:%d:%d", 
				user, dura, Gross_speed, Accuracy, score, mm, d, yy, h, m, s);
	fprintf(fpw, "\n");
	printf("\n���� ���� ����\n");
	fclose(fpw);
	
	while (!kbhit()); //Ű �Է� ��� 
	fflush(stdin);
    	
	
    
}

void shortLesson(int currntUser){
	srand(time(NULL)); 
	int index = rand()%5;
	
	float dura, score;
	int m, d, yy, h, mm, s;
	int i, j, n = 0, y = 6;
	char user[50];
	float Duration = 0; //�����ð�?? 
	float Gross_speed = 0; //Ÿ�ڼ� 
	float Accuracy = 0; //��Ȯ�� 
	int AccuracyCount = 0; //Ʋ�� ���� �� 
	int Score = 0; //���� 
	clock_t start, end;
	struct tm *t;
	time_t timer;
	char date[50];
	
	char line[80]="";
	
	strcpy(user, userList[currntUser].Name);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=�ʷ�, 5=����, ���ѳ��14
    printf("\n \t\t\t\t��  ª  ��  ��    ��  ��  ��\n\n");
    printf("user : %s, ", user);
    printf("���ڼ� : %d \n\n", shortLessonList[index].length_of_letters);
    //printf("user : %s,\t\t Gross speed : %.f,\t Accuracy : %.1f% \n\n\n", user, Gross_speed, Accuracy);
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //2=�ʷ�, 5=����, ���ѳ��14
	printf("%s", shortLessonList[index].letters);
	
	start = clock();
	gotoxy(0, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gets(line);
	end = clock();
	Gross_speed =  ((float)(strlen(line)-AccuracyCount) / (float)(end-start)*60)*100;
	
	//��Ȯ�� ����ϱ�
	AccuracyCount = 0;
	for(i = 0; i < strlen(line) ; i++){
		if (shortLessonList[index].letters[i]!=line[i]) {
			AccuracyCount++;
		}
	}
	//��Ȯ�� 
	Accuracy = (1-((float)AccuracyCount/(float)strlen(line))) * 100;
		
	timer = time(NULL);
	t = localtime(&timer);
	//date = 
	
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //2=�ʷ�, 5=����, ���ѳ��14
	printf("\n \t\t\t\t��  Ÿ�ڿ��� ���  ��\n\n");
	printf("Name : %s\n", user);
	printf("Lesson title : ª���ۿ���\n");
	dura = ((end - start) / (double)1000);
	printf("Duration : %.1f seconds\n", dura);
	printf("Gross Speed : %.f WPM\n", Gross_speed);
	printf("Accuracy : %.1f \n", Accuracy);
	score = (Gross_speed + Accuracy)*10;
	printf("Score : %.f \n",  score);
	printf("��¥ : %d, %d, %d\n", mm = t->tm_mon+1, d = t->tm_mday, yy = t->tm_year + 1900);
	printf("time [hh:mm:ss] = [%d:%d:%d]\n", h = t->tm_hour, m = t->tm_min, s = t->tm_sec);
	
	FILE *fpw = NULL;
	fpw = fopen("record.txt", "a");
	fprintf(fpw, "%s ª���ۿ��� %.1f %.f %.1f %.f %d/%d/%d %d:%d:%d", 
				user, dura, Gross_speed, Accuracy, score, mm, d, yy, h, m, s);
	fprintf(fpw, "\n");
	printf("\n���� ���� ����\n");
	fclose(fpw);

   // saveRecord(user, "ª���ۿ���", dura, Gross_speed, Accuracy, score, mm, d, yy, h, m, s);
    
    
	while (!kbhit()); //Ű �Է� ��� 
	fflush(stdin);
    	
   // 	printf("\n %s ª���ۿ��� %f %f %f %f %d/%d/%d %d:%d:%d", 
//		user, dura, Gross_speed, Accuracy, score, mm, d, yy, h, m, s);
   // saveRecord(user, "ª���ۿ���", dura, Gross_speed, Accuracy, score, mm, d, yy, h, m, s);

}

void longLesson(int index, int currntUser){
	index--;
	//CONSOLE_SCREEN_BUFFER_INFO cursor;
	float dura, score;
	int m, d, yy, h, mm, s;
	int i, j, n = 0, y = 8;
	char user[50];
	float Duration = 0; //�����ð�?? 
	float Gross_speed = 0; //Ÿ�ڼ� 
	float Accuracy = 0; //��Ȯ�� 
	int AccuracyCount = 0; //Ʋ�� ���� �� 
	int Score = 0; //���� 
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=�ʷ�, 5=����, ���ѳ��14
	    printf("\n \t\t\t\t��  ��  ��  ��  ��  ��\n\n");
	    printf("���� : %s, ���ڼ� : %d \n", longLessonList[index].Lesson_title, longLessonList[index].length_of_letters);
	    printf("user : %s,\t\t Gross speed : %.f,\t Accuracy : %.1f% \n\n\n", user, Gross_speed, Accuracy);
	    
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //2=�ʷ�, 5=����, ���ѳ��14
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
		
		//Ÿ�� ����ϱ�
		end = clock();
		Gross_speed =  ((float)(strlen(typing)-AccuracyCount) / (float)(end-start)*60)*100;
		
		//��Ȯ�� ����ϱ�
		AccuracyCount = 0;
		for(i = 0; i < strlen(typing) ; i++){
			//if(i%81==0){ i++; } 
			if (longLessonList[index].letters[i]!=typing[i]) {
				AccuracyCount++;
			}
		}
		
		//��Ȯ�� 
		Accuracy = (1-((float)AccuracyCount/(float)strlen(typing))) * 100;

		gotoxy(0, 4);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=�ʷ�, 5=����, ���ѳ��14
		printf("user : %s ,\t\t Gross speed : %.f,\t Accuracy : %.1f% \n\n\n", user, Gross_speed, Accuracy);
		
		
		gotoxy(0, 28);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("Ű : %d, �Է±��� : %d ", key, strlen(typing));
		printf("Ʋ������ : %d ��. ", AccuracyCount);
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //2=�ʷ�, 5=����, ���ѳ��14
		printf("\n \t\t\t\t��  Ÿ�ڿ��� ���  ��\n\n");
		printf("Name : %s\n", user);
		printf("Lesson title : ��ۿ���\n");
		dura = ((end - start) / (double)1000);
		printf("Duration : %.1f seconds\n", dura);
		printf("Gross Speed : %.f WPM\n", Gross_speed);
		printf("Accuracy : %.1f \n", Accuracy);
		score = (Gross_speed + Accuracy)*10;
		printf("Score : %.f \n",  score);
		printf("��¥ : %d, %d, %d\n", mm = t->tm_mon+1, d = t->tm_mday, yy = t->tm_year + 1900);
		printf("time [hh:mm:ss] = [%d:%d:%d]\n", h = t->tm_hour, m = t->tm_min, s = t->tm_sec);
		
		FILE *fpw = NULL;
		fpw = fopen("record.txt", "a");
		fprintf(fpw, "%s ��ۿ��� %.1f %.f %.1f %.f %d/%d/%d %d:%d:%d", 
					user, dura, Gross_speed, Accuracy, score, mm, d, yy, h, m, s);
		fprintf(fpw, "\n");
		printf("\n ���� ���� ����. ����\n");
		fclose(fpw);
		while (!kbhit()); //Ű �Է� ��� 
		fflush(stdin);
	//}
} 

void gotoxy(int x, int y) {
	COORD POS;
	POS.X = x;
	POS.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
}


