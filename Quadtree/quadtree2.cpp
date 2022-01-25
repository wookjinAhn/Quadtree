#include "quadtree2.h"

void Quadtree::subdivide() {
	float x = parent->mBoundary.GetX();
	float y = parent->mBoundary.GetY();
	float w = parent->mBoundary.GetW();
	float h = parent->mBoundary.GetH();

	QBox b_nw(x - w / 2, y + h / 2, w / 2, h / 2);
	QBox b_ne(x + w / 2, y + h / 2, w / 2, h / 2);
	QBox b_sw(x - w / 2, y - h / 2, w / 2, h / 2);
	QBox b_se(x + w / 2, y - h / 2, w / 2, h / 2);

	nw = new Quadtree(b_nw, mDepth, mCapacity);
	ne = new Quadtree(b_ne, mDepth, mCapacity);
	sw = new Quadtree(b_sw, mDepth, mCapacity);
	se = new Quadtree(b_se, mDepth, mCapacity);
	
	mDivided = true;
}

void Quadtree::insert(QPoint3D* p, int depth) {		// NW | NE		1 | 2 
	parent = this;										// ---+---	   ---+---
	mPoints.push(p);								// SW | SE		3 | 4
	std::cout << "insert ! " << std::endl;
	std::cout << "boundary : " << parent->GetBoundary().GetX() << ", " << parent->GetBoundary().GetY() << std::endl;

	if (mDepth <= depth)
		return;

	if (mCapacity < mPoints.size() && mDepth > depth) {
		subdivide();
	}

	if (mDivided) {
		std::cout << "mDivided true" << std::endl;   
		while(!mPoints.empty()) {
			QPoint3D* point = mPoints.front();
			mPoints.pop();
			std::cout << "point : " << point->GetX() << ", " << point->GetY() << ", " << point->GetZ() << std::endl;
			if (nw->mBoundary.constains(point)) {		// NW == 1
				parent = nw;
				point->SetStringPath("1");
				depth++;
				parent->insert(point, depth);
			}
			else if (ne->mBoundary.constains(point)) {	// NE == 2
				parent = ne;
				point->SetStringPath("2");
				depth++;
				parent->insert(point, depth);
			}
			else if (sw->mBoundary.constains(point)) {	// SW == 3
				parent = sw;
				point->SetStringPath("3");
				depth++;
				parent->insert(point, depth);
			}
			else if (se->mBoundary.constains(point)) {	// SE == 4
				parent = se;
				point->SetStringPath("4");
				depth++;
				parent->insert(point, depth);
			}
		}
	}
}