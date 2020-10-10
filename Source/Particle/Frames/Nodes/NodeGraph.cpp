#include "NodeGraph.h"

particle::NodeGraph::Input::Input(int id, std::string name, std::shared_ptr<dsp::Input> input)
        : id(id)
        , name(name)
        , input(input) {}

void particle::NodeGraph::Input::draw() {
    imnodes::BeginInputAttribute(id);
    ImGui::Text(name.c_str());
    imnodes::EndInputAttribute();
}

void particle::NodeGraph::Input::drawInspector() {}

particle::NodeGraph::Output::Output(int id, std::string name, std::shared_ptr<dsp::Output> output)
        : id(id)
        , name(name)
        , output(output) {}

void particle::NodeGraph::Output::draw() {
    imnodes::BeginOutputAttribute(id);
    ImGui::Text(name.c_str());
    imnodes::EndOutputAttribute();
}

void particle::NodeGraph::Output::drawInspector() {}

particle::NodeGraph::Node::Category::Category(std::string name, std::vector<Type> types)
        : name(name)
        , types(types) {}

particle::NodeGraph::Node::Node(int id, Type type, std::shared_ptr<dsp::Node> node)
        : id(id)
        , type(type)
        , node(node) {}

std::string particle::NodeGraph::Node::getName() const {
    return (std::to_string(id) + " - " + getTypeName(type, customName)).c_str();
}

std::string particle::NodeGraph::Node::getCustomName() const {
    return customName;
}

void particle::NodeGraph::Node::setCustomName(std::string name) {
    this->customName = customName;
}

void particle::NodeGraph::Node::draw() {
    imnodes::BeginNode(id);
    imnodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    imnodes::EndNodeTitleBar();
    ImGui::BeginGroup();
    for (auto &input : inputs) {
        input.second.draw();
    }
    ImGui::EndGroup();
    ImGui::SameLine(0);
    drawContent();
    ImGui::SameLine(0);
    ImGui::BeginGroup();
    for (auto& output : outputs) {
        output.second.draw();
    }
    ImGui::EndGroup();
    imnodes::EndNode();
}

void particle::NodeGraph::Node::drawContent() {
    // ImGui::BeginChild("Child", ImVec2(200, 200));
    // ImGui::EndChild();
}

void particle::NodeGraph::Node::drawInspector() {}

std::vector<particle::NodeGraph::Node::Category> particle::NodeGraph::Node::getCategories() {
    std::vector<Category> categories;
    categories.push_back(Category("Analyzers", std::vector<Type>{Type::RECORDER}));
    categories.push_back(Category(
            "Channel",
            std::vector<Type>{
                    Type::CHANNEL_MERGER, Type::CHANNEL_SPLITTER, Type::MID_SIDE, Type::SPREAD, Type::STEREO_PANNER}));
    categories.push_back(Category("Delays", std::vector<Type>{Type::CONVOLVER, Type::VARIABLE_DELAY}));
    categories.push_back(Category(
            "Dynamics",
            std::vector<Type>{Type::CLIPPER, Type::COMPRESSOR_GATE, Type::DRY_WET, Type::ENVELOPE, Type::SHAPER}));
    categories.push_back(Category("External", std::vector<Type>{Type::MIDI_INPUT, Type::MIDI_OUTPUT}));
    categories.push_back(Category("Filters", std::vector<Type>{Type::BIQUAD, Type::CROSSOVER, Type::ONE_POLE}));
    categories.push_back(
            Category("Generators", std::vector<Type>{Type::NOISE, Type::OSCILLATOR, Type::PHASOR, Type::SAMPLE_PLAYER}));
    categories.push_back(Category("Math",
                                  std::vector<Type>{
                                          Type::ABSOLUTE_VALUE,
                                          Type::BOOLEAN_MASK,
                                          Type::COMPARISON,
                                          Type::EXP2,
                                          Type::FLOOR,
                                          Type::FORWARD_FFT,
                                          Type::FREQUENCY_TO_NOTE,
                                          Type::IDENTITY,
                                          Type::INVERSE_FFT,
                                          Type::LOG2,
                                          Type::MODULO,
                                          Type::MULTIPLY,
                                          Type::MULTIPLY_HERTZ_SECONDS,
                                          Type::NOTE_TO_FREQUENCY,
                                          Type::NOT_GATE,
                                          Type::ONE_OVER
                                  }));
    categories.push_back(Category("Trigger",
                                  std::vector<Type>{Type::BEAT_TRIGGER,
                                                    Type::DIFFERENTIATOR,
                                                    Type::INTEGRATOR,
                                                    Type::ON_OFF,
                                                    Type::RESET_TRIGGER,
                                                    Type::SAMPLE_AND_HOLD,
                                                    Type::SEQUENCER}));
    categories.push_back(Category("Variables",
                                  std::vector<Type>{Type::BEAT_DURATION,
                                                    Type::BEAT_RATE,
                                                    Type::BUFFER_DURATION,
                                                    Type::BUFFER_RATE,
                                                    Type::SAMPLE_DURATION,
                                                    Type::SAMPLE_RATE}));
    return categories;
}

