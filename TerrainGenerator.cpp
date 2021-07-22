// TerrainGenerator.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "TerrainGenerator.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <SimpleImage.h>
#include <random>
#include <time.h>
#include <cstdlib>
#include <math.h>
#define IDX(x,y,w) ((x)+(y)*(w)) // x=spalte  y=zeile  w=breite des array
#define SQR(x) ((x)*(x))
default_random_engine generator; // keine Zeit daher immer fix

//globale texturen
//funktioniert im terrainGenerator nur mit 3 "../"
//-> zum testen also einmal ../ entfernen oder im ResourceGenerator starten
GEDUtils::SimpleImage tex_tief_flach("../../../../external/textures/gras15.jpg"); //c0
GEDUtils::SimpleImage tex_tief_steil("../../../../external/textures/mud02.jpg"); //c1
GEDUtils::SimpleImage tex_hoch_flach("../../../../external/textures/rock6.jpg");//c2
GEDUtils::SimpleImage tex_hoch_steil("../../../../external/textures/rock8.jpg"); //c3

//globale variable 
const int g_verhaeltnis = 2;



int _tmain(int argc, _TCHAR* argv[])
{
	
	// Überprüfung der EingabeParameter
	if ((argc != 9) || (_tcscmp(argv[1], _TEXT("-r")) != 0) || (_tcscmp(argv[3], _TEXT("-o_height")) != 0) || (_tcscmp(argv[5], _TEXT("-o_color")) != 0) || (_tcscmp(argv[7], _TEXT("-o_normal")) != 0))
	{
		cout << "ERROR - Eingabe-Parameter inkorrekt" << endl;

		system("PAUSE");
		return 0;
	}

	int resolution = _tstoi(argv[2]);
	srand(time(NULL));
	
	const wchar_t *o_height = argv[4];
	const wchar_t *o_color = argv[6];
	const wchar_t *o_normal = argv[8];

	if(resolution <= 0)
	{
		cout << "ERROR - Eingabe-Parameter inkorrekt" << endl;
		system("PAUSE");
		return 0;
	}
	
	float* map = new float[SQR(resolution + 1)];
	float* map_downsized = new float[SQR((resolution / 4))];
	Vector3* normalMap = new Vector3[SQR(resolution)];
	alphas* alphaMap = new alphas[SQR(resolution)];

	
	//map wird in diamond square neu ueberschrieben

	cout << "Erstelle heightmap" << endl;
	diamondSquare(map, resolution);

	//map wird gesmootht
	cout << "Smoothe heightmap" << endl;
	cout << "This might take a few minutes..." << endl;
	cout << "Enjoy a story meanwhile..." << endl;

	string story[] = {
		"Es ", "war ", "einmal ", "vor " , "langer " , "Zeit " , " ein Frosch " , "namens Friedrich.\n" ,
		"Er lebte " , "in einem " , "kleinen Teich " , "am Rande " , "der Stadt " , "Muenchen.\n", "Eines Tages ", "beschloss er ", "eine Reise  ",
		"zu machen. ", "Er packte ", "dafuer\n", "seine 7 ", "Sachen und ", "huepfte los. ",
		"Er wollte ", "als erstes ", "sich endlich ", "mal die\n", "technische ", "Universitaet ", "Muenchen ",
		"ansehen. ", "Sein Vetter ", "hatte ihm ", "mal erzaehlt,\n", "dass dort  ", "eine riesige ", "Rutsche ", "sei. Deshalb ", "machte er ", "sich auf "
		, "die Suche.\n", "Leider reiste ", "er zuerst ", "zum Maschinenwesen. ", "Dort gab ", "es nur ", "komische ", "Flieger. ", "Und keiner ", "davon ",
		"essbar :(\n", "Aber ein ", "Pinguin ", "gab ihm den ", "Tipp, dass ", "die Rutsche ", "nebenan sei. ", "Also ", "huepfte er ", "rueber. ",
		"Dort stellte ", "er mit ", "Schrecken ", "fest, dass ", "man in den ", "dritten Stock ", "muss! ", "Aber er ", "war ja ein ", "MeisterHuepfer!\n",
		"Als er ", "jedoch oben ", "ankam, sah ", "er, dass man ", "nur mit Matte ", "rutschen darf!! ", "Aber die ", "lagen alle unten:(\n", "Doch zu ", "seinem Glueck ",
		"gab es einen ", "Fahrstuhl!! :D\n", "Diesen benutzte ", "er dann auch! ", "Und so ", "kam es ", "zu einem ", "legendaeren ", "Rutschrekord! ", "Der bis ",
		"heute nie ", "gebrochen ", "wurde ;)\n ", "Und so ", "endet die ", "Geschichte ", "des meist ", "gerutschten Frosches ", "aller Zeiten!\n ", "ENDE\n ",
	};


	int smoothwert = 100;
	for (int i = 0; i < smoothwert; i++) { //hab auf 100 gesetzt weil es sonst zu lange lädt
		smoothArray(map, resolution, resolution);
		if (smoothwert <= 100) {
			cout << "" << story[i];
		}
		
	}


	//Erstelle die NormalMap

	cout << "Erstelle NormalMap" << endl;
	generateNormalMap(map, normalMap, resolution);


	//speichert die normalmap als .png Datei ---------------muss noch zu .tiff geändert werden
	cout << "Output NormalMap" << endl;
	outputNormalMap(normalMap, resolution, o_normal);

	//erstellen der neuen texture
	cout << "erstelle Texture" << endl;
	createColorTexture(resolution, map, normalMap, o_color);

	//downsized Heightmap
	cout << "Downsizing HeightMap" << endl;
	downsizing(map, map_downsized, resolution);


	cout << map_downsized[IDX(0, 0, resolution / 4)] << endl;


	cout << map_downsized[IDX(2, 4, resolution / 4)] << endl;
	cout << map_downsized[IDX(12, 12, resolution / 4)] << endl;
	cout << map_downsized[IDX(resolution/4-1, 0, resolution / 4)] << endl;

	cout << map_downsized[IDX(resolution / 4 - 1, resolution / 4 - 1, resolution / 4)] << endl;
	//speichert die downsized heightmap als .png Datei
	cout << "Output downsized HeightMap" << endl;
	outputHeightMap(map_downsized, resolution/4, o_height);

	cout << "Alles ausgefuehrt!" << endl;
	system("PAUSE");
    return 0;
}

