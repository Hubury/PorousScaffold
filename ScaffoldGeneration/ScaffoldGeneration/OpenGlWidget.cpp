#include "OpenGlWidget.h"
#include <qdebug.h>

OpenGlWidget::OpenGlWidget(QWidget* parent)
: QGLWidget(parent)
{
	_isreadfile = false;
	setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
	rotationX = 0.0;
	rotationY = 0.0;
	rotationZ = 0.0;
	cameraloc = 4.0;
	diagonal_length = 2.0;
	paintType = 3;//Ĭ�ϻ���ģʽΪ��Ƭ
	center.x = 0.0;
	center.y = 0.0;
	center.z = 0.0;
}

OpenGlWidget::~OpenGlWidget()
{
}

void OpenGlWidget::initializeGL()
{
	qglClearColor(Qt::darkBlue);
	//�ӹ�����Ϣ
	GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //ָ����0�Ź�Դ��λ��   
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient); //GL_AMBIENT��ʾ���ֹ������䵽�ò����ϣ�  
	//�����ܶ�η�������������ڻ����еĹ���ǿ�ȣ���ɫ��  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse); //�������~~  
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);//���淴���~~~  

	glEnable(GL_LIGHT0); //ʹ�õ�0�Ź���  
	glEnable(GL_LIGHTING); //�ں������Ⱦ��ʹ�ù���  
	glEnable(GL_DEPTH_TEST); //�����������Ȳ��ԣ��������ں��������ᱻ���ţ����緿�Ӻ����п����������������Ȳ��ԣ�  
	//���Ȼ��˷����ٻ��������Ḳ�Ƿ��ӵģ���������Ȳ��Ժ���������ô������һ���ڷ��Ӻ��棨�����ӵ��ţ�
}

