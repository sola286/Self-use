#include <drogon/HttpAppFramework.h>
#include "init/initDatabase.h"
int main() {
    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0",8080);
    drogon::app().loadConfigFile("config/config.json");

    initDatabase(drogon::app().getDbClient());

    drogon::app().run();
    return 0;
}