//Es wird jetzt doch keine alpha map erstellt sondern die alphawerte direkt in der funktion berechnet
/*
void calcAlphas(float height, float slope, float& alpha1, float& alpha2, float& alpha3) { 

	alpha1 = (1 - height) * slope;  
	alpha2 = height;  
	alpha3 = height * slope;
} // Problem: Very smooth blending, can you improve this?

//Speichern der Alphawerte in seperater Tabelle fürs Zugreifen
void calcAlphaMap(alphas* alphaMap, float* heightMap, Vector3* normalMap, int resolution) {
	for (int y = 0; y < resolution; y++) {
		for (int x = 0; x < resolution; x++) {
			calcAlphas(heightMap[IDX(x, y, resolution)], (1 - normalMap[IDX(x, y, resolution)].z),
				(alphaMap[IDX(x, y, resolution)].alpha1), (alphaMap[IDX(x, y, resolution)].alpha2), (alphaMap[IDX(x, y, resolution)].alpha3));
		}
	}

}
*/

//berechnet color anhand von alpha mapping
//und speichert sie in col
void getColor(int x, int y, float a1, float a2, float a3, color& col) {
	
	//newColor = a3 * c3 + (1- a3) * (a2 * c2 +(1-a2) * (a1* c1 + (1- a1) * c0))
	
	float r0, r1, r2, r3, g0, g1, g2, g3, b0, b1, b2, b3;
	tex_tief_flach.getPixel((x % tex_tief_flach.getWidth()), (y % tex_tief_flach.getHeight()), r0, g0, b0);
	tex_tief_steil.getPixel((x % tex_tief_steil.getWidth()), (y % tex_tief_steil.getHeight()), r1, g1, b1);
	tex_hoch_flach.getPixel((x % tex_hoch_flach.getWidth()), (y % tex_hoch_flach.getHeight()), r2, g2, b2);
	tex_hoch_steil.getPixel((x % tex_hoch_steil.getWidth()), (y % tex_hoch_steil.getHeight()), r3, g3, b3);

	col.r = a3 * r3 + (1 - a3) * (a2 * r2 + (1 - a2) * (a1 * r1 + (1 - a1) * r0));
	col.g = a3 * g3 + (1 - a3) * (a2 * g2 + (1 - a2) * (a1 * g1 + (1 - a1) * g0));
	col.b = a3 * b3 + (1 - a3) * (a2 * b2 + (1 - a2) * (a1 * b1 + (1 - a1) * b0));


}

