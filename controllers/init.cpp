#include <drogon/HttpController.h>
#include <drogon/drogon.h>
#include "initDatabase.h"
#include <atomic>

using namespace drogon;

class InitController : public drogon::HttpController<InitController>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(InitController::initDb, "/init", Get);
    METHOD_LIST_END

    InitController() {
        initialized = false;
    }

    void initDb(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback)
    {
        // 使用 std::atomic 确保只初始化一次
        if (!initialized.exchange(true))
        {
            auto client = app().getDbClient();  // 默认 DbClient
            if (client)
            {
                initDatabase(client);
            }
        }

        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("Database initialized (or already initialized)");
        callback(resp);
    }

private:
    std::atomic<bool> initialized;
};
