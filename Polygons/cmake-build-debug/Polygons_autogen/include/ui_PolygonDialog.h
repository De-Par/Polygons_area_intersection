/********************************************************************************
** Form generated from reading UI file 'PolygonDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLYGONDIALOG_H
#define UI_POLYGONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PolygonDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *insertButton;
    QPushButton *removeButton;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *PolygonDialog)
    {
        if (PolygonDialog->objectName().isEmpty())
            PolygonDialog->setObjectName(QString::fromUtf8("PolygonDialog"));
        PolygonDialog->resize(270, 320);
        PolygonDialog->setMaximumSize(QSize(400, 500));
        verticalLayout = new QVBoxLayout(PolygonDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
        label = new QLabel(PolygonDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(PolygonDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        tableWidget = new QTableWidget(PolygonDialog);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setMaximumSize(QSize(400, 500));
        tableWidget->setColumnCount(2);
        tableWidget->horizontalHeader()->setDefaultSectionSize(100);

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        insertButton = new QPushButton(PolygonDialog);
        insertButton->setObjectName(QString::fromUtf8("insertButton"));
        insertButton->setStyleSheet(QString::fromUtf8("QPushButton#insertButton {\n"
"    background-color: rgb(2, 164, 74);\n"
"    border-radius: 6px;\n"
"    font: bold 12px;\n"
"    min-width: 4em;\n"
"    padding: 3px;\n"
"}\n"
"QPushButton#insertButton:pressed {\n"
"    background-color: rgb(1, 199, 91);\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout->addWidget(insertButton);

        removeButton = new QPushButton(PolygonDialog);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setStyleSheet(QString::fromUtf8("QPushButton#removeButton {\n"
"    background-color: rgb(192, 8, 70);\n"
"    border-radius: 6px;\n"
"    font: bold 12px;\n"
"    min-width: 4em;\n"
"    padding: 3px;\n"
"}\n"
"QPushButton#removeButton:pressed {\n"
"    background-color: rgb(218, 10, 81);\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout->addWidget(removeButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2->setContentsMargins(86, -1, -1, -1);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        cancelButton = new QPushButton(PolygonDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setMaximumSize(QSize(64, 16777215));
        cancelButton->setAutoFillBackground(false);

        horizontalLayout_2->addWidget(cancelButton);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(PolygonDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMaximumSize(QSize(64, 16777215));
        pushButton->setAutoFillBackground(false);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton#pushButton {\n"
"    background-color: rgb(87, 60, 250);\n"
"    border-radius: 6px;\n"
"    font: bold 12px;\n"
"    min-width: 4em;\n"
"    padding: 3px;\n"
"}\n"
"QPushButton#pushButton:pressed {\n"
"    background-color: rgb(100, 89, 250);\n"
"    border-style: inset;\n"
"}"));
        pushButton->setCheckable(false);

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(PolygonDialog);

        QMetaObject::connectSlotsByName(PolygonDialog);
    } // setupUi

    void retranslateUi(QDialog *PolygonDialog)
    {
        PolygonDialog->setWindowTitle(QCoreApplication::translate("PolygonDialog", "Create polygon", nullptr));
        label->setText(QCoreApplication::translate("PolygonDialog", "Name:", nullptr));
        insertButton->setText(QCoreApplication::translate("PolygonDialog", "Insert", nullptr));
        removeButton->setText(QCoreApplication::translate("PolygonDialog", "Remove", nullptr));
        cancelButton->setText(QCoreApplication::translate("PolygonDialog", "Cancel", nullptr));
        pushButton->setText(QCoreApplication::translate("PolygonDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PolygonDialog: public Ui_PolygonDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLYGONDIALOG_H
