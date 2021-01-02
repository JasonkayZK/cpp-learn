#include <iostream>
#include <mutex>
#include <set>
#include <thread>

using namespace std;

class Account {
public:
    Account(string mName, double mMoney) : mName(std::move(mName)), mMoney(mMoney) {};

public:
    void changeMoney(double amount) {
        mMoney += amount;
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
};

class Bank {
public:
    void addAccount(Account *account) {
        mAccounts.insert(account);
    }

    static bool transferMoney(Account *accountA, Account *accountB, double amount) {
        lock_guard guardA(*accountA->getLock());
        lock_guard guardB(*accountB->getLock());

        if (amount > accountA->getMoney()) {
            return false;
        }

        accountA->changeMoney(-amount);
        accountB->changeMoney(amount);
        return true;
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

[[noreturn]] void randomTransfer(Bank *bank, Account *accountA, Account *accountB) {
    while (true) {
        double randomMoney = (double) rand() / RAND_MAX * 100;
        if (Bank::transferMoney(accountA, accountB, randomMoney)) {
            cout << "Transfer " << randomMoney << " from " << accountA->getName()
                 << " to " << accountB->getName()
                 << ", Bank totalMoney: " << bank->totalMoney() << endl;
        } else {
            cout << "Transfer failed, "
                 << accountA->getName() << " has only $" << accountA->getMoney() << ", but "
                 << randomMoney << " required" << endl;
        }
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