void OpenGlWidget::resizeGL(int width, int height)
{
	if (height == 0)	height = 1;
	float ratio = 1.0* width / height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ������ȷ��ͶӰ����
	gluPerspective(45, ratio, 0.1, 1000);
	//����������ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
}
//���ƺ���
void OpenGlWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, cameraloc, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//glTranslatef(center.x, center.y, center.z);
	glRotatef(rotationX, 1.0, 0.0, 0.0);
	glRotatef(rotationY, 0.0, 1.0, 0.0);
	glRotatef(rotationZ, 0.0, 0.0, 1.0);
	glTranslatef(-center.x, -center.y, -center.z);

	if (_isreadfile)
	{
		if (paintType == 0)//��ģ��
		{
			glPointSize(2);
			glBegin(GL_POINTS);
			for (int i = 0; i < Mesh->Vertex.size(); i++)
			{
				glNormal3d(Mesh->VertexNormal[i].x, Mesh->VertexNormal[i].y, Mesh->VertexNormal[i].z);//������
				glVertex3d(Mesh->Vertex[i].x, Mesh->Vertex[i].y, Mesh->Vertex[i].z);
			}
			glEnd();
		}
		if (paintType == 1)//�߿�ģ��
		{
			for (int i = 0; i < Mesh->Face.size(); i++)
			{
				glBegin(GL_LINE_LOOP);
				glNormal3d(Mesh->FaceNormal[i].x, Mesh->FaceNormal[i].y, Mesh->FaceNormal[i].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f1].x, Mesh->Vertex[Mesh->Face[i].f1].y, Mesh->Vertex[Mesh->Face[i].f1].z);
				glNormal3d(Mesh->FaceNormal[i].x, Mesh->FaceNormal[i].y, Mesh->FaceNormal[i].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f2].x, Mesh->Vertex[Mesh->Face[i].f2].y, Mesh->Vertex[Mesh->Face[i].f2].z);
				glNormal3d(Mesh->FaceNormal[i].x, Mesh->FaceNormal[i].y, Mesh->FaceNormal[i].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f3].x, Mesh->Vertex[Mesh->Face[i].f3].y, Mesh->Vertex[Mesh->Face[i].f3].z);
				glEnd();
			}
		}
		else if (paintType == 2)//��Ƭ���߿�
		{
			//����wire
			glDepthRange(0, 0.9999);
			glDisable(GL_LIGHTING);
			glLineWidth(1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			for (int i = 0; i < Mesh->Face.size(); i++)
			{
				glBegin(GL_LINE_LOOP);
				glNormal3d(Mesh->FaceNormal[i].x, Mesh->FaceNormal[i].y, Mesh->FaceNormal[i].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f1].x, Mesh->Vertex[Mesh->Face[i].f1].y, Mesh->Vertex[Mesh->Face[i].f1].z);
				glNormal3d(Mesh->FaceNormal[i].x, Mesh->FaceNormal[i].y, Mesh->FaceNormal[i].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f2].x, Mesh->Vertex[Mesh->Face[i].f2].y, Mesh->Vertex[Mesh->Face[i].f2].z);
				glNormal3d(Mesh->FaceNormal[i].x, Mesh->FaceNormal[i].y, Mesh->FaceNormal[i].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f3].x, Mesh->Vertex[Mesh->Face[i].f3].y, Mesh->Vertex[Mesh->Face[i].f3].z);
				glEnd();
			}
			glEnable(GL_LIGHTING);
			// ����flat
			glDepthRange(0, 1);
			glShadeModel(GL_FLAT);
			for (int i = 0; i < Mesh->Face.size(); i++)
			{
				glBegin(GL_TRIANGLES);
				glNormal3d(Mesh->FaceNormal[i].x, Mesh->FaceNormal[i].y, Mesh->FaceNormal[i].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f1].x, Mesh->Vertex[Mesh->Face[i].f1].y, Mesh->Vertex[Mesh->Face[i].f1].z);
				glNormal3d(Mesh->FaceNormal[i].x, Mesh->FaceNormal[i].y, Mesh->FaceNormal[i].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f2].x, Mesh->Vertex[Mesh->Face[i].f2].y, Mesh->Vertex[Mesh->Face[i].f2].z);
				glNormal3d(Mesh->FaceNormal[i].x, Mesh->FaceNormal[i].y, Mesh->FaceNormal[i].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f3].x, Mesh->Vertex[Mesh->Face[i].f3].y, Mesh->Vertex[Mesh->Face[i].f3].z);
				glEnd();
			}
		}
		else if (paintType == 3)//��Ƭģ��
		{
			glShadeModel(GL_FLAT);
			for (int i = 0; i < Mesh->Face.size(); i++)
			{
				glBegin(GL_TRIANGLES);
				glNormal3d(Mesh->FaceNormal[i].x, Mesh->FaceNormal[i].y, Mesh->FaceNormal[i].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f1].x, Mesh->Vertex[Mesh->Face[i].f1].y, Mesh->Vertex[Mesh->Face[i].f1].z);
				glNormal3d(Mesh->FaceNormal[i].x, Mesh->FaceNormal[i].y, Mesh->FaceNormal[i].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f2].x, Mesh->Vertex[Mesh->Face[i].f2].y, Mesh->Vertex[Mesh->Face[i].f2].z);
				glNormal3d(Mesh->FaceNormal[i].x, Mesh->FaceNormal[i].y, Mesh->FaceNormal[i].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f3].x, Mesh->Vertex[Mesh->Face[i].f3].y, Mesh->Vertex[Mesh->Face[i].f3].z);
				glEnd();
			}
		}
		else if (paintType == 4)//�⻬ģ��
		{
			glShadeModel(GL_SMOOTH);
			for (int i = 0; i < Mesh->Face.size(); i++)
			{
				glBegin(GL_TRIANGLES);
				glNormal3d(Mesh->VertexNormal[Mesh->Face[i].f1].x, Mesh->VertexNormal[Mesh->Face[i].f1].y, Mesh->VertexNormal[Mesh->Face[i].f1].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f1].x, Mesh->Vertex[Mesh->Face[i].f1].y, Mesh->Vertex[Mesh->Face[i].f1].z);
				glNormal3d(Mesh->VertexNormal[Mesh->Face[i].f2].x, Mesh->VertexNormal[Mesh->Face[i].f2].y, Mesh->VertexNormal[Mesh->Face[i].f2].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f2].x, Mesh->Vertex[Mesh->Face[i].f2].y, Mesh->Vertex[Mesh->Face[i].f2].z);
				glNormal3d(Mesh->VertexNormal[Mesh->Face[i].f3].x, Mesh->VertexNormal[Mesh->Face[i].f3].y, Mesh->VertexNormal[Mesh->Face[i].f3].z);//������
				glVertex3d(Mesh->Vertex[Mesh->Face[i].f3].x, Mesh->Vertex[Mesh->Face[i].f3].y, Mesh->Vertex[Mesh->Face[i].f3].z);
				glEnd();
			}
		}
	}
}
void OpenGlWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}
void OpenGlWidget::mouseMoveEvent(QMouseEvent *event)
{
	GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
	GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();
	if (event->buttons() & Qt::LeftButton){
		rotationX += 180 * dy;
		rotationY += 180 * dx;
		updateGL();
	}
	else if (event->buttons() & Qt::RightButton){
		rotationX += 180 * dy;
		rotationZ += 180 * dx;
		updateGL();
	}
	lastPos = event->pos();
}
void OpenGlWidget::wheelEvent(QWheelEvent *event)
{
	if (event->delta() > 0)
	{
		cameraloc = cameraloc + diagonal_length / 5;
		updateGL();
	}
	else if (event->delta() < 0)
	{
		cameraloc = cameraloc - diagonal_length / 5;
		updateGL();
	}
}