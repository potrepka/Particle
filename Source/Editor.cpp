#include "Editor.h"

particle::Editor::Editor(Processor &p)
        : AudioProcessorEditor(&p)
        , processor(p) {
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

particle::Editor::~Editor() {
    openGLContext.detach();
}

void particle::Editor::paint(juce::Graphics &g) {}

void particle::Editor::resized() {}

void particle::Editor::newOpenGLContextCreated() {
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

void particle::Editor::renderOpenGL() {
    ImGui_ImplOpenGL3_NewFrame();

    ImGui_ImplJUCE_NewFrame(this);

    ImGuiIO &io = ImGui::GetIO();
    const float scale = static_cast<float>(openGLContext.getRenderingScale());
    io.DisplayFramebufferScale = ImVec2(scale, scale);

    ImGui::NewFrame();

    processor.getRootView().draw();

    ImGui::Render();

    glViewport(0, 0, getScreenBounds().getWidth(), getScreenBounds().getHeight());
    glClearColor(processor.getRootView().getData().getStyle().backgroundColor.x,
                 processor.getRootView().getData().getStyle().backgroundColor.y,
                 processor.getRootView().getData().getStyle().backgroundColor.z,
                 processor.getRootView().getData().getStyle().backgroundColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void particle::Editor::openGLContextClosing() {
    ImGui_ImplOpenGL3_Shutdown();
}

bool particle::Editor::keyPressed(const juce::KeyPress& key, Component* originatingComponent) {
    return ImGui_ImplJUCE_HandleKeyPressed(key, originatingComponent);
}

bool particle::Editor::keyStateChanged(bool isKeyDown, Component *originatingComponent) {
    return ImGui_ImplJUCE_HandleKeyStateChanged(isKeyDown, originatingComponent);
}

void particle::Editor::mouseMove(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseMove(event);
}

void particle::Editor::mouseEnter(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseEnter(event);
}

void particle::Editor::mouseExit(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseExit(event);
}

void particle::Editor::mouseDown(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseDown(event);
}

void particle::Editor::mouseDrag(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseDrag(event);
}

void particle::Editor::mouseUp(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseUp(event);
}

void particle::Editor::mouseDoubleClick(const juce::MouseEvent &event) {
    ImGui_ImplJUCE_HandleMouseDoubleClick(event);
}

void particle::Editor::mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) {
    ImGui_ImplJUCE_HandleMouseWheelMove(event, wheel);
}

void particle::Editor::mouseMagnify(const juce::MouseEvent &event, float scaleFactor) {
    ImGui_ImplJUCE_HandleMouseMagnify(event, scaleFactor);
}
