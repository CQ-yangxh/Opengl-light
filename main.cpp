#include<windows.h>
#include<gl/gl.h>
#include<gl/glut.h>
#include<gl/glu.h>
#include<stdio.h>


//��ת�ǶȲ���
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void drawAxisLines(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) {
	// draw Z axis
	glPushMatrix();
	glBegin(GL_LINES);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // GREEN
	glVertex3f(0.0f, 0.0f, zMin);
	glVertex3f(0.0f, 0.0f, zMax);
	glEnd();
	glPopMatrix();

	// Draw X axis
	glPushMatrix();
	glBegin(GL_LINES);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // RED
	glVertex3f(xMin, 0.0f, 0.0f);
	glVertex3f(xMax, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	// Draw Y axis
	glPushMatrix();
	glBegin(GL_LINES);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // BLUE
	glVertex3f(0.0f, yMin, 0.0f);
	glVertex3f(0.0f, yMax, 0.0f);
	glEnd();
	glPopMatrix();
}

//��ʼ������
void SetupRC(void)
{

	//���ù�ԴLINGT0�Ĳ���
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f,1.0f };
	GLfloat light_ambient[] = { 0.0f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);

	//ʹ��Դ��Ч
	glEnable(GL_LIGHTING);  //��������
	glEnable(GL_LIGHT0);    //�������շ��ų���

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
	//���ô��ڱ�������ɫΪ��ɫ
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


}
void ChangeSize(int w, int h)
{
	GLfloat nRange = 80.0f;
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//�����ü��ռ�
	gluPerspective(40.0f, (GLfloat)w / (GLfloat)h, 1.0f, 20.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{

	//�����ɫ����Ȼ����� ������Ȳ��Կռ�
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();
	//ƽ��z����Ϊ�����õ�Ч��
	glTranslatef(0.0f, 0.0f, -5.0f);



	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f); //ʹ��ɫ������x����ת  
	glRotatef(yRot, 0.0, 1.0, 0.0f);   //ʹ��ɫ������y����ת 
	//��Դ����λ��
	//����ָ���Ĺ�Դ,light������GL_LIGHT0��GL_LIGHT1��pname������ǹ�Դ�����ԣ���ָ����һ������������params��ʾ��ʾpname���Խ�Ҫ�����õ�ֵ
	GLfloat position[] = { 0.0f, 0.0f, 1.5f, 5.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glTranslated(0.0f, 0.0f, 1.5f);
	//����һ����ɫ�Ĺ���
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(0.1f, 50.f, 50.f);
	glEnable(GL_LIGHTING);


	glPopMatrix();	//���»��Ƶ�ͼ�����������ת

	GLfloat mat_diffuse[] = { 1.0, 0.5, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	//glEnable(GL_COLOR_MATERIAL);
	//glBegin(GL_POLYGON);
	//glColor3f(1.0, 0.0, 0.0);
	//glVertex3f(1.0f, 1.0f, 0.0f);
	//glVertex3f(-1.0f, 1.0f, 0.0f);
	//glVertex3f(0.0f, -1.0f, 0.0f);
	//glEnd();
	glutSolidTorus(0.275, 0.85, 50, 50);
	glPopMatrix();
	glutSwapBuffers();  //ˢ���������


}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)    xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)  xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)  yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT) yRot += 5.0f;


	//���glPushMatrix()��glPopMatrix()��ͼģʽ�����ת
	// ���ȣ�glPushMateix��ס���Ļ�ͼ���꣨��㣩
	//glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	//glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	//Ȼ����ת��Ӧ����������ͼ��
	//glPopMatrix �ص�������ԭ����λ�ã���㣩

	printf("%lf\n", yRot);
	if (xRot >= 360.0f)   xRot = 0.0f;
	if (xRot < -1.0f)    xRot = 355.0f;
	if (yRot >= 360.0f)    yRot = 0.0f;
	if (yRot < -1.0f)    yRot = 355.0f;


	//ˢ�´���  ǿ��
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{

	//initialize the GLUT library  
	//��ʼ��GLUT��
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("�ƶ��Ĺ�Դ");

	//�ص�����
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	SetupRC();
	glutMainLoop();
	return 0;
}