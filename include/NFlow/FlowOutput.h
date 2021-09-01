#ifndef POINT_VORTEX_FLOWOUTPUT_H
#define POINT_VORTEX_FLOWOUTPUT_H

#include <vector>

#include <QString>

#include "NFlow/IFlowable.h"

namespace NFlow {
    class FlowInput;
    class FlowNode;

    class FlowOutput : public IFlowable {
        friend FlowNode;
    public:
        std::vector<FlowInput*> outputs;
        QString name;
        FlowNode* node;
    public:
        [[nodiscard]] FlowNode* getNode() const;
    };

}


#endif //POINT_VORTEX_FLOWOUTPUT_H
