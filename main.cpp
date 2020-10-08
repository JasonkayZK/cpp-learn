#include <iostream>

#include "cJSON/cJSON.h"
#include "math/MathUtils.h"

int main() {
    hello(2);
    std::cout << power(2, 5) << std::endl;

    char *post_str = nullptr;
    cJSON *root = cJSON_CreateObject();

    cJSON_AddStringToObject(root, "user", "jasonkay");
    cJSON_AddStringToObject(root, "pwd", "hkcw3cjbc");
    post_str = cJSON_Print(root);
    cJSON_Delete(root);
    root = nullptr;
    printf("post_str is %s \n",post_str);

    return 0;
}