void createColorTexture(int resolution, float* heightMap, Vector3* normalMap, const wchar_t* o_color) {
	GEDUtils::SimpleImage newTexture(resolution, resolution);
	
	float r, g, b;

	for (int y = 0; y < newTexture.getHeight(); y++) {
		for (int x = 0; x < newTexture.getWidth(); x++) {
			
			float alpha1, alpha2, alpha3;
			float height, slope;

			height = heightMap[(IDX(x, y, resolution))];
			slope = 1 - (normalMap[IDX(x, y, resolution)].z * 2 - 1);


			alpha1 = (1 - height) * slope;  
			alpha2 = height; 
			alpha3 = height * slope;

			//schreibt farbe in col rein
			color col;
			getColor(x, y, alpha1, alpha2, alpha3, col);

			//setzt farbe auf werte in col
			newTexture.setPixel(x, y, col.r, col.g, col.b);


		}

	}

	try {
		if (!newTexture.save(o_color)) {
			throw "Could not save color Texture";
		}
	}
	catch (char* exception) {
		printf("Error: %s\n", exception);
	}
	
}


void downsizing(float* old, float* target, int w)
{
	float temp;
	for (int x = 0; x < w; x = x + 4)
	{
		for (int y = 0; y < w; y = y + 4)
		{
			temp = 0;
			for (int a = 0; a < 4; a++)
			{
				for (int b = 0; b < 4; b++)
				{
					temp += old[IDX(x + a, y + b, w)];
				}
			}
			target[IDX(x / 4, y / 4, w/4)] = (temp / 16.f);
		}
	}
}

void outputNormalMap(Vector3* map, int resolution, const wchar_t* o_height)
{
	//heightmap wird in die ein Bild geladen und dann gespeichert
	try {
		Vector3 vector;
		GEDUtils::SimpleImage normalMap(resolution, resolution);
		for (unsigned int y = 0; y<normalMap.getHeight(); y++) {
			for (unsigned int x = 0; x<normalMap.getWidth(); x++) {
				vector = map[IDX(x, y, resolution)];
				normalMap.setPixel(x, y, vector.x, vector.y, vector.z);
			}
		}

		if (!normalMap.save(o_height)) {
			throw "Could not save NormalMap";
		}
	}
	catch (char* exception) {
		printf("Error: %s\n", exception);
	}
}

void generateNormalMap(float* heightMap, Vector3* normalMap, int w)
{
	float xDiff, yDiff , vectorLength;
	float newX, nexY, newZ;
	Vector3 normal;
	for (int y = 0; y < w; y++)
	{
		for (int x = 0; x < w;x++)
		{
			if (x ==0)
				xDiff = (heightMap[IDX(x + 1, y, w)] - heightMap[IDX(x, y, w)]) *w;
			// * w damit man von höhendifferenz in pixel umrechnet
			else
				xDiff = (((heightMap[IDX(x + 1, y, w)] - heightMap[IDX(x - 1, y, w)]) / 2) * w);

			if(y==0)
				yDiff = (heightMap[IDX(x, y + 1, w)] - heightMap[IDX(x, y, w)]) *w;
			else
				yDiff = (((heightMap[IDX(x, y + 1, w)] - heightMap[IDX(x, y - 1, w)]) / 2)* w);

			vectorLength = sqrtf(SQR(xDiff) + SQR(yDiff) + 1);

			//Normalizing und positiv machen
			normal.x = ((-xDiff / vectorLength) + 1) / 2;
			normal.y = ((-yDiff / vectorLength) + 1) / 2;

			
			normal.z = ((1 / vectorLength) + 1) / 2;
			
			//cout << normal.x << " - " << normal.y << " - " << normal.z << endl;
			normalMap[IDX(x, y, w)] = normal;
		} 
	}
}

