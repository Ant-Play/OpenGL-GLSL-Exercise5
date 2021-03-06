#include <GL/glut.h>

constexpr const auto WIDTH = 500;
constexpr const	auto HEIGHT = 500;

GLfloat xrot = 0;
GLfloat xold = 0;


void set_light() {
	static const GLfloat light_position[] = { 0.0f, 0.0f, -13.0f, 1.0f };
	static const GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	static const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void display() {

	//清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//设置视点
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 30.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	glRotatef(xrot, 0, 1, 0);
	//glTranslatef(0, 0, 3);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//设置光源
	set_light();

	//开启混合
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//第一个壶
	{
		GLfloat ambient[] = { 0.0,0.52,0.0,1.0 };
		GLfloat diffuse[] = { 0.86,0.54,0.0,1.0 };

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

		glTranslated(0.0, 0.0, -16.0);
		glColor4f(1, 0, 0, 1);
		glutSolidTeapot(4.5);
	}
	glPopMatrix();
	glPushMatrix();
	//第二个壶
	{
		GLfloat ambient[] = { 0.12,0.0,0.0,1.0 };
		GLfloat diffuse[] = { 0.81,0.0,0.0,1.0 };

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

		glTranslated(0, 0, -7);
		glutSolidTeapot(3);
	}
	glPopMatrix();
	glPushMatrix();

	glDepthMask(GL_FALSE);
	//第三个壶
	{
		GLfloat ambient[] = { 0.2,0.63,0.5,1 };
		GLfloat diffuse[] = { 0.57,0.83,0.62,0.2 };

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

		glTranslated(0, 0, -1.15);
		glutSolidTeapot(2);

	}
	glPopMatrix();
	glPushMatrix();
	//第四个壶
	{
		GLfloat ambient[] = { 0.2,0.3,0.2,1 };
		GLfloat diffuse[] = { 1,1,1,0.35 };

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

		glTranslated(0, 0, 3);
		glutSolidTeapot(1.2);
	}
	glPopMatrix();
	glPushMatrix();
	//第五个壶
	{
		GLfloat ambient[] = { 0.2,0.63,0.5,1 };
		GLfloat diffuse[] = { 0.57,0.83,0.62,0.2 };

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

		glTranslated(0, 0, 6);
		glutSolidTeapot(1);
	}

	glDepthMask(GL_TRUE);
	glPopMatrix();
	glutSwapBuffers();
}


void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		xold = x;
	}
}
void mouse_motion(int x, int y) {
	xrot += x - xold;

	xold = x;
	glutPostRedisplay();
}

void reshape(int w, int h) {
	float aspect = (float)w / (h ? h : 1);//平截头体的纵横比，也就是宽度除以高度，(h)?h:1意思是若h=0，则h=1

	glViewport(0, 0, w, h);

	//进行投影变换前调用下面两个函数，接下来的变换函数将影响投影矩阵
	//在窗口改变函数reshape中先用glMatrixMode(GL_PROJECTION)定义视锥,再用glMatrixMode(GL_MODELVIEW)改为模型变换
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(75.0f, aspect, 1.0f, 100.0f);//
	glViewport(0, 0, w, h);

	glMatrixMode(GL_MODELVIEW);

}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("BLEND");

	//glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_motion);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}