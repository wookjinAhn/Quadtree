#include <random>
#include "quadtree2.h"

int main() {
	//srand(time(NULL));
	std::random_device rng;
	std::uniform_real_distribution<double> range(0.0, 400.0);

	float WIDTH = 400;
	float HEIGHT = 400;
	int CAPACITY = 4;
	float MINSIZE = 200;
	int DEPTH = 2;
	
	QBox boundary(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);	// (x, y, w, h)

	//Quadtree qt(boundary, MINSIZE);
	Quadtree qt(boundary, DEPTH, CAPACITY);
	std::cout << "depth : " << qt.GetDepth() << std::endl;

	for (int i = 0; i < 10; i++) {
		//float x = range(rng);
		//float y = range(rng);
		//Point p(x, y);
		//std::cout << "point input | x : " << x << ", y : " << y << ", z : " << z << std::endl;
		float x = rand() % (int)WIDTH;
		float y = rand() % (int)HEIGHT;
		float z = rand() % 400;
		std::cout << "point input | x : " << x << ", y : " << y << ", z : " << z << std::endl;
		QPoint3D point(x, y, z);
		QPoint3D* p = &point;

		int depth = 0;
		qt.insert(p, depth);

		std::cout << "Point Path : ";
		std::vector<int> temp = p->GetPath();
		for (int i = 0; i < temp.size(); i++) {
			std::cout << temp[i] << " ";
		}
		std::cout << std::endl;
	}
}