std::string particle::NodeGraph::Node::getTypeName(Type type, std::string customName) {
    switch (type) {
        case Type::CUSTOM: return customName;
        case Type::RECORDER: return "Recorder";
        case Type::CHANNEL_MERGER: return "Channel Merger";
        case Type::CHANNEL_SPLITTER: return "Channel Splitter";
        case Type::MID_SIDE: return "Mid/Side";
        case Type::SPREAD: return "Spread";
        case Type::STEREO_PANNER: return "Stereo Panner";
        case Type::CONVOLVER: return "Convolver";
        case Type::VARIABLE_DELAY: return "Variable Delay";
        case Type::CLIPPER: return "Clipper";
        case Type::COMPRESSOR_GATE: return "Compressor/Gate";
        case Type::DRY_WET: return "Dry/Wet";
        case Type::ENVELOPE: return "Envelope";
        case Type::SHAPER: return "Shaper";
        case Type::MIDI_INPUT: return "MIDI Input";
        case Type::MIDI_OUTPUT: return "MIDI Output";
        case Type::BIQUAD: return "Biquad";
        case Type::CROSSOVER: return "Crossover";
        case Type::ONE_POLE: return "One-Pole";
        case Type::NOISE: return "Noise";
        case Type::OSCILLATOR: return "Oscillator";
        case Type::PHASOR: return "Phasor";
        case Type::SAMPLE_PLAYER: return "Sample Player";
        case Type::ABSOLUTE_VALUE: return "Absolute Value";
        case Type::BOOLEAN_MASK: return "Boolean Mask";
        case Type::COMPARISON: return "Comparison";
        case Type::EXP2: return "Exponential";
        case Type::FLOOR: return "Floor";
        case Type::FORWARD_FFT: return "Forward FFT";
        case Type::FREQUENCY_TO_NOTE: return "Frequency to Note";
        case Type::IDENTITY: return "Identity";
        case Type::INVERSE_FFT: return "Inverse FFT";
        case Type::LOG2: return "Logarithm";
        case Type::MODULO: return "Modulo";
        case Type::MULTIPLY: return "Multiply";
        case Type::MULTIPLY_HERTZ_SECONDS: return "Multiply Hertz/Seconds";
        case Type::NOTE_TO_FREQUENCY: return "Note to Frequency";
        case Type::NOT_GATE: return "Not Gate";
        case Type::ONE_OVER: return "Reciprocal";
        case Type::BEAT_TRIGGER: return "Beat Trigger";
        case Type::DIFFERENTIATOR: return "Differentiator";
        case Type::INTEGRATOR: return "Integrator";
        case Type::ON_OFF: return "On/Off";
        case Type::RESET_TRIGGER: return "Reset Trigger";
        case Type::SAMPLE_AND_HOLD: return "Sample & Hold";
        case Type::SEQUENCER: return "Sequencer";
        case Type::BEAT_DURATION: return "Beat Duration";
        case Type::BEAT_RATE: return "Beat Rate";
        case Type::BUFFER_DURATION: return "Buffer Duration";
        case Type::BUFFER_RATE: return "Buffer Rate";
        case Type::SAMPLE_DURATION: return "Sample Duration";
        case Type::SAMPLE_RATE: return "Sample Rate";
    }
}

particle::NodeGraph::Link::Link(int id, Output from, Input to)
        : id(id)
        , from(from)
        , to(to) {}

void particle::NodeGraph::Link::draw() {
    imnodes::Link(id, from.id, to.id);
}

void particle::NodeGraph::Link::drawInspector() {}

particle::NodeGraph::NodeGraph(Data &data, std::string name, std::vector<std::shared_ptr<dsp::Node>> &audioNodes)
        : Frame(data, name)
        , audioNodes(audioNodes) {
    context = imnodes::EditorContextCreate();
}

particle::NodeGraph::~NodeGraph() {
    imnodes::EditorContextFree(context);
}

imnodes::EditorContext *particle::NodeGraph::getContext() const {
    return context;
}

std::vector<std::shared_ptr<dsp::Node>> &particle::NodeGraph::getAudioNodes() {
    return audioNodes;
}

std::vector<dsp::Output> &particle::NodeGraph::getInputs() {
    return inputs;
}

std::vector<dsp::Input> &particle::NodeGraph::getOutputs() {
    return outputs;
}

std::vector<std::string> &particle::NodeGraph::getInputNames() {
    return inputNames;
}

std::vector<std::string> &particle::NodeGraph::getOutputNames() {
    return outputNames;
}

void particle::NodeGraph::drawInternal() {
    imnodes::EditorContextSet(context);
    imnodes::BeginNodeEditor();
    drawPopup();
    for (auto &node : nodes) {
        node.second.draw();
    }
    for (auto &link : links) {
        link.second.draw();
    }
    imnodes::EndNodeEditor();
}

void particle::NodeGraph::drawPopup() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.f, 8.f));
    if (!ImGui::IsAnyItemHovered() && imnodes::IsEditorHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
        ImGui::OpenPopup("Create Node");
    }
    if (ImGui::BeginPopup("Create Node")) {
        const ImVec2 mousePosition = ImGui::GetMousePosOnOpeningCurrentPopup();
        for (const auto &category : Node::getCategories()) {
            if (ImGui::BeginMenu(category.name.c_str())) {
                for (const auto &type : category.types) {
                    if (ImGui::MenuItem(Node::getTypeName(type).c_str())) {
                        // TODO: Do something
                    }
                }
                ImGui::EndMenu();
            }
        }
        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();
}
