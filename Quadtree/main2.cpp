#include <random>
#include <fstream>
#include <sstream>
#include "quadtree2.h"

int main() {
	//srand(time(NULL));
	std::random_device rng;
	std::uniform_real_distribution<double> range(0.0, 400.0);

	float WIDTH = 400;
	float HEIGHT = 400;
	int CAPACITY = 2;
	float MINSIZE = 200;
	int DEPTH = 5                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    ;
	
	QBox boundary(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);	// (x, y, w, h)

	//Quadtree qt(boundary, MINSIZE);
	Quadtree qt(boundary, DEPTH, CAPACITY);

	std::ifstream fin;
	fin.open("C:\\Users\\WOOKJIN\\Dropbox\\X1\\pointtest\\500.txt");

	std::vector<QPoint3D*> filePoints;
	std::string line;

	if (fin.is_open()) {
		while (!fin.eof()) {
			float x, y, z;
			QPoint3D* coordinate = new QPoint3D;
			getline(fin, line);
			std::istringstream iss(line);
			iss >> x >> y >> z;
			coordinate->SetXYZ(x, y, z);
			filePoints.push_back(coordinate);
		}
	}
	fin.close();

	//for (int i = 0; i < filePoints.size(); i++) {
	//	std::cout << filePoints[i]->GetX() << " " << filePoints[i]->GetY() << " " << filePoints[i]->GetZ() << std::endl;
	//}

	for (int i = 0; i < filePoints.size(); i++) {
		int depth = 0;
		//std::cout << "Point : " << filePoints[i]->GetX() << ", " << filePoints[i]->GetY() << std::endl;
		qt.insert(filePoints[i], depth);
	}

	for (int i = 0; i < filePoints.size(); i++) {
		std::cout << filePoints[i]->GetX() << "\t" << filePoints[i]->GetY() << "\t" << filePoints[i]->GetZ();
		std::cout << "\t| Path : ";
		std::cout << filePoints[i]->GetStringPath();
		std::cout << "\t| End Node XY : " << filePoints[i]->GetEndNodeXY().GetX() << ", " << filePoints[i]->GetEndNodeXY().GetY() << std::endl;
	}
}