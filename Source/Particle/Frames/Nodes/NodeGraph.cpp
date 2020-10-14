#include "NodeGraph.h"

particle::NodeGraph::Input::Input(int id, std::string name, std::shared_ptr<dsp::Input> input)
        : id(id)
        , name(name)
        , input(input) {}

void particle::NodeGraph::Input::draw() {
    imnodes::BeginInputAttribute(id);
    ImGui::Text("%s", name.c_str());
    imnodes::EndInputAttribute();
}

void particle::NodeGraph::Input::drawInspector() {}

particle::NodeGraph::Output::Output(int id, std::string name, std::shared_ptr<dsp::Output> output)
        : id(id)
        , name(name)
        , output(output) {}

void particle::NodeGraph::Output::draw() {
    imnodes::BeginOutputAttribute(id);
    ImGui::Text("%s", name.c_str());
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

void particle::NodeGraph::Node::addInput(int id, std::string name, std::shared_ptr<dsp::Input> input) {
    inputs.emplace(id, Input(id, name, input));
}

void particle::NodeGraph::Node::addOutput(int id, std::string name, std::shared_ptr<dsp::Output> output) {
    outputs.emplace(id, Output(id, name, output));
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
    ImGui::Text("%s", getTypeName(type, customName).c_str());
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
    categories.push_back(Category(
            "Generators",
            std::vector<Type>{
                    Type::MOORER_DSF, Type::NOISE, Type::PHASOR, Type::SAMPLE_PLAYER, Type::TABLE_OSCILLATOR}));
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
                                          Type::MULTIPLY_FREQUENCY_TIME,
                                          Type::NOTE_TO_FREQUENCY,
                                          Type::NOT_GATE,
                                          Type::RECIPROCAL,
                                  }));
    categories.push_back(Category("Trigger",
                                  std::vector<Type>{Type::CLOCK_TRIGGER,
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
        case Type::MOORER_DSF: return "Moorer DSF";
        case Type::NOISE: return "Noise";
        case Type::PHASOR: return "Phasor";
        case Type::SAMPLE_PLAYER: return "Sample Player";
        case Type::TABLE_OSCILLATOR: return "Table Oscillator";
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
        case Type::MULTIPLY_FREQUENCY_TIME: return "Multiply Frequency/Time";
        case Type::NOTE_TO_FREQUENCY: return "Note to Frequency";
        case Type::NOT_GATE: return "Not Gate";
        case Type::RECIPROCAL: return "Reciprocal";
        case Type::CLOCK_TRIGGER: return "Clock Trigger";
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

particle::NodeGraph::Node particle::NodeGraph::Node::generate(Data &data, int &counter, int id, Type type) {
    switch (type) {
        case Type::CUSTOM: {
            std::shared_ptr<dsp::Node> custom = std::make_shared<dsp::Node>();
            Node node(id, type, custom);
            return node;
        }
        case Type::RECORDER: {
            std::shared_ptr<dsp::Recorder> recorder = std::make_shared<dsp::Recorder>();
            Node node(id, type, recorder);
            node.addInput(++counter, "Input", recorder->getInput());
            node.addInput(++counter, "Gate", recorder->getGate());
            node.addInput(++counter, "Reset", recorder->getReset());
            return node;
        }
        case Type::CHANNEL_MERGER: {
            std::shared_ptr<dsp::ChannelMerger> merger = std::make_shared<dsp::ChannelMerger>();
            Node node(id, type, merger);
            node.addOutput(++counter, "Output", merger->getOutput());
            return node;
        }
        case Type::CHANNEL_SPLITTER: {
            std::shared_ptr<dsp::ChannelSplitter> splitter = std::make_shared<dsp::ChannelSplitter>();
            Node node(id, type, splitter);
            node.addInput(++counter, "Input", splitter->getInput());
            return node;
        }
        case Type::MID_SIDE: {
            std::shared_ptr<dsp::MidSide> midSide = std::make_shared<dsp::MidSide>();
            Node node(id, type, midSide);
            node.addInput(++counter, "Input", midSide->getInput());
            node.addInput(++counter, "Mix Amount", midSide->getMixAmount());
            node.addOutput(++counter, "Mid", midSide->getMid());
            node.addOutput(++counter, "Side", midSide->getSide());
            return node;
        }
        case Type::SPREAD: {
            std::shared_ptr<dsp::Spread> spread = std::make_shared<dsp::Spread>();
            Node node(id, type, spread);
            node.addInput(++counter, "Input", spread->getInput());
            node.addInput(++counter, "Spread", spread->getSpread());
            node.addOutput(++counter, "Output", spread->getOutput());
            return node;
        }
        case Type::STEREO_PANNER: {
            std::shared_ptr<dsp::StereoPanner> stereoPanner = std::make_shared<dsp::StereoPanner>();
            Node node(id, type, stereoPanner);
            node.addInput(++counter, "Input", stereoPanner->getInput());
            node.addInput(++counter, "Direction", stereoPanner->getDirection());
            node.addOutput(++counter, "Left", stereoPanner->getLeft());
            node.addOutput(++counter, "Right", stereoPanner->getRight());
            return node;
        }
        case Type::CONVOLVER: {
            std::shared_ptr<dsp::Convolver> convolver = std::make_shared<dsp::Convolver>();
            Node node(id, type, convolver);
            node.addInput(++counter, "Input", convolver->getInput());
            node.addOutput(++counter, "Output", convolver->getOutput());
            return node;
        }
        case Type::VARIABLE_DELAY: {
            std::shared_ptr<dsp::VariableDelay> variableDelay = std::make_shared<dsp::VariableDelay>();
            Node node(id, type, variableDelay);
            node.addInput(++counter, "Input", variableDelay->getInput());
            node.addInput(++counter, "Delay Time", variableDelay->getDelayTime());
            node.addInput(++counter, "Decay Time", variableDelay->getDecayTime());
            node.addInput(++counter, "Reset", variableDelay->getReset());
            node.addInput(++counter, "Feedback Sample Input", variableDelay->getFeedbackSink());
            node.addOutput(++counter, "Output", variableDelay->getOutput());
            node.addOutput(++counter, "Feedback Sample Output", variableDelay->getFeedbackSource());
            return node;
        }
        case Type::CLIPPER: {
            std::shared_ptr<dsp::Clipper> clipper = std::make_shared<dsp::Clipper>();
            Node node(id, type, clipper);
            node.addInput(++counter, "Input", clipper->getInput());
            node.addOutput(++counter, "Output", clipper->getOutput());
            return node;
        }
        case Type::COMPRESSOR_GATE: {
            std::shared_ptr<dsp::CompressorGate> compressorGate = std::make_shared<dsp::CompressorGate>();
            Node node(id, type, compressorGate);
            node.addInput(++counter, "Input", compressorGate->getInput());
            node.addInput(++counter, "Control", compressorGate->getControl());
            node.addInput(++counter, "Threshold", compressorGate->getThreshold());
            node.addInput(++counter, "Half Knee", compressorGate->getHalfKnee());
            node.addInput(++counter, "Compression Ratio", compressorGate->getCompressionRatio());
            node.addInput(++counter, "Gate Ratio", compressorGate->getGateRatio());
            node.addInput(++counter, "Attack", compressorGate->getAttack());
            node.addInput(++counter, "Release", compressorGate->getRelease());
            node.addOutput(++counter, "Output", compressorGate->getOutput());
            node.addOutput(++counter, "Gain Response", compressorGate->getGainResponse());
            return node;
        }
        case Type::DRY_WET: {
            std::shared_ptr<dsp::DryWet> dryWet = std::make_shared<dsp::DryWet>();
            Node node(id, type, dryWet);
            node.addInput(++counter, "Dry", dryWet->getDry());
            node.addInput(++counter, "Wet", dryWet->getWet());
            node.addInput(++counter, "Mix Amount", dryWet->getMixAmount());
            node.addOutput(++counter, "Output", dryWet->getOutput());
            return node;
        }
        case Type::ENVELOPE: {
            std::shared_ptr<dsp::Envelope> envelope = std::make_shared<dsp::Envelope>();
            Node node(id, type, envelope);
            node.addInput(++counter, "Attack", envelope->getAttack());
            node.addInput(++counter, "Release", envelope->getRelease());
            node.addInput(++counter, "Gate", envelope->getGate());
            node.addInput(++counter, "Reset", envelope->getReset());
            node.addOutput(++counter, "Output", envelope->getOutput());
            return node;
        }
        case Type::SHAPER: {
            std::shared_ptr<dsp::Shaper> shaper = std::make_shared<dsp::Shaper>();
            Node node(id, type, shaper);
            node.addInput(++counter, "Input", shaper->getInput());
            node.addInput(++counter, "Drive", shaper->getDrive());
            node.addOutput(++counter, "Output", shaper->getOutput());
            return node;
        }
        case Type::MIDI_INPUT: {
            std::shared_ptr<dsp::MidiInput> midiInput =
                    std::make_shared<dsp::MidiInput>(data.getNodeProcessor()->getInputMessages());
            Node node(id, type, midiInput);
            node.addOutput(++counter, "Output", midiInput->getOutput());
            return node;
        }
        case Type::MIDI_OUTPUT: {
            std::shared_ptr<dsp::MidiOutput> midiOutput =
                    std::make_shared<dsp::MidiOutput>(data.getNodeProcessor()->getOutputMessages());
            Node node(id, type, midiOutput);
            node.addInput(++counter, "Input", midiOutput->getInput());
            return node;
        }
        case Type::BIQUAD: {
            std::shared_ptr<dsp::Biquad> biquad = std::make_shared<dsp::Biquad>();
            Node node(id, type, biquad);
            node.addInput(++counter, "Input", biquad->getInput());
            node.addInput(++counter, "Frequency", biquad->getFrequency());
            node.addInput(++counter, "Resonance", biquad->getResonance());
            node.addInput(++counter, "Amplitude", biquad->getAmplitude());
            node.addInput(++counter, "Reset", biquad->getInput());
            node.addOutput(++counter, "Output", biquad->getOutput());
            return node;
        }
        case Type::CROSSOVER: {
            std::shared_ptr<dsp::Crossover> crossover = std::make_shared<dsp::Crossover>();
            Node node(id, type, crossover);
            node.addInput(++counter, "Input", crossover->getInput());
            node.addInput(++counter, "Frequency", crossover->getFrequency());
            node.addOutput(++counter, "Low", crossover->getLow());
            node.addOutput(++counter, "High", crossover->getHigh());
            return node;
        }
        case Type::ONE_POLE: {
            std::shared_ptr<dsp::OnePole> onePole = std::make_shared<dsp::OnePole>();
            Node node(id, type, onePole);
            node.addInput(++counter, "Input", onePole->getInput());
            node.addInput(++counter, "Frequency", onePole->getFrequency());
            node.addOutput(++counter, "Output", onePole->getOutput());
            return node;
        }
        case Type::MOORER_DSF: {
            std::shared_ptr<dsp::MoorerOscillator> moorer = std::make_shared<dsp::MoorerOscillator>();
            Node node(id, type, moorer);
            node.addInput(++counter, "Phase", moorer->getPhase());
            node.addInput(++counter, "Intensity", moorer->getIntensity());
            node.addInput(++counter, "Modulation Index", moorer->getModulationIndex());
            node.addInput(++counter, "Harmonics", moorer->getHarmonics());
            node.addOutput(++counter, "Output", moorer->getOutput());
            return node;
        }
        case Type::NOISE: {
            std::shared_ptr<dsp::Noise> noise = std::make_shared<dsp::Noise>();
            Node node(id, type, noise);
            node.addOutput(++counter, "Output", noise->getOutput());
            return node;
        }
        case Type::PHASOR: {
            std::shared_ptr<dsp::Phasor> phasor = std::make_shared<dsp::Phasor>();
            Node node(id, type, phasor);
            node.addInput(++counter, "Frequency", phasor->getFrequency());
            node.addInput(++counter, "Reset", phasor->getReset());
            node.addOutput(++counter, "Output", phasor->getOutput());
            return node;
        }
        case Type::SAMPLE_PLAYER: {
            std::shared_ptr<dsp::SamplePlayer> samplePlayer = std::make_shared<dsp::SamplePlayer>();
            Node node(id, type, samplePlayer);
            node.addInput(++counter, "Sample Index", samplePlayer->getSampleIndex());
            node.addInput(++counter, "Start Time", samplePlayer->getStartTime());
            node.addInput(++counter, "Speed", samplePlayer->getSpeed());
            node.addInput(++counter, "Gate", samplePlayer->getGate());
            node.addInput(++counter, "Reset", samplePlayer->getReset());
            node.addOutput(++counter, "Output", samplePlayer->getOutput());
            node.addOutput(++counter, "Current Time", samplePlayer->getCurrentTime());
            return node;
        }
        case Type::TABLE_OSCILLATOR: {
            std::shared_ptr<dsp::TableOscillator> tableOscillator = std::make_shared<dsp::TableOscillator>();
            Node node(id, type, tableOscillator);
            node.addInput(++counter, "Phase", tableOscillator->getPhase());
            node.addInput(++counter, "Position", tableOscillator->getPosition());
            node.addOutput(++counter, "Output", tableOscillator->getOutput());
            return node;
        }
        case Type::ABSOLUTE_VALUE: {
            std::shared_ptr<dsp::AbsoluteValue> absoluteValue = std::make_shared<dsp::AbsoluteValue>();
            Node node(id, type, absoluteValue);
            node.addInput(++counter, "Input", absoluteValue->getInput());
            node.addOutput(++counter, "Output", absoluteValue->getOutput());
            return node;
        }
        case Type::BOOLEAN_MASK: {
            std::shared_ptr<dsp::BooleanMask> booleanMask = std::make_shared<dsp::BooleanMask>();
            Node node(id, type, booleanMask);
            node.addInput(++counter, "Input", booleanMask->getInput());
            node.addInput(++counter, "Mask", booleanMask->getMask());
            node.addOutput(++counter, "Output", booleanMask->getOutput());
            return node;
        }
        case Type::COMPARISON: {
            std::shared_ptr<dsp::Comparison> comparison = std::make_shared<dsp::Comparison>();
            Node node(id, type, comparison);
            node.addInput(++counter, "Input", comparison->getInput());
            node.addInput(++counter, "Threshold", comparison->getThreshold());
            node.addOutput(++counter, "Output", comparison->getOutput());
            return node;
        }
        case Type::EXP2: {
            std::shared_ptr<dsp::Exp2> exponential = std::make_shared<dsp::Exp2>();
            Node node(id, type, exponential);
            node.addInput(++counter, "Input", exponential->getInput());
            node.addOutput(++counter, "Output", exponential->getOutput());
            return node;
        }
        case Type::FLOOR: {
            std::shared_ptr<dsp::Floor> floor = std::make_shared<dsp::Floor>();
            Node node(id, type, floor);
            node.addInput(++counter, "Input", floor->getInput());
            node.addInput(++counter, "Divisor", floor->getDivisor());
            node.addOutput(++counter, "Output", floor->getOutput());
            return node;
        }
        case Type::FORWARD_FFT: {
            std::shared_ptr<dsp::ForwardFFT> forwardFFT = std::make_shared<dsp::ForwardFFT>();
            Node node(id, type, forwardFFT);
            node.addInput(++counter, "Input", forwardFFT->getInput());
            node.addOutput(++counter, "Magnitude", forwardFFT->getMagnitude());
            node.addOutput(++counter, "Phase", forwardFFT->getPhase());
            return node;
        }
        case Type::FREQUENCY_TO_NOTE: {
            std::shared_ptr<dsp::FrequencyToNote> toNote = std::make_shared<dsp::FrequencyToNote>();
            Node node(id, type, toNote);
            node.addInput(++counter, "Input", toNote->getInput());
            node.addOutput(++counter, "Output", toNote->getOutput());
            return node;
        }
        case Type::IDENTITY: {
            std::shared_ptr<dsp::Identity> identity = std::make_shared<dsp::Identity>();
            Node node(id, type, identity);
            node.addInput(++counter, "Input", identity->getInput());
            node.addOutput(++counter, "Output", identity->getOutput());
            return node;
        }
        case Type::INVERSE_FFT: {
            std::shared_ptr<dsp::InverseFFT> inverseFFT = std::make_shared<dsp::InverseFFT>();
            Node node(id, type, inverseFFT);
            node.addInput(++counter, "Magnitude", inverseFFT->getMagnitude());
            node.addInput(++counter, "Phase", inverseFFT->getPhase());
            node.addOutput(++counter, "Output", inverseFFT->getOutput());
            return node;
        }
        case Type::LOG2: {
            std::shared_ptr<dsp::Log2> logarithm = std::make_shared<dsp::Log2>();
            Node node(id, type, logarithm);
            node.addInput(++counter, "Input", logarithm->getInput());
            node.addOutput(++counter, "Output", logarithm->getOutput());
            return node;
        }
        case Type::MODULO: {
            std::shared_ptr<dsp::Modulo> modulo = std::make_shared<dsp::Modulo>();
            Node node(id, type, modulo);
            node.addInput(++counter, "Input", modulo->getInput());
            node.addInput(++counter, "Divisor", modulo->getDivisor());
            node.addOutput(++counter, "Output", modulo->getOutput());
            return node;
        }
        case Type::MULTIPLY: {
            std::shared_ptr<dsp::Multiply> multiply = std::make_shared<dsp::Multiply>();
            Node node(id, type, multiply);
            node.addInput(++counter, "Input", multiply->getInput());
            node.addOutput(++counter, "Output", multiply->getOutput());
            return node;
        }
        case Type::MULTIPLY_FREQUENCY_TIME: {
            std::shared_ptr<dsp::MultiplyFrequencyTime> multiplyFT =
                    std::make_shared<dsp::MultiplyFrequencyTime>();
            Node node(id, type, multiplyFT);
            node.addInput(++counter, "Frequency", multiplyFT->getFrequency());
            node.addInput(++counter, "Time", multiplyFT->getTime());
            node.addOutput(++counter, "Output", multiplyFT->getOutput());
            return node;
        }
        case Type::NOTE_TO_FREQUENCY: {
            std::shared_ptr<dsp::NoteToFrequency> toFrequency = std::make_shared<dsp::NoteToFrequency>();
            Node node(id, type, toFrequency);
            node.addInput(++counter, "Input", toFrequency->getInput());
            node.addOutput(++counter, "Output", toFrequency->getOutput());
            return node;
        }
        case Type::NOT_GATE: {
            std::shared_ptr<dsp::NotGate> notGate = std::make_shared<dsp::NotGate>();
            Node node(id, type, notGate);
            node.addInput(++counter, "Input", notGate->getInput());
            node.addOutput(++counter, "Output", notGate->getOutput());
            return node;
        }
        case Type::RECIPROCAL: {
            std::shared_ptr<dsp::Reciprocal> reciprocal = std::make_shared<dsp::Reciprocal>();
            Node node(id, type, reciprocal);
            node.addInput(++counter, "Input", reciprocal->getInput());
            node.addOutput(++counter, "Output", reciprocal->getOutput());
            return node;
        }
        case Type::CLOCK_TRIGGER: {
            std::shared_ptr<dsp::ClockTrigger> clockTrigger = std::make_shared<dsp::ClockTrigger>();
            Node node(id, type, clockTrigger);
            node.addInput(++counter, "Interval", clockTrigger->getInterval());
            node.addInput(++counter, "Delay Time", clockTrigger->getDelayTime());
            node.addInput(++counter, "Reset", clockTrigger->getReset());
            node.addOutput(++counter, "Output", clockTrigger->getOutput());
            node.addOutput(++counter, "Current Time", clockTrigger->getCurrentTime());
            return node;
        }
        case Type::DIFFERENTIATOR: {
            std::shared_ptr<dsp::Differentiator> differentiator = std::make_shared<dsp::Differentiator>();
            Node node(id, type, differentiator);
            node.addInput(++counter, "Input", differentiator->getInput());
            node.addInput(++counter, "Gate", differentiator->getGate());
            node.addInput(++counter, "Reset", differentiator->getReset());
            node.addOutput(++counter, "Output", differentiator->getOutput());
            return node;
        }
        case Type::INTEGRATOR: {
            std::shared_ptr<dsp::Integrator> integrator = std::make_shared<dsp::Integrator>();
            Node node(id, type, integrator);
            node.addInput(++counter, "Input", integrator->getInput());
            node.addInput(++counter, "Gate", integrator->getGate());
            node.addInput(++counter, "Reset", integrator->getReset());
            node.addOutput(++counter, "Output", integrator->getOutput());
            return node;
        }
        case Type::ON_OFF: {
            std::shared_ptr<dsp::OnOff> onOff = std::make_shared<dsp::OnOff>();
            Node node(id, type, onOff);
            node.addInput(++counter, "On", onOff->getOnTrigger());
            node.addInput(++counter, "Off", onOff->getOffTrigger());
            node.addOutput(++counter, "Output", onOff->getOutput());
            return node;
        }
        case Type::RESET_TRIGGER: {
            std::shared_ptr<dsp::ResetTrigger> resetTrigger = std::make_shared<dsp::ResetTrigger>();
            Node node(id, type, resetTrigger);
            node.addOutput(++counter, "Output", resetTrigger->getOutput());
            return node;
        }
        case Type::SAMPLE_AND_HOLD: {
            std::shared_ptr<dsp::SampleAndHold> sampleAndHold = std::make_shared<dsp::SampleAndHold>();
            Node node(id, type, sampleAndHold);
            node.addInput(++counter, "Input", sampleAndHold->getInput());
            node.addInput(++counter, "Gate", sampleAndHold->getGate());
            node.addInput(++counter, "Reset", sampleAndHold->getReset());
            node.addOutput(++counter, "Output", sampleAndHold->getOutput());
            return node;
        }
        case Type::SEQUENCER: {
            std::shared_ptr<dsp::Sequencer> sequencer = std::make_shared<dsp::Sequencer>();
            Node node(id, type, sequencer);
            node.addInput(++counter, "Sequence Index", sequencer->getSequenceIndex());
            node.addInput(++counter, "Position Index", sequencer->getPositionIndex());
            node.addOutput(++counter, "Output", sequencer->getOutput());
            return node;
        }
        case Type::BEAT_DURATION: {
            std::shared_ptr<dsp::BeatDuration> beatDuration =
                    std::make_shared<dsp::BeatDuration>(data.getAudioProcessor());
            Node node(id, type, beatDuration);
            node.addOutput(++counter, "Output", beatDuration->getOutput());
            return node;
        }
        case Type::BEAT_RATE: {
            std::shared_ptr<dsp::BeatRate> beatRate = std::make_shared<dsp::BeatRate>(data.getAudioProcessor());
            Node node(id, type, beatRate);
            node.addOutput(++counter, "Output", beatRate->getOutput());
            return node;
        }
        case Type::BUFFER_DURATION: {
            std::shared_ptr<dsp::BufferDuration> bufferDuration = std::make_shared<dsp::BufferDuration>();
            Node node(id, type, bufferDuration);
            node.addOutput(++counter, "Output", bufferDuration->getOutput());
            return node;
        }
        case Type::BUFFER_RATE: {
            std::shared_ptr<dsp::BufferRate> bufferRate = std::make_shared<dsp::BufferRate>();
            Node node(id, type, bufferRate);
            node.addOutput(++counter, "Output", bufferRate->getOutput());
            return node;
        }
        case Type::SAMPLE_DURATION: {
            std::shared_ptr<dsp::SampleDuration> sampleDuration = std::make_shared<dsp::SampleDuration>();
            Node node(id, type, sampleDuration);
            node.addOutput(++counter, "Output", sampleDuration->getOutput());
            return node;
        }
        case Type::SAMPLE_RATE: {
            std::shared_ptr<dsp::SampleRate> sampleRate = std::make_shared<dsp::SampleRate>();
            Node node(id, type, sampleRate);
            node.addOutput(++counter, "Output", sampleRate->getOutput());
            return node;
        }
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

particle::NodeGraph::Link particle::NodeGraph::Link::generate(std::map<int, Node> &nodes, int id, int from, int to) {
    Input input;
    Output output;
    for (const auto &node : nodes) {
        std::map<int, Input>::const_iterator inputIterator;
        if ((inputIterator = node.second.inputs.find(from)) != node.second.inputs.end()) {
            input = inputIterator->second;
            break;
        }
        std::map<int, Output>::const_iterator outputIterator;
        if ((outputIterator = node.second.outputs.find(from)) != node.second.outputs.end()) {
            output = outputIterator->second;
            break;
        }
    }
    for (const auto &node : nodes) {
        std::map<int, Input>::const_iterator inputIterator;
        if ((inputIterator = node.second.inputs.find(to)) != node.second.inputs.end()) {
            input = inputIterator->second;
            break;
        }
        std::map<int, Output>::const_iterator outputIterator;
        if ((outputIterator = node.second.outputs.find(to)) != node.second.outputs.end()) {
            output = outputIterator->second;
            break;
        }
    }
    assert(input.id != 0);
    assert(output.id != 0);
    return Link(id, output, input);
}

particle::NodeGraph::NodeGraph(Data &data, std::string name, std::vector<std::shared_ptr<dsp::Node>> &audioNodes)
        : Frame(data, name)
        , audioNodes(audioNodes)
        , counter(0) {
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
    ImGuiIO &io = ImGui::GetIO();
    imnodes::EditorContextSet(context);
    if (ImGui::IsKeyPressed(io.KeyMap[ImGuiKey_Backspace])) {
        removeNodes();
        removeLinks();
    }
    imnodes::BeginNodeEditor();
    drawPopup();
    for (auto &node : nodes) {
        node.second.draw();
    }
    for (auto &link : links) {
        link.second.draw();
    }
    imnodes::EndNodeEditor();
    {
        int from;
        int to;
        if (imnodes::IsLinkCreated(&from, &to)) {
            const int id = ++counter;
            links.emplace(id, Link::generate(nodes, id, from, to));
        }
    }
    {
        int id;
        if (imnodes::IsLinkDestroyed(&id)) {
            links.erase(id);
        }
    }
}

void particle::NodeGraph::removeNodes() {
    int numSelectedNodes = imnodes::NumSelectedNodes();
    if (numSelectedNodes) {
        std::vector<int> selectedNodes(numSelectedNodes);
        imnodes::GetSelectedNodes(selectedNodes.data());
        for (const auto &node : selectedNodes) {
            nodes.erase(node);
        }
    }
}

void particle::NodeGraph::removeLinks() {
    int numSelectedLinks = imnodes::NumSelectedLinks();
    if (numSelectedLinks) {
        std::vector<int> selectedLinks(numSelectedLinks);
        imnodes::GetSelectedLinks(selectedLinks.data());
        for (const auto &link : selectedLinks) {
            links.erase(link);
        }
    }
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
                        const int id = ++counter;
                        imnodes::SetNodeScreenSpacePos(id, mousePosition);
                        nodes.emplace(id, Node::generate(getData(), counter, id, type));
                    }
                }
                ImGui::EndMenu();
            }
        }
        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();
}
