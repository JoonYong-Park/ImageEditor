//#include <stdio.h>
//#include <stdlib.h>
//#include "ConversionFile.h"
//#define _CRT_SECURE_NO_WARNINGS
//
//// RAW 데이터를 JPG 데이터로 변환합니다.
//unsigned char* convert_raw_to_jpg(unsigned char* raw_data, int width, int height, int channels) {
//    // JPG 데이터의 크기를 계산합니다.
//    int jpg_size = width * height * channels * 3;
//
//    // JPG 데이터를 생성합니다.
//    unsigned char* jpg_data = (unsigned char*)malloc(jpg_size);
//
//    // RAW 데이터를 JPG 데이터로 변환합니다.
//    for (int y = 0; y < height; y++) {
//        for (int x = 0; x < width; x++) {
//            for (int c = 0; c < channels; c++) {
//                // RAW 데이터의 각 채널을 JPG 데이터의 RGB 채널로 변환합니다.
//                jpg_data[y * width * 3 + x * 3 + c] = (raw_data[y * width * channels + x * channels + c] + 128) / 255;
//            }
//        }
//    }
//
//    return jpg_data;
//}
//
//
//// 함수 정의
//int main(int argc, char* argv[]) {
//    // RAW 파일의 경로
//    const char* raw_file_path = "lena.raw";
//
//    // JPG 파일의 경로
//    const char* jpg_file_path = "1111111111111.jpg";
//
//    // RAW 파일의 크기
//    int width, height, channels;
//
//    // RAW 파일의 데이터를 저장하기 위한 배열
//    unsigned char* raw_data = NULL;
//
//    // JPG 파일의 데이터를 저장하기 위한 배열
//    unsigned char* jpg_data = NULL;
//
//    // RAW 파일을 읽습니다.
//    FILE* raw_file = fopen(raw_file_path, "rb");
//    if (raw_file == NULL) {
//        printf("RAW 파일을 열지 못했습니다.\n");
//        return -1;
//    }
//
//    // RAW 파일의 헤더를 읽습니다.
//    fread(&width, sizeof(int), 1, raw_file);
//    fread(&height, sizeof(int), 1, raw_file);
//    fread(&channels, sizeof(int), 1, raw_file);
//
//    // RAW 파일의 데이터를 읽습니다.
//    raw_data = (unsigned char*)malloc(width * height * channels);
//    fread(raw_data, width * height * channels, 1, raw_file);
//
//    // RAW 파일을 닫습니다.
//    fclose(raw_file);
//
//    // JPG 파일을 생성합니다.
//    FILE* jpg_file = fopen(jpg_file_path, "wb");
//    if (jpg_file == NULL) {
//        printf("JPG 파일을 생성하지 못했습니다.\n");
//        return -1;
//    }
//
//    // RAW 데이터를 JPG 데이터로 변환합니다.
//    jpg_data = convert_raw_to_jpg(raw_data, width, height, channels);
//
//    // JPG 파일에 데이터를 씁니다.
//    fwrite(jpg_data, width * height * channels, 1, jpg_file);
//
//    // JPG 파일을 닫습니다.
//    fclose(jpg_file);
//
//    // 메모리를 해제합니다.
//    free(raw_data);
//    free(jpg_data);
//
//    return 0;
//}
