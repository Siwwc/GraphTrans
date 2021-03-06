// ConsoleApplication2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Shape.h"

using namespace std;

#define WIDTH 600
#define HEIGHT 600

int ori[2];
int coner = -1;
int mx, my;
list<Shape*> allShape;
bool isDraw = false;
bool isDrag = false;
bool isHave = false;
bool isSelect = false;
bool isChange = false;
ShapeType curTy = Cir;
Shape* shape = NULL;

void showCoord();

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineStipple(1, 0xF0F0);
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	for (list<Shape*>::iterator i = allShape.begin(); i != allShape.end(); i++) {
		(*i)->draw();
	}
	if (isDraw)
		shape->draw();
	if (isSelect&&isHave)
		shape->drawBoard();
	//showCoord();

	glutSwapBuffers();
}

void myMouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (!isSelect) {
			if (state == GLUT_DOWN) {
				ori[0] = x;
				ori[1] = y;
				isDraw = true;
				switch (curTy) {
				case Squr:
					shape = new SqurShape(x, HEIGHT - y - 17, 0, 0);
					break;
				case Line:
					shape = new LineShape(x, HEIGHT - y - 17, x, HEIGHT - y - 17);
					break;
				case Cir:
					shape = new CirShape(x, HEIGHT - y - 17, 0);
					break;
				default:
					isDraw = false;
					break;
				}
			}
			if (state == GLUT_UP) {
				switch (curTy) {
				case Cir:
					if (((CirShape*)shape)->r >= 1.0f)
						allShape.push_back(shape);
					else
						delete shape;
					break;
				case Squr:
					if (((SqurShape*)shape)->width != 0 && ((SqurShape*)shape)->height != 0)
						allShape.push_back(shape);
					else
						delete shape;
					break;
				case Line:
				{
					LineShape * cir = (LineShape*)shape;
					if (cir->p1.x != cir->p2.x || cir->p1.y != cir->p2.y)
						allShape.push_back(shape);
					else
						delete shape;
					break;
				}
				default:
					break;
				}
				shape = NULL;
				isDraw = false;
			}
		}
		else {
			if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
				if (state == GLUT_DOWN) {
					for (list<Shape*>::iterator i = allShape.begin(); i != allShape.end(); i++) {
						if ((*i)->In(x, HEIGHT - y - 17)) {
							ori[0] = x;
							ori[1] = y;
							shape = (*i);
							curTy = (*i)->type;
							isDrag = true;
							isHave = true;
							break;
						}
					}
					if (!isDrag) {
						shape = NULL;
						isHave = false;
					}
					glutPostRedisplay();
				}
				if (state == GLUT_UP) {
					if (!isHave)
						shape = NULL;
					isDrag = false;
				}
			}
			else {
				if (state == GLUT_DOWN) {
					if (isHave&&shape->isEdit(x, HEIGHT - y - 17, &coner)) {
						ori[0] = x;
						ori[1] = y;
						isChange = true;
					}
					else if (!(isHave&&shape->In(x, HEIGHT - y - 17))) {
						short test = 0;
						for (list<Shape*>::iterator i = allShape.begin(); i != allShape.end(); i++) {
							if ((*i)->In(x, HEIGHT - y - 17)) {
								shape = (*i);
								curTy = (*i)->type;
								isHave = true;
								test++;
								break;
							}
						}
						if (!test) {
							isHave = false;
							shape = NULL;
						}
						glutPostRedisplay();
					}
				}
				if (state == GLUT_UP) {
					if (!isHave)
						shape = NULL;
					isChange = false;
					isDrag = false;
				}
			}
		}
		break;
	default:
		break;
	}
}

void myMotion(int x, int y) {
	if (isDrag) {
		shape->move(x - ori[0], y - ori[1]);
		ori[0] = x;
		ori[1] = y;
	}
	else if (isDraw) {
		shape->size(x - ori[0], y - ori[1]);
	}
	else if (isChange) {
		shape->setStyle(x - ori[0], y - ori[1], coner);
		ori[0] = x;
		ori[1] = y;
	}

	if (isDrag || isDraw || isChange) {
		glutPostRedisplay();
	}
}

void myMenu(int select) {
	switch (select) {
	case 0:
		curTy = Cir;
		isSelect = false;
		break;
	case 1:
		curTy = Squr;
		isSelect = false;
		break;
	case 2:
		curTy = Line;
		isSelect = false;
		break;
	case 3:
		isSelect = true;
		isHave = false;
		shape = NULL;
		break;
	default:
		break;
	}
}

void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 127:
		if (isSelect&&isHave) {
			allShape.remove(shape);
			isHave = false;
			delete shape;
			shape = NULL;
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}
}

void showCoord() {
	glColor3f(0, 0, 0);
	glRasterPos2i(20, 30);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 88);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 58);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48 + (mx / 100));
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48 + (mx % 100) / 10);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48 + (mx % 10));

	glRasterPos2i(60, 30);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 89);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 58);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48 + (my / 100));
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48 + (my % 100) / 10);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48 + (my % 10));
}

void myPassive(int x, int y) {
	mx = x;
	my = HEIGHT - y - 17;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("Drag");

	glewInit();
	init();

	int subm = glutCreateMenu(myMenu);
	glutAddMenuEntry("Circle", 0);
	glutAddMenuEntry("Square", 1);
	glutAddMenuEntry("Line", 2);

	glutCreateMenu(myMenu);
	glutAddMenuEntry("Select", 3);
	glutAddSubMenu("Shape", subm);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(display);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);
	glutKeyboardFunc(myKeyboard);
	glutPassiveMotionFunc(myPassive);

	glutMainLoop();
    return 0;
}

