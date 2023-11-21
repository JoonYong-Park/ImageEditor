#define _CRT_SECURE_NO_WARNINGS // fopen ���� ���� ���� ������ ���� ����
#include <stdio.h>
#include <conio.h>              // (_getch)ȭ�鿡�� Ű �Է��� ó���ϱ� ���� ���Ǵ� ��� ����
#pragma warning(disable:4996)   // ��� �޽��� 4996�� �����ϴ� pragma ���ù�

char readFile[100];
char writeFile[100];

FILE* fp; // ���� ������ ����

unsigned char Readbuf[256][256];  // ���� ���� �迭 ����
unsigned char Writebuf[256][256]; // ����   �� �迭 ����

void save() {
    // ���� ����
    printf("������ ���� �̸��� �Է��Ͻÿ�: ");
    scanf("%s", writeFile);

    fp = fopen(writeFile, "wb"); // "LENA_256x256_8bit_new.raw" ������ ���� ���� ����
    //fp = fopen("LENA_256x256_8bit_4_up_down_left_right.raw", "wb"); // "LENA_256x256_8bit_new.raw" ������ ���� ���� ����

    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp); // Writebuf �迭�� �����͸� ���Ͽ� ����
    fclose(fp); // ���� �ݱ�
}

void LeftRight() {
    /////// ���� ��� �� �¿� ��Ī ///////
    fp = fopen(readFile, "rb"); 
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);   //	(������ �ּ�, ������ ũ��, ������ ����, ����������)
    }							    	 // ���Ͽ��� ������ �о�� Readbuf �迭�� ����
    fclose(fp); // ���� �ݱ�

    // ���� ����: ������ �������� ������ (Readbuf�� ���� ������ Writebuf�� ����)
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            Writebuf[j][i] = Readbuf[j][256 - i]; // �� �� ������
    
    save();
}

void UpDown() {
    /////// ���� ��� �� ���� ��Ī ///////
    fp = fopen(readFile, "rb"); // "LENA_256x256_8bit.raw" ������ �б� ���� ����
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);   //	(������ �ּ�, ������ ũ��, ������ ����, ����������)
    }							    	 // ���Ͽ��� ������ �о�� Readbuf �迭�� ����
    fclose(fp); // ���� �ݱ�

    // ���� ����: ������ �������� ������ (Readbuf�� ���� ������ Writebuf�� ����)
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            Writebuf[j][i] = Readbuf[256 - j][i]; // �� �� ������
    //Writebuf[j][i] = Readbuf[255 - j][255 - i]; // �����¿� ������

    save();
}

int main() {
    int choice = 0;             // �޴� ������ �����ϴ� ����

    printf("������ �̹����� �̸��� �Է��Ͻÿ�: ");
    scanf("%s", readFile);

    while (1) {                 // ���� ����: ���� �޴��� ��� ǥ���ϰ� ����� �Է��� ó���մϴ�.

        system("cls");          // ȭ���� ����� �޴��� �ٽ� ����մϴ�. (Windows ȯ�濡�� ���)

        printf("������ �̹����� �̸��� �Է��Ͻÿ�: %s\n\n",readFile);

        printf("-[���� ���� ����]-\n");
        if (choice == 0) printf("-> 1. �¿� ����\n"); // ���� ���õ� �׸� ȭ��ǥ ǥ��
        else printf("   1. �¿� ����\n");

        if (choice == 1) printf("-> 2. ���� ����\n");
        else printf("   2. ���� ����\n");

        if (choice == 2) printf("-> 3. ���\n");
        else printf("   3. ���\n");

        if (choice == 3) printf("-> 4. ��Ӱ�\n");
        else printf("   4. ��Ӱ�\n");

        if (choice == 4) printf("-> 5. Ȯ��\n");
        else printf("   5. Ȯ��\n");

        if (choice == 5) printf("-> 6. ���\n");
        else printf("   6. ���\n");

        if (choice == 6) printf("-> 7. ������ ����\n");
        else printf("   7. ������ ����\n");

        if (choice == 7) printf("-> 8. ����ȭ\n");
        else printf("   8. ����ȭ\n");

        if (choice == 8) printf("-> 9. ����\n");
        else printf("   9. ����\n");



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
                printf("\n�̿��� �ּż� �����մϴ�!!!!!\n");
                return 0;
            }
            printf("���� �Ǿ����ϴ�.");
        }
    }
}
