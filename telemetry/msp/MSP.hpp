#pragma once

#include <array>
#include <cassert>
#include <climits>
#include <iomanip>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "Message.hpp"

// undefine macros defined by GNU C std library
#undef major
#undef minor

namespace msp_telemetry{
    enum class ID : uint16_t {
        MSP_API_VERSION                    = 1,
        MSP_FC_VARIANT                     = 2,
        MSP_FC_VERSION                     = 3,
        MSP_BOARD_INFO                     = 4,
        MSP_BUILD_INFO                     = 5,
        MSP_INAV_PID                       = 6,
        MSP_SET_INAV_PID                   = 7,
        MSP_NAME                           = 10,  // out message
        MSP_SET_NAME                       = 11,  // in message
        MSP_NAV_POSHOLD                    = 12,  // only in iNav
        MSP_SET_NAV_POSHOLD                = 13,  // only in iNav
        MSP_CALIBRATION_DATA               = 14,
        MSP_SET_CALIBRATION_DATA           = 15,
        MSP_POSITION_ESTIMATION_CONFIG     = 16,
        MSP_SET_POSITION_ESTIMATION_CONFIG = 17,
        MSP_WP_MISSION_LOAD                = 18,  // Load mission from NVRAM
        MSP_WP_MISSION_SAVE                = 19,  // Save mission to NVRAM
        MSP_WP_GETINFO                     = 20,
        MSP_RTH_AND_LAND_CONFIG            = 21,
        MSP_SET_RTH_AND_LAND_CONFIG        = 22,
        MSP_FW_CONFIG                      = 23,
        MSP_SET_FW_CONFIG                  = 24,
        MSP_BATTERY_CONFIG                 = 32,  // not avaialable in iNav
        MSP_SET_BATTERY_CONFIG             = 33,  // not avaialable in iNav
        MSP_MODE_RANGES                    = 34,
        MSP_SET_MODE_RANGE                 = 35,
        MSP_FEATURE                        = 36,
        MSP_SET_FEATURE                    = 37,
        MSP_BOARD_ALIGNMENT                = 38,
        MSP_SET_BOARD_ALIGNMENT            = 39,
        MSP_CURRENT_METER_CONFIG           = 40,
        MSP_SET_CURRENT_METER_CONFIG       = 41,
        MSP_MIXER                          = 42,
        MSP_SET_MIXER                      = 43,
        MSP_RX_CONFIG                      = 44,
        MSP_SET_RX_CONFIG                  = 45,
        MSP_LED_COLORS                     = 46,
        MSP_SET_LED_COLORS                 = 47,
        MSP_LED_STRIP_CONFIG               = 48,
        MSP_SET_LED_STRIP_CONFIG           = 49,
        MSP_RSSI_CONFIG                    = 50,
        MSP_SET_RSSI_CONFIG                = 51,
        MSP_ADJUSTMENT_RANGES              = 52,
        MSP_SET_ADJUSTMENT_RANGE           = 53,
        MSP_CF_SERIAL_CONFIG               = 54,
        MSP_SET_CF_SERIAL_CONFIG           = 55,
        MSP_VOLTAGE_METER_CONFIG           = 56,
        MSP_SET_VOLTAGE_METER_CONFIG       = 57,
        MSP_SONAR_ALTITUDE                 = 58,
        MSP_PID_CONTROLLER                 = 59,
        MSP_SET_PID_CONTROLLER             = 60,
        MSP_ARMING_CONFIG                  = 61,
        MSP_SET_ARMING_CONFIG              = 62,
        MSP_RX_MAP                         = 64,
        MSP_SET_RX_MAP                     = 65,
        MSP_BF_CONFIG                      = 66,  // depricated, out message
        MSP_SET_BF_CONFIG                  = 67,  // depricated, in message
        MSP_REBOOT                         = 68,
        MSP_BF_BUILD_INFO                  = 69,  // depricated, iNav
        MSP_DATAFLASH_SUMMARY              = 70,
        MSP_DATAFLASH_READ                 = 71,
        MSP_DATAFLASH_ERASE                = 72,
        MSP_LOOP_TIME                      = 73,  // depricated, iNav
        MSP_SET_LOOP_TIME                  = 74,  // depricated, iNav
        MSP_FAILSAFE_CONFIG                = 75,
        MSP_SET_FAILSAFE_CONFIG            = 76,
        MSP_RXFAIL_CONFIG                  = 77,  // depricated, iNav
        MSP_SET_RXFAIL_CONFIG              = 78,  // depricated, iNav
        MSP_SDCARD_SUMMARY                 = 79,
        MSP_BLACKBOX_CONFIG                = 80,
        MSP_SET_BLACKBOX_CONFIG            = 81,
        MSP_TRANSPONDER_CONFIG             = 82,
        MSP_SET_TRANSPONDER_CONFIG         = 83,
        MSP_OSD_CONFIG                     = 84,  // out message, betaflight
        MSP_SET_OSD_CONFIG                 = 85,  // in message, betaflight
        MSP_OSD_CHAR_READ                  = 86,  // out message, betaflight
        MSP_OSD_CHAR_WRITE                 = 87,
        MSP_VTX_CONFIG                     = 88,
        MSP_SET_VTX_CONFIG                 = 89,
        MSP_ADVANCED_CONFIG                = 90,
        MSP_SET_ADVANCED_CONFIG            = 91,
        MSP_FILTER_CONFIG                  = 92,
        MSP_SET_FILTER_CONFIG              = 93,
        MSP_PID_ADVANCED                   = 94,
        MSP_SET_PID_ADVANCED               = 95,
        MSP_SENSOR_CONFIG                  = 96,
        MSP_SET_SENSOR_CONFIG              = 97,
        MSP_CAMERA_CONTROL                 = 98,   // MSP_SPECIAL_PARAMETERS
        MSP_SET_ARMING_DISABLED            = 99,   // MSP_SET_SPECIAL_PARAMETERS
        MSP_IDENT                          = 100,  // depricated
        MSP_STATUS                         = 101,
        MSP_RAW_IMU                        = 102,
        MSP_SERVO                          = 103,
        MSP_MOTOR                          = 104,
        MSP_RC                             = 105,
        MSP_RAW_GPS                        = 106,
        MSP_COMP_GPS                       = 107,
        MSP_ATTITUDE                       = 108,
        MSP_ALTITUDE                       = 109,
        MSP_ANALOG                         = 110,
        MSP_RC_TUNING                      = 111,
        MSP_PID                            = 112,
        MSP_ACTIVEBOXES                    = 113,  // depricated, iNav
        MSP_MISC                           = 114,  // depricated, iNav
        MSP_MOTOR_PINS                     = 115,  // depricated, iNav
        MSP_BOXNAMES                       = 116,
        MSP_PIDNAMES                       = 117,
        MSP_WP                             = 118,
        MSP_BOXIDS                         = 119,
        MSP_SERVO_CONF                     = 120,
        MSP_NAV_STATUS                     = 121,
        MSP_NAV_CONFIG                     = 122,
        MSP_MOTOR_3D_CONFIG                = 124,
        MSP_RC_DEADBAND                    = 125,
        MSP_SENSOR_ALIGNMENT               = 126,
        MSP_LED_STRIP_MODECOLOR            = 127,
        MSP_VOLTAGE_METERS                 = 128,  // not present in iNav
        MSP_CURRENT_METERS                 = 129,  // not present in iNav
        MSP_BATTERY_STATE                  = 130,  // not present in iNav
        MSP_MOTOR_CONFIG                   = 131,  // out message
        MSP_GPS_CONFIG                     = 132,  // out message
        MSP_COMPASS_CONFIG                 = 133,  // out message
        MSP_ESC_SENSOR_DATA                = 134,  // out message
        MSP_STATUS_EX                      = 150,
        MSP_SENSOR_STATUS                  = 151,  // only iNav
        MSP_UID                            = 160,
        MSP_GPSSVINFO                      = 164,
        MSP_GPSSTATISTICS                  = 166,
        MSP_OSD_VIDEO_CONFIG               = 180,
        MSP_SET_OSD_VIDEO_CONFIG           = 181,
        MSP_DISPLAYPORT                    = 182,
        MSP_COPY_PROFILE                   = 183,  // not in iNav
        MSP_BEEPER_CONFIG                  = 184,  // not in iNav
        MSP_SET_BEEPER_CONFIG              = 185,  // not in iNav
        MSP_SET_TX_INFO                    = 186,  // in message
        MSP_TX_INFO                        = 187,  // out message
        MSP_SET_RAW_RC                     = 200,
        MSP_SET_RAW_GPS                    = 201,
        MSP_SET_PID                        = 202,
        MSP_SET_BOX                        = 203,  // depricated
        MSP_SET_RC_TUNING                  = 204,
        MSP_ACC_CALIBRATION                = 205,
        MSP_MAG_CALIBRATION                = 206,
        MSP_SET_MISC                       = 207,  // depricated
        MSP_RESET_CONF                     = 208,
        MSP_SET_WP                         = 209,
        MSP_SELECT_SETTING                 = 210,
        MSP_SET_HEADING                    = 211,
        MSP_SET_SERVO_CONF                 = 212,
        MSP_SET_MOTOR                      = 214,
        MSP_SET_NAV_CONFIG                 = 215,
        MSP_SET_MOTOR_3D_CONF              = 217,
        MSP_SET_RC_DEADBAND                = 218,
        MSP_SET_RESET_CURR_PID             = 219,
        MSP_SET_SENSOR_ALIGNMENT           = 220,
        MSP_SET_LED_STRIP_MODECOLOR        = 221,
        MSP_SET_MOTOR_CONFIG               = 222,  // out message
        MSP_SET_GPS_CONFIG                 = 223,  // out message
        MSP_SET_COMPASS_CONFIG             = 224,  // out message
        MSP_SET_ACC_TRIM                   = 239,  // in message
        MSP_ACC_TRIM                       = 240,  // out message
        MSP_SERVO_MIX_RULES                = 241,  // out message
        MSP_SET_SERVO_MIX_RULE             = 242,  // in message
        MSP_PASSTHROUGH_SERIAL             = 244,  // not used in CF, BF, iNav
        MSP_SET_4WAY_IF                    = 245,  // in message
        MSP_SET_RTC                        = 246,  // in message
        MSP_RTC                            = 247,  // out message
        MSP_EEPROM_WRITE                   = 250,  // in message
        MSP_RESERVE_1                      = 251,  // reserved for system usage
        MSP_RESERVE_2                      = 252,  // reserved for system usage
        MSP_DEBUGMSG                       = 253,  // out message
        MSP_DEBUG                          = 254,  // out message
        MSP_V2_FRAME                       = 255,  // MSPv2 over MSPv1

