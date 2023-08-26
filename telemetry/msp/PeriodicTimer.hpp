#pragma once
#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>


namespace msp_telemetry{
    class PeriodicTimer{
        std::thread thrd_;
        std::function<void()> funct_;
        std::chrono::duration< size_t, std::micro >  periodUS_;
        std::timed_mutex mutex_timer_;
        std::chrono::steady_clock::time_point tstart_;
        std::atomic_flag running_ = ATOMIC_FLAG_INIT;

    public:
        PeriodicTimer( std::function<void()> f, double periodSec );
        
        ~PeriodicTimer();
        
        bool start();
        
        bool stop();
        
        double getPeriod()const{
            return periodUS_.count() / 1.e6;
        }

        void setPeriod( double periodSec );
    };
}// namespace msp_telemetry