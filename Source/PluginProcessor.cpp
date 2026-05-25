#include "PluginProcessor.h"
#include "PluginEditor.h"
VelvetAudioProcessor::VelvetAudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input",juce::AudioChannelSet::stereo()).withOutput("Output",juce::AudioChannelSet::stereo())),
      apvts(*this,nullptr,"Parameters",createParameterLayout()) {}
VelvetAudioProcessor::~VelvetAudioProcessor() {}
juce::AudioProcessorValueTreeState::ParameterLayout VelvetAudioProcessor::createParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>("INPUT_GAIN","Input Gain",juce::NormalisableRange<float>(-24.0f,24.0f,0.01f),0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OUTPUT_GAIN","Output Gain",juce::NormalisableRange<float>(-24.0f,24.0f,0.01f),0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_THRESHOLD_JYKO","Compressor Threshold",juce::NormalisableRange<float>(-60.0f,0.0f,0.01f),-18.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_RATIO_JYKO","Compressor Ratio",juce::NormalisableRange<float>(1.0f,20.0f,0.1f),4.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_ATTACK_JYKO","Compressor Attack",juce::NormalisableRange<float>(0.1f,200.0f,0.01f),10.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_RELEASE_JYKO","Compressor Release",juce::NormalisableRange<float>(10.0f,2000.0f,0.01f),150.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_MAKEUP_JYKO","Compressor Makeup",juce::NormalisableRange<float>(0.0f,24.0f,0.01f),0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("GAIN_GAIN_DB_94SG","Gain Gain",juce::NormalisableRange<float>(-24.0f,24.0f,0.01f),0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERB_SIZE_20QI","Reverb Size",juce::NormalisableRange<float>(0.0f,100.0f,0.01f),60.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERB_DAMP_20QI","Reverb Damping",juce::NormalisableRange<float>(0.0f,100.0f,0.01f),40.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERB_MIX_20QI","Reverb Mix",juce::NormalisableRange<float>(0.0f,100.0f,0.01f),40.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("BITCRUSHER_BITS_9RFK","Bit Crush Bits",juce::NormalisableRange<float>(2.0f,16.0f,0.01f),8.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("BITCRUSHER_RATEDIV_9RFK","Bit Crush Rate Div",juce::NormalisableRange<float>(1.0f,32.0f,0.01f),4.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("BITCRUSHER_MIX_9RFK","Bit Crush Mix",juce::NormalisableRange<float>(0.0f,100.0f,0.01f),80.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("FLANGER_RATE_S1OO","Flanger Rate",juce::NormalisableRange<float>(0.1f,5.0f,1.0f,0.5f),0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("FLANGER_DEPTH_S1OO","Flanger Depth",juce::NormalisableRange<float>(1.0f,15.0f,0.01f),5.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("FLANGER_FEEDBACK_S1OO","Flanger Feedback",juce::NormalisableRange<float>(0.0f,90.0f,0.01f),50.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("FLANGER_MIX_S1OO","Flanger Mix",juce::NormalisableRange<float>(0.0f,100.0f,0.01f),50.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("EXCITER_FREQ_8PKN","Exciter Freq",juce::NormalisableRange<float>(1000.0f,16000.0f,1.0f,0.5f),5000.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("EXCITER_DRIVE_8PKN","Exciter Drive",juce::NormalisableRange<float>(0.0f,100.0f,0.01f),40.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("EXCITER_MIX_8PKN","Exciter Mix",juce::NormalisableRange<float>(0.0f,100.0f,0.01f),40.0f));
    return layout;
}
void VelvetAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    currentSampleRate = sampleRate;
    juce::dsp::ProcessSpec spec;
    spec.sampleRate=(uint32_t)sampleRate; spec.maximumBlockSize=(uint32_t)samplesPerBlock; spec.numChannels=(uint32_t)getTotalNumOutputChannels();
    inputGainDsp.prepare(spec); inputGainDsp.setGainDecibels(0.0f);
    outputGainDsp.prepare(spec); outputGainDsp.setGainDecibels(0.0f);
    comp_JYKO.prepare(spec); comp_JYKO.setThreshold(-18.0f); comp_JYKO.setRatio(4.0f); comp_JYKO.setAttack(10.0f); comp_JYKO.setRelease(150.0f); compMakeup_JYKO.prepare(spec); compMakeup_JYKO.setGainDecibels(0.0f);
    gain_94SG.prepare(spec); gain_94SG.setGainDecibels(0.0f);
    { juce::dsp::Reverb::Parameters rp; rp.roomSize=0.6f; rp.damping=0.4f; rp.wetLevel=0.4f; rp.dryLevel=0.6f; reverb_20QI.setParameters(rp); reverb_20QI.prepare(spec); }
    // bitcrusher_9RFK no prepare
    flanger_S1OO.prepare(spec); flanger_S1OO.setRate(0.5f); flanger_S1OO.setDepth(0.05f); flanger_S1OO.setCentreDelay(3.0f); flanger_S1OO.setFeedback(0.5f); flanger_S1OO.setMix(1.0f);
    flangerMix_S1OO.prepare(spec); flangerMix_S1OO.setWetMixProportion(0.5f);
    *excHp_8PKN.state=*juce::dsp::IIR::Coefficients<float>::makeHighPass(spec.sampleRate,5000.0f,0.707); excHp_8PKN.prepare(spec); excMix_8PKN.prepare(spec); excMix_8PKN.setWetMixProportion(0.4f);
}
void VelvetAudioProcessor::releaseResources() {}
bool VelvetAudioProcessor::isBusesLayoutSupported(const BusesLayout& l) const {
    return l.getMainOutputChannelSet()==juce::AudioChannelSet::stereo()&&l.getMainInputChannelSet()==juce::AudioChannelSet::stereo();
}
void VelvetAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    juce::ScopedNoDenormals noDenormals;
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    inputGainDsp.setGainDecibels(*apvts.getRawParameterValue("INPUT_GAIN")); inputGainDsp.process(context);
    comp_JYKO.setThreshold(*apvts.getRawParameterValue("COMPRESSOR_THRESHOLD_JYKO")); comp_JYKO.setRatio(*apvts.getRawParameterValue("COMPRESSOR_RATIO_JYKO")); comp_JYKO.setAttack(*apvts.getRawParameterValue("COMPRESSOR_ATTACK_JYKO")); comp_JYKO.setRelease(*apvts.getRawParameterValue("COMPRESSOR_RELEASE_JYKO")); compMakeup_JYKO.setGainDecibels(*apvts.getRawParameterValue("COMPRESSOR_MAKEUP_JYKO")); comp_JYKO.process(context); compMakeup_JYKO.process(context);
    gain_94SG.setGainDecibels(*apvts.getRawParameterValue("GAIN_GAIN_DB_94SG")); gain_94SG.process(context);
    { juce::dsp::Reverb::Parameters rp; rp.roomSize=*apvts.getRawParameterValue("REVERB_SIZE_20QI")/100.0f; rp.damping=*apvts.getRawParameterValue("REVERB_DAMP_20QI")/100.0f; float rvMix=*apvts.getRawParameterValue("REVERB_MIX_20QI")/100.0f; rp.wetLevel=rvMix; rp.dryLevel=1.0f-rvMix; reverb_20QI.setParameters(rp); reverb_20QI.process(context); }
    { float bcBits=juce::jmax(1.0f,(float)*apvts.getRawParameterValue("BITCRUSHER_BITS_9RFK")); float bcLvl=std::pow(2.0f,bcBits)-1.0f; if(bcLvl<1.0f)bcLvl=1.0f; for(int ch=0;ch<buffer.getNumChannels();++ch){auto*d=buffer.getWritePointer(ch);for(int i=0;i<buffer.getNumSamples();++i){d[i]=std::round(d[i]*bcLvl)/bcLvl;}} }
    { flangerMix_S1OO.pushDrySamples(block); flanger_S1OO.setRate(*apvts.getRawParameterValue("FLANGER_RATE_S1OO")); flanger_S1OO.setDepth(*apvts.getRawParameterValue("FLANGER_DEPTH_S1OO")/100.0f); flanger_S1OO.setFeedback(*apvts.getRawParameterValue("FLANGER_FEEDBACK_S1OO")/100.0f); flanger_S1OO.process(context); flangerMix_S1OO.setWetMixProportion(*apvts.getRawParameterValue("FLANGER_MIX_S1OO")/100.0f); flangerMix_S1OO.mixWetSamples(block); }
    { excMix_8PKN.pushDrySamples(block); *excHp_8PKN.state=*juce::dsp::IIR::Coefficients<float>::makeHighPass(currentSampleRate,juce::jmax(200.0f,(float)*apvts.getRawParameterValue("EXCITER_FREQ_8PKN")),0.707f); excHp_8PKN.process(context); float excDrv=*apvts.getRawParameterValue("EXCITER_DRIVE_8PKN")/100.0f*3.0f+1.0f; for(int ch=0;ch<buffer.getNumChannels();++ch){auto*d=buffer.getWritePointer(ch);for(int i=0;i<buffer.getNumSamples();++i){d[i]=d[i]-std::tanh(d[i]*excDrv)/excDrv;}} excMix_8PKN.setWetMixProportion(*apvts.getRawParameterValue("EXCITER_MIX_8PKN")/100.0f); excMix_8PKN.mixWetSamples(block); }
    outputGainDsp.setGainDecibels(*apvts.getRawParameterValue("OUTPUT_GAIN")); outputGainDsp.process(context);
}
void VelvetAudioProcessor::getStateInformation(juce::MemoryBlock& d) {
    auto s=apvts.copyState(); std::unique_ptr<juce::XmlElement> xml(s.createXml()); copyXmlToBinary(*xml,d);
}
void VelvetAudioProcessor::setStateInformation(const void* d,int sz) {
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(d,sz));
    if(xml&&xml->hasTagName(apvts.state.getType())) apvts.replaceState(juce::ValueTree::fromXml(*xml));
}
juce::AudioProcessorEditor* VelvetAudioProcessor::createEditor() { return new VelvetAudioProcessorEditor(*this); }
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new VelvetAudioProcessor(); }
