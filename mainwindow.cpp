#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QTimer>
#include <QEventLoop>
#include <QSerialPortInfo>
#include <QDebug>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Apply Modern Dark Theme Stylesheet
    QString styleSheet = R"(
MainWindow {
    background-color: #0f172a;
}

QWidget {
    background-color: #0f172a;
    color: #e2e8f0;
}

QGroupBox {
    color: #0f172a;
    background-color: #1e293b;
    border: 2px solid #334155;
    border-radius: 8px;
    margin-top: 1ex;
    font-weight: bold;
    padding-top: 10px;
}

QGroupBox::title {
    subcontrol-origin: margin;
    left: 10px;
    padding: 0 3px 0 3px;
    color: #38bdf8;
}

QLabel {
    color: #e2e8f0;
    background-color: transparent;
}

QPushButton {
    background-color: #0ea5e9;
    color: white;
    border: none;
    border-radius: 6px;
    padding: 8px;
    font-weight: bold;
    font-size: 12px;
}

QPushButton:hover {
    background-color: #0284c7;
}

QPushButton:pressed {
    background-color: #0369a1;
}

#Connect {
    background-color: #06b6d4;
    min-height: 35px;
    font-size: 13px;
}

#Connect:hover {
    background-color: #0891b2;
}

#saveButton {
    background-color: #10b981;
    min-height: 32px;
}

#saveButton:hover {
    background-color: #059669;
}

#loadButton {
    background-color: #3b82f6;
    min-height: 32px;
}

#loadButton:hover {
    background-color: #2563eb;
}

#runButton {
    background-color: #f59e0b;
    min-height: 50px;
    font-size: 14px;
    font-weight: bold;
}

#runButton:hover {
    background-color: #d97706;
}

#pushButton_2, #pushButton_3, #pushButton_4, #pushButton_5 {
    background-color: #8b5cf6;
    min-width: 60px;
    min-height: 60px;
    font-weight: bold;
}

#pushButton_2:hover, #pushButton_3:hover, #pushButton_4:hover, #pushButton_5:hover {
    background-color: #7c3aed;
}

QSpinBox, QDoubleSpinBox {
    background-color: #1e293b;
    color: #e2e8f0;
    border: 2px solid #475569;
    border-radius: 4px;
    padding: 5px;
}

QSpinBox:hover, QDoubleSpinBox:hover {
    border: 2px solid #64748b;
}

QComboBox {
    background-color: #1e293b;
    color: #e2e8f0;
    border: 2px solid #475569;
    border-radius: 4px;
    padding: 5px;
    min-height: 30px;
}

QComboBox:hover {
    border: 2px solid #64748b;
}

QComboBox QAbstractItemView {
    background-color: #1e293b;
    color: #e2e8f0;
    selection-background-color: #0ea5e9;
}

QLineEdit {
    background-color: #1e293b;
    color: #e2e8f0;
    border: 2px solid #475569;
    border-radius: 4px;
    padding: 5px;
    font-weight: bold;
}

QLineEdit:hover {
    border: 2px solid #64748b;
}

QTableView {
    background-color: #1e293b;
    gridline-color: #334155;
    color: #e2e8f0;
    border: 2px solid #475569;
    border-radius: 4px;
}

QTableView::item:selected {
    background-color: #0ea5e9;
    color: white;
}

QHeaderView::section {
    background-color: #334155;
    color: #38bdf8;
    padding: 5px;
    border: none;
    font-weight: bold;
}

QGraphicsView {
    background-color: #0f172a;
    border: 2px solid #334155;
    border-radius: 6px;
}

QMenuBar {
    background-color: #1e293b;
    color: #e2e8f0;
}