void outputHeightMap(float* map, int resolution, const wchar_t* o_height)
{
	//heightmap wird in die ein Bild geladen und dann gespeichert
	try {
		GEDUtils::SimpleImage heightMap(resolution, resolution);
		for (unsigned int y = 0; y<heightMap.getHeight(); y++) {
			for (unsigned int x = 0; x<heightMap.getWidth(); x++) {
				heightMap.setPixel(x, y, map[IDX(x, y, resolution)]);
			}
		}

		if (!heightMap.save(o_height)) {
			throw "Could not save gray image";
		}
	}
	catch (char* exception) {
		printf("Error: %s\n", exception);
	}
}


//rundet terrain etwas ab
void smoothArray(float* field, int width, int height)
{
	float* temp = new float[width*height];
	for (int i = 0; i < (width*height); i++)
		temp[i] = field[i];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float sum = 0;
			int counter = 0;
			for (int a = -1; a < 2; a++)
			{
				for (int b = -1; b < 2;b++)
				{
					if ((j + b) >= 0 && (i + a) >= 0 && (i + a) < height && (j + b) < width)
					{
						sum += temp[IDX(j + b, i + a, width)];
						counter++;
					}
				}
			}
			field[IDX(j, i, width)] = (sum / counter * 10) / 10;
		}
	}
	delete temp;

}

//Array erstellen für Diamond Square
float* newArray(int resolution) {
	//n = resolution
	float* map = new float[SQR(((resolution)+1)^2)];
	
	//Ebene soll schon schräg anfangen 
	map[(IDX(0, 0, ((resolution) + 1)))] = randomNumber();							//1. Eckpunkt	
	map[(IDX(0, (resolution), ((resolution) + 1)))] = randomNumber();				//2. Eckpunkt
	map[(IDX((resolution), 0, ((resolution) + 1)))] = randomNumber();				//3. Eckpunkt
	map[(IDX((resolution), (resolution), ((resolution) + 1)))] = randomNumber();	//4. Eckpunkt

	return map;

}

//generiert random Nummer damit man das nicht immer hinschreiben muss - nur positive werte
float randomNumber() {
	float random;
	normal_distribution<float> distribution(0.0, 1.0);
	do
	{
		random = (distribution(generator) + 1) / 2;
	
	} while ((random < 0.0f) || (random > 1.0f));
	return random;
}


//gibt auch negative zahlen aus
float randomNumberPosNeg(float verhaeltnis) {
	float random;
	normal_distribution<float> distribution(0.0, verhaeltnis);

	do
	{
		random = (distribution(generator));
		
	} while ((random < -(verhaeltnis)) || (random > verhaeltnis));
	return random;
}


//ich fueg hier mal direkt die zufallsnummern mit dazu!
//für Diamond Step
float middleValue4Z(float a, float b, float c, float d, float verhaeltnis) {

	float random = randomNumberPosNeg(verhaeltnis);
	float returnFloat = (((a + b + c + d) / 4) + random);

	if (returnFloat > 1.f) {
		returnFloat = 1.0;
	}
	if (returnFloat < 0.0) {
		returnFloat = 0.0;
	}

	return returnFloat ;
}

//für Square Step
float middleValue3Z(float a, float b, float c, float verhaeltnis) {
	float random = randomNumberPosNeg(verhaeltnis);
	float returnFloat = (((a + b +c) / 3) + random);

	if (returnFloat > 1.f) {
		returnFloat = 1.0;
	}
	if (returnFloat < 0.0) {
		returnFloat = 0.0;
	}

	return returnFloat;
}

//Diamond Step
void diamondStep(int x, int y ,int abstand,float* pointer, int w) {
	int middleX = x + abstand / 2;
	int middleY = y + abstand / 2;
	float verhaeltnis = (float)abstand / ((float)w * g_verhaeltnis);

	/*
	A--------B
	|        |
	|        |
	|        |
	C--------D
	
	
	
	*/


	float valueA = pointer[(IDX(x, y, w))];
	float valueB = pointer[(IDX((x + abstand), y, w))];
	float valueC = pointer[(IDX(x, (y + abstand), w))];
	float valueD = pointer[(IDX((x + abstand), (y + abstand), w))];

	pointer[(IDX(middleX, middleY, w))] = middleValue4Z(valueA, valueB, valueC, valueD, verhaeltnis);

}

