/*
이 C++ 코드는 OpenCV 라이브러리를 사용하여 두 개의 입력 이미지에 대한 패턴 매칭 작업을 수행합니다. 코드는 두 개의 그레이스케일 이미지를 읽습니다. 
하나는 주요 검색 이미지(search_wally.png)이고 다른 하나는 더 작은 패턴 이미지(search_ptrn.png)입니다.
목표는 패턴 이미지를 검색 이미지 내에서 찾아 그 위치에 사각형을 그리는 것입니다.

코드의 단계별 설명은 다음과 같습니다:

OpenCV 및 C++ 표준 I/O에 필요한 헤더와 라이브러리를 포함합니다.
'cv'와 'std' 네임스페이스를 사용합니다.
main 함수를 정의합니다.
검색 이미지와 패턴 이미지를 그레이스케일 형식으로 읽습니다.
검색 이미지와 동일한 크기의 빈 매칭 이미지를 생성합니다.
검색 이미지에서 패턴을 찾은 위치를 저장하기 위한 포인트 벡터를 초기화합니다.
행과 열에 대한 중첩 루프를 사용하여 패턴 매칭을 수행합니다.
각 위치에 대해 검색 이미지와 패턴 이미지 간의 제곱 차이 합(TM_SQDIFF)을 계산합니다.
패턴 및 검색 이미지 강도의 제곱 합의 곱의 제곱근으로 제곱 차이 합(TM_SQDIFF_NORMED)을 나누어 정규화합니다.
매칭 이미지에 정규화된 값을 저장합니다.
TM_SQDIFF가 0이면 현재 포인트를 찾은 포인트 벡터에 추가합니다.
컬러 형식으로 검색 이미지를 읽습니다.
찾은 패턴 위치 주변에 사각형을 그립니다.
찾은 패턴 위치 주변에 사각형이 그려진 결과 이미지를 보여줍니다.
이미지 창을 닫을 때까지 키 입력을 기다립니다.
0을 반환하고 main 함수를 종료합니다.
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