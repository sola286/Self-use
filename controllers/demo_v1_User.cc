#include "demo_v1_User.h"
#include "initDatabase.h"

using namespace demo::v1;

void User::ping(const HttpRequestPtr &req,
          std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto resp = HttpResponse::newHttpResponse();
    resp->setContentTypeCode(CT_TEXT_HTML);
    if (!initialized.exchange(true))
    {
        auto client = app().getDbClient();  // 默认 DbClient
        if (client)
        {
            std::string initDataReturn = initDatabase(client);
            resp->setBody(initDataReturn);
        } else {
            resp->setBody("can't get db client");
        }
    }else{
        resp->setBody("initialized");
    }
    callback(resp);
}

void User::login(const HttpRequestPtr &req,
           std::function<void (const HttpResponsePtr &)> &&callback,
           std::string &&userId,
           const std::string &password)
{
    LOG_DEBUG<<"User "<<userId<<" login";
    //认证算法，读数据库，验证身份等...
    //...
    Json::Value ret;
    ret["result"]="ok";
    ret["token"]=drogon::utils::getUuid();
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}

void User::getInfo(const HttpRequestPtr &req,
             std::function<void (const HttpResponsePtr &)> &&callback,
             std::string userId,
            const std::string &token) const
{
    LOG_DEBUG<<"User "<<userId<<" get his information";
    //验证token有效性等
    //读数据库或缓存获取用户信息
    Json::Value ret;
    ret["result"]="ok";
    ret["user_name"]="Jack";
    ret["user_id"]=userId;
    ret["gender"]=1;
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}

void User::userReg(const HttpRequestPtr &req,
           std::function<void (const HttpResponsePtr &)> &&callback,
           std::string &&userId,
           const std::string &password)
{
    LOG_DEBUG<<"User "<<userId<<" register";

    //注册算法，写数据库等...
    

    Json::Value ret;
    ret["result"]="ok";
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}