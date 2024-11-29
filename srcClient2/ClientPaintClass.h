#ifndef _CLIENT_PAINT_CLASS_H
#define _CLIENT_PAINT_CLASS_H

#include <QWidget>
#include <QObject>
#include <QLineEdit>

#include "FieldGame/FieldGame.h"
#include "GuiClient.h"
#include "Logger/logger.h"

class QAction;

class ClientPaintClass : public QWidget
{
    Q_OBJECT
public:

    explicit ClientPaintClass(GuiClient *guiClient, Logger *lg, QWidget *parent = 0);
    ~ClientPaintClass(){}

protected slots:
    void AuthorizationButton();
    void StartNewGame();
    void StartMove();
    void RotableLeft();
    void RotableRight();
    void StopMove();
    void Shot();
    void StopGame();

    void LogGame();
    std::vector<std::map<std::string, int> > ParseLogData(const std::string &logData);

private:
    FieldGame                               *fieldGame;

    QLineEdit                               *authorLine;
    QLineEdit                               *newGameLine;
    GuiClient                               *guiClient;
    unsigned long long                      idObj;
    unsigned long long                      idGame;
    Logger *lg;
};

#endif /* _CLIENT_PAINT_CLASS_H */
