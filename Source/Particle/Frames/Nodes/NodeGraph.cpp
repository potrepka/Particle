#include "NodeGraph.h"

particle::NodeGraph::FloatInt::FloatInt(dsp::Type type, dsp::Sample value) {
    switch (type) {
        case dsp::Type::RATIO:
        case dsp::Type::HERTZ:
        case dsp::Type::SECONDS: valueFloat = value; break;
        case dsp::Type::INTEGER:
        case dsp::Type::BOOLEAN: valueInt = value; break;
    }
}

particle::NodeGraph::Input::Input(Data *data, int id, std::string name, std::shared_ptr<dsp::Input> input)
        : Named(name)
        , data(data)
        , id(id)
        , input(input)
        , value(input->getType(), input->getDefaultValue()) {}

void particle::NodeGraph::Input::draw() {
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, data->getStyle().framePadding);
    imnodes::BeginInputAttribute(id, imnodes::PinShape::PinShape_QuadFilled);
    ImGui::SetNextItemWidth(190);
    if (input->getConnections().size() == 0) {
        ImGuiIO &io = ImGui::GetIO();
        switch (input->getType()) {
            case dsp::Type::RATIO:
            case dsp::Type::HERTZ:
            case dsp::Type::SECONDS: {
                int precision = 16;
                float speed = io.KeyAlt ? 0.1f : io.KeyShift ? 100.0f : 1.0f;
                if (ImGui::DragFloat(getName().c_str(),
                                     &value.valueFloat,
                                     speed,
                                     0.0f,
                                     static_cast<float>(input->getRange()),
                                     ("%." + std::to_string(precision) + "f").c_str(),
                                     ImGuiSliderFlags_AlwaysClamp)) {
                    input->setAllChannelValues(value.valueFloat);
                    input->setDefaultValue(value.valueFloat);
                }
            } break;
            case dsp::Type::INTEGER: {
                float speed = io.KeyAlt ? 1.0f : 0.1f;
                if (ImGui::DragInt(getName().c_str(),
                                   &value.valueInt,
                                   speed,
                                   0,
                                   static_cast<int>(input->getRange()),
                                   "%d",
                                   ImGuiSliderFlags_AlwaysClamp)) {
                    input->setAllChannelValues(value.valueInt);
                    input->setDefaultValue(value.valueInt);
                }
            } break;
            case dsp::Type::BOOLEAN: {
                float speed = io.KeyAlt ? 100.0f : io.KeyShift ? 0.1f : 1.0f;
                if (ImGui::DragInt(
                            getName().c_str(), &value.valueInt, speed, 0, 1, "%d", ImGuiSliderFlags_AlwaysClamp)) {
                    input->setAllChannelValues(value.valueInt);
                    input->setDefaultValue(value.valueInt);
                }
            } break;
        }
    } else {
        input->lock();
        std::vector<dsp::Sample> x(input->getNumSamples());
        std::iota(x.begin(), x.end(), 0);
        switch (input->getType()) {
            case dsp::Type::RATIO:
            case dsp::Type::HERTZ:
            case dsp::Type::SECONDS: {
                int precision = 16;
                float lastSample = input->getWrapper().getSample(0, input->getNumSamples() - 1);
                lastSample = lastSample == 0.0 ? 0.0 : lastSample;
                ImGui::DragFloat(getName().c_str(),
                                 &lastSample,
                                 0.0f,
                                 0.0f,
                                 0.0f,
                                 ("%." + std::to_string(precision) + "f").c_str(),
                                 ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_NoInput);
            } break;
            case dsp::Type::INTEGER:
            case dsp::Type::BOOLEAN: {
                int lastSample = input->getWrapper().getSample(0, input->getNumSamples() - 1);
                ImGui::DragInt(getName().c_str(),
                               &lastSample,
                               0.0f,
                               0,
                               0,
                               "%d",
                               ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_NoInput);
            } break;
        }

        // TODO: remove commented code, put plots elsewhere

        //ImPlot::SetNextPlotLimits(0, input->getNumSamples(), -1, 1);
        //if (ImPlot::BeginPlot(("##" + getName()).c_str(),
        //                      NULL,
        //                      NULL,
        //                      ImVec2(100, ImGui::GetFrameHeight()),
        //                      ImPlotFlags_CanvasOnly | ImPlotFlags_NoChild,
        //                      ImPlotAxisFlags_Lock | ImPlotAxisFlags_NoDecorations,
        //                      ImPlotAxisFlags_Lock | ImPlotAxisFlags_NoDecorations)) {
        //    ImPlot::PlotLine("Channel 0",
        //                     x.data(),
        //                     input->getWrapper().getChannelPointer(0),
        //                     input->getNumSamples(),
        //                     0,
        //                     sizeof(dsp::Sample));
        //    ImPlot::EndPlot();
        //}
        //ImGui::SameLine();
        //ImGui::Text("%s", getName().c_str());

        input->unlock();
    }
    imnodes::EndInputAttribute();
    ImGui::PopStyleVar();
}

void particle::NodeGraph::Input::drawInspector() {}

// TODO: Set can edit
particle::NodeGraph::Output::Output(Data *data, int id, std::string name, std::shared_ptr<dsp::Output> output)
        : Named(name)
        , data(data)
        , id(id)
        , output(output)
        , value(output->getType(), output->getDefaultValue()) {}

void particle::NodeGraph::Output::draw() {
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, data->getStyle().framePadding);
    imnodes::BeginOutputAttribute(id, imnodes::PinShape::PinShape_QuadFilled);
    ImGui::SetNextItemWidth(190);
    output->lock();
    std::vector<dsp::Sample> x(output->getNumSamples());
    std::iota(x.begin(), x.end(), 0);
    switch (output->getType()) {
        case dsp::Type::RATIO:
        case dsp::Type::HERTZ:
        case dsp::Type::SECONDS: {
            int precision = 16;
            float lastSample = output->getWrapper().getSample(0, output->getNumSamples() - 1);
            lastSample = lastSample == 0.0 ? 0.0 : lastSample;
            ImGui::DragFloat(getName().c_str(),
                             &lastSample,
                             0.0f,
                             0.0f,
                             0.0f,
                             ("%." + std::to_string(precision) + "f").c_str(),
                             ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_NoInput);
            break;
        }
        case dsp::Type::INTEGER:
        case dsp::Type::BOOLEAN: {
            int lastSample = output->getWrapper().getSample(0, output->getNumSamples() - 1);
            ImGui::DragInt(getName().c_str(),
                           &lastSample,
                           0.0f,
                           0,
                           0,
                           "%d",
                           ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_NoInput);
            break;
        }
    }

    // TODO: remove commented code, put plots elsewhere

    //ImPlot::SetNextPlotLimits(0, output->getNumSamples(), -1, 1);
    //if (ImPlot::BeginPlot(("##" + getName()).c_str(),
    //                      NULL,
    //                      NULL,
    //                      ImVec2(100, ImGui::GetFrameHeight()),
    //                      ImPlotFlags_CanvasOnly | ImPlotFlags_NoChild,
    //                      ImPlotAxisFlags_Lock | ImPlotAxisFlags_NoDecorations,
    //                      ImPlotAxisFlags_Lock | ImPlotAxisFlags_NoDecorations)) {
    //    ImPlot::PlotLine("Channel 0",
    //                     x.data(),
    //                     output->getWrapper().getChannelPointer(0),
    //                     output->getNumSamples(),
    //                     0,
    //                     sizeof(dsp::Sample));
    //    ImPlot::EndPlot();
    //}
    //ImGui::SameLine();cd 
    //ImGui::Text("%s", getName().c_str());

    output->unlock();
    imnodes::EndOutputAttribute();
    ImGui::PopStyleVar();
}

