#include <iostream>
#include <vector>
#include <cmath>

#include "BoundingBox.h"
#include "Geometry.h"
#include "Nms.h"
#include "Detection.h"
#include "Vec2.h"

using namespace std;

static int testsRan = 0;
static int testsFailed = 0;

static void check(bool passed, const char* name){
    ++testsRan;
    if(passed){
        cout << " pass " << name << "\n";
    } else {
        ++testsFailed;
        cout << " FAIL " << name << "\n";
    }
}

//float results compared with tolerance
static bool nearly(double a, double b, double eps = 1e-9){
    return fabs(a - b) < eps;
}


int main() {
    cout << "AutoPerception Tests\n\n";

    //iou 
    BoundingBox a{0, 0, 4, 2}; //1st parameter is x, 2nd is y, 3rd is width, 4th is height
    BoundingBox b{2, 1, 4, 2};
    BoundingBox c{5, 5, 2, 2};

    check(nearly(iou(a,a), 1.0), "iou: identical boxes give 1.0");  // iou of a box with itself should be 1.0
    check(nearly(iou(a,b), 2.0 / 14.0), "iou: non-overlapping boxes give 0.0"); // iou has half overlap, so should give 0.5
    check(nearly(iou(a,c), 0.0), "iou: non-overlapping boxes give 0.0"); // iou has no overlap, so should give 0.0

    //nms (non-maximum suppression)
    //1st parameter in Detection is position, 2nd is label, 3rd is bounding box, 4th is confidence score

    vector<Detection> raw = {{Vec2(0,0), "car", BoundingBox{100, 100, 50, 40}, 0.92}, {Vec2(0,0), "car", BoundingBox{104, 102, 50, 40}, 0.75} ,
                            {Vec2(0,0), "car", BoundingBox{300, 200, 50, 40}, 0.88}};
    

    vector<Detection> kept = nonMaxSuppression(raw);

    check(kept.size() == 2, "Nms: three detections collapse to two");
    check(nearly(kept[0].confidence, 0.92), "Nms: most confident box is kept");
    check(nearly(kept[1].confidence, 0.88), "Nms: the separate object survies");

    int passed = testsRan - testsFailed;

    cout << "\n"<< passed << "/" << testsRan << " checks passed\n";
    return testsFailed == 0 ? 0 : 1;

}