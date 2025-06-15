#include "ClientPaintClass.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

#include <string>
#include <map>
#include <vector>

ClientPaintClass::ClientPaintClass(GuiClient *guiClient_, QWidget *parent)
    : QWidget(parent)
    , guiClient(guiClient_)
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
    CustomLogger.SetLogData("Новый пользователь с ид " + QString::number(idObj), MessageType::Default);
}

void ClientPaintClass::StartNewGame()
{
    std::string idOtherObj = "";
    std::string otherArgs = "";
    bool result = guiClient->StartNewGame(idObj, idOtherObj, otherArgs, idGame);
    newGameLine->setText(QString::number(idGame));
    CustomLogger.SetLogData("Новая игра " + QString::number(idGame), MessageType::Default);
}

void ClientPaintClass::StartMove()
{
    unsigned long long idSender = idObj;
    unsigned long long idGameCur = idGame;
    unsigned long long idObjCur = idObj;
    std::string TypeCommand = "CommandInterpret.StartMove";
    std::string args = "velocity, 1";

    bool result = guiClient->AddCommandGame(idSender, idGameCur, idObjCur, TypeCommand, args);

    CustomLogger.SetLogData("Движение запущено", MessageType::Default);
    LogGame();
}

void ClientPaintClass::RotableLeft()
{
    unsigned long long idSender = idObj;
    unsigned long long idGameCur = idGame;
    unsigned long long idObjCur = idObj;
    std::string TypeCommand = "CommandInterpret.Rotate";
    std::string args = "directionAngular, -1";

    bool result = guiClient->AddCommandGame(idSender, idGameCur, idObjCur, TypeCommand, args);

    CustomLogger.SetLogData("Поврот влево на 90 градусов", MessageType::Default);
    LogGame();
}

void ClientPaintClass::RotableRight()
{
    unsigned long long idSender = idObj;
    unsigned long long idGameCur = idGame;
    unsigned long long idObjCur = idObj;
    std::string TypeCommand = "CommandInterpret.Rotate";
    std::string args = "directionAngular, 1";

    bool result = guiClient->AddCommandGame(idSender, idGameCur, idObjCur, TypeCommand, args);

    CustomLogger.SetLogData("Поврот вправо на 90 градусов", MessageType::Default);
    LogGame();
}

void ClientPaintClass::StopMove()
{
    unsigned long long idSender = idObj;
    unsigned long long idGameCur = idGame;
    unsigned long long idObjCur = idObj;
    std::string TypeCommand = "CommandInterpret.StopMove";
    std::string args = "";

    bool result = guiClient->AddCommandGame(idSender, idGameCur, idObjCur, TypeCommand, args);

    CustomLogger.SetLogData("Оставнока движения", MessageType::Default);
    LogGame();
}

void ClientPaintClass::Shot()
{
    unsigned long long idSender = idObj;
    unsigned long long idGameCur = idGame;
    unsigned long long idObjCur = idObj;
    std::string TypeCommand = "CommandInterpret.Shot";
    std::string args = "";

    bool result = guiClient->AddCommandGame(idSender, idGameCur, idObjCur, TypeCommand, args);

    CustomLogger.SetLogData("Выстрел", MessageType::Default);
    LogGame();
}

void ClientPaintClass::StopGame()
{
    unsigned long long idSender = idObj;
    unsigned long long idGameCur = idGame;
    bool result = guiClient->StopGame(idSender, idGameCur);

    CustomLogger.SetLogData("Остановка движения", MessageType::Default);
    LogGame();
}

void ClientPaintClass::LogGame()
{
    unsigned long long idGameCur = idGame;
    std::string infGame;
    guiClient->GetInfGame(idGameCur, infGame);

    std::vector<std::map<std::string, int> > mapLog = ParseLogData(infGame);

    CustomLogger.SetLogData("ид -" + QString::number(mapLog[0]["id"]), MessageType::Clear);
    CustomLogger.SetLogData("Текущие координаты - [" + QString::number(mapLog[0]["x"]) + ", " + QString::number(mapLog[0]["y"]) + "] Количество заряда - " + QString::number(mapLog[0]["numberShot"]), MessageType::Clear);
}

// пока для одного игрока
std::vector<std::map<std::string, int> > ClientPaintClass::ParseLogData(const std::string &logData)
{
    std::map<std::string, int> oneObj;

    //     std::string dsfsd = "velocity, 1;directionAngular, 1";
    const char* const delimeters = ";";

    std::string logDataStr = logData;
    char* strCur = std::strtok(logDataStr.data(), delimeters);

    const char* const delimeters2 = ",";
    char* strCur2;
    if (strCur)
    {
        std::string str1 = strCur;

        std::vector<std::string> words;
        strCur2 = std::strtok(str1.data(), delimeters2);
        while (strCur2 != nullptr)
        {
            words.push_back(strCur2);
            strCur2 = std::strtok(nullptr, delimeters2);
        }

        oneObj["id"] = std::stoi(words[0]);
        oneObj["x"] = std::stoi(words[1]);
        oneObj["y"] = std::stoi(words[2]);
        oneObj["numberShot"] = std::stoi(words[3]);
    }

    std::vector<std::map<std::string, int> > result;
    result.push_back(oneObj);
    return result;
}
