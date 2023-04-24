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
    // ���Ͽ��� �̹��� �б�
    Mat image = imread("../Build/x64/images/lena.jpg", IMREAD_COLOR);

    // �̹����� ����� �ε�Ǿ����� Ȯ�� 
    if (image.empty()) {
        std::cout << "Error: Could not read the image." << std::endl;
        return 1;
    }

    // �����쿡 �̹��� ǥ��
    imshow("Example Image", image);

    // Ű ������ ��ٸ� �� â �ݱ�
    waitKey(0);
    return 0;
}