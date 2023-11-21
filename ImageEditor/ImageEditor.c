#define _CRT_SECURE_NO_WARNINGS // fopen 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <conio.h>              // (_getch)화면에서 키 입력을 처리하기 위해 사용되는 헤더 파일
#pragma warning(disable:4996)   // 경고 메시지 4996을 무시하는 pragma 지시문

char readFile[100];
char writeFile[100];

FILE* fp; // 파일 포인터 선언

unsigned char Readbuf[256][256];  // 영상 읽을 배열 선언
unsigned char Writebuf[256][256]; // 영상   쓸 배열 선언

void save() {
    // 영상 저장
    printf("저장할 파일 이름을 입력하시오: ");
    scanf("%s", writeFile);

    fp = fopen(writeFile, "wb"); // "LENA_256x256_8bit_new.raw" 파일을 쓰기 모드로 열기
    //fp = fopen("LENA_256x256_8bit_4_up_down_left_right.raw", "wb"); // "LENA_256x256_8bit_new.raw" 파일을 쓰기 모드로 열기

    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp); // Writebuf 배열의 데이터를 파일에 쓰기
    fclose(fp); // 파일 닫기
}

void LeftRight() {
    /////// 영상 취득 및 좌우 대칭 ///////
    fp = fopen(readFile, "rb"); 
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);   //	(저장할 주소, 데이터 크기, 데이터 개수, 파일포인터)
    }							    	 // 파일에서 데이터 읽어와 Readbuf 배열에 저장
    fclose(fp); // 파일 닫기

    // 영상 편집: 영상을 수직으로 뒤집기 (Readbuf의 값을 뒤집어 Writebuf에 저장)
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            Writebuf[j][i] = Readbuf[j][256 - i]; // 좌 우 뒤집기
    
    save();
}

void UpDown() {
    /////// 영상 취득 및 상하 대칭 ///////
    fp = fopen(readFile, "rb"); // "LENA_256x256_8bit.raw" 파일을 읽기 모드로 열기
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);   //	(저장할 주소, 데이터 크기, 데이터 개수, 파일포인터)
    }							    	 // 파일에서 데이터 읽어와 Readbuf 배열에 저장
    fclose(fp); // 파일 닫기

    // 영상 편집: 영상을 수직으로 뒤집기 (Readbuf의 값을 뒤집어 Writebuf에 저장)
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            Writebuf[j][i] = Readbuf[256 - j][i]; // 상 하 뒤집기
    //Writebuf[j][i] = Readbuf[255 - j][255 - i]; // 상하좌우 뒤집기

    save();
}

int main() {
    int choice = 0;             // 메뉴 선택을 저장하는 변수

    printf("편집할 이미지의 이름을 입력하시오: ");
    scanf("%s", readFile);

    while (1) {                 // 무한 루프: 게임 메뉴를 계속 표시하고 사용자 입력을 처리합니다.

        system("cls");          // 화면을 지우고 메뉴를 다시 출력합니다. (Windows 환경에서 사용)

        printf("편집할 이미지의 이름을 입력하시오: %s\n\n",readFile);

        printf("-[편집 내용 선택]-\n");
        if (choice == 0) printf("-> 1. 좌우 반전\n"); // 현재 선택된 항목에 화살표 표시
        else printf("   1. 좌우 반전\n");

        if (choice == 1) printf("-> 2. 상하 반전\n");
        else printf("   2. 상하 반전\n");

        if (choice == 2) printf("-> 3. 밝게\n");
        else printf("   3. 밝게\n");

        if (choice == 3) printf("-> 4. 어둡게\n");
        else printf("   4. 어둡게\n");

        if (choice == 4) printf("-> 5. 확대\n");
        else printf("   5. 확대\n");

        if (choice == 5) printf("-> 6. 축소\n");
        else printf("   6. 축소\n");

        if (choice == 6) printf("-> 7. 노이즈 제거\n");
        else printf("   7. 노이즈 제거\n");

        if (choice == 7) printf("-> 8. 이진화\n");
        else printf("   8. 이진화\n");

        if (choice == 8) printf("-> 9. 종료\n");
        else printf("   9. 종료\n");



        int key = _getch();                      // 키 입력을 받습니다. 사용자가 누른 키의 아스키 코드를 반환합니다.
        if (key == 224) {                        // 방향키 입력
            key = _getch();                      // 확장 키 입력을 다시 받습니다.
            if (key == 72 && choice > 0)         // UP 화살표 키를 누르고 현재 선택이 0보다 크면
                choice--;
            else if (key == 80 && choice < 8)    // DOWN 화살표 키를 누르고 현재 선택이 1보다 작으면
                choice++;
        }

        else if (key == 13) {                    // Enter키 입력 
            if (choice == 0) {
                LeftRight();
            }
            else if (choice == 1) {
                UpDown();
            }
            else if (choice == 2) {
            
            }
            else if (choice == 3) {
            
            }
			else if (choice == 4) {
			
			}
			else if (choice == 5) {
			
			}
			else if (choice == 6) {
			
			}
			else if (choice == 7) {
			
			}
            else if (choice == 8) {
                printf("\n이용해 주셔서 감사합니다!!!!!\n");
                return 0;
            }
            printf("저장 되었습니다.");
        }
    }
}
