
#define PRINTOUT

#define	VERSION	"$Revision: 2.0 $"

#ifdef  UNIX
#define         TABLES_PATH     "tables/"  /* to find data files */
/* name of environment variable holding path of table files */
#define         MPEGTABENV      "MPEGTABLES"
#define         PATH_SEPARATOR  "/"        /* how to build paths */
#define         PROTO_ARGS                 /* unix gcc uses arg. prototypes */
#endif  /* UNIX */

/***********************************************************************
*
*  Global Include Files
*
***********************************************************************/

#include        <stdio.h>
#include        <string.h>
#include        <math.h>

#ifdef  UNIX
#include        <unistd.h>	 /* removed 92-08-05 shn */
#include	<stdlib.h>       /* put in 92-08-05 shn */
#endif  /* UNIX */


/***********************************************************************
*
*  Global Definitions
*
***********************************************************************/

/* General Definitions */

#define         FLOAT                   float

#define         FALSE                   0
#define         TRUE                    (!FALSE)
#define         NULL_CHAR               '\0'

#define         MAX_U_32_NUM            0xFFFFFFFF
#define         PI                      3.14159265358979
#define         PI4                     PI/4
#define         PI64                    PI/64
#define         LN_TO_LOG10             0.2302585093

#define         VOL_REF_NUM             0
#define         MPEG_AUDIO_ID           1
#define         MAC_WINDOW_SIZE         24

#define         MONO                    1
#define         STEREO                  2
#define         BITS_IN_A_BYTE          8
#define         WORD                    16
#define         MAX_NAME_SIZE           81
#define         SBLIMIT                 32
#define         FFT_SIZE                1024
#define         HAN_SIZE                512
#define         SCALE_BLOCK             12
#define         SCALE_RANGE             63
#define         SCALE                   32768
#define         CRC16_POLYNOMIAL        0x8005

#define         MAX_PRED_COEFF          3.96875     /* gleichfoermige Quantisierung der */
                                                    /* Praediktorkoeff. im Bereich */
                                                    /* [-MAX_PRED_COEF .. +MAX_PRED_COEF] */

#define CHANMAX1        5
#define CHANMAX2        7
#define CHANMAX3       12
#define SBGRS          12

/* Channels */

#define	    L0	    0							    
#define	    R0	    1							    
#define	    C	    2							    
#define	    LS	    3							    
#define	    RS	    4							    
#define	    L	    5							    
#define	    R	    6	
#define	    L7	    7
#define	    R7	    8							    
#define	    C7	    9
#define	    LC	    10						    
#define	    RC	    11						    


/* Sums */

#define	    T23	    0
#define	    T24	    1
#define	    T34	    2
#define	    T234    3						    
#define	    T56     4					    

/* MPEG Header Definitions - Mode Values */

#define         MPG_MD_STEREO           0
#define         MPG_MD_JOINT_STEREO     1
#define         MPG_MD_DUAL_CHANNEL     2
#define		MPG_MD_MONO		3
#define		MPG_MD_NONE		4

/* AIFF Definitions */

#ifndef	MS_DOS
#define         IFF_ID_FORM             "FORM" /* HP400 unix v8.0: double qoutes 1992-07-24 shn */
#define         IFF_ID_AIFF             "AIFF"
#define         IFF_ID_COMM             "COMM"
#define         IFF_ID_SSND             "SSND"
#define         IFF_ID_MPEG             "MPEG"
#else
#define         IFF_ID_FORM             "FORM"
#define         IFF_ID_AIFF             "AIFF"
#define         IFF_ID_COMM             "COMM"
#define         IFF_ID_SSND             "SSND"
#define         IFF_ID_MPEG             "MPEG"
#endif

/* "bit_stream.h" Definitions */

#define         MINIMUM         4    /* Minimum size of the buffer in bytes */
#define         MAX_LENGTH      32   /* Maximum length of word written or
                                        read from bit stream */
#define         READ_MODE       0
#define         WRITE_MODE      1
#define         ALIGNING        8
#define         BINARY          0
#define         ASCII           1
#define         BS_FORMAT       BINARY /* BINARY or ASCII = 2x bytes */
#define         BUFFER_SIZE     4096

#define         MIN(A, B)       ((A) < (B) ? (A) : (B))
#define         MAX(A, B)       ((A) > (B) ? (A) : (B))

/***********************************************************************
*
*  Global Type Definitions
*
***********************************************************************/

/* Structure for Reading Layer II Allocation Tables from File */

