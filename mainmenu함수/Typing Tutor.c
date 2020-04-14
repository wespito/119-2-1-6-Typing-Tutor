#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

//int keycomtrol();
void mainmenu();
//void gotoxy(int x, int y);

#define UP 72
#define DOWN 80


int main() {
    /*int x = 10;
    int y = 20;*/

    mainmenu();


    /*int keycode = keycomtrol();
    gotoxy(x, y);
    if (keycode = UP)
        y--;
    else if (keycode = DOWN)
        y++;
	*/
	
    return 0;
}

/*int keycomtrol() {
    char c = _getch();
    if (c == -32) {
        c = _getch();
        switch (c) {
        case UP:
            printf("위로 이동\n");
            printf("%d \n", c);
            return UP;
            break;
        case DOWN:
            printf("아래로 이동\n");
            return DOWN;
            break;
        }
    }
}*/

void mainmenu() {
	int key;
	int i;
	int menuNum=1;
	
	printf("\n"); //나중에 여기 공백 지울것 
	
	
	while(1){ 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //2=초록, 5=자주, 연한노랑14
    printf("\t\t\t\t\t\t?T Y P I N G  T E S T E R?\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    printf("≫ Press the arrow keys: ↑ or ↓ to navigate the options.\n");
    printf("≫ Press <ENTER> key to accept an option.\n");
    printf("≫ [or] Press the number keys to slelect your choice\n");
    printf("\n"); 
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("\n\t\t\t\t??????????????????????????????????????????????");
    printf("\n\t\t\t\t?        ***MAIN MENU***                     ?");
    printf("\n\t\t\t\t?                                            ?");
   
   for(i=1; i<6; i++){
   	printf("\n\t\t\t\t?");
   		switch (i){
   			case 1: 
   				if(menuNum==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
				printf("   <1> Select User                          ");
   			break;
   			case 2: 
   				if(menuNum==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
				printf("   <2> Statistics                           ");
   			break;
   			case 3: 
   				if(menuNum==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
				printf("   <3> View User Records                    ");
   			break;
   			case 4: 
   				if(menuNum==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
				printf("   <4> About                                ");
   			break;
   			case 5: 
   				if(menuNum==5) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
				printf("   <5> Quit                                 ");
   			break;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
   	printf("?");
   	printf("\n\t\t\t\t?                                            ?");
   }
   
   /*
    printf("\n\t\t\t\t?   <1> Select User                          ?");
    printf("\n\t\t\t\t?                                            ?");
    printf("\n\t\t\t\t?   <2> Statistics                           ?");
    printf("\n\t\t\t\t?                                            ?");
    printf("\n\t\t\t\t?   <3> View User Records                    ?");
    printf("\n\t\t\t\t?                                            ?");
    printf("\n\t\t\t\t?   <4> About                                ?");
    printf("\n\t\t\t\t?                                            ?");
    printf("\n\t\t\t\t?   <5> Quit                                 ?");
    printf("\n\t\t\t\t?                                            ?");
	*/
    printf("\n\t\t\t\t??????????????????????????????????????????????");
	
	key = getch();
	if(key==224){
		key = getch(); //224값 버림 
		system("cls"); //화면 지우기 
	}
	if(key == UP){ //위 방향키 
		if(menuNum>1){ menuNum--; } 
	} else if(key == DOWN){ //아래 방향키
		if(menuNum<5){ menuNum++; } 
	} //menuNum -> 1 ~ 5
	printf("키 : %d , 메뉴 : %d \n", key, menuNum);
}//end of while
}

/*void gotoxy(int x, int y)

{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
*/

