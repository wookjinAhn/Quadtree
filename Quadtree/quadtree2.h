#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

class QPoint2D {
private:
	float mX, mY;

public:
	QPoint2D() : mX(0), mY(0) {}
	QPoint2D(float x, float y) : mX(x), mY(y) {}

	float GetX() const { return mX; }
	float GetY() const { return mY; }

	void SetX(float x) { this->mX = x; }
	void SetY(float y) { this->mY = y; }
};

struct QPoint3D {	// 
private:
	float mX, mY, mZ;
	QPoint2D mEndNodeXY;
	std::vector<int> path;	
	std::string mStringPath;

public:
	QPoint3D() : mX(0), mY(0), mZ(0) {}
	QPoint3D(float x, float y, float z) : mX(x), mY(y), mZ(z) {}

	float GetX() const { return mX; }
	float GetY() const { return mY; }
	float GetZ() const { return mZ; }
	std::vector<int> GetPath() const { return path; }
	std::string GetStringPath() const { return mStringPath; }
	QPoint2D GetEndNodeXY() const { return mEndNodeXY; }

	void SetPath(int path) { this->path.push_back(path); }
	void SetStringPath(std::string path) { this->mStringPath.append(path); }
	void SetEndNodeXY(QPoint2D endNodeXY) { this->mEndNodeXY = endNodeXY; }
	void SetEndNodeXY(float x, float y) { this->mEndNodeXY.SetX(x); this->mEndNodeXY.SetY(y); }
	void SetXYZ(float x, float y, float z) { this->mX = x; this->mY = y; this->mZ = z; }
};

class QBox {
private:
	float mX, mY, mW, mH;

public:
	QBox() : mX(0), mY(0), mW(0), mH(0) {}
	QBox(float x, float y, float w, float h) : mX(x), mY(y), mW(w), mH(h) {}

	float GetX() const { return mX; }
	float GetY() const { return mY; }
	float GetW() const { return mW; }
	float GetH() const { return mH; }

	bool constains(QPoint3D* p) {
		return (p->GetX() >= mX - mW && p->GetX() < mX + mW
			&& p->GetY() >= mY - mH && p->GetY() < mY + mH);
	}
};

class Quadtree {	// boudnary, cap, 
private:
	QBox mBoundary;
	int mCapacity = 0;
	float mMinsize = 0;
	int mDepth = 0;
	int check = 0;
	bool mDivided = false;

	Quadtree* parent = this;
	Quadtree* nw = nullptr;
	Quadtree* ne = nullptr;
	Quadtree* sw = nullptr;
	Quadtree* se = nullptr;

	std::queue<QPoint3D*> mPoints;	// not use yet

public:
	//Quadtree(Box _boundary, int _cap) : boundary(_boundary), cap(_cap) {}
	Quadtree(QBox boundary, float minsize) : mBoundary(boundary), mMinsize(minsize) {}
	Quadtree(QBox boundary, int depth) : mBoundary(boundary), mDepth(depth) {}
	Quadtree(QBox boundary, int depth, int capacity) : mBoundary(boundary), mDepth(depth), mCapacity(capacity) {}

	QBox GetBoundary() const { return mBoundary; }
	float GetMin() const { return mMinsize; }
	int GetDepth() const { return mDepth; }

	void SetMin(float minsize) { this->mMinsize = minsize; }
	void SetDepth(int depth) { this->mDepth = depth; }

	void subdivide();
	void insert(QPoint3D* p, int depth);
};