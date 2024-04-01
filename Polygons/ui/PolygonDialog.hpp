#pragma once
#include <QDialog>
#include <QString>
#include "../app/data/Polygon.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
    class PolygonDialog;
}
QT_END_NAMESPACE

class PolygonDialog : public QDialog {
    Q_OBJECT
public:
    explicit PolygonDialog(QWidget *parent = nullptr);
    ~PolygonDialog() override;
    static void showCriticalMessageBox(const QString &message);

signals:
    void elementSelected(Polygon& data);

private:
    Ui::PolygonDialog *ui;
};
