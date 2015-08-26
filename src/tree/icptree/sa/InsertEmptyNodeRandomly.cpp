#include "tree/icptree/sa/InsertEmptyNodeRandomly.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

InsertEmptyNodeRandomly::InsertEmptyNodeRandomly() {

}

InsertEmptyNodeRandomly::~InsertEmptyNodeRandomly() {

}

void InsertEmptyNodeRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->insertEmptyNodeRandomly();
    icpTree->placeMacrosAssumingNoSwitch();
}
