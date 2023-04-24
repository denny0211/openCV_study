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
    Mat inputImage = imread("../Build/x64/images/lena.jpg", IMREAD_GRAYSCALE);

    if (inputImage.empty()) {
        cout << "이미지를 불러올 수 없습니다. 경로를 확인하세요." << endl;
        return -1;
    }

    // 결과 이미지를 저장할 Mat 객체를 생성합니다.
    Mat thresholded_image;

    // 이미지를 이진화합니다.
    threshold(inputImage, thresholded_image, 128, 255, THRESH_BINARY);

    // 원본 이미지와 이진화된 이미지를 출력합니다.
    imshow("Input Image", inputImage);
    imshow("Thresholded Image", thresholded_image);

    waitKey(0);
    return 0;
}
