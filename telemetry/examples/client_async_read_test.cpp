#include "Client.hpp"
#include "MSP.hpp"

#include <iostream>

int main( int argc, char** argv ){
    const std::string device = argc > 1 ? argv[1] : "/dev/ttyACM0";
    const int baudRate = 115200;
    msp_telemetry::Client client;
    msp_telemetry::FirmwareVariant fwVariant = msp_telemetry::FirmwareVariant::INAV;
    client.setVariant( fwVariant );
    client.start( device, baudRate );

    const std::function<void(const msp_telemetry::RawImu&)> cbIMU =
        [](const msp_telemetry::RawImu& imu) {
            std::cout << imu;
            std::cout << msp_telemetry::ImuCI(
                imu, 512.0, 1.0 / 4.096, 0.92f / 10.0f, 9.80665f);
        };
    client.subscribe( cbIMU, 0.1 );

    const std::function< void( msp_telemetry::Rc const& rc )> cbRC = 
    [](msp_telemetry::Rc const& rc ){
        std::cout <<  rc << std::endl;
    };
    client.subscribe( cbRC, 0.1 );


    const std::function<void( msp_telemetry::Altitude const& a )> cbAlt = 
    [] ( msp_telemetry::Altitude const& a ){
        std::cout << a;
    };
    client.subscribe( cbAlt, 0.1 );
    std::cin.get();
    client.stop();
    return 0;
}