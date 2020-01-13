#ifndef IMGUI_DEFINE_MATH_OPERATORS
    #define IMGUI_DEFINE_MATH_OPERATORS
#endif

#pragma once
#include <syntacts>
#include <carnot>
#include <deque>
#include "ImGui/PolyBezier.hpp"
#include "Palette.hpp"

///////////////////////////////////////////////////////////////////////////////

namespace ImGui {

bool NodeHeld();
void NodeSlot(const char* label, const ImVec2& size = ImVec2(-1, 0), ImGuiCol col = ImGuiCol_Button);
void BeginNodeTarget(ImGuiCol col = ImGuiCol_Button);
void EndNodeTarget();

void NodeSourceP(PItem pitem);
void NodeSourceL(const std::string& name);
bool NodeDroppedP();
bool NodeDroppedL();
PItem NodePayloadP();
const std::string& NodePayloadL();

void NodeUpdate();
}

const std::string& signalName(std::type_index id);
const std::string& signalName(const tact::Signal& sig);

///////////////////////////////////////////////////////////////////////////////

struct Node {
    virtual void gui() = 0;
    virtual tact::Signal signal() = 0;
    virtual const std::string& name() = 0;
    virtual bool empty() { return false; };
    virtual float* gain() = 0;
    virtual float* bias() = 0;
};

std::shared_ptr<Node> makeNode(PItem id);

///////////////////////////////////////////////////////////////////////////////

struct NodeList : public Node { 
    void gui();
    float* gain() override;
    float* bias() override;
    std::vector<std::shared_ptr<Node>> m_nodes;
    std::deque<bool> m_closeHandles;
    std::vector<int> m_ids;
    int m_nextId;
    float m_scale = 1, m_offset = 0;
};

///////////////////////////////////////////////////////////////////////////////

struct ProductNode : public NodeList
{
    tact::Signal signal() override;
    const std::string& name() override;
};

///////////////////////////////////////////////////////////////////////////////

struct SumNode : public NodeList
{
    tact::Signal signal() override;
    const std::string& name() override;
};

///////////////////////////////////////////////////////////////////////////////

struct LibrarySignalNode : public Node {
    LibrarySignalNode(const std::string& name);
    tact::Signal signal() override;
    const std::string& name() override;
    void gui() override;
    float* gain() override;
    float* bias() override;
protected:
    std::string libName;
    tact::Signal sig;    
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct SignalNode : public Node {
    tact::Signal signal() override { return sig; }
    const std::string& name() override { return signalName(sig.typeId()); }
    float* gain() override { return &sig.scale; }
    float* bias() override { return &sig.offset; }
protected:
    tact::Signal sig = T();
};

///////////////////////////////////////////////////////////////////////////////

struct OscillatorNode : public SignalNode<tact::Sine> {
    OscillatorNode(tact::Signal osc);
    void gui() override;
};

///////////////////////////////////////////////////////////////////////////////

struct ChirpNode : public SignalNode<tact::Chirp> {    
    void gui() override;
};

///////////////////////////////////////////////////////////////////////////////

struct ExpressionNode : public SignalNode<tact::Expression> {
    ExpressionNode();
    void gui();
    char buffer[256];
    bool ok = true;
};

///////////////////////////////////////////////////////////////////////////////

struct PolyBezierNode : public SignalNode<tact::PolyBezier> {
    PolyBezierNode();
    void gui();
    ImGui::PolyBezier pb;
    static std::vector<carnot::Color> colors; 
    static int colorIdx;
};

///////////////////////////////////////////////////////////////////////////////

struct EnvelopeNode : public SignalNode<tact::Envelope> {
    void gui();
};

///////////////////////////////////////////////////////////////////////////////

struct ASRNode : public SignalNode<tact::ASR> {
    void gui() ;
};

///////////////////////////////////////////////////////////////////////////////

struct ADSRNode : public SignalNode<tact::ADSR> {
    void gui();
};

///////////////////////////////////////////////////////////////////////////////

struct NoiseNode : public SignalNode<tact::Noise> {
    void gui();
};

///////////////////////////////////////////////////////////////////////////////

struct TimeNode : public SignalNode<tact::Time> {
    void gui();
};

///////////////////////////////////////////////////////////////////////////////

struct ScalarNode : SignalNode<tact::Scalar> {
    void gui();
};

///////////////////////////////////////////////////////////////////////////////

struct RampNode : SignalNode<tact::Ramp> {
    void gui();
};

///////////////////////////////////////////////////////////////////////////////