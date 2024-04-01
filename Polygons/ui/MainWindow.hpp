#pragma once
#include <QMainWindow>
#include "../app/data/Polygon.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void closeEvent(QCloseEvent *event) override;
    static void showCriticalMessageBox(const QString &message);

    void plotPolygons(std::vector<Polygon> &pol_v);
    static QVector<QColor> randomColors(int count);
    static std::tuple<size_t, size_t> separatePoints(std::vector<Point> &points);

private:
    Ui::MainWindow *ui;
    std::vector<Polygon> polygons{};
};
