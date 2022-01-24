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
	mPoints.push_back(p);								// SW | SE		3 | 4

	if (mDepth <= depth)
		return;

	if (mCapacity < mPoints.size() && mDepth > depth) {
		subdivide();
		depth++;
	}

	if (mDivided) {
		for (int i = 0; i < mPoints.size(); i++) {
			if (nw->mBoundary.constains(mPoints[i])) {		// NW == 1
				QPoint3D* point = mPoints[i];
				parent = nw;
				p->SetPath(1);
				parent->insert(point, depth);
			}
			else if (ne->mBoundary.constains(mPoints[i])) {	// NE == 2
				QPoint3D* point = mPoints[i];
				parent = ne;
				p->SetPath(2);
				parent->insert(point, depth);
			}
			else if (sw->mBoundary.constains(mPoints[i])) {	// SW == 3
				QPoint3D* point = mPoints[i];
				parent = sw;
				p->SetPath(3);
				parent->insert(point, depth);
			}
			else if (se->mBoundary.constains(mPoints[i])) {	// SE == 4
				QPoint3D* point = mPoints[i];
				parent = se;
				p->SetPath(4);
				parent->insert(point, depth);
			}
		}
	}
}