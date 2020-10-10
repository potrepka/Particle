#pragma once

#include <string>

#include "Frame.h"
#include "Node.h"

namespace particle {

class NodeGraph : public Frame {

public:

    struct Input {
        int id;
        std::string name;
        std::shared_ptr<dsp::Input> input;

        Input(int id, std::string name, std::shared_ptr<dsp::Input> input);

        void draw();
        void drawInspector();
    };

    struct Output {
        int id;
        std::string name;
        std::shared_ptr<dsp::Output> output;
    
        Output(int id, std::string name, std::shared_ptr<dsp::Output> output);

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
            NOISE,
            OSCILLATOR,
            PHASOR,
            SAMPLE_PLAYER,
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
            MULTIPLY_HERTZ_SECONDS,
            NOTE_TO_FREQUENCY,
            NOT_GATE,
            ONE_OVER,
            BEAT_TRIGGER,
            DIFFERENTIATOR,
            INTEGRATOR,
            ON_OFF,
            RESET_TRIGGER,
            SAMPLE_AND_HOLD,
            SEQUENCER,
            BEAT_DURATION,
            BEAT_RATE,
            BUFFER_DURATION,
            BUFFER_RATE,
            SAMPLE_DURATION,
            SAMPLE_RATE
        };

        struct Category {
            std::string name;
            std::vector<Type> types;

            Category(std::string name, std::vector<Type> types = std::vector<Type>());
        };

        int id;
        Type type;
        std::shared_ptr<dsp::Node> node;
        std::map<int, Input> inputs;
        std::map<int, Output> outputs;
        std::string customName;

        Node(int id, Type type, std::shared_ptr<dsp::Node> node);

        std::string getName() const;
        std::string getCustomName() const;
        void setCustomName(std::string customName);

        void draw();
        void drawContent();
        void drawInspector();

        static std::vector<Category> getCategories();
        static std::string getTypeName(Type type, std::string customName = "");
    };
    
    struct Link {
        int id;
        Output from;
        Input to;

        Link(int id, Output from, Input to);

        void draw();
        void drawInspector();
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
    int counter = 0;
    imnodes::EditorContext *context;
    std::vector<std::shared_ptr<dsp::Node>> &audioNodes;
    std::vector<dsp::Output> inputs;
    std::vector<dsp::Input> outputs;
    std::vector<std::string> inputNames;
    std::vector<std::string> outputNames;
    std::map<int, Node> nodes;
    std::map<int, Link> links;

    void drawInternal() override;
    void drawPopup();
};

} // namespace particle
