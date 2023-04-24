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
        cout << "�̹����� �ҷ��� �� �����ϴ�. ��θ� Ȯ���ϼ���." << endl;
        return -1;
    }

    // ��� �̹����� ������ Mat ��ü�� �����մϴ�.
    Mat thresholded_image;

    // �̹����� ����ȭ�մϴ�.
    threshold(inputImage, thresholded_image, 128, 255, THRESH_BINARY);

    // ���� �̹����� ����ȭ�� �̹����� ����մϴ�.
    imshow("Input Image", inputImage);
    imshow("Thresholded Image", thresholded_image);

    waitKey(0);
    return 0;
}
