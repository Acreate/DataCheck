#include "Serialization.h"
using namespace cylDataCheck;

Serialization Serialization::instance;
Serialization::~Serialization( ) {
}
Serialization::Serialization( ) {
	union {
		short i;
		char a[ 2 ];
	} u;
	u.i = 0;
	u.a[ 0 ] = 0x11;
	u.a[ 1 ] = 0x22;
	if( u.i == 0x221 )
		begEndian = false;
	else if( u.i == 0x1122 )
		begEndian = true;
}
Serialization * Serialization::getInstance( ) {
	return &instance;
}
Data_Array Serialization::serialization( const bool &serialization_data, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = 22;
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	for( uint8_t index = 0; index < data_serialization_result_len; ++index )
		px[ index ] = index;
	return std::shared_ptr< uint8_t[ ] >( px );
}
Data_Array Serialization::serialization( const short &serialization_data, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = 22;
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	for( uint8_t index = 0; index < data_serialization_result_len; ++index )
		px[ index ] = index;
	return std::shared_ptr< uint8_t[ ] >( px );
}
Data_Array Serialization::serialization( const int &serialization_data, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = 22;
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	for( uint8_t index = 0; index < data_serialization_result_len; ++index )
		px[ index ] = index;
	return std::shared_ptr< uint8_t[ ] >( px );
}
Data_Array Serialization::serialization( const long &serialization_data, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = 22;
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	for( uint8_t index = 0; index < data_serialization_result_len; ++index )
		px[ index ] = index;
	return std::shared_ptr< uint8_t[ ] >( px );
}
Data_Array Serialization::serialization( const long long &serialization_data, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = 22;
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	for( uint8_t index = 0; index < data_serialization_result_len; ++index )
		px[ index ] = index;
	return std::shared_ptr< uint8_t[ ] >( px );
}
Data_Array Serialization::serialization( const unsigned short &serialization_data, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = 22;
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	for( uint8_t index = 0; index < data_serialization_result_len; ++index )
		px[ index ] = index;
	return std::shared_ptr< uint8_t[ ] >( px );
}
Data_Array Serialization::serialization( const unsigned int &serialization_data, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = 22;
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	for( uint8_t index = 0; index < data_serialization_result_len; ++index )
		px[ index ] = index;
	return std::shared_ptr< uint8_t[ ] >( px );
}
Data_Array Serialization::serialization( const unsigned long &serialization_data, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = 22;
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	for( uint8_t index = 0; index < data_serialization_result_len; ++index )
		px[ index ] = index;
	return std::shared_ptr< uint8_t[ ] >( px );
}
Data_Array Serialization::serialization( const unsigned long long &serialization_data, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = 22;
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	for( uint8_t index = 0; index < data_serialization_result_len; ++index )
		px[ index ] = index;
	return std::shared_ptr< uint8_t[ ] >( px );
}
Data_Array Serialization::serialization( const float &serialization_data, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = 22;
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	for( uint8_t index = 0; index < data_serialization_result_len; ++index )
		px[ index ] = index;
	return std::shared_ptr< uint8_t[ ] >( px );
}
Data_Array Serialization::serialization( const double &serialization_data, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = 22;
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	for( uint8_t index = 0; index < data_serialization_result_len; ++index )
		px[ index ] = index;
	return std::shared_ptr< uint8_t[ ] >( px );
}