QStatusBar {
    background-color: #1e293b;
    color: #e2e8f0;
}
)";

    this->setStyleSheet(styleSheet);

    // Initialize serial port
    serialPort = new QSerialPort(this);
    isConnected = false;

    // Setup graphics scene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::white));

    // Setup COM ports in dropdown
    for (const auto &info : QSerialPortInfo::availablePorts()) {
        ui->Com_port->addItem(info.portName());
    }

    // Setup baud rates
    ui->baudrate_port->addItem("9600");
    ui->baudrate_port->addItem("115200");
    ui->baudrate_port->addItem("57600");
    ui->baudrate_port->setCurrentText("9600");

    // Setup table for saved positions
    QStandardItemModel *model = new QStandardItemModel(0, 5, this);
    model->setHorizontalHeaderLabels({"Name", "X (mm)", "Y (mm)", "Z (°)", "Status"});
    ui->tableView->setModel(model);

    // Connect position control signals
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onCalculateIK);
    connect(ui->spinBox_2, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onCalculateIK);
    connect(ui->spinBox_3, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int) {
        theta3 = ui->spinBox_3->value();
        updateStatusLabels();
        updateVisualization();
    });

    // Connect manual control buttons
    connect(ui->pushButton_5, &QPushButton::clicked, this, [this]() {
        ui->spinBox_2->setValue(ui->spinBox_2->value() + 10);
    });
    connect(ui->pushButton_2, &QPushButton::clicked, this, [this]() {
        ui->spinBox->setValue(ui->spinBox->value() - 10);
    });
    connect(ui->pushButton_4, &QPushButton::clicked, this, [this]() {
        ui->spinBox->setValue(ui->spinBox->value() + 10);
    });
    connect(ui->pushButton_3, &QPushButton::clicked, this, [this]() {
        ui->spinBox_2->setValue(ui->spinBox_2->value() - 10);
    });

    // Connect save/load/run signals
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::onSavePosition);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::onLoadPosition);
    connect(ui->runButton, &QPushButton::clicked, this, &MainWindow::onRunSequence);

    // Connect serial
    connect(ui->Connect, &QPushButton::clicked, this, &MainWindow::onConnectSerial);
    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::onSerialDataReceived);

    // Timer untuk update port secara realtime
    QTimer *portUpdateTimer = new QTimer(this);
    connect(portUpdateTimer, &QTimer::timeout, this, &MainWindow::updateAvailablePorts);
    portUpdateTimer->start(1000); // Update setiap 1 detik

    updateVisualization();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::calculateInverseKinematics(double x, double y, double& t1, double& t2)
{
    double D = (x*x + y*y - L1*L1 - L2*L2) / (2.0 * L1 * L2);

    if (std::abs(D) > 1.0) {
        return false;
    }

    double t2_rad = atan2(-sqrt(1.0 - D*D), D);
    t2 = t2_rad * 180.0 / M_PI;

    double A = L1 + L2 * cos(t2_rad);
    double B = L2 * sin(t2_rad);
    double t1_rad = atan2(y, x) - atan2(B, A);
    t1 = t1_rad * 180.0 / M_PI;

    while (t1 > 180.0) t1 -= 360.0;
    while (t1 < -180.0) t1 += 360.0;
    while (t2 > 180.0) t2 -= 360.0;
    while (t2 < -180.0) t2 += 360.0;

    return true;
}

void MainWindow::calculateForwardKinematics(double t1, double t2, double& x, double& y)
{
    double t1_rad = t1 * M_PI / 180.0;
    double t2_rad = t2 * M_PI / 180.0;

    x = L1 * cos(t1_rad) + L2 * cos(t1_rad + t2_rad);
    y = L1 * sin(t1_rad) + L2 * sin(t1_rad + t2_rad);
}

double MainWindow::roundToOneDecimal(double value)
{
    return round(value * 10.0) / 10.0;
}

void MainWindow::sendSerialData(double t1, double t2)
{
    if (!isConnected || !serialPort->isOpen()) {
        qDebug() << "Serial not connected or not open!";
        return;
    }

    // Round to 1 decimal place
    double t1_rounded = roundToOneDecimal(t1);
    double t2_rounded = roundToOneDecimal(t2);

    // Validasi nilai - pastikan tidak NaN atau Inf
    if (std::isnan(t1_rounded) || std::isinf(t1_rounded)) {
        qDebug() << "ERROR: t1 is NaN or Inf, value:" << t1;
        return;
    }
    if (std::isnan(t2_rounded) || std::isinf(t2_rounded)) {
        qDebug() << "ERROR: t2 is NaN or Inf, value:" << t2;
        return;
    }

    // Format dengan benar: "90.0,90.0\n"
    QString data = QString("%1,%2\n").arg(t1_rounded, 0, 'f', 1).arg(t2_rounded, 0, 'f', 1);

    qDebug() << "Kirim ke Serial:" << data.trimmed();
    qDebug() << "Panjang data:" << data.length() << "bytes";
    qDebug() << "Hex:" << data.toUtf8().toHex();

    // Tunggu buffer siap
    if (!serialPort->waitForBytesWritten(1000)) {
        qDebug() << "WARNING: Serial write timeout!";
    }

    // Kirim data
    qint64 bytesWritten = serialPort->write(data.toUtf8());

    if (bytesWritten == -1) {
        qDebug() << "ERROR: Failed to write to serial port!";
        qDebug() << "Error:" << serialPort->errorString();
    } else {
        qDebug() << "Berhasil kirim:" << bytesWritten << "bytes";
    }

    // Flush buffer untuk memastikan data langsung terkirim
    serialPort->flush();
}

