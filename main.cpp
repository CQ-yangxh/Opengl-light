#include<windows.h>
#include<gl/gl.h>
#include<gl/glut.h>
#include<gl/glu.h>
#include<stdio.h>


//旋转角度参数
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

//初始化窗口
void SetupRC(void)
{

	//设置光源LINGT0的参数
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f,1.0f };
	GLfloat light_ambient[] = { 0.0f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);

	//使光源有效
	glEnable(GL_LIGHTING);  //启动光照
	glEnable(GL_LIGHT0);    //启动光照符号常数

	//开启深度测试
	glEnable(GL_DEPTH_TEST);
	//设置窗口背景西颜色为黑色
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

	//建立裁剪空间
	gluPerspective(40.0f, (GLfloat)w / (GLfloat)h, 1.0f, 20.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{

	//清除颜色及深度缓冲区 开启深度测试空间
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();
	//平移z负轴为了良好的效果
	glTranslatef(0.0f, 0.0f, -5.0f);



	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f); //使黄色球绕着x轴旋转  
	glRotatef(yRot, 0.0, 1.0, 0.0f);   //使黄色球绕着y轴旋转 
	//光源设置位置
	//创建指定的光源,light可以是GL_LIGHT0、GL_LIGHT1，pname定义的是光源的属性，它指定了一个命名参数。params表示表示pname属性将要被设置的值
	GLfloat position[] = { 0.0f, 0.0f, 1.5f, 5.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glTranslated(0.0f, 0.0f, 1.5f);
	//绘制一个黄色的光球
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(0.1f, 50.f, 50.f);
	glEnable(GL_LIGHTING);


	glPopMatrix();	//以下绘制的图案不会跟着旋转

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
	glutSwapBuffers();  //刷新命令缓冲区


}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)    xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)  xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)  yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT) yRot += 5.0f;


	//结合glPushMatrix()和glPopMatrix()绘图模式理解旋转
	// 首先，glPushMateix记住来的绘图坐标（起点）
	//glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	//glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	//然后旋转相应的坐标后绘制图形
	//glPopMatrix 回到了坐标原来的位置（起点）

	printf("%lf\n", yRot);
	if (xRot >= 360.0f)   xRot = 0.0f;
	if (xRot < -1.0f)    xRot = 355.0f;
	if (yRot >= 360.0f)    yRot = 0.0f;
	if (yRot < -1.0f)    yRot = 355.0f;


	//刷新窗口  强制
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{

	//initialize the GLUT library  
	//初始化GLUT库
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("移动的光源");

	//回调函数
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	SetupRC();
	glutMainLoop();
	return 0;
}