#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <string.h>
#include <glut.h>

#define PI 3.14159265
#define radToDeg  (180.0 / PI);
#define degToRad  (PI / 180.0);

GLUquadricObj *quadratic;

double screenX = glutGet(GLUT_SCREEN_WIDTH);
double screenY = glutGet(GLUT_SCREEN_HEIGHT);

double eyeX = 0;
double eyeY = 0;
double eyeZ = 10;

double cameraX = 0;

double shootingAngle = 0;

double bulletX = 0;
double bulletY = 0;
double bulletZ = 0;
int bulletAngle = 0;

double grenadeX = 0;
double grenadeY = 0;
double grenadeZ = 0;
int grenadeAngle = 0;

double shurikenX = 0;
double shurikenY = 0;
double shurikenZ = 0;
int shurikenAngle = 0;

double targetX = 0;
double targetY = 0;
double targetZ = -55;

double* p;
int p0[3];
int p1[3];
int p2[3];
int p3[3];

int weapone = 0;
bool hit = false;
bool replay = false;
bool done = false;
float startFire = 0;

void startAgain(){
	eyeX = 0;
	eyeY = 0;
	eyeZ = 10;
	cameraX = -60;
	shootingAngle = 0;
	bulletX = 0;
	bulletY = 0;
	bulletZ = 0;
	bulletAngle = 0;
	grenadeX = 0;
	grenadeY = 0;
	grenadeZ = 0;
	grenadeAngle = 0;
	shurikenX = 0;
	shurikenY = 0;
	shurikenZ = 0;
	shurikenAngle = 0;
	targetX = 0;
	targetY = 0;
	targetZ = -55;
	weapone = 0;
	hit = false;
	replay = false;
	done = false;
	startFire = 0;
}

void replayScene(){
	eyeX = 0;
	eyeY = 0;
	eyeZ = 10;
	bulletX = 0;
	bulletY = 0;
	bulletZ = 0;
	bulletAngle = 0;
	grenadeX = 0;
	grenadeY = 0;
	grenadeZ = 0;
	grenadeAngle = 0;
	shurikenX = 0;
	shurikenY = 0;
	shurikenZ = 0;
	shurikenAngle = 0;
	replay = true;
	startFire = 0;
}

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
			 cameraX, 0.0, -60,   //center
			  0.0, 1.0, 0.0);  //up
}

void passM(int x, int y)
{
	if (!hit){
		shootingAngle = ((2 * x - screenX) / screenX) * 62;
		double radAngle = shootingAngle * degToRad;
		cameraX = 50* tan(radAngle);
	}
		
	glutPostRedisplay();
}

void actM(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !hit)
		hit = true;
	glutPostRedisplay();
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
	if (k == '1' && !hit)
		weapone = 0;
	if (k == '2' && !hit)
		weapone = 1;
	if (k == '3' && !hit)
		weapone = 2;
	if (k == 'w' && !hit && targetZ > -58)
		targetZ -= 2;
	if (k == 'a' && !hit && targetX > -33)
		targetX -= 2;
	if (k == 's' && !hit && targetZ < -20)
		targetZ += 2;
	if (k == 'd' && !hit && targetX < 33)
		targetX += 2;
	if (k == (char)27)
		exit(0);
	if (k == (char)13)
		startAgain();
	if (k == (char)32 && done){
		replayScene();
	}

	glutPostRedisplay();
}

void print(int x, int y, char *string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
}

double* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	double res[3];
	res[0] = pow((1 - t), 3)*p0[0] + 3 * t*pow((1 - t), 2)*p1[0] + 3 * pow(t, 2)*(1 - t)*p2[0] + pow(t, 3)*p3[0];
	res[1] = pow((1 - t), 3)*p0[1] + 3 * t*pow((1 - t), 2)*p1[1] + 3 * pow(t, 2)*(1 - t)*p2[1] + pow(t, 3)*p3[1];
	res[2] = pow((1 - t), 3)*p0[2] + 3 * t*pow((1 - t), 2)*p1[2] + 3 * pow(t, 2)*(1 - t)*p2[2] + pow(t, 3)*p3[2];
	return res;
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
	//Backward Wall
	glPushMatrix();
	glTranslated(0, 0, 35);
	glScaled(10, 4, 1);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawWall(0.02);
	glPopMatrix();
	//Downward Wall
	glPushMatrix();
	glTranslated(0, -20, -25);
	glScaled(10, 4, 12);
	drawWall(0.02);
	glPopMatrix();
	//Upper Wall
	glPushMatrix();
	glTranslated(0, 20, -25);
	glScaled(10, 4, 12);
	drawWall(0.02);
	glPopMatrix();
	//Right Wall
	glPushMatrix();
	glTranslated(50, 0, -25);
	glScaled(10, 4, 12);
	glRotated(90, 0.0, 0.0, 1.0);
	drawWall(0.02);
	glPopMatrix();
	//Left Wall
	glPushMatrix();
	glTranslated(-50, 0, -25);
	glScaled(10, 4, 12);
	glRotated(-90, 0.0, 0.0, 1.0);
	drawWall(0.02);
	glPopMatrix();
}

void drawBulletPath(){
	glColor3d(0.5, 0.5, 0.5);
	double radAngle = shootingAngle * degToRad;
	double slope = tan(radAngle);
	double xPosition = 2 * sin(radAngle);
	for (double i = bulletZ-2; i > targetZ; i--){
		glPushMatrix();
		xPosition += slope;
		glTranslated(xPosition, 0, i);
		glutSolidSphere(0.1, 100, 100);
		glPopMatrix();
	}
	glColor3d(1, 1, 1);
}

