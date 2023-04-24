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

    // ��������� �̹����� ������ Mat ��ü ����
    Mat resizedImage;

    // ���ϴ� ��� ũ�� ����
    Size outputSize(300, 300);

    // resize() �Լ��� ����Ͽ� �Է� �̹����� ũ�� ����
    resize(inputImage, resizedImage, outputSize, 0, 0, INTER_LINEAR);

    // ���� �̹����� ��������� �̹��� ǥ��
    imshow("���� �̹���", inputImage);
    imshow("��������� �̹���", resizedImage);

    // Ű�� ���� ������ ����ϰ� â �ݱ�
    waitKey(0);
    destroyAllWindows();

    return 0;
}