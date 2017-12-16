#include "stdafx.h"
#include "Shape.h"

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

CirShape::CirShape(int x, int y, float r) :ori(x, y) {
	this->type = Cir;
	this->r = r;
}

void CirShape::draw() {
	if (r == 0)
		return;

	int x = 0, y = 0;
	int cx = ori.x, cy = ori.y;

	float f;
	y = r;
	f = 1.25f - r;
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POINTS);
	while (x <= y) {
		glVertex2i(x + cx, y + cy);
		glVertex2i(x + cx, cy - y);
		glVertex2i(cx - x, y + cy);
		glVertex2i(cx - x, cy - y);
		glVertex2i(y + cx, x + cy);
		glVertex2i(cx - y, x + cy);
		glVertex2i(y + cx, cy - x);
		glVertex2i(cx - y, cy - x);
		if (f < 0)
			f += 2.0f*x + 3.0f;
		else {
			f += 2.0f*(x - y) + 1.0f;
			y--;
		}
		x++;
	}
	glEnd();
}

void CirShape::drawBoard() {
	glColor3f(0, 0, 0);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_QUADS);
	glVertex2f(ori.x - r, ori.y + r);
	glVertex2f(ori.x - r, ori.y - r);
	glVertex2f(ori.x + r, ori.y - r);
	glVertex2f(ori.x + r, ori.y + r);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(ori.x - r, ori.y + r);
	glVertex2f(ori.x - r, ori.y - r);
	glVertex2f(ori.x + r, ori.y - r);
	glVertex2f(ori.x + r, ori.y + r);
	glEnd();
	glPointSize(1);
}

bool CirShape::In(int x, int y) {
	if ((x - ori.x)*(x - ori.x) + (y - ori.y)*(y - ori.y) <= r * r)
		return true;
	return false;
}

void CirShape::size(int dx, int dy) {
	r = sqrt(dx*dx + dy * dy);
}

void CirShape::move(int dx, int dy) {
	ori.x += dx;
	ori.y -= dy;
}

void CirShape::setStyle(int dx, int dy, int coner) {
	int Diff;
	float diff;

	switch (coner) {
	case 0:
		if (dx*dy >= 0) {
			Diff = abs(dx) < abs(dy) ? dx : dy;
			diff = Diff / 2;
			r -= diff;
			ori.x += diff;
			ori.y -= diff;
		}
		break;
	case 1:
		if (dx*dy <= 0) {
			Diff = abs(dx) < abs(dy) ? abs(dx) : abs(dy);
			if (dx <= 0 && dy >= 0)
				Diff = -Diff;
			diff = Diff / 2;
			r -= diff;
			ori.x += diff;
			ori.y += diff;
		}
		break;
	case 2:
		if (dx*dy >= 0) {
			Diff = abs(dx) < abs(dy) ? dx : dy;
			diff = Diff / 2;
			r += diff;
			ori.x += diff;
			ori.y -= diff;
		}
		break;
	case 3:
		if (dx*dy <= 0) {
			Diff = abs(dx) < abs(dy) ? abs(dx) : abs(dy);
			if (dx <= 0 && dy >= 0)
				Diff = -Diff;
			diff = Diff / 2;
			r += diff;
			ori.x += diff;
			ori.y += diff;
		}
		break;
	default:
		break;
	}
}

bool CirShape::isEdit(int x, int y, int* coner) {
	int s = 10;

	float tx = ori.x - r;
	float ty = ori.y + r;
	if (x >= tx - s && x <= tx + s && y >= ty - s && y <= ty + s) {
		*coner = 0;
		return true;
	}

	tx = ori.x - r;
	ty = ori.y - r;
	if (x >= tx - s && x <= tx + s && y >= ty - s && y <= ty + s) {
		*coner = 1;
		return true;
	}

	tx = ori.x + r;
	ty = ori.y - r;
	if (x >= tx - s && x <= tx + s && y >= ty - s && y <= ty + s) {
		*coner = 2;
		return true;
	}

	tx = ori.x + r;
	ty = ori.y + r;
	if (x >= tx - s && x <= tx + s && y >= ty - s && y <= ty + s) {
		*coner = 3;
		return true;
	}

	return false;
}

SqurShape::SqurShape(int x, int y, int width, int height) : lb(x, y) {
	this->type = Squr;
	this->width = width;
	this->height = height;
}

