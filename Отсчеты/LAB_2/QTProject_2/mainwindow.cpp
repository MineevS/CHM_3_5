#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, (&MainWindow::func));

    ui->spinBox_1->setValue(4);

    ui->pushButton->setVisible(false);
    func_X();
}

void MainWindow::func_X()
{
    if(ui->spinBox_1->value() > 0)
    {
        /*double vecA[4][4] = {
            {3,1,-1,2},
            {-5,1,3,-4},
            {2,0,1,-1},
            {1,-5,+3,-3}
        };

        double vecB[4][1] = {
            {6},
            {-12},
            {1},
            {3}
        };*/

        /*double vecA[4][4] = {
            {3,1,-1,2},
            {-5,1,3,-4},
            {2,0,1,-1},
            {1,-5,+3,-3}
        };

        double vecB[4][1] = {
            {6},
            {-12},
            {1},
            {3}
        };*/

        double vecA[4][4] = {
            {4,2,-1,0.5},
            {1,-5,2,1},
            {2,1,-4,-1.5},
            {1,-0.4,0.8,-3}
        };

        double vecB[4][1] = {
            {4.5},
            {14},
            {-27.5},
            {-1.8}
        };

        if(qElem_s_1.count() == 4){
            foreach (auto qvec, qElem_s_1){
                foreach(auto elem, qvec){
                     elem.qLineEdit->setText(QString::number(vecA[elem.row][elem.col]));
                }
            }

            foreach(auto elem, qElem_s_2){
                elem.qLineEdit->setText(QString::number(vecB[elem.row][elem.col]));
            }
        }
    }
}

void MainWindow::func()
{
    if(ui->spinBox_1->value() < 10)
    {
        qDebug() << qElem_s_1.count()*qElem_s_1.count();

        if(qElem_s_1.count() > 0)
        {
            foreach (auto qvec, qElem_s_1) {

                foreach(auto elem, qvec)
                {
                    //qDebug() << elem.row <<  " : " << elem.col;

                    ui->gridLayout_3->itemAtPosition(elem.row, elem.col)->widget()->deleteLater();
                    ui->gridLayout_3->removeItem(ui->gridLayout_3->itemAtPosition(elem.row,elem.col));
                }

            }
            qElem_s_1.clear();
        }

        //qDebug() << "CountCol:" << ui->gridLayout_3->columnCount();

        ui->gridLayout_3->setGeometry(QRect(10, 10, 100, 1000));
        ui->spinBox_1->setValue(ui->spinBox_1->value() + 1);

        for(size_t i = 0; i < ui->spinBox_1->value(); i++){

                auto func = [i = i, ui = ui] () -> QVector<Elem> {

                    QVector<Elem> qvec;

                    for(size_t j = 0; j < ui->spinBox_1->value(); j++)
                    {
                        ui->horizontalSpacer_1->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_1->geometry().height());
                        ui->horizontalSpacer_2->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_1->geometry().height());

                        Elem elem;

                        elem.qLineEdit = new  QLineEdit;
                        elem.qLineEdit->setAlignment(Qt::AlignHCenter);

                        elem.row = i;
                        elem.col = j;

                        qvec.push_back(elem);

                        ui->gridLayout_3->addWidget(elem.qLineEdit,elem.row,elem.col,Qt::Alignment());
                    }
                        return qvec;
                };

                qElem_s_1.push_back(func());
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->timer->start(1000);
}

