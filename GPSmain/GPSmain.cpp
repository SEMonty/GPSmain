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

struct marker_result
{
	int id;
	double position[3];
	double orientation[4];
};

int main()
{

	VideoCapture cap(0);

	//cap.set(CAP_PROP_FPS,15);		//FPS指定
	//cap.set(CAP_PROP_FRAME_WIDTH, 1280);	//サイズ指定
	//cap.set(CAP_PROP_FRAME_HEIGHT, 720);	//サイズ指定
	//cap.set(CAP_PROP_EXPOSURE, -5);	//露出指定　-9～0
	//cap.set(CAP_PROP_GAIN, 255);

	if (!cap.isOpened()) {
		return -1;
	}

	//コンソールにカメラ設定の出力(初期値）
	cout << "Web Camera settings:" << endl;
	cout << "Width:" + to_string(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Height:" + to_string(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "FPS:" + to_string(cap.get(CAP_PROP_FPS)) << endl;
	cout << "Exposure:" + to_string(cap.get(CAP_PROP_EXPOSURE)) << endl; 
	cout << "Gain:" + to_string(cap.get(CAP_PROP_GAIN)) << endl;
	cout << "Iso_speed:" + to_string(cap.get(CAP_PROP_ISO_SPEED)) << endl;
	cout << "speed:" + to_string(cap.get(CAP_PROP_SPEED)) << endl;

	int WIDTH = cap.get(CAP_PROP_FRAME_WIDTH);
	int HEIGHT = cap.get(CAP_PROP_FRAME_HEIGHT);
	WIDTH = 300;
	HEIGHT = 300;

	MarkerDetector MDetector;
	vector<Marker> Markers;
	//透視変換前の4隅座標
	Point2f lefttop;
	Point2f righttop;
	Point2f leftbottom;
	Point2f rightbottom;

	aruco::MarkerDetector::Params params = MDetector.getParams();

	cout << "_thresParam1" << ": " << params._thresParam1 << endl;
	cout << "_thresParam1_range" << ": " << params._thresParam1_range << endl;
	cout << "_thresParam2" << ": " << params._thresParam2 << endl;
	cout << "_borderDistThres" << ": " << params._borderDistThres << endl;
	cout << "_subpix_wsize" << ": " << params._subpix_wsize << endl;

	params._thresParam1 = 3;	//ブロックサイズ
	params._thresParam1_range = 0;
	params._thresParam2 = 9;

	MDetector.setParams(params);

	while (1) {

		Mat frame;
		Mat cvt_frame;
		cap >> frame;

		//画像にテキストを埋め込む
		//putText(frame, text, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 0), 2, 8, false);
		
	

		//////////////////Marker Detection//////////////////
		//Ok, let's detect
		MDetector.detect(frame, Markers);
		//for each marker, draw info and its boundaries in the image
		marker_result result;
		for (unsigned int i = 0; i<Markers.size(); i++) {
			//cout << Markers[i] << endl;
			Markers[i].draw(frame, Scalar(0, 0, 255), 2);
			//左上
			if (Markers[i].id == 0) 
			{
				lefttop = Markers[i][2];
				//cout << Markers[i][2].x << ", " << Markers[i][2].y << endl;
				circle(frame, lefttop , 2, Scalar(0, 255, 0), 3, 4);
			}
			if (Markers[i].id == 1)
			{
				righttop = Markers[i][3];//Point2f(Markers[i][0].x, Markers[i][2].y);
				circle(frame, righttop, 2, Scalar(255, 0, 0), 3, 4);
			}

			if (Markers[i].id == 2)
			{
				rightbottom = Markers[i][0];
				circle(frame, rightbottom, 2, Scalar(255,0 , 255), 3, 4);
			}

			if (Markers[i].id == 3)
			{
				leftbottom = Markers[i][1];
				circle(frame, leftbottom, 2, Scalar(0, 255, 255), 3, 4);
			}


		}

		//////////////////キャリブレーション//////////////////
		//チェッカーボードを印刷しないと・・・。試してない。
		//ARUCOにもカメラパラメータを渡すはず。渡してるサンプルはあった。

		///////////////////////色変換/////////////////////////
		//cv::cvtColor(frame, cvt_frame, COLOR_RGB2HSV);


		//////////////////////透視変換///////////////////////
		
		// 変換前の画像での座標
		const Point2f src_pt[] = {lefttop, leftbottom,righttop,rightbottom};

		// 変換後の画像での座標
		const Point2f dst_pt[] = {
			Point2f(0,0),
			Point2f(0,HEIGHT - 1),
			Point2f(WIDTH - 1, 0),
			Point2f(WIDTH - 1, HEIGHT - 1) };


		// homography 行列を計算
		const Mat homography_matrix = getPerspectiveTransform(src_pt, dst_pt);

		// 透視変換
		warpPerspective(frame, cvt_frame, homography_matrix, Size(WIDTH,HEIGHT));

		
		//////////////表示
		cv::imshow("window", frame);
		cv::imshow("window2", cvt_frame);


		int key = cv::waitKey(1);
		if (key == 113)//qボタンが押されたとき
		{
			break;//whileループから抜ける．
		}
	
	}

	waitKey(0);

	cv::destroyAllWindows();
	return 0;
}

