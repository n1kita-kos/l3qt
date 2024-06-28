#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isAnimationStarted(false)
{

    ui->setupUi(this);
    //размер тескта
    font.setPointSize(14);
    ui->score->setFont(font);
    ui->score->setText(QString::number(score));

    //основная кнопка прозрачная, остальные белые
    ui->pushButton->setFlat(true);
    ui->pushButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->upgrade->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->upgrade2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->upgrade3->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->upgrade4->setStyleSheet("background-color: rgb(255, 255, 255);");

    //фон основного окна
    this->setStyleSheet("QWidget#centralwidget { background-color: rgb(224, 255, 255); }");

    //анимация основных сообщений игроку
    animation = new QPropertyAnimation(ui->warning, "geometry");
    animation->setDuration(3000);
    animation->setStartValue(QRect(300, 580, 800, 50));
    animation->setEndValue(QRect(300, 40, 800, 50));

    //подключение функции к концу анимации
    connect(animation, &QPropertyAnimation::finished, this, &MainWindow::onAnimationFinished);

    //таймер для предупреждения о задержке кнопки
    holdTimer = new QTimer(this);
    holdTimer->setInterval(1000);
    holdTimer->setSingleShot(true);
    connect(holdTimer, &QTimer::timeout, this, &MainWindow::onHoldTimeout);

    //таймер к плюсикам на экране
    displayTimer = new QTimer(this);
    displayTimer->setInterval(100);
    displayTimer->setSingleShot(true);
    connect(displayTimer, &QTimer::timeout, this, &MainWindow::hidePlusLabel);

   //таймер на автокликер
    upgradeTimer = new QTimer(this);
    upgradeTimer->setInterval(1000);
    connect(upgradeTimer, &QTimer::timeout, this, &MainWindow::onUpgradeTimeout);

    //функция выхода
    connect(ui->exit, &QAction::triggered, this, &MainWindow::on_exit_triggered);

    //таймер для буста
    upgr2 = new QTimer(this);
    upgr2->setInterval(10000);
    connect(upgr2, &QTimer::timeout, this, &MainWindow::onUpgr2out);

    //расставляю стоимость улучшений
    ui->pr1->setFont(font);
    ui->pr1->setText(QString::number(cost));
    ui->pr2->setFont(font);
    ui->pr2->setText(QString::number(cost2));
    ui->pr3->setFont(font);
    ui->pr3->setText(QString::number(cost3));
    ui->pr4->setFont(font);
    ui->pr4->setText(QString::number(cost4));

    //иконка покупки автокликера
    ic1.addFile(":/images/checkmark3.png", QSize(100,100));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_clicked()
{
    ui->warning->hide();
    score += n;
    ui->score->setFont(font);
    ui->score->setText(QString::number(score));
    QString pls = "+" + QString::number(n);
    QFont ff;
    ff.setPointSize(24);
    ui->plus->setFont(ff);
    ui->plus->setText(pls);
    QPoint pp;
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
    f1.setPointSize(24);
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
    long long c1;
    c1 = (ui->pr1->text()).toLongLong(&ok);
    if (score >= c1) {
        score -= c1;
        ui->score->setText(QString::number(score));
        c1 *= 1.5;
        ui->pr1->setText(QString::number(c1));
        n *= 1.3;
        n++;
    } else {
        QFont f3;
        long long a = (c1 - score);
        f3.setPointSize(24);
        ui->warning->show();
        ui->warning->setFont(f3);
        ui->warning->setText("You need " + QString::number(a));
        animation->start();
    }
}

void MainWindow::on_upgrade2_clicked()
{
    bool ok;
    long long c2;
    c2 = (ui->pr2->text()).toLongLong(&ok);
    if(score>=c2){
        if(aut1){
            aut1=false;
            if (upgr && score >= c2) {
                upgr = false;
                if (score >= c2) {
                    score -= c2;
                    ui->score->setText(QString::number(score));
                    c2 *= 2;
                    ui->pr2->setText(QString::number(c2));

                    if (!upgradeTimer->isActive()) {
                        upgradeTimer->start();
                    }
                }

                ui->upgrade2->setText("");
                ui->upgrade2->setIcon(ic1);
                ui->upgrade2->setIconSize(QSize(81, 81));
                ui->pr2->setText("-");
                ui->autoplus->setFont(font);
                ui->autoplus->setText(QString::number(k) + " auto");
                aut = true;
            } else {
                QFont f3;
                long long a = (c2 - score);
                f3.setPointSize(24);
                ui->warning->show();
                ui->warning->setFont(f3);
                ui->warning->setText("You need " + QString::number(a));
                animation->start();
            }
        }else{
            ui->warning->show();
            ui->warning->setText("You have already bought auto.");
            animation->start();
        }
    }else{
        QFont f3;
        long long a = (c2 - score);
        f3.setPointSize(24);
        ui->warning->show();
        ui->warning->setFont(f3);
        ui->warning->setText("You need " + QString::number(a));
        animation->start();
    }
}

void MainWindow::on_upgrade3_clicked()
{
    if (aut) {
        bool ok;
        long long c3;
        c3 = (ui->pr3->text()).toLongLong(&ok);
        if (score >= c3) {
            score -= c3;
            ui->score->setText(QString::number(score));
            c3 *= 1.5;
            ui->pr3->setText(QString::number(c3));
            k *= 1.3;
            k++;
            ui->autoplus->setFont(font);
            ui->autoplus->setText(QString::number(k) + " auto");
        } else {
            QFont f3;
            long long a = (c3 - score);
            f3.setPointSize(24);
            ui->warning->show();
            ui->warning->setFont(f3);
            ui->warning->setText("You need " + QString::number(a));
            animation->start();
        }
    } else {
        QFont f3;
        f3.setPointSize(24);
        ui->warning->show();
        ui->warning->setFont(f3);
        ui->warning->setText("Buy auto");
        animation->start();
    }
}

void MainWindow::onUpgradeTimeout()
{
    score += k;
    ui->score->setText(QString::number(score));
}

void MainWindow::onAnimationFinished()
{
    ui->warning->hide();
}

void MainWindow::on_upgrade4_clicked()
{   bool ok;
    long long c4;
    c4 = (ui->pr4->text()).toLongLong(&ok);
    if(!bustb==1){
        bustb=true;
        if (score >= c4) {
            score-=c4;
            ui->score->setText(QString::number(score));
            n*=5;
            c4 *=1.8 ;
            ui->pr4->setText(QString::number(c4));
            upgr2->start();
            ui->plus->setStyleSheet("QLabel { color : yellow; }");
        }else{
            QFont f3;
            long long a = (c4 - score);
            f3.setPointSize(24);
            ui->warning->show();
            ui->warning->setFont(f3);
            ui->warning->setText("You need " + QString::number(a));
            animation->start();
        }
    }else{
        QFont f3;
        f3.setPointSize(24);
        ui->warning->show();
        ui->warning->setFont(f3);
        ui->warning->setText("You've already bought bust");
        animation->start();
    }
}

void MainWindow::onUpgr2out()
{
    bustb=false;
    n/=5;
    ui->plus->setStyleSheet("QLabel { color : black; }");

}