void MainWindow::on_spinBox_1_valueChanged(int arg1)
{
    if(arg1 >= 0){
        //qDebug() << qElem_s_1.count()*qElem_s_1.count();
        if(qElem_s_1.count() > 0){
            foreach (auto qvec, qElem_s_1){
                foreach(auto elem, qvec){
                    //qDebug() << elem.row <<  " : " << elem.col;
                    ui->gridLayout_3->itemAtPosition(elem.row, elem.col)->widget()->deleteLater();
                    ui->gridLayout_3->removeItem(ui->gridLayout_3->itemAtPosition(elem.row,elem.col));
                }
            }
            qElem_s_1.clear();
        }

        if(qElem_s_2.count() > 0){
            foreach(auto elem, qElem_s_2)
            {
                ui->gridLayout_6->itemAtPosition(elem.row, elem.col)->widget()->deleteLater();
                ui->gridLayout_6->removeItem(ui->gridLayout_6->itemAtPosition(elem.row,elem.col));
            }
            qElem_s_2.clear();
        }

        for(size_t i = 0; i < arg1; i++){

             Elem elem_B;

             elem_B.qLineEdit = new  QLineEdit;
             elem_B.qLineEdit->setAlignment(Qt::AlignHCenter);

             ui->horizontalSpacer_4->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_4->geometry().height());
             ui->horizontalSpacer_5->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_5->geometry().height());

             elem_B.row = i;
             elem_B.col = 0;

             qElem_s_2.push_back(elem_B);

             ui->gridLayout_6->addWidget(elem_B.qLineEdit,elem_B.row,elem_B.col,Qt::Alignment());

            auto func = [i = i, ui = ui, arg = arg1] () -> QVector<Elem> {

                QVector<Elem> qvec_1;

                for(size_t j = 0; j < arg; j++)
                {
                    if(arg<11){
                    ui->horizontalSpacer_1->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_1->geometry().height());
                    ui->horizontalSpacer_2->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_2->geometry().height());
                    }

                    if((arg<22) && (arg>10)){
                        ui->horizontalSpacer_1->changeSize(50/((i+1)),ui->horizontalSpacer_1->geometry().height());
                        ui->horizontalSpacer_2->changeSize(50/((i+1)),ui->horizontalSpacer_2->geometry().height());
                    }

                    if((arg<40) && (arg>29)){
                        ui->horizontalSpacer_1->changeSize(25/((i+1)),ui->horizontalSpacer_1->geometry().height());
                        ui->horizontalSpacer_2->changeSize(25/((i+1)),ui->horizontalSpacer_2->geometry().height());
                    }

                    Elem elem_A;

                    elem_A.qLineEdit = new  QLineEdit;
                    elem_A.qLineEdit->setAlignment(Qt::AlignHCenter);

                    elem_A.row = i;
                    elem_A.col = j;

                    qvec_1.push_back(elem_A);

                    ui->gridLayout_3->addWidget(elem_A.qLineEdit,elem_A.row,elem_A.col,Qt::Alignment());
                }
                    return qvec_1;
            };

            qElem_s_1.push_back(func());
        }
    }
}

double MainWindow::setNewValue(const QString& fhStr)
{
  bool ok(false);
  double d = fhStr.toDouble(&ok);
  if (ok) {
      return d;
  }else{
      exit(-1);
  }
}

void MainWindow::PrintMatrix_2(QVector<QVector<double>> Matrix){

    QString strHtml_M;
    //ui->textBrowser_1->setHtml("<b>A:</b>");
    if(Matrix.count() > 0){
        strHtml_M.append("<table border=1 style=\"border-collapse: collapse;\">");
        foreach (auto qvec, Matrix){
            strHtml_M.append("<tr>");
            foreach(auto elem, qvec){
                strHtml_M.append("<td align=center>");
                strHtml_M.append(" " + QString::number(elem) + " ");
                strHtml_M.append("</td>");
            }
            strHtml_M.append("</tr>");
        }
        strHtml_M.append("</table>");

        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_M);
    }
}

void MainWindow::PrintMatrix_1(QVector<double> Matrix)
{
    QString strHtml_B;
    //ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>B:</b>");
    if(qElem_s_2.count() > 0){
        strHtml_B.append("<table border=1 style=\"border-collapse: collapse;\">");
        foreach (auto elem_B, Matrix){
            strHtml_B.append("<tr>");
            strHtml_B.append("<td align=center>");
            strHtml_B.append(" " + QString::number(elem_B) + " ");
            strHtml_B.append("</td>");
            strHtml_B.append("</tr>");
        }
        strHtml_B.append("</table>");

        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_B);
    }
}

