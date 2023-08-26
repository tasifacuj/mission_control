#pragma once
#include <memory>
#include <string>
#include <vector>
#include "ByteVector.hpp"
#include "FirmwareVariant.hpp"

namespace msp_telemetry{
    enum class ID : uint16_t;

    class Message{
    protected:
        FirmwareVariant fw_variant_;

    public:
        virtual ~Message(){}
        Message(FirmwareVariant v) : fw_variant_(v) {}
        
        virtual ID id() const = 0;

        void setFirmwareVariant(FirmwareVariant v) { fw_variant_ = v; }

        FirmwareVariant getFirmwareVariant() const { return fw_variant_; }

        virtual bool decode(const ByteVector& /*data*/) { return false; }

        virtual ByteVectorUptr encode() const { return ByteVectorUptr(); }

        virtual std::ostream& print(std::ostream& s) const {
            s << "Print method for message ID " << uint16_t(id())
            << " is not implemented" << std::endl;
            return s;
        }
    };
}// namespace msp_telemetry

inline std::ostream& operator<<(std::ostream& s, const msp_telemetry::ID& id) {
    s << int(id);
    return s;
}

inline std::ostream& operator<<(std::ostream& s, const msp_telemetry::Message& val) {
    return val.print(s);
}
