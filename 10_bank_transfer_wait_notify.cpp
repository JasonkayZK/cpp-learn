#include <iostream>
#include <mutex>
#include <set>
#include <thread>
#include <condition_variable>

using namespace std;

class Account {
public:
    Account(string mName, double mMoney) : mName(std::move(mName)), mMoney(mMoney) {};

public:
    void changeMoney(double amount) {
        unique_lock lock(moneyLock);
        mConditionVar.wait(lock, [this, amount] {
            // 调整后金额合法
            return mMoney + amount > 0;
        });
        mMoney += amount;
        // 通知其他线程
        mConditionVar.notify_all();
    }

    string getName() {
        return mName;
    }

    double getMoney() const {
        return mMoney;
    }

    mutex *getLock() {
        return &moneyLock;
    }

private:
    string mName;
    double mMoney;
    mutex moneyLock;
    condition_variable mConditionVar;
};

class Bank {
public:
    void addAccount(Account *account) {
        mAccounts.insert(account);
    }

    static void transferMoney(Account *accountA, Account *accountB, double amount) {
        accountA->changeMoney(-amount);
        accountB->changeMoney(amount);
    }

    [[nodiscard]] double totalMoney() const {
        double sum = 0;
        for (auto a : mAccounts) {
            sum += a->getMoney();
        }
        return sum;
    }

private:
    set<Account *> mAccounts;
};

// cout lock
mutex sCoutLock;

[[noreturn]] void randomTransfer(Bank *bank, Account *accountA, Account *accountB) {
    while(true) {
        double randomMoney = (double) rand() / RAND_MAX * 100;
        {
            lock_guard guard(sCoutLock);
            cout << "Try to Transfer " << randomMoney
                 << " from " << accountA->getName() << "(" << accountA->getMoney()
                 << ") to " << accountB->getName() << "(" << accountB->getMoney()
                 << "), Bank totalMoney: " << bank->totalMoney() << endl;
        }
        Bank::transferMoney(accountA, accountB, randomMoney);
    }
}

int main() {
    Account a("Paul", 100);
    Account b("Moira", 100);

    Bank aBank;
    aBank.addAccount(&a);
    aBank.addAccount(&b);

    thread t1(randomTransfer, &aBank, &a, &b);
    thread t2(randomTransfer, &aBank, &b, &a);

    t1.join();
    t2.join();

    return 0;
}
