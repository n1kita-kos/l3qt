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

private:
    Ui::MainWindow *ui;
    QPropertyAnimation *animation;
    QTimer *holdTimer;
    QTimer *displayTimer;
    QTimer *upgradeTimer;
    bool isAnimationStarted;
    int score = 0;
    int n = 1;
    int k=1;
    int cost =100;
    int cost2=10;
    int cost3=10;
    QFont font;
};

#endif // MAINWINDOW_H
