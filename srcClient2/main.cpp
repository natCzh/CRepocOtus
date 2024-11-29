#include <QObject>
#include <QSplitter>

#include <QApplication>
#include <QCoreApplication>

#include "Logger/logger.h"
#include "ClientPaintClass.h"
#include "GuiClient.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //////////////////
    GuiClient srv;

    std::string server_address("127.0.0.1:35454");
    grpc::EnableDefaultHealthCheckService(true);
    srv.connectToServer(server_address);
    //////////////////
    std::shared_ptr<QSplitter> mainWidget(new QSplitter(Qt::Vertical));


    ////////////// Logger
    // TODO разобраться почему имеено так
    Logger lg(1024*1024, 10); // посм что это за размеры
    QObject *logObj = lg.createLogWidget(mainWidget.get());
    QWidget *logWidget = dynamic_cast<QWidget*>(logObj);


    ClientPaintClass *mainWindInputdata = new ClientPaintClass(&srv, &lg, mainWidget.get());

    mainWidget->addWidget(mainWindInputdata);

    logWidget->setWindowTitle("Log");
    mainWidget->addWidget(logWidget);

    mainWidget->show();


    return a.exec();
}
