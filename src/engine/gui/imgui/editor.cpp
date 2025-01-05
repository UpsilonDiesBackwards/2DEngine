
#include "engine/gui/imgui/editor.h"

Editor::Editor() {
    topBar = new TopBar;
    editorViews = new EditorViews;
    sceneHeirarchy = new SceneHierarchy;
}

void Editor::Render() {
    // Persistent UI
    topBar->Show();

    if (showEditorViews) {
        editorViews->Show();
    }

    if (showSceneHeirarchy) {
        sceneHeirarchy->Show();
    }
}
