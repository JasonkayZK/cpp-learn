#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

/*
 * 标准把随机数抽象成：随机数引擎和分布两部分.引擎用来产生随机数,分布产生特定分布的随机数(比如平均分布,正太分布等)；

　　标准提供三种常用的引擎:

    linear_congruential_engine,mersenne_twister_engine和subtract_with_carry_engine.

    第一种是线性同余算法,第二种是梅森旋转算法,第三种带进位的线性同余算法；

   第一种是最常用的,而且速度也是非常快的; 第二种号称是最好的伪随机数生成器;

　　随机数引擎接受一个整形参数当作种子,不提供的话,会使用默认值. 推荐使用random_device来产生一个随机数当作种子.

    (windows下爱咋整咋整,谁叫windows的random_device是调用rand_s)

 */
// 产生随机数
void generateRandomData(vector<double>& collection, int size) {
    // random_device提供()操作符,用来返回一个min()到max()之间的一个数字
    // 如果是Linux(Unix Like或者Unix)下,都可以使用这个来产生高质量的随机数,可以理解为真随机数;
    random_device rd;
    // 梅森旋转算法（Mersenne twister）：
    // https://zh.wikipedia.org/wiki/%E6%A2%85%E6%A3%AE%E6%97%8B%E8%BD%AC%E7%AE%97%E6%B3%95
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(1.0, 100.0);
    for (int i = 0; i < size; i++) {
        collection.push_back(dist(mt));
    }
}

int main() {
    vector<double> collection;
    generateRandomData(collection, 10e6); // ①

    vector<double> copy1(collection); // ②
    vector<double> copy2(collection);
    vector<double> copy3(collection);

    auto time1 = chrono::steady_clock::now(); // ③
    sort(execution::seq, copy1.begin(), copy1.end()); // ④
    auto time2 = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(time2 - time1).count();
    cout << "Sequenced sort consuming " << duration << "ms." << endl; // ⑤

    auto time3 = chrono::steady_clock::now();
    sort(execution::par, copy2.begin(),copy2.end()); // ⑥
    auto time4 = chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(time4 - time3).count();
    cout << "Parallel sort consuming " << duration << "ms." << endl;

    auto time5 = chrono::steady_clock::now();
    sort(execution::par_unseq, copy2.begin(),copy2.end()); // ⑦
    auto time6 = chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(time6 - time5).count();
    cout << "Parallel unsequenced sort consuming " << duration << "ms." << endl;
}
