#include "sac.h"

sac::sac()
{

   sac_m = "EEEEEEEEEEEEEEEAAAAAAAAAIIIIIIIINNNNNNRRRRRRSSSSSSTTTTTTUUUUUULLLLLDDDMMMGGBBCCPPFFHHVVJQKWXYZ__";
   //sac_m = "EEEEEEEEEEEEEEEAAAAAAAAAIIIIIIIINNNNNNRRRRRRSSSSSSTTTTTT________________________________________";
}

QString sac::remplirMain(int n)
{
    QString letters;
    srand(QDateTime::currentDateTime().toTime_t());


    if(n<=sac_m.count())  {

    for(int i=0;i<n;i++)
    {
    int rnd=qrand() % sac_m.count();

    letters.append(sac_m.at(rnd));
    sac_m.remove(sac_m.at(rnd));

    qDebug() << "letters in hand:" << letters;
    }
    return letters;

    }  else return "";

}


/*
 *
 *
    2 blank tiles (scoring 0 points)
    1 point: E ×15, A ×9, I ×8, N ×6, O ×6, R ×6, S ×6, T ×6, U ×6, L ×5
    2 points: D ×3, M ×3, G ×2
    3 points: B ×2, C ×2, P ×2
    4 points: F ×2, H ×2, V ×2
    8 points: J ×1, Q ×1
    10 points: K ×1, W ×1, X ×1, Y ×1, Z ×1
*/
