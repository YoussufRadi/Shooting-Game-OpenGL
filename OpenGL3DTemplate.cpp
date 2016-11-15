#include <math.h>
#include <glut.h>

#define PI 3.14159265
#define radToDeg  (180.0 / PI);
#define degToRad  (PI / 180.0);

double screenX = glutGet(GLUT_SCREEN_WIDTH);
double screenY = glutGet(GLUT_SCREEN_HEIGHT);
double eyeX;
double eyeY;
double eyeZ = 10;
double shootingAngle;
double bulletX;
double bulletY;
double bulletZ;
double grenadeX;
double grenadeY;
double grenadeZ;
double shurikenX;
double shurikenY;
double shurikenZ;
double targetX;
double targetY;
double targetZ = -50;

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
	shootingAngle = ((2 * x - screenX) / screenX) * 45;
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
	glTranslated(0, 0, 1.48);
	glScaled(1, 0.4, 1);
	glutSolidCone(0.5, 2.5, 4, 1);
	glPushMatrix();
	glRotated(180, 0, 1, 0);
	glutSolidCone(0.5, 1, 4, 1);
	glPopMatrix();
	glPopMatrix();
}

void drawShuriken(){
	glutSolidTorus(0.07, 0.43, 100, 100);
	
	glutSolidCone(0.38, 0.25, 4, 1);
	
	glPushMatrix();
	glRotated(180, 0, 1, 0);
	glutSolidCone(0.38, 0.25, 4, 1);
	glPopMatrix();

	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	drawShurikenPart();
	glPopMatrix();

	glPushMatrix();
	glRotated(-120, 0, 0, 1);
	glRotated(-90, 1, 0, 0);
	drawShurikenPart();
	glPopMatrix();

	glPushMatrix();
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
	gluCylinder(quadratic, 5, 5, 1, 100, 100);
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
	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();
}

void drawWall(double thickness) {
	glPushMatrix();
	glColor3f(0.8, 1.0, 0.8);
	glScaled(1.0, 0.1 * thickness, 1.0);
	glutSolidCube(10);
	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();
}

void drawRoom(){
	//Front Wall
	glPushMatrix();
	glTranslated(0, 0, -60);
	glScaled(10, 4, 1);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawWall(0.02);
	glPopMatrix();
	//Downward Wall
	glPushMatrix();
	glTranslated(0, -20, -25);
	glScaled(10, 4, 7);
	drawWall(0.02);
	glPopMatrix();
	//Upper Wall
	glPushMatrix();
	glTranslated(0, 20, -25);
	glScaled(10, 4, 7);
	drawWall(0.02);
	glPopMatrix();
	//Right Wall
	glPushMatrix();
	glTranslated(50, 0, -25);
	glScaled(10, 4, 7);
	glRotated(90, 0.0, 0.0, 1.0);
	drawWall(0.02);
	glPopMatrix();
	//Left Wall
	glPushMatrix();
	glTranslated(-50, 0, -25);
	glScaled(10, 4, 7);
	glRotated(-90, 0.0, 0.0, 1.0);
	drawWall(0.02);
	glPopMatrix();
}

void drawaBulletPath(){
	glColor3d(0.5, 0.5, 0.5);
	double radAngle = shootingAngle * degToRad;
	double slope = tan(radAngle);
	double xPosition = 2*sin(radAngle);
	for (double i = -2; i > targetZ; i--){
		glPushMatrix();
		xPosition += slope ;
		glTranslated(xPosition, 0, i);
		glutSolidSphere(0.1, 100, 100);
		glPopMatrix();
	}
	glColor3d(1, 1, 1);
}

void Display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//setupLights();
	setupCamera();
	
	drawaBulletPath();
	glPushMatrix();
	glTranslated(bulletX, bulletY, bulletZ);
	glScaled(0.6, 0.6, 0.5);
	glRotated(-shootingAngle, 0, 1, 0);
	glRotated(180, 0, 1, 0);
	drawBullet();
	glPopMatrix();

	glPushMatrix();
	glTranslated(grenadeX, grenadeY, grenadeZ);
	glRotated(shootingAngle, 0, 1, 0);
	//drawGrenade();
	glPopMatrix();

	glPushMatrix();
	glTranslated(shurikenX, shurikenY, shurikenZ);
	glRotated(shootingAngle, 0, 1, 0);
	//drawShuriken();
	glPopMatrix();

	glPushMatrix();
	glTranslated(targetX, targetY, targetZ);
	drawTarget();
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
	quadratic = gluNewQuadric();
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
