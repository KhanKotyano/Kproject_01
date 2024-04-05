#include "functions.h"

//Memory Unsafe???
char* FloatToString( float recast ){
    int length = snprintf( NULL, 0, "%g", recast ); 
    char *str = (char*)malloc( length + 1 );
    snprintf( str, length + 1, "%g", recast );
    return str;
}
//Memory Unsafe???
char* IntToString( int recast ){
    int length = snprintf( NULL, 0, "%d", recast ); 
    char *str = (char*)malloc( length + 1 );
    snprintf( str, length + 1, "%d", recast );
    return str;
}
/*char* ToStringInt( int recast , char *str){
    free(str);
    int length = snprintf( NULL, 0, "%d", recast ); 
    str = (char*)malloc( length + 1 );
    snprintf( str, length + 1, "%d", recast );
    return str;
}
char* ToStringFloat( float recast , char *str){
    free(str);
    int length = snprintf( NULL, 0, "%g", recast ); 
    str = (char*)malloc( length + 1 );
    snprintf( str, length + 1, "%g", recast );
    return str;
}*/