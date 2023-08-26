#pragma once

// std
#include <functional>
#include <memory>

// project
#include "Message.hpp"
#include "PeriodicTimer.hpp"

namespace msp_telemetry{
    class SubscriptionBase{
    protected:
        std::unique_ptr<PeriodicTimer> timer_;  

    public:
        SubscriptionBase() {}

        virtual ~SubscriptionBase() {}

        virtual void decode(msp_telemetry::ByteVector& data) const = 0;

        virtual void makeRequest() const = 0;

        virtual void handleResponse() const = 0;

        virtual const Message& getMsgObject() const = 0;

        /**
        * @brief Checks to see if the subscription fires automatically
        * @returns True if the request happens automatically
        */
        bool isAutomatic() const {
            return hasTimer() && (timer_->getPeriod() > 0.0);
        }

        /**
        * @brief Checks to see if the timer has been created
        * @returns True if there is a timer
        */
        bool hasTimer() const { return timer_ ? true : false; }

        /**
        * @brief Start the timer for automatic execution
        * @returns True if the timer starts successfully
        */
        bool start() const { return this->timer_->start(); }

        /**
        * @brief Stop the timer's automatic execution
        * @returns True if the timer stops successfully
        */
        bool stop() const { return this->timer_->stop(); }

        void setTimerPeriod(const double& period_seconds) {
            if(timer_) {
                timer_->setPeriod(period_seconds);
            }
            else if(period_seconds > 0.0) {
                timer_ = std::unique_ptr<PeriodicTimer>(new PeriodicTimer(
                    std::bind(&SubscriptionBase::makeRequest, this),
                    period_seconds));
                this->timer_->start();
            }
        }

        void setTimerFrequency(const double& rate_hz) {
            if(timer_) {
                timer_->setPeriod(1.0 / rate_hz);
            }
            else if(rate_hz > 0.0) {
                timer_ = std::unique_ptr<PeriodicTimer>(new PeriodicTimer(
                    std::bind(&SubscriptionBase::makeRequest, this),
                    1.0 / rate_hz));
                this->timer_->start();
            }
        }
    };

    template<typename MsgT>
    class Subscription : public SubscriptionBase{
    public:// == TYPES ==
        using CallbackT = std::function<void(const MsgT&)> ;
        using CallbackM =  std::function<void(const Message&)>;

    private:
        CallbackT recvCallback_;
        CallbackM sendCallback_;
        std::unique_ptr<MsgT> ioObject_;

    public:// == CTOR ==
        Subscription( CallbackT const& recvCb, CallbackM const& sendCb, std::unique_ptr< MsgT >&& ioObj, const double period = 0.0 )
        : recvCallback_(recvCb),
        sendCallback_(sendCb),
        ioObject_(std::move(ioObj)) {
            if(period > 0.0) {
                timer_ = std::unique_ptr<PeriodicTimer>(new PeriodicTimer(
                    std::bind(&Subscription<MsgT>::makeRequest, this), period));
                timer_->start();
            }
        }

    public:
        virtual void decode(ByteVector& data) const override{
            ioObject_->decode( data );
            recvCallback_( *ioObject_ );
        }

        void setIOObject( std::unique_ptr< MsgT >&& ioObj ){
            ioObject_ = std::move( ioObj );
        }

        const MsgT& getIoObject() const { return *ioObject_; }

        void setReceiveCallback(const CallbackT& recv_callback) const {
            recvCallback_ = recv_callback;
        }

        virtual void handleResponse() const override {
            if(recvCallback_) recvCallback_(*ioObject_);
        }

        void setSendCallback(const CallbackM& send_callback) const {
            sendCallback_ = send_callback;
        }

        /**
        * @brief Calls the send callback if it exists
        */
        virtual void makeRequest() const override {
            if(sendCallback_) sendCallback_(*ioObject_);
        }

           virtual const Message& getMsgObject() const override {
                return *ioObject_;
            }

    };
}