

#define DFLT_LAY	2	/* default encoding layer is II */
#define DFLT_MOD	'r'	/* default mode is stereo front channels */
#define DFLT_PSY	1	/* default psych model is 1 */
#define DFLT_SFQ        44.1   	/* default input sampling rate is 44.1 kHz, now 48kHz 28.6.93 SR */
#define DFLT_BRT        192    	/* default total output bitrate is 384 kbps */
#define DFLT_EMP        'n'    	/* default de-emphasis is none */
#define DFLT_EXT        ".mp2" 	/* default output file extension */
#define DFLT_EXT_EXT    ".ext" 	/* default output file extension of extension bit stream*/
#define DFLT_ML_EXT     ".ml"  	/* default extension for MultiLingual file */
#define	DFLT_VERB	1	/* default level of verbosity */
#define DFLT_NADB	2	/* default number of ancillary data bytes (for DVD !!!) */

#define FILETYPE_ENCODE 'TEXT'
#define CREATOR_ENCODE  'MpgD'

#define TC_ALLOC        0.0

/* This is the smallest MNR a subband can have before it is counted
   as 'noisy' by the logic which chooses the number of JS subbands */
/* Now optionally in fr_ps */

/*#define NOISY_MIN_MNR   0.0*/

/* Psychacoustic Model 1 Definitions */

#define CB_FRACTION     0.33
#define MAX_SNR         1000
#define NOISE           10
#define TONE            20
#define DBMIN           -200.0
#define LAST            -1
#define STOP            -100
#define POWERNORM       90.3090
			/*96.0*/
			/* Full amplitude, 32767, should correspond to
			   96 dB, 1992-11-06 Soren H. Nielsen */
		/* 90.3090  = 20 * log10(32768) to normalize */
                                /* max output power to 96 dB per spec */

/* Psychoacoustic Model 2 Definitions */

#define LOGBLKSIZE      10
#define BLKSIZE         1024
#define HBLKSIZE        513
#define CBANDS          63
#define LXMIN           32.0

/***********************************************************************
*
*  Encoder Type Definitions
*
***********************************************************************/

/* Psychoacoustic Model 1 Type Definitions */

typedef int        IFFT2[FFT_SIZE/2];
typedef int        IFFT[FFT_SIZE];
typedef double     D9[9];
typedef double     D10[10];
typedef double     D640[640];
typedef double     D1408[1408];
typedef double     DFFT2[FFT_SIZE/2];
typedef double     DFFT[FFT_SIZE];
typedef double     DSBL[SBLIMIT];
typedef double     D2SBL[2][SBLIMIT];
typedef double     D5SBL[5][SBLIMIT];
typedef double     D7SBL[7][SBLIMIT];  /*added because of 7 channels, 8/10/93, SR*/
typedef double     D12SBL[12][SBLIMIT];  /*added because of 12 channels, 8/10/93, SR*/

typedef struct {
        int        line;
        double     bark, hear, x;
} g_thres, *g_ptr;

typedef struct {
        double     x;
        int        type, next, map;
} mask, *mask_ptr;

/* Psychoacoustic Model 2 Type Definitions */

typedef int        ICB[CBANDS];
typedef int        IHBLK[HBLKSIZE];
typedef FLOAT      F32[32];
typedef FLOAT      F2_32[2][32];
typedef FLOAT      FCB[CBANDS];
typedef FLOAT      FCBCB[CBANDS][CBANDS];
typedef FLOAT      FBLK[BLKSIZE];
typedef FLOAT      FHBLK[HBLKSIZE];
typedef FLOAT      F2HBLK[2][HBLKSIZE];
typedef FLOAT      F22HBLK[2][2][HBLKSIZE];
typedef double     DCB[CBANDS];

/***********************************************************************
*
*  Encoder Variable External Declarations
*
***********************************************************************/

#ifdef MS_DOS
/* extern unsigned _stklen = 16384; */ /* removed, 92-07-13 sr */
#endif

/***********************************************************************
*
*  Encoder Function Prototype Declarations
*
***********************************************************************/

/* The following functions are in the file "musicin.c" */
