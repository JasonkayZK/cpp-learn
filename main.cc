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

  try {
    auto w = pqxx::work(*db_handler);
    pqxx::result r = w.exec("CREATE TABLE IF NOT EXISTS student \n"
                            "(\n"
                            "    id        SERIAL,\n"
                            "    name      varchar(20) not null,\n"
                            "    dept_name varchar(20),\n"
                            "    tot_cred  numeric(3, 0) check (tot_cred >= 0),\n"
                            "    primary key (id)\n"
                            ");");
    w.commit();
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
    FAIL();
  }

  std::cout << "Create table success " << std::endl;
  SUCCEED();
}

TEST(DBTest, Insert) {

  try {
    auto w = pqxx::work(*db_handler);
    pqxx::result r = w.exec(fmt::format(
        "INSERT INTO student (name,dept_name,tot_cred) values ({}, {}, {})",
        "'haha'", "'dept1'", 0));
    w.commit();
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
    FAIL();
  }
  std::cout << "Insert success: " << std::endl;
  SUCCEED();
}

TEST(DBTest, Update) {
  try {
    auto w = pqxx::work(*db_handler);
    pqxx::result r = w.exec(fmt::format(
        "INSERT INTO student (name,dept_name,tot_cred) values ({}, {}, {})",
        "'haha'", "'dept1'", 0));
    w.commit();
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
    FAIL();
  }
  std::cout << "Insert success: " << std::endl;
  SUCCEED();
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
