#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isAnimationStarted(false)
{
    ui->setupUi(this);
    ui->score->setText(QString::number(score));
    font.setPointSize(14);

    animation = new QPropertyAnimation(ui->warning, "geometry");
    animation->setDuration(3000);
    animation->setStartValue(QRect(400, 580, 340, 50));
    animation->setEndValue(QRect(400, 40, 340, 50));

    holdTimer = new QTimer(this);
    holdTimer->setInterval(1000);
    holdTimer->setSingleShot(true);

    displayTimer = new QTimer(this);
    displayTimer->setInterval(50);  // 0.1 секунды
    displayTimer->setSingleShot(true);
    connect(displayTimer, &QTimer::timeout, this, &MainWindow::hidePlusLabel);

    connect(holdTimer, &QTimer::timeout, this, &MainWindow::onHoldTimeout);

    upgradeTimer = new QTimer(this);  // Новый таймер для апгрейда
    upgradeTimer->setInterval(1000);  // Каждую секунду
    connect(upgradeTimer, &QTimer::timeout, this, &MainWindow::onUpgradeTimeout);

    ui->pr1->setFont(font);
    ui->pr1->setText(QString::number(cost));
    ui->pr2->setFont(font);
    ui->pr2->setText(QString::number(cost2));
    ui->pr3->setFont(font);
    ui->pr3->setText(QString::number(cost3));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->warning->hide();
    score += n;
    ui->score->setFont(font);
    ui->score->setText(QString::number(score));
    QString pls = "+" + QString::number(n);
    QFont ff;
    ff.setPointSize(32);
    ui->plus->setFont(ff);
    ui->plus->setText(pls);
    QPoint pp;
    srand(time(NULL));
    pp.setX(rand() % 1000);
    pp.setY(rand() % 750);
    ui->plus->move(pp);
    ui->plus->show();
    displayTimer->start();
}

void MainWindow::on_pushButton_pressed()
{
    holdTimer->start();
}

void MainWindow::on_pushButton_released()
{
    holdTimer->stop();
    if (isAnimationStarted) {
        ui->warning->hide();
        animation->stop();
        isAnimationStarted = false;
    }
}

void MainWindow::onHoldTimeout()
{
    ui->warning->show();
    QFont f1;
    f1.setPointSize(32);
    ui->warning->setFont(f1);
    ui->warning->setText("Play fair!");
    animation->start();
    isAnimationStarted = true;
}

void MainWindow::hidePlusLabel()
{
    ui->plus->hide();
}

void MainWindow::on_upgrade_clicked()
{
    bool ok;
    int c1;
    c1 = (ui->pr1->text()).toInt(&ok);
    if (score >= c1) {
        score -= c1;
        ui->score->setText(QString::number(score));
        c1 *= 2;
        ui->pr1->setText(QString::number(c1));
        n += 1;
    }
}

void MainWindow::on_upgrade2_clicked()
{
    bool ok;
    int c2;
    c2 = (ui->pr2->text()).toInt(&ok);
    if (score >= c2) {
        score -= c2;
        ui->score->setText(QString::number(score));
        c2 *= 2;
        ui->pr2->setText(QString::number(c2));


        if (!upgradeTimer->isActive()) {
            upgradeTimer->start();  // Запускаем таймер, если он еще не запущен
        }
    }
}

void MainWindow::on_upgrade3_clicked()
{
    bool ok;
    int c3;
    c3 = (ui->pr3->text()).toInt(&ok);
    if (score >= c3) {
        score -= c3;
        ui->score->setText(QString::number(score));
        c3 *= 2;
        ui->pr3->setText(QString::number(c3));
        k += 1;
    }
}

void MainWindow::onUpgradeTimeout()
{
    score += k;  // Увеличиваем score на k каждую секунду
    ui->score->setText(QString::number(score));
}
