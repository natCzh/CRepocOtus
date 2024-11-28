#include <iostream>

#include "routerMain/RouterMainClass.h"


unsigned long long RouterMainClass::AuthorizationObj(size_t typeRegister)
{
    return authorClient->AuthorizationObj(static_cast<unsigned long long>(typeRegister));
}

bool RouterMainClass::StartNewGame(unsigned long long idObj, const std::string &idOtherObj, const std::string &otherArgs, unsigned long long &idGame)
{
    unsigned long long typeObj;
    bool flagAuth = authorClient->CheckAuthorizationObj(idObj, typeObj);
    if (!flagAuth)
    {
        std::cout << "Error authorization - idObj isn't correct" << std::endl;
        return false;
    }

    idGame = spaceGameClient->StartNewGame(idObj, (int)typeObj, otherArgs, otherArgs);

    return true;
}

bool RouterMainClass::AddCommandGame(unsigned long long idSender, unsigned long long idGame, unsigned long long idObj, const std::string &TypeCommand, const std::string &args)
{
    unsigned long long typeObj;
    bool flagAuth = authorClient->CheckAuthorizationObj(idSender, typeObj);
    if (!flagAuth)
    {
        std::cout << "Error authorization - idObj isn't correct" << std::endl;
        return false;
    }

    // тут должна быть проверка на разрешение отправления команды, либо модно сделать это ниже в функции
    spaceGameClient->AddCommandGame(idSender, idGame, idObj, TypeCommand, args);

    return true;
}

bool RouterMainClass::StopGame(unsigned long long idSender, unsigned long long idGame)
{
    unsigned long long typeObj;
    bool flagAuth = authorClient->CheckAuthorizationObj(idSender, typeObj);
    if (!flagAuth)
    {
        std::cout << "Error authorization - idObj isn't correct" << std::endl;
        return false;
    }

    return spaceGameClient->StopGame(idGame);
}

void RouterMainClass::GetInfGame(unsigned long long idGame, std::string &infGame)
{
    // TODO дописать !!!!!!!!!!
}