void particle::NodeGraph::Output::drawInspector() {}

particle::NodeGraph::Node::Category::Category(std::string name, std::vector<Type> types)
        : Named(name)
        , types(types) {}

particle::NodeGraph::Node::Node(Data *data, int id, Type type, ImVec2 position, std::shared_ptr<dsp::Node> node)
        : Named("")
        , data(data)
        , id(id)
        , type(type)
        , position(position)
        , node(node) {}

void particle::NodeGraph::Node::addInput(int id, std::string name, std::shared_ptr<dsp::Input> input) {
    inputs.emplace(id, Input(data, id, name, input));
}

void particle::NodeGraph::Node::addOutput(int id, std::string name, std::shared_ptr<dsp::Output> output) {
    outputs.emplace(id, Output(data, id, name, output));
}

std::string particle::NodeGraph::Node::getTypeName() const {
    return getTypeName(type);
}

void particle::NodeGraph::Node::draw(bool selected) {
    if (selected) {
        // TODO: uncomment
        //imnodes::PushStyleVar(imnodes::StyleVar_NodeBorderThickness, 2.5f);
        imnodes::PushColorStyle(imnodes::ColorStyle_NodeOutline,
                                imnodes::GetStyle().colors[imnodes::ColorStyle_LinkSelected]);
    }
    imnodes::BeginNode(id);
    imnodes::BeginNodeTitleBar();
    ImGui::Text("%s", getTypeName(type).c_str());
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
    if (selected) {
        imnodes::PopColorStyle();
        // TODO: uncomment
        //imnodes::PopStyleVar();
    }
}

void particle::NodeGraph::Node::drawContent() {
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, data->getStyle().framePadding);

    // TODO: remove this comment
    // ImGui::BeginChild("Child", ImVec2(200, 200));
    // ImGui::EndChild();

    switch (type) {
        case Type::RESET_TRIGGER: {
            std::shared_ptr<dsp::ResetTrigger> resetTrigger = std::dynamic_pointer_cast<dsp::ResetTrigger>(node);
            if (ImGui::Button("Reset")) {
                resetTrigger->reset();
            }
        } break;
    }
    ImGui::PopStyleVar();
}

void particle::NodeGraph::Node::drawInspector() {}

std::vector<particle::NodeGraph::Node::Category> particle::NodeGraph::Node::getCategories(bool isPlugin) {
    std::vector<Category> categories;
    categories.push_back(Category("Analyzers", std::vector<Type>{Type::RECORDER}));
    categories.push_back(Category(
            "Channel",
            std::vector<Type>{
                    Type::CHANNEL_MERGER, Type::CHANNEL_SPLITTER, Type::MID_SIDE, Type::SPREAD, Type::STEREO_PANNER}));
    categories.push_back(Category("Delays", std::vector<Type>{Type::CONVOLVER, Type::VARIABLE_DELAY}));
    categories.push_back(Category(
            "Dynamics",
            std::vector<Type>{
                    Type::CLIPPER, Type::COMPRESSOR_GATE, Type::CROSSFADER, Type::ENVELOPE, Type::LAG, Type::SHAPER}));
    categories.push_back(Category("External",
                                  std::vector<Type>{Type::AUDIO_INPUT,
                                                    Type::AUDIO_INPUT_CLIPPING,
                                                    Type::AUDIO_OUTPUT,
                                                    Type::AUDIO_OUTPUT_CLIPPING,
                                                    Type::MIDI_INPUT,
                                                    Type::MIDI_OUTPUT}));
    categories.push_back(Category("Filters", std::vector<Type>{Type::BIQUAD, Type::CROSSOVER, Type::ONE_POLE}));
    categories.push_back(Category(
            "Generators",
            std::vector<Type>{
                    Type::MOORER_DSF, Type::NOISE, Type::PHASOR, Type::SAMPLE_PLAYER, Type::TABLE_OSCILLATOR}));
    categories.push_back(Category("Math",
                                  std::vector<Type>{Type::ABSOLUTE_VALUE,
                                                    Type::BOOLEAN_MASK,
                                                    Type::COMPARISON,
                                                    Type::DIVISION,
                                                    Type::FLOOR,
                                                    Type::FORWARD_FFT,
                                                    Type::FREQUENCY_TO_NOTE,
                                                    Type::HYPERBOLIC,
                                                    Type::INVERSE_FFT,
                                                    Type::LOGARITHM,
                                                    Type::MODULO,
                                                    Type::MULTIPLICATION,
                                                    Type::NEGATIVE,
                                                    Type::NOTE_TO_FREQUENCY,
                                                    Type::NOT_GATE,
                                                    Type::POWER,
                                                    Type::RECIPROCAL,
                                                    Type::TRIGONOMETRIC}));
    if (isPlugin) {
        categories.push_back(Category("Plugin",
                                      std::vector<Type>{Type::BEAT_DURATION,
                                                        Type::BEAT_RATE,
                                                        Type::TIME_SIGNATURE,
                                                        Type::TRANSPORT_STATE}));
    }
    categories.push_back(Category("Trigger",
                                  std::vector<Type>{Type::CLOCK_TRIGGER,
                                                    Type::DIFFERENTIATOR,
                                                    Type::INTEGRATOR,
                                                    Type::ON_OFF,
                                                    Type::RESET_TRIGGER,
                                                    Type::SAMPLE_AND_HOLD,
                                                    Type::SEQUENCER,
                                                    Type::TRIGGER_HOLD}));
    categories.push_back(Category("Variables",
                                  std::vector<Type>{Type::BUFFER_DURATION,
                                                    Type::BUFFER_RATE,
                                                    Type::EULER,
                                                    Type::INF,
                                                    Type::PHI,
                                                    Type::PI,
                                                    Type::SAMPLE_DURATION,
                                                    Type::SAMPLE_RATE,
                                                    Type::TAU,
                                                    Type::VARIABLE}));
    return categories;
     
}

