#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/binding/MusicDownloadManager.hpp>
#include <Geode/binding/SongInfoObject.hpp>
#include <Geode/binding/LevelTools.hpp>
#include "Toast.hpp"

using namespace geode::prelude;

class $modify(CustomPlayLayer, PlayLayer) {
    void onEnterTransitionDidFinish() {
        PlayLayer::onEnterTransitionDidFinish();

        if (!m_level) return;

        std::string songName = "";
        std::string artistName = "";

        if (m_level->m_songID > 0) {
            auto mdm = MusicDownloadManager::sharedState();
            if (auto songInfo = mdm->getSongInfoObject(m_level->m_songID)) {
                songName = songInfo->m_songName;
                artistName = songInfo->m_artistName;
            } else {
                songName = m_level->getAudioFileName();
            }
        } else {
            int audioID = m_level->m_audioTrack;
            
            songName = LevelTools::getAudioTitle(audioID);
            
            int artistID = LevelTools::artistForAudio(audioID);
            artistName = LevelTools::nameForArtist(artistID);
        }

        if (songName.empty()) {
            songName = m_level->m_levelName;
        }
        if (artistName.empty()) {
            artistName = "Unknown Artist";
        }

        if (auto toast = Toast::create(songName, artistName)) {
            this->addChild(toast, 100);
            toast->animate();
        }
    }
};