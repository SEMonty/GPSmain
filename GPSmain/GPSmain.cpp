// GPSmain.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>

using namespace cv;
using namespace std;

int main()
{

	//カレントディレクトリはデフォルトでC:\Users\｛ユーザ名｝\Documents\Visual Studio 2015\Projects\GPSmain\GPSmain
	string name = "p.jpg";
	//string name = C:\\temp\\p.jpg

	Mat image;
	image = imread(name, IMREAD_COLOR);

	//正しく読み込まれているか？
	if (!image.data) {
		return -1;
	}

	//アルゴリズムにAKAZEを使用する
	auto algorithm = cv::AKAZE::create();

	// 特徴点抽出
	vector<cv::KeyPoint> keypoints;
	algorithm->detect(image, keypoints);

	Mat output;
	drawKeypoints(image, keypoints, output);


	namedWindow("test", WINDOW_AUTOSIZE);
	imshow("test", output);

	waitKey(0);

	return 0;
}

