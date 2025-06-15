#include "service/StorageIdScope.h"

#include "IoC/IoC.h"

std::atomic<size_t> StorageIdScope::gameScopeId(0);

extern IoC* ioc;
size_t StorageIdScope::getNewScope()
{
    size_t idScope = getScopeId();

    std::shared_ptr<Scopes::Scope> scopeNew = ioc->Resolve<std::shared_ptr<Scopes::Scope> >("Scopes.Create.Root", (int)idScope);
    ioc->Resolve<void>("Scopes.Current.Set", scopeNew);

    return idScope;
}

void StorageIdScope::saveScopeWithIdGame(size_t idScope, idGameAndThread idGame)
{
    hashMapScope[idGame.idGame] = std::make_pair(idScope, idGame.threadId);
}
