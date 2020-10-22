#pragma once

#include <JuceHeader.h>

#include "Frame.h"
#include "Nodes/Nodes.h"

#include "DSP.h"

namespace particle {

class NodeGraph : public Frame, public std::enable_shared_from_this<NodeGraph> {

public:
    struct Input : public Named {
        int id;
        std::shared_ptr<dsp::Input> input;

        Input(int id = 0, std::string name = "", std::shared_ptr<dsp::Input> input = nullptr);

        void draw();
        void drawInspector();
    };

    struct Output : public Named {
        int id;
        std::shared_ptr<dsp::Output> output;
    
        Output(int id = 0, std::string name = "", std::shared_ptr<dsp::Output> output = nullptr);

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

        struct Category : public Named {
            std::vector<Type> types;

            Category(std::string name = "", std::vector<Type> types = std::vector<Type>());
        };

        int id;
        Type type;
        ImVec2 position;
        std::shared_ptr<dsp::Node> node;
        std::map<int, Input> inputs;
        std::map<int, Output> outputs;

        Node(int id = 0,
             Type type = Type::CUSTOM,
             ImVec2 position = ImVec2(0, 0),
             std::shared_ptr<dsp::Node> node = nullptr);

        void addInput(int id, std::string name, std::shared_ptr<dsp::Input> input);
        void addOutput(int id, std::string name, std::shared_ptr<dsp::Output> output);

        std::string getTypeName() const;

        void draw();
        void drawContent();
        void drawInspector();

        static std::vector<Category> getCategories(bool isPlugin);
        static std::string getTypeName(Type type);
        static Node generate(Data &data, int &counter, int id, Type type, ImVec2 position);
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

    class CreateNode : public Action {

    public:
        CreateNode(std::shared_ptr<NodeGraph> nodeGraph, Node node);

        void perform() override;
        void undo() override;

    private:
        std::shared_ptr<NodeGraph> nodeGraph;
        Node node;
    };

    class CreateLink : public Action {

    public:
        CreateLink(std::shared_ptr<NodeGraph> nodeGraph, Link link);

        void perform() override;
        void undo() override;

    private:
        std::shared_ptr<NodeGraph> nodeGraph;
        Link link;
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
};

} // namespace particle