void MainWindow::onConnectSerial()
{
    if (!isConnected) {
        QString portName = ui->Com_port->currentText();
        int baudRate = ui->baudrate_port->currentText().toInt();

        serialPort->setPortName(portName);
        serialPort->setBaudRate(baudRate);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);

        if (serialPort->open(QIODevice::ReadWrite)) {
            isConnected = true;
            ui->lineEdit->setText(QString("Connected to %1 at %2 baud").arg(portName).arg(baudRate));
            ui->Connect->setText("Disconnect");
            ui->Com_port->setEnabled(false);
            ui->baudrate_port->setEnabled(false);

            sendSerialData(theta1, theta2);

            QMessageBox::information(this, "Connected",
                                     QString("Connected to %1 at %2 baud rate").arg(portName).arg(baudRate));
        } else {
            QMessageBox::critical(this, "Error",
                                  QString("Failed to open port %1").arg(portName));
        }
    } else {
        if (serialPort->isOpen()) {
            serialPort->close();
        }
        isConnected = false;
        ui->lineEdit->setText("Disconnected");
        ui->Connect->setText("Connect");
        ui->Com_port->setEnabled(true);
        ui->baudrate_port->setEnabled(true);

        QMessageBox::information(this, "Disconnected", "Serial port closed");
    }
}

void MainWindow::onSerialDataReceived()
{
    if (!serialPort->isOpen()) {
        return;
    }

    QByteArray rawData = serialPort->readAll();
    QString receivedData = QString::fromUtf8(rawData).trimmed();

    qDebug() << "=== SERIAL DATA RECEIVED ===";
    qDebug() << "Raw bytes:" << rawData.length();
    qDebug() << "Hex:" << rawData.toHex();
    qDebug() << "Text:" << receivedData;

    // Validasi data
    if (receivedData.isEmpty()) {
        qDebug() << "WARNING: Received empty data";
        return;
    }

    // Coba parse jika format adalah "value1,value2"
    if (receivedData.contains(",")) {
        QStringList parts = receivedData.split(",");
        if (parts.length() >= 2) {
            bool ok1, ok2;
            double feedback1 = parts[0].trimmed().toDouble(&ok1);
            double feedback2 = parts[1].trimmed().toDouble(&ok2);

            if (ok1 && ok2) {
                qDebug() << "Parsed feedback: T1=" << feedback1 << "T2=" << feedback2;

                // Update label dengan feedback
                ui->labelTheta1->setText(QString("Θ1: %1° (Feedback: %2°)")
                                             .arg(theta1, 0, 'f', 2).arg(feedback1, 0, 'f', 2));
                ui->labelTheta2->setText(QString("Θ2: %1° (Feedback: %2°)")
                                             .arg(theta2, 0, 'f', 2).arg(feedback2, 0, 'f', 2));
            } else {
                qDebug() << "ERROR: Failed to parse feedback values";
                qDebug() << "Part 0:" << parts[0] << "parsed ok:" << ok1;
                qDebug() << "Part 1:" << parts[1] << "parsed ok:" << ok2;
            }
        }
    } else if (receivedData == "OK" || receivedData == "ACK") {
        qDebug() << "Received ACK from device";
    } else {
        qDebug() << "Received unknown data:" << receivedData;
    }

    qDebug() << "========================\n";
}

void MainWindow::onCalculateIK()
{
    double x = ui->spinBox->value();
    double y = ui->spinBox_2->value();

    qDebug() << "\n=== CALCULATE IK ===";
    qDebug() << "Target Position: X=" << x << "Y=" << y;

    if (calculateInverseKinematics(x, y, theta1, theta2)) {
        qDebug() << "IK Success: T1=" << theta1 << "T2=" << theta2;

        updateStatusLabels();
        updateVisualization();

        // Kirim ke serial dengan delay kecil
        QTimer::singleShot(50, this, [this]() {
            sendSerialData(theta1, theta2);
        });
    } else {
        qDebug() << "IK FAILED: Position unreachable!";
        qDebug() << "Distance:" << sqrt(x*x + y*y) << "mm";
        qDebug() << "Max reach:" << (L1 + L2) << "mm";
        qDebug() << "Min reach:" << (L1 - L2) << "mm";

        ui->labelTheta1->setText("Theta1: UNREACHABLE");
        ui->labelTheta2->setText("Theta2: UNREACHABLE");
    }
    qDebug() << "==================\n";
}

