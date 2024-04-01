#include <QModelIndex>
#include <QStringListModel>
#include <QMessageBox>
#include <QCloseEvent>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <set>

#include "ui_MainWindow.h"
#include "MainWindow.hpp"
#include "PolygonDialog.hpp"
#include "../Constants.hpp"
#include "../app/Geometry.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    auto mList = ui->listView;
    auto model = new QStringListModel(this);

    mList->setModel(model);
    mList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mList->setSelectionMode(QAbstractItemView::MultiSelection);
    mList->setDragEnabled(false);
    mList->setAcceptDrops(false);
    mList->viewport()->setAcceptDrops(false);
    mList->setDropIndicatorShown(false);
    mList->setDragDropMode(QAbstractItemView::InternalMove);

    QChart *chart = new QChart();
    chart->setTitle("(-__-)");
    ui->graphicsView->setChart(chart);
    ui->areaText->setText(QStringLiteral("Area: %1").arg(0));

    connect(ui->insertButton, &QPushButton::clicked, this, [=]() {
        auto dialog = new PolygonDialog(this);
        connect(dialog, &PolygonDialog::elementSelected, this, [=](Polygon data) {
            model->insertRow(model->rowCount());
            QModelIndex index = model->index(model->rowCount() - 1);
            model->setData(index, QString::fromStdString(data.getName()));
            polygons.push_back(data);
        });
        dialog->show();
    });

    connect(ui->editButton, &QPushButton::clicked, this, [=]() {
        auto indexes = mList->selectionModel()->selectedIndexes();
        if (indexes.length() != 1) {
            showCriticalMessageBox("Please, select only one polygon!");
        } else {
            // change instance...
        }
    });

    connect(ui->removeButton, &QPushButton::clicked, this, [=]() {
        auto indexes = mList->selectionModel()->selectedIndexes();
        if (indexes.length() != 1) {
            showCriticalMessageBox("Please, select only one polygon!");
        } else {
            model->removeRow(indexes.back().row());
            polygons.erase(polygons.begin() + indexes.back().row());
        }
    });

    connect(ui->plotButton, &QPushButton::clicked, this, [=]() {
        if (polygons.empty()) {
            chart->setTitle("(-__-)");
            ui->graphicsView->setChart(chart);
            showCriticalMessageBox("Please, create at least one polygon!");
        } else {
            auto indexes = mList->selectionModel()->selectedIndexes();
            std::set<size_t> choosen_indexes{};
            for (const auto &index : indexes) {
                choosen_indexes.insert(index.row());
            }
            std::vector<Polygon> ploted_polygons;
            bool is_stopped = false;
            for (size_t i = 0; i < polygons.size(); ++i) {
                if (!choosen_indexes.empty() && choosen_indexes.find(i) == choosen_indexes.end()) {
                    continue;
                }
                std::set<Point> unique_points{};
                for (const auto& point : polygons[i].getPoints()) {
                    unique_points.insert(point);
                }
                if (unique_points.size() >= MIN_POINT_AMOUNT) {
                    Polygon new_polygon(Geometry::convexHull(unique_points));
                    ploted_polygons.push_back(new_polygon);
                } else {
                    is_stopped = true;
                }
                unique_points.clear();
            }
            if (is_stopped || ploted_polygons.size() < 1) {
                ui->areaText->setText(QStringLiteral("Area: %1").arg(0));
            } else {
                plotPolygons(ploted_polygons);
                Polygon clipped_polygon = Geometry::clipPolygons(ploted_polygons);
                double total_area = clipped_polygon.area();
                ui->areaText->setText(QStringLiteral("Area: %1").arg(total_area));
            }
            ploted_polygons.clear();
            choosen_indexes.clear();
        }
    });
}

void MainWindow::closeEvent(QCloseEvent *event) {
    event->ignore();
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to terminate the session?");
    msgBox.setInformativeText("All information and results will be lost when you exit thr application.");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setIconPixmap(QPixmap(":/res/ico/exit.ico"));
    int ret = msgBox.exec();
    if (QMessageBox::Yes == ret) {
        event->accept();
    }
}

