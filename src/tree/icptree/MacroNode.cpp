#include "tree/icptree/MacroNode.h"
#include "model/Macro.h"
#include "tree/binarytree/NextNodesBehaviorLeftFirst.h"
#include "tree/binarytree/NextNodesBehaviorRightFirst.h"
#include "tree/binarytree/NextNodesBehaviorRightOnly.h"
#include "tree/icptree/contour/Edge.h"

MacroNode::MacroNode() {
    branchNumber = MacroNode::TOP_BRANCH;
    setAsNormalNode();
    setPackingDirection(true);
    empty = false;
    macro = 0;
    verticalDisplacement = 0;
    covered = false;
    topEdge = 0;
    rightEdge = 0;
    bottomEdge = 0;
    leftEdge = 0;
}

MacroNode::MacroNode(Macro *macro) : MacroNode() {
    this->macro = macro;
}

MacroNode::~MacroNode() {
    if (empty)
        delete macro;
    delete topEdge;
    delete rightEdge;
    delete bottomEdge;
    delete leftEdge;
}

MacroNode::BranchNumber MacroNode::getNextBranchNumber(MacroNode::BranchNumber branchNumber) {
    switch (branchNumber) {
    case MacroNode::TOP_BRANCH:
        return MacroNode::RIGHT_BRANCH;
    case MacroNode::RIGHT_BRANCH:
        return MacroNode::BOTTOM_BRANCH;
    case MacroNode::BOTTOM_BRANCH:
        return MacroNode::LEFT_BRANCH;
    case MacroNode::LEFT_BRANCH:
        return MacroNode::TOP_BRANCH;
    default:
        return MacroNode::RIGHT_BRANCH;
    }
}

void MacroNode::setBranchNumber(MacroNode::BranchNumber branchNumber) {
    this->branchNumber = branchNumber;
}

MacroNode::BranchNumber MacroNode::getBranchNumber() {
    return branchNumber;
}

void MacroNode::setMacroWidthByBranchNumber(int width) {
    if (macro == 0) {
        return;
    }
    switch (branchNumber) {
    case MacroNode::TOP_BRANCH:
        macro->setWidth(width);
        break;
    case MacroNode::RIGHT_BRANCH:
        macro->setHeight(width);
        break;
    case MacroNode::BOTTOM_BRANCH:
        macro->setWidth(width);
        break;
    case MacroNode::LEFT_BRANCH:
        macro->setHeight(width);
        break;
    default:
        break;
    }
}

int MacroNode::getMacroWidthByBranchNumber() {
    if (macro == 0) {
        return 0;
    }
    switch (branchNumber) {
    case MacroNode::TOP_BRANCH:
        return macro->getWidth();
    case MacroNode::RIGHT_BRANCH:
        return macro->getHeight();
    case MacroNode::BOTTOM_BRANCH:
        return macro->getWidth();
    case MacroNode::LEFT_BRANCH:
        return macro->getHeight();
    default:
        return macro->getWidth();
    }
}

void MacroNode::setIdentity(MacroNode::Identity identity) {
    switch (identity) {
        case MacroNode::NORMAL_NODE:
            setAsNormalNode();
            break;
        case MacroNode::BRANCH_NODE:
            setAsBranchNode();
            break;
        case MacroNode::SWITCH_NODE:
            setAsSwitchNode();
            break;
        case MacroNode::CORNER_NODE:
            setAsCornerNode();
            break;
        default:
            setAsNormalNode();
            break;
    }
}

MacroNode::Identity MacroNode::getIdentity() {
    return identity;
}

void MacroNode::setAsNormalNode() {
    if (identity != MacroNode::NORMAL_NODE) {
        setNextNodesBehavior(new NextNodesBehaviorLeftFirst());
        identity = MacroNode::NORMAL_NODE;
    }
}

void MacroNode::setAsBranchNode() {
    if (identity != MacroNode::BRANCH_NODE) {
        updateBranchNodeNextNodesBehavior();
        identity = MacroNode::BRANCH_NODE;
    }
}

void MacroNode::setAsSwitchNode() {
    if (identity != MacroNode::SWITCH_NODE) {
        setNextNodesBehavior(new NextNodesBehaviorRightOnly());
        identity = MacroNode::SWITCH_NODE;
    }
}

void MacroNode::setAsCornerNode() {
    if (identity != MacroNode::CORNER_NODE) {
        setNextNodesBehavior(new NextNodesBehaviorRightOnly());
        identity = MacroNode::CORNER_NODE;
    }
}

