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

        double vecA[4][4] = {
            {2,3,-4,1},
            {1,-2,-5,1},
            {5,-3,1,-4},
            {10,2,-1,2}
        };

        double vecB[4][1] = {
            {3},
            {2},
            {1},
            {-4}
        };

        double eps = 0.01;

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
    ui->textBrowser_1->clear();

    this->ORD = ui->spinBox_1->value();

    QString strHtml_A;
    ui->textBrowser_1->setHtml("<b>A:</b>");
    if(qElem_s_1.count() > 0){
        QVector<QVector<double>> a(ORD, QVector<double>(ORD, 0));
        A = a;
        strHtml_A.append("<table border=1 style=\"border-collapse: collapse;\">");
        foreach (auto qvec, qElem_s_1){
            strHtml_A.append("<tr>");
            foreach(auto elem_A, qvec){
                strHtml_A.append("<td align=center>");
                strHtml_A.append(" " + elem_A.qLineEdit->text() + " ");
                A[elem_A.row][elem_A.col] = elem_A.qLineEdit->text().toDouble();
                strHtml_A.append("</td>");
            }
            strHtml_A.append("</tr>");
        }
        strHtml_A.append("</table>");

        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_A);
    }

    QString strHtml_B;
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>B:</b>");
    if(qElem_s_2.count() > 0){
        QVector<double> b(ORD, 0);
        B = b;
        strHtml_B.append("<table border=1 style=\"border-collapse: collapse;\">");
        foreach (auto elem_B, qElem_s_2){
            strHtml_B.append("<tr>");
            strHtml_B.append("<td align=center>");
            strHtml_B.append(" " + elem_B.qLineEdit->text() + " ");
            B[elem_B.row] = elem_B.qLineEdit->text().toDouble();
            strHtml_B.append("</td>");
            strHtml_B.append("</tr>");
        }
        strHtml_B.append("</table>");

        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + strHtml_B);
    }

    /////////////////////////////////////////////
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Точность ε = " +  Epsilon.qLineEdit->text() + "; </b>");

    if(Epsilon.qLineEdit->text().toDouble() == 0){
        qDebug() << "Не указана точность!";
        return;
    }
    /////////////////////////////////////////////
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>A:</b>");
    PrintMatrix_2(A);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>B:</b>");
    PrintMatrix_1(B);
    /////////////////////////////////////////////

    auto F_2_1 = [](QVector<QVector<double>>& M,double value) -> QVector<QVector<double>> {

        QVector<QVector<double>> m;

        foreach(auto row, M){

            QVector<double> m_i(row.size()/ 8);

            foreach(auto elem, row){

                m_i.push_back(elem + value);
            };

            m.push_back(m_i);
        };

        return m;
    };

    auto F_1_2 = [this](QVector<double>& M, double value) -> QVector<double> {

        QVector<double> m;

            foreach(auto elem, M){

                m.push_back(value * elem);
            };

        return m;
    };

    auto F_1_5 = [this](QVector<double>& M,QVector<double>& N) -> QVector<double> {

        QVector<double> m;

            for(size_t i = 0; i < Count.count(); i++){

                m.push_back(M[i] + N[i]);
            };

        return m;
    };

    auto F_2_3 = [this](QVector<QVector<double>>& M, double value) -> QVector<QVector<double>> {

        QVector<QVector<double>> m;

        foreach(auto row, M){
            QVector<double> m_ik(row.count() / 8);

            foreach(auto elem, row){

                m_ik.push_back(elem / value);
            };

            m.push_back(m_ik);
        };

        return m;
    };

    auto F_1_3 = [this](QVector<double>& M, double value) -> QVector<double> {

        QVector<double> m;

        foreach(auto elem, M){

            m.push_back(elem / value);
        };

        return m;
    };

    auto F_1_6 = [this](double M, qint16 value) -> double {

        return M * (double)value;
    };

    /*auto F_2_4 = [this](QVector<QVector<double>>& M, QVector<QVector<double>>& N) -> QVector<QVector<double>> {

        QVector<QVector<double>> m(ORD, QVector<double>(ORD,0));


        for(size_t i = 0; i < ORD; i++){
            for(size_t j = 0; j < ORD; j++){
                //m[i][j] = 0;
                for(size_t k = 0; k < ORD; k++){
                    m[i][j] += M[i][k]*N[k][j];
                }
            }

        }

        return m;
    };*/


    auto norm_m_1 = [](QVector<QVector<double>>& M) -> double {

        auto V = [&](QVector<QVector<double>>& M) -> QVector<double> {

            /* auto summ_a = [](QVector<double> M) -> double {
                  int x = 0;

                 for(size_t j = 0; j < M.count(); j++){
                     x += M[j];
                 }

                 return x;
             };*/

            auto summ_b = [](auto summ_b, QVector<double> M, size_t k) -> double {

                if(k == M.count()) return 0;

                return M[k] + summ_b(summ_b, M, k + 1);
            };

            QVector<double> v(M.count() , 0);

            for(size_t i = 0; i < M.count(); i++){
                v[i] = summ_b(summ_b, M[i], 0);
            }

            return v;
        };

        ////////////////////////////////////////////////////////////

        auto max = [](QVector<double> vec) -> double {

            return *std::max_element(vec.begin(),vec.end());
        };

        return max(V(M));
    };
    auto norm_i_1 = [](QVector<QVector<double>>& M) -> double {

        auto V = [&](QVector<QVector<double>>& M) -> QVector<double> {

            auto T = [](QVector<QVector<double>>& M) -> QVector<QVector<double>> {

                QVector<QVector<double>> tM(M.count(), QVector<double>(M.count(),0));

                for(size_t i = 0; i < M.count(); i++){
                    for(size_t j = 0; j < M.count(); j++){
                        tM[i][j]=M[j][i];
                    }
                }

                return tM;
            };

            QVector<QVector<double>> Tm = T(M);

            /* auto summ_a = [](QVector<double> M) -> double {
                  int x = 0;

                 for(size_t j = 0; j < M.count(); j++){
                     x += M[j];
                 }

                 return x;
             };*/

            auto summ_b = [](auto summ_b, QVector<double> M, size_t k) -> double {

                if(k == M.count()) return 0;

                return M[k] + summ_b(summ_b, M, k + 1);
            };

            QVector<double> v(M.count() , 0);

            for(size_t i = 0; i < M.count(); i++){
                v[i] = summ_b(summ_b, Tm[i], 0);
            }

            return v;
        };

        ////////////////////////////////////////////////////////////

        auto max = [](QVector<double> vec) -> double {
            return *std::max_element(vec.begin(), vec.end());
        };

        return max(V(M));
    };
    auto norm_k_1 = [](QVector<QVector<double>>& M) -> double {

        auto SUMM = [](QVector<QVector<double>>& M) -> double {
            double x = 0;
            for(size_t i = 0; i < M.count(); i++){
                for(size_t j = 0; j < M[i].count(); j++){
                    x += qPow(M[i][j], 2);
                }
            }
            return x;
        };

        return qSqrt(SUMM(M));
    };

    int norm_m(1), norm_i(1), norm_k(1);

    QVector<QVector<double>> R;
    QVector<QVector<double>> W;
    QVector<QVector<double>> G;

    QVector<QVector<double>> Q;
    QVector<QVector<double>> S;
    QVector<QVector<double>> D;

    QVector<double> r;

    double ip = 0;
    QVector<bool> count(A.count(), false);

    Count = count;

    auto F_1_4 = [](QVector<QVector<double>>& M, QVector<double>& N,QVector<bool>& count) -> void {

        auto SummAbs = [](QVector<double>& M, qint16 k) -> double {
            qint16 x(0);

            for(size_t i = 0; i < M.count(); i++){

                if(i != k){
                    x += qAbs(M[i]);
                }
            }

            return x;

        };

        QVector<double> m;

        for(size_t i = 0; i < M.count(); i++){

          for(size_t j = 0; j < M[i].count(); j++){

                if(qAbs(M[j][i]) > SummAbs(M[j], i)){

                    qDebug() << j  << " : "  << i<< " : " << M[j][i] << " : " << SummAbs(M[j], i) << " : " << "\033[32m" << true << "\033[0m";

                    count[i] = true;

                    std::swap(M[i], M[j]);
                    std::swap(N[i], N[j]);

                }else{
                    qDebug() << j  << " : "  << i << " : "  << M[j][i] << " : " << SummAbs(M[j], i) << " : " << false;
                }
        }

        }

        return;
    };

    F_1_4(A, B,count);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>A:</b>");
    PrintMatrix_2(A);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>B:</b>");
    PrintMatrix_1(B);

    F_1_4(A, B, count);

    auto Cou = [&]()-> bool {
        bool x = false;
        foreach(auto elem, Count){
            if(!elem) x =!elem;
        };
        return x;
    };

    Count = count;

    auto F_1_7 = [](QVector<QVector<double>>& M, QVector<double>& N, QVector<bool>& count) -> void {
        for(size_t i = 0; i < M.count(); i++){

            if(!count[i]){
                for(size_t j = 0; j < M.count(); j++){
                    if(!count[j]){

                        if(qAbs(M[i][j]) < qAbs(M[j][i])){
                            std::swap(M[i], M[j]);
                            std::swap(N[i], N[j]);
                        }
                    }
                }
            }
        }
    };

    F_1_7(A, B, count); // Перестановка строк по возрастанию для недиагонолизироанных строк.

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>A:</b>");
    PrintMatrix_2(A);
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>B:</b>");
    PrintMatrix_1(B);

    F_1_4(A, B,count);

    while(Cou())
    {
        for(size_t i = 0; i < Count.count(); i++){
            if(!Count[i]){
                QVector<qint16> H(A[i].count(),0);

                QVector<quint16> h(A[i].count(), 0);

                h[i] = 1;

                for(size_t t = h[3]; (!Count[i])  &&  (t < 4); t++){
                    for(size_t z = h[2]; (!Count[i])  &&  (z < 4); z++){
                         for(size_t k = h[1]; (!Count[i])  &&  (k < 4); k++){
                             for(size_t l = h[0]; (!Count[i]) && (l < 4); l++){

                                if(*std::max_element(A[h[i]].begin(),A[h[i]].end()) > A[i][i]){
                                    H[0] = -l;
                                    H[1] = k;
                                    H[2] = -z;
                                    H[3] = t;
                                }else {
                                      switch(i){
                                          case(1):
                                              H[0] = l;
                                              H[1] = k;
                                              H[2] = -z;
                                              H[3] = t;
                                              break;
                                          case(2):
                                              H[0] = l;
                                              H[1] = -z;
                                              H[2] = k;
                                              H[3] = -t;
                                            break;
                                      };
                                }

                                QVector<double> C(A[i].count(),0);
                               // QVector<double> D(A[i].count(),0);

                                auto iterat_A = [&](auto it, QVector<qint16> H, int i) -> QVector<double> {

                                    // qDebug() << "033\[31m" << H.count() << "033[0m";

                                     if(i >= H.count()) return QVector<double>(A[i-1].count(), 0);

                                      QVector<double> F12 = F_1_2(A[i], H[i]);
                                      QVector<double> It = it(it, H, i + 1);

                                      return F_1_5( F12 , It);
                                 };

                                C = iterat_A(iterat_A, H, 0);

                                auto SummAbs = [](QVector<double>& M, qint16 k) -> double {
                                   qint16 x(0);

                                   for(size_t i = 0; i < M.count(); i++){

                                       if(i != k){
                                           x += qAbs(M[i]);
                                       }
                                   }

                                   return x;
                                };

                                if(C.count() > 0){
                                       if(qAbs(C[i]) > SummAbs(C, i)){

                                           auto F_1_6 = [&](QVector<double>& M, QVector<double>& N) -> void {

                                               for(size_t u = 0; u < C.count() ; u++){
                                                   M[u] = N[u];
                                               };
                                           };

                                           auto iterat_B = [&](auto it, QVector<qint16> H, qint16 j, size_t i) -> double {

                                             // qDebug() << "033\[31m" << H.count() << "033[0m";

                                                  if(i >= B.count()) return 0;

                                                   B[j] = B[i] * H[i] + it(it,H,j, i + 1);

                                               return B[j];
                                           };

                                           iterat_B(iterat_B, H, i, 0);

                                           qDebug() << "H[0] : " << H[0];
                                           qDebug() << "H[1] : " << H[1];
                                           qDebug() << "H[2] : " << H[2];
                                           qDebug() << "H[3] : " << H[3];

                                           F_1_6(A[i] , C);

                                           //F_1_6(B , D);

                                           Count[i] = true;
                                       }
                                    }
                             }
                         }
                    }
                }
            }
        }
    }


 /*
while(ip < 2){
    ip += 0.1;
    Q = F_2_2(A, -1);// (-1)*A;
    S = F_2_1(Q, ip);// 1 + (-1)*A= 1 - A;
    D = F_2_3(S, ip);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Q:</b>");
    PrintMatrix_2(Q);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>S:</b>");
    PrintMatrix_2(S);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>D:</b>");
    PrintMatrix_2(D);
}



    for(size_t i = 0; i < D.count(); i++){
        if(D[i][i] == 0){
            qDebug() << "Матрица для данного метода простых иттераций не подходит!";
            break;
        }else{
            R.push_back(F_1_3(D[i], - D[i][i]));
            r.push_back(B[i] / D[i][i]);
        }
    }

    for(size_t i = 0; i < R.count(); i++){
        R[i][i] = 0;
    }

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>R:</b>");
    PrintMatrix_2(R);
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>r:</b>");
    PrintMatrix_1(r);

    norm_m = norm_m_1(R);
    norm_i = norm_i_1(R);
    norm_k = norm_k_1(R);
    */

    /*

    while((norm_m >= 1) || (norm_i >= 1) || (norm_k >= 1)){
        ++i;

        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b style = \"color: red;\" > " + QString::number(i) + " </b>");

        W = F_2_2(A, -1);// (-1)*A;
        R = F_2_1(W, i);// 1 + (-1)*A= 1 - A;

        G = F_2_3(A, i);

        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>W:</b>");
        PrintMatrix_2(W);

        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>R:</b>");
        PrintMatrix_2(R);

        ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>G:</b>");
        PrintMatrix_2(G);


        norm_m = norm_m_1(G);
        norm_i = norm_i_1(G);
        norm_k = norm_k_1(G);

        //qDebug() << norm_m;
        //qDebug() << norm_i;
        //qDebug() << norm_k;
    }*/

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>A:</b>");
    PrintMatrix_2(A);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>B:</b>");
    PrintMatrix_1(B);

    norm_m = norm_m_1(A);
    norm_i = norm_i_1(A);
    norm_k = norm_k_1(A);

    qDebug() << norm_m;
    qDebug() << norm_i;
    qDebug() << norm_k;




}
