// MIT License
//
// Copyright (c) 2021 Point Vortex | Danil Maksimovich Andrieiev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
