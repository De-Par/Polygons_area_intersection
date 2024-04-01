/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtCharts"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QListView *listView;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QPushButton *insertButton;
    QPushButton *removeButton;
    QPushButton *editButton;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QChartView *graphicsView;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *plotButton;
    QLabel *areaText;
    QSpacerItem *horizontalSpacer_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(308, 430);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(16777215, 200));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        listView = new QListView(widget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setMinimumSize(QSize(100, 100));
        listView->setMaximumSize(QSize(130, 130));
        listView->setLineWidth(2);

        horizontalLayout->addWidget(listView);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        insertButton = new QPushButton(widget);
        insertButton->setObjectName(QString::fromUtf8("insertButton"));
        insertButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(insertButton);

        removeButton = new QPushButton(widget);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(removeButton);

        editButton = new QPushButton(widget);
        editButton->setObjectName(QString::fromUtf8("editButton"));
        editButton->setEnabled(true);
        editButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(editButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(1, 2);

        verticalLayout->addWidget(widget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        graphicsView = new QChartView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(200, 200));
        graphicsView->setMaximumSize(QSize(1200, 1800));

        horizontalLayout_5->addWidget(graphicsView);

        horizontalSpacer_4 = new QSpacerItem(5, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        plotButton = new QPushButton(centralwidget);
        plotButton->setObjectName(QString::fromUtf8("plotButton"));
        plotButton->setStyleSheet(QString::fromUtf8("QPushButton#plotButton {\n"
"    background-color: rgb(87, 60, 250);\n"
"    border-radius: 6px;\n"
"    font: bold 12px;\n"
"    min-width: 4em;\n"
"    padding: 3px;\n"
"}\n"
"QPushButton#plotButton:pressed {\n"
"    background-color: rgb(100, 89, 250);\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout_3->addWidget(plotButton);

        areaText = new QLabel(centralwidget);
        areaText->setObjectName(QString::fromUtf8("areaText"));

        horizontalLayout_3->addWidget(areaText);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 308, 33));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Polygons", nullptr));
        insertButton->setText(QCoreApplication::translate("MainWindow", "Insert ", nullptr));
        removeButton->setText(QCoreApplication::translate("MainWindow", "Remove ", nullptr));
        editButton->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        plotButton->setText(QCoreApplication::translate("MainWindow", "Plot", nullptr));
        areaText->setText(QCoreApplication::translate("MainWindow", "Area: 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
