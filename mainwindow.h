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

private:
    Ui::MainWindow *ui;
    QPropertyAnimation *animation;
    QTimer *holdTimer;
    QTimer *displayTimer;
    QTimer *upgradeTimer;
    QIcon ic1;
    bool isAnimationStarted;
    bool upgr=true;
    bool aut=false;
    bool aut1=true;
    long long score = 0;
    long long n = 1;
    long long k=1;
    long long cost =100;
    long long cost2=10000;
    long long cost3=100;
    QFont font;
};

#endif
