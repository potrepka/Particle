#include "TimeSignature.h"

dsp::TimeSignature::TimeSignature(juce::AudioProcessor *audioProcessor)
        : numerator(std::make_shared<Output>(Type::INTEGER))
        , denominator(std::make_shared<Output>(Type::INTEGER))
        , audioProcessor(audioProcessor) {}

std::shared_ptr<dsp::Output> dsp::TimeSignature::getNumerator() const {
    return numerator;
}

std::shared_ptr<dsp::Output> dsp::TimeSignature::getDenominator() const {
    return denominator;
}

void dsp::TimeSignature::processNoLock() {
    if (audioProcessor) {
        juce::AudioPlayHead::CurrentPositionInfo info;
        audioProcessor->getPlayHead()->getCurrentPosition(info);
        getNumerator()->getWrapper().fill(info.timeSigNumerator);
        getDenominator()->getWrapper().fill(info.timeSigDenominator);
    }
}
