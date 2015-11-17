/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "pieceslist.h"
#include "puzzlewidget.h"
#include "sac.h"

#include <QtWidgets>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupMenus();
    setupWidgets();

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setWindowTitle(tr("Puzzle"));

    lettersImage << QPixmap(":/images/A.png");
    lettersImage << QPixmap(":/images/B.png");
    lettersImage << QPixmap(":/images/C.png");
    lettersImage << QPixmap(":/images/D.png");
    lettersImage << QPixmap(":/images/E.png");
    lettersImage << QPixmap(":/images/F.png");
    lettersImage << QPixmap(":/images/G.png");
    lettersImage << QPixmap(":/images/H.png");
    lettersImage << QPixmap(":/images/I.png");
    lettersImage << QPixmap(":/images/J.png");
    lettersImage << QPixmap(":/images/K.png");
    lettersImage << QPixmap(":/images/L.png");
    lettersImage << QPixmap(":/images/M.png");
    lettersImage << QPixmap(":/images/N.png");
    lettersImage << QPixmap(":/images/O.png");
    lettersImage << QPixmap(":/images/P.png");
    lettersImage << QPixmap(":/images/Q.png");
    lettersImage << QPixmap(":/images/R.png");
    lettersImage << QPixmap(":/images/S.png");
    lettersImage << QPixmap(":/images/T.png");
    lettersImage << QPixmap(":/images/U.png");
    lettersImage << QPixmap(":/images/V.png");
    lettersImage << QPixmap(":/images/W.png");
    lettersImage << QPixmap(":/images/X.png");
    lettersImage << QPixmap(":/images/Y.png");
    lettersImage << QPixmap(":/images/Z.png");
    lettersImage << QPixmap(":/images/_.png");


    setupPuzzle();
}

void MainWindow::openImage(const QString &path)
{
 /*   QString fileName = path;

    if (fileName.isNull()) {
        fileName = QFileDialog::getOpenFileName(this,
            tr("Open Image"), "", "Image Files (*.png *.jpg *.bmp)");
    }

    if (!fileName.isEmpty()) {
        QPixmap newImage;
        if (!newImage.load(fileName)) {
            QMessageBox::warning(this, tr("Open Image"),
                                  tr("The image file could not be loaded."),
                                  QMessageBox::Cancel);
            return;
        }
        puzzleImage = newImage;
        setupPuzzle();
    }

    */
}

void MainWindow::setCompleted()
{
    QMessageBox::information(this, tr("Puzzle Completed"),
                             tr("Congratulations! You have completed the puzzle!\n"
                                "Click OK to start again."),
                             QMessageBox::Ok);

    setupPuzzle();
}

void MainWindow::setupPuzzle()
{
 /*   int size = qMin(puzzleImage.width(), puzzleImage.height());
    puzzleImage = puzzleImage.copy((puzzleImage.width() - size)/2,
        (puzzleImage.height() - size)/2, size, size).scaled(puzzleWidget->width(),
            puzzleWidget->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    piecesList->clear();

    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            int pieceSize = puzzleWidget->pieceSize();
            QPixmap pieceImage = puzzleImage.copy(x * pieceSize, y * pieceSize, pieceSize, pieceSize);
            piecesList->addPiece(pieceImage, QPoint(x, y));
        }
    }

    qsrand(QCursor::pos().x() ^ QCursor::pos().y());

    for (int i = 0; i < piecesList->count(); ++i) {
        if (int(2.0*qrand()/(RAND_MAX+1.0)) == 1) {
            QListWidgetItem *item = piecesList->takeItem(i);
            piecesList->insertItem(0, item);
        }
    }

    puzzleWidget->clear();


*/

    s1=new sac();

    qsrand(QCursor::pos().x() ^ QCursor::pos().y());

    QString main1=s1->remplirMain(7);

    qDebug() << main1;

    for(int i=0; i<main1.count();i++)

    {

    //qDebug() << lettersImage.at(i);


        QString c=main1.at(i);


        if(c=="") return;

        if(c=="A") model->addPieces(lettersImage.at(0),'A');
        if(c=="B") model->addPieces(lettersImage.at(1),'B');
        if(c=="C") model->addPieces(lettersImage.at(2),'C');
        if(c=="D") model->addPieces(lettersImage.at(3),'D');
        if(c=="E") model->addPieces(lettersImage.at(4),'E');
        if(c=="F") model->addPieces(lettersImage.at(5),'F');
        if(c=="G") model->addPieces(lettersImage.at(6),'G');
        if(c=="H") model->addPieces(lettersImage.at(7),'H');
        if(c=="I") model->addPieces(lettersImage.at(8),'I');
        if(c=="J") model->addPieces(lettersImage.at(9),'J');
        if(c=="K") model->addPieces(lettersImage.at(10),'K');
        if(c=="L") model->addPieces(lettersImage.at(11),'L');
        if(c=="M") model->addPieces(lettersImage.at(12),'M');
        if(c=="N") model->addPieces(lettersImage.at(13),'N');
        if(c=="O") model->addPieces(lettersImage.at(14),'O');
        if(c=="P") model->addPieces(lettersImage.at(15),'P');
        if(c=="Q") model->addPieces(lettersImage.at(16),'Q');
        if(c=="R") model->addPieces(lettersImage.at(17),'R');
        if(c=="S") model->addPieces(lettersImage.at(18),'S');
        if(c=="T") model->addPieces(lettersImage.at(19),'T');
        if(c=="U") model->addPieces(lettersImage.at(20),'U');
        if(c=="V") model->addPieces(lettersImage.at(21),'V');
        if(c=="W") model->addPieces(lettersImage.at(22),'W');
        if(c=="X") model->addPieces(lettersImage.at(23),'X');
        if(c=="Y") model->addPieces(lettersImage.at(24),'Y');
        if(c=="Z") model->addPieces(lettersImage.at(25),'Z');
        if(c=="_") model->addPieces(lettersImage.at(26),'_');



    }

    //qDebug() << main1;

    //main1=model->reverse(main1);
    //model->setMain(main1);

}

