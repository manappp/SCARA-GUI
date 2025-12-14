/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QHBoxLayout *mainContentLayout;
    QVBoxLayout *leftColumnLayout;
    QGroupBox *visualizationGroup;
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *graphicsView;
    QLabel *vizLabel;
    QGroupBox *statusGroup;
    QGridLayout *gridLayout_3;
    QLabel *labelTheta1;
    QLabel *labelGripper;
    QLabel *labelOrientationZ;
    QLabel *labelTheta2;
    QVBoxLayout *middleColumnLayout;
    QGroupBox *serialGroup;
    QGridLayout *gridLayout;
    QLabel *label_port;
    QComboBox *Com_port;
    QLabel *label_baud;
    QComboBox *baudrate_port;
    QPushButton *Connect;
    QLineEdit *lineEdit;
    QGroupBox *positionControlGroup;
    QGridLayout *gridLayout_2;
    QLabel *label_x;
    QSpinBox *spinBox;
    QLabel *label_y;
    QSpinBox *spinBox_2;
    QLabel *label_z;
    QSpinBox *spinBox_3;
    QLabel *label_gripper;
    QSpinBox *spinBox_4;
    QLabel *label_manual;
    QPushButton *pushButton_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QLabel *label_center;
    QGroupBox *savedPositionsGroup;
    QVBoxLayout *verticalLayout_3;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *runButton;
    QLabel *label_runInfo;
    QVBoxLayout *rightColumnLayout;
    QWidget *layoutWidget_2;
    QVBoxLayout *headerLayout;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1440, 943);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(1440, 900));
        centralwidget->setMaximumSize(QSize(1440, 900));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 30, 1431, 771));
        mainContentLayout = new QHBoxLayout(layoutWidget);
        mainContentLayout->setSpacing(12);
        mainContentLayout->setObjectName("mainContentLayout");
        mainContentLayout->setContentsMargins(0, 0, 0, 0);
        leftColumnLayout = new QVBoxLayout();
        leftColumnLayout->setSpacing(12);
        leftColumnLayout->setObjectName("leftColumnLayout");
        visualizationGroup = new QGroupBox(layoutWidget);
        visualizationGroup->setObjectName("visualizationGroup");
        verticalLayout_2 = new QVBoxLayout(visualizationGroup);
        verticalLayout_2->setObjectName("verticalLayout_2");
        graphicsView = new QGraphicsView(visualizationGroup);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setMinimumSize(QSize(550, 550));
        graphicsView->setMaximumSize(QSize(450, 450));

        verticalLayout_2->addWidget(graphicsView);

        vizLabel = new QLabel(visualizationGroup);
        vizLabel->setObjectName("vizLabel");
        vizLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        vizLabel->setProperty("subtitle", QVariant(true));

        verticalLayout_2->addWidget(vizLabel);


        leftColumnLayout->addWidget(visualizationGroup);

        statusGroup = new QGroupBox(layoutWidget);
        statusGroup->setObjectName("statusGroup");
        gridLayout_3 = new QGridLayout(statusGroup);
        gridLayout_3->setObjectName("gridLayout_3");
        labelTheta1 = new QLabel(statusGroup);
        labelTheta1->setObjectName("labelTheta1");
        labelTheta1->setProperty("status", QVariant(true));

        gridLayout_3->addWidget(labelTheta1, 0, 0, 1, 1);

        labelGripper = new QLabel(statusGroup);
        labelGripper->setObjectName("labelGripper");
        labelGripper->setProperty("status", QVariant(true));

        gridLayout_3->addWidget(labelGripper, 1, 1, 1, 1);

        labelOrientationZ = new QLabel(statusGroup);
        labelOrientationZ->setObjectName("labelOrientationZ");
        labelOrientationZ->setProperty("status", QVariant(true));

        gridLayout_3->addWidget(labelOrientationZ, 1, 0, 1, 1);

        labelTheta2 = new QLabel(statusGroup);
        labelTheta2->setObjectName("labelTheta2");
        labelTheta2->setProperty("status", QVariant(true));

        gridLayout_3->addWidget(labelTheta2, 0, 1, 1, 1);


        leftColumnLayout->addWidget(statusGroup);


        mainContentLayout->addLayout(leftColumnLayout);

        middleColumnLayout = new QVBoxLayout();
        middleColumnLayout->setSpacing(12);
        middleColumnLayout->setObjectName("middleColumnLayout");
        serialGroup = new QGroupBox(layoutWidget);
        serialGroup->setObjectName("serialGroup");
        gridLayout = new QGridLayout(serialGroup);
        gridLayout->setObjectName("gridLayout");
        label_port = new QLabel(serialGroup);
        label_port->setObjectName("label_port");

        gridLayout->addWidget(label_port, 0, 0, 1, 1);

        Com_port = new QComboBox(serialGroup);
        Com_port->setObjectName("Com_port");

        gridLayout->addWidget(Com_port, 0, 1, 1, 1);

        label_baud = new QLabel(serialGroup);
        label_baud->setObjectName("label_baud");

        gridLayout->addWidget(label_baud, 1, 0, 1, 1);

        baudrate_port = new QComboBox(serialGroup);
        baudrate_port->setObjectName("baudrate_port");

        gridLayout->addWidget(baudrate_port, 1, 1, 1, 1);

        Connect = new QPushButton(serialGroup);
        Connect->setObjectName("Connect");

        gridLayout->addWidget(Connect, 2, 0, 1, 2);

        lineEdit = new QLineEdit(serialGroup);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit->setReadOnly(true);

        gridLayout->addWidget(lineEdit, 3, 0, 1, 2);


        middleColumnLayout->addWidget(serialGroup);

        positionControlGroup = new QGroupBox(layoutWidget);
        positionControlGroup->setObjectName("positionControlGroup");
        gridLayout_2 = new QGridLayout(positionControlGroup);
        gridLayout_2->setObjectName("gridLayout_2");
        label_x = new QLabel(positionControlGroup);
        label_x->setObjectName("label_x");

        gridLayout_2->addWidget(label_x, 0, 0, 1, 1);

        spinBox = new QSpinBox(positionControlGroup);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimumSize(QSize(0, 40));
        spinBox->setMinimum(-1000);
        spinBox->setMaximum(1000);

        gridLayout_2->addWidget(spinBox, 0, 1, 1, 3);

        label_y = new QLabel(positionControlGroup);
        label_y->setObjectName("label_y");

        gridLayout_2->addWidget(label_y, 1, 0, 1, 1);

        spinBox_2 = new QSpinBox(positionControlGroup);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setMinimumSize(QSize(0, 40));
        spinBox_2->setMinimum(-1000);
        spinBox_2->setMaximum(1000);

        gridLayout_2->addWidget(spinBox_2, 1, 1, 1, 3);

        label_z = new QLabel(positionControlGroup);
        label_z->setObjectName("label_z");

        gridLayout_2->addWidget(label_z, 2, 0, 1, 1);

        spinBox_3 = new QSpinBox(positionControlGroup);
        spinBox_3->setObjectName("spinBox_3");
        spinBox_3->setMinimumSize(QSize(0, 40));
        spinBox_3->setMinimum(-100);
        spinBox_3->setMaximum(100);

        gridLayout_2->addWidget(spinBox_3, 2, 1, 1, 3);

        label_gripper = new QLabel(positionControlGroup);
        label_gripper->setObjectName("label_gripper");

        gridLayout_2->addWidget(label_gripper, 3, 0, 1, 1);

        spinBox_4 = new QSpinBox(positionControlGroup);
        spinBox_4->setObjectName("spinBox_4");
        spinBox_4->setMinimumSize(QSize(0, 40));
        spinBox_4->setMaximum(360);

        gridLayout_2->addWidget(spinBox_4, 3, 1, 1, 3);

        label_manual = new QLabel(positionControlGroup);
        label_manual->setObjectName("label_manual");
        label_manual->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_manual, 4, 0, 1, 4);

        pushButton_5 = new QPushButton(positionControlGroup);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(60, 60));
        pushButton_5->setMaximumSize(QSize(60, 60));

        gridLayout_2->addWidget(pushButton_5, 5, 1, 1, 1);

        pushButton_2 = new QPushButton(positionControlGroup);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(60, 60));
        pushButton_2->setMaximumSize(QSize(60, 60));

        gridLayout_2->addWidget(pushButton_2, 6, 0, 1, 1);

        pushButton_4 = new QPushButton(positionControlGroup);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(60, 60));
        pushButton_4->setMaximumSize(QSize(60, 60));

        gridLayout_2->addWidget(pushButton_4, 6, 2, 1, 1);

        pushButton_3 = new QPushButton(positionControlGroup);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(60, 60));
        pushButton_3->setMaximumSize(QSize(60, 60));

        gridLayout_2->addWidget(pushButton_3, 7, 1, 1, 1);

        label_center = new QLabel(positionControlGroup);
        label_center->setObjectName("label_center");
        label_center->setStyleSheet(QString::fromUtf8("font-size: 24px; color: #64748b;"));
        label_center->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_center, 6, 1, 1, 1);


        middleColumnLayout->addWidget(positionControlGroup);


        mainContentLayout->addLayout(middleColumnLayout);

        savedPositionsGroup = new QGroupBox(layoutWidget);
        savedPositionsGroup->setObjectName("savedPositionsGroup");
        verticalLayout_3 = new QVBoxLayout(savedPositionsGroup);
        verticalLayout_3->setObjectName("verticalLayout_3");
        tableView = new QTableView(savedPositionsGroup);
        tableView->setObjectName("tableView");
        tableView->setMinimumSize(QSize(360, 0));
        tableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_3->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        saveButton = new QPushButton(savedPositionsGroup);
        saveButton->setObjectName("saveButton");

        horizontalLayout->addWidget(saveButton);

        loadButton = new QPushButton(savedPositionsGroup);
        loadButton->setObjectName("loadButton");

        horizontalLayout->addWidget(loadButton);


        verticalLayout_3->addLayout(horizontalLayout);

        runButton = new QPushButton(savedPositionsGroup);
        runButton->setObjectName("runButton");
        runButton->setMinimumSize(QSize(0, 50));

        verticalLayout_3->addWidget(runButton);

        label_runInfo = new QLabel(savedPositionsGroup);
        label_runInfo->setObjectName("label_runInfo");
        label_runInfo->setWordWrap(true);
        label_runInfo->setProperty("subtitle", QVariant(true));

        verticalLayout_3->addWidget(label_runInfo);


        mainContentLayout->addWidget(savedPositionsGroup);

        rightColumnLayout = new QVBoxLayout();
        rightColumnLayout->setSpacing(12);
        rightColumnLayout->setObjectName("rightColumnLayout");

        mainContentLayout->addLayout(rightColumnLayout);

        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(0, 0, 367, 36));
        headerLayout = new QVBoxLayout(layoutWidget_2);
        headerLayout->setSpacing(2);
        headerLayout->setObjectName("headerLayout");
        headerLayout->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(layoutWidget_2);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setProperty("heading", QVariant(true));

        headerLayout->addWidget(titleLabel);

        subtitleLabel = new QLabel(layoutWidget_2);
        subtitleLabel->setObjectName("subtitleLabel");
        subtitleLabel->setProperty("subtitle", QVariant(true));

        headerLayout->addWidget(subtitleLabel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1440, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        visualizationGroup->setTitle(QCoreApplication::translate("MainWindow", "\360\237\223\212 Robot Visualization", nullptr));
        vizLabel->setText(QCoreApplication::translate("MainWindow", "2D Top-Down View \342\200\242 Real-time Forward Kinematics", nullptr));
        statusGroup->setTitle(QCoreApplication::translate("MainWindow", "\360\237\216\257 Position & Orientation", nullptr));
        labelTheta1->setText(QCoreApplication::translate("MainWindow", "\316\2301: 0\302\260 (Feedback: 0\302\260)", nullptr));
        labelGripper->setText(QCoreApplication::translate("MainWindow", "Gripper: 0%", nullptr));
        labelOrientationZ->setText(QCoreApplication::translate("MainWindow", "Z: 0\302\260", nullptr));
        labelTheta2->setText(QCoreApplication::translate("MainWindow", "\316\2302: 0\302\260 (Feedback: 0\302\260)", nullptr));
        serialGroup->setTitle(QCoreApplication::translate("MainWindow", "\360\237\224\214 Serial Connection", nullptr));
        label_port->setText(QCoreApplication::translate("MainWindow", "COM Port:", nullptr));
        label_baud->setText(QCoreApplication::translate("MainWindow", "Baud Rate:", nullptr));
        Connect->setText(QCoreApplication::translate("MainWindow", "\360\237\224\227 Connect", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "\360\237\224\214 Disconnected", nullptr));
        positionControlGroup->setTitle(QCoreApplication::translate("MainWindow", "\360\237\216\256 XYZ Position Control", nullptr));
        label_x->setText(QCoreApplication::translate("MainWindow", "X (mm):", nullptr));
        label_y->setText(QCoreApplication::translate("MainWindow", "Y (mm):", nullptr));
        label_z->setText(QCoreApplication::translate("MainWindow", "Z (mm):", nullptr));
        label_gripper->setText(QCoreApplication::translate("MainWindow", "Gripper (%):", nullptr));
        label_manual->setText(QCoreApplication::translate("MainWindow", "Manual Control:", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\342\226\262\n"
"Y+", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\342\227\204\n"
"X-", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\342\226\272\n"
"X+", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\342\226\274\n"
"Y-", nullptr));
        label_center->setText(QCoreApplication::translate("MainWindow", "\342\212\225", nullptr));
        savedPositionsGroup->setTitle(QCoreApplication::translate("MainWindow", "\360\237\222\276 Saved Positions", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "\360\237\222\276 Save", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\245 Load", nullptr));
        runButton->setText(QCoreApplication::translate("MainWindow", "\342\226\266\357\270\217 RUN SEQUENCE", nullptr));
        label_runInfo->setText(QCoreApplication::translate("MainWindow", "Save multiple positions, then press RUN to execute them sequentially with 5-second intervals.", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "SCARA Robot Control System", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("MainWindow", "Selective Compliance Assembly Robot Arm - L1=232mm, L2=180mm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
