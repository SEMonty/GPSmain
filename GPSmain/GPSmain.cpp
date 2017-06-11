// GPSmain.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


#include "aruco-2.0.19/src/aruco.h"
#include "aruco-2.0.19/src/cvdrawingutils.h"

#include <iostream>

using namespace cv;
using namespace std;
using namespace aruco;

int main()
{

	VideoCapture cap(0);

	//cap.set(CAP_PROP_FPS,15);		//FPS指定
	//cap.set(CAP_PROP_FRAME_WIDTH, 1280);	//サイズ指定
	//cap.set(CAP_PROP_FRAME_HEIGHT, 720);	//サイズ指定
	//cap.set(CAP_PROP_EXPOSURE, -5);	//露出指定　-9～0

	if (!cap.isOpened()) {
		return -1;
	}

	//コンソールにカメラ設定の出力(初期値）
	cout << "Web Camera settings:" << endl;
	cout << "Width:" + to_string(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Height:" + to_string(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "FPS:" + to_string(cap.get(CAP_PROP_FPS)) << endl;
	cout << "Exposure:" + to_string(cap.get(CAP_PROP_EXPOSURE)) << endl;

	int WIDTH = cap.get(CAP_PROP_FRAME_WIDTH);
	int HEIGHT = cap.get(CAP_PROP_FRAME_HEIGHT);


	MarkerDetector MDetector;
	vector<Marker> Markers;
	while (1) {
		Mat frame;
		Mat cvt_frame;
		cap >> frame;
		cvt_frame = frame;

		//画像にテキストを埋め込む
		//putText(frame, text, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 0), 2, 8, false);


		//////////////////Marker Detection//////////////////

		//Ok, let's detect
		MDetector.detect(frame, Markers);
		//for each marker, draw info and its boundaries in the image
		for (unsigned int i = 0; i<Markers.size(); i++) {
			cout << Markers[i] << endl;
			Markers[i].draw(frame, Scalar(0, 0, 255), 2);
		}

		//////////////////キャリブレーション//////////////////
		//チェッカーボードを印刷しないと・・・。試してない。
		//ARUCOにもカメラパラメータを渡すはず。渡してるサンプルはあった。

		///////////////////////色変換/////////////////////////
		//cv::cvtColor(frame, cvt_frame, COLOR_RGB2HSV);


		//////////////////////透視変換///////////////////////
		/*
		// 変換前の画像での座標
		const Point2f src_pt[] = {
			Point2f(360 , 69),
			Point2f(85  , 602),
			Point2f(1032, 79),
			Point2f(1198, 631) };



		// 変換後の画像での座標
		const Point2f dst_pt[] = {
			Point2f(50,                 50),
			Point2f(50,                 50 + HEIGHT - 1),
			Point2f(50 + WIDTH - 1,       50),
			Point2f(50 + WIDTH - 1,       50 + HEIGHT - 1) };


		// homography 行列を計算
		const Mat homography_matrix = getPerspectiveTransform(src_pt, dst_pt);

		// 透視変換
		//warpPerspective(frame, cvt_frame, homography_matrix,frame.size());

		*/
		//////////////表示
		imshow("window", frame);


		int key = cv::waitKey(1);
		if (key == 113)//qボタンが押されたとき
		{
			break;//whileループから抜ける．
		}
	
	}
	/*
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
	*/

	destroyAllWindows();
	return 0;
}

