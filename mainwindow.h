#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QSerialPort>
#include <QThread>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCalculateIK();
    void onSavePosition();
    void onLoadPosition();
    void onRunSequence();
    void onConnectSerial();
    void onSerialDataReceived();
    void updateAvailablePorts();
    void testSerialConnection();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QSerialPort *serialPort;
    bool isConnected;

    // Robot parameters
    double L1 = 232.0;
    double L2 = 180.0;

    // Current joint angles
    double theta1 = 0.0;
    double theta2 = 0.0;
    double theta3 = 0.0;

    // Saved positions
    struct Position {
        double x, y, z;
        double t1, t2;
        QString name;
    };
    QVector<Position> savedPositions;

    // IK calculations
    bool calculateInverseKinematics(double x, double y, double& t1, double& t2);
    void calculateForwardKinematics(double t1, double t2, double& x, double& y);
    void updateVisualization();
    void drawRobot(double t1, double t2);
    void updateStatusLabels();
    void loadTableData();
    void sendSerialData(double t1, double t2);
    double roundToOneDecimal(double value);
};

#endif // MAINWINDOW_H
