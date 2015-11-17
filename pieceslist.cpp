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

#include "pieceslist.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>

PiecesList::PiecesList(int pieceSize, QWidget *parent)
    : QListWidget(parent), m_PieceSize(pieceSize)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(m_PieceSize, m_PieceSize));
    setSpacing(5);
    setAcceptDrops(true);
    setDropIndicatorShown(true);

    main_m=new QString();

}

QString PiecesList::reverse(QString str) const
{

    QString rev;

    for(int i=0;i<str.count();i++)
    {
    rev += str.at(str.count()-i-1);

    }
    return rev;



}



void PiecesList::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
        event->accept();
    else
        event->ignore();
}

void PiecesList::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
        event->setDropAction(Qt::MoveAction);

        event->accept();
    } else {
        event->ignore();
    }
}

void PiecesList::dropEvent(QDropEvent *event)
{
    QString lettre,joker;
    //QChar car;

    if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint location;
        dataStream >> pixmap >> location >> lettre >> joker;

        qDebug() << "Vers la reglette: " << lettre;
        qDebug() << "Vers la reglette: " << joker;

        if(joker=="_")

        {

            addPiece(QPixmap(":/images/_.png"), location,'_');

        } else addPiece(pixmap, location,lettre.at(0));

        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void PiecesList::addPiece(QPixmap pixmap, QPoint location,QChar lettre)
{
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setText(lettre);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, location);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);

    main_m->append(lettre);

}


void PiecesList::addPieces(const QPixmap& pixmap, QChar lettre)
{


    QPixmap pieceImage = pixmap.copy(82, 82, 82, 82);
    addPiece(pieceImage, QPoint(0, 0),lettre);


}

void PiecesList::setMain(QString str)
{

    main_m->append(str);

    //qDebug() << main_m->count();
}

void PiecesList::startDrag(Qt::DropActions /*supportedActions*/)
{
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
    QPoint location = item->data(Qt::UserRole+1).toPoint();

    dataStream << pixmap << location << item->text() << " ";

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("image/x-puzzle-piece", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
    {
        int r=row(item);

        delete takeItem(r);

        main_m->remove(r,1);

      qDebug() << "Sur la reglette : " << main_m->toUtf8() << r;



    }
}