std::string particle::NodeGraph::Node::getTypeName(Type type) {
    switch (type) {
        case Type::CUSTOM: return "Custom";
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
        case Type::CROSSFADER: return "Crossfader";
        case Type::ENVELOPE: return "Envelope";
        case Type::LAG: return "Lag";
        case Type::SHAPER: return "Shaper";
        case Type::AUDIO_INPUT: return "Audio Input";
        case Type::AUDIO_INPUT_CLIPPING: return "Audio Input Clipping";
        case Type::AUDIO_OUTPUT: return "Audio Output";
        case Type::AUDIO_OUTPUT_CLIPPING: return "Audio Output Clipping";
        case Type::MIDI_INPUT: return "MIDI Input";
        case Type::MIDI_OUTPUT: return "MIDI Output";
        case Type::BIQUAD: return "Biquad";
        case Type::CROSSOVER: return "Crossover";
        case Type::ONE_POLE: return "One-Pole";
        case Type::MOORER_DSF: return "Moorer DSF";
        case Type::NOISE: return "Noise";
        case Type::PHASOR: return "Phasor";
        case Type::SAMPLE_PLAYER: return "Sample Player";
        case Type::TABLE_OSCILLATOR: return "Table Oscillator";
        case Type::ABSOLUTE_VALUE: return "Absolute Value";
        case Type::BOOLEAN_MASK: return "Boolean Mask";
        case Type::COMPARISON: return "Comparison";
        case Type::DIVISION: return "Division";
        case Type::FLOOR: return "Floor";
        case Type::FORWARD_FFT: return "Forward FFT";
        case Type::FREQUENCY_TO_NOTE: return "Frequency to Note";
        case Type::HYPERBOLIC: return "Hyperbolic";
        case Type::INVERSE_FFT: return "Inverse FFT";
        case Type::LOGARITHM: return "Logarithm";
        case Type::MODULO: return "Modulo";
        case Type::MULTIPLICATION: return "Multiplication";
        case Type::NEGATIVE: return "Negative";
        case Type::NOTE_TO_FREQUENCY: return "Note to Frequency";
        case Type::NOT_GATE: return "Not Gate";
        case Type::POWER: return "Power";
        case Type::RECIPROCAL: return "Reciprocal";
        case Type::TRIGONOMETRIC: return "Trigonometric";
        case Type::BEAT_DURATION: return "Beat Duration";
        case Type::BEAT_RATE: return "Beat Rate";
        case Type::TIME_SIGNATURE: return "Time Signature";
        case Type::TRANSPORT_STATE: return "Transport State";
        case Type::CLOCK_TRIGGER: return "Clock Trigger";
        case Type::DIFFERENTIATOR: return "Differentiator";
        case Type::INTEGRATOR: return "Integrator";
        case Type::ON_OFF: return "On/Off";
        case Type::RESET_TRIGGER: return "Reset Trigger";
        case Type::SAMPLE_AND_HOLD: return "Sample & Hold";
        case Type::SEQUENCER: return "Sequencer";
        case Type::TRIGGER_HOLD: return "Trigger Hold";
        case Type::BUFFER_DURATION: return "Buffer Duration";
        case Type::BUFFER_RATE: return "Buffer Rate";
        case Type::EULER: return "Euler";
        case Type::INF: return "Infinity";
        case Type::PHI: return "Phi";
        case Type::PI: return "Pi";
        case Type::SAMPLE_DURATION: return "Sample Duration";
        case Type::SAMPLE_RATE: return "Sample Rate";
        case Type::TAU: return "Tau";
        case Type::VARIABLE: return "Variable";

    }
}

