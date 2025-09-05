#include <drogon/HttpController.h>
#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>
#include "initDatabase.h"

using namespace drogon;

class TaskController : public drogon::HttpController<TaskController>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TaskController::getAllTables, "/tasks", Get);
    METHOD_LIST_END

    void getAllTables(const HttpRequestPtr &req,
                    std::function<void (const HttpResponsePtr &)> &&callback)
    {
        auto client = app().getDbClient();
        if (!client)
        {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(HttpStatusCode::k500InternalServerError);
            resp->setBody("DbClient is null!");
            callback(resp);
            return;
        }

        client->execSqlAsync(
            "SELECT table_name FROM information_schema.tables WHERE table_schema = DATABASE();",
            [callback](const drogon::orm::Result &r) {
                Json::Value jsonRes(Json::arrayValue);
                for (auto row : r) {
                    jsonRes.append(row["table_name"].as<std::string>());
                }
                auto resp = HttpResponse::newHttpJsonResponse(jsonRes);
                callback(resp);
            },
            [callback](const drogon::orm::DrogonDbException &e) {
                auto resp = HttpResponse::newHttpResponse();
                resp->setStatusCode(HttpStatusCode::k500InternalServerError);
                resp->setBody(std::string("Database query error: ") + e.base().what());
                callback(resp);
            }
        );
    }

};
