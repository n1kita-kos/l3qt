#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isAnimationStarted(0)
{
    ui->setupUi(this);

    ui->res_pr->hide();

    player2=new QMediaPlayer(this);
    video = new QVideoWidget(this);
    player2->setVideoOutput(video);
    player2->setSource(QUrl("qrc:/images/phon3.mov"));
    video->setGeometry(0,0,1005,800);
    video->setFixedSize(1005,800);
    player=new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/images/phon3.mov"));
    audioOutput->setVolume(50);
    player->setLoops(1);
    video->show();
    player->play();
    player2->play();
    connect(player2,&QMediaPlayer::mediaStatusChanged,this,&MainWindow::onvideoout);


    //размер тескта
    font.setPointSize(14);
    ui->score->setFont(font);
    ui->score->setText(QString::number(score));

    //таймер на автокликер
    upgradeTimer = new QTimer(this);
    upgradeTimer->setInterval(1000);
    connect(upgradeTimer, &QTimer::timeout, this, &MainWindow::onUpgradeTimeout);

    QFile dbin("data1.bin");
    //иконка покупки автокликера
    ic1.addFile(":/images/checkmark3.png", QSize(100, 100));
    if (dbin.open(QIODevice::ReadOnly)) {
        QDataStream binin(&dbin);
        binin >> n >> k >> score >> aut1 >> cost >> cost2 >> cost3 >> cost4 >> reset >> mus>>aut>>upgr>>bustb>>str>>colname;
        qDebug() << "Data loaded successfully: " << n << k << score << aut1 << cost << cost2 << cost3 << cost4 << reset << mus << str<<colname;
        dbin.close();
    }
    if(str==0){
        n=1;
        k=1;
        score=0;
        cost=100;
        cost2=10000;
        cost3=150;
        cost4=1000;
        aut1=1;
        aut=0;
        bustb=0;
        reset=1;
        mus=0;
        plsn=0;
        upgr=1;
        stpd=0;
        colname="rgb(224,255,255)";
        ui->pr2->setFont(font);
        ui->pr2->setText(QString::number(cost2));

    }else{
        if(aut1==0){
            upgradeTimer->start();
            ui->upgrade2->setText("");
            ui->upgrade2->setIcon(ic1);
            ui->upgrade2->setIconSize(QSize(81, 81));
            ui->pr2->setText("-");
            ui->autoplus->setFont(font);
            ui->autoplus->setText(QString::number(k) + " auto");
        }else{
            ui->pr2->setFont(font);
            ui->pr2->setText(QString::number(cost2));
        }
    }

    //расставляю стоимость улучшений
    ui->score->setFont(font);
    ui->score->setText(QString::number(score));
    ui->pr1->setFont(font);
    ui->pr1->setText(QString::number(cost));
    ui->pr3->setFont(font);
    ui->pr3->setText(QString::number(cost3));
    ui->pr4->setFont(font);
    ui->pr4->setText(QString::number(cost4));
    bool ok;
    c1 = (ui->pr1->text()).toLongLong(&ok);
    bool ok1;
    c2 = (ui->pr2->text()).toLongLong(&ok1);
    bool ok2;
    c3 = (ui->pr3->text()).toLongLong(&ok2);
    bool ok3;
    c4 = (ui->pr4->text()).toLongLong(&ok3);


    ui->widget->hide();
    setFixedSize(1005,800);
    ui->widget->setFixedSize(1005,800);

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
    ui->res_pr->setStyleSheet("background-color: rgb(255, 255, 255);");

    //фон основного окна
    if(str==0){
        this->setStyleSheet(QString("QWidget#centralwidget { background-color: %1; }").arg(colname));
    }else{
        this->setStyleSheet(QString("QWidget#centralwidget { background-color: %1; }").arg(colname));
    }

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


    lbgif=new QLabel(ui->widget);
    moviegf = new QMovie(":/images/coingif.gif");
    lbgif->move(490, 180);
    lbgif->setFixedSize(300, 300);
    moviegf->setScaledSize(QSize(300, 300));
    lbgif->setMovie(moviegf);
}

MainWindow::~MainWindow()
{
    QFile dbin("data1.bin");
    if (dbin.open(QIODevice::WriteOnly)) {
        QDataStream binin(&dbin);
        if(bustb==1){
            onUpgr2out();
        }
        str = 1;
        binin << n << k << score << aut1 << c1 << c2 << c3 << c4 << reset << mus<<aut<<upgr <<bustb<< str<<colname;
        dbin.close();
        qDebug() << "Data saved successfully";
        qDebug() <<n << k << score << aut1 << cost << cost2 << cost3 << cost4 << reset << mus << str<<bustb<<c1<<c2<<c3<<c4<<aut<<plsn<<upgr<<stpd<<colname;
    }
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    qDebug() << event;
    colr +=event->text();
    CheatCode += event->text();
    if (CheatCode.endsWith("hesoyam")) { // Пример чит-кода
        HESOYAM();
        CheatCode.clear();
    }
    if(colr.endsWith("color")){
        color1();
        colr.clear();
    }
    if (event->key() == Qt::Key_Space and !event->isAutoRepeat()) {
        on_pushButton_clicked();
    }
    ui->warning->setStyleSheet("QLabel { color : black; }");
    QMainWindow::keyPressEvent(event);  // Обработка остальных событий клавиш
}
void MainWindow::color1(){
    on_settings_clicked();
    on_changebackgr_clicked();

}
void MainWindow::HESOYAM() {
    score += 10000;
    QFont f1;
    f1.setPointSize(14);
    ui->score->setFont(f1);
    ui->score->setText(QString::number(score));
    QFont f3;
    f3.setPointSize(24);
    ui->warning->show();
    ui->warning->setFont(f3);
    ui->warning->setStyleSheet("QLabel { color : yellow; }");
    ui->warning->setText("+" + QString::number(10000));
    animation->start();
}


