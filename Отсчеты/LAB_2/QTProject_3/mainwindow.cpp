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
    QTime start_1 = QTime::currentTime();

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

    // Метод прибовления к матрице константы.
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

    // Метод умножения матрице на константу.
    auto F_1_2 = [this](QVector<double>& M, double value) -> QVector<double> {

        QVector<double> m;

            foreach(auto elem, M){

                m.push_back(value * elem);
            };

        return m;
    };

    // Метод сложения двух матриц.
    auto F_1_5 = [this](QVector<double>& M,QVector<double>& N) -> QVector<double> {

        QVector<double> m;

            for(size_t i = 0; i < Count.count(); i++){

                m.push_back(M[i] + N[i]);
            };

        return m;
    };

    // Метод транспонирования:
    auto T = [](QVector<QVector<double>>& M) -> QVector<QVector<double>> {

        QVector<QVector<double>> tM(M.count(), QVector<double>(M.count(),0));

        for(size_t i = 0; i < M.count(); i++){
            for(size_t j = 0; j < M.count(); j++){
                tM[i][j] = M[j][i];
            }
        }
        return tM;
    };

    auto norm_m_1 = [](QVector<QVector<double>>& M) -> double {

        auto V = [&](QVector<QVector<double>>& M) -> QVector<double> {

            auto summ_b = [](auto summ_b, QVector<double> M, size_t k) -> double {

                if(k == M.count()) return 0;

                return qAbs(M[k]) + summ_b(summ_b, M, k + 1);
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
    auto norm_i_1 = [&](QVector<QVector<double>>& M) -> double {

        auto V = [&](QVector<QVector<double>>& M) -> QVector<double> {


            QVector<QVector<double>> Tm = T(M);

            auto summ_b = [](auto summ_b, QVector<double> M, size_t k) -> double {

                if(k == M.count()) return 0;

                return qAbs(M[k]) + summ_b(summ_b, M, k + 1);
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
                    x += qPow(qAbs(M[i][j]), 2);
                }
            }
            return x;
        };

        return qSqrt(SUMM(M));
    };

    double norm_m(1), norm_i(1), norm_k(1);

    QVector<QVector<double>> R;
    QVector<double> r;

    double ip = 0;
    QVector<bool> count(A.count(), false);

    Count = count;

    // Метод сортировки строк матрицы в зависимости от того чтобы
    // на главной диагонали по возможности был максимальный элемент по отношению к элементам соответствующей строи/столбца.
    auto F_1_4 = [&](QVector<QVector<double>>& M, QVector<double>& N,QVector<bool>& count) -> void {
        auto SummAbs_i = [](QVector<double>& M, qint16 k) -> double {
            double x(0);

            for(size_t i = 0; i < M.count(); i++){

                if(i != k){
                    x += qAbs(M[i]);
                }
            }
            return x;
        };

        auto SummAbs_j = [](QVector<double>& M, qint16 k) -> double {
            double x(0);

            for(size_t i = 0; i < M.count(); i++){

                if(i != k){
                    x += qAbs(M[i]);
                }
            }
            return x;
        };

        for(size_t i = 0; i < M.count(); i++){
            for(size_t j = 0; j < M[i].count(); j++){
                if(( qAbs(M[j][i]) > SummAbs_i(M[j], i) ) && (qAbs(M[j][i]) > SummAbs_j(T(M)[j], i))){
                    qDebug() << j  << " : "  << i<< " : " << M[j][i] << " : " << SummAbs_i(M[j], i) << " : " << SummAbs_j(T(M)[j], j) << " : "<< "\033[32m" << true << "\033[0m";

                    count[i] = true;

                    std::swap(M[i], M[j]);
                    std::swap(N[i], N[j]);
                }else{
                    qDebug() << j  << " : "  << i << " : "  << M[j][i] << " : " << SummAbs_i(M[j], i) << " : " << SummAbs_j(T(M)[j], j) << " : " << false;
                }
            }
        }
        return;
    };

    // Менее требовательная функция к столбцам матрицы.
    auto F_1_4_2 = [&](QVector<QVector<double>>& M, QVector<double>& N,QVector<bool>& count) -> void {
        auto SummAbs_i = [](QVector<double>& M, qint16 k) -> double {
            double x(0);

            for(size_t i = 0; i < M.count(); i++){

                if(i != k){
                    x += qAbs(M[i]);
                }
            }
            return x;
        };


        auto SummAbs_j = [](QVector<double>& M, qint16 k) -> double {
            double x(0);

            for(size_t i = 0; i < M.count(); i++){

                if(i != k){
                    x += qAbs(M[i]);
                }
            }
            return x;
        };

        for(size_t i = 0; i < M.count(); i++){
            for(size_t j = 0; j < M[i].count(); j++){
                if(qAbs(M[j][i]) > SummAbs_i(M[j], i)){
                    qDebug() << j  << " : "  << i<< " : " << M[j][i] << " : " << SummAbs_i(M[j], i) << " : " << SummAbs_j(T(M)[j], j) << " : "<< "\033[32m" << true << "\033[0m";

                    count[i] = true;

                    std::swap(M[i], M[j]);
                    std::swap(N[i], N[j]);
                }else{
                    qDebug() << j  << " : "  << i << " : "  << M[j][i] << " : " << SummAbs_i(M[j], i) << " : " << SummAbs_j(T(M)[j], j) << " : " << false;
                }
            }
        }
        return;
    };

    F_1_4(A, B, count);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>A:</b>");
    PrintMatrix_2(A);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>B:</b>");
    PrintMatrix_1(B);

    F_1_4(A, B, count);

    // Метод проверки наличия строк для которых невыполняется условие (2.4)
    auto Cou = [&]()-> bool {
        bool x = false;
        foreach(auto elem, Count){
            if(!elem) x =!elem;
        };
        return x;
    };

    Count = count;

    // Метод сортировки строк в зависимости от наличия на главной диагонали
    // максимального по модулю элемента по стравнению с элементами в строке.
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

    F_1_4_2(A, B, count);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<hr>");

    Count = count;

    QVector<QVector<double>> origin_A = A;
    QVector<double> origin_B = B;
    // Цикл элементарных преобразований(диагонализации) по строке для строк, которые не выполняется условие (2.4).
    while(Cou())
    {
        for(size_t i = 0; i < Count.count(); i++){
            if(!Count[i]){

                QVector<qint16> H(A[i].count(),0);
                QVector<quint16> h(A[i].count(), 0);

                h[i] = 1;

                quint16 MAX = 4;
                QVector<size_t> ITER_BUFF_F(A[i].count(), 0);

                auto ITER_F = [&, this](auto iter_f, QVector<size_t>& iter_buff_f, size_t f) -> void {

                        if(f == 0)
                        {
                            QVector<int> ITER_BUFF_D(A[i].count(), 0);
                             QVector<double> C(A[i].count(),0);

                            auto ITER_D = [&](auto iter_d, QVector<size_t>& iter_buff_f,QVector<int>& iter_buff_d, int di) -> void {

                                    if(di == 0)
                                    {
                                        for(size_t z = 0; z < H.count(); z++)
                                        {
                                            H[z] = iter_buff_d[z] * iter_buff_f[z];
                                        }

                                        auto iterat_A = [&](auto it, QVector<qint16> H, int i) -> QVector<double> {

                                             if(i >= H.count()) return QVector<double>(A[i-1].count(), 0);

                                              QVector<double> F12 = F_1_2(origin_A[i], H[i]);//origin_A
                                              QVector<double> It = it(it, H, i + 1);

                                              return F_1_5( F12 , It);
                                         };

                                        C = iterat_A(iterat_A, H, 0);

                                        if(C[3] == -9 && C[0] == 3)
                                            qDebug() << "C: " << C[0] << "; " << C[1] << "; " <<C[2] << "; " << C[3] << "\n";

                                        auto SummAbs = [](QVector<double>& M, qint16 k) -> double {
                                           qint16 x(0);

                                           for(size_t i = 0; i < M.count(); i++){

                                               if(i != k){
                                                   x += qAbs(M[i]);
                                               }
                                           }

                                           return x;
                                        };

                                        auto T = [](QVector<QVector<double>>& M) -> QVector<QVector<double>> {

                                            QVector<QVector<double>> tM(M.count(), QVector<double>(M.count(),0));

                                            for(size_t i = 0; i < M.count(); i++){
                                                for(size_t j = 0; j < M.count(); j++){
                                                    tM[i][j] = M[j][i];
                                                }
                                            }
                                            return tM;
                                        };

                                        auto STEG = [](QVector<bool> Count) -> int{
                                            int x = Count.count() - 1;

                                            for(int i = Count.count() - 1; Count[i] && (i >= 0); --i){
                                                x--;
                                            }
                                            return x;
                                        };

                                        auto PRED = [&](QVector<QVector<double>>& M, QVector<double>& N, int k) -> bool{
                                            bool FLG_1 = false;
                                            for(int i = 0; i < N.count(); i++){
                                                QVector<QVector<double>> n = T(M);

                                                if(i != k){

                                                    int xd = SummAbs(n[i], k) - qAbs(M[i][i]) + qAbs(N[i]);

                                                    if((xd) >= qAbs(M[i][i])){
                                                        return false;
                                                    }

                                                }else if(i == k){

                                                        if(qAbs(N[i]) > SummAbs(n[i], k)){

                                                            FLG_1 = true;
                                                            return FLG_1;

                                                        }
                                                    }

                                                }
                                            return FLG_1;
                                        };


                                        if(C.count() > 0)
                                        {
                                            qDebug() << SummAbs(C, i);
                                            qDebug() << STEG(Count);

                                           if((i == STEG(Count)) && (qAbs(C[i]) > SummAbs(C, i)) ){

                                               if((PRED(A, C, i))){

                                                   auto F_1_6 = [&](QVector<double>& M, QVector<double>& N) -> void {

                                                       for(size_t u = 0; u < C.count() ; u++){
                                                           M[u] = N[u];
                                                       };
                                                   };

                                                   auto iterat_B = [&](auto it, QVector<qint16> H, qint16 j, size_t i) -> double {

                                                          if(i >= B.count()) return 0;

                                                           B[j] = origin_B[i] * H[i] + it(it,H,j, i + 1);

                                                       return B[j];
                                                   };

                                                   iterat_B(iterat_B, H, i, 0);

                                                   // Получение в консоли информации к какой строке какие коэффициенты
                                                   //  были применены для достижения в строке изсеняемой диагонализированного вида.
                                                   qDebug() << "H[0] : " << H[0];
                                                   qDebug() << "H[1] : " << H[1];
                                                   qDebug() << "H[2] : " << H[2];
                                                   qDebug() << "H[3] : " << H[3];

                                                   F_1_6(A[i] , C);

                                                   Count[i] = true;
                                               }else{

                                                   qDebug() << "H[0] : " << H[0];
                                                   qDebug() << "H[1] : " << H[1];
                                                   qDebug() << "H[2] : " << H[2];
                                                   qDebug() << "H[3] : " << H[3];

                                                   qDebug() << "При итерации не удалось найти решение";
                                               }

                                           }else if(qAbs(C[i]) > SummAbs(C, i) ){//&& (qAbs(C[i]) > SummAbs(T(A)[i], i))


                                               auto F_1_6 = [&](QVector<double>& M, QVector<double>& N) -> void {

                                                   for(size_t u = 0; u < C.count() ; u++){
                                                       M[u] = N[u];
                                                   };
                                               };

                                               auto iterat_B = [&](auto it, QVector<qint16> H, qint16 j, size_t i) -> double {

                                                      if(i >= B.count()) return 0;

                                                       B[j] = B[i] * H[i] + it(it,H,j, i + 1);

                                                   return B[j];
                                               };

                                               iterat_B(iterat_B, H, i, 0);

                                               // Получение в консоли информации к какой строке какие коэффициенты
                                               //  были применены для достижения в строке изсеняемой диагонализированного вида.
                                               qDebug() << "H[0] : " << H[0];
                                               qDebug() << "H[1] : " << H[1];
                                               qDebug() << "H[2] : " << H[2];
                                               qDebug() << "H[3] : " << H[3];

                                               F_1_6(A[i] , C);

                                               Count[i] = true;
                                           }
                                        }

                                    }else {

                                        for(int s = 1; (!Count[i]) && (s > (-2)); s-=2)
                                        {
                                            iter_buff_d[di - 1] = s;

                                            iter_d(iter_d, iter_buff_f, iter_buff_d, di - 1);
                                        }
                                    }
                            };

                            ITER_D(ITER_D, iter_buff_f, ITER_BUFF_D, A.count());

                        }else {
                            for(size_t t = h[f - 1];(!Count[i])  &&  (t < MAX); t++){

                                iter_buff_f[f - 1] = t;
                                iter_f(iter_f, iter_buff_f, f - 1);
                            }
                        }
                };

                ITER_F(ITER_F, ITER_BUFF_F, A.count());
            };
        };

        if(Cou()){
            qDebug() << "Программа не смогла деагонализировать матрицу. "
                        "Попробуйте увеличить глубину ассоциативности, указав значение выше "
                        "установленного в переменной MAX, строки кода:  [668].";
            exit(0);
        };
    };

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>A:</b>");
    PrintMatrix_2(A);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>B:</b>");
    PrintMatrix_1(B);

    ////////////////////////////////////
    // Метод выражения элементов матрицы в зависимости от элементов, стоящих на главной диагонали.
    auto F_2_2 = [](QVector<QVector<double>>& M) -> QVector<QVector<double>> {
         QVector<QVector<double>> m;

         auto F_2_4 = [](QVector<double> M, int value)-> QVector<double> {
             QVector<double> m;

             for(size_t i = 0; i < M.count(); i++){
                 m.push_back((M[i] / value));
             }

             return m;
         };

         for(size_t i = 0; i < M.count(); i++){
             m.push_back(F_2_4(M[i], -M[i][i]));
             m[i][i] = 0;
         }

         return m;
    };

    R = F_2_2(A);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>R:</b>");
    PrintMatrix_2(R);

    // Метод деления элементов матрицы по строке на соответствующий элемент, стоящий на главной диагонали.
    auto F_2_7 = [&](QVector<double> M) -> QVector<double>{
            QVector<double> m(M.count(),0);

            for(size_t n = 0; n < M.count(); n++){
                m[n] = M[n] / A[n][n];
            }

            return m;
    };

    r = F_2_7(B);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>r:</b>");
    PrintMatrix_1(r);

    ////////////////////////////////////

    norm_m = norm_m_1(R);
    norm_i = norm_i_1(R);
    norm_k = norm_k_1(R);

    qDebug() << norm_m;
    qDebug() << norm_i;
    qDebug() << norm_k;

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Норма m: </b>" + QString::number(norm_m));
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Норма i: </b>" + QString::number(norm_i) + "< 1;");
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Норма k: </b>" + QString::number(norm_k) + "< 1;");

    ///////////////////////////////////

    QVector<double> x_0 = r;
    QVector<double> x_i(B.count(), 0);
    QVector<double> x_j(B.count(), 0);

    double eps = Epsilon.qLineEdit->text().toDouble();

    // Метод проверки выхода из цикла итерации по достижению точности.
    auto FAb = [&](QVector<double>& M, QVector<double>& N, double& eps) -> bool {
        bool flg = false;
        for(size_t i = 0; i < M.count(); i++){
            if(fabs(M[i] - N[i]) >= eps){
                flg = true;
            }
        }
        return flg;
    };

    size_t counter = 0;

    do{
        if(counter == 0){
            x_i = x_0;
        }else{
            x_i = x_j;
        }

        counter++;

        auto FAST = [](QVector<QVector<double>>& M,QVector<double>& x_i,QVector<double>& b){

            auto SUMM = [](QVector<double>& m_i, QVector<double>& x_i) -> double {
                double x = 0;
                for(int i = 0; i < x_i.count(); i++){
                    x += m_i[i]*x_i[i];
                }

                return x;
            };

            QVector<double> d(x_i.count(), 0);

            for(int i = 0; i < x_i.count(); i++){
                d[i] = SUMM(M[i], x_i) + b[i];
            }

            return d;
        };

        x_j = FAST(R, x_i, r);

    } while(FAb(x_i, x_j, eps));

    ///////////////////////////////////////

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Ответ: </b>");
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>x: </b>");
    PrintMatrix_1(x_j);

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Количество итераций:</b>");
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml()  + QString::number(counter) + " ;");

    QTime finish = QTime::currentTime();
    double time = start_1.msecsTo(finish) / 1000.0;

    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml() + "<b>Время работы:</b>");
    ui->textBrowser_1->setHtml(ui->textBrowser_1->toHtml()  + QString::number(time) + " ;");
};
