#include <glut.h>

double screenX = glutGet(GLUT_SCREEN_WIDTH);
double screenY = glutGet(GLUT_SCREEN_HEIGHT);
double eyeX = 0;
double eyeY = 0;
double eyeZ = 10;
GLUquadricObj *quadratic;

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-0.5, 0.5, -0.5, 0.5, -1, 1);
	gluPerspective(60, screenX / screenY, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ,   //eye
			  0.0, 0.0, 0.0,   //center
			  0.0, 1.0, 0.0);  //up
}

void passM(int x, int y)
{
	
	glutPostRedisplay();
}

void actM(int button, int state, int x, int y)
{

	glutPostRedisplay();//redisplay to update the screen with the new paraeters
}

void spe(int k, int x, int y)
{
	if (k == GLUT_KEY_UP){
		eyeY++;
		if (eyeY > 0)
			eyeZ--;
		else
			eyeZ++;
	}
	if (k == GLUT_KEY_DOWN){
		eyeY--;
		if (eyeY < 0)
			eyeZ--;
		else
			eyeZ++;
	}
	if (k == GLUT_KEY_LEFT){
		eyeX++;
	}
	if (k == GLUT_KEY_RIGHT)
		eyeX--;
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{

	if (k == (char)27)
		exit(0);
	glutPostRedisplay();
}

void drawWall(double thickness) {
	glPushMatrix();
	glScaled(1.0, 0.1 * thickness, 1.0);
	glutSolidCube(10);
	glPopMatrix();
}

void drawBullet(){
	glutSolidTorus(0.05, 0.29, 100, 100);
	glutSolidTorus(0.05, 0.14, 100, 100);
	gluCylinder(quadratic, 0.3, 0.3, 2.8, 100, 10);
	gluDisk(quadratic, 0, 0.3, 100, 100);
	glPushMatrix();
	glTranslated(0, 0, 2.8);
	gluCylinder(quadratic, 0.3, 0.23, 0.27, 100, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, 3.07);
	gluCylinder(quadratic, 0.23, 0.23, 0.5, 100, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, 3.57);
	gluCylinder(quadratic, 0.23, 0.14, 0.255, 100, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, 3.79);
	glutSolidSphere(0.142, 100, 100);
	glPopMatrix();
}

void drawGrenade(){
	glutSolidSphere(4, 100, 100);
	glutSolidTorus(0.2, 4, 100, 100);
	glPushMatrix();
	glTranslated(0, 0, 2.5);
	gluCylinder(quadratic, 1.2, 1.2, 2.2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, 4.7);
	gluDisk(quadratic, 0, 1.2, 100, 100);
	glPopMatrix();
}

void drawShurikenPart(){
	glPushMatrix();
	glScaled(1, 0.4, 1);
	glutSolidCone(0.5, 2.5, 4, 100);
	glPushMatrix();
	glRotated(180, 0, 1, 0);
	glutSolidCone(0.5, 1, 4, 100);
	glPopMatrix();
	glPopMatrix();
}

void drawShuriken(){
	glPushMatrix();
	glTranslated(0, -0.43, 0);
	glutSolidTorus(0.02, 0.13, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.43, 0);
	glutSolidCone(0.11, 0.1, 4, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.43, 0);
	glRotated(180, 0, 1, 0);
	glutSolidCone(0.11, 0.1, 4, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.7, 0);
	glRotated(-90, 1, 0, 0);
	drawShurikenPart();
	glPopMatrix();

	glPushMatrix();
	glTranslated(1, -1, 0);
	glRotated(-120, 0, 0, 1);
	glRotated(-90, 1, 0, 0);
	drawShurikenPart();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1, -1, 0);
	glRotated(120, 0, 0, 1);
	glRotated(-90, 1, 0, 0);
	drawShurikenPart();
	glPopMatrix();

}

void drawTarget(){
	glColor3f(1.0, 0.0, 0.0);
	gluDisk(quadratic, 4, 5, 100, 100);
	glColor3f(1.0, 1.0, 1.0);
	gluDisk(quadratic, 3, 4, 100, 100);
	glColor3f(1.0, 0.0, 0.0);
	gluDisk(quadratic, 2, 3, 100, 100);
	glColor3f(1.0, 1.0, 1.0);
	gluDisk(quadratic, 1, 2, 100, 100);
	glColor3f(1.0, 0.0, 0.0);
	gluDisk(quadratic, 0, 1, 100, 100);
	gluCylinder(quadratic, 5, 5, 0.3, 100, 100);
	glPushMatrix();
	glTranslated(0, 0, 0.3);
	glColor3f(1.0, 0.0, 0.0);
	gluDisk(quadratic, 4, 5, 100, 100);
	glColor3f(1.0, 1.0, 1.0);
	gluDisk(quadratic, 4, 5, 100, 100);
	glColor3f(1.0, 0.0, 0.0);
	gluDisk(quadratic, 2, 3, 100, 100);
	glColor3f(1.0, 1.0, 1.0);
	gluDisk(quadratic, 1, 2, 100, 100);
	glColor3f(1.0, 0.0, 0.0);
	gluDisk(quadratic, 0, 1, 100, 100);
	glPopMatrix();
}

void drawRoom(){
	//Downward Wall
	glPushMatrix();
	glTranslated(0, 0, -30);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawWall(0.02);
	glPopMatrix();
	//Front Wall
	glPushMatrix();
	glTranslated(0, -5, -25);
	glScaled(1, 1, 7);
	drawWall(0.02);
	glPopMatrix();
	//Right Wall
	glPushMatrix();
	glTranslated(5, 0, -25);
	glScaled(1, 1, 7);
	glRotated(90, 0.0, 0.0, 1.0);
	drawWall(0.02);
	glPopMatrix();
	//Left Wall
	glPushMatrix();
	glTranslated(-5, 0, -25);
	glScaled(1, 1, 7);
	glRotated(-90, 0.0, 0.0, 1.0);
	drawWall(0.02);
	glPopMatrix();
	//Upper Wall
	glPushMatrix();
	glTranslated(0, 5, -25);
	glScaled(1, 1, 7);
	drawWall(0.02);
	glPopMatrix();
}

void Display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setupLights();
	setupCamera();
	quadratic = gluNewQuadric();

	glPushMatrix();
	//drawBullet();
	glPopMatrix();

	glPushMatrix();
	//drawGrenade();
	glPopMatrix();

	glPushMatrix();
	//drawShuriken();
	glPopMatrix();

	glPushMatrix();
	//drawTarget();
	glPopMatrix();

	drawRoom();

	glFlush();
}

void Anim() {

	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(screenX, screenY);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Assignment 2");
	glutDisplayFunc(Display);
	glutIdleFunc(Anim);

	//glutFullScreen();
	//glutSetCursor(GLUT_CURSOR_NONE);
	glutPassiveMotionFunc(passM);
	glutKeyboardFunc(key);
	glutSpecialFunc(spe);
	glutMouseFunc(actM);	

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	
	
	glutMainLoop();
	
}
