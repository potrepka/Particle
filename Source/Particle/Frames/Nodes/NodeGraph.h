#pragma once

#include "JuceHeader.h"

#include "DSP.h"
#include "Frame.h"
#include "Nodes/Nodes.h"

namespace particle {

class NodeGraph : public Frame {

public:
    struct Input {
        int id;
        std::string name;
        std::shared_ptr<dsp::Input> input;

        Input(int id = 0, std::string name = "", std::shared_ptr<dsp::Input> input = nullptr);

        void draw();
        void drawInspector();
    };

    struct Output {
        int id;
        std::string name;
        std::shared_ptr<dsp::Output> output;
    
        Output(int id = 0, std::string name = "", std::shared_ptr<dsp::Output> output = nullptr);

        void draw();
        void drawInspector();
    };

    struct Node {

    public:
        enum class Type {
            CUSTOM,
            RECORDER,       // TODO: Add more analyzers
            CHANNEL_MERGER,
            CHANNEL_SPLITTER,
            MID_SIDE,
            SPREAD,
            STEREO_PANNER,
            CONVOLVER,
            VARIABLE_DELAY,
            CLIPPER,
            COMPRESSOR_GATE,
            DRY_WET,
            ENVELOPE,
            SHAPER,
            MIDI_INPUT,
            MIDI_OUTPUT,
            BIQUAD,
            CROSSOVER,
            ONE_POLE,
            MOORER_DSF,
            NOISE,
            PHASOR,
            SAMPLE_PLAYER,
            WAVETABLE_OSCILLATOR,
            ABSOLUTE_VALUE,
            BOOLEAN_MASK,
            COMPARISON,
            EXP2,
            FLOOR,
            FORWARD_FFT,
            FREQUENCY_TO_NOTE,
            IDENTITY,
            INVERSE_FFT,
            LOG2,
            MODULO,
            MULTIPLY,
            MULTIPLY_FREQUENCY_TIME,
            NOTE_TO_FREQUENCY,
            NOT_GATE,
            RECIPROCAL,
            CLOCK_TRIGGER,
            DIFFERENTIATOR,
            INTEGRATOR,
            ON_OFF,
            RESET_TRIGGER,
            SAMPLE_AND_HOLD,
            SEQUENCER,
            BUFFER_DURATION,
            BUFFER_RATE,
            SAMPLE_DURATION,
            SAMPLE_RATE,
            VARIABLE,
            BEAT_DURATION,
            BEAT_RATE,
            TIME_SIGNATURE,
            TRANSPORT_STATE
        };

        struct Category {
            std::string name;
            std::vector<Type> types;

            Category(std::string name = "", std::vector<Type> types = std::vector<Type>());
        };

        int id;
        Type type;
        std::shared_ptr<dsp::Node> node;
        std::map<int, Input> inputs;
        std::map<int, Output> outputs;
        std::string customName;

        Node(int id = 0, Type type = Type::CUSTOM, std::shared_ptr<dsp::Node> node = nullptr);

        void addInput(int id, std::string name, std::shared_ptr<dsp::Input> input);
        void addOutput(int id, std::string name, std::shared_ptr<dsp::Output> output);

        std::string getCustomName() const;
        void setCustomName(std::string customName);

        void draw();
        void drawContent();
        void drawInspector();

        static std::vector<Category> getCategories(bool isPlugin);
        static std::string getTypeName(Type type);
        static Node generate(Data &data, int &counter, int id, Type type);
    };
    
    struct Link {
        int id;
        Output from;
        Input to;

        Link(int id = 0, Output from = Output(), Input to = Input());

        void draw();
        void drawInspector();

        static Link generate(std::map<int, Node> &nodes, int id, int from, int to);
    };

    NodeGraph(Data &data, std::string name, std::vector<std::shared_ptr<dsp::Node>> &audioNodes);
    ~NodeGraph();

    imnodes::EditorContext *getContext() const;

    std::vector<std::shared_ptr<dsp::Node>> &getAudioNodes();

    std::vector<dsp::Output> &getInputs();
    std::vector<dsp::Input> &getOutputs();
    std::vector<std::string> &getInputNames();
    std::vector<std::string> &getOutputNames();

private:
    std::vector<std::shared_ptr<dsp::Node>> &audioNodes;
    int counter;
    imnodes::EditorContext *context;
    std::vector<dsp::Output> inputs;
    std::vector<dsp::Input> outputs;
    std::vector<std::string> inputNames;
    std::vector<std::string> outputNames;
    std::map<int, Node> nodes;
    std::map<int, Link> links;

    void drawInternal() override;
    void removeNodes();
    void removeLinks();
    void drawPopup();
};

} // namespace particle
