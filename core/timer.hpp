#pragma once
#include <chrono>
#include <atomic>
#include <thread>
class Timer{
private:
        std::atomic<int>countToRelax{0};
        std::atomic<int> seconds{1500};
        std::atomic<bool>isRunning{false};
        std::atomic<bool>isRelaxed{false};

        std::thread timerThread;

        void run(){
            while(isRunning.load()){
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                if (seconds.load() > 0){
                    seconds--;
                }
                else{
                    if (!isRelaxed.load()){
                        countToRelax++;
                        isRelaxed.store(true);
                        seconds.store(300);
                    }
                    else{
                        isRelaxed.store(false);
                        seconds.store(1500);
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

};

