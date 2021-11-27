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
#include <QtCore/qmath.h>
//#include <QtGlobal>
#include "ethread.h"
#include <QTime>
#include <QLabel>
#include <QComboBox>

class EThread;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Elem
{
    QLineEdit* qLineEdit_a = nullptr; // after - после
    qint16 row_a = 0, col_a = 0;

    QLabel* qLabel = nullptr;
    qint16 lrow = 0, lcol = 0;

    QComboBox* qComboBox_f; // front - перед
    qint16 Crow_f = 0, Ccol_f = 0;

    QLineEdit* qLineEdit_f = nullptr; // front - перед
    qint16 row_f = 0, col_f = 0;

    QComboBox* qComboBox_a;
    qint16 Crow_a = 0, Ccol_a = 0; // after - после

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

    QVector<Elem>& GetQElem_s_1(){
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

    QVector<double>& GA(){
        return A_f;
    };

    QVector<QVector<double>>& GB(){
        return C;
    };

    QVector<bool>& GetFLAG_s_Ethread(){
        return FLAG_s_Ethread;
    };

    void SetFLAG_s_Ethread(int index,bool flg){
        FLAG_s_Ethread[index - 1] = flg;
    };

    QVector<bool> GetCount(){
        return Count;
    }

private:
     QMutex mutex;
     EThread* thread_1;
     EThread* thread_2;

private slots:
    void on_pushButton_clicked();

    void on_spinBox_1_valueChanged(int arg1);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QVector<QGridLayout> gridLayout;

    ////////////////////////
    QAbstractItemModel* _qAIM;


    ////////////////////////

    Elem Epsilon;
    ////////////////////////

    QVector<Elem> qElem_s_2;

    bool paus = false;

    QVector<Elem>qElem_s_1;

    QVector<bool> FLAG_s_Ethread;

    int ORD;

    QVector<double> A_f;
    QVector<double> A_a;

    QVector<int> C_f;
    QVector<int> C_a;
    QVector<QVector<double>> C;
    QVector<double> B;

    QVector<double> Y;
    QVector<double> X;

    QVector<bool> Count;


};
#endif // MAINWINDOW_H

