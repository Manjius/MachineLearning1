#pragma once
#include <iostream>
#include <chrono>
#include <ctime>  
#include <windows.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;

void readImages(vector<vector<float>> &X, vector<float> &y, int sizeimage);
vector<vector<float>> oneVsAll(vector<vector<float>> X, vector<float> y, int num_labels, float lambda);

vector<float> filtery(vector<float> y, int x);

float sigmoid(float z);

void costFunctionReg(vector<float> theta, vector<vector<float>> X, vector<float> y, float lambda, float &J, vector<float> &grad, int iterations = 1);

float predictOneVsAll(vector<vector<float>> all_theta, vector<vector<float>> X, vector<float> y);

void neuralNetwork();


void testNewPictureMany(vector<vector<float>> all_theta, vector<float> y, int imagesize);
void testNewPictureManual(vector<vector<float>> all_theta, vector<float> y, int imagesize);
vector<float> testNewPicture(int imagesize, std::string number);


int test();