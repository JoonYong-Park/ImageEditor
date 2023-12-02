#define _CRT_SECURE_NO_WARNINGS // fopen 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <conio.h>              // (_getch)화면에서 키 입력을 처리하기 위해 사용되는 헤더 파일
#include <windows.h>            // 글자 색상 변경을 위해 사용되는 헤더 파일
#pragma warning(disable:4996)   // 경고 메시지 4996을 무시하는 pragma 지시문

#define W 256
#define H 256

// 파일 이름
char readFile[100];
char writeFile[100];

// 파일 포인터
FILE* fp; 

// 영상 데이터를 저장할 배열
unsigned char Readbuf[256][256];  
unsigned char Writebuf[256][256]; 

// 사용자 정의 함수 선언
void setColor();          // 글자 색상 변경
void open();              // 영상 읽기
void save();              // 영상 저장
void LeftRight();         // 좌우 반전
void UpDown();            // 상하 반전
void light();             // 밝게
void dark();              // 어둡게
void zoomIn();            // 확대
void zoomOut();           // 축소
void noise();             // 노이즈 제거
void binarization();      // 이진화


int main() {
    int color = 1; 
    int choice = 0;             // 메뉴 선택을 저장하는 변수
    
    setColor(color);
    printf("편집할 이미지의 이름을 입력하시오: ");
    scanf("%s", readFile);

    open();

    while (1) {                 // 무한 루프: 게임 메뉴를 계속 표시하고 사용자 입력을 처리합니다.
        setColor(color++);
        if(color == 16) color = 1;
        system("cls");          // 화면을 지우고 메뉴를 다시 출력합니다. (Windows 환경에서 사용)

        printf("편집할 이미지의 이름을 입력하시오: %s\n\n",readFile);

        printf("--[편집 내용 선택]--\n");
        if (choice == 0) printf("|-> 1. 좌우 반전   |\n"); // 현재 선택된 항목에 화살표 표시
        else printf("|   1. 좌우 반전   |\n");
        if (choice == 1) printf("|-> 2. 상하 반전   |\n");
        else printf("|   2. 상하 반전   |\n");
        if (choice == 2) printf("|-> 3. 밝게        |\n");
        else printf("|   3. 밝게        |\n");
        if (choice == 3) printf("|-> 4. 어둡게      |\n");
        else printf("|   4. 어둡게      |\n");
        if (choice == 4) printf("|-> 5. 확대        |\n");
        else printf("|   5. 확대        |\n");
        if (choice == 5) printf("|-> 6. 축소        |\n");
        else printf("|   6. 축소        |\n");
        if (choice == 6) printf("|-> 7. 노이즈 제거 |\n");
        else printf("|   7. 노이즈 제거 |\n");
        if (choice == 7) printf("|-> 8. 이진화      |\n");
        else printf("|   8. 이진화      |\n");
        if (choice == 8) printf("|-> 9. 종료        |\n");
        else printf("|   9. 종료        |\n");
        printf("--------------------\n");
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
                light();
            }
            else if (choice == 3) {
            	dark();
            }
			else if (choice == 4) {
			    zoomIn();
			}
			else if (choice == 5) {
				zoomOut();
			}
			else if (choice == 6) {
			    noise();
			}
			else if (choice == 7) {
				binarization();
			}
            else if (choice == 8) {
                printf("\n!!이용해 주셔서 감사합니다!!\n");
                return 0;
            }
            printf("저장 되었습니다.");
        }
    }
}
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void open() {
    // 영상 취득
    fp = fopen(readFile, "rb");
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, W * H, fp);   //	(저장할 주소, 데이터 크기, 데이터 개수, 파일포인터)
    }							    	 // 파일에서 데이터 읽어와 Readbuf 배열에 저장
    fclose(fp); // 파일 닫기
}
void save() {
    // 영상 저장
    printf("저장할 파일 이름을 입력하시오: ");
    scanf("%s", writeFile);

    fp = fopen(writeFile, "wb"); // 파일을 쓰기 모드로 열기

    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp); // Writebuf 배열의 데이터를 파일에 쓰기
    fclose(fp); // 파일 닫기
}

void LeftRight() {

    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            Writebuf[j][i] = Readbuf[j][256 - i]; // 좌 우 뒤집기

    save();
}

void UpDown() {

    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            Writebuf[j][i] = Readbuf[256 - j][i]; // 상 하 뒤집기
    //Writebuf[j][i] = Readbuf[255 - j][255 - i]; // 상하좌우 뒤집기

    save();
}
void light() {

   
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            
            printf("%d\t", Readbuf[i][j]);
            if (Readbuf[i][j] >= 225) {
                Writebuf[i][j] = 255;
                printf("밝은색");
            }

            else {
                Writebuf[i][j] = Readbuf[i][j] + 30;
            }

        }
    }
    save();
}

void dark() {

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {

            
            if (Readbuf[i][j] < 30) {
                Writebuf[i][j] = 0;
                printf("어두운색");
            }
            else {
                Writebuf[i][j] = Readbuf[i][j] - 30;
            }
        }
    }
    save();
}

void zoomIn() {
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {

            int x = (int)(i * 0.7);
            int y = (int)(j * 0.7);
            if (x >= 0 && x < 256 && y >= 0 && y < 256) {
                Writebuf[i][j] = Readbuf[x][y];
            }
        }
    }
    save();
}

void zoomOut() {
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            int x = (int)(i * 1.5);
            int y = (int)(j * 1.5);

            if (x >= 0 && x < 256 && y >= 0 && y < 256) {
                 Writebuf[i][j] = Readbuf[x][y];
            }
            else {
                Writebuf[i][j] = 0;
            }
        }
    }
    save();
}

void noise() {
    // 메디안 필터: 3x3
    for (int i = 1; i < 255; i++) {
        for (int j = 1; j < 255; j++) {
            unsigned char temp[9] = { 0 };
            temp[0] = Readbuf[i - 1][j - 1];
            temp[1] = Readbuf[i - 1][j];
            temp[2] = Readbuf[i - 1][j + 1];
            temp[3] = Readbuf[i][j - 1];
            temp[4] = Readbuf[i][j];
            temp[5] = Readbuf[i][j + 1];
            temp[6] = Readbuf[i + 1][j - 1];
            temp[7] = Readbuf[i + 1][j];
            temp[8] = Readbuf[i + 1][j + 1];

            for (int k = 0; k < 9; k++) {
                for (int l = 0; l < 9 - k - 1; l++) {
                    if (temp[l] > temp[l + 1]) {
                        unsigned char tmp = temp[l];
                        temp[l] = temp[l + 1];
                        temp[l + 1] = tmp;
                    }
                }
            }

            Writebuf[i][j] = temp[4];
        }
    }
	save();
}

void binarization() {

    // 임계값 설정 : 각 픽셀의 밝기 값이 그 임계값보다 크면 1(또는 흰색), 작으면 0(또는 검은색)으로 변환
    int T = 100;

    // 영상이진화 : 0과 1 또는 검은색과 흰색으로 나누는 과정
    for (int i = 0; i < 256; i++){
        for (int j = 0; j < 256; j++) {
            if (Readbuf[i][j] < T) {
                Writebuf[i][j] = 0;
            }
            else {
                Writebuf[i][j] = 255;
            }
        }
    }


   /* for (int i = 0; i < W * H; i++) {
        if (readbuf[i] < T) {
            writebuf[i] = 0;
        }
        else {
            writebuf[i] = 255;
        }
    }*/
	save();
}