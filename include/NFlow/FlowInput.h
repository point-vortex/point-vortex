#ifndef POINT_VORTEX_FLOWINPUT_H
#define POINT_VORTEX_FLOWINPUT_H

#include <QString>

#include "NFlow/FlowDataset.h"
#include "NFlow/FlowOutput.h"

namespace NFlow {
    class FlowInput {
        friend FlowNode;

        FlowOutput* input;
        QString name;
        FlowNode* node;
        bool isDirty;
    };
}


#endif //POINT_VORTEX_FLOWINPUT_H
