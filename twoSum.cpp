#include <iostream>
#include <vector>
#include <unordered_map>

void sum2(std::vector<int> &v, int target) {
    std::unordered_map<int, int> num2index;
    for (int i = 0; i < v.size(); i++) {
        int match = target - v[i];
        if (num2index.end() != num2index.find(match)) {
            std::cout << "pair [" << i << "," << num2index[match] << "] = (" << v[i] << "," << match << ")" << std::endl;
        }
        num2index[v[i]] = i;
    }
}

int main() {
    std::vector<int> v = {2,6,0,4,1,3,7,5};
    sum2(v, 4);
    return 0;
}

