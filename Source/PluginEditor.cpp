#include "PluginEditor.h"

ParticleAudioProcessorEditor::ParticleAudioProcessorEditor(ParticleAudioProcessor &p)
        : AudioProcessorEditor(&p)
        , audioProcessor(p) {
    setOpaque(true);
    setResizable(true, false);
    setSize(1280, 720);

    addKeyListener(this);
    setWantsKeyboardFocus(true);

    openGLContext.setRenderer(this);
    openGLContext.attachTo(*this);
    openGLContext.setContinuousRepainting(true);
    openGLContext.setOpenGLVersionRequired(juce::OpenGLContext::openGL3_2);
}

ParticleAudioProcessorEditor::~ParticleAudioProcessorEditor() {
    openGLContext.detach();
}

void ParticleAudioProcessorEditor::paint(juce::Graphics &g) {}

void ParticleAudioProcessorEditor::resized() {}

void ParticleAudioProcessorEditor::newOpenGLContextCreated() {
#if !defined(IMGUI_IMPL_OPENGL_ES2) && !defined(IMGUI_IMPL_OPENGL_ES3)
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    gl3wInit();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    glewInit();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    gladLoadGL();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
    gladLoaderLoadGL();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
    glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
    glbinding::initialize();
#endif
#endif

    std::cout << "GL VERSION: " << glGetString(GL_VERSION) << std::endl;

    ImGui_ImplOpenGL3_Init();
}

void ParticleAudioProcessorEditor::renderOpenGL() {
    ImGui_ImplOpenGL3_NewFrame();

    ImGui_ImplJUCE_NewFrame(this);

    ImGuiIO &io = ImGui::GetIO();
    const float scale = static_cast<float>(openGLContext.getRenderingScale());
    io.DisplayFramebufferScale = ImVec2(scale, scale);

    ImGui::NewFrame();

    audioProcessor.getRootView().draw();

    ImGui::Render();

    glViewport(0, 0, getScreenBounds().getWidth(), getScreenBounds().getHeight());
    glClearColor(audioProcessor.getRootView().getData().getStyle().backgroundColor.x,
                 audioProcessor.getRootView().getData().getStyle().backgroundColor.y,
                 audioProcessor.getRootView().getData().getStyle().backgroundColor.z,
                 audioProcessor.getRootView().getData().getStyle().backgroundColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ParticleAudioProcessorEditor::openGLContextClosing() {
    ImGui_ImplOpenGL3_Shutdown();
}

bool ParticleAudioProcessorEditor::keyPressed(const juce::KeyPress& key, Component* originatingComponent) {
    return ImGui_ImplJUCE_HandleKeyPressed(key, originatingComponent);
}

bool ParticleAudioProcessorEditor::keyStateChanged(bool isKeyDown, Component *originatingComponent) {
    return ImGui_ImplJUCE_HandleKeyStateChanged(isKeyDown, originatingComponent);
}

void ParticleAudioProcessorEditor::mouseMove(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseMove(event);
}

void ParticleAudioProcessorEditor::mouseEnter(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseEnter(event);
}

void ParticleAudioProcessorEditor::mouseExit(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseExit(event);
}

void ParticleAudioProcessorEditor::mouseDown(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseDown(event);
}

void ParticleAudioProcessorEditor::mouseDrag(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseDrag(event);
}

void ParticleAudioProcessorEditor::mouseUp(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseUp(event);
}

void ParticleAudioProcessorEditor::mouseDoubleClick(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseDoubleClick(event);
}

void ParticleAudioProcessorEditor::mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) {
    ImGui_ImplJUCE_HandleMouseWheelMove(event, wheel);
}

void ParticleAudioProcessorEditor::mouseMagnify(const juce::MouseEvent &event, float scaleFactor) {
    ImGui_ImplJUCE_HandleMouseMagnify(event, scaleFactor);
}