void SqurShape::draw() {
	if (width == 0 || height == 0)
		return;

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2i(lb.x, lb.y);
	glVertex2i(lb.x, lb.y - height);
	glVertex2i(lb.x + width, lb.y - height);
	glVertex2i(lb.x + width, lb.y);
	glEnd();
}

void SqurShape::drawBoard() {
	glColor3f(0, 0, 0);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_QUADS);
	glVertex2i(lb.x, lb.y);
	glVertex2i(lb.x, lb.y - height);
	glVertex2i(lb.x + width, lb.y - height);
	glVertex2i(lb.x + width, lb.y);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2i(lb.x, lb.y);
	glVertex2i(lb.x, lb.y - height);
	glVertex2i(lb.x + width, lb.y - height);
	glVertex2i(lb.x + width, lb.y);
	glEnd();
	glPointSize(1);
}

void SqurShape::size(int dx, int dy) {
	width = dx;
	height = dy;
}

void SqurShape::move(int dx, int dy) {
	lb.x += dx;
	lb.y -= dy;
}

void SqurShape::setStyle(int dx, int dy, int coner) {
	switch (coner) {
	case 0:
		lb.x += dx;
		lb.y -= dy;
		width -= dx;
		height -= dy;
		break;
	case 1:
		lb.x += dx;
		width -= dx;
		height += dy;
		break;
	case 2:
		width += dx;
		height += dy;
		break;
	case 3:
		lb.y -= dy;
		width += dx;
		height -= dy;
		break;
	default:
		break;
	}
}

bool SqurShape::isEdit(int x, int y, int* coner) {
	int s = 10;

	int tx = lb.x;
	int ty = lb.y;
	if (x >= tx - s && x <= tx + s && y >= ty - s && y <= ty + s) {
		*coner = 0;
		return true;
	}

	tx = lb.x;
	ty = lb.y - height;
	if (x >= tx - s && x <= tx + s && y >= ty - s && y <= ty + s) {
		*coner = 1;
		return true;
	}

	tx = lb.x + width;
	ty = lb.y - height;
	if (x >= tx - s && x <= tx + s && y >= ty - s && y <= ty + s) {
		*coner = 2;
		return true;
	}

	tx = lb.x + width;
	ty = lb.y;
	if (x >= tx - s && x <= tx + s && y >= ty - s && y <= ty + s) {
		*coner = 3;
		return true;
	}

	return false;
}

bool SqurShape::In(int x, int y) {
	if (x >= lb.x&&x <= lb.x + width && y >= lb.y - height && y <= lb.y)
		return true;
	return false;
}

LineShape::LineShape(int x, int y, int x1, int y1) : p1(x, y), p2(x1, y1) {
	this->type = Line;
}

void LineShape::draw() {
	if (p1.x == p2.x&&p1.y == p2.y)
		return;

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p2.y);
	glEnd();
}

void LineShape::drawBoard() {
	glColor3f(0, 0, 0);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p2.y);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p2.y);
	glEnd();
	glPointSize(1);
}

void LineShape::size(int dx, int dy) {
	p2.x = p1.x + dx;
	p2.y = p1.y - dy;
}

void LineShape::move(int dx, int dy) {
	p1.x += dx;
	p1.y -= dy;
	p2.x += dx;
	p2.y -= dy;
}

void LineShape::setStyle(int dx, int dy, int coner) {
	switch (coner) {
	case 0:
		p1.x += dx;
		p1.y -= dy;
		break;
	case 1:
		p2.x += dx;
		p2.y -= dy;
		break;
	default:
		break;
	}
}

bool LineShape::isEdit(int x, int y, int* coner) {
	int s = 10;

	int tx = p1.x;
	int ty = p1.y;
	if (x >= tx - s && x <= tx + s && y >= ty - s && y <= ty + s) {
		*coner = 0;
		return true;
	}

	tx = p2.x;
	ty = p2.y;
	if (x >= tx - s && x <= tx + s && y >= ty - s && y <= ty + s) {
		*coner = 1;
		return true;
	}

	return false;
}

bool LineShape::In(int x, int y) {
	if (p1.x == p2.x&&p1.y == p2.y)
		return false;

	int min = p1.x < p2.x ? p1.x : p2.x;
	int max = p1.x < p2.x ? p2.x : p1.x;

	if (x<min || x>max)
		return false;
	else {
		int a = p2.y - p1.y;
		int b = p1.x - p2.x;
		int c = p2.x*p1.y - p1.x*p2.y;
		if ((a*x + b * y + c)*(a*x + b * y + c) <= 25 * (a*a + b * b))
			return true;
		return false;
	}
}