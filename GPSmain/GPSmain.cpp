// GPSmain.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
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

	return 0;
}

