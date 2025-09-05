#include "initDatabase.h"
#include <drogon/drogon.h>
#include <iostream>

using namespace drogon::orm;
using namespace std;

void initDatabase(const DbClientPtr &client)
{
    if (!client) {
        cerr << "initDatabase DbClientPtr is nullptr!" << endl;
        return;
    }

        cerr << "initDatabase DbClientPtr is success!" << endl;
    try {
        // Users 表
        client->execSqlSync(
            "CREATE TABLE IF NOT EXISTS users ("
            "id INT AUTO_INCREMENT PRIMARY KEY,"
            "username VARCHAR(50) NOT NULL UNIQUE,"
            "password VARCHAR(255) NOT NULL,"
            "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
            ");"
        );
        cout << "Users table is ready." << endl;

        // Tasks 表
        client->execSqlSync(
            "CREATE TABLE IF NOT EXISTS tasks ("
            "id INT AUTO_INCREMENT PRIMARY KEY,"
            "user_id INT NOT NULL,"
            "title VARCHAR(255) NOT NULL,"
            "description TEXT,"
            "status ENUM('pending','processing','done') DEFAULT 'pending',"
            "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
            "updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,"
            "FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE"
            ");"
        );
        cout << "Tasks table is ready." << endl;

    } catch (const std::exception &e) {
        cerr << "initDatabase error: " << e.what() << endl;
    }
}
