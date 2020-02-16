//Uncomment the following line if you are compiling this code in Visual Studio
#include "functions.h"


using namespace cv;
using namespace std;


void testNewPictureMany(vector<vector<float>> all_theta, vector<float> y, int imagesize)
{
	std::string number;
	int testsetsize = 60;
	vector<vector<float>> X;

	std::string filenumber[60];

	for (int i = 0; i < (testsetsize / 2); i++)//yellow roses
	{	
		filenumber[i] = "00" + std::to_string(i + 51);
	}
	for (int i = 0; i < (testsetsize / 2); i++)//purple roses
	{
		filenumber[i+30] = "0" + std::to_string(i + 290);
	}
	for (int i = 0; i < testsetsize ; i++)
	{
		X.push_back(testNewPicture(imagesize, filenumber[i]));
	}


	predictOneVsAll(all_theta, X, y);

}

void testNewPictureManual(vector<vector<float>> all_theta, vector<float> y, int imagesize)
{
	std::string number;
	vector<vector<float>> newX;
	vector<vector<float>> X;

	int largerscale = 5;
	Mat image(imagesize*largerscale, imagesize*largerscale, CV_8UC3);
	


	cout << "introduce number of image to test: always 4 numbers( ex:0002)" << endl;
	cin >> number;

	newX.push_back(testNewPicture(imagesize, number));
	if (newX[0].size() == 0)//escapes if number is invalid
	{
		return;
	}
	X = newX;

	for (int k = 0; k < (imagesize*largerscale); k = k + (1* largerscale))
	{

		for (int j = 0; j < (imagesize * 3 * largerscale); j = j + (3* largerscale))//x3 for rgb
		{

			image.at<uchar>(k, j + 2) = newX[0].back(); //.begin();// .front();
			newX[0].pop_back();
			//newX[0].erase(newX[0].begin());
			image.at<uchar>(k, j + 1) = newX[0].back(); //.begin();// .front();
			newX[0].pop_back();
			//newX[0].erase(newX[0].begin());
			image.at<uchar>(k, j ) = newX[0].back();
			//newX[0].erase(newX[0].begin());
			newX[0].pop_back();
		}
	}
	imshow("picked sample", image); // Show our image inside the created window.

	waitKey(0); // Wait for any keystroke in the window

	destroyWindow("picked sample"); //destroy the created window


//	predictOneVsAll(all_theta, X, y);

}

vector<float> testNewPicture( int imagesize, std::string number)
{
	std::string filename;
	Mat image;
	int width;
	int height;
	int w;
	int h;
	vector<float> X;
	vector<vector<float>> newX;


	filename = "D:\\downloads\\17flowers\\jpg\\image_" + number + ".jpg";



	// Read the image file
	image = imread(filename);

	//size of the reescaled images so the algorithm is faster
	int newsize = imagesize;//same as training set
	// Check for failure
	if (image.empty())
	{
		cout << "Could not open or find the image" << filename << endl;
		cin.get();
		return X;
	}
	else
	{
		width = image.cols;
		height = image.rows;

		w = width / newsize;
		h = height / newsize;


		//add X(0) which is always 1
		X.push_back(1);

		for (int k = 0; k < newsize; k++)
		{
			for (int j = 0; j < (newsize * 3); j++)//x3 for rgb
			{
				//get all  features

				X.push_back((float)image.at<uchar>((k*h), (j*w)));

			}
		}

	}
	return X;
}

