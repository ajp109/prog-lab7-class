#include "mbed.h"

class Flasher {

    DigitalOut pin_;
    Ticker ticker_;
    Timeout timeout_;
    chrono::milliseconds onTime_;
    chrono::milliseconds offTime_;

    void on() {
        pin_ = true;
        timeout_.attach(callback(this, &Flasher::off), onTime_);
    }

    void off() {
        pin_ = false;
    }

public:

    Flasher(PinName pin, chrono::milliseconds const & onTime, chrono::milliseconds const & offTime) :
        pin_(pin), onTime_(onTime), offTime_(offTime) { }

    void start() {
        ticker_.attach(callback(this, &Flasher::on), onTime_ + offTime_);
    }

    void stop() {
        ticker_.detach();
    }

};



Flasher green(D2, 500ms, 2500ms);
Flasher red(D3, 300ms, 1700ms);

int main()
{
    green.start();
    red.start();
    // This while loop is important - it's there to stop the program from ending
    while (true);
}