void MainWindow::updateStatusLabels()
{
    ui->labelTheta1->setText(QString("Theta1: %1 deg").arg(theta1, 0, 'f', 2));
    ui->labelTheta2->setText(QString("Theta2: %1 deg").arg(theta2, 0, 'f', 2));
    ui->labelOrientationZ->setText(QString("Z: %1 deg").arg(theta3, 0, 'f', 1));

    double x_fk, y_fk;
    calculateForwardKinematics(theta1, theta2, x_fk, y_fk);

    ui->labelGripper->setText(QString("EE: X=%.1f Y=%.1f mm").arg(x_fk, 0, 'f', 1).arg(y_fk, 0, 'f', 1));
}

void MainWindow::updateVisualization()
{
    scene->clear();

    QPen gridPen(Qt::lightGray);
    for (int i = -500; i <= 500; i += 100) {
        scene->addLine(i, -500, i, 500, gridPen);
        scene->addLine(-500, i, 500, i, gridPen);
    }

    QPen workspacePen(Qt::blue);
    workspacePen.setStyle(Qt::DashLine);
    scene->addEllipse(-L1-L2, -L1-L2, 2*(L1+L2), 2*(L1+L2), workspacePen);
    scene->addEllipse(-(L1-L2), -(L1-L2), 2*(L1-L2), 2*(L1-L2), workspacePen);

    drawRobot(theta1, theta2);
}

void MainWindow::drawRobot(double t1, double t2)
{
    double t1_rad = t1 * M_PI / 180.0;
    double t2_rad = t2 * M_PI / 180.0;

    double base_x = 0, base_y = 0;
    double j1_x = L1 * cos(t1_rad);
    double j1_y = L1 * sin(t1_rad);
    double ee_x = j1_x + L2 * cos(t1_rad + t2_rad);
    double ee_y = j1_y + L2 * sin(t1_rad + t2_rad);

    QPen linkPen(Qt::darkBlue);
    linkPen.setWidth(8);
    scene->addLine(base_x, base_y, j1_x, j1_y, linkPen);
    scene->addLine(j1_x, j1_y, ee_x, ee_y, linkPen);

    QPen basePen(Qt::red);
    scene->addEllipse(base_x - 8, base_y - 8, 16, 16, basePen, QBrush(Qt::red));

    QPen j1Pen(QColor(220, 140, 0));
    scene->addEllipse(j1_x - 6, j1_y - 6, 12, 12, j1Pen, QBrush(QColor(255, 165, 0)));

    QPen eePen(QColor(184, 134, 11));
    scene->addEllipse(ee_x - 6, ee_y - 6, 12, 12, eePen, QBrush(QColor(255, 255, 0)));

    double ee_angle = (t1 + t2 + theta3) * M_PI / 180.0;
    double arrow_len = 30;
    double arrow_x = ee_x + arrow_len * cos(ee_angle);
    double arrow_y = ee_y + arrow_len * sin(ee_angle);
    QPen arrowPen(Qt::green);
    arrowPen.setWidth(3);
    scene->addLine(ee_x, ee_y, arrow_x, arrow_y, arrowPen);

    QGraphicsTextItem *text = scene->addText(QString("T1=%1").arg(t1, 0, 'f', 1));
    text->setPos(-100, -150);

    text = scene->addText(QString("T2=%1").arg(t2, 0, 'f', 1));
    text->setPos(50, -150);

    text = scene->addText(QString("(%1,%2)").arg(ee_x, 0, 'f', 0).arg(ee_y, 0, 'f', 0));
    text->setPos(ee_x + 15, ee_y + 15);
}

void MainWindow::onSavePosition()
{
    double x_fk, y_fk;
    calculateForwardKinematics(theta1, theta2, x_fk, y_fk);

    Position pos;
    pos.x = x_fk;
    pos.y = y_fk;
    pos.z = theta3;
    pos.t1 = theta1;
    pos.t2 = theta2;
    pos.name = QString("Pos_%1").arg(savedPositions.size() + 1);

    savedPositions.append(pos);
    loadTableData();
}

