#include "ClientPaintClass.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

ClientPaintClass::ClientPaintClass(GuiClient *guiClient_, Logger *lg_, QWidget *parent)
    : QWidget(parent)
    , guiClient(guiClient_)
    , lg(lg_)
{
    QVBoxLayout *vbxMain = new QVBoxLayout(this);
    QHBoxLayout *hboxButtonUp = new QHBoxLayout();
    QHBoxLayout *hboxButtonUpNewGame = new QHBoxLayout();
    QHBoxLayout *hboxButtonCommandGame = new QHBoxLayout();

    fieldGame = new FieldGame(this);


    QPushButton *authorizationButton = new QPushButton(tr("Авторизация"), this);
    connect(authorizationButton, &QPushButton::clicked, this, &ClientPaintClass::AuthorizationButton);
    hboxButtonUp->addWidget(authorizationButton);
    authorLine = new QLineEdit(this);
    authorLine->setEnabled(false);
    hboxButtonUp->addWidget(authorLine);

    QPushButton *newGameButton = new QPushButton(tr("Начать новую игру"), this);
    connect(newGameButton, &QPushButton::clicked, this, &ClientPaintClass::StartNewGame);
    hboxButtonUpNewGame->addWidget(newGameButton);
    newGameLine = new QLineEdit(this);
    newGameLine->setEnabled(false);
    hboxButtonUpNewGame->addWidget(newGameLine);
    QPushButton *stopGameButton = new QPushButton(tr("Оставновить игру"), this);
    connect(stopGameButton, &QPushButton::clicked, this, &ClientPaintClass::StopGame);
    hboxButtonUpNewGame->addWidget(stopGameButton);

    vbxMain->addLayout(hboxButtonUp);
    vbxMain->addLayout(hboxButtonUpNewGame);
    vbxMain->addWidget(fieldGame);

    QPushButton *startMoveButton = new QPushButton(tr("Начать движение"), this);
    connect(startMoveButton, &QPushButton::clicked, this, &ClientPaintClass::StartMove);
    hboxButtonCommandGame->addWidget(startMoveButton);
    QPushButton *rotableButtonR = new QPushButton(tr("Поворот вправо"), this);
    connect(rotableButtonR, &QPushButton::clicked, this, &ClientPaintClass::RotableRight);
    hboxButtonCommandGame->addWidget(rotableButtonR);
    QPushButton *rotableButtonL = new QPushButton(tr("Поворот влево"), this);
    connect(rotableButtonL, &QPushButton::clicked, this, &ClientPaintClass::RotableLeft);
    hboxButtonCommandGame->addWidget(rotableButtonL);
    QPushButton *stopMoveButton = new QPushButton(tr("Остановить движение"), this);
    connect(stopMoveButton, &QPushButton::clicked, this, &ClientPaintClass::StopMove);
    hboxButtonCommandGame->addWidget(stopMoveButton);
    QPushButton *shotButton = new QPushButton(tr("Выстрел"), this);
    connect(shotButton, &QPushButton::clicked, this, &ClientPaintClass::Shot);
    hboxButtonCommandGame->addWidget(shotButton);

    vbxMain->addLayout(hboxButtonCommandGame);
}

void ClientPaintClass::AuthorizationButton()
{
    size_t typeRegister = 1; // сейчас всегда 1
    idObj = guiClient->AuthorizationObj(typeRegister);
    authorLine->setText(QString::number(idObj));
    lg->setLastLogMessage("Новый пользователь с ид " + QString::number(idObj));
}

void ClientPaintClass::StartNewGame()
{
    std::string idOtherObj = "";
    std::string otherArgs = "";
    bool result = guiClient->StartNewGame(idObj, idOtherObj, otherArgs, idGame);
    newGameLine->setText(QString::number(idGame));
    lg->setLastLogMessage("Новая игра " + QString::number(idGame));
}

void ClientPaintClass::StartMove()
{
    unsigned long long idSender = idObj;
    unsigned long long idGameCur = idGame;
    unsigned long long idObjCur = idObj;
    std::string TypeCommand = "CommandInterpret.StartMove";
    std::string args = "velocity, 1";

    bool result = guiClient->AddCommandGame(idSender, idGameCur, idObjCur, TypeCommand, args);

    lg->setLastLogMessage("Движение запущено");
}

void ClientPaintClass::RotableLeft()
{
    unsigned long long idSender = idObj;
    unsigned long long idGameCur = idGame;
    unsigned long long idObjCur = idObj;
    std::string TypeCommand = "CommandInterpret.Rotate";
    std::string args = "directionAngular, -1";

    bool result = guiClient->AddCommandGame(idSender, idGameCur, idObjCur, TypeCommand, args);

    lg->setLastLogMessage("Поврот влево на 90 градусов");
}

void ClientPaintClass::RotableRight()
{
    unsigned long long idSender = idObj;
    unsigned long long idGameCur = idGame;
    unsigned long long idObjCur = idObj;
    std::string TypeCommand = "CommandInterpret.Rotate";
    std::string args = "directionAngular, 1";

    bool result = guiClient->AddCommandGame(idSender, idGameCur, idObjCur, TypeCommand, args);

    lg->setLastLogMessage("Поврот вправо на 90 градусов");
}

void ClientPaintClass::StopMove()
{
    unsigned long long idSender = idObj;
    unsigned long long idGameCur = idGame;
    unsigned long long idObjCur = idObj;
    std::string TypeCommand = "CommandInterpret.StopMove";
    std::string args = "";

    bool result = guiClient->AddCommandGame(idSender, idGameCur, idObjCur, TypeCommand, args);

    lg->setLastLogMessage("Оставнока движения");
}

void ClientPaintClass::Shot()
{
    unsigned long long idSender = idObj;
    unsigned long long idGameCur = idGame;
    unsigned long long idObjCur = idObj;
    std::string TypeCommand = "CommandInterpret.Shot";
    std::string args = "";

    bool result = guiClient->AddCommandGame(idSender, idGameCur, idObjCur, TypeCommand, args);

    lg->setLastLogMessage("Выстрел");
}

void ClientPaintClass::StopGame()
{
    unsigned long long idSender = idObj;
    unsigned long long idGameCur = idGame;
    bool result = guiClient->StopGame(idSender, idGameCur);

    lg->setLastLogMessage("Остановка движения");
}
