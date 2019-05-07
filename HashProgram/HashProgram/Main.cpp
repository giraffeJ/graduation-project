#include "opencv2/opencv.hpp"  
#include <iostream>  
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AudioFile.h"
#include "sha256.h"
#include <string>
#include <chrono>

using namespace cv;
using namespace std;
using namespace chrono;

typedef long long int lli;
lli video_hash() {
	printf("videofile start");
	//동영상 파일로부터 부터 데이터 읽어오기 위해 준비  
	VideoCapture cap("2.mp4");
	system_clock::time_point t1 = system_clock::now();
	if (!cap.isOpened())
	{
		printf("동영상 파일을 열수 없습니다. \n");
	}
	int frame_num = cap.get(CAP_PROP_FRAME_COUNT);
	int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);
	lli r_sum = 0, g_sum = 0, b_sum = 0;
	Mat frame;
	for (int f = 1; f <= frame_num; f += 20) {
		//cap.set(CAP_PROP_POS_FRAMES, f);
		bool success = cap.read(frame);
		if (!success) {
			cout << "Cannot read  frame " << endl;
			break;
		}
		for (int x = 0; x < height; x += 4) {
			for (int y = 0; y < width; y += 4) {

				uchar b = frame.at<Vec3b>(x, y)[0];
				uchar g = frame.at<Vec3b>(x, y)[1];
				uchar r = frame.at<Vec3b>(x, y)[2];

				r_sum += r;
				g_sum += g;
				b_sum += b;
			}
		}
	}
	system_clock::time_point t2 = system_clock::now();
	printf("r: %lld b: %lld g: %lld\n", r_sum, g_sum, b_sum);
	duration<double> sec = t2 - t1;
	printf("execution time : %lf\n", sec);
	return r_sum << 6 + g_sum << 3 + b_sum;
}
AudioFile<double> audioFile;

double audio_hash() {
	system_clock::time_point t1 = system_clock::now();
	audioFile.load("2.wav");
	int numChannels = audioFile.getNumChannels();
	int numSamples = audioFile.getNumSamplesPerChannel();
	system_clock::time_point t2 = system_clock::now();
	double sum = 0;
	for (int i = 0; i < numChannels; i++) {
		for (int j = 0; j < numSamples; j+=10) {
			double currentSample = audioFile.samples[i][j];
			if (currentSample < 0) sum -= currentSample;
			else sum += currentSample;
		}
	}
	system_clock::time_point t3 = system_clock::now();
	printf("Channel num : %d\nsample num : %lld\nsum : %lf\n", numChannels, numChannels*numSamples, sum);
	duration<double> sec1 = t2 - t1;
	duration<double> sec2 = t3 - t2;
	printf("loading time : %lf\nexecution time : %lf\n", sec1, sec2);
	return sum;
}
void encryption() {
	printf("entered.");
	string a = "abcdef";
	string output;
	output = sha256(a);
	cout << output << endl;
}
string change_into_string(lli a) {
	char temp;
	string ret;
	while (a > 0) {
		temp = a % 10 + 48;
		ret += temp;
		a /= 10;
	}
	return ret;
}
string change_into_string(double a) {
	int a_i = a;
	char temp;
	string ret;
	while (a > 0) {
		temp = a_i % 10 + 48;
		ret += temp;
		a /= 10;
	}
	lli a_lli = a * 1000000000000;
	return ret + change_into_string(a_lli);
}
int main(){
	system_clock::time_point t1 = system_clock::now();
	lli video_sum = video_hash();
	double audio_sum = audio_hash();
	cout << endl;
	cout << "video hash value : "<<sha256(change_into_string(video_sum)) << endl;
	cout << "audio hash value : "<<sha256(change_into_string(audio_sum)) << endl;
	system_clock::time_point t2 = system_clock::now();
	duration<double> sec = t2 - t1;
	printf("total execution time : %lf\n", sec);
	system("pause");
	return 0;
}