SCARA Robot Control System (Qt GUI + Microcontroller)

This repository contains a Qt-based desktop GUI and microcontroller firmware for controlling a SCARA robot arm via serial communication.

The system allows real-time visualization, Cartesian control (X–Y–Z), manual jogging, and motion sequencing of a SCARA robot.

.
├── SCARA/                          # Microcontroller firmware (robot-side)
│   └── (master)
|   └── (slave 1)
|   └──(slave 2)
│
├── build/                          # Qt build directory (generated)
│   └── Desktop_Qt_6_9_3_MinGW_64-bit-Debug
│
├── main.cpp                        # Qt application entry point
├── mainwindow.h                    # Main window header
├── mainwindow.cpp                  # Main window logic
├── mainwindow.ui                   # Qt Designer UI layout
├── qeqwewq.pro                     # Qt project file
├── image.png                       # GUI preview / asset
├── .gitignore
└── README.md

Features

Real-time 2D SCARA robot visualization

Serial communication (COM port & baud rate selection)

Cartesian control (X, Y, Z in mm)

Manual jog control (X+/X−, Y+/Y−)

Gripper control (%)

Save & execute motion sequences

Technologies

Qt 6

C++

Qt Widgets

Qt Serial Port

Requirements
PC (GUI)

Qt 6.9.3 or newer

MinGW 64-bit (Windows)

Qt Creator

Robot Hardware

SCARA robot (2-DOF + Z axis)

Arduino Mega or compatible MCU

Stepper motor drivers (TB6600 / TMC series)

USB serial connection
