#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QListView>
#include <QComboBox>
#include <QStringListModel>
#include <QFile>
#include <QTextStream>
#include <QDialog>
#include <QString>
#include <QStringList>
#include <QPropertyAnimation>
#include <QTimer>
#include <QIcon>
#include <QGraphicsOpacityEffect>
#include <QColorDialog>
#include <QPalette>
#include <QtMultimedia>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QUrl>
#include <QDebug>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QEvent>
#include <QMovie>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_pressed();
    void on_pushButton_released();
    void onHoldTimeout();
    void hidePlusLabel();

    void on_upgrade_clicked();

    void on_upgrade2_clicked();

    void on_upgrade3_clicked();
    void onUpgradeTimeout();
    void onAnimationFinished();

    void on_upgrade4_clicked();
    void onUpgr2out();
    void ont_1();
    void ont_1_1();
    void hidefire();
    void on_settings_clicked();

    void on_ex_sett_clicked();

    void on_reset_clicked();

    void on_changebackgr_clicked();

    void on_soundoff_clicked();

    void on_soundon_clicked();

    void on_ex_game_clicked();

    void on_ch_mus_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QPropertyAnimation *animation;//анимка
    QTimer *holdTimer;//таймер для задержки
    QTimer *displayTimer;//таймер для плюсиков
    QTimer *displayTimer2;//таймер для огоньков
    QTimer *upgradeTimer;//таймер автоклика
    QTimer *upgr2;//таймер буста
    QTimer *upgr2_1;//таймер буста_1
    QTimer *upgr2_1_1;//таймер буста_1_1
    QMediaPlayer *plar;
    QAudioOutput *aout;
    QIcon ic1;//иконка при покупке авто
    QIcon ic2;//иконка при покупке буста
    QIcon ic3;//иконка для крестика
    QIcon ic4;//иконка монетки
    QColorDialog *col1;
    bool stpd=false;
    bool isAnimationStarted;
    bool plsn=false;
    bool upgr=true;
    bool aut=false;
    bool aut1=true;
    bool bustb=false;//буст включен?
    long long score = 0;//начальный счет
    long long n = 1;//начальное значение клика
    long long n_1;//клон клика
    long long k=1;//начальное значение автоклика
    long long cost =100;//апгрейд клика
    long long cost2=10000;//покупка автоклика
    long long cost3=150;//прокачка автоклика
    long long cost4=1000;//буст
    long long timelf=10;//время для вывода
    int reset=1;
    int rtime=0;
    int rtime2=0;
    int rtime3=0;
    int mus=0;
    QFont font;
    QLabel *lbgif;
    QMovie *moviegf;
};

#endif
