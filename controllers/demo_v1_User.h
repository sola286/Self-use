#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace demo
{
namespace v1
{
class User : public drogon::HttpController<User>
{
  public:
    User() {
        initialized = false;
    }

    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    METHOD_ADD(User::ping,"/",Get);
    METHOD_ADD(User::ping,"/ping",Get);
    METHOD_ADD(User::login,"/token?userId={1}&passwd={2}",Post);
    METHOD_ADD(User::getInfo,"/{1}/info?token={2}",Get);
    METHOD_ADD(User::userReg,"/token?userId={1}&passwd={2}",Post);
    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
    void ping(const HttpRequestPtr &req,
              std::function<void (const HttpResponsePtr &)> &&callback);
    void login(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               std::string &&userId,
               const std::string &password);
    void getInfo(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 std::string userId,
                 const std::string &token) const;
    void userReg(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 std::string &&userId,
                 const std::string &password);

  private:
      std::atomic<bool> initialized;
  };
}
}