void MainWindow::onLoadPosition()
{
    int row = ui->tableView->currentIndex().row();
    if (row < 0 || row >= savedPositions.size()) {
        QMessageBox::warning(this, "Error", "Select a position first!");
        return;
    }

    Position pos = savedPositions[row];
    theta1 = pos.t1;
    theta2 = pos.t2;
    theta3 = pos.z;

    ui->spinBox->blockSignals(true);
    ui->spinBox_2->blockSignals(true);
    ui->spinBox_3->blockSignals(true);

    ui->spinBox->setValue((int)pos.x);
    ui->spinBox_2->setValue((int)pos.y);
    ui->spinBox_3->setValue((int)pos.z);

    ui->spinBox->blockSignals(false);
    ui->spinBox_2->blockSignals(false);
    ui->spinBox_3->blockSignals(false);

    updateStatusLabels();
    updateVisualization();
    sendSerialData(theta1, theta2);
}

void MainWindow::onRunSequence()
{
    if (savedPositions.isEmpty()) {
        QMessageBox::warning(this, "Error", "No saved positions!");
        return;
    }

    for (int i = 0; i < savedPositions.size(); i++) {
        Position pos = savedPositions[i];
        theta1 = pos.t1;
        theta2 = pos.t2;
        theta3 = pos.z;

        updateStatusLabels();
        updateVisualization();
        sendSerialData(theta1, theta2);

        QCoreApplication::processEvents();

        QEventLoop loop;
        QTimer::singleShot(5000, &loop, &QEventLoop::quit);
        loop.exec();
    }

    QMessageBox::information(this, "Done", "Sequence complete!");
}

void MainWindow::loadTableData()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView->model());
    model->removeRows(0, model->rowCount());

    for (int i = 0; i < savedPositions.size(); i++) {
        Position pos = savedPositions[i];
        QList<QStandardItem*> row;
        row << new QStandardItem(pos.name);
        row << new QStandardItem(QString::number(pos.x, 'f', 1));
        row << new QStandardItem(QString::number(pos.y, 'f', 1));
        row << new QStandardItem(QString::number(pos.z, 'f', 1));
        row << new QStandardItem("OK");
        model->appendRow(row);
    }
}

void MainWindow::updateAvailablePorts()
{
    // Jangan update jika sedang terhubung
    if (isConnected) {
        return;
    }

    // Dapatkan daftar port yang tersedia
    QStringList currentPorts;
    for (const auto &info : QSerialPortInfo::availablePorts()) {
        currentPorts << info.portName();
    }

    // Dapatkan daftar port yang ada di combobox
    QStringList comboBoxPorts;
    for (int i = 0; i < ui->Com_port->count(); i++) {
        comboBoxPorts << ui->Com_port->itemText(i);
    }

    // Cek apakah ada perubahan
    if (currentPorts != comboBoxPorts) {
        // Simpan port yang dipilih sebelumnya
        QString selectedPort = ui->Com_port->currentText();

        // Hapus semua item
        ui->Com_port->clear();

        // Tambahkan port baru
        for (const QString &port : currentPorts) {
            ui->Com_port->addItem(port);
        }

        // Restore port yang dipilih jika masih tersedia
        int index = ui->Com_port->findText(selectedPort);
        if (index >= 0) {
            ui->Com_port->setCurrentIndex(index);
        }
    }
}

void MainWindow::testSerialConnection()
{
    if (!isConnected) {
        QMessageBox::warning(this, "Error", "Serial not connected!");
        return;
    }

    qDebug() << "\n=== SERIAL TEST ===";

    // Test 1: Kirim nilai tetap
    double testT1 = 45.5;
    double testT2 = 30.2;

    qDebug() << "Test 1: Sending" << testT1 << "," << testT2;
    sendSerialData(testT1, testT2);

    // Test 2: Setelah delay
    QTimer::singleShot(500, this, [this]() {
        qDebug() << "Test 2: Sending 90.0, 90.0";
        sendSerialData(90.0, 90.0);
    });

    // Test 3: Setelah delay lagi
    QTimer::singleShot(1000, this, [this]() {
        qDebug() << "Test 3: Sending 0.1, 0.1";
        sendSerialData(0.1, 0.1);

        qDebug() << "==================\n";

        QMessageBox::information(this, "Serial Test",
                                 "Test data sent!\nCheck debug console for details");
    });
}
