#ifndef POINT_VORTEX_FLOWNODE_H
#define POINT_VORTEX_FLOWNODE_H

#include <vector>

#include <QString>

#include "NFlow/Node.h"
#include "NFlow/FlowOutput.h"
#include "NFlow/FlowInput.h"

namespace NFlow {
    class FlowNode : public Node {
    protected:
        std::vector<FlowInput*> inputs;
        std::vector<FlowInput*> outputs;
        QString uid;
    public:
        FlowNode();
        FlowNode(const FlowNode& reference);
        ~FlowNode();
    public:
        virtual void executor();
        void handler();
    public:
        FlowNode* copy() const override;

    };
}

#endif //POINT_VORTEX_FLOWNODE_H
