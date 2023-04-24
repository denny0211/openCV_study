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
    // 파일에서 이미지 읽기
    Mat image = imread("../Build/x64/images/lena.jpg", IMREAD_COLOR);

    // 이미지가 제대로 로드되었는지 확인 
    if (image.empty()) {
        std::cout << "Error: Could not read the image." << std::endl;
        return 1;
    }

    // 윈도우에 이미지 표시
    imshow("Example Image", image);

    // 키 누름을 기다린 후 창 닫기
    waitKey(0);
    return 0;
}