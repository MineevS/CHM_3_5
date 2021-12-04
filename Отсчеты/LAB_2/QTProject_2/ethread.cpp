#include "ethread.h"

EThread::EThread(QString thread_name, size_t ind, MainWindow& MW):
    name(thread_name), index(ind), mw(MW)
{
    this->moveToThread(this);
}

void EThread::Pause(){
    if(index == 1)
        mw.SetPaus(true);

    if(index == 2)
        mw.SetPaus(false);

    mw.SetFLAG_s_Ethread(index, true);
    mw.GetMutex().unlock();
}

void EThread::Resume(){
    if(index == 1){
        while(mw.GetPaus()){
            SuspendThread(this);
        }
    }

    if(index == 2){
        while(!mw.GetPaus()){
            SuspendThread(this);
        }
    }

    mw.GetMutex().lock();
}

void EThread::run()
{
    switch(index)
    {
    case(1):
            for(size_t j = 0; j < mw.GetORD(); j++)
            {
                Resume();
                for(size_t i = 0; i < mw.GetORD(); i++)
                {
                    if(j == 0){
                            mw.GU()[i][j] = mw.setNewValue(mw.GetQElem_s_1()[i][0].qLineEdit->text());

                    }else if(i>=j){

                        auto SUMM = [this, i, j](auto& summ,int start, int end) -> double{
                            if(start > end) return 0;
                            return mw.GU()[i][start]* mw.GC()[start][j] + summ(summ,start + 1, end);
                        };
                       mw.GU()[i][j] = mw.setNewValue(mw.GetQElem_s_1()[i][j].qLineEdit->text()) - SUMM(SUMM,0, j - 1);
                    }
                }
                Pause();
             }
        break;
    case(2):
        for(size_t i = 0; i < mw.GetORD(); i++) {
            Resume();
            for(size_t j = 0; j < mw.GetORD(); j++){
                if(i == j){
                    mw.GC()[i][j] = 1;
                }else if(j>i){
                    auto SUMM = [this, i, j](auto& summ,int start, int end) -> double{
                        if(start > end) return 0;
                        return mw.GU()[i][start]* mw.GC()[start][j] + summ(summ,start + 1, end);
                    };
                   mw.GC()[i][j] = ((mw.setNewValue(mw.GetQElem_s_1()[i][j].qLineEdit->text()) - SUMM(SUMM,0, j - 1))/(mw.GU()[i][i]));
                }
                if((i == 0) && (j >0)){
                    mw.GC()[i][j] = mw.setNewValue(mw.GetQElem_s_1()[i][j].qLineEdit->text()) / mw.GU()[i][i];
                }
            }
            Pause();
        }
        break;
    default:
        break;
    };
}
