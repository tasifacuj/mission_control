#pragma once

// std
#include <cstdint>
#include <limits>
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>
#include <string>

// project
#include "Value.hpp"

namespace msp_telemetry{

    class ByteVector : public std::vector< uint8_t >{
    protected:
        mutable std::size_t offset_;

    public:// == CTORS ==
        ByteVector() : offset_( 0 ){}

        template<typename T1>
        ByteVector( T1 arg ) : std::vector< uint8_t >( arg ), offset_( 0 ){}

        template<typename T1, typename T2>
        ByteVector( T1 arg1, T2 arg2 ) : std::vector< uint8_t >( arg1, arg2 ), offset_( 0 ){}

    public:
        template<typename T, typename std::enable_if< std::is_integral<T>::value, T >::type* = nullptr >
        bool pack( T const& val ){
            // little endian
            for( size_t i = 0; i < sizeof( val ); ++i ){
                this->push_back( val >> (i * 8) & 0xFF );
            }

            return true;
        }

        /**
        * @brief Packs another ByteVector into the ByteVector.
        * @param data ByteVector to be packed
        * @param max_len Optional max number of characters to transfer into the
        * ByteVector
        * @return True if successful
        */

        bool pack( ByteVector const& data, size_t maxLen = std::numeric_limits< size_t >::max() ){
            size_t cnt = 0;
            
            for( auto c : data ){
                this->push_back( c );

                if( ++cnt == maxLen )
                    break;
            }

            return true;
        }

        /**
        * @brief Packs floating point types into the ByteVector. Uses IEEE 754
        * format.
        * @tparam T Underlying data type to be packed. Must be a floating point
        * type.
        * @param val Value to be packed
        * @return True if successful
        */
        template< typename T, typename std::enable_if< std::is_floating_point<T>::value,T >::type* = nullptr >
        bool pack( T const& val ){
            ByteVector bv( sizeof( val ) );
            reinterpret_cast< T& >( bv.front() ) = val;
            return this->pack( bv );
        }

        /**
        * @brief Packs scaled values (e.g. float to scaled int) as packed_val =
        * (val+offset)*scale
        * @tparam encoding_T Data type to use for the actual data packing (usually
        * an integral type)
        * @tparam T1 Type of input value (usually a floating point type)
        * @tparam T2 Type of scale and offset coefficients
        * @param val Value to be packed
        * @param scale Value of scaling to apply to the offset value
        * @param offset Value of offset to apply to the input value (optional,
        * defaults to 0)
        * @return True if successful
        */

        template<
            typename EncodingT, 
            typename T1, 
            typename T2, 
            typename std::enable_if< std::is_arithmetic< T1 >::value, T1 >::type* = nullptr,
            typename std::enable_if< std::is_arithmetic< T2 >::value, T2 >::type* = nullptr
        >
        bool pack( T1 const val, T2 const scale, T2 const offset = 0 ){
            T1 const tmp = ( val + offset_ ) * scale;
            
            if( tmp <= std::numeric_limits<EncodingT>::min() )
                return pack( std::numeric_limits<EncodingT>::min() );
            else if( tmp >= std::numeric_limits<EncodingT>::max() )
                return pack( std::numeric_limits<EncodingT>::max() );
            else 
                return pack( static_cast< EncodingT >( tmp ) );
        }

        /**
        * @brief Packs string data into the ByteVector.
        * @param val String to be packed
        * @param max_len Optional max number of characters to transfer into the
        * ByteVector
        * @return True if successful
        */

        bool pack( std::string const& value, size_t maxLen = std::numeric_limits< size_t >::max() ){
            size_t cnt = 0;

            for( auto c : value ){
                this->push_back( c );

                if( ++cnt = maxLen )
                    break;
            }

            this->push_back( 0 );
            return true;
        }

        /**
        * @brief Packs scaled value types (e.g. value<float> to scaled int) as
        * packed_val = (val+offset)*scale
        * @tparam encoding_T Data type to use for the actual data packing (usually
        * an integral type)
        * @tparam T1 Type of input value (usually a floating point type)
        * @tparam T2 Type of scale and offset coefficients
        * @param val Value to be packed
        * @param scale Value of scaling to apply to the offset value
        * @param offset Value of offset to apply to the input value (optional,
        * defaults to 0)
        * @return True if successful
        */
        template<
            typename EncodingT,
            typename T1,
            typename T2,
            typename std::enable_if< std::is_arithmetic< T1 >::value, T1 >::type* = nullptr,
            typename std::enable_if< std::is_arithmetic< T2 >::value, T2 >::type* = nullptr
        >
        bool pack( Value<T1> const& val, T2 const scale, T2 const offset = 0 ){
            if( !val.set() )
                return false;

            return pack< EncodingT >( val.data(), scale, offset );
        }

