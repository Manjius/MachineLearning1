#include "functions.h"


using namespace cv;
using namespace std;

void neuralNetwork()
{
	/* Machine Learning Online Class - Exercise 3 | Part 1: One - vs - all

		%  Instructions
		%  ------------
		%
		%  This file contains code that helps you get started on the
		%  linear exercise.You will need to complete the following functions
		%  in this exericse:
		%
		%     lrCostFunction.m(logistic regression cost function)
		%	  oneVsAll.m
		%     predictOneVsAll.m
		%     predict.m
		%
		%  For this exercise, you will not need to change any code in this file,
		% or any other files other than those mentioned above.
		%
		%% Initialization
		clear; close all; clc

		%% Setup the parameters you will use for this part of the exercise
		input_layer_size = 400; % 20x20 Input Images of Digits

		num_labels = 10; % 10 labels, from 1 to 10
		% (note that we have mapped "0" to label 10)

		% % == == == == == = Part 1: Loading and Visualizing Data == == == == == == =
		%  We start the exercise by first loading and visualizing the dataset.
		%  You will be working with a dataset that contains handwritten digits.
		%

		% Load Training Data*/
		

		//load('ex3data1.mat'); % training data stored in arrays X, y
		cout << "Loading Data ...\n";

		vector<vector<float>> X(100); //100 rows (images)
		vector<float> y;
		int size = 30;//size of rescaled image size*size

		readImages(X, y, size);
		//amount of training samples in dataset
		cout << "Loading Data ended ...\n";
		int m = X.size();//.size(X, 1);


		cout << "Program paused. Press enter to continue.\n";
		cin.get();

	/*
	%% == == == == == == Part 2a: Vectorize Logistic Regression == == == == == ==
	%% == == == == == == Part 2b: One - vs - All Training == == == == == ==
	*/
	cout << "\nTraining One-vs-All Logistic Regression...\n";

	float lambda = 0.1;
	vector<vector<float>> all_theta;
	all_theta = oneVsAll(X, y, 2, lambda);

	cout << "Program paused. Press enter to continue.\n";
	cin.get();


//	%% == == == == == == == == Part 3: Predict for One - Vs - All == == == == == == == ==
	float accuracy=0;
	cout << "\nTraining Set Accuracy: ";
	accuracy = predictOneVsAll(all_theta, X, y);
	cout << accuracy;
	//test with new ones

	cin.get();

	cout << "\nTest Set Accuracy: ";
	testNewPictureMany(all_theta, y, size);
	do {
		testNewPictureManual(all_theta, y, size);
	} while (true);

	cin.get();
	//testNewFlowers();


}