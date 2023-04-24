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

    // 리사이즈된 이미지를 저장할 Mat 객체 생성
    Mat resizedImage;

    // 원하는 출력 크기 정의
    Size outputSize(300, 300);

    // resize() 함수를 사용하여 입력 이미지의 크기 조정
    resize(inputImage, resizedImage, outputSize, 0, 0, INTER_LINEAR);

    // 원본 이미지와 리사이즈된 이미지 표시
    imshow("원본 이미지", inputImage);
    imshow("리사이즈된 이미지", resizedImage);

    // 키를 누를 때까지 대기하고 창 닫기
    waitKey(0);
    destroyAllWindows();

    return 0;
}