void MainWindow::setupMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAction = fileMenu->addAction(tr("&Open..."));
    openAction->setShortcuts(QKeySequence::Open);

    QAction *exitAction = fileMenu->addAction(tr("E&xit"));
    exitAction->setShortcuts(QKeySequence::Quit);

    QMenu *gameMenu = menuBar()->addMenu(tr("&Game"));

    QAction *restartAction = gameMenu->addAction(tr("&Restart"));

    connect(openAction, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(restartAction, SIGNAL(triggered()), this, SLOT(setupPuzzle()));
}

void MainWindow::setupWidgets()
{
    QFrame *frame = new QFrame;
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    puzzleWidget = new PuzzleWidget(780);

    model = new PiecesList(puzzleWidget->pieceSize(), this);


    connect(puzzleWidget, SIGNAL(puzzleCompleted()),
            this, SLOT(setCompleted()), Qt::QueuedConnection);

    valider = new QPushButton("Valider");

    connect(valider, SIGNAL(clicked()), puzzleWidget, SLOT(valid()));
    connect(valider, SIGNAL(clicked()), this, SLOT(fillHand()));


    frameLayout->addWidget(model);

    frameLayout->addWidget(valider);

    frameLayout->addWidget(puzzleWidget);
    setCentralWidget(frame);
}

void MainWindow::fillHand()
{


        qDebug() << 7-model->count();

        int n=7-model->count();

        QString addToHand=s1->remplirMain(n);

        //model->clear();

        QString c=addToHand;

        for(int i=0; i<n;i++)

        {

        //qDebug() << lettersImage.at(i);

            c=addToHand.at(i);

            //model->clear();
            //model->main_m->append(addToHand.at(i));

            qDebug() << "ajout de " << addToHand.at(i) << " sur la reglette";




            if(c=="A") model->addPieces(lettersImage.at(0),'A');
            if(c=="B") model->addPieces(lettersImage.at(1),'B');
            if(c=="C") model->addPieces(lettersImage.at(2),'C');
            if(c=="D") model->addPieces(lettersImage.at(3),'D');
            if(c=="E") model->addPieces(lettersImage.at(4),'E');
            if(c=="F") model->addPieces(lettersImage.at(5),'F');
            if(c=="G") model->addPieces(lettersImage.at(6),'G');
            if(c=="H") model->addPieces(lettersImage.at(7),'H');
            if(c=="I") model->addPieces(lettersImage.at(8),'I');
            if(c=="J") model->addPieces(lettersImage.at(9),'J');
            if(c=="K") model->addPieces(lettersImage.at(10),'K');
            if(c=="L") model->addPieces(lettersImage.at(11),'L');
            if(c=="M") model->addPieces(lettersImage.at(12),'M');
            if(c=="N") model->addPieces(lettersImage.at(13),'N');
            if(c=="O") model->addPieces(lettersImage.at(14),'O');
            if(c=="P") model->addPieces(lettersImage.at(15),'P');
            if(c=="Q") model->addPieces(lettersImage.at(16),'Q');
            if(c=="R") model->addPieces(lettersImage.at(17),'R');
            if(c=="S") model->addPieces(lettersImage.at(18),'S');
            if(c=="T") model->addPieces(lettersImage.at(19),'T');
            if(c=="U") model->addPieces(lettersImage.at(20),'U');
            if(c=="V") model->addPieces(lettersImage.at(21),'V');
            if(c=="W") model->addPieces(lettersImage.at(22),'W');
            if(c=="X") model->addPieces(lettersImage.at(23),'X');
            if(c=="Y") model->addPieces(lettersImage.at(24),'Y');
            if(c=="Z") model->addPieces(lettersImage.at(25),'Z');
            if(c=="_") model->addPieces(lettersImage.at(26),'_');

            qDebug() << "main_m : " << *model->main_m;


        }

}

