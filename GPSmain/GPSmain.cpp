// GPSmain.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
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

	//cap.set(CAP_PROP_FPS,15);		//FPS�w��
	//cap.set(CAP_PROP_FRAME_WIDTH, 1280);	//�T�C�Y�w��
	//cap.set(CAP_PROP_FRAME_HEIGHT, 720);	//�T�C�Y�w��
	//cap.set(CAP_PROP_EXPOSURE, -5);	//�I�o�w��@-9�`0

	if (!cap.isOpened()) {
		return -1;
	}

	//�R���\�[���ɃJ�����ݒ�̏o��(�����l�j
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

		//�摜�Ƀe�L�X�g�𖄂ߍ���
		//putText(frame, text, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 0), 2, 8, false);


		//////////////////Marker Detection//////////////////

		//Ok, let's detect
		MDetector.detect(frame, Markers);
		//for each marker, draw info and its boundaries in the image
		for (unsigned int i = 0; i<Markers.size(); i++) {
			cout << Markers[i] << endl;
			Markers[i].draw(frame, Scalar(0, 0, 255), 2);
		}

		//////////////////�L�����u���[�V����//////////////////
		//�`�F�b�J�[�{�[�h��������Ȃ��ƁE�E�E�B�����ĂȂ��B
		//ARUCO�ɂ��J�����p�����[�^��n���͂��B�n���Ă�T���v���͂������B

		///////////////////////�F�ϊ�/////////////////////////
		//cv::cvtColor(frame, cvt_frame, COLOR_RGB2HSV);


		//////////////////////�����ϊ�///////////////////////
		/*
		// �ϊ��O�̉摜�ł̍��W
		const Point2f src_pt[] = {
			Point2f(360 , 69),
			Point2f(85  , 602),
			Point2f(1032, 79),
			Point2f(1198, 631) };



		// �ϊ���̉摜�ł̍��W
		const Point2f dst_pt[] = {
			Point2f(50,                 50),
			Point2f(50,                 50 + HEIGHT - 1),
			Point2f(50 + WIDTH - 1,       50),
			Point2f(50 + WIDTH - 1,       50 + HEIGHT - 1) };


		// homography �s����v�Z
		const Mat homography_matrix = getPerspectiveTransform(src_pt, dst_pt);

		// �����ϊ�
		//warpPerspective(frame, cvt_frame, homography_matrix,frame.size());

		*/
		//////////////�\��
		imshow("window", frame);


		int key = cv::waitKey(1);
		if (key == 113)//q�{�^���������ꂽ�Ƃ�
		{
			break;//while���[�v���甲����D
		}
	
	}
	/*
	//�J�����g�f�B���N�g���̓f�t�H���g��C:\Users\�o���[�U���p\Documents\Visual Studio 2015\Projects\GPSmain\GPSmain
	string name = "p.jpg";
	//string name = C:\\temp\\p.jpg

	Mat image;
	image = imread(name, IMREAD_COLOR);

	//�������ǂݍ��܂�Ă��邩�H
	if (!image.data) {
		return -1;
	}

	//�A���S���Y����AKAZE���g�p����
	auto algorithm = cv::AKAZE::create();

	// �����_���o
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

