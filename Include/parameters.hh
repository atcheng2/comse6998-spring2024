#ifndef _PARAMETERS_HH_
#define _PARAMETERS_HH_

#ifndef NFPU
#define NFPU 1
#endif
#ifndef NFXU
#define NFXU 1
#endif
#ifndef NBRU
#define NBRU 1
#endif
#ifndef NLDU
#define NLDU 1
#endif
#ifndef NSTU
#define NSTU 1
#endif

using namespace std;

namespace CDC8600
{
    extern bool tracing;		// run-time tracing

    namespace params
    {
	namespace micro
	{

	    enum
	    {
		Xs	  = 16,
		MODEFLAGS = 17,
		CONDFLAGS = 18,
		CMPFLAGS  = 19,
		RA	  = 20,
		XA	  = 21,
		FL	  = 22,
		P	  = 23
	    };

	    const u32	nFPUs = NFPU;
	    const u32	nFXUs = NFXU;
	    const u32	nBRUs = NBRU;
	    const u32   nLDUs = NLDU;
	    const u32 	nSTUs = NSTU;

	    const u32	nregs = 24;	// number of micro-architected registers
	    				// 0-15 : X registers
					// 16 : X scratch register
					// 17 : mode flags
					// 18 : condition flags
					// 19 : compare flags
					// 20 : RA
					// 21 : XA
					// 22 : FL
					// 23 : P
	}
	namespace MEM
	{
	    const u32	N = 262144;	// Memory size = 256Ki words
	} // namespace MEM
    } // namespace params
} // namespace CDC8600

#endif // _PARAMETERS_HH_
