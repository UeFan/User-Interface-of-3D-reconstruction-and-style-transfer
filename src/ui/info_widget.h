// COLMAP - Structure-from-Motion and Multi-View Stereo.
// Copyright (C) 2017  Johannes L. Schoenberger <jsch at inf.ethz.ch>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef COLMAP_SRC_UI_INFO_WIDGET_H_
#define COLMAP_SRC_UI_INFO_WIDGET_H_



#include <QtWidgets>
#include <QAbstractSocket>
#include <QTcpServer>
#include <QScrollBar>
#include <QMessageBox>


//#include "util/option_manager.h"

class QTcpSocket;
class QFile;


namespace colmap {

class InfoWidget : public QWidget {

public:
    InfoWidget(QWidget* parent);
private:
    QTcpServer tcpServer;
    QTcpSocket *tcpServerConnection;
//    qint64 totalBytes;     // 存放总大小信息
//    qint64 bytesReceived;  // 已收到数据的大小
//    qint64 fileNameSize;   // 文件名的大小信息
//    QString fileName;      // 存放文件名
//    QFile *localFile;      // 本地文件
//    QByteArray inBlock;    // 数据缓冲区
    QScrollBar *scrollbar;
    QTextEdit *textEdit;

    void clear();
    void acceptConnection();
    void updateServerProgress();
//    void displayError(QAbstractSocket::SocketError socketError);

};

}  // namespace colmap

#endif  // COLMAP_SRC_UI_INFO_WIDGET_H_