        /**
        * @brief Packs a Value<ByteVector> into the ByteVector.
        * @param val The Value<ByteVector> to be packed
        * @param max_len Optional max number of characters to transfer into the
        * ByteVector
        * @return True if successful
        */
        bool pack( Value< ByteVector > const& val, size_t maxLen = std::numeric_limits< size_t > :: max() ){
            if( !val.set() ) return false;
            return pack( val.data(), maxLen );
        }

        /**
        * @brief Packs a Value<std::string> into the ByteVector.
        * @param val The Value<std::string> to be packed
        * @param max_len Optional max number of characters to transfer into the
        * ByteVector
        * @return True if successful
        */
        bool pack( Value< std::string > const& val, size_t maxLen = std::numeric_limits< size_t > :: max() ){
            if( !val.set() ) return false;

            return pack( val.data(), maxLen );
        }

        /**
         * @brief Packs the contents of a Value<T> into the ByteVector.
         * @tparam T Type of the Value<T> being packed. May be automatically deduced
         * from arguments
         * @param val The Value<T> to be packed
         * @return True if successful
         */

        template<typename T>
        bool pack( Value< T > const& val ){
            if( !val.set() ) return false;
            return pack( val.data() );
        }

        /**
        * @brief Returns the number of bytes still avialable for unpacking
        * @returns Number of bytes remaining
        */
        std::size_t unpackingRemaining() const { return this->size() - offset_; }

        /**
         * @brief Extracts little endian integers from the ByteVector. Consumes
         * a number of bytes matching sizeof(T). Fails if not enough bytes
         * are available.
         * @tparam T Underlying data type to be extracted. Must be an integral type.
         * @param val Destination of unpack operation.
         * @return True on successful unpack
         */
        template<typename T, typename std::enable_if< std::is_integral<T>::value, T >::type* = nullptr>
        bool unpack( T& val )const{
            if( unpackingRemaining() < sizeof( val ) ) return false;

            val = 0;
            for( size_t i = 0; i < sizeof( val ); ++ i ){
                val |= ( *this )[ offset_ ++ ] << ( 8 * i );
            }
            return true;
        }

        /**
         * @brief unpack Extracts a boolen from a single byte
         * @param val Destination of unpack operation.
         * @return True on successful unpack
         */
        bool unpack( bool& val )const{
            if( unpackingRemaining() < 1 ) return false;

            val = ( *this )[ offset_ ++ ];
            return true;
        }

        /**
         * @brief Extracts floating point numbers from the ByteVector.
         * Consumes a number of bytes matching sizeof(T). Fails if not enough
         * bytes are available.
         * @tparam T Underlying data type to be extracted. Must be a floating point
         * type.
         * @param val Destination of unpack operation.
         * @return True on successful unpack
         */
        template<typename T, typename std::enable_if< std::is_floating_point<T>::value, T >::type* = nullptr>
        bool unpack( T& val )const{
            if( unpackingRemaining() > sizeof( val ) ) return false;
            val = reinterpret_cast<T&>( ( *this )[ offset_ ] );
            offset_ += sizeof( val );
            return true;
        }

        /**
         * @brief Extracts data from the ByteVector and stores it in a
         * std::string. Consumes all remaining data unless instructed otherwise.
         * @param val Destination of unpack operation.
         * @param count Max number of bytes to extract. Optional, if unset, all
         * remaining bytes will be consumed.
         * @return True on successful unpack
         */
        bool unpack( std::string& val, size_t cnt = std::numeric_limits<size_t>::max() )const{
            if( cnt == std::numeric_limits< size_t >::max() )
                cnt = unpackingRemaining();

            if( cnt > unpackingRemaining() )
                return false;

            bool rc = true;
            val.clear();
            int8_t tmp;
            for( size_t i = 0; i < cnt; ++ i ){
                rc &= unpack( tmp );
                val += tmp;
            }
            return rc;
        }

        /**
         * @brief Manually consumes data, thus skipping the values.
         * @param count Number of bytes to consume
         * @returns True if successful
         * @returns False if there were not enough bytes to satisfy the request
         */
        bool consume(std::size_t count) const {
            if(count > unpackingRemaining()) {
                return false;
            }
            offset_ += count;
            return true;
        }

        std::vector<uint8_t>::const_iterator unpackingIterator() const {
            return this->begin() + offset_;
        }

