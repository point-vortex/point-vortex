#ifndef POINT_VORTEX_NODE_H
#define POINT_VORTEX_NODE_H

#include "utils/ICopyable.h"

namespace NFlow {
    class Node : public utils::ICopyable {
    protected:
        bool isPassthrough;
    public:
        Node();
        Node(const Node &reference);
        ~Node();
    public:
        [[nodiscard]] Node *copy() const override;
    };
}


#endif //POINT_VORTEX_NODE_H