void MainWindow::showCriticalMessageBox(const QString &message) {
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Icon::Critical);
    msgBox.setIconPixmap(QPixmap(":/res/ico/caution.ico"));
    msgBox.exec();
}

void MainWindow::plotPolygons(std::vector<Polygon> &pol_v) {
    double mx_x = MIN, mn_x = MAX, mx_y = MIN, mn_y = MAX;
    QChart *chart = new QChart();
    auto colors = randomColors(pol_v.size());

    for (auto &polygon : pol_v) {
        auto margins = separatePoints(polygon.getPoints());
        double fr = std::get<0>(margins), to = std::get<1>(margins);
        QLineSeries *line_series_0 = new QLineSeries();
        QLineSeries *line_series_1 = new QLineSeries();

        for (size_t i = fr; i <= to; ++i) {
            auto point = polygon.getPoints()[i];
            mx_x = std::max(mx_x, point.x);
            mn_x = std::min(mn_x, point.x);
            mx_y = std::max(mx_y, point.y);
            mn_y = std::min(mn_y, point.y);
            *line_series_0 << QPointF(point.x, point.y);
        }
        for (size_t i = to; i < polygon.size(); ++i) {
            auto point = polygon.getPoints()[i];
            mx_x = std::max(mx_x, point.x);
            mn_x = std::min(mn_x, point.x);
            mx_y = std::max(mx_y, point.y);
            mn_y = std::min(mn_y, point.y);
            *line_series_1 << QPointF(point.x, point.y);
        }
        for (size_t i = 0; i <= fr; ++i) {
            auto point = polygon.getPoints()[i];
            mx_x = std::max(mx_x, point.x);
            mn_x = std::min(mn_x, point.x);
            mx_y = std::max(mx_y, point.y);
            mn_y = std::min(mn_y, point.y);
            *line_series_1 << QPointF(point.x, point.y);
        }
        QAreaSeries *area_series = new QAreaSeries(line_series_0, line_series_1);
        QColor color = colors.back().lighter(); color.setAlpha(50);
        QPen pen(color); pen.setWidth(0);

        area_series->setName(QString::fromStdString(polygon.getName()));
        area_series->setPen(pen);
        area_series->setColor(color);
        area_series->setPointsVisible(true);
        area_series->setPointLabelsColor(Qt::black);

        chart->addSeries(area_series);
        colors.pop_back();
    }
    colors.clear();
    chart->createDefaultAxes();

    double delta_x = fabs(mx_x - mn_x) * 0.1;
    double delta_y = fabs(mx_y - mn_y) * 0.1;

    chart->axes(Qt::Horizontal).first()->setRange(mn_x - delta_x, mx_x + delta_x);
    chart->axes(Qt::Vertical).first()->setRange(mn_y - delta_y, mx_y + delta_y);
    chart->setBackgroundVisible();
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setChart(chart);
}

QVector<QColor> MainWindow::randomColors(int count) {
    QVector<QColor> colors;
    float currentHue = 0.0;
    for (int i = 0; i < count; ++i) {
        colors.push_back(QColor::fromHslF(currentHue, 1.0, 0.5));
        currentHue += 0.618033988749895f;
        currentHue = std::fmod(currentHue, 1.0f);
    }
    return colors;
}

std::tuple<size_t, size_t> MainWindow::separatePoints(std::vector<Point> &points) {
    double mn_x = MAX, mx_x = MIN;
    size_t ind_mn, ind_mx;
    for (size_t i = 0; i < points.size(); ++i) {
        if (points[i].x > mx_x) {
            mx_x = points[i].x;
            ind_mx = i;
        }
        if (points[i].x < mn_x) {
            mn_x = points[i].x;
            ind_mn = i;
        }
    }
    return {std::min(ind_mn, ind_mx), std::max(ind_mn, ind_mx)};
}


MainWindow::~MainWindow() {
    delete ui;
}