        MSP2_COMMON_TZ               = 0x1001,  // out message, TZ offset
        MSP2_COMMON_SET_TZ           = 0x1002,  // in message, sets the TZ offset
        MSP2_COMMON_SETTING          = 0x1003,  // in/out message, returns setting
        MSP2_COMMON_SET_SETTING      = 0x1004,  // in message, sets a setting value
        MSP2_COMMON_MOTOR_MIXER      = 0x1005,
        MSP2_COMMON_SET_MOTOR_MIXER  = 0x1006,
        MSP2_INAV_STATUS             = 0x2000,
        MSP2_INAV_OPTICAL_FLOW       = 0x2001,
        MSP2_INAV_ANALOG             = 0x2002,
        MSP2_INAV_MISC               = 0x2003,
        MSP2_INAV_SET_MISC           = 0x2004,
        MSP2_INAV_BATTERY_CONFIG     = 0x2005,
        MSP2_INAV_SET_BATTERY_CONFIG = 0x2006,
        MSP2_INAV_RATE_PROFILE       = 0x2007,
        MSP2_INAV_SET_RATE_PROFILE   = 0x2008,
        MSP2_INAV_AIR_SPEED          = 0x2009
    };

    enum class ArmingFlags : uint32_t {
    ARMED          = (1 << 2),
    WAS_EVER_ARMED = (1 << 3),

