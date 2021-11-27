#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, (&MainWindow::func));

    ui->spinBox_1->setValue(2);

    ui->pushButton->setVisible(false);

    func_X();
}

void MainWindow::func_X()
{
    ORD = ui->spinBox_1->value();

    if(ui->spinBox_1->value() > 0)
    {
        double vecF[4] = {1, -1, 1}; // // front - перед
        double vecT[4] = {2, 1, -7}; // // after - после

        double vecS[2] = {3.5, 4.5}; //Segment

        double eps = 0.001;

        if((qElem_s_1.count() - 1) == ORD){
            for (size_t i = 0; i < qElem_s_1.count(); i++){
                qElem_s_1[i].qLineEdit_f->setText(QString::number(vecF[i]));
                qElem_s_1[i].qLineEdit_a->setText(QString::number(vecT[i]));
            }

            qElem_s_2[0].qLineEdit_f->setText(QString::number(vecS[0]));
            qElem_s_2[1].qLineEdit_f->setText(QString::number(vecS[1]));
        }

        Epsilon.qLineEdit_f->setText(QString::number(eps));
    }
}

void MainWindow::func()
{
    /*
    if(ui->spinBox_1->value() < 10)
    {
        qDebug() << qElem_s_1.count()*qElem_s_1.count();

        if(qElem_s_1.count() > 0)
        {
            foreach (auto elem, qElem_s_1) {
                ui->gridLayout_3->itemAtPosition(elem.row_f, elem.col_f)->widget()->deleteLater();
                ui->gridLayout_3->removeItem(ui->gridLayout_3->itemAtPosition(elem.row_f,elem.col_f));
            }
            qElem_s_1.clear();
        }

        for(size_t i = 0; i < ui->spinBox_1->value(); i++){

                Elem elem;

                ui->horizontalSpacer_1->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_1->geometry().height());
                ui->horizontalSpacer_2->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_1->geometry().height());

                elem.qLineEdit_f = new  QLineEdit;
                elem.qLineEdit_f->setAlignment(Qt::AlignHCenter);

                elem.row_f = 0;
                elem.col_f = i;

                qElem_s_1.push_back(elem);

                ui->gridLayout_3->addWidget(elem.qLineEdit_f,elem.row_f,elem.col_f,Qt::Alignment());
        }
    }
    */
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
                ui->gridLayout_3->itemAtPosition(elem.row_f, elem.col_f)->widget()->deleteLater();
                ui->gridLayout_3->removeItem(ui->gridLayout_3->itemAtPosition(elem.row_f,elem.col_f));

                ui->gridLayout_3->itemAtPosition(elem.lrow, elem.lcol)->widget()->deleteLater();
                ui->gridLayout_3->removeItem(ui->gridLayout_3->itemAtPosition(elem.lrow,elem.lcol));

                ui->gridLayout_3->itemAtPosition(elem.row_a, elem.col_a)->widget()->deleteLater();
                ui->gridLayout_3->removeItem(ui->gridLayout_3->itemAtPosition(elem.row_a,elem.col_a));

                ui->gridLayout_3->itemAtPosition(elem.Crow_f, elem.Ccol_f)->widget()->deleteLater();
                ui->gridLayout_3->removeItem(ui->gridLayout_3->itemAtPosition(elem.Crow_f,elem.Ccol_f));
            }
            qElem_s_1.clear();
        }

        if(qElem_s_2.count() > 0){
            foreach(auto elem, qElem_s_2)
            {
                ui->gridLayout_6->itemAtPosition(elem.row_f, elem.col_f)->widget()->deleteLater();
                ui->gridLayout_6->removeItem(ui->gridLayout_6->itemAtPosition(elem.row_f,elem.col_f));
            }
            qElem_s_2.clear();
        }

        // Epsilon:

        if(Epsilon.qLineEdit_f != nullptr){
            ui->gridLayout_9->itemAtPosition(Epsilon.row_f, Epsilon.col_f)->widget()->deleteLater();
            ui->gridLayout_9->removeItem(ui->gridLayout_9->itemAtPosition(Epsilon.row_f,Epsilon.col_f));

            delete Epsilon.qLineEdit_f;
        }

            Epsilon.qLineEdit_f = new  QLineEdit;
            Epsilon.qLineEdit_f->setAlignment(Qt::AlignHCenter);
            Epsilon.row_f = 0;
            Epsilon.col_f = 0;

            ui->gridLayout_9->addWidget(Epsilon.qLineEdit_f,Epsilon.row_f,Epsilon.col_f,Qt::Alignment());

            for(size_t i = 0; i < 2; i++){
                Elem elem_B;

                elem_B.qLineEdit_f = new  QLineEdit;
                elem_B.qLineEdit_f->setAlignment(Qt::AlignHCenter);

                ui->horizontalSpacer_4->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_4->geometry().height());
                ui->horizontalSpacer_5->changeSize(100*((i+1)*(i+1)),ui->horizontalSpacer_5->geometry().height());

                elem_B.row_f = 0;
                elem_B.col_f = i;

                qElem_s_2.push_back(elem_B);

                ui->gridLayout_6->addWidget(elem_B.qLineEdit_f,elem_B.row_f,elem_B.col_f,Qt::Alignment());
            }

        for(size_t i = 0; i <= arg1*5; i+=5){

             Elem elem;

             ui->horizontalSpacer_1->changeSize(50,ui->horizontalSpacer_1->geometry().height());
             ui->horizontalSpacer_2->changeSize(1000/((i+2)),ui->horizontalSpacer_2->geometry().height());

             elem.qLineEdit_f = new  QLineEdit;
             elem.qLineEdit_f->setAlignment(Qt::AlignHCenter);
             elem.qLabel = new QLabel;
             elem.qLabel->setTextFormat(Qt::RichText);

             elem.qComboBox_f = new QComboBox;

             //elem.qComboBox_f->setMaximumWidth(100);

                 QString string_1 = " tan( , lg( , ( , 1 ";

                 // С помощью метода split() разделяем строку на подстроки
                 QStringList items_1 = string_1.split(",");

                 elem.qComboBox_f->addItems(items_1);

                 switch(arg1 - i/5){
                 case(1):
                      elem.qComboBox_f->setCurrentIndex(1);
                     break;
                 case(5):
                     elem.qComboBox_f->setCurrentIndex(0);
                 case(2):
                     elem.qComboBox_f->setCurrentIndex(3);
                     break;
                 default:
                     elem.qComboBox_f->setCurrentIndex(3);
                     break;
                 };

                 //elem.qComboBox_f->currentIndex();

                 //elem.qComboBox_f->setAttribute(Qt::AlignHCenter);

             elem.qLineEdit_a = new  QLineEdit;
             elem.qLineEdit_a->setAlignment(Qt::AlignHCenter);

              elem.qComboBox_a = new QComboBox;

                  QString string_2 = " + , ) + , ) , ^2 + , ^1 + , ^1 ) + , ^0 + , ^0";

                  // С помощью метода split() разделяем строку на подстроки
                  QStringList items_2 = string_2.split(",");

                  elem.qComboBox_a->addItems(items_2);

             //////////////////////
                  switch(arg1 - i/5){
                  case(0):
                       elem.qComboBox_a->setCurrentIndex(7);
                      break;
                  case(2):
                      elem.qComboBox_a->setCurrentIndex(4);
                      break;
                  case(1):
                      elem.qComboBox_a->setCurrentIndex(5);
                      break;
                  default:
                      elem.qComboBox_a->setCurrentIndex(0);
                      break;
                  };
             //////////////////////

             QFont newFont("Times New Roman", 12, QFont::Times, true);

              elem.qLabel->setFont(newFont);

              if(i < arg1*5){
                  elem.qLabel->setText("<html><head/><body><p>x<span style=\" vertical-align:super;\">""</span></p></body></html>");
              }else{
                  elem.qLabel->setText("<html><head/><body><p>x<span style=\" vertical-align:super;\">""</span></p></body></html>");
              }

             elem.row_f = 0;
             elem.col_f = i;

             elem.Crow_f = 0;
             elem.Ccol_f = i + 1;

             elem.row_a = 0;
             elem.col_a = i + 2;

             elem.lrow = 0;
             elem.lcol = i + 3;

             elem.Crow_a = 0;
             elem.Ccol_a = i + 4;

             qElem_s_1.push_back(elem);

             ui->gridLayout_3->addWidget(elem.qLineEdit_f,elem.row_f,elem.col_f,Qt::Alignment());
             ui->gridLayout_3->addWidget(elem.qLabel,elem.lrow,elem.lcol,Qt::Alignment());
             ui->gridLayout_3->addWidget(elem.qLineEdit_a,elem.row_a,elem.col_a,Qt::Alignment());
             ui->gridLayout_3->addWidget(elem.qComboBox_f,elem.Crow_f,elem.Ccol_f,Qt::Alignment());
             ui->gridLayout_3->addWidget(elem.qComboBox_a,elem.Crow_a,elem.Ccol_a,Qt::Alignment());
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QTime start_1 = QTime::currentTime();

    ui->textBrowser_1->clear();

    this->ORD = ui->spinBox_1->value();

    QString strHtml_A;

    if(qElem_s_1.count() > 0){
        A_f = QVector<double>(ORD + 1, 0);
        A_a = QVector<double>(ORD + 1, 0);

        C_f = QVector<int>(ORD + 1, 0);
        C_a = QVector<int>(ORD + 1, 0);

        strHtml_A.append("<b>A_f:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i <= ORD; i++){
                strHtml_A.append("<td align=center> " + qElem_s_1[i].qLineEdit_f->text() + " </td>");
                A_f[i] = qElem_s_1[i].qLineEdit_f->text().toDouble();
        }
        strHtml_A.append("</tr></table>");

        strHtml_A.append("<b>A_a:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i <= ORD; i++){
                strHtml_A.append("<td align=center> " + qElem_s_1[i].qLineEdit_a->text() + " </td>");
                A_a[i] = qElem_s_1[i].qLineEdit_a->text().toDouble();
        }
        strHtml_A.append("</tr></table>");

        strHtml_A.append("<b>C_f:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i <= ORD; i++){
                strHtml_A.append("<td align=center> " + QString::number(qElem_s_1[i].qComboBox_f->currentIndex()) + " </td>");
                C_f[i] = qElem_s_1[i].qComboBox_f->currentIndex();
        }
        strHtml_A.append("</tr></table>");

        strHtml_A.append("<b>C_a:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i <= ORD; i++){
                strHtml_A.append("<td align=center> " + QString::number(qElem_s_1[i].qComboBox_a->currentIndex()) + " </td>");
                C_a[i] = qElem_s_1[i].qComboBox_a->currentIndex();
        }
        strHtml_A.append("</tr></table>");
    }

    if(qElem_s_2.count() > 0){
        B = QVector<double>(2, 0);
        strHtml_A.append("<b>B:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i < 2; i++){
                strHtml_A.append("<td align=center> " + qElem_s_2[i].qLineEdit_f->text() + " </td>");
                B[i] = qElem_s_2[i].qLineEdit_f->text().toDouble();
        }
        strHtml_A.append("</tr></table>");
    }

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");

    double eps = Epsilon.qLineEdit_f->text().toDouble();

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Точность расчетов:</b> ε = " + Epsilon.qLineEdit_f->text() + ";" + "<hr>");

    ////////////////////////////////////////////////


    auto f = [&](double x) -> double{

        double xi = 0;

        size_t ik = 0;

        std::function<double(int index, int i)> C_f_fun;

        auto C_a_fun = [&](int index, int i, double buff) -> double {

            if(buff == 0.0){

                switch(index)
                {
                case(0):
                    return 1.0;
                case(1):
                    return 1.0;
                case(2):
                    return 1.0;
                case(4):
                    return x;   // qPow(x, 1) ~ x
                case(7):
                    return 1;  // qPow(x, 1) ~ x
                default:
                    return 0;
                };

            }else {
                switch(index)
                {
                case(0):
                    ik++;
                    return 1.0f + ( ( A_f[i + 1] * C_f_fun(C_f[i + 1], i + 1) ) / buff );
                case(1):
                    return 1;
                case(2):
                    return 1;
                case(5):
                    return x;  // qPow(x, 1) ~ x
                case(7):
                    return 1;  // qPow(x, 1) ~ x
                default:
                    return 0;
                };
            }
            return 0;
        };

         C_f_fun = [&](int index, int i) -> double {//auto

            switch(index)
            {
            case(3):
                if((x == 0) && (ORD - i) == 0){
                    return A_a[i]*C_a_fun(C_a[i], i, 0.0);
                }else{
                    return A_a[i]*C_a_fun(C_a[i], i, 0.0);
                }
            case(0):
                if((x == 0) && (ORD - i) == 0){
                    return qTan( A_a[i] * C_a_fun( C_a[i], i, ( A_a[i] * qPow(x, ORD - i) )));// m *(1 + (... / (buff = m))) == (m + ...);
                }else{
                    return qTan( A_a[i] * qPow(x, ORD - i) * C_a_fun( C_a[i], i, ( A_a[i] * qPow(x, ORD - i) )));
                }
            case(1):
                return std::log10( A_a[i] * C_a_fun( C_a[i], i, ( A_a[i] )));
            case(2):
               return 1;
            default:
                return 0;
            };
        };

        for(ik = 0; ik < qElem_s_1.count(); ik++)
        {
            xi += A_f[ik] * C_f_fun(C_f[ik], ik);
        }

        return xi;
    };

    auto fi = [&](double x) -> double{

        double xi = 0;

        size_t ik = 0;

        std::function<double(int index, int i)> C_f_fun;

        auto C_a_fun = [&](int index, int i, double buff) -> double {

            if(buff == 0.0){

                switch(index)
                {
                case(0):
                    return 1.0;
                case(1):
                    return 1.0;
                case(2):
                    return 1.0;
                case(3):
                    return 1.0;
                case(4):
                    return x;   // qPow(x, 1) ~ x
                case(5):
                    return 1;  // qPow(x, 1) ~ x
                case(6):
                    return 1;  // qPow(x, 1) ~ x
                case(7):
                    return 1;  // qPow(x, 1) ~ x
                default:
                    return 0;
                };

            }else {
                switch(index)
                {
                case(0):
                    ik++;
                    return 1.0f + ( ( A_f[i + 1] * C_f_fun(C_f[i + 1], i + 1) ) / buff );
                case(1):
                    return 1;
                case(2):
                    return 1;
                case(3):
                    return 1;
                case(4):
                    return 1;
                case(5):
                    return x;  // qPow(x, 1) ~ x
                case(6):
                    return x;  // qPow(x, 1) ~ x
                case(7):
                    return 1;  // qPow(x, 1) ~ x
                default:
                    return 0;
                };
            }
            return 0;
        };

         C_f_fun = [&](int index, int i) -> double {//auto

            switch(index)
            {
            case(0):
                return qTan( A_a[i] * C_a_fun( C_a[i], i, ( A_a[i] )));
            case(1):
                return std::log10( A_a[i] * C_a_fun( C_a[i], i, ( A_a[i] )));
            case(2):
                return 1;
            case(3):
                return A_a[i]*C_a_fun(C_a[i], i, 0.0);
            default:
                return 0;
            };
        };

        for(ik = 1; ik < qElem_s_1.count(); ik++)
        {
            xi += (-1) * A_f[ik] * C_f_fun(C_f[ik], ik) / A_a[0]*A_f[0];
        }

        return xi;
    };

    double x_0(0), x_i(0), x_j(0), b(0);

    x_0 = B[0];

    size_t count = 0;

    do{
        if(count == 0){
            x_i = x_0;
        }else{
            x_i = x_j;
        }

        count++;

        x_j = fi(x_i);

        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>x_j = </b>"
                                   + QString::number(x_j, 'f', Epsilon.qLineEdit_f->text().length() - 2) + " ;");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Номер итерации: </b>" +  QString::number(count, 'd', 0) + " ;");

    }while(qFabs(x_j - x_i) >= eps);

    ////////////////////////////////////////////////

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() +"<hr>" + "<b>Ответ: </b><b>x_j = </b> "
                               + QString::number(x_j, 'f', Epsilon.qLineEdit_f->text().length() - 2) + " ;");
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Итерация номер: </b>" +  QString::number(count, 'd', 0) + " ;");

    QTime finish = QTime::currentTime();
    double time = start_1.msecsTo(finish) / 1000.0;

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Время работы: </b> " +  QString::number(time) + " ;");
};
