#include "View.h"

particle::View::View(juce::AudioProcessor *audioProcessor,
                             juce::AudioDeviceManager *audioDeviceManager,
                             dsp::NodeProcessor *nodeProcessor)
        : data(audioProcessor, audioDeviceManager, nodeProcessor)
        , projectContainer(std::make_shared<dsp::Node>())
        , nodeGraph(std::make_shared<NodeGraph>(data, "Node Graph", projectContainer))
        , audioSettings(std::make_shared<AudioSettings>(data))
        , status(std::make_shared<Status>(data)) {
    // TODO: build a better project system, don't forget to update initializations above
    nodeProcessor->getNodes().push_back(projectContainer);
    
    frames.push_back(nodeGraph);
    frames.push_back(audioSettings);
    frames.push_back(status);
    for (const auto& frame : frames) {
        frame->show();
    }
}

particle::Data &particle::View::getData() {
    return data;
}

void particle::View::setup() {
    // TODO: persist theme between runs
    data.getStyle().light();

    // TODO: Remove font chooser
    ImGuiIO &io = ImGui::GetIO();

    int numFonts = 3;

    ttf.resize(numFonts);
    ttfSize.resize(numFonts);

    ttf[0] = BinaryData::OxygenMonoRegular_ttf;
    ttfSize[0] = BinaryData::OxygenMonoRegular_ttfSize;

    ttf[1] = BinaryData::FiraCodeRegular_ttf;
    ttfSize[1] = BinaryData::FiraCodeRegular_ttfSize;

    ttf[2] = BinaryData::DMMonoRegular_ttf;
    ttfSize[2] = BinaryData::DMMonoRegular_ttfSize;

    fontData.resize(numFonts);
    font.resize(numFonts);
    for (int i = 0; i < numFonts; ++i) {
        fontData[i] = IM_ALLOC(ttfSize[i]);
        std::memcpy(fontData[i], ttf[i], ttfSize[i]);
        font[i] = io.Fonts->AddFontFromMemoryTTF(fontData[i], ttfSize[i], 12.0f * 1.2f);
    }
}

void particle::View::draw() {
    // TODO: Remove demo window code
    //static bool show_demo_window = true;
    //if (show_demo_window) {
    //ImGui::ShowDemoWindow(&show_demo_window);
    //}

    ImGuiIO &io = ImGui::GetIO();

    if (io.KeyCtrl) {
        if (ImGui::IsKeyPressed('Z') && data.hasUndo()) {
            data.undo();
        } else if (ImGui::IsKeyPressed('Y') && data.hasRedo()) {
            data.redo();
        }
    }

    // TODO: Remove font chooser
    static const char *current_item = NULL;
    static int current_index = 0;

    // TODO: Make const font variable
    ImGui::PushFont(font[current_index]);

    // TODO: Put this into Style class
    ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, IM_COL32(0, 0, 0, 0));
    ImGui::DockSpaceOverViewport();
    ImGui::PopStyleColor();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::MenuItem("New Project");
            ImGui::MenuItem("Open Project");
            ImGui::MenuItem("Save Project");
            ImGui::MenuItem("Duplicate Project");
            ImGui::Separator();
            ImGui::MenuItem("Close Project");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "Ctrl+Z", false, data.hasUndo())) {
                data.undo();
            }
            if (ImGui::MenuItem("Redo", "Ctrl+Y", false, data.hasRedo())) {
                data.redo();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {
            ImGui::MenuItem("Node Tree");
            ImGui::MenuItem("Node Graph", NULL, &nodeGraph->isVisible());
            ImGui::MenuItem("Node Inspector");
            ImGui::Separator();
            ImGui::MenuItem("Theme Editor");
            ImGui::Separator();
            ImGui::MenuItem("Audio Settings", NULL, &audioSettings->isVisible());
            ImGui::MenuItem("MIDI Settings");
            ImGui::MenuItem("OSC Settings");
            ImGui::Separator();
            ImGui::MenuItem("Status", NULL, &status->isVisible());
            ImGui::EndMenu();
        }
        // TODO: Remove this menu and replace with theme editor
        if (ImGui::BeginMenu("Theme")) {
            if (ImGui::MenuItem("Light", NULL, false, true)) {
                data.getStyle().light(1.0f);
            }
            if (ImGui::MenuItem("Dark", NULL, false, true)) {
                data.getStyle().dark(1.0f);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // TODO: Remove testing code to display working directory
    //ImGui::Begin("Current Working Directory");
    //ImGui::Text("%s", juce::File::getCurrentWorkingDirectory().getFullPathName());
    //ImGui::End();

    // TODO: Remove font chooser
    ImGui::Begin("Font");
    const char *items[] = {"Oxygen Mono", "Fira Code", "DM Mono"};
    if (ImGui::BeginCombo("##combo", current_item)) {
        for (int i = 0; i < IM_ARRAYSIZE(items); ++i) {
            bool is_selected = (current_item == items[i]);
            if (ImGui::Selectable(items[i], is_selected)) {
                current_item = items[i];
                current_index = i;
            }
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
    ImGui::End();

    for (const auto& frame : frames) {
        frame->draw();
    }

    ImGui::PopFont();
}
