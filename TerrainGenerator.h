#pragma once

using namespace std;


void smoothArray(float*, int, int);
float*  newArray(int);
float randomNumberPosNeg(float);
float randomNumber();
float middleValue4Z(float, float, float, float, float);
float middleValue3Z(float, float, float, float);
void diamondStep(int, int, int, float*, int);
void squareStep(int, int, int, float*, int);
void squareStep2(int, int, float*, int);
void diamondSquare(float*, int);

struct alphas {
	float alpha1 = 0.f;
	float alpha2 = 0.f;
	float alpha3 = 0.f;
};


struct color {
	float r = 0.f;
	float g = 0.f;
	float b = 0.f;
};

struct Vector3 { float x, y, z; };


//void calcAlphas(float, float, float&, float&, float&);
//void calcAlphaMap(alphas*, float*, Vector3*, int);
//bool loadImage(GEDUtils::SimpleImage&, const char*);
void getColor(int, int, float, float, float, color&);
void createColorTexture(int, float*, Vector3*, const wchar_t*);
void createGreyImage(float*, Vector3, alphas, int);

void generateNormalMap(float*, Vector3*, int);

void outputHeightMap(float*, int, const wchar_t*);
void outputNormalMap(Vector3*, int, const wchar_t*);

void downsizing(float*, float*, int);
//array erstellen

//random number

//mittelpunkt berechnen