    ARMING_DISABLED_FAILSAFE_SYSTEM = (1 << 7),

    ARMING_DISABLED_NOT_LEVEL                    = (1 << 8),
    ARMING_DISABLED_SENSORS_CALIBRATING          = (1 << 9),
    ARMING_DISABLED_SYSTEM_OVERLOADED            = (1 << 10),
    ARMING_DISABLED_NAVIGATION_UNSAFE            = (1 << 11),
    ARMING_DISABLED_COMPASS_NOT_CALIBRATED       = (1 << 12),
    ARMING_DISABLED_ACCELEROMETER_NOT_CALIBRATED = (1 << 13),
    ARMING_DISABLED_ARM_SWITCH                   = (1 << 14),
    ARMING_DISABLED_HARDWARE_FAILURE             = (1 << 15),
    ARMING_DISABLED_BOXFAILSAFE                  = (1 << 16),
    ARMING_DISABLED_BOXKILLSWITCH                = (1 << 17),
    ARMING_DISABLED_RC_LINK                      = (1 << 18),
    ARMING_DISABLED_THROTTLE                     = (1 << 19),
    ARMING_DISABLED_CLI                          = (1 << 20),
    ARMING_DISABLED_CMS_MENU                     = (1 << 21),
    ARMING_DISABLED_OSD_MENU                     = (1 << 22),
    ARMING_DISABLED_ROLLPITCH_NOT_CENTERED       = (1 << 23),
    ARMING_DISABLED_SERVO_AUTOTRIM               = (1 << 24),
    ARMING_DISABLED_OOM                          = (1 << 25),
    ARMING_DISABLED_INVALID_SETTING              = (1 << 26),