particle::NodeGraph::Node
particle::NodeGraph::Node::generate(Data *data, int &counter, int id, Type type, ImVec2 position) {
    switch (type) {
        case Type::CUSTOM: {
            std::shared_ptr<dsp::Node> custom = std::make_shared<dsp::Node>();
            Node node(data, id, type, position, custom);
            return node;
        }
        case Type::RECORDER: {
            std::shared_ptr<dsp::Recorder> recorder = std::make_shared<dsp::Recorder>();
            Node node(data, id, type, position, recorder);
            node.addInput(++counter, "Input", recorder->getInput());
            node.addInput(++counter, "Gate", recorder->getGate());
            node.addInput(++counter, "Reset", recorder->getReset());
            return node;
        }
        case Type::CHANNEL_MERGER: {
            std::shared_ptr<dsp::ChannelMerger> merger = std::make_shared<dsp::ChannelMerger>();
            Node node(data, id, type, position, merger);
            node.addOutput(++counter, "Output", merger->getOutput());
            return node;
        }
        case Type::CHANNEL_SPLITTER: {
            std::shared_ptr<dsp::ChannelSplitter> splitter = std::make_shared<dsp::ChannelSplitter>();
            Node node(data, id, type, position, splitter);
            node.addInput(++counter, "Input", splitter->getInput());
            return node;
        }
        case Type::MID_SIDE: {
            std::shared_ptr<dsp::MidSide> midSide = std::make_shared<dsp::MidSide>();
            Node node(data, id, type, position, midSide);
            node.addInput(++counter, "Input", midSide->getInput());
            node.addInput(++counter, "Mix Amount", midSide->getMixAmount());
            node.addOutput(++counter, "Mid", midSide->getMid());
            node.addOutput(++counter, "Side", midSide->getSide());
            return node;
        }
        case Type::SPREAD: {
            std::shared_ptr<dsp::Spread> spread = std::make_shared<dsp::Spread>();
            Node node(data, id, type, position, spread);
            node.addInput(++counter, "Input", spread->getInput());
            node.addInput(++counter, "Spread", spread->getSpread());
            node.addInput(++counter, "Mode", spread->getMode());
            node.addOutput(++counter, "Output", spread->getOutput());
            return node;
        }
        case Type::STEREO_PANNER: {
            std::shared_ptr<dsp::StereoPanner> stereoPanner = std::make_shared<dsp::StereoPanner>();
            Node node(data, id, type, position, stereoPanner);
            node.addInput(++counter, "Input", stereoPanner->getInput());
            node.addInput(++counter, "Direction", stereoPanner->getDirection());
            node.addOutput(++counter, "Left", stereoPanner->getLeft());
            node.addOutput(++counter, "Right", stereoPanner->getRight());
            return node;
        }
        case Type::CONVOLVER: {
            std::shared_ptr<dsp::Convolver> convolver = std::make_shared<dsp::Convolver>();
            Node node(data, id, type, position, convolver);
            node.addInput(++counter, "Input", convolver->getInput());
            node.addOutput(++counter, "Output", convolver->getOutput());
            return node;
        }
        case Type::VARIABLE_DELAY: {
            // TODO: implement feedback interface
            std::shared_ptr<dsp::VariableDelay> variableDelay = std::make_shared<dsp::VariableDelay>();
            Node node(data, id, type, position, variableDelay);
            node.addInput(++counter, "Input", variableDelay->getInput());
            node.addInput(++counter, "Delay Time", variableDelay->getDelayTime());
            node.addInput(++counter, "Decay Time", variableDelay->getDecayTime());
            node.addInput(++counter, "Reset", variableDelay->getReset());
            node.addOutput(++counter, "Output", variableDelay->getOutput());
            return node;
        }
        case Type::CLIPPER: {
            std::shared_ptr<dsp::Clipper> clipper = std::make_shared<dsp::Clipper>();
            Node node(data, id, type, position, clipper);
            node.addInput(++counter, "Input", clipper->getInput());
            node.addInput(++counter, "Minimum", clipper->getMinimum());
            node.addInput(++counter, "Maximum", clipper->getMaximum());
            node.addInput(++counter, "Mode", clipper->getMode());
            node.addOutput(++counter, "Output", clipper->getOutput());
            return node;
        }
        case Type::COMPRESSOR_GATE: {
            std::shared_ptr<dsp::CompressorGate> compressorGate = std::make_shared<dsp::CompressorGate>();
            Node node(data, id, type, position, compressorGate);
            node.addInput(++counter, "Input", compressorGate->getInput());
            node.addInput(++counter, "Control", compressorGate->getControl());
            node.addInput(++counter, "Threshold", compressorGate->getThreshold());
            node.addInput(++counter, "Hardness", compressorGate->getHardness());
            node.addInput(++counter, "Compression Ratio", compressorGate->getCompressionRatio());
            node.addInput(++counter, "Gate Ratio", compressorGate->getGateRatio());
            node.addInput(++counter, "Attack", compressorGate->getAttack());
            node.addInput(++counter, "Release", compressorGate->getRelease());
            node.addOutput(++counter, "Output", compressorGate->getOutput());
            node.addOutput(++counter, "Gain", compressorGate->getGain());
            return node;
        }
        case Type::CROSSFADER: {
            std::shared_ptr<dsp::Crossfader> crossfader = std::make_shared<dsp::Crossfader>();
            Node node(data, id, type, position, crossfader);
            node.addInput(++counter, "Input", crossfader->getInput());
            node.addInput(++counter, "Position", crossfader->getPosition());
            node.addOutput(++counter, "A", crossfader->getA());
            node.addOutput(++counter, "B", crossfader->getB());
            return node;
        }
        case Type::ENVELOPE: {
            std::shared_ptr<dsp::Envelope> envelope = std::make_shared<dsp::Envelope>();
            Node node(data, id, type, position, envelope);
            node.addInput(++counter, "Attack", envelope->getAttack());
            node.addInput(++counter, "Release", envelope->getRelease());
            node.addInput(++counter, "Attack Shape", envelope->getAttackShape());
            node.addInput(++counter, "Release Shape", envelope->getReleaseShape());
            node.addInput(++counter, "Gate", envelope->getGate());
            node.addInput(++counter, "Reset", envelope->getReset());
            node.addOutput(++counter, "Output", envelope->getOutput());
            return node;
        }
        case Type::LAG: {
            std::shared_ptr<dsp::Lag> lag = std::make_shared<dsp::Lag>();
            Node node(data, id, type, position, lag);
            node.addInput(++counter, "Input", lag->getInput());
            node.addInput(++counter, "Lag Time", lag->getLagTime());
            node.addOutput(++counter, "Output", lag->getOutput());
            return node;
        }
        case Type::SHAPER: {
            std::shared_ptr<dsp::Shaper> shaper = std::make_shared<dsp::Shaper>();
            Node node(data, id, type, position, shaper);
            node.addInput(++counter, "Input", shaper->getInput());
            node.addInput(++counter, "Drive", shaper->getDrive());
            node.addInput(++counter, "Mode", shaper->getMode());
            node.addOutput(++counter, "Output", shaper->getOutput());
            return node;
        }
        case Type::AUDIO_INPUT: {
            Node node(data, id, type, position, nullptr);
            node.addOutput(++counter, "Output", data->getNodeProcessor()->getAudioInput());
            return node;
        }
        case Type::AUDIO_INPUT_CLIPPING: {
            Node node(data, id, type, position, nullptr);
            node.addOutput(++counter, "Output", data->getNodeProcessor()->getAudioInputClipping());
            return node;
        }
        case Type::AUDIO_OUTPUT: {
            Node node(data, id, type, position, nullptr);
            node.addInput(++counter, "Input", data->getNodeProcessor()->getAudioOutput());
            return node;
        }
        case Type::AUDIO_OUTPUT_CLIPPING: {
            Node node(data, id, type, position, nullptr);
            node.addOutput(++counter, "Output", data->getNodeProcessor()->getAudioOutputClipping());
            return node;
        }
        case Type::MIDI_INPUT: {
            std::shared_ptr<dsp::MidiInput> midiInput =
                    std::make_shared<dsp::MidiInput>(data->getNodeProcessor()->getInputMessages());
            Node node(data, id, type, position, midiInput);
            node.addOutput(++counter, "Output", midiInput->getOutput());
            return node;
        }
        case Type::MIDI_OUTPUT: {
            std::shared_ptr<dsp::MidiOutput> midiOutput =
                    std::make_shared<dsp::MidiOutput>(data->getNodeProcessor()->getOutputMessages());
            Node node(data, id, type, position, midiOutput);
            node.addInput(++counter, "Input", midiOutput->getInput());
            return node;
        }
        case Type::BIQUAD: {
            std::shared_ptr<dsp::Biquad> biquad = std::make_shared<dsp::Biquad>();
            Node node(data, id, type, position, biquad);
            node.addInput(++counter, "Input", biquad->getInput());
            node.addInput(++counter, "Frequency", biquad->getFrequency());
            node.addInput(++counter, "Resonance", biquad->getResonance());
            node.addInput(++counter, "Amplitude", biquad->getAmplitude());
            node.addInput(++counter, "Mode", biquad->getMode());
            node.addOutput(++counter, "Output", biquad->getOutput());
            return node;
        }
        case Type::CROSSOVER: {
            std::shared_ptr<dsp::Crossover> crossover = std::make_shared<dsp::Crossover>();
            Node node(data, id, type, position, crossover);
            node.addInput(++counter, "Input", crossover->getInput());
            node.addInput(++counter, "Frequency", crossover->getFrequency());
            node.addOutput(++counter, "Low", crossover->getLow());
            node.addOutput(++counter, "High", crossover->getHigh());
            return node;
        }
        case Type::ONE_POLE: {
            std::shared_ptr<dsp::OnePole> onePole = std::make_shared<dsp::OnePole>();
            Node node(data, id, type, position, onePole);
            node.addInput(++counter, "Input", onePole->getInput());
            node.addInput(++counter, "Frequency", onePole->getFrequency());
            node.addInput(++counter, "Mode", onePole->getMode());
            node.addOutput(++counter, "Output", onePole->getOutput());
            return node;
        }
        case Type::MOORER_DSF: {
            std::shared_ptr<dsp::MoorerOscillator> moorer = std::make_shared<dsp::MoorerOscillator>();
            Node node(data, id, type, position, moorer);
            node.addInput(++counter, "Phase", moorer->getPhase());
            node.addInput(++counter, "Intensity", moorer->getIntensity());
            node.addInput(++counter, "Modulation Index", moorer->getModulationIndex());
            node.addInput(++counter, "Harmonics", moorer->getHarmonics());
            node.addInput(++counter, "Mode", moorer->getMode());
            node.addOutput(++counter, "Output", moorer->getOutput());
            return node;
        }
        case Type::NOISE: {
            std::shared_ptr<dsp::Noise> noise = std::make_shared<dsp::Noise>();
            Node node(data, id, type, position, noise);
            node.addInput(++counter, "Mode", noise->getMode());
            node.addOutput(++counter, "Output", noise->getOutput());
            return node;
        }
        case Type::PHASOR: {
            std::shared_ptr<dsp::Phasor> phasor = std::make_shared<dsp::Phasor>();
            Node node(data, id, type, position, phasor);
            node.addInput(++counter, "Frequency", phasor->getFrequency());
            node.addInput(++counter, "Mode", phasor->getMode());
            node.addInput(++counter, "Reset", phasor->getReset());
            node.addOutput(++counter, "Output", phasor->getOutput());
            return node;
        }
        case Type::SAMPLE_PLAYER: {
            std::shared_ptr<dsp::SamplePlayer> samplePlayer = std::make_shared<dsp::SamplePlayer>();
            Node node(data, id, type, position, samplePlayer);
            node.addInput(++counter, "Speed", samplePlayer->getSpeed());
            node.addInput(++counter, "Start Time", samplePlayer->getStartTime());
            node.addInput(++counter, "Sample Index", samplePlayer->getSampleIndex());
            node.addInput(++counter, "Interpolation", samplePlayer->getInterpolation());
            node.addInput(++counter, "Gate", samplePlayer->getGate());
            node.addInput(++counter, "Reset", samplePlayer->getReset());
            node.addOutput(++counter, "Output", samplePlayer->getOutput());
            node.addOutput(++counter, "Current Time", samplePlayer->getCurrentTime());
            return node;
        }
        case Type::TABLE_OSCILLATOR: {
            std::shared_ptr<dsp::TableOscillator> oscillator = std::make_shared<dsp::TableOscillator>();
            Node node(data, id, type, position, oscillator);
            node.addInput(++counter, "Phase", oscillator->getPhase());
            node.addInput(++counter, "Position", oscillator->getPosition());
            node.addInput(++counter, "Phase Interpolation", oscillator->getPhaseInterpolation());
            node.addInput(++counter, "Position Interpolation", oscillator->getPositionInterpolation());
            node.addOutput(++counter, "Output", oscillator->getOutput());
            return node;
        }
        case Type::ABSOLUTE_VALUE: {
            std::shared_ptr<dsp::AbsoluteValue> absoluteValue = std::make_shared<dsp::AbsoluteValue>();
            Node node(data, id, type, position, absoluteValue);
            node.addInput(++counter, "Input", absoluteValue->getInput());
            node.addOutput(++counter, "Output", absoluteValue->getOutput());
            return node;
        }
        case Type::BOOLEAN_MASK: {
            std::shared_ptr<dsp::BooleanMask> booleanMask = std::make_shared<dsp::BooleanMask>();
            Node node(data, id, type, position, booleanMask);
            node.addInput(++counter, "Input", booleanMask->getInput());
            node.addInput(++counter, "Mask", booleanMask->getMask());
            node.addOutput(++counter, "Output", booleanMask->getOutput());
            return node;
        }
        case Type::COMPARISON: {
            std::shared_ptr<dsp::Comparison> comparison = std::make_shared<dsp::Comparison>();
            Node node(data, id, type, position, comparison);
            node.addInput(++counter, "Input", comparison->getInput());
            node.addInput(++counter, "Threshold", comparison->getThreshold());
            node.addOutput(++counter, "Output", comparison->getOutput());
            return node;
        }
        case Type::DIVISION: {
            std::shared_ptr<dsp::Division> division = std::make_shared<dsp::Division>();
            Node node(data, id, type, position, division);
            node.addInput(++counter, "Input", division->getInput());
            node.addInput(++counter, "Divisor", division->getDivisor());
            node.addOutput(++counter, "Output", division->getOutput());
            return node;
        }
        case Type::FLOOR: {
            std::shared_ptr<dsp::Floor> floor = std::make_shared<dsp::Floor>();
            Node node(data, id, type, position, floor);
            node.addInput(++counter, "Input", floor->getInput());
            node.addInput(++counter, "Divisor", floor->getDivisor());
            node.addOutput(++counter, "Output", floor->getOutput());
            return node;
        }
        case Type::FORWARD_FFT: {
            std::shared_ptr<dsp::ForwardFFT> forwardFFT = std::make_shared<dsp::ForwardFFT>();
            Node node(data, id, type, position, forwardFFT);
            node.addInput(++counter, "Input", forwardFFT->getInput());
            node.addOutput(++counter, "Magnitude", forwardFFT->getMagnitude());
            node.addOutput(++counter, "Phase", forwardFFT->getPhase());
            return node;
        }
        case Type::FREQUENCY_TO_NOTE: {
            std::shared_ptr<dsp::FrequencyToNote> toNote = std::make_shared<dsp::FrequencyToNote>();
            Node node(data, id, type, position, toNote);
            node.addInput(++counter, "Frequency", toNote->getInput());
            node.addInput(++counter, "Tuning Frequency", toNote->getTuningFrequency());
            node.addOutput(++counter, "Note", toNote->getOutput());
            return node;
        }
        case Type::HYPERBOLIC: {
            std::shared_ptr<dsp::Hyperbolic> hyperbolic = std::make_shared<dsp::Hyperbolic>();
            Node node(data, id, type, position, hyperbolic);
            node.addInput(++counter, "Input", hyperbolic->getInput());
            node.addInput(++counter, "Mode", hyperbolic->getMode());
            node.addOutput(++counter, "Output", hyperbolic->getOutput());
            return node;
        }
        case Type::INVERSE_FFT: {
            std::shared_ptr<dsp::InverseFFT> inverseFFT = std::make_shared<dsp::InverseFFT>();
            Node node(data, id, type, position, inverseFFT);
            node.addInput(++counter, "Magnitude", inverseFFT->getMagnitude());
            node.addInput(++counter, "Phase", inverseFFT->getPhase());
            node.addOutput(++counter, "Output", inverseFFT->getOutput());
            return node;
        }
        case Type::LOGARITHM: {
            std::shared_ptr<dsp::Logarithm> logarithm = std::make_shared<dsp::Logarithm>();
            Node node(data, id, type, position, logarithm);
            node.addInput(++counter, "Input", logarithm->getInput());
            node.addInput(++counter, "Base", logarithm->getBase());
            node.addOutput(++counter, "Exponent", logarithm->getOutput());
            return node;
        }
        case Type::MODULO: {
            std::shared_ptr<dsp::Modulo> modulo = std::make_shared<dsp::Modulo>();
            Node node(data, id, type, position, modulo);
            node.addInput(++counter, "Input", modulo->getInput());
            node.addInput(++counter, "Divisor", modulo->getDivisor());
            node.addOutput(++counter, "Output", modulo->getOutput());
            return node;
        }
        case Type::MULTIPLICATION: {
            std::shared_ptr<dsp::Multiplication> multiplication = std::make_shared<dsp::Multiplication>();
            Node node(data, id, type, position, multiplication);
            node.addInput(++counter, "Input", multiplication->getInput());
            node.addInput(++counter, "Factor", multiplication->getFactor());
            node.addOutput(++counter, "Output", multiplication->getOutput());
            return node;
        }
        case Type::NEGATIVE: {
            std::shared_ptr<dsp::Negative> negative = std::make_shared<dsp::Negative>();
            Node node(data, id, type, position, negative);
            node.addInput(++counter, "Input", negative->getInput());
            node.addOutput(++counter, "Output", negative->getOutput());
            return node;
        }
        case Type::NOTE_TO_FREQUENCY: {
            std::shared_ptr<dsp::NoteToFrequency> toFrequency = std::make_shared<dsp::NoteToFrequency>();
            Node node(data, id, type, position, toFrequency);
            node.addInput(++counter, "Note", toFrequency->getInput());
            node.addInput(++counter, "Tuning Frequency", toFrequency->getTuningFrequency());
            node.addOutput(++counter, "Frequency", toFrequency->getOutput());
            return node;
        }
        case Type::NOT_GATE: {
            std::shared_ptr<dsp::NotGate> notGate = std::make_shared<dsp::NotGate>();
            Node node(data, id, type, position, notGate);
            node.addInput(++counter, "Input", notGate->getInput());
            node.addOutput(++counter, "Output", notGate->getOutput());
            return node;
        }
        case Type::POWER: {
            std::shared_ptr<dsp::Power> power = std::make_shared<dsp::Power>();
            Node node(data, id, type, position, power);
            node.addInput(++counter, "Base", power->getInput());
            node.addInput(++counter, "Exponent", power->getExponent());
            node.addOutput(++counter, "Output", power->getOutput());
            return node;
        }
        case Type::RECIPROCAL: {
            std::shared_ptr<dsp::Reciprocal> reciprocal = std::make_shared<dsp::Reciprocal>();
            Node node(data, id, type, position, reciprocal);
            node.addInput(++counter, "Input", reciprocal->getInput());
            node.addOutput(++counter, "Output", reciprocal->getOutput());
            return node;
        }
        case Type::TRIGONOMETRIC: {
            std::shared_ptr<dsp::Trigonometric> trigonometric = std::make_shared<dsp::Trigonometric>();
            Node node(data, id, type, position, trigonometric);
            node.addInput(++counter, "Input", trigonometric->getInput());
            node.addInput(++counter, "Mode", trigonometric->getMode());
            node.addOutput(++counter, "Output", trigonometric->getOutput());
            return node;
        }
        case Type::BEAT_DURATION: {
            std::shared_ptr<dsp::BeatDuration> beatDuration =
                    std::make_shared<dsp::BeatDuration>(data->getAudioProcessor());
            Node node(data, id, type, position, beatDuration);
            node.addOutput(++counter, "Output", beatDuration->getOutput());
            return node;
        }
        case Type::BEAT_RATE: {
            std::shared_ptr<dsp::BeatRate> beatRate = std::make_shared<dsp::BeatRate>(data->getAudioProcessor());
            Node node(data, id, type, position, beatRate);
            node.addOutput(++counter, "Output", beatRate->getOutput());
            return node;
        }
        case Type::TIME_SIGNATURE: {
            std::shared_ptr<dsp::TimeSignature> timeSignature =
                    std::make_shared<dsp::TimeSignature>(data->getAudioProcessor());
            Node node(data, id, type, position, timeSignature);
            node.addOutput(++counter, "Numerator", timeSignature->getNumerator());
            node.addOutput(++counter, "Denominator", timeSignature->getDenominator());
            return node;
        }
        case Type::TRANSPORT_STATE: {
            std::shared_ptr<dsp::TransportState> transportState =
                    std::make_shared<dsp::TransportState>(data->getAudioProcessor());
            Node node(data, id, type, position, transportState);
            node.addOutput(++counter, "Time Elapsed", transportState->getTimeElapsed());
            node.addOutput(++counter, "Is Playing", transportState->isPlaying());
            node.addOutput(++counter, "Is Recording", transportState->isRecording());
            return node;
        }
        case Type::CLOCK_TRIGGER: {
            std::shared_ptr<dsp::ClockTrigger> clockTrigger = std::make_shared<dsp::ClockTrigger>();
            Node node(data, id, type, position, clockTrigger);
            node.addInput(++counter, "Interval", clockTrigger->getInterval());
            node.addInput(++counter, "Delay Time", clockTrigger->getDelayTime());
            node.addInput(++counter, "Reset", clockTrigger->getReset());
            node.addOutput(++counter, "Output", clockTrigger->getOutput());
            node.addOutput(++counter, "Current Time", clockTrigger->getCurrentTime());
            return node;
        }
        case Type::DIFFERENTIATOR: {
            std::shared_ptr<dsp::Differentiator> differentiator = std::make_shared<dsp::Differentiator>();
            Node node(data, id, type, position, differentiator);
            node.addInput(++counter, "Input", differentiator->getInput());
            node.addInput(++counter, "Gate", differentiator->getGate());
            node.addInput(++counter, "Reset", differentiator->getReset());
            node.addOutput(++counter, "Output", differentiator->getOutput());
            return node;
        }
        case Type::INTEGRATOR: {
            std::shared_ptr<dsp::Integrator> integrator = std::make_shared<dsp::Integrator>();
            Node node(data, id, type, position, integrator);
            node.addInput(++counter, "Input", integrator->getInput());
            node.addInput(++counter, "Gate", integrator->getGate());
            node.addInput(++counter, "Reset", integrator->getReset());
            node.addOutput(++counter, "Output", integrator->getOutput());
            return node;
        }
        case Type::ON_OFF: {
            std::shared_ptr<dsp::OnOff> onOff = std::make_shared<dsp::OnOff>();
            Node node(data, id, type, position, onOff);
            node.addInput(++counter, "On", onOff->getOnTrigger());
            node.addInput(++counter, "Off", onOff->getOffTrigger());
            node.addOutput(++counter, "Output", onOff->getOutput());
            return node;
        }
        case Type::RESET_TRIGGER: {
            std::shared_ptr<dsp::ResetTrigger> resetTrigger = std::make_shared<dsp::ResetTrigger>();
            Node node(data, id, type, position, resetTrigger);
            node.addOutput(++counter, "Output", resetTrigger->getOutput());
            return node;
        }
        case Type::SAMPLE_AND_HOLD: {
            std::shared_ptr<dsp::SampleAndHold> sampleAndHold = std::make_shared<dsp::SampleAndHold>();
            Node node(data, id, type, position, sampleAndHold);
            node.addInput(++counter, "Input", sampleAndHold->getInput());
            node.addInput(++counter, "Gate", sampleAndHold->getGate());
            node.addInput(++counter, "Reset", sampleAndHold->getReset());
            node.addOutput(++counter, "Output", sampleAndHold->getOutput());
            return node;
        }
        case Type::SEQUENCER: {
            std::shared_ptr<dsp::Sequencer> sequencer = std::make_shared<dsp::Sequencer>();
            Node node(data, id, type, position, sequencer);
            node.addInput(++counter, "Sequence Index", sequencer->getSequenceIndex());
            node.addInput(++counter, "Position Index", sequencer->getPositionIndex());
            node.addOutput(++counter, "Output", sequencer->getOutput());
            return node;
        }
        case Type::TRIGGER_HOLD: {
            std::shared_ptr<dsp::TriggerHold> triggerHold = std::make_shared<dsp::TriggerHold>();
            Node node(data, id, type, position, triggerHold);
            node.addInput(++counter, "Input", triggerHold->getInput());
            node.addInput(++counter, "Hold Time", triggerHold->getHoldTime());
            node.addOutput(++counter, "Output", triggerHold->getOutput());
            return node;
        }
        case Type::BUFFER_DURATION: {
            std::shared_ptr<dsp::BufferDuration> bufferDuration = std::make_shared<dsp::BufferDuration>();
            Node node(data, id, type, position, bufferDuration);
            node.addOutput(++counter, "Output", bufferDuration->getOutput());
            return node;
        }
        case Type::BUFFER_RATE: {
            std::shared_ptr<dsp::BufferRate> bufferRate = std::make_shared<dsp::BufferRate>();
            Node node(data, id, type, position, bufferRate);
            node.addOutput(++counter, "Output", bufferRate->getOutput());
            return node;
        }
        case Type::EULER: {
            std::shared_ptr<dsp::Variable> variable = std::make_shared<dsp::Variable>(dsp::E);
            Node node(data, id, type, position, variable);
            node.addOutput(++counter, "Output", variable->getOutput());
            return node;
        }
        case Type::INF: {
            std::shared_ptr<dsp::Infinity> infinity = std::make_shared<dsp::Infinity>();
            Node node(data, id, type, position, infinity);
            node.addInput(++counter, "Mode", infinity->getMode());
            node.addOutput(++counter, "Output", infinity->getOutput());
            return node;
        }
        case Type::PHI: {
            std::shared_ptr<dsp::Variable> variable = std::make_shared<dsp::Variable>(dsp::PHI);
            Node node(data, id, type, position, variable);
            node.addOutput(++counter, "Output", variable->getOutput());
            return node;
        }
        case Type::PI: {
            std::shared_ptr<dsp::Variable> variable = std::make_shared<dsp::Variable>(dsp::PI);
            Node node(data, id, type, position, variable);
            node.addOutput(++counter, "Output", variable->getOutput());
            return node;
        }
        case Type::SAMPLE_DURATION: {
            std::shared_ptr<dsp::SampleDuration> sampleDuration = std::make_shared<dsp::SampleDuration>();
            Node node(data, id, type, position, sampleDuration);
            node.addOutput(++counter, "Output", sampleDuration->getOutput());
            return node;
        }
        case Type::SAMPLE_RATE: {
            std::shared_ptr<dsp::SampleRate> sampleRate = std::make_shared<dsp::SampleRate>();
            Node node(data, id, type, position, sampleRate);
            node.addOutput(++counter, "Output", sampleRate->getOutput());
            return node;
        }
        case Type::TAU: {
            std::shared_ptr<dsp::Variable> variable = std::make_shared<dsp::Variable>(dsp::TAU);
            Node node(data, id, type, position, variable);
            node.addOutput(++counter, "Output", variable->getOutput());
            return node;
        }
        case Type::VARIABLE: {
            std::shared_ptr<dsp::Identity> identity = std::make_shared<dsp::Identity>();
            Node node(data, id, type, position, identity);
            node.addInput(++counter, "Input", identity->getInput());
            node.addOutput(++counter, "Output", identity->getOutput());
            return node;
        }
    }
}

