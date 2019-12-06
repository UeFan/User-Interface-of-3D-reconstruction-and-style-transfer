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

#include "ui/info_widget.h"
#include <QtNetwork>

namespace colmap {

InfoWidget::InfoWidget(QWidget* parent){
    setWindowFlags(Qt::Window);
    setWindowTitle("Info");
    resize(320, parent->height());

    QGridLayout* grid = new QGridLayout(this);
    grid->setContentsMargins(5, 10, 5, 5);

    QHBoxLayout* left_button_layout = new QHBoxLayout();

    QPushButton* save_log_button = new QPushButton(tr("Save"), this);
   // connect(save_log_button, &QPushButton::released, this, &LogWidget::SaveLog);
    left_button_layout->addWidget(save_log_button);

    QPushButton* clear_button = new QPushButton(tr("Clear"), this);
    connect(clear_button, &QPushButton::released, this, &InfoWidget::clear);
    left_button_layout->addWidget(clear_button);

    grid->addLayout(left_button_layout, 0, 0, Qt::AlignLeft);

    QHBoxLayout* right_button_layout = new QHBoxLayout();

    grid->addLayout(right_button_layout, 0, 1, Qt::AlignRight);

    textEdit = new QTextEdit(this);
    textEdit->setObjectName(QStringLiteral("textEdit"));
    textEdit->setReadOnly(true);
    grid->addWidget(textEdit, 1, 0, 1, 2);

    connect(&tcpServer, &QTcpServer::newConnection,
            this, &InfoWidget::acceptConnection);
    if (!tcpServer.listen(QHostAddress::LocalHost, 6666)) {
        qDebug() << tcpServer.errorString();
        close();
        return;
    }
}

void InfoWidget::clear(){
    textEdit->clear();
}

void InfoWidget::acceptConnection(){
    tcpServerConnection = tcpServer.nextPendingConnection();
    connect(tcpServerConnection, &QTcpSocket::readyRead,
            this, &InfoWidget::updateServerProgress);
//    connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)),
//            this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void InfoWidget::updateServerProgress(){
    //获取系统现在的时间
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("[ hh:mm:ss ]"); //设置显示格式
    qDebug()<<str;

    qint64 len = tcpServerConnection->bytesAvailable();
    qDebug()<<"socket data len:"<< len;
    QByteArray alldata = tcpServerConnection->read(len);
    //开始转换编码
    QTextCodec *utf8codec = QTextCodec::codecForName("UTF-8");
    QString utf8str = utf8codec->toUnicode(alldata.mid(2));
    qDebug()<<"hex:["<<alldata.toHex().toUpper()<<"]";
    qDebug()<<"utf-8 ["<< (utf8str) << "]";
    //显示到控件上
    textEdit->insertPlainText(str);//在标签上显示时间
    textEdit->insertPlainText(utf8str);
    textEdit->insertPlainText(tr("\n"));
    scrollbar = textEdit->verticalScrollBar();
    if (scrollbar)
    {
       scrollbar->setSliderPosition(scrollbar->maximum());
    }
}

}  // namespace colmap