void drawGrenadePath(){
	glColor3f(0.5, 0.5, 0.5);
	double radAngle = shootingAngle * degToRad;
	p0[0] = 0;
	p0[1] = 0;
	p0[2] = 0;

	p1[0] = 2;
	p1[1] = 15;
	p1[2] = 15 * tan(radAngle);
	
	p2[0] = 72;
	p2[1] = 10;
	p2[2] = 50 * tan(radAngle);
	
	p3[0] = 62;
	p3[1] = -30;
	p3[2] = 60 * tan(radAngle);
	
	for (float t = 0; t<1; t += 0.02)
	{
		p = bezier(t, p0, p1, p2, p3);
		glPushMatrix();
		glTranslated(p[2], p[1], -p[0]);
		glutSolidSphere(0.1, 100, 100);
		glPopMatrix();
	}
	glColor3d(1, 1, 1);
}

void drawShurikenPath(){
	glColor3f(0.5, 0.5, 0.5);
	double radAngle = shootingAngle * degToRad;
	p0[0] = 0;
	p0[1] = 0;

	p1[0] = 30;
	p1[1] = 15 + 30 * tan(radAngle);

	p2[0] = 55;
	p2[1] = 30 +55 * tan(radAngle);

	p3[0] = 60;
	p3[1] = 0 + 60 * tan(radAngle);

	for (float t = 0; t<1; t += 0.02)
	{
		p = bezier(t, p0, p1, p2, p3);
		glPushMatrix();
		glTranslated(p[1], 0, -p[0]);
		glutSolidSphere(0.1, 100, 100);
		glPopMatrix();
	}
	glColor3d(1, 1, 1);
}

void Display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//setupLights();
	setupCamera();
	
	switch (weapone)
	{
	case 0:
		drawBulletPath();
		glPushMatrix();
		glTranslated(bulletX, bulletY, bulletZ);
		glScaled(0.6, 0.6, 0.5);
		glRotated(-shootingAngle, 0, 1, 0);
		glRotated(180, 0, 1, 0);
		glRotated(bulletAngle, 0, 0, 1);
		drawBullet();
		glPopMatrix();
		break;
	case 1:
		drawGrenadePath();
		glPushMatrix();
		glTranslated(grenadeX, grenadeY, grenadeZ);
		glScaled(0.1, 0.1, 0.1);
		glRotated(-45, 1, 0, 0);
		glRotated(shootingAngle, 0, 1, 0);
		glRotated(grenadeAngle, 1, 0, 0);
		drawGrenade();
		glPopMatrix();
		break;
	case 2:
		drawShurikenPath();
		glPushMatrix();
		glTranslated(shurikenX, shurikenY, shurikenZ);
		glRotated(shootingAngle, 0, 1, 0);
		glRotated(90, 1, 0, 0);
		glRotated(shootingAngle, 0, 1, 0);
		glScaled(0.2, 0.2, 0.2);
		drawShuriken();
		glPopMatrix();
		break;
	}

	glPushMatrix();
	glTranslated(targetX, targetY, targetZ);
	glScaled(2, 2, 2);
	drawTarget();
	glPopMatrix();

	drawRoom();

	glFlush();
}

void Anim() {
	if (hit){
		//variables for Bullet Firing	
		double radAngle = shootingAngle * degToRad;
		double slope = tan(radAngle);
		double zStop = 0;

		//variables for Gernade & Shuriken Firing	
		if (weapone != 2){
			p0[0] = 0;
			p0[1] = 0;
			p0[2] = 0;

			p1[0] = 2;
			p1[1] = 15;
			p1[2] = 15 * tan(radAngle);

			p2[0] = 72;
			p2[1] = 10;
			p2[2] = 50 * tan(radAngle);

			p3[0] = 62;
			p3[1] = -30;
			p3[2] = 60 * tan(radAngle);
		}
		else{
			p1[0] = 30;
			p1[1] = 15 + 30 * tan(radAngle);

			p2[0] = 55;
			p2[1] = 30 + 55 * tan(radAngle);

			p3[0] = 60;
			p3[1] = 0 + 60 * tan(radAngle);
		}
		if (targetX - 10 < targetZ * tan(radAngle) && targetX + 10 > targetZ * tan(radAngle))
			zStop = targetZ;
		else
			zStop = -60;
		switch (weapone)
		{
		case 0:
			if (bulletZ > zStop + 1 && bulletX < 49 && bulletX > -49){
				bulletX += 1 * slope;
				bulletZ = startFire;
				startFire -= 1;
				bulletAngle = ++bulletAngle % 360;
			}
			else
				done = true;
			if (replay)
			{
				eyeX = bulletX;
				eyeY = bulletY;
				eyeZ = 5 + bulletZ ;
			}
			break;
		case 1:
			if (grenadeZ > zStop + 1 && grenadeX < 49 && grenadeX > -49){
				p = bezier(startFire, p0, p1, p2, p3);
				grenadeX = p[2];
				grenadeY = p[1];
				grenadeZ = -p[0];
				startFire += 0.01;
				grenadeAngle = ++grenadeAngle % 360;
			}
			else
				done = true;
			if (replay)
			{
				eyeX = grenadeX;
				eyeY = grenadeY;
				eyeZ = 5 + grenadeZ;
			}
			break;
		case 2:
			if (shurikenZ > zStop + 1 && shurikenX < 49 && shurikenX > -49){
				p = bezier(startFire, p0, p1, p2, p3);
				shurikenX = p[1];
				shurikenZ = -p[0];
				startFire += 0.01;
				shurikenAngle = ++shurikenAngle % 360;
			}
			else
				done = true;
			if (replay)
			{
				eyeX = shurikenX;
				eyeY = shurikenY;
				eyeZ = shurikenZ + 5;
			}
			break;
		}
		
	}
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