    ARMING_DISABLED_ALL_FLAGS =
        (ARMING_DISABLED_FAILSAFE_SYSTEM | ARMING_DISABLED_NOT_LEVEL |
         ARMING_DISABLED_SENSORS_CALIBRATING |
         ARMING_DISABLED_SYSTEM_OVERLOADED | ARMING_DISABLED_NAVIGATION_UNSAFE |
         ARMING_DISABLED_COMPASS_NOT_CALIBRATED |
         ARMING_DISABLED_ACCELEROMETER_NOT_CALIBRATED |
         ARMING_DISABLED_ARM_SWITCH | ARMING_DISABLED_HARDWARE_FAILURE |
         ARMING_DISABLED_BOXFAILSAFE | ARMING_DISABLED_BOXKILLSWITCH |
         ARMING_DISABLED_RC_LINK | ARMING_DISABLED_THROTTLE |
         ARMING_DISABLED_CLI | ARMING_DISABLED_CMS_MENU |
         ARMING_DISABLED_OSD_MENU | ARMING_DISABLED_ROLLPITCH_NOT_CENTERED |
         ARMING_DISABLED_SERVO_AUTOTRIM | ARMING_DISABLED_OOM |
         ARMING_DISABLED_INVALID_SETTING)
};

    inline std::string armingFlagToString(uint32_t flag) {
        std::string val;
        if(flag & (1 << 2)) val += "ARMED ";
        if(flag & (1 << 3)) val += "WAS_EVER_ARMED ";
        if(flag & (1 << 7)) val += "ARMING_DISABLED_FAILSAFE_SYSTEM ";
        if(flag & (1 << 8)) val += "ARMING_DISABLED_NOT_LEVEL ";
        if(flag & (1 << 9)) val += "ARMING_DISABLED_SENSORS_CALIBRATING ";
        if(flag & (1 << 10)) val += "ARMING_DISABLED_SYSTEM_OVERLOADED ";
        if(flag & (1 << 11)) val += "ARMING_DISABLED_NAVIGATION_UNSAFE ";
        if(flag & (1 << 12)) val += "ARMING_DISABLED_COMPASS_NOT_CALIBRATED ";
        if(flag & (1 << 13)) val += "ARMING_DISABLED_ACCELEROMETER_NOT_CALIBRATED ";
        if(flag & (1 << 14)) val += "ARMING_DISABLED_ARM_SWITCH ";
        if(flag & (1 << 15)) val += "ARMING_DISABLED_HARDWARE_FAILURE ";
        if(flag & (1 << 16)) val += "ARMING_DISABLED_BOXFAILSAFE ";
        if(flag & (1 << 17)) val += "ARMING_DISABLED_BOXKILLSWITCH ";
        if(flag & (1 << 18)) val += "ARMING_DISABLED_RC_LINK ";
        if(flag & (1 << 19)) val += "ARMING_DISABLED_THROTTLE ";
        if(flag & (1 << 20)) val += "ARMING_DISABLED_CLI ";
        if(flag & (1 << 21)) val += "ARMING_DISABLED_CMS_MENU ";
        if(flag & (1 << 22)) val += "ARMING_DISABLED_OSD_MENU ";
        if(flag & (1 << 23)) val += "ARMING_DISABLED_ROLLPITCH_NOT_CENTERED ";
        if(flag & (1 << 24)) val += "ARMING_DISABLED_SERVO_AUTOTRIM ";
        if(flag & (1 << 25)) val += "ARMING_DISABLED_OOM ";
        if(flag & (1 << 26)) val += "ARMING_DISABLED_INVALID_SETTING ";
        return val;
    }

