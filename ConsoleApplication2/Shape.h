enum ShapeType {
	Cir, Squr, Line
};

class Point {
public:
	int x;
	int y;
	Point() {};
	Point(int x, int y);
	~Point() {};
};

class Shape {
public:
	ShapeType type;
	virtual bool In(int x, int y) = 0;
	virtual void draw() = 0;
	virtual void drawBoard() = 0;
	virtual void size(int dx, int dy) = 0;
	virtual void move(int dx, int dy) = 0;
	virtual void setStyle(int dx, int dy, int coner) = 0;
	virtual bool isEdit(int x, int y, int* coner) = 0;
	virtual ~Shape() {};
};

class CirShape :public Shape {
public:
	Point ori;
	float r;
	CirShape() {};
	CirShape(int x, int y, float r);
	bool In(int x, int y) override;
	void draw() override;
	void drawBoard() override;
	void size(int dx, int dy) override;
	void move(int dx, int dy) override;
	void setStyle(int dx, int dy, int coner) override;
	bool isEdit(int x, int y, int* coner) override;
};

class SqurShape :public Shape {
public:
	Point lb;
	int width;
	int height;
	SqurShape() {};
	SqurShape(int x, int y, int width, int height);
	bool In(int x, int y) override;
	void draw() override;
	void drawBoard() override;
	void size(int dx, int dy) override;
	void move(int dx, int dy) override;
	void setStyle(int dx, int dy, int coner) override;
	bool isEdit(int x, int y, int* coner) override;
};

class LineShape :public Shape {
public:
	Point p1;
	Point p2;
	LineShape() {};
	LineShape(int x, int y, int x1, int y1);
	bool In(int x, int y) override;
	void draw() override;
	void drawBoard() override;
	void size(int dx, int dy) override;
	void move(int dx, int dy) override;
	void setStyle(int dx, int dy, int coner) override;
	bool isEdit(int x, int y, int* coner) override;
};