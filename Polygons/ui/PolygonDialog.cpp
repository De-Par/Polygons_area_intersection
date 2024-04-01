#include <QPushButton>
#include <QModelIndex>
#include <QTableWidget>
#include <QMessageBox>
#include <QCloseEvent>

#include "PolygonDialog.hpp"
#include "ui_PolygonDialog.h"
#include "../Constants.hpp"

PolygonDialog::PolygonDialog(QWidget *parent) : QDialog(parent), ui(new Ui::PolygonDialog) {
    ui->setupUi(this);

    auto mTable = ui->tableWidget;

    mTable->setColumnCount(2);
    QStringList labels; labels << "X" << "Y";
    mTable->setHorizontalHeaderLabels(labels);
    mTable->resizeColumnsToContents();
    mTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mTable->verticalHeader()->setVisible(false);
    mTable->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    mTable->setSelectionMode(QAbstractItemView::MultiSelection);
    mTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    mTable->setDragEnabled(false);
    mTable->setAcceptDrops(false);
    mTable->setDropIndicatorShown(false);
    mTable->setDragDropMode(QAbstractItemView::NoDragDrop);
    mTable->viewport()->setFocusPolicy(Qt::NoFocus);

    connect(ui->insertButton, &QPushButton::clicked, this, [=]() { 
        int rowPos = mTable->rowCount();
        auto item_x = new QTableWidgetItem();
        auto item_y = new QTableWidgetItem();
        item_x->setBackground(QBrush(QColor(20, 164, 74)));
        item_y->setBackground(QBrush(QColor(20, 164, 74)));
        mTable->insertRow(rowPos);
        mTable->setItem(rowPos, 0, item_x);
        mTable->setItem(rowPos, 1, item_y);

        auto qle_x = new QLineEdit(mTable);
        auto qle_y = new QLineEdit(mTable);
        auto validator = new QRegularExpressionValidator(QRegularExpression("[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?"));
        qle_x->setValidator(validator);
        qle_y->setValidator(validator);
        mTable->setCellWidget(rowPos, 0, qle_x);
        mTable->setCellWidget(rowPos, 1, qle_y);
    });

    connect(ui->removeButton, &QPushButton::clicked, this, [=]() {
        auto indexes = mTable->selectionModel()->selectedIndexes();
        if (indexes.isEmpty()) {
            showCriticalMessageBox("Please, select one more item!");
        } else {
            for (const auto &index : indexes) {
                mTable->removeRow(index.row());
            }
        }
    });

    connect(ui->cancelButton, &QPushButton::clicked, this, [=]() { close(); });

    connect(ui->pushButton, &QPushButton::clicked, this, [=]() {
        if (mTable->rowCount() < MIN_POINT_AMOUNT) {
            showCriticalMessageBox("Specify at least three points!");
        } else {
            bool flag = true;
            QLineEdit* qle;
            for (size_t i = 0; i < mTable->rowCount(); ++i) {
                for (size_t j = 0; j < mTable->columnCount(); ++j) {
                    qle = qobject_cast<QLineEdit*>(mTable->cellWidget(i, j));
                    if (!qle || qle->text().isEmpty()) {
                        flag = false;
                        break;
                    }
                }
            }
            if (!flag) {
                showCriticalMessageBox("Fill all items!");
            } else {
                std::vector<Point> pVec{};
                for (size_t i = 0; i < mTable->rowCount(); ++i) {
                    qle = qobject_cast<QLineEdit*>(mTable->cellWidget(i, 0));
                    double x = qle->text().toDouble();
                    qle = qobject_cast<QLineEdit*>(mTable->cellWidget(i, 1));
                    double y = qle->text().toDouble();
                    pVec.emplace_back(x, y);
                }
                Polygon data(pVec);
                if (!ui->lineEdit->text().isEmpty()) {
                    data.setName(ui->lineEdit->text().toStdString());
                } else {
                    data.setName("Polygon");
                }
                emit elementSelected(data);
                close();
            }
        }
    });
}

void PolygonDialog::showCriticalMessageBox(const QString &message) {
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Icon::Critical);
    msgBox.setIconPixmap(QPixmap(":/res/ico/caution.ico"));
    msgBox.exec();
}

PolygonDialog::~PolygonDialog() {
    delete ui;
}
