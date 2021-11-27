#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QGridLayout>
#include <QLineEdit>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QVector>
//#include <functional>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include "ethread.h"
#include <QTime>

class EThread;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Elem
{
    QLineEdit* qLineEdit;
    qint16 row = 0, col = 0;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void func();
    void func_X();

    QVector<Elem>& GetQElem_s_2(){
        return qElem_s_2;
    };

    QVector<QVector<Elem>>& GetQElem_s_1(){
        return qElem_s_1;
    };

    double setNewValue(const QString& fhStr);

    int& GetORD(){
        return ORD;
    };

    bool GetPaus(){
        return paus;
    };

    void SetPaus(bool p){
         paus = p;
    };

    QMutex& GetMutex(){
        return mutex;
    };

    QVector<QVector<double>>& GU(){
        return U;
    };

    QVector<QVector<double>>& GC(){
        return C;
    };

    QVector<bool>& GetFLAG_s_Ethread(){
        return FLAG_s_Ethread;
    };

    void SetFLAG_s_Ethread(int index,bool flg){
        FLAG_s_Ethread[index - 1] = flg;
    };

private:
     QMutex mutex;
     EThread* thread_1;
     EThread* thread_2;

private slots:
    void on_pushButton_clicked();

    void on_spinBox_1_valueChanged(int arg1);

    void on_pushButton_2_clicked();

    void PrintMatrix_2(QVector<QVector<double>> Matrix);
    void PrintMatrix_1(QVector<double> Matrix);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QVector<QGridLayout> gridLayout;

    QVector<Elem> qElem_s_2;

    bool paus = false;

    QVector<QVector<Elem>> qElem_s_1;

    QVector<bool> FLAG_s_Ethread;

    int ORD;

    QVector<QVector<double>> U;
    QVector<QVector<double>> C;

    QVector<double> Y;
    QVector<double> X;


};
#endif // MAINWINDOW_H