void MainWindow::on_pushButton_clicked()
{
    if(bustb==1){
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
    c1 = (ui->pr1->text()).toLongLong(&ok);
    if (score >= c1) {
        if(bustb==1){
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
            n *= 1.3;
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
    c2 = (ui->pr2->text()).toLongLong(&ok);
    if (score >= c2) {
        if (aut1==1) {
            aut1 = 0;
            if (upgr==1 && score >= c2) {
                upgr = 0;
                if (score >= c2) {
                    score -= c2;
                    c2=0;
                    ui->score->setText(QString::number(score));

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
                aut =1;
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
    if (aut==1) {
        bool ok;
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
            upgradeTimer->start();
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
    c4 = (ui->pr4->text()).toLongLong(&ok);
    if ((!bustb)==1) {
        if (score >= c4) {
            bustb = 1;
            score -= c4;
            ui->score->setText(QString::number(score));
            n_1=n;
            n *= 5;
            c4 *= 1.8 ;
            ui->pr4->setText(QString::number(c4));

            // Перезапуск таймеров и сброс переменных
            upgr2->stop();
            upgr2_1->stop();
            upgr2_1_1->stop();
            timelf = 10;

            if(stpd==1){
                upgr2->setInterval(10000);
            }
            upgr2->start();

            ui->plus->setStyleSheet("QLabel { color : yellow; }");
            if(stpd==1){
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
    bustb = 0;
    n=n_1;
    ui->plus->setStyleSheet("QLabel { color : black; }");
    upgr2_1->stop();
    upgr2->stop();
    if(stpd==1){
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
        if(stpd==1){
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
    stpd=1;
    upgr2_1_1->start(rtime3);
    moviegf->stop();
}


void MainWindow::on_reset_clicked()
{
    if(score>=1000000*(reset*2)){
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
        stpd=1;
        upgr2_1_1->start(rtime3);
        ui->widget->hide();
    }else{
        ui->widget->hide();
        QFont f3;
        upgr2->start(rtime);
        upgr2_1->start(rtime2);
        stpd=1;
        upgr2_1_1->start(rtime3);
        animation->start();
        long long a = ((1000000*(reset*2)) - score);
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
        colname=color.name();

        this->setStyleSheet(QString("QWidget#centralwidget { background-color: %1; }").arg(colname));
    }else{
        upgr2->start(rtime);
        upgr2_1->start(rtime2);
        stpd=1;
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
    QFile dbin("data1.bin");
    if (dbin.open(QIODevice::WriteOnly)) {
        QDataStream binin(&dbin);
        if(bustb==1){
            onUpgr2out();
        }
        str = 1;
        binin << n << k << score << aut1 << c1 << c2 << c3 << c4 << reset << mus <<aut<<upgr<<bustb<< str<<colname;
        dbin.close();
        qDebug() << "Data saved successfully";
        qDebug() <<n << k << score << aut1 << cost << cost2 << cost3 << cost4 << reset << mus << str<<bustb<<c1<<c2<<c3<<c4<<aut<<plsn<<upgr<<stpd<<colname;
        dbin.close();
    }
    QApplication::quit();
}


void MainWindow::on_ch_mus_clicked()
{
    mus++;
    if(mus%4==0){
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl("qrc:/images/Digital Dream.mp3"));
        audioOutput->setVolume(50);
        player->setLoops(QMediaPlayer::Infinite);
        player->play();
    }
    if(mus%4==1){
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl("qrc:/images/Pixel Dreams.mp3"));
        audioOutput->setVolume(50);
        player->setLoops(QMediaPlayer::Infinite);
        player->play();
    }
    if(mus%4==2){
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl("qrc:/images/SHADXWBXRN - KNIGHT.mp3"));
        audioOutput->setVolume(50);
        player->setLoops(QMediaPlayer::Infinite);
        player->play();
    }
    if(mus%4==3){
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl("qrc:/images/Skrillex - Bangarang.mp3"));
        audioOutput->setVolume(50);
        player->setLoops(QMediaPlayer::Infinite);
        player->play();
    }
}

void MainWindow::onvideoout(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        player2->stop();
        video->hide();
        //музыка
        player=new QMediaPlayer(this);
        if(mus%4==0){
            player->setAudioOutput(audioOutput);
            player->setSource(QUrl("qrc:/images/Digital Dream.mp3"));
            audioOutput->setVolume(50);
            player->setLoops(QMediaPlayer::Infinite);
            player->play();
        }
        if(mus%4==1){
            player->setAudioOutput(audioOutput);
            player->setSource(QUrl("qrc:/images/Pixel Dreams.mp3"));
            audioOutput->setVolume(50);
            player->setLoops(QMediaPlayer::Infinite);
            player->play();
        }
        if(mus%4==2){
            player->setAudioOutput(audioOutput);
            player->setSource(QUrl("qrc:/images/SHADXWBXRN - KNIGHT.mp3"));
            audioOutput->setVolume(50);
            player->setLoops(QMediaPlayer::Infinite);
            player->play();
        }
        if(mus%4==3){
            player->setAudioOutput(audioOutput);
            player->setSource(QUrl("qrc:/images/Skrillex - Bangarang.mp3"));
            audioOutput->setVolume(50);
            player->setLoops(QMediaPlayer::Infinite);
            player->play();
        }
    }
}


void MainWindow::on_res_pr_clicked()
{


}

