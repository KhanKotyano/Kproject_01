#include "functions.h"


char* FloatToString( float recast ){
    int length = snprintf( NULL, 0, "%g", recast ); 
    char *str = (char*)malloc( length + 1 );
    snprintf( str, length + 1, "%g", recast );
    return str;
}
char* IntToString( int recast ){
    int length = snprintf( NULL, 0, "%d", recast ); 
    char *str = (char*)malloc( length + 1 );
    snprintf( str, length + 1, "%d", recast );
    return str;
}
