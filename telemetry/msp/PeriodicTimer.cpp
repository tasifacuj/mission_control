#include "PeriodicTimer.hpp"

namespace msp_telemetry{

PeriodicTimer::PeriodicTimer( std::function<void()> f, double periodSec )
: funct_( f )
, periodUS_( std::chrono::duration< size_t, std::micro >( size_t( periodSec * 1e6 ) ) )
{}

PeriodicTimer::~PeriodicTimer(){
    stop();
}

bool PeriodicTimer::start(){
    if( !( periodUS_.count() > 0 ) )
        return false;

    if( running_.test_and_set() )
        return false;

    mutex_timer_.lock();

    thrd_ = std::thread( [ this ](){
        tstart_ = std::chrono::steady_clock::now();

        while( true ){
            funct_();
            tstart_ += periodUS_;

            if( mutex_timer_.try_lock_until( tstart_ ) ){
                // gets here if lock was acquired (means someone called stop and
                // manually unlocked the mutex)
                mutex_timer_.unlock();
                break;
            }
        }
    } );

    return true;
}

bool PeriodicTimer::stop(){
    bool rc = false;

    if( running_.test_and_set() ){
        mutex_timer_.unlock();

        if( thrd_.joinable() )
            thrd_.join();

        rc = true;
    }

    running_.clear();
    return rc;
}

void PeriodicTimer::setPeriod( double periodSec ){
    stop();
    std::chrono::duration< size_t, std::micro >( size_t( periodSec * 1e6 ) );
    start();
}

}// namespace msp_telemetry