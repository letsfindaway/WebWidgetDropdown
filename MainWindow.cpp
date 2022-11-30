/*
 * backstash
 * User interface for easy backup and restore using borg.
 *
 * Copyright (C) 2022 "letsfindaway" Martin Winter
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QWebEnginePage>
#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    proxy = new QGraphicsProxyWidget();
    view = new QWebEngineView();

    proxy->setWidget(view);
    proxy->resize(700, 600);
    scene->addItem(proxy);
    ui->graphicsView->setScene(scene);

    // workaround for wrong positioning of menu
    connect(ui->posWorkaround, &QCheckBox::toggled, this, [this](bool checked){
        if (checked)
        {
            QSize actualSize = view->size();
            view->resize(actualSize - QSize(1,1));
            view->resize(actualSize);
        }
    });

    // move
    QPointF pos = proxy->pos();
    connect(ui->moveButton, &QPushButton::toggled, this, [this,pos](bool checked){
        if (checked)
        {
            proxy->setPos(pos + QPointF(200, 150));
        }
        else
        {
            proxy->setPos(pos);
        }
    });

    // zoom
    connect(ui->zoomButton, &QPushButton::toggled, this, [this](bool checked){
        if (checked)
        {
            proxy->setScale(0.8);
        }
        else
        {
            proxy->setScale(1);
        }
    });

    view->load(QUrl("https://www.w3schools.com/tags/tryit.asp?filename=tryhtml_select"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

