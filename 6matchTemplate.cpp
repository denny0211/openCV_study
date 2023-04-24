/*
�� C++ �ڵ�� OpenCV ���̺귯���� ����Ͽ� �� ���� �Է� �̹����� ���� ���� ��Ī �۾��� �����մϴ�. �ڵ�� �� ���� �׷��̽����� �̹����� �н��ϴ�. 
�ϳ��� �ֿ� �˻� �̹���(search_wally.png)�̰� �ٸ� �ϳ��� �� ���� ���� �̹���(search_ptrn.png)�Դϴ�.
��ǥ�� ���� �̹����� �˻� �̹��� ������ ã�� �� ��ġ�� �簢���� �׸��� ���Դϴ�.

�ڵ��� �ܰ躰 ������ ������ �����ϴ�:

OpenCV �� C++ ǥ�� I/O�� �ʿ��� ����� ���̺귯���� �����մϴ�.
'cv'�� 'std' ���ӽ����̽��� ����մϴ�.
main �Լ��� �����մϴ�.
�˻� �̹����� ���� �̹����� �׷��̽����� �������� �н��ϴ�.
�˻� �̹����� ������ ũ���� �� ��Ī �̹����� �����մϴ�.
�˻� �̹������� ������ ã�� ��ġ�� �����ϱ� ���� ����Ʈ ���͸� �ʱ�ȭ�մϴ�.
��� ���� ���� ��ø ������ ����Ͽ� ���� ��Ī�� �����մϴ�.
�� ��ġ�� ���� �˻� �̹����� ���� �̹��� ���� ���� ���� ��(TM_SQDIFF)�� ����մϴ�.
���� �� �˻� �̹��� ������ ���� ���� ���� ���������� ���� ���� ��(TM_SQDIFF_NORMED)�� ������ ����ȭ�մϴ�.
��Ī �̹����� ����ȭ�� ���� �����մϴ�.
TM_SQDIFF�� 0�̸� ���� ����Ʈ�� ã�� ����Ʈ ���Ϳ� �߰��մϴ�.
�÷� �������� �˻� �̹����� �н��ϴ�.
ã�� ���� ��ġ �ֺ��� �簢���� �׸��ϴ�.
ã�� ���� ��ġ �ֺ��� �簢���� �׷��� ��� �̹����� �����ݴϴ�.
�̹��� â�� ���� ������ Ű �Է��� ��ٸ��ϴ�.
0�� ��ȯ�ϰ� main �Լ��� �����մϴ�.
*/
#include <iostream>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#pragma comment(lib,"opencv_world470d.lib")
#else	//RELEASE
#pragma comment(lib,"opencv_world470.lib")
#endif
using namespace std;
using namespace cv;

int main()
{

	Mat search_img = cv::imread("../Build/x64/images/search_wally.png", IMREAD_GRAYSCALE);
	Mat search_ptrn = cv::imread("../Build/x64/images/search_ptrn.png", IMREAD_GRAYSCALE);

	Mat matching_img = Mat::zeros(search_img.size(), CV_64F);

	vector<Point> ptFind; ptFind.clear();
	//pattern matching
	for (size_t row = 0; row < search_img.rows - search_ptrn.rows; row++)
	{
		for (size_t col = 0; col < search_img.cols - search_ptrn.cols; col++)
		{
			uchar* pSearch = search_img.data;
			uchar* pPtrn = search_ptrn.data;

			double TM_SQDIFF = 0.0;
			double TM_SQDIFF_NORMED = 0.0;
			for (size_t prow = 0; prow < search_ptrn.rows; prow++)
			{
				for (size_t pcol = 0; pcol < search_ptrn.cols; pcol++)
				{
					int search_index = (row + prow) * search_img.cols + (col + pcol);
					int ptrn_index = prow * search_ptrn.cols + pcol;

					double diff = pSearch[search_index] - pPtrn[ptrn_index];
					TM_SQDIFF += (diff * diff);
				}
			}
			double ptrnSQ = 0., searchSQ = 0.;
			for (size_t prow = 0; prow < search_ptrn.rows; prow++)
			{
				for (size_t pcol = 0; pcol < search_ptrn.cols; pcol++)
				{
					int search_index = (row + prow) * search_img.cols + (col + pcol);
					int ptrn_index = prow * search_ptrn.cols + pcol;
					searchSQ += pSearch[search_index] * pSearch[search_index];
					ptrnSQ += pPtrn[ptrn_index] * pPtrn[ptrn_index];
				}
			}

			if (TM_SQDIFF == 0)
				ptFind.push_back(Point(col, row));
			if (ptrnSQ == 0) ptrnSQ = 1;
			TM_SQDIFF_NORMED = TM_SQDIFF / sqrt(ptrnSQ * searchSQ);
			matching_img.at<double>(row, col) = TM_SQDIFF_NORMED;
		}
	}

	Mat search_img_color = cv::imread("../Build/x64/images/search_wally.png", IMREAD_ANYCOLOR);
	for (size_t i = 0; i < ptFind.size(); i++)
	{
		cv::rectangle(search_img_color, Rect(ptFind[i].x, ptFind[i].y, search_ptrn.cols, search_ptrn.rows), Scalar(0, 0, 255), 3);
	}

	imshow("search_img_color", search_img_color);
	waitKey(0);


	return 0;
}