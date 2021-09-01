#include "NFlow/FlowNode.h"

#include <QDebug>

namespace NFlow {
    FlowNode::FlowNode() {

    }

    FlowNode::FlowNode(const FlowNode &reference) {

    }

    FlowNode::~FlowNode() {

    }

    void FlowNode::executor() {
        qDebug() << "Empty node executor call.";
    }

    void FlowNode::handler() {
        FlowDataset *dataset = nullptr; //TODO: get it;
        if (this->isPassthrough) return;
        for (const FlowInput* input : this->inputs) {
            if (input->isDirty) {
                this->executor();
                break;
            }
        }
    }

    FlowNode *FlowNode::copy() const {
        return new FlowNode(*this);
    }
}