particle::NodeGraph::Link::Link(
        Data *data, int id, int from, int to, std::shared_ptr<dsp::Output> output, std::shared_ptr<dsp::Input> input)
        : data(data)
        , id(id)
        , from(from)
        , to(to)
        , output(output)
        , input(input) {}

void particle::NodeGraph::Link::draw() {
    imnodes::Link(id, from, to);
}

void particle::NodeGraph::Link::drawInspector() {}

particle::NodeGraph::Link
particle::NodeGraph::Link::generate(Data *data, std::map<int, Node> &nodes, int id, int from, int to) {
    std::shared_ptr<dsp::Output> output;
    std::shared_ptr<dsp::Input> input;
    for (const auto &nodePair : nodes) {
        std::map<int, Input>::const_iterator inputIterator;
        if ((inputIterator = nodePair.second.inputs.find(from)) != nodePair.second.inputs.end()) {
            input = inputIterator->second.input;
            break;
        }
        std::map<int, Output>::const_iterator outputIterator;
        if ((outputIterator = nodePair.second.outputs.find(from)) != nodePair.second.outputs.end()) {
            output = outputIterator->second.output;
            break;
        }
    }
    for (const auto &nodePair : nodes) {
        std::map<int, Input>::const_iterator inputIterator;
        if ((inputIterator = nodePair.second.inputs.find(to)) != nodePair.second.inputs.end()) {
            input = inputIterator->second.input;
            break;
        }
        std::map<int, Output>::const_iterator outputIterator;
        if ((outputIterator = nodePair.second.outputs.find(to)) != nodePair.second.outputs.end()) {
            output = outputIterator->second.output;
            break;
        }
    }
    return Link(data, id, from, to, output, input);
}