    enum class Sensor {
        Accelerometer,
        Barometer,
        Magnetometer,
        GPS,
        Sonar,
        OpticalFlow,
        Pitot,
        GeneralHealth
    };


    struct StatusBase : public Packable{
        Value<uint16_t> cycle_time;  // in us
        Value<uint16_t> i2c_errors;
        std::set<Sensor> sensors;
        std::set<size_t> box_mode_flags;
        Value<uint8_t> current_profile;

        virtual bool unpackFrom( ByteVector const& data ) override{
            bool rc = true;
            rc &= data.unpack(cycle_time);
            rc &= data.unpack(i2c_errors);

            sensors.clear();
            uint16_t sensor = 0;
            rc &= data.unpack(sensor);

            if(sensor & (1 << 0)) sensors.insert(Sensor::Accelerometer);
            if(sensor & (1 << 1)) sensors.insert(Sensor::Barometer);
            if(sensor & (1 << 2)) sensors.insert(Sensor::Magnetometer);
            if(sensor & (1 << 3)) sensors.insert(Sensor::GPS);
            if(sensor & (1 << 4)) sensors.insert(Sensor::Sonar);
            if(sensor & (1 << 5)) sensors.insert(Sensor::OpticalFlow);
            if(sensor & (1 << 6)) sensors.insert(Sensor::Pitot);
            if(sensor & (1 << 15)) sensors.insert(Sensor::GeneralHealth);

            // check active boxes
            box_mode_flags.clear();
            uint32_t flag = 0;
            rc &= data.unpack(flag);
            for(size_t ibox(0); ibox < sizeof(flag) * CHAR_BIT; ibox++) {
                if(flag & (1 << ibox)) box_mode_flags.insert(ibox);
            }

            rc &= data.unpack(current_profile);
            return rc;
        }

        virtual bool packInto(ByteVector& /*data*/) const {
            return false;
        }
    };

    struct Status : public StatusBase, public Message{
        Status(FirmwareVariant v) : Message(v) {}

        virtual ID id() const override { return ID::MSP_STATUS; }

        virtual bool decode( ByteVector const& data ) override{
            bool rc = true;
            rc &= StatusBase::unpackFrom( data );
            return rc;
        }

        bool hasAccelerometer() const {
            return sensors.count(Sensor::Accelerometer);
        }

