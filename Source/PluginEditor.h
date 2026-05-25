#pragma once
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"
class VelvetAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    VelvetAudioProcessorEditor(VelvetAudioProcessor&);
    ~VelvetAudioProcessorEditor() override;
    void paint(juce::Graphics&) override;
    void resized() override;
private:
    VelvetAudioProcessor& processorRef;
    VelvetLookAndFeel lnf;
    juce::Slider knob_INPUT_GAIN;
    juce::Label lbl_INPUT_GAIN;
    juce::AudioProcessorValueTreeState::SliderAttachment att_INPUT_GAIN;
    juce::Slider knob_COMPRESSOR_THRESHOLD_JYKO;
    juce::Label lbl_COMPRESSOR_THRESHOLD_JYKO;
    juce::AudioProcessorValueTreeState::SliderAttachment att_COMPRESSOR_THRESHOLD_JYKO;
    juce::Slider knob_COMPRESSOR_RATIO_JYKO;
    juce::Label lbl_COMPRESSOR_RATIO_JYKO;
    juce::AudioProcessorValueTreeState::SliderAttachment att_COMPRESSOR_RATIO_JYKO;
    juce::Slider knob_COMPRESSOR_ATTACK_JYKO;
    juce::Label lbl_COMPRESSOR_ATTACK_JYKO;
    juce::AudioProcessorValueTreeState::SliderAttachment att_COMPRESSOR_ATTACK_JYKO;
    juce::Slider knob_COMPRESSOR_RELEASE_JYKO;
    juce::Label lbl_COMPRESSOR_RELEASE_JYKO;
    juce::AudioProcessorValueTreeState::SliderAttachment att_COMPRESSOR_RELEASE_JYKO;
    juce::Slider knob_COMPRESSOR_MAKEUP_JYKO;
    juce::Label lbl_COMPRESSOR_MAKEUP_JYKO;
    juce::AudioProcessorValueTreeState::SliderAttachment att_COMPRESSOR_MAKEUP_JYKO;
    juce::Slider knob_GAIN_GAIN_DB_94SG;
    juce::Label lbl_GAIN_GAIN_DB_94SG;
    juce::AudioProcessorValueTreeState::SliderAttachment att_GAIN_GAIN_DB_94SG;
    juce::Slider knob_REVERB_SIZE_20QI;
    juce::Label lbl_REVERB_SIZE_20QI;
    juce::AudioProcessorValueTreeState::SliderAttachment att_REVERB_SIZE_20QI;
    juce::Slider knob_REVERB_DAMP_20QI;
    juce::Label lbl_REVERB_DAMP_20QI;
    juce::AudioProcessorValueTreeState::SliderAttachment att_REVERB_DAMP_20QI;
    juce::Slider knob_REVERB_MIX_20QI;
    juce::Label lbl_REVERB_MIX_20QI;
    juce::AudioProcessorValueTreeState::SliderAttachment att_REVERB_MIX_20QI;
    juce::Slider knob_BITCRUSHER_BITS_9RFK;
    juce::Label lbl_BITCRUSHER_BITS_9RFK;
    juce::AudioProcessorValueTreeState::SliderAttachment att_BITCRUSHER_BITS_9RFK;
    juce::Slider knob_BITCRUSHER_RATEDIV_9RFK;
    juce::Label lbl_BITCRUSHER_RATEDIV_9RFK;
    juce::AudioProcessorValueTreeState::SliderAttachment att_BITCRUSHER_RATEDIV_9RFK;
    juce::Slider knob_BITCRUSHER_MIX_9RFK;
    juce::Label lbl_BITCRUSHER_MIX_9RFK;
    juce::AudioProcessorValueTreeState::SliderAttachment att_BITCRUSHER_MIX_9RFK;
    juce::Slider knob_FLANGER_RATE_S1OO;
    juce::Label lbl_FLANGER_RATE_S1OO;
    juce::AudioProcessorValueTreeState::SliderAttachment att_FLANGER_RATE_S1OO;
    juce::Slider knob_FLANGER_DEPTH_S1OO;
    juce::Label lbl_FLANGER_DEPTH_S1OO;
    juce::AudioProcessorValueTreeState::SliderAttachment att_FLANGER_DEPTH_S1OO;
    juce::Slider knob_FLANGER_FEEDBACK_S1OO;
    juce::Label lbl_FLANGER_FEEDBACK_S1OO;
    juce::AudioProcessorValueTreeState::SliderAttachment att_FLANGER_FEEDBACK_S1OO;
    juce::Slider knob_FLANGER_MIX_S1OO;
    juce::Label lbl_FLANGER_MIX_S1OO;
    juce::AudioProcessorValueTreeState::SliderAttachment att_FLANGER_MIX_S1OO;
    juce::Slider knob_EXCITER_FREQ_8PKN;
    juce::Label lbl_EXCITER_FREQ_8PKN;
    juce::AudioProcessorValueTreeState::SliderAttachment att_EXCITER_FREQ_8PKN;
    juce::Slider knob_EXCITER_DRIVE_8PKN;
    juce::Label lbl_EXCITER_DRIVE_8PKN;
    juce::AudioProcessorValueTreeState::SliderAttachment att_EXCITER_DRIVE_8PKN;
    juce::Slider knob_EXCITER_MIX_8PKN;
    juce::Label lbl_EXCITER_MIX_8PKN;
    juce::AudioProcessorValueTreeState::SliderAttachment att_EXCITER_MIX_8PKN;
    juce::Slider knob_OUTPUT_GAIN;
    juce::Label lbl_OUTPUT_GAIN;
    juce::AudioProcessorValueTreeState::SliderAttachment att_OUTPUT_GAIN;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VelvetAudioProcessorEditor)
};
