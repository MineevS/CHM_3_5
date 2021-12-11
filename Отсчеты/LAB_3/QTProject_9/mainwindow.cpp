#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, (&MainWindow::func));

    ui->spinBox_1->setValue(3);

    ui->pushButton->setVisible(false);

    func_X();
}

void MainWindow::func_X()
{
    ORD = ui->spinBox_1->value();

    if(ui->spinBox_1->value() > 0)
    {
        double vecF[4] = {1, -3, 6, -5}; // f(x)

        double vecS[2] = {1, 3}; //Segment

        QVector<double> lE_s_1 = {1, 1, 0.1, 1.5};

        QVector<double> lE_s_2 = {-1, 1, 1};
        QVector<double> lE_s_3 = {-0.59, -0.81};

        /*
        QVector<double> lE_s_2 = {1, 1, 1};
        QVector<double> lE_s_3 = {0.68, 0.5};
        */

        this->LE_s_1 = lE_s_1;// Получение данных от первого элемента системы.
        this->LE_s_2 = lE_s_2;// Получение данных от второго элемента системы.
        this->LE_s_3 = lE_s_3;// Получение данных от второго элемента системы.

         this->eps = 0.001;

        this->ui->lE_1->setText(QString::number(lE_s_1[0]));
        this->ui->lE_2->setText(QString::number(lE_s_1[1]));
        this->ui->lE_3->setText(QString::number(lE_s_1[2]));
        this->ui->lE_4->setText(QString::number(lE_s_1[3]));

        this->ui->lE_5->setText(QString::number(lE_s_2[0]));
        this->ui->lE_6->setText(QString::number(lE_s_2[1]));
        this->ui->lE_7->setText(QString::number(lE_s_2[2]));

        this->ui->lE_8->setText(QString::number(lE_s_3[0]));
        this->ui->lE_9->setText(QString::number(lE_s_3[1]));


        //this->ui->lE_4->setText(QString::number(lE_s_1[3]));

        /*if((qElem_s_1.count() - 1) == ORD){
            for (size_t i = 0; i < qElem_s_1.count(); i++){
                qElem_s_1[i].qLineEdit->setText(QString::number(vecF[i]));
            }

            qElem_s_2[0].qLineEdit->setText(QString::number(vecS[0]));
            qElem_s_2[1].qLineEdit->setText(QString::number(vecS[1]));
        }*/

        Epsilon.qLineEdit->setText(QString::number(eps));
    }
}