        /**
         * @brief Extracts data from the ByteVector and stores it in a
         * another ByteVector. Consumes all remaining data unless instructed
         * otherwise.
         * @param val Destination of unpack operation.
         * @param count Max number of bytes to extract. Optional, if unset, all
         * remaining bytes will be consumed.
         * @return True on successful unpack
         */
        bool unpack( ByteVector& val, size_t cnt = std::numeric_limits<size_t> :: max() )const{
            if( cnt == std::numeric_limits<size_t> :: max() )
                cnt = unpackingRemaining();

            if( !consume( cnt ) )
                return false;

            val.clear();
            val.insert( val.end(), unpackingIterator(), unpackingIterator() + cnt );
            return true;
        }

         /**
         * @brief Unpacks scaled value types (e.g. scaled int to floating point) as
         * val = (packed_val/scale)-offset
         * @tparam encoding_T data type used to store the scaled value (usually an
         * integral type)
         * @tparam T1 type of output value (usually a floating point type)
         * @tparam T2 type of scale and offset coefficients
         * @param val Destination of unpack operation
         * @param scale Value of scaling to apply to the offset value
         * @param offset Value of offset to apply to the input value (optional,
         * defaults to 0)
         * @return True if successful
         */
        template<
            typename EncodingT,
            typename T1,
            typename T2,
            typename std::enable_if<std::is_arithmetic<T1>::value,T1>::type* = nullptr,
            typename std::enable_if<std::is_arithmetic<T2>::value,T2>::type* = nullptr
        >
        bool unpack( T1& val, T2 scale, T2 offset = 0 )const{
            bool rc = true;
            EncodingT tmp = 0;
            rc &= unpack( tmp );
            val = static_cast< T1 >( tmp ) / scale;
            val -= offset_;
            return rc;
        }

        /**
         * @brief Unpacks Value types other than string and ByteVector
         * specializations
         * @tparam T Type of the Value<T> being packed. May be automatically deduced
         * from arguments
         * @param val The destination of the unpack operation
         * @return  true on success
         */
        template<typename T>
        bool unpack( Value<T>& val )const{
            return val.set() = unpack( val.data() );
        }

        /**
         * @brief Extracts data from the ByteVector and stores it in a
         * Value<std::string>. Consumes all remaining data unless instructed
         * otherwise.
         * @param val Destination of unpack operation.
         * @param count Max number of bytes to extract. Optional, if unset, all
         * remaining bytes will be consumed.
         * @return True on successful unpack
         */
        bool unpack( Value< std::string>& val, size_t cnt = std::numeric_limits<size_t>::max() )const{
            return val.set() = unpack( val.data(), cnt );
        }

        /**
         * @brief Extracts data from the ByteVector and stores it in a
         * Value<ByteVector>. Consumes all remaining data unless instructed
         * otherwise.
         * @param val Destination of unpack operation.
         * @param count Max number of bytes to extract. Optional, if unset, all
         * remaining bytes will be consumed.
         * @return True on successful unpack
         */
        bool unpack( Value< ByteVector>& val, size_t cnt = std::numeric_limits<size_t>::max() )const{
            return val.set() = unpack( val.data(), cnt );
        }

        /**
         * @brief Unpacks scaled Value types (e.g. scaled int to floating point) as
         * val = (packed_val/scale)-offset
         * @tparam encoding_T data type used to store the scaled Value (usually an
         * integral type)
         * @tparam T1 type of output Value (usually a floating point type)
         * @tparam T2 type of scale and offset coefficients (default: float)
         * @param val Destination of unpack operation
         * @param scale Value of scaling to apply to the offset value
         * @param offset Value of offset to apply to the input value (optional,
         * defaults to 0)
         * @return True if successful
         */
        template<
            typename EncodingT,
            typename T1,
            typename T2,
            typename std::enable_if<std::is_arithmetic<T1>::value,T1>::type* = nullptr,
            typename std::enable_if<std::is_arithmetic<T2>::value,T2>::type* = nullptr
        >
        bool unpack( Value<T1>& val, T2 scale = 1, T2 offset = 0 )const{
            return val.set() = unpack< EncodingT >( val.data(), scale, offset );
        }

        std::size_t unpacking_offset() const { return offset_; }
    };

    using ByteVectorPtr =  std::shared_ptr<ByteVector> ;
    using ByteVectorUptr = std::unique_ptr<ByteVector>;

    struct Packable {
        virtual ~Packable() {}
        virtual bool packInto(ByteVector& data) const   = 0;
        virtual bool unpackFrom(const ByteVector& data) = 0;
    };

}// namespace msp_telemetry

inline std::ostream& operator<<(std::ostream& s, const msp_telemetry::ByteVector& val) {
    s << std::hex;
    for(const auto& v : val) {
        s << uint32_t(v) << " ";
    }
    s << std::dec << std::endl;
    return s;
}