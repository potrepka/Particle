#include "Processor.h"

#include "Editor.h"

particle::Processor::Processor()
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
        , view(this, nullptr, &nodeProcessor)
#endif
{
    if (supportsDoublePrecisionProcessing()) {
        setProcessingPrecision(juce::AudioProcessor::ProcessingPrecision::doublePrecision);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplJUCE_Init();
    imnodes::Initialize();
    //imnodes::GetIO().emulate_three_button_mouse.enabled = true;
    //imnodes::GetIO().emulate_three_button_mouse.modifier = &ImGui::GetIO().KeyCtrl;
    ImPlot::CreateContext();
    view.setup();

    // TODO: Remove MIDI status messages

    std::shared_ptr<dsp::MidiInput> input =
            std::make_shared<dsp::MidiInput>(nodeProcessor.getInputMessages());
    std::weak_ptr<dsp::MidiInput> inputWeak(input);
    input->setProcessFunction([inputWeak]() {
        const auto input = inputWeak.lock();
        const auto messages = input->getInputMessages();
        for (const auto meta : *messages) {
            const auto message = meta.getMessage();
            std::cout << "INPUT: " << message.getDescription() << std::endl;
        }
    });
    nodeProcessor.lock();
    nodeProcessor.getNodes().push_back(input);
    nodeProcessor.unlock();

    std::shared_ptr<dsp::MidiOutput> output =
            std::make_shared<dsp::MidiOutput>(nodeProcessor.getOutputMessages());
    std::weak_ptr<dsp::MidiOutput> outputWeak(output);
    output->setProcessFunction([outputWeak]() {
        const auto output = outputWeak.lock();
        const auto messages = output->getOutputMessages();
        for (const auto meta : *messages) {
            const auto message = meta.getMessage();
            std::cout << "OUTPUT: " << message.getDescription() << std::endl;
        }
    });
    nodeProcessor.lock();
    nodeProcessor.getNodes().push_back(output);
    nodeProcessor.unlock();

    // TODO: Remove pink noise test code

    //std::shared_ptr<dsp::Noise> pink = std::make_shared<dsp::Noise>();
    //pink->setMode(dsp::Noise::Mode::PINK);
    //pink->setNumOutputChannels(2);
    //nodeProcessor.lock();
    //nodeProcessor.getNodes().push_back(pink);
    //pink->getOutput() >> nodeProcessor.getAudioOutput();
    //nodeProcessor.unlock();
}

particle::Processor::~Processor() {
    ImPlot::DestroyContext();
    imnodes::Shutdown();
    ImGui_ImplJUCE_Shutdown();
    ImGui::DestroyContext();
}

const juce::String particle::Processor::getName() const {
    return JucePlugin_Name;
}

bool particle::Processor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool particle::Processor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool particle::Processor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double particle::Processor::getTailLengthSeconds() const {
    return 0.0;
}

int particle::Processor::getNumPrograms() {
    // TODO: ADD PROGRAMS
    // Should be greater than zero. Otherwise some hosts will not work correctly.
    return 1;
}

int particle::Processor::getCurrentProgram() {
    // TODO: ADD PROGRAMS
    return 0;
}

void particle::Processor::setCurrentProgram(int index) {
    // TODO: ADD PROGRAMS
}

const juce::String particle::Processor::getProgramName(int index) {
    // TODO: ADD PROGRAMS
    return {};
}

void particle::Processor::changeProgramName(int index, const juce::String &newName) {}

void particle::Processor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    size_t numInputChannels = getTotalNumInputChannels() > nodeProcessor.getNumInputChannels()
                                      ? getTotalNumInputChannels()
                                      : nodeProcessor.getNumInputChannels();
    size_t numOutputChannels = getTotalNumOutputChannels() > nodeProcessor.getNumOutputChannels()
                                       ? getTotalNumOutputChannels()
                                       : nodeProcessor.getNumOutputChannels();
    nodeProcessor.setInputSize(numInputChannels, samplesPerBlock);
    nodeProcessor.setOutputSize(numOutputChannels, samplesPerBlock);
    nodeProcessor.setSampleRate(sampleRate);
}

void particle::Processor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool particle::Processor::isBusesLayoutSupported(const BusesLayout &layouts) const {
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

void particle::Processor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    nodeProcessor.process(buffer, midiMessages);
}

void particle::Processor::processBlock(juce::AudioBuffer<double> &buffer, juce::MidiBuffer &midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    nodeProcessor.process(buffer, midiMessages);
}

bool particle::Processor::hasEditor() const {
    return true;
}

juce::AudioProcessorEditor *particle::Processor::createEditor() {
    auto *editor = new Editor(*this);
    if (wrapperType == wrapperType_Standalone) {
        if (juce::TopLevelWindow::getNumTopLevelWindows() == 1) {
            juce::DocumentWindow *w = dynamic_cast<juce::DocumentWindow *>(juce::TopLevelWindow::getTopLevelWindow(0));
            w->setResizable(true, false);
            // TODO: Clean up this code after you create standalone wrapper
            w->setTitleBarButtonsRequired(juce::DocumentWindow::allButtons, false);
            //w->setUsingNativeTitleBar(true);
            //w->setTitleBarButtonsRequired(juce::DocumentWindow::allButtons, true);
        }
    }
    view.getData().setAudioDeviceManager(getAudioDeviceManager());
    return editor;
}

void particle::Processor::getStateInformation(juce::MemoryBlock &destData) {
    // TODO: SAVE STATE
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void particle::Processor::setStateInformation(const void *data, int sizeInBytes) {
    // TODO: LOAD STATE
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioDeviceManager *particle::Processor::getAudioDeviceManager() {
    juce::StandalonePluginHolder *standalone = juce::StandalonePluginHolder::getInstance();
    return standalone != nullptr ? &standalone->deviceManager : nullptr;
}

dsp::NodeProcessor &particle::Processor::getNodeProcessor() {
    return nodeProcessor;
}

particle::View &particle::Processor::getView() {
    return view;
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new particle::Processor();
}