void MainWindow::func()
{
    if(ui->spinBox_1->value() < 10)
    {
        qDebug() << qElem_s_1.count()*qElem_s_1.count();

        if(qElem_s_1.count() > 0)
        {
            foreach (auto elem, qElem_s_1) {
                ui->gridLayout_3->itemAtPosition(elem.row, elem.col)->widget()->deleteLater();
                ui->gridLayout_3->removeItem(ui->gridLayout_3->itemAtPosition(elem.row,elem.col));
            }
            qElem_s_1.clear();
        }

        //qDebug() << "CountCol:" << ui->gridLayout_3->columnCount();

        //ui->gridLayout_3->setGeometry(QRect(10, 10, 100, 1000));
        //ui->spinBox_1->setValue(ui->spinBox_1->value() + 1);

        for(size_t i = 0; i < ui->spinBox_1->value(); i++){

                Elem elem;

                ui->horizontalSpacer_1->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_1->geometry().height());
                ui->horizontalSpacer_2->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_1->geometry().height());

                elem.qLineEdit = new  QLineEdit;
                elem.qLineEdit->setAlignment(Qt::AlignHCenter);

                elem.row = 0;
                elem.col = i;

                qElem_s_1.push_back(elem);

                ui->gridLayout_3->addWidget(elem.qLineEdit,elem.row,elem.col,Qt::Alignment());
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

        if(qElem_s_1.count() > 0){
            foreach (auto elem, qElem_s_1){
                ui->gridLayout_3->itemAtPosition(elem.row, elem.col)->widget()->deleteLater();
                ui->gridLayout_3->removeItem(ui->gridLayout_3->itemAtPosition(elem.row,elem.col));

                ui->gridLayout_3->itemAtPosition(elem.lrow, elem.lcol)->widget()->deleteLater();
                ui->gridLayout_3->removeItem(ui->gridLayout_3->itemAtPosition(elem.lrow,elem.lcol));
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

        // Epsilon:

        if(Epsilon.qLineEdit != nullptr){
            ui->gridLayout_9->itemAtPosition(Epsilon.row, Epsilon.col)->widget()->deleteLater();
            ui->gridLayout_9->removeItem(ui->gridLayout_9->itemAtPosition(Epsilon.row,Epsilon.col));

            delete Epsilon.qLineEdit;
        }

            Epsilon.qLineEdit = new  QLineEdit;
            Epsilon.qLineEdit->setAlignment(Qt::AlignHCenter);
            Epsilon.row = 0;
            Epsilon.col = 0;

            ui->gridLayout_9->addWidget(Epsilon.qLineEdit,Epsilon.row,Epsilon.col,Qt::Alignment());
/*
            for(size_t i = 0; i < 2; i++){
                Elem elem_B;

                elem_B.qLineEdit = new  QLineEdit;
                elem_B.qLineEdit->setAlignment(Qt::AlignHCenter);

                ui->horizontalSpacer_4->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_4->geometry().height());
                ui->horizontalSpacer_5->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_5->geometry().height());

                elem_B.row = 0;
                elem_B.col = i;

                qElem_s_2.push_back(elem_B);

                ui->gridLayout_6->addWidget(elem_B.qLineEdit,elem_B.row,elem_B.col,Qt::Alignment());
            }*/
        /*
        for(size_t i = 0; i <= arg1*2; i+=2){

             Elem elem;

             ui->horizontalSpacer_1->changeSize(50,ui->horizontalSpacer_1->geometry().height());
             ui->horizontalSpacer_2->changeSize(1000/((i+2)),ui->horizontalSpacer_2->geometry().height());

             elem.qLineEdit = new  QLineEdit;
             elem.qLineEdit->setAlignment(Qt::AlignHCenter);
             elem.qLabel = new QLabel;
             elem.qLabel->setTextFormat(Qt::RichText);

             QFont newFont("Times New Roman", 12, QFont::Times, true);

              elem.qLabel->setFont(newFont);

              if(i < arg1*2){
                  elem.qLabel->setText("<html><head/><body><p>x<span style=\" vertical-align:super;\">"+ QString::number(arg1 - i/2)+"</span>+</p></body></html>");
              }else{
                  elem.qLabel->setText("<html><head/><body><p>x<span style=\" vertical-align:super;\">"+ QString::number(arg1 - i/2)+"</span></p></body></html>");
              }

             elem.row = 0;
             elem.col = i;

             elem.lrow = 0;
             elem.lcol = i + 1;

             qElem_s_1.push_back(elem);

             ui->gridLayout_3->addWidget(elem.qLineEdit,elem.row,elem.col,Qt::Alignment());
             ui->gridLayout_3->addWidget(elem.qLabel,elem.lrow,elem.lcol,Qt::Alignment());
        }
        */

    }

}

void MainWindow::on_pushButton_2_clicked()
{
    QTime start_1 = QTime::currentTime();

    ui->textBrowser_1->clear();

    //////////////////////

    LE_s_1[0] = this->ui->lE_1->text().toDouble();
    LE_s_1[1] = this->ui->lE_2->text().toDouble();
    LE_s_1[2] = this->ui->lE_3->text().toDouble();
    LE_s_1[3] = this->ui->lE_4->text().toDouble();

    LE_s_2[0] = this->ui->lE_5->text().toDouble();
    LE_s_2[1] = this->ui->lE_6->text().toDouble();
    LE_s_2[2] = this->ui->lE_7->text().toDouble();

    LE_s_3[0] = this->ui->lE_8->text().toDouble();
    LE_s_3[1] = this->ui->lE_9->text().toDouble();

    /////////////
    QString strHtml_A;

    strHtml_A.append("<b>φ_1:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");

    foreach(auto elem, LE_s_1){

        strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>");
    }

    strHtml_A.append("</tr></table>");

    /////////////

    strHtml_A.append("<b>φ_2:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");

    foreach(auto elem, LE_s_2){

        strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>");
    }

    strHtml_A.append("</tr></table>");

    /////////////


    strHtml_A.append("<b>X^(0): </b><table border=1 style=\"border-collapse: collapse;\"><tr>");

    foreach(auto elem, LE_s_3){

        strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>");
    }

    strHtml_A.append("</tr></table>");

    /////////////

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Точность расчетов:</b> ε = " + Epsilon.qLineEdit->text() + ";" + "<hr>");

    ////////////////////////////////////////////////
    QVector<double> X_0 = LE_s_3;

    auto fi_1 = [&](QVector<double> X_k) -> double {
        return (sin(LE_s_1[0] * X_k[0] + LE_s_1[1]*X_k[1]) + LE_s_1[2]) / LE_s_1[3];
    };

    auto fi_2 = [&](QVector<double> X_k) -> double {
        return LE_s_2[0]*sqrt(LE_s_2[1] - LE_s_2[2]*qPow(X_k[0], 2));
    };

    auto ITER = [&](QVector<double> X_k)->QVector<double>{

        QVector<double> X_kp1(X_k.count(), 0);

        X_kp1[0] = fi_1(X_k);
        X_kp1[1] = fi_2(X_k);

        return X_kp1;
    };

    auto FABS = [&](QVector<double> x_k,QVector<double>& x_kp1)-> bool{

        qDebug() << qMax(qAbs(x_kp1[0] - x_k[0]), qAbs(x_kp1[1] - x_k[1]));

        if(qMax(qAbs(x_kp1[0] - x_k[0]), qAbs(x_kp1[1] - x_k[1])) <= this->eps){
            return true;
        }else{
            return false;
        };

    };

    int count = 0;
    QVector<double> X_k(2, 0);
    QVector<double> X_kp1(2, 0);

    do{

        if(count == 0){
            X_k = X_0;
        }else{
            X_k = X_kp1;
        }

        count++;

        X_kp1 = ITER(X_k);

        //////////////////

        QString strHtml_X;
        strHtml_A.append("<b>φ_1:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        foreach(auto elem, X_kp1){
            strHtml_X.append("<td align=center> " + QString::number(elem) + " </td>");
        }
        strHtml_X.append("</tr></table>");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Номер итерации: </b>" +  QString::number(count, 'd', 0) + " ;");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_X + "<p></p>");


        //////////////////

    }while(!FABS(X_k, X_kp1));

     ////////////////////////////////////////////////

    QTime finish = QTime::currentTime();
    double time = start_1.msecsTo(finish) / 1000.0;

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Время работы: </b> " +  QString::number(time) + " ;");
};
