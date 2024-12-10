
#ifndef ENGINE_STYLEMANAGER_H
#define ENGINE_STYLEMANAGER_H


#include <string>

class StyleManager {
public:
    StyleManager(const std::string& stylePath);

    void LoadStyle();
    void SaveStyle();
private:
    std::string stylePath;
};


#endif //ENGINE_STYLEMANAGER_H
