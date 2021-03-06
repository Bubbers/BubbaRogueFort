#ifndef LEVELFILEREADER_H
#define LEVELFILEREADER_H

#include <Scene.h>
#include "unordered_map"
#include "string"
#include "../scenes/RogueFortScene.h"

class LevelFileReader {
public:
    LevelFileReader();

    static Scene* read(const std::string& filename, RogueFortScene *rogueFortScene);

private:
    static void parseObjects(const std::vector<std::vector<std::string>> &lines,
                          std::unordered_map<std::string, std::shared_ptr<Mesh>> &meshMap,
                          Scene* scene, RogueFortScene *rogueFortScene);

    static std::vector<std::string> words(const std::string& str);
};

#endif // LEVELFILEREADER_H
