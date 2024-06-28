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
    void on_exit_triggered();
    void onAnimationFinished();

    void on_upgrade4_clicked();
    void onUpgr2out();
    void ont_1();
    void ont_1_1();
    void hidefire();

private:
    Ui::MainWindow *ui;
    QPropertyAnimation *animation;//анимка
    QTimer *holdTimer;//таймер для задержки
    QTimer *displayTimer;//таймер для плюсиков
    QTimer *displayTimer2;//таймер для огоньков
    QTimer *upgradeTimer;//таймер автоклика
    QTimer *upgr2;//таймер буста
    QTimer *upgr2_1;//таймер буста_1
    QTimer *upgr2_1_1;//таймер буста_1_1
    QIcon ic1;//иконка при покупке авто
    QIcon ic2;//иконка при покупке буста
    bool isAnimationStarted;
    bool upgr=true;
    bool aut=false;
    bool aut1=true;
    bool bustb=false;//буст включен?
    long long score = 10000;//начальный счет
    long long n = 1;//начальное значение клика
    long long n_1;//клон клика
    long long k=1;//начальное значение автоклика
    long long cost =100;//апгрейд клика
    long long cost2=10000;//покупка автоклика
    long long cost3=150;//прокачка автоклика
    long long cost4=1000;//буст
    long long timelf=10;//время для вывода
    QFont font;
};

#endif
