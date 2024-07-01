#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isAnimationStarted(false)
{

    ui->setupUi(this);
    ui->widget->hide();
    setFixedSize(1005,800);
    ui->widget->setFixedSize(1005,800);

    //размер тескта
    font.setPointSize(14);
    ui->score->setFont(font);
    ui->score->setText(QString::number(score));

    //основная кнопка и fire прозрачные, остальные белые
    ui->pushButton->setFlat(true);
    ui->pushButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->upgrade->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->upgrade2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->upgrade3->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->upgrade4->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->settings->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->fire->setFlat(true);
    ui->fire->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->ex_sett->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->reset->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->soundoff->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->soundon->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->changebackgr->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->ex_sett->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->ex_game->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->ch_mus->setStyleSheet("background-color: rgb(255, 255, 255);");

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

    //таймер к огонькам на экране
    displayTimer2 = new QTimer(this);
    displayTimer2->setInterval(100);
    displayTimer2->setSingleShot(true);
    connect(displayTimer2, &QTimer::timeout, this, &MainWindow::hidefire);

    //таймер на автокликер
    upgradeTimer = new QTimer(this);
    upgradeTimer->setInterval(1000);
    connect(upgradeTimer, &QTimer::timeout, this, &MainWindow::onUpgradeTimeout);

    //таймер для буста
    upgr2 = new QTimer(this);
    upgr2->setInterval(10000);
    connect(upgr2, &QTimer::timeout, this, &MainWindow::onUpgr2out);

    //таймер для буста_1
    upgr2_1 = new QTimer(this);
    upgr2_1->setInterval(1000);
    connect(upgr2_1, &QTimer::timeout, this, &MainWindow::ont_1);

    //таймер для буста_1_1
    upgr2_1_1 = new QTimer(this);
    upgr2_1_1->setInterval(100);
    connect(upgr2_1_1, &QTimer::timeout, this, &MainWindow::ont_1_1);


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
    ic1.addFile(":/images/checkmark3.png", QSize(100, 100));
    //иконка при покупке буста
    ic2.addFile(":/images/c5.png", QSize(75, 75));
    //иконка крестика
    ic3.addFile(":/images/c6.png", QSize(50, 50));
    ui->ex_sett->setIconSize(QSize(50,50));
    ic4.addFile(":/images/gold-coin-icon.png",QSize(300,300));
    ui->pushButton->setIconSize(QSize(300,300));
    ui->pushButton->setIcon(ic4);

    ui->ex_sett->setIcon(ic3);
    ui->fire->hide();

    //музыка
    player=new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/images/Digital Dream.mp3"));
    audioOutput->setVolume(50);
    player->setLoops(QMediaPlayer::Infinite);
    player->play();

    lbgif=new QLabel(ui->widget);
    moviegf = new QMovie(":/images/coingif.gif");
    lbgif->move(560, 230);
    lbgif->setFixedSize(300, 300);
    moviegf->setScaledSize(QSize(300, 300));
    lbgif->setMovie(moviegf);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(bustb){
        ui->fire->setIcon(ic2);
        QPoint pp1;
        pp1.setX(rand() % 1000);
        pp1.setY(rand() % 750);
        ui->fire->move(pp1);
        ui->fire->show();
        displayTimer2->start();
    }
    ui->warning->hide();
    score += n;
    ui->score->setFont(font);
    ui->score->setText(QString::number(score));
    QString pls = "+" + QString::number(n);
    QFont ff;
    ff.setPointSize(24);
    ui->plus->setFont(ff);
    ui->plus->setText(pls);
    ui->scprcl->setFont(font);
    ui->scprcl->setText("+ "+QString::number(n));
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

void MainWindow::hidefire(){
    ui->fire->hide();
}

void MainWindow::on_upgrade_clicked()
{
    bool ok;
    long long c1;
    c1 = (ui->pr1->text()).toLongLong(&ok);
    if (score >= c1) {
        if(bustb){
            QFont f3;
            f3.setPointSize(24);
            ui->warning->show();
            ui->warning->setFont(f3);
            ui->warning->setText("You need can't upgrade while bust.");
            animation->start();
        }else{
            score -= c1;
            ui->score->setText(QString::number(score));
            c1 *= 1.5;
            ui->pr1->setText(QString::number(c1));
            n *= 1.45;
            n++;
        }

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
    if (score >= c2) {
        if (aut1) {
            aut1 = false;
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
        } else {
            QFont f3;
            f3.setPointSize(24);
            ui->warning->show();
            ui->warning->setFont(f3);
            ui->warning->setText("You have already bought auto.");
            animation->start();
        }
    } else {
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
            k *= 1.45;
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
        ui->warning->setText("Buy autoclicker");
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
{
    bool ok;
    long long c4;
    c4 = (ui->pr4->text()).toLongLong(&ok);
    if (!bustb) {
        if (score >= c4) {
            bustb = true;
            score -= c4;
            ui->score->setText(QString::number(score));
            n_1=n;
            n *= 5;
            c4 *= 1.6;
            ui->pr4->setText(QString::number(c4));

            // Перезапуск таймеров и сброс переменных
            upgr2->stop();
            upgr2_1->stop();
            upgr2_1_1->stop();
            timelf = 10;

            if(stpd){
                upgr2->setInterval(10000);
            }
            upgr2->start();

            ui->plus->setStyleSheet("QLabel { color : yellow; }");
            if(stpd){
                upgr2_1->setInterval(1000);
            }
            upgr2_1->start();
            ui->timeleft->setFont(font);
            ui->timeleft->setText(QString::number(timelf) + " sec left");
            timelf--;
        } else {
            QFont f3;
            long long a = (c4 - score);
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
        ui->warning->setText("You've already bought bust");
        animation->start();
    }
}

void MainWindow::onUpgr2out()
{
    ui->timeleft->setFont(font);
    ui->timeleft->setText(QString::number(timelf) + " sec left");
    bustb = false;
    n=n_1;
    ui->plus->setStyleSheet("QLabel { color : black; }");
    upgr2_1->stop();
    upgr2->stop();
    if(stpd){
        upgr2_1_1->setInterval(100);
    }
    upgr2_1_1->start();
}

void MainWindow::ont_1()
{
    if (timelf > 0) {
        ui->timeleft->setFont(font);
        ui->timeleft->setText(QString::number(timelf) + " sec left");
        timelf--;
        if(stpd){
            upgr2_1->setInterval(1000);
        }
        upgr2_1->start();
    } else {
        upgr2_1->stop();
    }

}

void MainWindow::ont_1_1()
{
    ui->timeleft->setFont(font);
    ui->timeleft->setText("");
    timelf = 10;
    ui->fire->hide();
}




void MainWindow::on_settings_clicked()
{
    ui->widget->show();
    rtime=upgr2->remainingTime();
    rtime2=upgr2_1->remainingTime();
    rtime3=upgr2_1_1->remainingTime();
    upgr2->stop();
    upgr2_1->stop();
    upgr2_1_1->stop();
    moviegf->start();
}


void MainWindow::on_ex_sett_clicked()
{
    ui->widget->hide();
    upgr2->start(rtime);
    upgr2_1->start(rtime2);
    stpd=true;
    upgr2_1_1->start(rtime3);
    moviegf->stop();
}


void MainWindow::on_reset_clicked()
{
    if(score>=1000000*(reset)){
        n=5*reset;
        cost=100;
        cost3=150;
        cost4=1000;
        score=10000;
        k=1;
        QFont ff;
        ff.setPointSize(14);
        ui->pr1->setText(QString::number(cost));
        ui->pr3->setText(QString::number(cost3));
        ui->pr4->setText(QString::number(cost4));
        ui->score->setText(QString::number(score));
        ui->scprcl->setFont(ff);
        ui->scprcl->setText("+ "+QString::number(n));
        reset++;
        upgr2->start(rtime);
        upgr2_1->start(rtime2);
        stpd=true;
        upgr2_1_1->start(rtime3);
        ui->widget->hide();
    }else{
        ui->widget->hide();
        QFont f3;
        upgr2->start(rtime);
        upgr2_1->start(rtime2);
        stpd=true;
        upgr2_1_1->start(rtime3);
        animation->start();
        long long a = ((1000000*(reset)) - score);
        f3.setPointSize(24);
        ui->warning->show();
        ui->warning->setFont(f3);
        ui->warning->setText("You need " + QString::number(a)+" to reset!");

    }

}


void MainWindow::on_changebackgr_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет");

    if (color.isValid()) {

        QString colorName = color.name();

        this->setStyleSheet(QString("QWidget#centralwidget { background-color: %1; }").arg(colorName));
    }else{
        upgr2->start(rtime);
        upgr2_1->start(rtime2);
        stpd=true;
        upgr2_1_1->start(rtime3);
        QFont f3;
        f3.setPointSize(24);
        ui->warning->show();
        ui->warning->setFont(f3);
        ui->warning->setText("Wrong color format.");
        animation->start();
    }
}


void MainWindow::on_soundoff_clicked()
{
   player->pause();
}


void MainWindow::on_soundon_clicked()
{
   player->play();
}


void MainWindow::on_ex_game_clicked()
{
    QApplication::quit();
}


void MainWindow::on_ch_mus_clicked()
{
    mus++;
    if(mus%2==0){
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl("qrc:/images/Digital Dream.mp3"));
        audioOutput->setVolume(50);
        player->setLoops(QMediaPlayer::Infinite);
        player->play();
    }
    if(mus%2==1){
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl("qrc:/images/Pixel Dreams.mp3"));
        audioOutput->setVolume(50);
        player->setLoops(QMediaPlayer::Infinite);
        player->play();
    }
}