void readImages(vector<vector<float>> &X,vector<float> &y, int sizeimage)
{
	std::string filename[100];
	Mat image;
	int width;
	int height;
	int w;
	int h;
	int trainingsetsize = 100;

	for (int i = 0; i < (trainingsetsize/2); i++)//yellow roses
	{
		//cout << "debug" << i;
		if (i < 9) 
		{	
			filename[i] = "D:\\downloads\\17flowers\\jpg\\image_000" + std::to_string(i + 1) + ".jpg";
		}
		else
		{
			filename[i] = "D:\\downloads\\17flowers\\jpg\\image_00" + std::to_string(i + 1) + ".jpg";
		}
	}
	for (int i = 50; i < (trainingsetsize); i++)//white roses
	{
		//cout << "debug" << i;
		if (i < 10)
		{
			filename[i] = "D:\\downloads\\17flowers\\jpg\\image_00" + std::to_string(i + 190) + ".jpg";
		}
		else
		{
			filename[i] = "D:\\downloads\\17flowers\\jpg\\image_0" + std::to_string(i + 190) + ".jpg";
		}
	}

	
	for (int i = 0; i < trainingsetsize; i++)
	{

		// Read the image file
		image = imread(filename[i]);

		//size of the reescaled images so the algorithm is faster
		int newsize = sizeimage;
		// Check for failure
		if (image.empty())
		{
			cout << "Could not open or find the image" << filename[i] << endl;
			cin.get();
		}
		else
		{
			width = image.cols;
			height = image.rows;

			w = width / newsize;
			h = height / newsize;


			//add X(0) which is always 1
			X[i].push_back(1);
			//add y=1 for the first half
			if (i < trainingsetsize / 2)
			{
				y.push_back(1);
			}
			else //add y=1 for the first half
			{
				y.push_back(2);
			}

			for (int k = 0; k < newsize; k++)
			{

				for (int j = 0; j < (newsize * 3); j = j + 3)//x3 for rgb
				{
					X[i].push_back((float)image.at<uchar>((k*h), (j*w)));
					X[i].push_back((float)image.at<uchar>((k*h), (j*w) + 1));
					X[i].push_back((float)image.at<uchar>((k*h), (j*w) + 2));
				/*	if (i < 50)
					{
						X[i].push_back(10*j);
					}
					else
					{
						X[i].push_back(10*(2-j));
					}
					*/
				}
			}
			/*
			for (int z = 0; z < (X[i].size()); z++)
			{
				cout << X[i][z] << ";";
			}
			cout << "endlol\n";
			*/
		}
	}


};

