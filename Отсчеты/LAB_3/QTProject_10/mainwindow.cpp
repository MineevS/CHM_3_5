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

        QVector<double> lE_s_1 = {1, -1, 1, -0.5};

        QVector<double> lE_s_2 = {1, -1, 1, -3};

        QVector<double> lE_s_3 = {0, 0};//{1.2, 3.4}

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
        this->ui->lE_8->setText(QString::number(lE_s_2[3]));

        this->ui->lE_9->setText(QString::number(lE_s_3[0]));
        this->ui->lE_10->setText(QString::number(lE_s_3[1]));

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
    LE_s_2[3] = this->ui->lE_8->text().toDouble();

    LE_s_3[0] = this->ui->lE_9->text().toDouble();
    LE_s_3[1] = this->ui->lE_10->text().toDouble();

    /////////////
    QString strHtml_A;

    strHtml_A.append("<b>ƒ_1:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");

    foreach(auto elem, LE_s_1){

        strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>");
    }

    strHtml_A.append("</tr></table>");

    /////////////


    strHtml_A.append("<b>ƒ_2:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");

    foreach(auto elem, LE_s_2){

        strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>");
    }

    strHtml_A.append("</tr></table>");

    /////////////
    // ƒ_1 = qCos(LE_s_1[0]*x_k_1+LE_s_1[1])+LE_s_1[2]*x_k_2+LE_s_1[3];
    // ƒ_2 = LE_s_2[0]*x_k_2 + LE_s_2[1]*qCos(LE_s_2[2]*x_k_1)+LE_s_2[3];

    strHtml_A.append("<b>X^(0): </b><table border=1 style=\"border-collapse: collapse;\"><tr>");

    foreach(auto elem, LE_s_3){

        strHtml_A.append("<td align=center> " + QString::number(elem) + " </td>");
    }

    strHtml_A.append("</tr></table>");

    /////////////

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Точность расчетов:</b> ε = " + Epsilon.qLineEdit->text() + ";" + "<hr>");

    ////////////////////////////////////////////////

    auto F_X = [&](QVector<double> x_k) -> QVector<double>{
        QVector<double> f_k(2, 0);
            f_k[0] = LE_s_1[2]*x_k[0]+ qCos(LE_s_1[0]*x_k[1] + LE_s_1[1]) + LE_s_1[3];
            f_k[1] = LE_s_2[1]*qCos(LE_s_2[2]*x_k[0]) + LE_s_2[0]*x_k[1] + LE_s_2[3];
        return f_k;
    };

    auto W_X = [&](QVector<double> x_k) -> QVector<QVector<double>> {
        QVector<QVector<double>> w_k(2, QVector<double>(2, 0));
        w_k[0][0] = 1;
        w_k[0][1] = (-1) * qSin(LE_s_1[0]*x_k[1] + LE_s_1[1]);
        w_k[1][0] = LE_s_2[2]*LE_s_2[1]*(-1)*qSin(LE_s_2[2]*x_k[0]);
        w_k[1][1] = 1;
        return w_k;
    };

    auto T = [&](QVector<QVector<double>> M) -> QVector<QVector<double>> {
        QVector<QVector<double>> C(M.count(), QVector<double>(M.count(), 0));
        for(int i = 0; i < M.count(); i++){
            for(int j = 0; j < M.count(); j++){
               C[i][j] = M[j][i];
            }
        }
        return C;
    };

    auto M_multipliaclion_N = [&](QVector<QVector<double>> M, QVector<QVector<double>> N) -> QVector<QVector<double>> {
        QVector<QVector<double>> C(M.count(), QVector<double>(M.count(), 0));

        auto SM = [](QVector<double> M, QVector<double> N) -> double {
            double c = 0;
            for(int i = 0; i < M.count(); i++){
                c += M[i]*N[i];
            }
            return c;
        };

        for(int i = 0; i < M.count(); i++){
            for(int j = 0; j < M.count(); j++){
                C[i][j] = SM(M[i], T(N)[j]);
            }
        }

        return C;
    };

    auto C_multipliaclion_N = [&](double c, QVector<double> N) -> QVector<double> {
        QVector<double> C(N.count(), 0);

        for(int i = 0; i < N.count(); i++){
           C[i] = c * N[i];
        }

        return C;
    };

    auto M_multipliaclion_2_N = [&](QVector<QVector<double>> M, QVector<double> N) -> QVector<double> {
        QVector<double> C(M.count(), 0);
        // TODO;
        auto SM = [](QVector<double> M, QVector<double> N) -> double {
            double c = 0;

            for(int i = 0; i < M.count(); i++){
                c += M[i]*N[i];
            }

            return c;
        };

        for(int i = 0; i < M.count(); i++){
            C[i] = SM(M[i], N);
        }

        return C;
    };

    QVector<double> X_0 = LE_s_3;

    auto FAbs = [&](QVector<double> x_k, QVector<double> x_k_1,double eps) -> bool {
        bool FLAG = false;
        for(int i = 0; i < x_k.count();i++){
            if(qAbs(x_k_1[i] - x_k[i]) > eps){
                FLAG = true;
                return FLAG;
            }
        }

        return  FLAG;
    };

    auto Subtract = [](QVector<double> x_k, QVector<double> x_k_j) -> QVector<double> {
        // TODO;
        QVector<double> n_k(x_k.count(), 0);

        for(int i = 0; i < x_k.count(); i++){
            n_k[i] = x_k[i] - x_k_j[i];
        }

        return n_k;
    };

    auto Scalar = [](QVector<double> M, QVector<double> N) -> double {
    // TODO;
        double C = 0;

        for(int i = 0; i < M.count(); i++){
           C += M[i]* N[i];
        }

        return C;
    };

    auto n = [&](QVector<double> x_k) -> double {
        double n_k;

        n_k = (Scalar(F_X(x_k) , M_multipliaclion_2_N(M_multipliaclion_N(W_X(x_k), T(W_X(x_k))), F_X(x_k)))) /
                (Scalar(M_multipliaclion_2_N(M_multipliaclion_N(W_X(x_k), T(W_X(x_k))), F_X(x_k)), M_multipliaclion_2_N(M_multipliaclion_N(W_X(x_k), T(W_X(x_k))), F_X(x_k))));

        return n_k;
    };

    int count = 0;
    QVector<double> x_k(X_0.count(), 0);
    QVector<double> x_k_1(X_0.count(), 0);

    do{

        if(count == 0){
            x_k = X_0;
        }else{
            x_k = x_k_1;
        }
        count++;

        x_k_1 = Subtract(x_k , C_multipliaclion_N(n(x_k), M_multipliaclion_2_N( T(W_X(x_k)), F_X(x_k) )));

        //////////////////////////////

        QString strHtml_C;

        strHtml_C.append("<b>x_j:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");

        foreach(auto elem, x_k_1){

            strHtml_C.append("<td align=center> " + QString::number(elem) + " </td>");
        }

        strHtml_C.append("</tr></table>");

        //////////////////////////////
         ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_C + "<p></p>");

         qDebug() << QString::number( x_k_1[0]) + " : " + QString::number(x_k_1[1]) + "\n";

         //qDebug() << QString::number( x_k_1[0] - x_k[0]) + " : " + QString::number(x_k_1[1] - x_k[1]) + "\n";

          //ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + QString::number( x_k_1[0] - x_k[0]) + " : " + QString::number(x_k_1[1] - x_k[1]) + " " + "<p></p>");

    }while(FAbs(x_k , x_k_1, eps));

    ////////////////////////////////////////////////
    QString strHtml_C;
    strHtml_C.append("<hr><b>Ответ: </b><b>x_j:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");

    foreach(auto elem, x_k_1){

        strHtml_C.append("<td align=center> " + QString::number(elem) + " </td>");
    }

    strHtml_C.append("</tr></table>");

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_C + "<p></p>");
    ////////////////////////////////////////////////

    QTime finish = QTime::currentTime();

    double time = start_1.msecsTo(finish) / 1000.0;

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Время работы: </b> " +  QString::number(time) + " ;");
};