typedef struct {
        unsigned int    steps;
        unsigned int    bits;
        unsigned int    group;
        unsigned int    quant;
} sb_alloc, *alloc_ptr;

typedef sb_alloc        al_table[SBLIMIT][16];

/* Header Information Structure */

typedef struct {
    int version;
    int lay;
    int error_protection;
    int bitrate_index;
    int sampling_frequency;
    int padding;
    int extension;
    int mode;
    int mode_ext;
    int copyright;
    int original;
    int emphasis;
    int center;			 /* center present */
    int surround; 		 /* surrounds present*/
    int audio_mix;		 /* large listening room or not? */
    int matrix;			 /* type of dematricing */
    int lfe;			 /* low frequency effect channel*/
    int multiling_ch;		 /* number of multilingual channels */
    int multiling_fs;		 /* fs of ML channels is half fs of main channels */
    int multiling_lay;		 /* Layer IIML or Layer II ML is used*/
    int ext_bit_stream_present;  /* extension bitstream present? */
    int n_ad_bytes;              /* if yes, how many bits anc.data for mpeg2 */
    int mc_pred[8];		 /* prediction bit*/
    int tc_alloc[12];		 /* transmission channel allocation in each sbgroup*/
    int predsi[8][6];		 /* predictor select information*/
    int delay_comp[8][6];
    int pred_coef[8][6][3];
    int mc_prediction_on;
    int tc_sbgr_select;
    int tc_allocation;
    int dyn_cross_on;
    int dyn_cross_LR;            /* center out of Lo or Ro*/
    int dyn_cross[12];
    int ext_length;
    int ext_sync;
    int ext_bit;
    int copy_ident_bit;
    int copy_ident_start;
    int dyn_second_stereo[12];
#ifdef Augmentation_7ch
    int aug_mtx_proc;
    int aug_dyn_cross_on;
    int aug_future_ext;
    int aug_tc_alloc[12];	   /* transmission channel allocation in each sbgroup */
    int aug_dyn_cross[12];
#endif
} layer, *the_layer;



/* Parent Structure Interpreting some Frame Parameters in Header */

typedef struct {
         layer                   *header;        /* raw header information */
	 int			 actual_mode;	 /* when writing IS, may forget if 0 chs */
         al_table                *alloc;         /* bit allocation table read in */
	 al_table		 *alloc_mc;      /* MC bit allocation table read in */
         al_table                *alloc_ml;      /* ML bit allocation table read in */
         int                     tab_num;        /* number of table as loaded */
         int                     tab_num_mc;     /* number of MC table as loaded */
         int                     tab_num_ml;     /* number of ML table as loaded */
	 int			 stereo; 	 /* 1 for mono, 2 for stereo */
	 int			 stereomc;
	 int			 stereoaug;
	 int			 lfe_pos;
	 int			 jsbound;	 /* first band of joint stereo coding */
	 double		         mnr_min;	 /* mnr for dynamic bitallocation */
         int                     sblimit;        /* total number of sub bands */
         int                     sblimit_mc;     /* total number of MC sub bands */
         int                     sblimit_ml;     /* total number of ML sub bands */
	 int                     phantom_c;      /* phantom coding of Center signal */
	 int                     config;      	 /* config code: 320, 310, 300, 302, 220, 210, 200, 202, 100, 102 */
} frame_params;

/* Double and SANE Floating Point Type Definitions */

typedef struct  IEEE_DBL_struct {
                unsigned long   hi;
                unsigned long   lo;
} IEEE_DBL;

typedef struct  SANE_EXT_struct {
                unsigned long   l1;
                unsigned long   l2;
                unsigned short  s1;
} SANE_EXT;

/* AIFF Type Definitions */

typedef char	 ID[4];

typedef struct  identifier_struct{
					 ID name;
					 long ck_length;
}identifier;


typedef struct  ChunkHeader_struct {
                ID      ckID;
                long    ckSize;
} ChunkHeader;

typedef struct  Chunk_struct {
                ID      ckID;
                long    ckSize;
                ID      formType;
} Chunk;

typedef struct  CommonChunk_struct {
                ID              ckID;
                long            ckSize;
                short           numChannels;
                unsigned long   numSampleFrames;
                short           sampleSize;
                char            sampleRate[10];
} CommonChunk;

typedef struct  SoundDataChunk_struct {
                ID              ckID;
                long            ckSize;
                unsigned long   offset;
                unsigned long   blockSize;
} SoundDataChunk;

typedef struct  blockAlign_struct {
                unsigned long   offset;
                unsigned long   blockSize;
} blockAlign;