particle::NodeGraph::CreateNodes::CreateNodes(std::shared_ptr<NodeGraph> nodeGraph, std::vector<Node> nodes)
        : Action(nodes.size() == 1 ? "Create Node" : "Create Nodes")
        , nodeGraph(nodeGraph)
        , nodes(nodes) {}

void particle::NodeGraph::CreateNodes::perform() {
    for (const auto &node : nodes) {
        // GUI
        nodeGraph->getNodes().emplace(node.id, node);
        imnodes::SetNodeGridSpacePos(node.id, node.position);
        // DSP
        if (node.node != nullptr) {

            // TODO: TEMPORARY! REMOVE!
            node.node->setNumChannels(2);

            nodeGraph->getContainer()->addChild(node.node);
        }
    }
}

void particle::NodeGraph::CreateNodes::undo() {
    for (const auto &node : nodes) {
        // DSP
        if (node.node != nullptr) {
            nodeGraph->getContainer()->removeChild(node.node);
        }
        // GUI
        nodeGraph->getNodes().erase(node.id);
    }
}

particle::NodeGraph::CreateLinks::CreateLinks(std::shared_ptr<NodeGraph> nodeGraph, std::vector<Link> links)
        : Action(links.size() == 1 ? "Create Link" : "Create Links")
        , nodeGraph(nodeGraph)
        , links(links) {}

