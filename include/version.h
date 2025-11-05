#ifndef VERSION_H_
#define VERSION_H_

/*-----------------------------------------------------------------------------*/
/* Version Number															  */
/*-----------------------------------------------------------------------------*/

#ifndef BUILD_INFO
#define BUILD_INFO							    		"unknown"
#endif

#define PROJECT               "FIRMWARE"
#else
#define PROJECT               "TEST_FIRMWARE"
#endif
#define	PROJECT_VERSION		     "01"    // Formal version
#define	TSTCODE_VER                                  0x01
#define	TSTCODE_SUBVER                               0x00

// #endif /* VERSION_H_ */