//Abstand wird am Ende halbiert
void squareStep(int x, int y, int abstand, float* pointer, int w) {

	float verhaeltnis = (float)abstand / ((float)w * g_verhaeltnis);

	//alle Positionen oben und links(außer letzte Spalte und letzte Zeile)
	int obenX = x + abstand / 2;
	int obenY = y;
	if (y - abstand / 2 >= 0)
	{
		pointer[(IDX(obenX, obenY, w))] = middleValue4Z(pointer[(IDX(x, y, w))], pointer[(IDX((x + abstand), y, w))], 
			pointer[(IDX(obenX, y-abstand/2, w))], pointer[(IDX(obenX, y + abstand / 2, w))], verhaeltnis);
	}
	else
	{
		pointer[(IDX(obenX, obenY, w))] = middleValue3Z(pointer[(IDX(x, y, w))], pointer[(IDX((x + abstand), y, w))], 
			pointer[(IDX(obenX, y + abstand / 2, w))], verhaeltnis);
	}

	int linksX = x;
	int linksY = y + abstand / 2;
	if (x - abstand / 2 >= 0)
	{
		pointer[(IDX(linksX, linksY, w))] = middleValue4Z(pointer[(IDX(x, y, w))], pointer[(IDX((x), (y+abstand), w))], 
			pointer[(IDX((x-abstand/2), obenY, w))], pointer[(IDX((x + abstand / 2), obenY, w))], verhaeltnis);
	}
	else
	{
		pointer[(IDX(linksX, linksY, w))] = middleValue3Z(pointer[(IDX(x, y, w))], pointer[(IDX((x), (y + abstand), w))], 
			pointer[(IDX((x + abstand / 2), obenY, w))], verhaeltnis);
	}


}

void squareStep2(int i, int abstand, float* pointer, int w)
{
	// befüllen der letzten Zeile und letzten Spalte
	float verhaeltnis = (float)abstand / ((float)w * g_verhaeltnis);
	int untenX = i + abstand / 2;
	int untenY = w;
	pointer[(IDX(untenX, untenY, w))] = middleValue3Z(pointer[(IDX(i, untenY, w))], pointer[(IDX((i + abstand), untenY, w))], 
		pointer[(IDX(untenX, (i + abstand / 2), w))], verhaeltnis);


	int rechtsX = w;
	int rechtsY = i + abstand / 2;
	pointer[(IDX(rechtsX, rechtsY, w))] = middleValue3Z(pointer[(IDX(rechtsX, i, w))], pointer[(IDX(rechtsX, (i+abstand), w))], 
		pointer[(IDX((i + abstand / 2), rechtsY, w))], verhaeltnis);
}
void diamondSquare(float* pointer, int w) {
	//pointer = newArray(w);

	//Ebene soll schon schräg anfangen 
	pointer[(IDX(0, 0, ((w+1))))] = randomNumber();						//1. Eckpunkt	
	pointer[(IDX(0, (w), ((w+1))))] = randomNumber();					//2. Eckpunkt
	pointer[(IDX((w), 0, ((w+1))))] = randomNumber();					//3. Eckpunkt
	pointer[(IDX((w), (w), ((w+1))))] = randomNumber();					//4. Eckpunkt

	int abstand = w;

	while (abstand > 1) {
		for (int y = 0; y < (w); (y = y + abstand)) {
			for (int x = 0; x < (w); x = (x + abstand)) {
				diamondStep(x, y, abstand, pointer, w);
				squareStep(x, y, abstand, pointer, w); 
				// squareStep wird nur für Punkte links und oben außgeführt, sonst befüllt man manche Felder 2mal(Effizienz)
			}
		}

		/*durch step squareStep sind alle felder für die SquareSteps befüllt, außer letzte Zeile und letzte Spalte
		=> squreStep2 befüllt rest
		*/
		for (int i = 0; i < w; i = i + abstand) 
		{
			squareStep2(i, abstand, pointer, w);
		}
		abstand = abstand / 2;
	}
	
}