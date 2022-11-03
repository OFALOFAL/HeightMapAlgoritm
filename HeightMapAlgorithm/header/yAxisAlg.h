#ifndef GLFWLEARN_YAXISALG_H
#define GLFWLEARN_YAXISALG_H

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <iomanip>

class yAxisAlg {
public:
    yAxisAlg(int x = 7, float y = 0, int z = 7);
    void addhVal(int x, float y, int z);

    inline std::vector<std::vector<float>> gethVals() {return hVal;}
    inline void clearhVals() {hVal.clear();}

    std::array<float, 15*15> yAxisGet(int heightDivider);

private:
    std::vector<std::vector<float>> hVal;

};


#endif