MainWindow * mwPointer(MainWindow *ptr = nullptr)
{
    static MainWindow * mvPtr = nullptr;
    if (ptr)
        mvPtr = ptr;
    return mvPtr;
}

void MainWindow::on_pushButton_2_clicked()
{
    QTime start = QTime::currentTime();

    ui->textBrowser_1->clear();

    QString strHtml_A;
    ui->textBrowser_1->setHtml("<b>A:</b>");
    if(qElem_s_1.count() > 0){
        strHtml_A.append("<table border=1 style=\"border-collapse: collapse;\">");
        foreach (auto qvec, qElem_s_1){
            strHtml_A.append("<tr>");
            foreach(auto elem_A, qvec){
                strHtml_A.append("<td align=center>");
                strHtml_A.append(" " + elem_A.qLineEdit->text() + " ");
                strHtml_A.append("</td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");

        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A);
    }

    //qDebug() << ui->textBrowser_1->toHtml();

    QString strHtml_B;
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>B:</b>");
    if(qElem_s_2.count() > 0){
        strHtml_B.append("<table border=1 style=\"border-collapse: collapse;\">");
        foreach (auto elem_B, qElem_s_2){
            strHtml_B.append("<tr>");
            strHtml_B.append("<td align=center>");
            strHtml_B.append(" " + elem_B.qLineEdit->text() + " ");
            strHtml_B.append("</td>");
            strHtml_B.append("</tr>");
        }
        strHtml_B.append("</table>");

        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_B);
    }

    /////////////////////////////////////////////
    this->ORD = ui->spinBox_1->value();
    QVector<QVector<double>> u(ORD, QVector<double>(ORD, 0));
    QVector<QVector<double>> c(ORD, QVector<double>(ORD, 0));
    QVector<bool> fLAG_s_Ethread(2, true);
    U = u;
    C = c;
    FLAG_s_Ethread = fLAG_s_Ethread;
    thread_1 = new EThread("thread 1", 1, *this);
    thread_2 = new EThread("thread 2", 2, *this);
    thread_1->start(QThread::TimeCriticalPriority);
    thread_2->start(QThread::TimeCriticalPriority);
    while(thread_1->isRunning() || thread_2->isRunning()){
        SuspendThread(MainWindow::thread());
    }
    if(FLAG_s_Ethread[0] && FLAG_s_Ethread[1]){
        qDebug() << "Матрицы U и C посчитаны успешно !";
    }
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>U:</b>");
    PrintMatrix_2(U);
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>C:</b>");
    PrintMatrix_2(C);
    QVector<double> y(ORD, 0);
    QVector<double> x(ORD, 0);
    Y = y;
    X = x;
    for(size_t i = 0; i< ORD; i++){
        if(i == 0){
            Y[i] = setNewValue(qElem_s_2[i].qLineEdit->text()) / (U[i][i]);
        }else{
            auto SUMM = [this, i](auto& summ,int start, int end) -> double{
                if(start > end) return 0;
                return U[i][start]*Y[start] + summ(summ,start + 1, end);
            };
            Y[i] = (setNewValue(qElem_s_2[i].qLineEdit->text()) - SUMM(SUMM,0, i - 1))/(U[i][i]);
        }
    }

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Y:</b>");
    PrintMatrix_1(Y);

    for(size_t i = ORD-1; i < ORD; i--){
        if(i == (ORD-1)){
            X[i] = Y[i];
        }else{
            auto SUMM = [this, i](auto& summ,int start, int end) -> double{
                if(start > end) return 0;
                return C[i][start]*X[start] + summ(summ,start + 1, end);
            };

            X[i] = Y[i] - SUMM(SUMM,i, ORD-1);
        }
    }

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Ответ: </b>");
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>X: </b>");
    PrintMatrix_1(X);

    QTime finish = QTime::currentTime();
    double time = start.msecsTo(finish) / 1000.0;

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Время работы программы: </b>");
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + QString::number(time));
}
