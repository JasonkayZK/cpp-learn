#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <fmt/core.h>
#include "gtest/gtest.h"

int port = 5432;
std::string hostaddr = "127.0.0.1";
std::string dbname = "postgres";
std::string user = "postgres";
std::string password = "******";

pqxx::connection *db_handler;

class DbHandle : public testing::Environment {
  void SetUp() override {
    std::cout << "Before all cases, register db" << std::endl;
    db_handler = new pqxx::connection(fmt::format(
        "dbname={} user={} password={} hostaddr={} port={}",
        dbname, user, password, hostaddr, port));

    if (db_handler == nullptr) return;

    if (db_handler->is_open()) {
      std::cout << "Opened database successfully: " << db_handler->dbname() << std::endl;
    } else {
      std::cout << "Can't open database" << std::endl;
      FAIL();
    }
  }
  void TearDown() override {
    std::cout << "After all cases done, close connection" << std::endl;
    if (db_handler->is_open()) {
      db_handler->close();
      delete db_handler;
      std::cout << "Database closed!" << std::endl;
    }
  }
};

TEST(DBTest, DBConnectionOk) {
  ASSERT_TRUE(db_handler->is_open());
}

TEST(DBTest, CreateTable) {

}

TEST(DBTest, Insert) {

}

TEST(DBTest, Update) {

}

TEST(DBTest, Select) {

}

TEST(DBTest, Delete) {

}

TEST(DBTest, DropTable) {

}

int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  ::testing::AddGlobalTestEnvironment(new DbHandle); // add db environment
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
