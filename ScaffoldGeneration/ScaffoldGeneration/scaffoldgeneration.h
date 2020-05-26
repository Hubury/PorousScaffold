#ifndef SCAFFOLDGENERATION_H
#define SCAFFOLDGENERATION_H

//#include <QtWidgets/QMainWindow>
//#include "ui_scaffoldgeneration.h"

#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QButtonGroup>
#include <QRadioButton>
#include "OpenGlWidget.h"
#include <qaction.h>
#include <qtoolbar.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qstatusbar.h>
#include <QInputDialog>
#include <QDebug>
#include <QPushButton>

class ScaffoldGeneration : public QMainWindow
{
	Q_OBJECT

public:
	ScaffoldGeneration(QWidget *parent = 0);
	~ScaffoldGeneration();
private slots://�ۺ���
	void fileOpen();//��ͼ���ļ�
	void fileSave();//��ͼ���ļ�
	void PointsPaint();
	void WirePaint();
	void FlatPaint();
	void FlatlinesPaint();
	void SmoothPaint();
	//void pushButton_clicked();
	//void TPMS_type();
	//void structure_type();

private:
	int type_TPMS;//TPMS���ͣ�P,G,D,IWP��
	int type_structure;//�ṹ���ͣ�Rod,Pore,Sheet��
	QString rsrcPath;//��ǰ·��
	OpenGlWidget *glwidget;
	QWidget *centralWidget;
	QGridLayout *centralLayout;
	QMenu *FileMenu;//�ļ��˵�	
	QMenu *RenderMenu;//�ļ��˵�
	QToolBar *fileToolBar;//������
	QToolBar *SeeToolBar;

	QAction *fileopenAct;//�������ļ�����
	QAction *filesaveAct;//���������ļ�����

	QAction *PointsAct;
	QAction *WireAct;
	QAction *FlatAct;
	QAction *FlatlinesAct;
	QAction *SmoothAct;

	////��������
	//QDialog* dlg;
	//QPushButton *btn;

	//QButtonGroup *TPMSGroup;
	//QRadioButton *PradioButton;
	//QRadioButton *GradioButton;
	//QRadioButton *DradioButton;
	//QRadioButton *IWPradioButton;

	//QButtonGroup *StructureGroup;
	//QRadioButton *RodradioButton;
	//QRadioButton *PoreradioButton;
	//QRadioButton *SheetradioButton;

	void createActions();//��������
	void createWidgets();//�������
	void createMenus();//�����˵�
	void createToolBars();//����������
	void createStatusBar();//����״̬��
	//void creatTPMSDialog();//��������

	void type_choose();
};
#endif // SCAFFOLDGENERATION_H