        bool hasBarometer() const { return sensors.count(Sensor::Barometer); }

        bool hasMagnetometer() const { return sensors.count(Sensor::Magnetometer); }

        bool hasGPS() const { return sensors.count(Sensor::GPS); }

        bool hasSonar() const { return sensors.count(Sensor::Sonar); }

        bool hasOpticalFlow() const { return sensors.count(Sensor::OpticalFlow); }

        bool hasPitot() const { return sensors.count(Sensor::Pitot); }

        bool isHealthy() const { return sensors.count(Sensor::GeneralHealth); }

        virtual std::ostream& print(std::ostream& s) const override {
            s << "#Status:" << std::endl;
            s << " Cycle time: " << cycle_time << " us" << std::endl;
            s << " I2C errors: " << i2c_errors << std::endl;
            s << " Sensors:" << std::endl;

            s << "    Accelerometer: ";
            hasAccelerometer() ? s << "ON" : s << "OFF";
            s << std::endl;

            s << "    Barometer: ";
            hasBarometer() ? s << "ON" : s << "OFF";
            s << std::endl;

            s << "    Magnetometer: ";
            hasMagnetometer() ? s << "ON" : s << "OFF";
            s << std::endl;

            s << "    GPS: ";
            hasGPS() ? s << "ON" : s << "OFF";
            s << std::endl;

            s << "    Sonar: ";
            hasSonar() ? s << "ON" : s << "OFF";
            s << std::endl;

            s << " Active Boxes (by ID):";
            for(const size_t box_id : box_mode_flags) {
                s << " " << box_id;
            }
            s << std::endl;

            return s;
        }  
    };

    // MSP_RAW_IMU: 102
    struct RawImu : public Message {
        RawImu(FirmwareVariant v) : Message(v) {}

        virtual ID id() const override { return ID::MSP_RAW_IMU; }

        std::array<Value<int16_t>, 3> acc;
        std::array<Value<int16_t>, 3> gyro;
        std::array<Value<int16_t>, 3> mag;

        virtual bool decode(const ByteVector& data) override {
            bool rc = true;
            for(auto& a : acc) {
                rc &= data.unpack(a);
            }
            for(auto& g : gyro) {
                rc &= data.unpack(g);
            }
            for(auto& m : mag) {
                rc &= data.unpack(m);
            }
            return rc;
        }

        virtual std::ostream& print(std::ostream& s) const override {
            s << "#RawImu:" << std::endl;
            s << " Linear acceleration: " << acc[0] << ", " << acc[1] << ", "
            << acc[2] << std::endl;
            s << " Angular velocity: " << gyro[0] << ", " << gyro[1] << ", "
            << gyro[2] << std::endl;
            s << " Magnetometer: " << mag[0] << ", " << mag[1] << ", " << mag[2]
            << std::endl;
            return s;
        }
    };

    // helper class to convert raw imu readigs into standard physic units
    // custom scaling factors have to be derived from the sensor documentation
    struct ImuCI {
        std::array<Value<float>, 3> acc;   // m/s^2
        std::array<Value<float>, 3> gyro;  // deg/s
        std::array<Value<float>, 3> mag;   // uT

        ImuCI(RawImu const& raw,
            const float acc_1g,     // sensor value at 1g
            const float gyro_unit,  // resolution in 1/(deg/s)
            const float magn_gain,  // scale magnetic value to uT (micro Tesla)
            const float si_unit_1g  // acceleration at 1g (in m/s^2))
        ) {
            for(int i = 0; i < 3; ++i) {
                acc[i] = raw.acc[i] / acc_1g * si_unit_1g;
                acc[i].set() = true;
            }
            for(int i = 0; i < 3; ++i) {
                gyro[i] = raw.gyro[i].data() * gyro_unit;
                gyro[i].set() = true;
            }
            for(int i = 0; i < 3; ++i) {
                mag[i] = raw.mag[i].data() * magn_gain;
                mag[i].set() = true;
            }
        }

