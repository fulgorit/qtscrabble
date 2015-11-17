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

#include "puzzlewidget.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QInputDialog>

PuzzleWidget::PuzzleWidget(int imageSize, QWidget *parent)
    : QWidget(parent), m_ImageSize(imageSize)
{
    setAcceptDrops(true);
    setMinimumSize(m_ImageSize, m_ImageSize);
    setMaximumSize(m_ImageSize, m_ImageSize);
}

void PuzzleWidget::clear()
{
    pieceLocations.clear();
    piecePixmaps.clear();
    pieceRects.clear();
    highlightedRect = QRect();
    inPlace = 0;
    update();
}

void PuzzleWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
        event->accept();
    else
        event->ignore();
}

void PuzzleWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    event->accept();
}

void PuzzleWidget::dragMoveEvent(QDragMoveEvent *event)
{
    QRect updateRect = highlightedRect.united(targetSquare(event->pos()));

    if (event->mimeData()->hasFormat("image/x-puzzle-piece")
        && findPiece(targetSquare(event->pos())) == -1) {


        highlightedRect = targetSquare(event->pos());
        event->setDropAction(Qt::MoveAction);
        event->accept();

        int x=event->pos().x()/pieceSize();
        int y=event->pos().y()/pieceSize();

        // qDebug() << "Detection Joker :" << x << y;
        // qDebug() << trackJoker;

        QString lettre,joker;
        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QRect square = targetSquare(event->pos());
        QPixmap pixmap;
        QPoint location;
        dataStream >> pixmap >> location >> lettre >> joker;

        // qDebug() << joker;



        if(joker=="_") {





           //     qDebug() << "Joker detecté";

           //     qDebug() << "location" << location;
           //     qDebug() << x;
           //     qDebug() << y;

                trackJoker.replace(0,QPoint(x,y));
  //              qDebug() << "Nouvelle coord" << x << y ;





        }


    } else {
        highlightedRect = QRect();
        event->ignore();
    }

    update(updateRect);
}

void PuzzleWidget::dropEvent(QDropEvent *event)
{

    int x,y;
    x=targetSquare(event->pos()).x()/pieceSize();
    y=targetSquare(event->pos()).y()/pieceSize();


    QString lettre,joker;

    if (event->mimeData()->hasFormat("image/x-puzzle-piece")
        && findPiece(targetSquare(event->pos())) == -1) {


        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QRect square = targetSquare(event->pos());
        QPixmap pixmap;
        QPoint location;
        dataStream >> pixmap >> location >> lettre >> joker;

        qDebug() << lettre << joker;

        qDebug() << "Joker(s): " << trackJoker.count();



        if (lettre=="_")

        {

            bool ok;
            QString text = QInputDialog::getText(this, tr("Remplacer par ?"),
                                                     tr("Lettre:"), QLineEdit::Normal,
                                                      "", &ok);
            if (ok && text.count()==1 && text.at(0).isLetter())
            {

                lettre=text;
                pixmap=QPixmap(":/images/"+QString(lettre)+".png");


                trackJoker.clear();    

                trackJoker << QPoint(x,y);

            }   else {


                QMessageBox msgBox;
                msgBox.setText("Erreur d'édition");
                msgBox.exec();

                event->ignore();
                return;

            }

        }


/*

            board[x][y]=lettre.at(0);


            pieceLocations.append(location);
            piecePixmaps.append(QPixmap(":/images/"+QString(board[x][y])+".png"));
            pieceRects.append(square);


            highlightedRect = QRect();

            event->setDropAction(Qt::MoveAction);
            event->accept();

            update(square);




            return;




        } else {

*/
        QMessageBox msgBox;
        msgBox.setText(lettre);
        msgBox.exec();

//        }

        pieceLocations.append(location);
        piecePixmaps.append(pixmap);
        pieceRects.append(square);

        board[x][y]=lettre.at(0);


        highlightedRect = QRect();
        update(square);

        event->setDropAction(Qt::MoveAction);
        event->accept();

        if (location == QPoint(square.x()/pieceSize(), square.y()/pieceSize())) {
            inPlace++;
            if (inPlace == 25)
                emit puzzleCompleted();
        }
    } else {
        highlightedRect = QRect();
        event->ignore();
    }
}

int PuzzleWidget::findPiece(const QRect &pieceRect) const
{
    for (int i = 0; i < pieceRects.size(); ++i) {
        if (pieceRect == pieceRects[i])
            return i;
    }
    return -1;
}

void PuzzleWidget::mousePressEvent(QMouseEvent *event)
{
    QRect square = targetSquare(event->pos());
    int found = findPiece(square);

    if (found == -1)
        return;

    QPoint location = pieceLocations[found];
    QPixmap pixmap = piecePixmaps[found];
    pieceLocations.removeAt(found);
    piecePixmaps.removeAt(found);
    pieceRects.removeAt(found);

    if (location == QPoint(square.x()/pieceSize(), square.y()/pieceSize()))
        inPlace--;

    update(square);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    QString lettre,joker=" ";
    lettre=board[square.x()/pieceSize()][square.y()/pieceSize()];

    for(int i=0;i<trackJoker.count();i++)
    {

        if(trackJoker.at(i).x()==square.x()/pieceSize()&&trackJoker.at(i).y()==square.y()/pieceSize()) { joker="_"; qDebug() << "Joker trouvé"; }



    }

/*
    QMessageBox msgBox;
    msgBox.setText(joker);
    msgBox.exec();
*/

    dataStream << pixmap << location << lettre << joker;

    board[square.x()/pieceSize()][square.y()/pieceSize()]=QChar::Null;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("image/x-puzzle-piece", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - square.topLeft());
    drag->setPixmap(pixmap);

    if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction)) {
        pieceLocations.insert(found, location);
        piecePixmaps.insert(found, pixmap);
        pieceRects.insert(found, square);


        update(targetSquare(event->pos()));

        if (location == QPoint(square.x()/pieceSize(), square.y()/pieceSize()))
            inPlace++;
    }
}

void PuzzleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    QImage q1(":/images/plateauvierge.png");

    int h=size().height();
    int w=size().width();


    q1=q1.scaled(1000,1000,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    QRect rect(0,0,h,w);

    painter.drawImage(rect,q1);


    //painter.fillRect(event->rect(), Qt::white);

    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }

   for (int i = 0; i < pieceRects.size(); ++i)
        painter.drawPixmap(pieceRects[i], piecePixmaps[i]);

    for(int i=0;i<15;i++)
    {

        for(int j=0;j<15;j++)
        {

            if(board2[i][j].isLetter()) painter.drawPixmap(i*pieceSize(),j*pieceSize(),pieceSize(),pieceSize(),QPixmap(":/images/"+QString(board[i][j])+".png"));

        }

    }


    painter.end();
}


void PuzzleWidget::valid()
{

    qDebug() << "valid";

    for(int i=0;i<15;i++)
    {

        for(int j=0;j<15;j++)
        {

            if(board[i][j].isLetter()) board2[i][j]=board[i][j];

        }

    }

    pieceRects.clear();
    piecePixmaps.clear();

    trackJoker.clear();




}

const QRect PuzzleWidget::targetSquare(const QPoint &position) const
{
    return QRect(position.x()/pieceSize() * pieceSize(), position.y()/pieceSize() * pieceSize(), pieceSize(), pieceSize());
}

int PuzzleWidget::pieceSize() const
{
    return m_ImageSize / 15;
}

int PuzzleWidget::imageSize() const
{
    return m_ImageSize;
}
