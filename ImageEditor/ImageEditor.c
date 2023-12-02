#define _CRT_SECURE_NO_WARNINGS // fopen ���� ���� ���� ������ ���� ����
#include <stdio.h>
#include <conio.h>              // (_getch)ȭ�鿡�� Ű �Է��� ó���ϱ� ���� ���Ǵ� ��� ����
#include <windows.h>            // ���� ���� ������ ���� ���Ǵ� ��� ����
#pragma warning(disable:4996)   // ��� �޽��� 4996�� �����ϴ� pragma ���ù�

#define W 256
#define H 256

// ���� �̸�
char readFile[100];
char writeFile[100];

// ���� ������
FILE* fp; 

// ���� �����͸� ������ �迭
unsigned char Readbuf[256][256];  
unsigned char Writebuf[256][256]; 

// ����� ���� �Լ� ����
void setColor();          // ���� ���� ����
void open();              // ���� �б�
void save();              // ���� ����
void LeftRight();         // �¿� ����
void UpDown();            // ���� ����
void light();             // ���
void dark();              // ��Ӱ�
void zoomIn();            // Ȯ��
void zoomOut();           // ���
void noise();             // ������ ����
void binarization();      // ����ȭ


int main() {
    int color = 1; 
    int choice = 0;             // �޴� ������ �����ϴ� ����
    
    setColor(color);
    printf("������ �̹����� �̸��� �Է��Ͻÿ�: ");
    scanf("%s", readFile);

    open();

    while (1) {                 // ���� ����: ���� �޴��� ��� ǥ���ϰ� ����� �Է��� ó���մϴ�.
        setColor(color++);
        if(color == 16) color = 1;
        system("cls");          // ȭ���� ����� �޴��� �ٽ� ����մϴ�. (Windows ȯ�濡�� ���)

        printf("������ �̹����� �̸��� �Է��Ͻÿ�: %s\n\n",readFile);

        printf("--[���� ���� ����]--\n");
        if (choice == 0) printf("|-> 1. �¿� ����   |\n"); // ���� ���õ� �׸� ȭ��ǥ ǥ��
        else printf("|   1. �¿� ����   |\n");
        if (choice == 1) printf("|-> 2. ���� ����   |\n");
        else printf("|   2. ���� ����   |\n");
        if (choice == 2) printf("|-> 3. ���        |\n");
        else printf("|   3. ���        |\n");
        if (choice == 3) printf("|-> 4. ��Ӱ�      |\n");
        else printf("|   4. ��Ӱ�      |\n");
        if (choice == 4) printf("|-> 5. Ȯ��        |\n");
        else printf("|   5. Ȯ��        |\n");
        if (choice == 5) printf("|-> 6. ���        |\n");
        else printf("|   6. ���        |\n");
        if (choice == 6) printf("|-> 7. ������ ���� |\n");
        else printf("|   7. ������ ���� |\n");
        if (choice == 7) printf("|-> 8. ����ȭ      |\n");
        else printf("|   8. ����ȭ      |\n");
        if (choice == 8) printf("|-> 9. ����        |\n");
        else printf("|   9. ����        |\n");
        printf("--------------------\n");
        int key = _getch();                      // Ű �Է��� �޽��ϴ�. ����ڰ� ���� Ű�� �ƽ�Ű �ڵ带 ��ȯ�մϴ�.
        if (key == 224) {                        // ����Ű �Է�
            key = _getch();                      // Ȯ�� Ű �Է��� �ٽ� �޽��ϴ�.
            if (key == 72 && choice > 0)         // UP ȭ��ǥ Ű�� ������ ���� ������ 0���� ũ��
                choice--;
            else if (key == 80 && choice < 8)    // DOWN ȭ��ǥ Ű�� ������ ���� ������ 1���� ������
                choice++;
        }

        else if (key == 13) {                    // EnterŰ �Է� 
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
                printf("\n!!�̿��� �ּż� �����մϴ�!!\n");
                return 0;
            }
            printf("���� �Ǿ����ϴ�.");
        }
    }
}
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void open() {
    // ���� ���
    fp = fopen(readFile, "rb");
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, W * H, fp);   //	(������ �ּ�, ������ ũ��, ������ ����, ����������)
    }							    	 // ���Ͽ��� ������ �о�� Readbuf �迭�� ����
    fclose(fp); // ���� �ݱ�
}
void save() {
    // ���� ����
    printf("������ ���� �̸��� �Է��Ͻÿ�: ");
    scanf("%s", writeFile);

    fp = fopen(writeFile, "wb"); // ������ ���� ���� ����

    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp); // Writebuf �迭�� �����͸� ���Ͽ� ����
    fclose(fp); // ���� �ݱ�
}

void LeftRight() {

    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            Writebuf[j][i] = Readbuf[j][256 - i]; // �� �� ������

    save();
}

void UpDown() {

    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            Writebuf[j][i] = Readbuf[256 - j][i]; // �� �� ������
    //Writebuf[j][i] = Readbuf[255 - j][255 - i]; // �����¿� ������

    save();
}
void light() {

   
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            
            printf("%d\t", Readbuf[i][j]);
            if (Readbuf[i][j] >= 225) {
                Writebuf[i][j] = 255;
                printf("������");
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
                printf("��ο��");
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
    // �޵�� ����: 3x3
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

    // �Ӱ谪 ���� : �� �ȼ��� ��� ���� �� �Ӱ谪���� ũ�� 1(�Ǵ� ���), ������ 0(�Ǵ� ������)���� ��ȯ
    int T = 100;

    // ��������ȭ : 0�� 1 �Ǵ� �������� ������� ������ ����
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