        std::ostream& print(std::ostream& s) const {
            s << "#Imu:" << std::endl;
            s << " Linear acceleration: " << acc[0] << ", " << acc[1] << ", "
            << acc[2] << " m/s²" << std::endl;
            s << " Angular velocity: " << gyro[0] << ", " << gyro[1] << ", "
            << gyro[2] << " deg/s" << std::endl;
            s << " Magnetometer: " << mag[0] << ", " << mag[1] << ", " << mag[2]
            << " uT" << std::endl;
            return s;
        }
    };

    // MSP_RC: 105,rc channels
    class Rc: public Message{
        std::vector<uint16_t> channels_;

    public:
        Rc( FirmwareVariant fw ) : Message( fw ){}

    public:
        virtual ID id() const override { 
            return ID::MSP_RC; 
        }

        virtual bool decode( ByteVector const& bv ) override{
            channels_.clear();
            bool rval = true;

            while( rval ){
                uint16_t data;
                rval = bv.unpack( data );

                if( rval ) channels_.push_back( data );
            }

            return !channels_.empty();
        }

        virtual std::ostream& print( std::ostream& strm )const override{
            strm << "Rc channels: "  << channels_.size() << std::endl;
            for( auto ch : channels_ ){
                strm << ch << ' ';
            }

            return strm;
        }

        std::vector<uint16_t> const& channels()const{
            return channels_;
        }
    };

    // MSP_ATTITUDE: 108    2 angles 1 heading 
    class Attitude : public Message{
        Value<float> roll_; // [-180, +180]
        Value<float> pitch_;// [-90, +90 ]
        Value<uint16_t> yaw_;// [ -180, +180 ]
    public:
        Attitude( FirmwareVariant fw ) : Message( fw ){}
        virtual ID id()const override{
            return ID::MSP_ATTITUDE;
        }

        virtual bool decode( ByteVector const& bv )override{
            bool rval = true;
            rval &= bv.unpack<int16_t>( roll_, 10 );
            rval &= bv.unpack<int16_t>( pitch_, 10 );
            rval &= bv.unpack( yaw_ );
            return rval;
        }

        virtual std::ostream& print( std::ostream& strm ) const override{
            strm << "Attitude:" << std::endl
            << "Roll: " << roll_ << "[deg]" << std::endl
            << "Pitch: " << pitch_ << "[deg]" << std::endl
            << "Yaw: " << yaw_ << "[deg]" << std::endl
            ;

            return strm;
        }

        Value<float> const& roll()const{
            return roll_;
        }

        Value<float> pitch()const{
            return pitch_;
        }

        Value<uint16_t> yaw()const{
            return yaw_;
        }
    }; 

    // MSP_ALTITUDE: 109    altitude, variometer
    class Altitude : public Message{
        Value<float> altitude_;  // m
        Value<float> vZ_;     // m/s
        bool baroAltitudeSet_{false};
        Value<float> baroAltitude_;

    public:
        Altitude( FirmwareVariant fw ) : Message( fw ){}

        virtual ID id() const override{
            return ID::MSP_ALTITUDE;
        }

        virtual bool decode( ByteVector const& bv ){
            bool rval = true;
            rval &= bv.unpack<int32_t>( altitude_, 100 );
            rval &= bv.unpack<int16_t>( vZ_, 100 );

            if( bv.unpackingRemaining() ){
                baroAltitude_ = true;
                rval &= bv.unpack<int32_t>( baroAltitude_, 100 );
            }

            return rval;
        }

        virtual std::ostream& print( std::ostream& strm )const override{
            strm << "#Altitude:" << std::endl;
            strm << " Alt: " << altitude_ << "[m]" << "z spd: " << vZ_ << "[m/s]" << std::endl
            ;

            if( baroAltitude_ ){
                strm << "Barometer: " << baroAltitude_ << "[m]" << std::endl;
            }

            return strm;
        }
    };
}


inline std::ostream& operator<<(std::ostream& s, const msp_telemetry::ImuCI& val) {
    return val.print(s);
}