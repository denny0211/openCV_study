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
    // �̹��� ���� �б�
    Mat inputImage = imread("../Build/x64/images/lena.jpg", IMREAD_COLOR);
    if (inputImage.empty()) {
        cerr << "Error: �̹����� �ҷ��� �� �����ϴ�." << endl;
        return -1;
    }

    // ��� �̹����� ������ Mat ��ü ����
    Mat grayImage;

    // BGR �̹����� ȸ������ ��ȯ
    cvtColor(inputImage, grayImage, COLOR_BGR2GRAY);

    // ��ȯ�� �̹��� ǥ��
    imshow("Input Image", inputImage);
    imshow("Gray Image", grayImage);

    // Ű���� �Է� ���
    waitKey(0);

    return 0;
}