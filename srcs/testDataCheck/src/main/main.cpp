#include <QApplication>
#include <DB/DBTools.h>
#include "../auto_generate_files/macro/cmake_to_c_cpp_header_env.h"
#include "data/serialization/Serialization.h"
int main( int argc, char *argv[ ] ) {
	QApplication app( argc, argv );
	QString sqlitePath( u8"%1%2" );
	sqlitePath = sqlitePath.append( Cache_Path_Dir ).arg( "test.db" );
	auto dbInterface = cylDB::DBTools::linkDB( sqlitePath, cylDB::DBTools::SQLite );
	bool flag = false;
	uint64_t resuult;
	auto dataArray = cylDB::Serialization::getInstance( )->serialization( flag, resuult );
	if( dataArray )
		for( int index = 0; index < resuult; ++index )
			qDebug( ) << dataArray[ index ];
	qDebug( ) << "\n\n\n\n=============\n" << "int main( int argc, char *argv[ ] ) ";
	qDebug( ) << "return app.exec( );";
	return app.exec( );
}