typedef struct  IFF_AIFF_struct {
                short           numChannels;
                unsigned long   numSampleFrames;
                short           sampleSize;
                double          sampleRate;
                ID/*char**/     sampleType;/*must be allocated 21.6.93 SR*/
                blockAlign      blkAlgn;
} IFF_AIFF;

/* "bit_stream.h" Type Definitions */

typedef struct  bit_stream_struc {
    FILE        *pt;            /* pointer to bit stream device */
    unsigned char *buf;         /* bit stream buffer */
    int         buf_size;       /* size of buffer (in number of bytes) */
    long        totbit;         /* bit counter of bit stream */
    int         buf_byte_idx;   /* pointer to top byte in buffer */
    int         buf_bit_idx;    /* pointer to top bit of top byte in buffer */
    int         mode;           /* bit stream open in read or write mode */
    int         eob;            /* end of buffer index */
    int         eobs;           /* end of bit stream flag */
    char        format;
/* format of file in rd mode (BINARY/ASCII) */
    } Bit_stream_struc;

/* JMZ 08/03/1995 begin SORT*/
typedef struct {
         int    tc_channel;
         int    audio_channel;
         int    subband;
         int    sbgroup;
         int    used;
         double mnr;
         int    next;
} channel_sort;
/* JMZ 08/03/1995 end SORT*/

/***********************************************************************
*
*  Global Variable External Declarations
*
***********************************************************************/

extern char     *mode_names[4];
extern char     *layer_names[3];
extern double   s_freq[4];
extern int	bitrate[3][16];
extern double	multiple[64];
extern int      sbgrp[32];
extern int      sb_groups[12];
extern int      n_pred_coef[16];          
extern int	no_channel[8][2];
extern int	T2[SBGRS], T3[SBGRS], T4[SBGRS];	 
#ifdef Augmentation_7ch
extern int	T5[SBGRS], T6[SBGRS];	 
#endif
extern int	T2outof[12], T3outof[12], T4outof[12]; /* L0 or R0 */	
extern int	T2from[12], T3from[12], T4from[12];	
extern int	verbosity;

/***********************************************************************
*
*  Global Function Prototype Declarations
*
***********************************************************************/

/* The following functions are in the file "common.c" */

void	      program_information(void);

FILE           *OpenTableFile(char *name);
//int            read_bit_alloc(int table, al_table (*alloc));
//int            pick_table(frame_params *fr_ps);
int            js_bound(int lay, int m_ext);
void           hdr_to_frps(frame_params *fr_ps);
int            BitrateIndex(int layr, int bRate);
int            SmpFrqIndex(long int sRate);
void           *mem_alloc(long unsigned int block, char *item);
void           mem_free(void **ptr_addr);
void           double_to_extended(double *pd, char *ps);
void           extended_to_double(char *ps, double *pd);
int            aiff_read_headers(FILE *file_ptr, IFF_AIFF *aiff_ptr, int *byte_per_sample);
int            aiff_seek_to_sound_data(FILE *file_ptr);
int            aiff_write_headers(FILE *file_ptr, IFF_AIFF *aiff_ptr);
int            refill_buffer(Bit_stream_struc *bs);
void           empty_buffer(Bit_stream_struc *bs, int minimum);
void           open_bit_stream_w(Bit_stream_struc *bs, char *bs_filenam, int size);
void           open_bit_stream_r(Bit_stream_struc *bs, char *bs_filenam, int size);
void           close_bit_stream_r(Bit_stream_struc *bs);
void           close_bit_stream_w(Bit_stream_struc *bs);
void           alloc_buffer(Bit_stream_struc *bs, int size);
void           desalloc_buffer(Bit_stream_struc *bs);
unsigned int   get1bit(Bit_stream_struc *bs);
void           put1bit(Bit_stream_struc *bs, int bit);
unsigned long  getbits(Bit_stream_struc *bs, int N);
void           putbits(Bit_stream_struc *bs, unsigned int val, int N);
unsigned long  sstell (Bit_stream_struc *bs);
int            end_bs (Bit_stream_struc *bs);
int            transmission_channel (frame_params *fr_ps, int sbgr, int m);
int            dyn_ch (frame_params *fr_ps, int sbgr, int m);
int            dyn_bbal (int config, int center, int dynx, int m);
int            dyn_bbal_2ndst (int dynx, int m);
void           init_mc_pred (frame_params *fr_ps);
void           set_mc_pred (frame_params *fr_ps);
