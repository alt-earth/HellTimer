#include "audioEngine.hpp"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

AudioEngine::AudioEngine() {
    engine = new ma_engine();
    ma_result result = ma_engine_init(nullptr, engine);
    if (result == MA_SUCCESS) {
        m_isInitialized = true;
    }
}

AudioEngine::~AudioEngine() {
    if (m_isInitialized) {
        ma_engine_uninit(engine);
    }
    delete engine;
}

void AudioEngine::play() const {
    if (!m_isInitialized) return;
    ma_engine_play_sound(engine, "assets/sound/relax.wav", nullptr);
}
