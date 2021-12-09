#ifndef DEBUG
#define DEBUG

#ifdef DEBUG_VAR
#define debug( x ) std::cout << x
#else
#define debug( x ) 
#endif

#endif // DEBUG