#include "../header/yAxisAlg.h"
#include <algorithm>

yAxisAlg::yAxisAlg(int x, float y, int z) {
    addhVal(x, y, z);
}

std::array<float, 15*15> yAxisAlg::yAxisGet(int heightDivider){

    srand(time(NULL));

    const int k = 15, l = 15;

    float yAxis[15][15];

    for (int i {}; i < k; i++) {
        for (int j{}; j < l; j++) {
            int sum = 0;
            float closest[3]{};
            for (int n{}; n < 3; n++)
                closest[n] = hVal.at(0).at(n);

            float closestDistance = abs(int(closest[0] - i)) + abs(int(closest[1]) - j);

            for (auto x : hVal) {
                int distance = abs((int(x.at(0)) - i)) + abs((int(x.at(1)) - j));

                sum += distance;

                if (distance < closestDistance) {
                    for (int n{}; n < 3; n++)
                        closest[n] = x.at(n);
                }
                closestDistance = abs(int(closest[0] - i)) + abs(int(closest[1]) - j);
            }

            float oppositeMeanDistance = 1 / float(float(sum / hVal.size()) / hVal.size());
            float oppositeMeanDistanceP1 = 1 / (float(float(sum / hVal.size()) / hVal.size()) + 1);

            float r = static_cast <float> (rand()) /
                      (static_cast <float> (RAND_MAX / (oppositeMeanDistance - oppositeMeanDistanceP1)));

            float mean;

            for (auto x: hVal) {
                mean += x.at(2);
            }

            mean += 2 * closest[2];

            mean /= hVal.size() + heightDivider;

            yAxis[i][j] = (mean / float(float(sum / hVal.size()) / hVal.size())) + r;

            if (hVal.size() == 1) {
                for (auto x: hVal) {
                    if (i == int(x.at(0)) && j == int(x.at(1))) { //skip if it's hVal
                        yAxis[i][j] = closest[2] * 1.5;
                    }
                }
            }
        }

    }


    return reinterpret_cast<std::array<float, 15*15> &&>(yAxis);
}

void yAxisAlg::addhVal(int x, float y, int z) {
    std::vector<float> newhVal;
    newhVal.push_back(float(x));
    newhVal.push_back(float(z));
    newhVal.push_back(y);

    hVal.push_back(newhVal);
}
