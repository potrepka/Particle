#include "PluginProcessor.h"

#include "PluginEditor.h"

ParticleAudioProcessor::ParticleAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
        : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
                                 // TODO: CLEAN UP CHANNEL CONFIGURATION
                                 //#if ! JucePlugin_IsSynth
                                 .withInput("Input", juce::AudioChannelSet::stereo(), true)
                                 //#endif
                                 .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
                                 )
        , nodeProcessor(2, 2, 0, 0.0)
#endif
{
    if (supportsDoublePrecisionProcessing()) {
        setProcessingPrecision(juce::AudioProcessor::ProcessingPrecision::doublePrecision);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplJUCE_Init();

    // TODO: Remove MIDI status messages

    std::shared_ptr<dsp::MidiInput> input =
            std::make_shared<dsp::MidiInput>(dsp::Type::RATIO, nodeProcessor.getInputMessages());
    std::weak_ptr<dsp::MidiInput> inputWeak(input);
    input->setProcessFunction([inputWeak]() {
        const auto input = inputWeak.lock();
        for (const auto meta : *input->getInputMessages()) {
            const auto message = meta.getMessage();
            std::cout << "INPUT: " << message.getDescription() << std::endl;
        }
    });
    nodeProcessor.lock();
    nodeProcessor.getNodes().push_back(input);
    nodeProcessor.unlock();

    std::shared_ptr<dsp::MidiOutput> output =
            std::make_shared<dsp::MidiOutput>(dsp::Type::RATIO, nodeProcessor.getOutputMessages());
    std::weak_ptr<dsp::MidiOutput> outputWeak(output);
    output->setProcessFunction([outputWeak]() {
        const auto output = outputWeak.lock();
        for (const auto meta : *output->getOutputMessages()) {
            const auto message = meta.getMessage();
            std::cout << "OUTPUT: " << message.getDescription() << std::endl;
        }
    });
    nodeProcessor.lock();
    nodeProcessor.getNodes().push_back(output);
    nodeProcessor.unlock();

//    std::shared_ptr<dsp::WhiteNoise> white = std::make_shared<dsp::WhiteNoise>();
//    white->setNumOutputChannels(2);
//    nodeProcessor.lock();
//    nodeProcessor.getNodes().push_back(white);
//    white->getOutputSignal()->connect(nodeProcessor.getAudioOutput());
//    nodeProcessor.unlock();

    std::shared_ptr<dsp::PinkNoise> pink = std::make_shared<dsp::PinkNoise>();
    pink->setNumOutputChannels(2);
    nodeProcessor.lock();
    nodeProcessor.getNodes().push_back(pink);
    pink->getOutput()->connect(nodeProcessor.getAudioOutput());
    nodeProcessor.unlock();
}

ParticleAudioProcessor::~ParticleAudioProcessor() {
    ImGui_ImplJUCE_Shutdown();
    ImGui::DestroyContext();
}

const juce::String ParticleAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool ParticleAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool ParticleAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool ParticleAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double ParticleAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int ParticleAudioProcessor::getNumPrograms() {
    // TODO: ADD PROGRAMS
    // Should be greater than zero. Otherwise some hosts will not work correctly.
    return 1;
}

int ParticleAudioProcessor::getCurrentProgram() {
    // TODO: ADD PROGRAMS
    return 0;
}

void ParticleAudioProcessor::setCurrentProgram(int index) {
    // TODO: ADD PROGRAMS
}

const juce::String ParticleAudioProcessor::getProgramName(int index) {
    // TODO: ADD PROGRAMS
    return {};
}

void ParticleAudioProcessor::changeProgramName(int index, const juce::String &newName) {}

void ParticleAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    // TODO: HANDLE CHANGING NUMBER OF INPUT/OUTPUT CHANNELS MORE GRACEFULLY
    nodeProcessor.setInputSize(getTotalNumInputChannels(), samplesPerBlock);
    nodeProcessor.setOutputSize(getTotalNumOutputChannels(), samplesPerBlock);
    nodeProcessor.setSampleRate(sampleRate);
}

void ParticleAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ParticleAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
    // TODO: CLEAN UP CHANNEL CONFIGURATION
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo()) {
        return false;
    }
    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet()) {
        return false;
    }
#endif
    return true;
#endif
}
#endif

void ParticleAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    nodeProcessor.process(buffer, midiMessages);
}

void ParticleAudioProcessor::processBlock(juce::AudioBuffer<double> &buffer, juce::MidiBuffer &midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    nodeProcessor.process(buffer, midiMessages);
}

bool ParticleAudioProcessor::hasEditor() const {
    return true;
}

juce::AudioProcessorEditor *ParticleAudioProcessor::createEditor() {
    auto *editor = new ParticleAudioProcessorEditor(*this);
    if (wrapperType == wrapperType_Standalone) {
        if (juce::TopLevelWindow::getNumTopLevelWindows() == 1) {
            juce::DocumentWindow *w = dynamic_cast<juce::DocumentWindow *>(juce::TopLevelWindow::getTopLevelWindow(0));
            w->setResizable(true, false);
            w->setUsingNativeTitleBar(true);
            w->setTitleBarButtonsRequired(juce::DocumentWindow::allButtons, true);
        }
    }
    return editor;
}

void ParticleAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
    // TODO: SAVE STATE
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ParticleAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    // TODO: LOAD STATE
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new ParticleAudioProcessor();
}
