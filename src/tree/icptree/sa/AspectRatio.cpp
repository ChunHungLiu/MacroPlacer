#include "tree/icptree/sa/AspectRatio.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

AspectRatio::AspectRatio(double targetRatio) {
    this->targetRatio = targetRatio;
}

AspectRatio::~AspectRatio() {

}

double AspectRatio::calculateCost(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    double ratio = floorplanState->getICPTree()->getBoundingBoxAspectRatio();
    if (ratio < targetRatio) {
        return targetRatio / ratio - 1;
    } else {
        return ratio / targetRatio - 1;
    }
}
