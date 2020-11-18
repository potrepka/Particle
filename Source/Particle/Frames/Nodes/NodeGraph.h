#pragma once

#include <JuceHeader.h>

#include "Frame.h"
#include "Nodes/Nodes.h"

#include "DSP.h"

#include <set>

namespace particle {

class NodeGraph : public Frame, public std::enable_shared_from_this<NodeGraph> {

public:
    static const int PRECISION;
    static const float FRAME_WIDTH;

    union FloatInt {
        FloatInt(dsp::Type type, dsp::Sample value);
        float valueFloat;
        int valueInt;
    };

    struct Input : public Named {
        Data *data;
        int id;
        std::shared_ptr<dsp::Input> input;
        std::vector<std::string> values;
        FloatInt value;

        Input(Data *data = nullptr,
              int id = 0,
              std::string name = "",
              std::shared_ptr<dsp::Input> input = nullptr,
              std::vector<std::string> values = std::vector<std::string>());

        void draw();
        void drawInspector();
    };

    struct Output : public Named {
        Data *data;
        int id;
        std::shared_ptr<dsp::Output> output;
        std::vector<std::string> values;
        FloatInt value;
    
        Output(Data *data = nullptr,
               int id = 0,
               std::string name = "",
               std::shared_ptr<dsp::Output> output = nullptr,
               std::vector<std::string> values = std::vector<std::string>());

        void draw();
        void drawInspector();
    };

    struct Node : public Named {
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
            LAG,
            SHAPER,
            AUDIO_INPUT,
            AUDIO_INPUT_CLIPPING,
            AUDIO_OUTPUT,
            AUDIO_OUTPUT_CLIPPING,
            MIDI_INPUT,
            MIDI_OUTPUT,
            BIQUAD,
            CROSSOVER,
            ONE_POLE,
            MOORER_DSF,
            NOISE,
            PHASOR,
            SAMPLE_PLAYER,
            TABLE_OSCILLATOR,
            ABSOLUTE_VALUE,
            BOOLEAN_MASK,
            COMPARISON,
            DIVISION,
            FLOOR,
            FORWARD_FFT,
            FREQUENCY_TO_NOTE,
            HYPERBOLIC,
            INVERSE_FFT,
            LOGARITHM,
            MODULO,
            MULTIPLICATION,
            NEGATIVE,
            NOTE_TO_FREQUENCY,
            NOT_GATE,
            POWER,
            RECIPROCAL,
            TRIGONOMETRIC,
            BEAT_DURATION,
            BEAT_RATE,
            TIME_SIGNATURE,
            TRANSPORT_STATE,
            CLOCK_TRIGGER,
            DIFFERENTIATOR,
            INTEGRATOR,
            ON_OFF,
            RESET_TRIGGER,
            SAMPLE_AND_HOLD,
            SEQUENCER,
            TRIGGER_HOLD,
            BUFFER_DURATION,
            BUFFER_RATE,
            EULER,
            INF,
            PHI,
            PI,
            SAMPLE_DURATION,
            SAMPLE_RATE,
            TAU,
            VARIABLE
        };

        struct Category : public Named {
            std::vector<Type> types;

            Category(std::string name = "", std::vector<Type> types = std::vector<Type>());
        };

        Data *data;
        int id;
        Type type;
        ImVec2 position;
        std::shared_ptr<dsp::Node> node;
        std::map<int, Input> inputs;
        std::map<int, Output> outputs;

        Node(Data *data = nullptr,
             int id = 0,
             Type type = Type::CUSTOM,
             ImVec2 position = ImVec2(0, 0),
             std::shared_ptr<dsp::Node> node = nullptr);

        void addInput(int id,
                      std::string name,
                      std::shared_ptr<dsp::Input> input,
                      std::vector<std::string> values = std::vector<std::string>{});
        void addOutput(int id,
                       std::string name,
                       std::shared_ptr<dsp::Output> output,
                       std::vector<std::string> values = std::vector<std::string>{});

        std::string getTypeName() const;

        void draw(bool selected = false);
        void drawContent();
        void drawInspector();

        static std::vector<Category> getCategories(bool isPlugin);
        static std::string getTypeName(Type type);
        static Node generate(Data *data, int &counter, int id, Type type, ImVec2 position);

    private:
        float getFrameHeight(float numberOfBlocks);
        void drawPlot(std::string title,
                      std::vector<dsp::Sample> x,
                      std::vector<std::vector<dsp::Sample>> y,
                      dsp::Sample x_min,
                      dsp::Sample x_max,
                      dsp::Sample y_min,
                      dsp::Sample y_max,
                      ImVec2 size = ImVec2(-1.0f, 0.0f),
                      ImPlotAxisFlags x_flags = ImPlotAxisFlags_None,
                      ImPlotAxisFlags y_flags = ImPlotAxisFlags_None);
        void drawLabel(const char *text);
    };
    
    struct Link {
        Data *data;
        int id;
        int from;
        int to;
        std::shared_ptr<dsp::Output> output;
        std::shared_ptr<dsp::Input> input;

        Link(Data *data = nullptr,
             int id = 0,
             int from = 0,
             int to = 0,
             std::shared_ptr<dsp::Output> output = nullptr,
             std::shared_ptr<dsp::Input> input = nullptr);

        void draw();
        void drawInspector();

        static Link generate(Data *data, std::map<int, Node> &nodes, int id, int from, int to);
    };

    class CreateNodes : public Action {

    public:
        CreateNodes(std::shared_ptr<NodeGraph> nodeGraph, std::vector<Node> nodes);

        void perform() override;
        void undo() override;

    private:
        std::shared_ptr<NodeGraph> nodeGraph;
        std::vector<Node> nodes;
    };

    class CreateLinks : public Action {

    public:
        CreateLinks(std::shared_ptr<NodeGraph> nodeGraph, std::vector<Link> links);

        void perform() override;
        void undo() override;

    private:
        std::shared_ptr<NodeGraph> nodeGraph;
        std::vector<Link> links;
    };

    class DestroyNodes : public Action {

    public:
        DestroyNodes(std::shared_ptr<NodeGraph> nodeGraph, std::vector<int> ids);

        void perform() override;
        void undo() override;

    private:
        std::shared_ptr<NodeGraph> nodeGraph;
        std::vector<int> ids;
        std::deque<Node> nodes;
        std::deque<Link> links;
    };

    class DestroyLinks : public Action {

    public:
        DestroyLinks(std::shared_ptr<NodeGraph> nodeGraph, std::vector<int> ids);

        void perform() override;
        void undo() override;

    private:
        std::shared_ptr<NodeGraph> nodeGraph;
        std::vector<int> ids;
        std::deque<Link> links;
    };

    NodeGraph(Data &data, std::string name, std::shared_ptr<dsp::Node> container);
    ~NodeGraph();
    
    std::shared_ptr<dsp::Node> getContainer();
    std::map<int, Node> &getNodes();
    std::map<int, Link> &getLinks();

    imnodes::EditorContext *getContext() const;

private:
    int counter;
    std::shared_ptr<dsp::Node> container;
    std::map<int, Node> nodes;
    std::map<int, Link> links;

    imnodes::EditorContext *context;

    void drawInternal() override;
    void destroyNodes();
    void destroyLinks();
    void createNode();
    void createLink();

    std::vector<int> getSelectedNodes();
    std::vector<int> getSelectedLinks();
};

} // namespace particle
