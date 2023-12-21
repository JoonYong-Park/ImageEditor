//#include <stdio.h>
//#include <stdlib.h>
//#include "ConversionFile.h"
//#define _CRT_SECURE_NO_WARNINGS
//
//// RAW �����͸� JPG �����ͷ� ��ȯ�մϴ�.
//unsigned char* convert_raw_to_jpg(unsigned char* raw_data, int width, int height, int channels) {
//    // JPG �������� ũ�⸦ ����մϴ�.
//    int jpg_size = width * height * channels * 3;
//
//    // JPG �����͸� �����մϴ�.
//    unsigned char* jpg_data = (unsigned char*)malloc(jpg_size);
//
//    // RAW �����͸� JPG �����ͷ� ��ȯ�մϴ�.
//    for (int y = 0; y < height; y++) {
//        for (int x = 0; x < width; x++) {
//            for (int c = 0; c < channels; c++) {
//                // RAW �������� �� ä���� JPG �������� RGB ä�η� ��ȯ�մϴ�.
//                jpg_data[y * width * 3 + x * 3 + c] = (raw_data[y * width * channels + x * channels + c] + 128) / 255;
//            }
//        }
//    }
//
//    return jpg_data;
//}
//
//
//// �Լ� ����
//int main(int argc, char* argv[]) {
//    // RAW ������ ���
//    const char* raw_file_path = "lena.raw";
//
//    // JPG ������ ���
//    const char* jpg_file_path = "1111111111111.jpg";
//
//    // RAW ������ ũ��
//    int width, height, channels;
//
//    // RAW ������ �����͸� �����ϱ� ���� �迭
//    unsigned char* raw_data = NULL;
//
//    // JPG ������ �����͸� �����ϱ� ���� �迭
//    unsigned char* jpg_data = NULL;
//
//    // RAW ������ �н��ϴ�.
//    FILE* raw_file = fopen(raw_file_path, "rb");
//    if (raw_file == NULL) {
//        printf("RAW ������ ���� ���߽��ϴ�.\n");
//        return -1;
//    }
//
//    // RAW ������ ����� �н��ϴ�.
//    fread(&width, sizeof(int), 1, raw_file);
//    fread(&height, sizeof(int), 1, raw_file);
//    fread(&channels, sizeof(int), 1, raw_file);
//
//    // RAW ������ �����͸� �н��ϴ�.
//    raw_data = (unsigned char*)malloc(width * height * channels);
//    fread(raw_data, width * height * channels, 1, raw_file);
//
//    // RAW ������ �ݽ��ϴ�.
//    fclose(raw_file);
//
//    // JPG ������ �����մϴ�.
//    FILE* jpg_file = fopen(jpg_file_path, "wb");
//    if (jpg_file == NULL) {
//        printf("JPG ������ �������� ���߽��ϴ�.\n");
//        return -1;
//    }
//
//    // RAW �����͸� JPG �����ͷ� ��ȯ�մϴ�.
//    jpg_data = convert_raw_to_jpg(raw_data, width, height, channels);
//
//    // JPG ���Ͽ� �����͸� ���ϴ�.
//    fwrite(jpg_data, width * height * channels, 1, jpg_file);
//
//    // JPG ������ �ݽ��ϴ�.
//    fclose(jpg_file);
//
//    // �޸𸮸� �����մϴ�.
//    free(raw_data);
//    free(jpg_data);
//
//    return 0;
//}
