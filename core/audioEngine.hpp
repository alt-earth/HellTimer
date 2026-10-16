#pragma once

struct ma_engine;

class AudioEngine {
private:
    ma_engine* engine;
    bool m_isInitialized = false;

public:
    AudioEngine();
    ~AudioEngine();

    void play() const;

    AudioEngine(const AudioEngine&) = delete;
    AudioEngine& operator=(const AudioEngine&) = delete;
};
