#pragma once
#include "ELC.h"
#include <string>
#include <vector>

namespace ELC {
    // SFX - One-shot sounds (pew pew!)
    class Sound {
    public:
        ::Sound sound = {0};
        Sound() = default;
        Sound(const std::string& filepath);
        ~Sound();
        void Play();
        bool IsPlaying() const;
        void Stop();
        bool IsLoaded() const { return sound.frameCount > 0; }
    };
    
    // Music - Looping background tracks
    class Music {
    public:
        ::Music music = {0};
        Music() = default;
        Music(const std::string& filepath);
        ~Music();
        void Play();
        void Pause();
        void Resume();
        void Stop();
        void Update();
        void SetVolume(float volume);
        bool IsPlaying() const;
        bool IsLoaded() const { return music.frameCount > 0; }
    };
}