void particle::NodeGraph::CreateLinks::perform() {
    for (const auto &link : links) {
        // GUI
        nodeGraph->getLinks().emplace(link.id, link);
        // DSP
        link.output->connect(link.input);
    }
    nodeGraph->getContainer()->sortChildren();
}

void particle::NodeGraph::CreateLinks::undo() {
    for (const auto &link : links) {
        // DSP
        link.output->disconnect(link.input);
        // GUI
        nodeGraph->getLinks().erase(link.id);
    }
}

particle::NodeGraph::DestroyNodes::DestroyNodes(std::shared_ptr<NodeGraph> nodeGraph, std::vector<int> ids)
        : Action(ids.size() == 1 ? "Destroy Node" : "Destroy Nodes")
        , nodeGraph(nodeGraph)
        , ids(ids) {}

void particle::NodeGraph::DestroyNodes::perform() {
    for (const auto& nodeId : ids) {
        Node& node = nodeGraph->getNodes()[nodeId];
        std::vector<int> attachedLinks;
        for (const auto& inputPair : node.inputs) {
            for (const auto& linkPair : nodeGraph->getLinks()) {
                if (inputPair.first == linkPair.second.to) {
                    attachedLinks.push_back(linkPair.first);
                }
            }
        }
        for (const auto& outputPair : node.outputs) {
            for (const auto& linkPair : nodeGraph->getLinks()) {
                if (outputPair.first == linkPair.second.from) {
                    attachedLinks.push_back(linkPair.first);
                }
            }
        }
        for (const auto& linkId : attachedLinks) {
            Link& link = nodeGraph->getLinks()[linkId];
            // DSP
            link.output->disconnect(link.input);
            // LOCAL
            links.push_front(link);
            // GUI
            nodeGraph->getLinks().erase(link.id);
        }
        // DSP
        if (node.node != nullptr) {
            nodeGraph->getContainer()->removeChild(node.node);
        }
        // LOCAL
        node.position = imnodes::GetNodeGridSpacePos(node.id);
        nodes.push_front(node);
        // GUI
        nodeGraph->getNodes().erase(node.id);
    }
}

