#pragma once

#include <functional>

class Timer {
public:
    Timer() = default;
    ~Timer() = default;

    void start();
    void stop();
    void reset();
    void setWaitTime(float val);
    void setOneshot(bool flag);
    void setTimeoutCallback(const std::function<void()>& on_timeout);
    void pause();
    void resume();
    void onUpdate(float dt);

private:
    float _pass_time = 0.0f;
    float _wait_time = 0.0f;
    bool _oneshot = false;
    bool _paused = false;
    bool _shotted = false;
    std::function<void()> on_timeout;
};
