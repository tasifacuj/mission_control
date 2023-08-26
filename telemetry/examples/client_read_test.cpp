#include <Client.hpp>
#include <iostream>
#include "MSP.hpp"

int main( int argc, char** argv ){
    const std::string device = argc > 1 ? argv[1] : "/dev/ttyACM0";
    const int baudRate = 115200;
    msp_telemetry::Client client;
    msp_telemetry::FirmwareVariant fwVariant = msp_telemetry::FirmwareVariant::INAV;
    client.setVariant( fwVariant );
    client.start( device, baudRate );

    msp_telemetry::Status status(fwVariant);
    
    if(client.sendMessage(status, 1))
        std::cout << status;
    else
        std::cerr << "unsupported: " << size_t(status.id()) << std::endl;


    {
        msp_telemetry::RawImu rawImu(fwVariant);
        
        if(client.sendMessage(rawImu)) {
            std::cout << rawImu;
            msp_telemetry::ImuCI imuCI(
                rawImu, 
                512.0, 
                1.0 / 4.096, 
                0.92f / 10.0f, 
                9.80665f);
            std::cout << imuCI;
        }else{
            std::cerr << "unsupported: " << size_t(rawImu.id()) << std::endl;
        }   
    }

    {
        msp_telemetry::Rc rc(fwVariant);
        if(client.sendMessage(rc) == 1)
            std::cout << rc << std::endl;
        else
            std::cerr << "unsupported: " << size_t(rc.id()) << std::endl;

    }

    {
        msp_telemetry::Attitude attitude(fwVariant);
        if(client.sendMessage(attitude) == 1)
            std::cout << attitude;
        else
            std::cerr << "unsupported: " << size_t(attitude.id()) << std::endl;

    }

    {
        msp_telemetry::Altitude altitude(fwVariant);
        if(client.sendMessage(altitude) == 1)
            std::cout << altitude;
        else
            std::cerr << "unsupported: " << size_t(altitude.id()) << std::endl;

    }

    client.stop();
    return 0;
}