void particle::NodeGraph::DestroyNodes::undo() {
    for (const auto& node : nodes) {
        // GUI
        nodeGraph->getNodes().emplace(node.id, node);
        imnodes::SetNodeGridSpacePos(node.id, node.position);
        // DSP
        if (node.node != nullptr) {
            nodeGraph->getContainer()->addChild(node.node);
        }
    }
    for (const auto& link : links) {
        // GUI
        nodeGraph->getLinks().emplace(link.id, link);
        // DSP
        link.output->connect(link.input);
    }
    // LOCAL
    nodes.clear();
    links.clear();
    // DSP
    nodeGraph->getContainer()->sortChildren();
}

particle::NodeGraph::DestroyLinks::DestroyLinks(std::shared_ptr<NodeGraph> nodeGraph, std::vector<int> ids)
        : Action(ids.size() == 1 ? "Destroy Link" : "Destroy Links")
        , nodeGraph(nodeGraph)
        , ids(ids) {}

void particle::NodeGraph::DestroyLinks::perform() {
    for (const auto& linkId : ids) {
        Link &link = nodeGraph->getLinks()[linkId];
        // DSP
        link.output->disconnect(link.input);
        // LOCAL
        links.push_front(nodeGraph->getLinks()[linkId]);
        // GUI
        nodeGraph->getLinks().erase(linkId);
    }
}

void particle::NodeGraph::DestroyLinks::undo() {
    for (const auto &link : links) {
        // GUI
        nodeGraph->getLinks().emplace(link.id, link);
        // DSP
        link.output->connect(link.input);
    }
    // LOCAL
    links.clear();
    // DSP
    nodeGraph->getContainer()->sortChildren();
}

particle::NodeGraph::NodeGraph(Data &data, std::string name, std::shared_ptr<dsp::Node> container)
        : Frame(data, name)
        , counter(0)
        , container(container) {
    context = imnodes::EditorContextCreate();
}

particle::NodeGraph::~NodeGraph() {
    imnodes::EditorContextFree(context);
}

std::shared_ptr<dsp::Node> particle::NodeGraph::getContainer() {
    return container;
}

std::map<int, particle::NodeGraph::Node> &particle::NodeGraph::getNodes() {
    return nodes;
}

std::map<int, particle::NodeGraph::Link> &particle::NodeGraph::getLinks() {
    return links;
}

imnodes::EditorContext *particle::NodeGraph::getContext() const {
    return context;
}

void particle::NodeGraph::drawInternal() {
    ImGuiIO &io = ImGui::GetIO();
    imnodes::EditorContextSet(context);
    ImVec2 panning = imnodes::EditorContextGetPanning();
    {
        float speed = io.KeyAlt ? 1.0f : io.KeyShift ? 100.0f : 10.0f;
        int x = ImGui::IsKeyDown(io.KeyMap[ImGuiKey_LeftArrow]) - ImGui::IsKeyDown(io.KeyMap[ImGuiKey_RightArrow]);
        int y = ImGui::IsKeyDown(io.KeyMap[ImGuiKey_UpArrow]) - ImGui::IsKeyDown(io.KeyMap[ImGuiKey_DownArrow]);
        panning.x += speed * x;
        panning.y += speed * y;
        imnodes::EditorContextResetPanning(panning);
    }
    if (!ImGui::IsAnyItemActive() && ImGui::IsKeyPressed(io.KeyMap[ImGuiKey_Backspace])) {
        destroyNodes();
        destroyLinks();
    }
    std::set<int> selectedNodeSet;
    for (const int node_id : getSelectedNodes()) {
        selectedNodeSet.insert(node_id);
    }
    imnodes::BeginNodeEditor();
    ImGui::Text("(%.0f, %.0f)", panning.x, panning.y);
    createNode();
    for (auto &nodePair : nodes) {
        nodePair.second.draw(selectedNodeSet.find(nodePair.first) != selectedNodeSet.end());
    }
    for (auto &linkPair : links) {
        linkPair.second.draw();
    }
    imnodes::EndNodeEditor();
    createLink();
}

void particle::NodeGraph::destroyNodes() {
    std::vector<int> selectedNodes = getSelectedNodes();
    if (!selectedNodes.empty()) {
        getData().pushAction(std::make_shared<DestroyNodes>(shared_from_this(), selectedNodes));
    }
}

void particle::NodeGraph::destroyLinks() {
    std::vector<int> selectedLinks = getSelectedLinks();
    if (!selectedLinks.empty()) {
        getData().pushAction(std::make_shared<DestroyLinks>(shared_from_this(), selectedLinks));
    }
}

void particle::NodeGraph::createNode() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, getData().getStyle().windowPadding);
    if (!ImGui::IsAnyItemHovered() && imnodes::IsEditorHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
        ImGui::OpenPopup("Create Node");
    }
    if (ImGui::BeginPopup("Create Node")) {
        const ImVec2 mousePosition = ImGui::GetMousePosOnOpeningCurrentPopup();
        for (const auto &category : Node::getCategories(getData().getAudioProcessor()->getPlayHead() != nullptr)) {
            if (ImGui::BeginMenu(category.getName().c_str())) {
                for (const auto &type : category.types) {
                    if (ImGui::MenuItem(Node::getTypeName(type).c_str())) {
                        std::vector<Node> nodes;
                        // TODO: remove for loop here
                        for (int i = 0; i < 1; ++i) {
                            const int id = ++counter;
                            imnodes::SetNodeScreenSpacePos(id, mousePosition);
                            nodes.push_back(Node::generate(&getData(), counter, id, type, imnodes::GetNodeGridSpacePos(id)));
                        }
                        getData().pushAction(std::make_shared<CreateNodes>(shared_from_this(), nodes));
                    }
                }
                ImGui::EndMenu();
            }
        }
        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();
}

void particle::NodeGraph::createLink() {
    int from;
    int to;
    if (imnodes::IsLinkCreated(&from, &to)) {
        const int id = ++counter;
        Link link = Link::generate(&getData(), nodes, id, from, to);
        getData().pushAction(std::make_shared<CreateLinks>(shared_from_this(), std::vector<Link>{link}));
    }
}

std::vector<int> particle::NodeGraph::getSelectedNodes() {
    std::vector<int> selectedNodes;
    int numSelectedNodes = imnodes::NumSelectedNodes();
    if (numSelectedNodes) {
        selectedNodes.resize(numSelectedNodes);
        imnodes::GetSelectedNodes(selectedNodes.data());
        selectedNodes.erase(std::remove_if(selectedNodes.begin(),
                                           selectedNodes.end(),
                                           [this](int nodeId) { return nodes.find(nodeId) == nodes.end(); }),
                            selectedNodes.end());
    }
    return selectedNodes;
}

std::vector<int> particle::NodeGraph::getSelectedLinks() {
    std::vector<int> selectedLinks;
    int numSelectedLinks = imnodes::NumSelectedLinks();
    if (numSelectedLinks) {
        selectedLinks.resize(numSelectedLinks);
        imnodes::GetSelectedLinks(selectedLinks.data());
        selectedLinks.erase(std::remove_if(selectedLinks.begin(),
                                           selectedLinks.end(),
                                           [this](int linkId) { return links.find(linkId) == links.end(); }),
                            selectedLinks.end());
    }
    return selectedLinks;
}
