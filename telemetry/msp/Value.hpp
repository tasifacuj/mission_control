#pragma once

#include <utility>

namespace msp_telemetry{
    template<typename T>
    class Value{
        std::pair<T, bool> data_;

    public:
        Value<T>& operator =( Value<T>& rhs ) = default;

        operator T()const{
            return data_.first;
        }

        operator T&(){
            return data_.first;
        }

        Value<T>& operator =( T const rhs ){
            data_.first = rhs;
            data_.second = false;
            return *this;
        }

        bool set()const{
            return data_.second;
        }

        bool& set(){
            return data_.second;
        }


        T data() const { 
            return data_.first; 
        }

        T& data() { 
            return data_.first; 
        }
    };
}

template<typename T>
inline std::ostream& operator <<( std::ostream& s, msp_telemetry::Value< T > const& val ){
    if( val.set() ){
        s << val.data();
    }else{
        s << "<unset>";
    }

    return s;
}

template <>
inline std::ostream& operator<<(std::ostream& s,
                                const msp_telemetry::Value<uint8_t>& val) {
    if(val.set())
        s << uint32_t(val.data());
    else
        s << "<unset>";
    return s;
}

template <>
inline std::ostream& operator<<(std::ostream& s,
                                const msp_telemetry::Value<int8_t>& val) {
    if(val.set())
        s << int32_t(val.data());
    else
        s << "<unset>";
    return s;
}