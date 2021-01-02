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
        lock(*accountA->getLock(), *accountB->getLock()); // ①
        lock_guard lockA(*accountA->getLock(), adopt_lock);  // ②
        lock_guard lockB(*accountB->getLock(), adopt_lock);  // ③

//        lock_guard guardA(*accountA->getLock());
//        lock_guard guardB(*accountB->getLock());

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

// cout lock
mutex sCoutLock;

[[noreturn]] void randomTransfer(Bank *bank, Account *accountA, Account *accountB) {
    while (true) {
        double randomMoney = (double) rand() / RAND_MAX * 100;
        if (Bank::transferMoney(accountA, accountB, randomMoney)) {
            sCoutLock.lock();
            cout << "Transfer " << randomMoney << " from " << accountA->getName()
                 << " to " << accountB->getName()
                 << ", Bank totalMoney: " << bank->totalMoney() << endl;
            sCoutLock.unlock();
        } else {
            sCoutLock.lock();
            cout << "Transfer failed, "
                 << accountA->getName() << " has only $" << accountA->getMoney() << ", but "
                 << randomMoney << " required" << endl;
            sCoutLock.unlock();
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
