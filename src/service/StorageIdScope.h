#ifndef _STORAGE_ID_SCOPE_H_
#define _STORAGE_ID_SCOPE_H_

#include <atomic>
#include <map>

#include "service/IdGameAndThread.h"


// создаме новые скоупы под игру и храним
class StorageIdScope
{
public:

    /// [out] ид нового скоупа
    size_t getNewScope();

    // Сохранение ид игры и скоупа
    void saveScopeWithIdGame(size_t idScope, idGameAndThread idGame);

protected:
    size_t getScopeId()
    {
        return ++gameScopeId;
    }

private:
    static std::atomic<size_t>									gameScopeId;
    std::map<size_t, std::pair<size_t,size_t > >             	hashMapScope; // ключ - ид игры, значение - скоуп, ид потока
};

#endif /* _STORAGE_ID_SCOPE_H_ */
