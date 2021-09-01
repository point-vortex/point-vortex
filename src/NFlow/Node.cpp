#include "NFlow/Node.h"

namespace NFlow {
    Node::Node() {
    }

    Node::Node(const Node &reference) : utils::ICopyable(reference) {
    }

    Node::~Node() {
    }

    Node *Node::copy() const {
        return new Node(*this);
    }
}
