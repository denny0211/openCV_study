#include <iostream>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#pragma comment(lib,"opencv_world470d.lib")
#else	//RELEASE
#pragma comment(lib,"opencv_world470.lib")
#endif
using namespace std;
using namespace cv;


int main() {
    // 이미지 파일 읽기
    Mat inputImage = imread("../Build/x64/images/lena.jpg", IMREAD_COLOR);
    if (inputImage.empty()) {
        cerr << "Error: 이미지를 불러올 수 없습니다." << endl;
        return -1;
    }

    // 결과 이미지를 저장할 Mat 객체 생성
    Mat grayImage;

    // BGR 이미지를 회색조로 변환
    cvtColor(inputImage, grayImage, COLOR_BGR2GRAY);

    // 변환된 이미지 표시
    imshow("Input Image", inputImage);
    imshow("Gray Image", grayImage);

    // 키보드 입력 대기
    waitKey(0);

    return 0;
}