vector<vector<float>> oneVsAll(vector<vector<float>> X, vector<float> y, int num_labels, float lambda)
{
	/*function[all_theta] = oneVsAll(X, y, num_labels, lambda)
		% ONEVSALL trains multiple logistic regression classifiers and returns all
		%the classifiers in a matrix all_theta, where the i - th row of all_theta
		%corresponds to the classifier for label i
		%[all_theta] = ONEVSALL(X, y, num_labels, lambda) trains num_labels
		%   logistic regression classifiers and returns each of these classifiers
		%   in a matrix all_theta, where the i - th row of all_theta corresponds
		%   to the classifier for label i
		% Some useful variables*/

	int m = X.size();// size(X, 1);
	int n = X[0].size();//  size(X, 2);


	vector<float> initial_theta(n, 1);

	//% You need to return the following variables correctly
	//matrix of num_labels * n
	vector<vector<float>> all_theta(num_labels);//zeros(num_labels, n + 1);
	float J = 0;

	for (int i = 0; i < num_labels; i++)
	{
		vector<float> newY = filtery(y, i + 1);//gets the y for classificator[num_label]
		costFunctionReg(initial_theta, X, newY, lambda, J, all_theta[i], 3);
	}

	std::cout << "thetas " << " : ";
	for (int j = 0; j < num_labels; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			std::cout << all_theta[j][i] << ";";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	cin.get();
	return all_theta;
}

vector<float> filtery(vector<float> y,int x)
{
	int s = y.size();
	vector<float> newY;
	for (int i = 0; i < s; i++)
	{
		if (y[i] == x)
		{
			newY.push_back(1);
		}
		else
		{
			newY.push_back(0);
		}
	}
	return newY;
}

//sigmoid for scalar
float sigmoid(float z)
{
	//% SIGMOID Compute sigmoid function
		//% You need to return the following variables correctly
	float g = 0;// = zeros(size(z));

	g = 1 / (1 + exp(-z));

	return g;
}

float predictOneVsAll(vector<vector<float>> all_theta, vector<vector<float>> X, vector<float> y)
{
	int num_categories = all_theta.size();
	int num_features = all_theta[0].size();
	int num_samples = X.size();
	int lambda = 10;

	float J = 0;
	float aux = 0;
	float accuracy = 0;

	vector<vector<float>> result(num_categories);

/*
	A = zeros(m, num_labels);
	for c = 1:num_labels
		theta = all_theta(c, :);
	A(:, c) = X*theta';
		endfor

		[z, p] = max(A, [], 2);
*/
	
	for (int n = 0; n < num_categories; n++)
	{
		for (int i = 0; i < num_samples; i++)
		{
			for (int ti = 0; ti < num_features; ti++)
			{
				aux = aux + (X[i][ti] * all_theta[n][ti]);
				//std::cout << X[ti][i] << " ; " << theta[ti] << "; ";
			}
			
			result[n].push_back(aux);

			J = 0;
			aux = 0;
		}
	}


	for (int i = 0; i < num_samples; i++)
	{

		cout << result[0][i] << "\n";

		cout << result[1][i] << "\n";
		if (result[0][i] >= result[1][i])
		{
			cout << "classifier number 0 cost bigger than 1: " << "num sample: " << i << "\n";
			if (i > (num_samples/2))
			{
				accuracy++;
			}
		}
		else
		{
			cout << "classifier number 1 cost bigger than 0: " << "num sample: " << i << "\n";
			if (i <= (num_samples / 2))
			{
				accuracy++;
			}
		}
	}

	accuracy =  ((accuracy / num_samples) * 100);

	cout << "acuracy of training dataset = " << accuracy << "%  \n";
	
	return 1;
}

void costFunctionReg(vector<float> theta, vector<vector<float>> X, vector<float> y, float lambda, float &J, vector<float> &grad, int iterations )
{
	/*int m = y.size();// length(y); % number of training examples
	int thetasize = theta.size();
	//% You need to return the following variables correctly
	J = 0;	% Initialize some useful values*/
	int m = y.size();// length(y); % number of training examples
	int thetasize = theta.size();
	//% You need to return the following variables correctly
	J = 0;
	vector<float> grad2(theta.size(), 0.0);// = zeros(size(theta));
	grad = grad2;
	/*% == == == == == == == == == == == YOUR CODE HERE == == == == == == == == == == ==
	% Instructions: Compute the cost of a particular choice of theta.
	%               You should set J to the cost.
	%               Compute the partial derivatives and set grad to the partial
	%               derivatives of the cost w.r.t.each parameter in theta
	%
	% Note : grad should have the same dimensions as theta
	%*/

	float aux = 0;
	if (theta.size() != X[0].size() || y.size() != X.size())
	{
		std::cout << "size mismatch error uhu" << "theta.size != X.size()" << theta.size() << ";;" << X.size() << "y.size() != X[0].size()" << y.size() << ";;" << X[0].size() << std::endl;
		//return 0;
	}
	else
	{
		
		//calculate gradients

		for (int k = 0; k < iterations; k++)
		{
			aux = 0;

			std::cout << "iteration \n";
			for (int j = 0; j < thetasize; j++)
			{
				//if ((j % 100) == 0)
					//std::cout << " grad theta " << j << ";" << "\n";
				for (int i = 0; i < m; i++)
				{
					for (int ti = 0; ti < thetasize; ti++)
					{
						aux = aux + (X[i][ti] * theta[ti]);
					}
					grad[j] = grad[j] + ((sigmoid(aux) - y[i]) * X[i][j]);
					aux = 0;
				}

				//std::cout << "thetas: ";

				grad[j] = grad[j] / m;

				//std::cout << grad[j] << ";";

				if (j > 0)
				{
					grad[j] = grad[j] + (lambda / m)*theta[j];
				}
			}

			//std::cout << "\n";
			theta = grad;
		}

		//std::cout << "X :";

		for (int i = 0; i < m; i++)
		{
			for (int ti = 0; ti < thetasize; ti++)
			{
				//std::cout << X[i][ti] << ";";
			}
		}
	}

}


int test()
{
	// Read the image file
	Mat image = imread("D:\\downloads\\17flowers\\jpg\\image_0001.jpg");

	// Check for failure
	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		cin.get();

		cin.get(); //wait for any key press
		return -1;
	}

	String windowName = "Yeehaw"; //Name of the window
	String windowName2 = "Yeehaw2"; //Name of the window

	namedWindow(windowName); // Create a window

	Mat result8u;
	image.convertTo(result8u, CV_8UC3);

	cout << result8u.size();
	
	int size = 60;


//	uint8_t *myData = result8u.data;
	int width = result8u.cols;
	int height = result8u.rows;
	int _stride = result8u.step;//in case cols != strides


	cout << width << ";" << height << " ;" << _stride << ";\n";

	Mat test(size, size, CV_8UC3);

	int w = width / size;
	int h = height / size;

	cout << w << ";" << h << "  ";

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < (size *3); j=j+3)
		{

			test.at<uchar>(i, j) = result8u.at<uchar>((i*h), (j*w));
			test.at<uchar>(i, j+1) = result8u.at<uchar>((i*h), (j*w)+1);
			test.at<uchar>(i, j+2) = result8u.at<uchar>((i*h), (j*w)+2);
			//test.at<uint8_t>(i, j) = result8u.at<uint8_t>((i*h), (j*w*4)); // 4 BECAUSE OF RGB + ALPHA
			//do whatever you want with your value
		}
	}


	imshow(windowName, result8u); // Show our image inside the created window.


	imshow(windowName2, test); // Show our image inside the created window.
	
	waitKey(0); // Wait for any keystroke in the window

	destroyWindow(windowName); //destroy the created window


	waitKey(0); // Wait for any keystroke in the window

	destroyWindow(windowName); //destroy the created window

	return 0;
}