bool MacroNode::isNormalNode() {
    return identity == MacroNode::NORMAL_NODE;
}

bool MacroNode::isBranchNode() {
    return identity == MacroNode::BRANCH_NODE;
}

bool MacroNode::isSwitchNode() {
    return identity == MacroNode::SWITCH_NODE;
}

bool MacroNode::isCornerNode() {
    return identity == MacroNode::CORNER_NODE;
}

void MacroNode::setPackingDirection(bool forward) {
    if (packingForward != forward) {
        packingForward = forward;
        if (identity == MacroNode::BRANCH_NODE)
            updateBranchNodeNextNodesBehavior();
    }
}

void MacroNode::changePackingDirection() {
    packingForward ^= true;
    if (identity == MacroNode::BRANCH_NODE)
        updateBranchNodeNextNodesBehavior();
}

bool MacroNode::isPackingForward() {
    return packingForward;
}

void MacroNode::setEmpty() {
    empty = true;
}

bool MacroNode::isEmptyNode() {
    return empty;
}

void MacroNode::setMacro(Macro *macro) {
    this->macro = macro;
}

Macro *MacroNode::getMacro() {
    return macro;
}

void MacroNode::setVerticalDisplacement(int displacement) {
    verticalDisplacement = displacement;
}

void MacroNode::addToVerticalDisplacement(int displacement) {
    verticalDisplacement += displacement;
}

int MacroNode::getVerticalDisplacement() {
    return verticalDisplacement;
}

void MacroNode::setCovered(bool covered) {
    this->covered = covered;
}

bool MacroNode::isCovered() {
    return covered;
}

Node *MacroNode::createNode() {
    return new MacroNode();
}

Node *MacroNode::copy() {
    MacroNode *node = dynamic_cast<MacroNode *>(Node::copy());
    node->setAttributes(packingForward, identity, empty);
    node->setVerticalDisplacement(verticalDisplacement);
    if (empty) {
        if (macro != 0) {
            node->setMacro(macro->copy());
        }   // Do not delete these braces or the if else statement changes.
    } else {
        node->setMacro(macro);
    }
    return node;
}

void MacroNode::setAttributes(bool packingForward, MacroNode::Identity identity, bool empty) {
    this->packingForward = packingForward;
    this->identity = identity;
    this->empty = empty;
}

MacroNode *MacroNode::createEmptyNode() {
    MacroNode *node = new MacroNode();
    node->setEmpty();
    return node;
}

MacroNode *MacroNode::createEmptyNode(MacroNode *node) {
    MacroNode *emptyNode = new MacroNode();
    emptyNode->setEmpty();
    emptyNode->setVerticalDisplacement(node->getVerticalDisplacement());
    if (node->getMacro() != 0) {
        emptyNode->setMacro(node->getMacro()->copy());
    }
    return emptyNode;
}

void MacroNode::updateBranchNodeNextNodesBehavior() {
    if (packingForward)
        setNextNodesBehavior(new NextNodesBehaviorLeftFirst());
    else
        setNextNodesBehavior(new NextNodesBehaviorRightFirst());
}

Edge *MacroNode::createTopEdge() {
    delete topEdge;
    topEdge = Edge::createTopEdge(macro->getXStart(), macro->getXEnd(), macro->getYEnd());
    topEdge->setMacroNode(this);
    return topEdge;
}

Edge *MacroNode::getTopEdge() {
    return topEdge;
}

Edge *MacroNode::createRightEdge() {
    delete rightEdge;
    rightEdge = Edge::createRightEdge(macro->getYEnd(), macro->getYStart(), macro->getXEnd());
    rightEdge->setMacroNode(this);
    return rightEdge;
}

Edge *MacroNode::getRightEdge() {
    return rightEdge;
}

Edge *MacroNode::createBottomEdge() {
    delete bottomEdge;
    bottomEdge = Edge::createBottomEdge(macro->getXEnd(), macro->getXStart(), macro->getYStart());
    bottomEdge->setMacroNode(this);
    return bottomEdge;
}

Edge *MacroNode::getBottomEdge() {
    return bottomEdge;
}

Edge *MacroNode::createLeftEdge() {
    delete leftEdge;
    leftEdge = Edge::createLeftEdge(macro->getYStart(), macro->getYEnd(), macro->getXStart());
    leftEdge->setMacroNode(this);
    return leftEdge;
}

Edge *MacroNode::getLeftEdge() {
    return leftEdge;
}
