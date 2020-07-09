#include "treewidget.h"
#include <QFile>
#include <QApplication>
#include <QDebug>
void setstylesheet(){
    //QFile file("../css/styleSheet.css");
    QFile file(":/styleSheet.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
    file.close();
    //qApp->setPalette(QPalette(QColor("#87CEFA")));
    //qApp->setStyleSheet("QLineEdit { background-color: yellow }");
}
void setStyle(QString style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //setStyle("qss.qss");
    setstylesheet();

    TreeWidget w;
    w.show();
    return a.exec();
}
