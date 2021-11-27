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

        double eps = 0.001;

        if((qElem_s_1.count() - 1) == ORD){
            for (size_t i = 0; i < qElem_s_1.count(); i++){
                qElem_s_1[i].qLineEdit->setText(QString::number(vecF[i]));
            }

            qElem_s_2[0].qLineEdit->setText(QString::number(vecS[0]));
            qElem_s_2[1].qLineEdit->setText(QString::number(vecS[1]));
        }

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
            }

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
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QTime start_1 = QTime::currentTime();

    ui->textBrowser_1->clear();

    this->ORD = ui->spinBox_1->value();

    QString strHtml_A;

    if(qElem_s_1.count() > 0){
        A = QVector<double>(ORD + 1, 0);
        strHtml_A.append("<b>A:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i <= ORD; i++){
                strHtml_A.append("<td align=center> " + qElem_s_1[i].qLineEdit->text() + " </td>");
                A[i] = qElem_s_1[i].qLineEdit->text().toDouble();
        }
        strHtml_A.append("</tr></table>");
    }

    if(qElem_s_2.count() > 0){
        B = QVector<double>(2, 0);
        strHtml_A.append("<b>B:</b><table border=1 style=\"border-collapse: collapse;\"><tr>");
        for(size_t i = 0; i < 2; i++){
                strHtml_A.append("<td align=center> " + qElem_s_2[i].qLineEdit->text() + " </td>");
                B[i] = qElem_s_2[i].qLineEdit->text().toDouble();
        }
        strHtml_A.append("</tr></table>");
    }

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A + "<p></p>");

    double eps = Epsilon.qLineEdit->text().toDouble();

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Точность расчетов:</b> ε = " + Epsilon.qLineEdit->text() + ";" + "<hr>");

    ////////////////////////////////////////////////

    auto s = [ORD = ORD,A = A](double x, size_t i = 1) -> double {

            double xi = 0;

            for(size_t j = i; j < A.count(); j++){

                xi += ( (-1) * ( A[j] / A[0] ) )* qPow(x, (ORD - j));
            }

        return qPow(xi, 1.0/(ORD));

    };

    size_t count = 0;
    double x_0 = B[0];
    double x_i(0), x_j(0);

    do{
        if(count == 0){
            x_i = x_0;
        }else{
            x_i = x_j;
        }
        count++;

        x_j = s(x_i);

        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>x_j = </b>" +  QString::number(x_j, 'f', Epsilon.qLineEdit->text().length() - 2) + " ;");
        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Номер итерации: </b>" +  QString::number(count, 'd', 0) + " ;");

    }while(qFabs(x_j - x_i) >= eps);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() +"<hr>" + "<b>Ответ: </b><b>x_j = </b> " +  QString::number(x_j, 'f', Epsilon.qLineEdit->text().length() - 2) + " ;");
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Номер итерации: </b>" +  QString::number(count, 'd', 0) + " ;");
    ////////////////////////////////////////////////

    QTime finish = QTime::currentTime();
    double time = start_1.msecsTo(finish) / 1000.0;

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Время работы: </b> " +  QString::number(time) + " ;");
};
