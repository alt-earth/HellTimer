#pragma once
#include <chrono>
#include <atomic>
#include <thread>
#include <string>
#include "audioEngine.hpp"

class Timer{
private:
        std::atomic<int>countToRelax{0};
        std::atomic<int> seconds{1500};
        std::atomic<bool>isRunning{false};
        std::atomic<bool>isRelaxed{false};

        std::thread timerThread;

        AudioEngine audio;

        void run(){
            while(isRunning.load()){
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                if (seconds.load() > 0){
                    seconds--;
                }
                else{
                    if (!isRelaxed.load()){
                        countToRelax++;

                        if (countToRelax.load() >= 4){
                            seconds.store(1200);
                            countToRelax.store(0);
                        }
                        else{
                            seconds.store(300);
                        }
                        isRelaxed.store(true);
                        audio.play();
                    }
                    else{
                        isRelaxed.store(false);
                        seconds.store(1500);
                        audio.play();
                    }
                }
            }
        }
public:
    ~Timer(){
        stop();
    }

    void start(){
        if (!isRunning.load()){
            isRunning.store(true);
            audio.play();
            timerThread = std::thread(&Timer::run, this);
        }
    }

    void stop(){
        if(isRunning.load()){
            isRunning.store(false);
            if(timerThread.joinable()){
                timerThread.join();
            }
        }
    }

    int getSeconds() const {
        return seconds.load() % 60;
    }
    int getMinutes() const {
        return seconds.load() / 60;
    }
    std::string getStatus() const {
        return isRelaxed ? "Relax" : "Work";
    }
    bool isStarted() const {
        return isRunning;
    }
    int getCountToRelax() const {
        return countToRelax.load();
    }

};

