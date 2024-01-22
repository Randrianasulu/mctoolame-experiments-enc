#include "common.h"
#include "alloc_tables.h"
#include <ctype.h>
#include <stdint.h>

/***********************************************************************
*
*  Global Variable Definitions
*
***********************************************************************/

char *mode_names[4] = { "stereo", "j-stereo", "dual-ch", "single-ch" };
char *layer_names[3] = { "I", "II", "III" };

double s_freq[4] = { 44.1, 48, 32, 0 };

int bitrate[3][16] = {
  {0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 0},
  {0, 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, 0},
  {0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 0}
};

double /*far */ multiple[64] = {
  2.00000000000000, 1.58740105196820, 1.25992104989487,
  1.00000000000000, 0.79370052598410, 0.62996052494744, 0.50000000000000,
  0.39685026299205, 0.31498026247372, 0.25000000000000, 0.19842513149602,
  0.15749013123686, 0.12500000000000, 0.09921256574801, 0.07874506561843,
  0.06250000000000, 0.04960628287401, 0.03937253280921, 0.03125000000000,
  0.02480314143700, 0.01968626640461, 0.01562500000000, 0.01240157071850,
  0.00984313320230, 0.00781250000000, 0.00620078535925, 0.00492156660115,
  0.00390625000000, 0.00310039267963, 0.00246078330058, 0.00195312500000,
  0.00155019633981, 0.00123039165029, 0.00097656250000, 0.00077509816991,
  0.00061519582514, 0.00048828125000, 0.00038754908495, 0.00030759791257,
  0.00024414062500, 0.00019377454248, 0.00015379895629, 0.00012207031250,
  0.00009688727124, 0.00007689947814, 0.00006103515625, 0.00004844363562,
  0.00003844973907, 0.00003051757813, 0.00002422181781, 0.00001922486954,
  0.00001525878906, 0.00001211090890, 0.00000961243477, 0.00000762939453,
  0.00000605545445, 0.00000480621738, 0.00000381469727, 0.00000302772723,
  0.00000240310869, 0.00000190734863, 0.00000151386361, 0.00000120155435,
  1E-20
};

int sbgrp[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 9, 10, 10, 10, 10,
  11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11
};
int sb_groups[12] = { 0, 1, 2, 3, 4, 5, 6, 7, 9, 11, 15, 26 /*31 */  };


int transmission_channel7[8][2] = {	/* for 5/2 config */
  {10, 11},
  {7, 11},
  {10, 8},
  {7, 8},
  {10, 9},
  {7, 9},
  {9, 11},
  {9, 8},
};

int transmission_channel5[8][5] = {	/* for 3/2 config */
  {0, 1, 2, 3, 4},
  {0, 1, 5, 3, 4},
  {0, 1, 6, 3, 4},
  {0, 1, 2, 5, 4},
  {0, 1, 2, 3, 6},
  {0, 1, 2, 5, 6},
  {0, 1, 6, 5, 4},
  {0, 1, 5, 3, 6},
};

int transmission_channel4a[6][4] = {	/* for 3/1 config */
  {0, 1, 2, 3},
  {0, 1, 5, 3},
  {0, 1, 6, 3},
  {0, 1, 2, 5},
  {0, 1, 2, 6},
  {0, 1, 5, 6},
};

int transmission_channel4b[4][4] = {	/* for 2/2 config */
  {0, 1, 2, 3},
  {0, 1, 5, 3},
  {0, 1, 2, 6},
  {0, 1, 5, 6},
};

int transmission_channel3[3][5] = {	/* for 3/0 (+ 2/0) and 2/1 config's */
  {0, 1, 2, 3, 4},
  {0, 1, 5, 3, 4},
  {0, 1, 6, 3, 4},
};

int no_channel[8][2] = {
  {5, 6},
  {2, 6},
  {5, 2},
  {3, 6},
  {5, 4},
  {3, 4},
  {3, 2},
  {2, 4},
};


int n_pred_coef[16];
int n_pred_coef4[16] = { 6, 4, 4, 4, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0 };
int n_pred_coef3[16] = { 4, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int n_pred_coef1[16] = { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int dyn_bbal5[19][12] = {	/* for 5/2 config */
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
};
int dyn_bbal4[15][12] = {	/* for 3/2 config */
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {12, 12, 12, 12, 12, 12, 12, 12, 24, 21, 36, 87},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
};
int dyn_bbal4PhC[15][12] = {	/* for 3/2 config in case of Phantom center coding */
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 0, 0},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 12, 29},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 12, 29},
  {12, 12, 12, 12, 12, 12, 12, 12, 24, 21, 24, 58},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 12, 29},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
};
int dyn_bbal3[5][12] = {	/* for 3/1 and 2/2 config */
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 24, 58},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
};
int dyn_bbal3PhC[5][12] = {	/* for 3/1 config in case of Phantom center coding */
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 0, 0},
  {8, 8, 8, 8, 8, 8, 8, 8, 16, 14, 12, 29},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
};
int dyn_bbal1[2][12] = {	/* for 3/0 (+2/0) and 2/1 config */
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 12, 29},
};
int dyn_bbal1PhC[2][12] = {	/* for 3/0 (+2/0) config in case of Phantom center coding */
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 0, 0},
};


int dyn_ch5[19][2] = {		/* for 5/2 config */
  {1, 1},
  {1, 0},
  {1, 0},
  {1, 0},
  {1, 0},
  {0, 1},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 1},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 1},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
};

int dyn_ch4[15][3] = {		/* for 3/2 config */
  {1, 1, 1},
  {1, 1, 0},
  {1, 0, 1},
  {0, 1, 1},
  {1, 0, 0},
  {0, 1, 0},
  {0, 0, 1},
  {0, 0, 0},
  {1, 1, 0},
  {1, 0, 1},
  {1, 1, 0},
  {1, 0, 0},
  {1, 0, 0},
  {0, 1, 0},
  {1, 0, 0},
};

int dyn_ch3[5][2] = {		/* for 3/1 and 2/2 config */
  {1, 1},
  {1, 0},
  {0, 1},
  {0, 0},
  {1, 0},
};

int dyn_ch1[2][3] = {		/* for 3/0 (+2/0) and 2/1 config */
  {1, 1, 1},
  {0, 1, 1},
};

int T2[12], T3[12], T4[12], T5[12], T6[12];
int T2outof[12], T3outof[12], T4outof[12];	/* L0 or R0 */
int T2from[12], T3from[12], T4from[12];


/***********************************************************************
*
*  Global Function Definitions
*
***********************************************************************/

void program_information (void)
{
  printf ("ISO MPEG Audio Subgroup Software Simulation Group (1996)\n");
  printf ("ISO 13818-3 MPEG-2 Audio Multichannel Encoder\n");
  printf ("%s\n", VERSION);
}

/* The system uses a variety of data files.  By opening them via this
   function, we can accommodate various locations. */

FILE *OpenTableFile (char *name)
{
  char fulname[80];
  char *envdir;
  FILE *f;

  fulname[0] = '\0';

#ifdef TABLES_PATH
  strcpy (fulname, TABLES_PATH);	/* default relative path for tables */
#endif	/* TABLES_PATH */		 /* (includes terminal path seperator */

#ifdef UNIX			/* envir. variables for UNIX only */
  {
    char *getenv (const char *);

    envdir = getenv (MPEGTABENV);	/* check for environment */
    if (envdir != NULL)
      strcpy (fulname, envdir);
    strcat (fulname, PATH_SEPARATOR);	/* add a "/" on the end */
  }
#endif /* UNIX */

  strcat (fulname, name);
  if ((f = fopen (fulname, "r")) == NULL) {
    fprintf (stderr, "OpenTable: could not find %s\n", fulname);

#ifdef UNIX
    if (envdir != NULL)
      fprintf (stderr, "Check %s directory '%s'\n", MPEGTABENV, envdir);
    else
      fprintf (stderr, "Check local directory './%s' or setenv %s\n",
	       TABLES_PATH, MPEGTABENV);
#else /* not unix : no environment variables */

#ifdef TABLES_PATH
    fprintf (stderr, "Check local directory './%s'\n", TABLES_PATH);
#endif /* TABLES_PATH */

#endif /* UNIX */

  }
  return f;
}



int js_bound (int lay, int m_ext)
{
  static int jsb_table[3][4] = { {4, 8, 12, 16}, {4, 8, 12, 16},
  {0, 4, 8, 16}
  };				/* lay+m_e -> jsbound */

  if (lay < 1 || lay > 3 || m_ext < 0 || m_ext > 3) {
    fprintf (stderr, "js_bound bad layer/modext (%d/%d)\n", lay, m_ext);
    exit (1);
  }

  return (jsb_table[lay - 1][m_ext]);
}

void hdr_to_frps (frame_params * fr_ps)
{				/* interpret data in hdr str to fields in fr_ps */
  layer *hdr = fr_ps->header;	/* (or pass in as arg?) */

  fr_ps->actual_mode = hdr->mode;
  if (hdr->mode != MPG_MD_NONE)
    fr_ps->stereo = (hdr->mode == MPG_MD_MONO) ? 1 : 2;
  else
    fr_ps->stereo = 0;

  if (verbosity >= 2)
    printf ("stereo = %d stereomc = %d stereoaug = %d\n",
	    fr_ps->stereo, fr_ps->stereomc, fr_ps->stereoaug);

  if (hdr->lay == 2)
    fr_ps->sblimit = pick_table (fr_ps);
  else
    fr_ps->sblimit = SBLIMIT;

  if (hdr->mode == MPG_MD_JOINT_STEREO)
    fr_ps->jsbound = js_bound (hdr->lay, hdr->mode_ext);
  else
    fr_ps->jsbound = fr_ps->sblimit;

  if (hdr->multiling_ch > 0 && hdr->multiling_lay > 0) {
    fprintf (stderr, "MultiLingual not in Layer 2!\n exit.\n");
    exit (1);
  }

  if (fr_ps->stereomc > 0 || hdr->lfe || hdr->multiling_ch > 0)
    mc_pick_table (fr_ps);
}

int BitrateIndex (int layr, int bRate)

{				/* convert bitrate in kbps to index */
  /* 1 or 2 */
  /* legal rates from 32 to 448 */
  int index = 0;
  int found = 0;

  while (!found && index < 15) {
    if (bitrate[layr - 1][index] == bRate)
      found = 1;
    else
      ++index;
  }
  if (found)
    return (index);
  else {
    fprintf (stderr, "BitrateIndex: %d (layer %d) is not a legal bitrate\n",
	     bRate, layr);
    return (-1);		/* Error! */
  }
}

int SmpFrqIndex (long int sRate)



{				/* convert samp frq in Hz to index */
  /* for MultiLingual LSF                                                       */
  /* Note this function differs from the one called upon MPEG2 Audio-LSF coding */
  /* The value '16' is used to detect half sample rate of ML wrt. MC            */
  /* 7/8/95 WtK                                                                 */
  switch (sRate) {
  case 44100:
    return (0);
    break;
  case 48000:
    return (1);
    break;
  case 32000:
    return (2);
    break;
  case 22050:
    return (16);
    break;
  case 24000:
    return (17);
    break;
  case 16000:
    return (18);
    break;
  default:
    fprintf (stderr, "SmpFrqIndex: %ld is not a legal sample rate\n", sRate);
    return (-1);		/* Error! */
  }
}

/*******************************************************************************
*
*  Allocate number of bytes of memory equal to "block".
*
*******************************************************************************/

void *mem_alloc (long unsigned int block, char *item)
{
  void *ptr;

  ptr = (void *) malloc (block);

  if (ptr != NULL) 
    memset (ptr, 0, block);
  else {
    printf ("Unable to allocate %s\n", item);
    exit (1);
  }

  return (ptr);
}

/****************************************************************************
*
*  Free memory pointed to by "*ptr_addr".
*
*****************************************************************************/

void mem_free (void **ptr_addr)
{
  if (*ptr_addr != NULL) {
    free (*ptr_addr);
    *ptr_addr = NULL;
  }
}

/****************************************************************************
*
*  Routines to convert between the Apple SANE extended floating point format
*  and the IEEE double precision floating point format.  These routines are
*  called from within the Audio Interchange File Format (AIFF) routines.
*
*****************************************************************************/

/*
*** Apple's 80-bit SANE extended has the following format:

 1       15      1            63
+-+-------------+-+-----------------------------+
|s|       e     |i|            f                |
+-+-------------+-+-----------------------------+
  msb        lsb   msb                       lsb

The value v of the number is determined by these fields as follows:
If 0 <= e < 32767,              then v = (-1)^s * 2^(e-16383) * (i.f).
If e == 32767 and f == 0,       then v = (-1)^s * (infinity), regardless of i.
If e == 32767 and f != 0,       then v is a NaN, regardless of i.

*** IEEE Draft Standard 754 Double Precision has the following format:

MSB
+-+---------+-----------------------------+
|1| 11 Bits |           52 Bits           |
+-+---------+-----------------------------+
 ^     ^                ^
 |     |                |
 Sign  Exponent         Mantissa
*/

/*****************************************************************************
*
*  double_to_extended()
*
*  Purpose:     Convert from IEEE double precision format to SANE extended
*               format.
*
*  Passed:      Pointer to the double precision number and a pointer to what
*               will hold the Apple SANE extended format value.
*
*  Outputs:     The SANE extended format pointer will be filled with the
*               converted value.
*
*  Returned:    Nothing.
*
*****************************************************************************/


void double_to_extended (double *pd, char *ps)
{

#ifdef  MACINTOSH

  x96tox80 (pd, (extended *) ps);

#else

/* fixed bus alignment error, HP 27-may-93 */

  register unsigned long top2bits;

  register unsigned short *ps2;
  register IEEE_DBL *p_dbl;
  register SANE_EXT *p_ext;
  SANE_EXT ext_align;
  char *c_align;
  int i;

  p_dbl = (IEEE_DBL *) pd;
  p_ext = &ext_align;
  top2bits = p_dbl->hi & 0xc0000000;
  p_ext->l1 = ((p_dbl->hi >> 4) & 0x3ff0000) | top2bits;
  p_ext->l1 |= ((p_dbl->hi >> 5) & 0x7fff) | 0x8000;
  p_ext->l2 = (p_dbl->hi << 27) & 0xf8000000;
  p_ext->l2 |= ((p_dbl->lo >> 5) & 0x07ffffff);
  ps2 = (unsigned short *) &(p_dbl->lo);
  ps2++;
  p_ext->s1 = (*ps2 << 11) & 0xf800;

  c_align = (char *) p_ext;
  for (i = 0; i < 10; i++)
    ps[i] = c_align[i];

#endif

}


/*****************************************************************************
*
*  extended_to_double()
*
*  Purpose:     Convert from SANE extended format to IEEE double precision
*               format.
*
*  Passed:      Pointer to the Apple SANE extended format value and a pointer
*               to what will hold the the IEEE double precision number.
*
*  Outputs:     The IEEE double precision format pointer will be filled with
*               the converted value.
*
*  Returned:    Nothing.
*
*****************************************************************************/

void extended_to_double (char *ps, double *pd)
{

#ifdef  MACINTOSH

  x80tox96 ((extended *) ps, pd);

#else

/* fixed bus alignment error, HP 27-may-93 */

  register unsigned long top2bits;

  register IEEE_DBL *p_dbl;
  register SANE_EXT *p_ext;
  SANE_EXT ext_align;
  char *c_align;
  int i;

  p_dbl = (IEEE_DBL *) pd;
  p_ext = &ext_align;

  c_align = (char *) p_ext;
  for (i = 0; i < 10; i++)
    c_align[i] = ps[i];

  top2bits = p_ext->l1 & 0xc0000000;
  p_dbl->hi = ((p_ext->l1 << 4) & 0x3ff00000) | top2bits;
  p_dbl->hi |= (p_ext->l1 << 5) & 0xffff0;
  p_dbl->hi |= (p_ext->l2 >> 27) & 0x1f;
  p_dbl->lo = (p_ext->l2 << 5) & 0xffffffe0;
  p_dbl->lo |= (unsigned long) ((p_ext->s1 >> 11) & 0x1f);

#endif

}

//byteswap from stackoverflow.
// https://stackoverflow.com/questions/2182002/how-to-convert-big-endian-to-little-endian-in-c-without-using-library-functions


//! Byte swap unsigned short
uint16_t swap_uint16( uint16_t val )
{
    return (val << 8) | (val >> 8 );
}

//! Byte swap short
int16_t swap_int16( int16_t val )
{
    return (val << 8) | ((val >> 8) & 0xFF);
}

//! Byte swap unsigned int
uint32_t swap_uint32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
    return (val << 16) | (val >> 16);
}

//! Byte swap int
int32_t swap_int32( int32_t val )
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF );
    return (val << 16) | ((val >> 16) & 0xFFFF);
}

#define IFF_ID_FORM 0x464f524d	/* "FORM" */
#define IFF_ID_AIFF 0x41494646	/* "AIFF" */
#define IFF_ID_COMM 0x434f4d4d	/* "COMM" */
#define IFF_ID_SSND 0x53534e44	/* "SSND" */
#define IFF_ID_MPEG 0x4d504547	/* "MPEG" */

#define AIFF_FORM_HEADER_SIZE 12
#define AIFF_SSND_HEADER_SIZE 16

#define	kFloatLength	4
#define	kDoubleLength	8
#define	kExtendedLength	10

# define FloatToUnsigned(f)	((unsigned long)(((long)((f) - 2147483648.0)) + 2147483647L + 1))
# define UnsignedToFloat(u)	(((double)((long)((u) - 2147483647L - 1))) + 2147483648.0)

static double ConvertFromIeeeExtended (char *bytes)
{
  double f;
  long expon;
  unsigned long hiMant, loMant;

  expon = ((bytes[0] & 0x7F) << 8) | (bytes[1] & 0xFF);
  hiMant = ((unsigned long) (bytes[2] & 0xFF) << 24)
    | ((unsigned long) (bytes[3] & 0xFF) << 16) |
    ((unsigned long) (bytes[4] & 0xFF) << 8) |
    ((unsigned long) (bytes[5] & 0xFF));
  loMant = ((unsigned long) (bytes[6] & 0xFF) << 24)
    | ((unsigned long) (bytes[7] & 0xFF) << 16) |
    ((unsigned long) (bytes[8] & 0xFF) << 8) |
    ((unsigned long) (bytes[9] & 0xFF));

  if (expon == 0 && hiMant == 0 && loMant == 0) {
    f = 0;
  } else {
    if (expon == 0x7FFF) {	/* Infinity or NaN */
      f = HUGE_VAL;
    } else {
      expon -= 16383;
      f = ldexp (UnsignedToFloat (hiMant), expon -= 31);
      f += ldexp (UnsignedToFloat (loMant), expon -= 32);
    }
  }

  if (bytes[0] & 0x80)
    return -f;
  else
    return f;
}

static void ReadBytes (FILE *fp, char *p, int n)
{
  while (!feof (fp) & (n-- > 0))
    *p++ = getc (fp);
}

static int Read16BitsHighLow (FILE *fp)
{
  int first, second, result;

  first = 0xff & getc (fp);
  second = 0xff & getc (fp);

  result = (first << 8) + second;
  return (result);
}

static double ReadIeeeExtendedHighLow (FILE *fp)
{
  char bits[kExtendedLength];

  ReadBytes (fp, bits, kExtendedLength);
  return ConvertFromIeeeExtended (bits);
}

static int Read32BitsHighLow (FILE *fp)
{
  int first, second, result;

  first = 0xffff & Read16BitsHighLow (fp);
  second = 0xffff & Read16BitsHighLow (fp);

  result = (first << 16) + second;
  return (result);
}




/*****************************************************************************
 *
 *  Read Audio Interchange File Format (AIFF) headers.
 *
 *****************************************************************************/

int aiff_read_headers (FILE * file_ptr, IFF_AIFF * aiff_ptr, int *byte_per_sample)
{
  int chunkSize, subSize, sound_position;
  unsigned long offset;

  if (fseek (file_ptr, 0, SEEK_SET) != 0)
    return -1;

  if (Read32BitsHighLow (file_ptr) != IFF_ID_FORM)
    return -1;

  chunkSize = Read32BitsHighLow (file_ptr);

  if (Read32BitsHighLow (file_ptr) != IFF_ID_AIFF)
    return -1;

  sound_position = 0;
  while (chunkSize > 0) {
    chunkSize -= 4;
    switch (Read32BitsHighLow (file_ptr)) {

    case IFF_ID_COMM:
      chunkSize -= subSize = Read32BitsHighLow (file_ptr);
      aiff_ptr->numChannels = Read16BitsHighLow (file_ptr);
      subSize -= 2;
      aiff_ptr->numSampleFrames = Read32BitsHighLow (file_ptr);
      subSize -= 4;
      aiff_ptr->sampleSize = Read16BitsHighLow (file_ptr);
      subSize -= 2;
      *byte_per_sample = ceil (aiff_ptr->sampleSize / 8);
      aiff_ptr->sampleRate = (double)ReadIeeeExtendedHighLow (file_ptr);
      subSize -= 10;
      
      printf("Num. ch: %i \n", aiff_ptr->numChannels);
      printf("Samples per frame %i \n", aiff_ptr->numSampleFrames);
      printf("Sample size in bits %i \n", aiff_ptr->sampleSize);
      printf("Sample rate %f \n", aiff_ptr->sampleRate);
      
      while (subSize > 0) {
    getc (file_ptr);
    subSize -= 1;
      }
      break;

    case IFF_ID_SSND:
      //aiff_ptr->sampleType = IFF_ID_SSND; 
      chunkSize -= subSize = Read32BitsHighLow (file_ptr);
      //aiff_ptr->blkAlgn.offset = Read32BitsHighLow (file_ptr);
      offset = Read32BitsHighLow (file_ptr);
      subSize -= 4;
      //aiff_ptr->blkAlgn.blockSize = Read32BitsHighLow (file_ptr);
      Read32BitsHighLow (file_ptr);
      subSize -= 4;
      sound_position = ftell (file_ptr) + offset; //aiff_ptr->blkAlgn.offset;
      if (fseek (file_ptr, (long) subSize, SEEK_CUR) != 0) {
    printf("Seek failed! \n"); return -1; }
      break;
      
    default:
      chunkSize -= subSize = Read32BitsHighLow (file_ptr);
      while (subSize > 0) {
    getc (file_ptr);
    subSize -= 1;
      }
      break;
    }
  }

    return 0;
  //return sound_position;
}



/*****************************************************************************
*
*  Read Audio Interchange File Format (AIFF) headers.
*
*****************************************************************************/
#if 0

int aiff_read_headers (FILE * file_ptr, IFF_AIFF * aiff_ptr,
		       int *byte_per_sample)
{


  register int i;
  //  register long seek_offset;

  char temp_sampleRate[10];
  char *dummy;
  //MFC char holder;
  Chunk FormChunk;
  CommonChunk CommChunk;
  SoundDataChunk SndDChunk;
  identifier ident;

  if (fseek (file_ptr, 0, SEEK_SET) != 0)
    return (-1);

  if (fread (&FormChunk, sizeof (Chunk), 1, file_ptr) != 1)
    return (-1);

#ifdef MSDOS
  holder = FormChunk.ckID[0];
  FormChunk.ckID[0] = FormChunk.ckID[3];
  FormChunk.ckID[3] = holder;
  holder = FormChunk.ckID[1];
  FormChunk.ckID[1] = FormChunk.ckID[2];
  FormChunk.ckID[2] = holder;
/* fixed bug in next line, HP 27-may-93 */
  holder = FormChunk.formType[0];
  FormChunk.formType[0] = FormChunk.formType[3];
  FormChunk.formType[3] = holder;
  holder = FormChunk.formType[1];
  FormChunk.formType[1] = FormChunk.formType[2];
  FormChunk.formType[2] = holder;
  FormChunk.ckSize = _lrotl (FormChunk.ckSize, 8);
#endif


/* fixed bug in next line, HP 27-may-93 */
  if (strncmp (FormChunk.ckID, IFF_ID_FORM, 4) != 0 ||
      strncmp (FormChunk.formType, IFF_ID_AIFF, 4) != 0)
    return (-1);		/* warning: different levels of indirection.7/8/92.sr */

  if (fread (&ident, sizeof (identifier), 1, file_ptr) != 1)
    return (-1);

printf("Common.C after identifier \n");

#ifdef MSDOS
  holder = ident.name[0];
  ident.name[0] = ident.name[3];
  ident.name[3] = holder;
  holder = ident.name[1];
  ident.name[1] = ident.name[2];
  ident.name[2] = holder;
  ident.ck_length = _lrotl (ident.ck_length, 8);
#endif


/* fixed bug in next line, HP 27-may-93 */
  while (strncmp (ident.name, IFF_ID_COMM, 4) != 0) {
    dummy = (char *) mem_alloc (ident.ck_length * sizeof (char), "dummy");
    if(!dummy) printf("Eii! \n");
    if (fread (dummy, ident.ck_length, 1, file_ptr) != 1)
      return (-1);
      
      printf ("common.c After dummy \n");
      
    mem_free ((void **) &dummy);
/* fixed bug in next line, HP 27-may-93 */
    if (fread (&ident, sizeof (identifier), 1, file_ptr) != 1)
      return (-1);


#ifdef MSDOS
    holder = ident.name[0];
    ident.name[0] = ident.name[3];
    ident.name[3] = holder;
    holder = ident.name[1];
    ident.name[1] = ident.name[2];
    ident.name[2] = holder;
    ident.ck_length = _lrotl (ident.ck_length, 8);
#endif
  }

  for (i = 0; i < 4; ++i)
    CommChunk.ckID[i] = ident.name[i];

  CommChunk.ckSize = ident.ck_length;

  if (fread (&CommChunk.numChannels, sizeof (short), 1, file_ptr) != 1)
    return (-1);
    
    printf("Common.c - after NumChannels : swapped numch = %i \n", swap_int16(CommChunk.numChannels));

  if (fread (&CommChunk.numSampleFrames, sizeof (unsigned long), 1, file_ptr) !=
      1)
    return (-1);

  if (fread (&CommChunk.sampleSize, sizeof (short), 1, file_ptr) != 1)
    return (-1);

  if (fread (CommChunk.sampleRate, sizeof (char[10]), 1, file_ptr) != 1)
    return (-1);

#ifdef MSDOS
  CommChunk.sampleSize = _rotl (CommChunk.sampleSize, 8);
  CommChunk.ckSize = _lrotl (CommChunk.ckSize, 8);
  CommChunk.numChannels = _rotl (CommChunk.numChannels, 8);
  CommChunk.numSampleFrames = _lrotl (CommChunk.numSampleFrames, 8);
#endif

  *byte_per_sample = ceil ((double) CommChunk.sampleSize / 8);

  for (i = 0; i < sizeof (char[10]); i++)
    temp_sampleRate[i] = CommChunk.sampleRate[i];

  extended_to_double (temp_sampleRate, &aiff_ptr->sampleRate);
  
  printf("common.c after extend to double \n");


/* to start the search again from the beginning, HP 27-may-93 */

  fseek (file_ptr, 0, SEEK_SET);

  if (fread (&ident, sizeof (identifier), 1, file_ptr) != 1)
    return (-1);
    
    printf("common.c after seek to beginning 2 \n");

#ifdef MSDOS
  holder = ident.name[0];
  ident.name[0] = ident.name[3];
  ident.name[3] = holder;
  holder = ident.name[1];
  ident.name[1] = ident.name[2];
  ident.name[2] = holder;
  ident.ck_length = _lrotl (ident.ck_length, 8);
#endif
#if 1

/* fixed bug in next line, HP 27-may-93 */
  while (strncmp (ident.name, IFF_ID_SSND, 4) != 0) {
    dummy = (char *) mem_alloc (ident.ck_length * sizeof (char), "dummy");
    int ret = fread (dummy, ident.ck_length, 1, file_ptr);
    if ( ret != 1)
      {
      printf("fread 1 failed, retcode  %i \n", ret);
      //return (-1);
      }
    //printf("after syrncmp ssnd \n");

    mem_free ((void **) &dummy);
    int ret1 = fread (&ident, sizeof (identifier), 1, file_ptr);
    if ( ret1 != 1)
      {
      printf("fread 2 failed! ret %i \n", ret1);
      return (-1);
      }
      
      //printf("common.c after ssnd \n");
/* the following lines are not necessary, HP 27-may-93 */
/*
	{
	fseek (file_ptr, 0, SEEK_SET);
	if (fread (&ident, sizeof (identifier), 1, file_ptr) != 1)
	return (-1);
	}
*/

#ifdef MSDOS
    holder = ident.name[0];
    ident.name[0] = ident.name[3];
    ident.name[3] = holder;
    holder = ident.name[1];
    ident.name[1] = ident.name[2];
    ident.name[2] = holder;
    ident.ck_length = _lrotl (ident.ck_length, 8);
#endif
  }

  for (i = 0; i < 4; ++i)
    SndDChunk.ckID[i] = ident.name[i];
  SndDChunk.ckSize = ident.ck_length;

  if (fread (&SndDChunk.offset, sizeof (unsigned long), 1, file_ptr) != 1)
    return (-1);

  if (fread (&SndDChunk.blockSize, sizeof (unsigned long), 1, file_ptr) != 1)
    return (-1);
    
    printf("common.c after BlockSize \n");

#ifdef MSDOS
  SndDChunk.offset = _lrotl (SndDChunk.offset, 8);
  SndDChunk.blockSize = _lrotl (SndDChunk.blockSize, 8);
#endif

/* why seek behinde the SSND Chunk ????, HP 27-may-93 */
/*
    seek_offset = SndDChunk.ckSize - sizeof (SoundDataChunk) + sizeof (ChunkHeader);

    if (fseek (file_ptr, seek_offset, SEEK_CUR) != 0)
	return (-1);
*/
#endif

  aiff_ptr->numChannels = swap_int16(CommChunk.numChannels);
  aiff_ptr->numSampleFrames = swap_uint32(CommChunk.numSampleFrames);
  aiff_ptr->sampleSize = swap_int16(CommChunk.sampleSize);
  aiff_ptr->blkAlgn.offset = swap_uint32(SndDChunk.offset);
  aiff_ptr->blkAlgn.blockSize = swap_uint32(SndDChunk.blockSize);
  strncpy (aiff_ptr->sampleType, SndDChunk.ckID, 4);

  return (0);
}
#endif // old aiff_read_headers 

/*****************************************************************************
*
*  Seek past some Audio Interchange File Format (AIFF) headers to sound data.
*
*****************************************************************************/

int aiff_seek_to_sound_data (FILE * file_ptr)
{
  if (fseek (file_ptr, sizeof (Chunk) + sizeof (SoundDataChunk), SEEK_SET) != 0)
    return (-1);
  else
    return (0);
}

/*******************************************************************************
*
*  Write Audio Interchange File Format (AIFF) headers.
*
*******************************************************************************/

int aiff_write_headers (FILE * file_ptr, IFF_AIFF * aiff_ptr)
{
  register short int i;
  register long seek_offset;

  char temp_sampleRate[10];

  Chunk FormChunk;
  CommonChunk CommChunk;
  SoundDataChunk SndDChunk;

  strcpy (FormChunk.ckID, IFF_ID_FORM);
  strcpy (FormChunk.formType, IFF_ID_AIFF);
  strcpy (CommChunk.ckID, IFF_ID_COMM);	/*7/7/93,SR,changed FormChunk to CommChunk */

  double_to_extended (&aiff_ptr->sampleRate, temp_sampleRate);

  for (i = 0; i < sizeof (char[10]); i++)
    CommChunk.sampleRate[i] = temp_sampleRate[i];

  CommChunk.numChannels = aiff_ptr->numChannels;
  CommChunk.numSampleFrames = aiff_ptr->numSampleFrames;
  CommChunk.sampleSize = aiff_ptr->sampleSize;
  SndDChunk.offset = aiff_ptr->blkAlgn.offset;
  SndDChunk.blockSize = aiff_ptr->blkAlgn.blockSize;
  strncpy (SndDChunk.ckID, aiff_ptr->sampleType, 4);

  CommChunk.ckSize = sizeof (CommChunk.numChannels) +
    sizeof (CommChunk.numSampleFrames) +
    sizeof (CommChunk.sampleSize) + sizeof (CommChunk.sampleRate);

  SndDChunk.ckSize = sizeof (SoundDataChunk) - sizeof (ChunkHeader) +
    (CommChunk.sampleSize + BITS_IN_A_BYTE - 1) / BITS_IN_A_BYTE *
    CommChunk.numChannels * CommChunk.numSampleFrames;

  FormChunk.ckSize = sizeof (Chunk) + SndDChunk.ckSize + sizeof (ChunkHeader) +
    CommChunk.ckSize;

  if (fseek (file_ptr, 0, SEEK_SET) != 0)
    return (-1);

  if (fwrite (&FormChunk, sizeof (Chunk), 1, file_ptr) != 1)
    return (-1);

  if (fwrite (&SndDChunk, sizeof (SoundDataChunk), 1, file_ptr) != 1)
    return (-1);

  seek_offset =
    SndDChunk.ckSize - sizeof (SoundDataChunk) + sizeof (ChunkHeader);

  if (fseek (file_ptr, seek_offset, SEEK_CUR) != 0)
    return (-1);

  if (fwrite (CommChunk.ckID, sizeof (ID), 1, file_ptr) != 1)
    return (-1);

  if (fwrite (&CommChunk.ckSize, sizeof (long), 1, file_ptr) != 1)
    return (-1);

  if (fwrite (&CommChunk.numChannels, sizeof (short), 1, file_ptr) != 1)
    return (-1);

  if (fwrite (&CommChunk.numSampleFrames, sizeof (unsigned long), 1, file_ptr)
      != 1)
    return (-1);

  if (fwrite (&CommChunk.sampleSize, sizeof (short), 1, file_ptr) != 1)
    return (-1);

  if (fwrite (CommChunk.sampleRate, sizeof (char[10]), 1, file_ptr) != 1)
    return (-1);

  return (0);
}

/*****************************************************************************
*
*  bit_stream.c package
*  Author:  Jean-Georges Fritsch, C-Cube Microsystems
*
*****************************************************************************/

/********************************************************************
  This package provides functions to write (exclusive or read)
  information from (exclusive or to) the bit stream.

  If the bit stream is opened in read mode only the get functions are
  available. If the bit stream is opened in write mode only the put
  functions are available.
********************************************************************/

/* refill the buffer from the input device when the buffer becomes empty    */
int refill_buffer (Bit_stream_struc * bs)
			/* bit stream structure */
{
  register int i = bs->buf_size - 2 - bs->buf_byte_idx;
  register unsigned long n=0;
  register int index = 0;
  char val[2];

  while ((i >= 0) && (!bs->eob)) {

    if (bs->format == BINARY)
      n = fread (&bs->buf[i--], sizeof (unsigned char), 1, bs->pt);

    else {
      while ((index < 2) && n) {
	n = fread (&val[index], sizeof (char), 1, bs->pt);
	switch (val[index]) {
	case 0x30:
	case 0x31:
	case 0x32:
	case 0x33:
	case 0x34:
	case 0x35:
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x44:
	case 0x45:
	case 0x46:
	  index++;
	  break;
	default:
	  break;
	}
      }

      if (val[0] <= 0x39)
	bs->buf[i] = (val[0] - 0x30) << 4;
      else
	bs->buf[i] = (val[0] - 0x37) << 4;
      if (val[1] <= 0x39)
	bs->buf[i--] |= (val[1] - 0x30);
      else
	bs->buf[i--] |= (val[1] - 0x37);
      index = 0;
    }

    if (!n) {
      bs->eob = i + 1;
    }

  }
  return (0); //MFC fixme: this func may as well be void()
}

// MFC static char *he = "0123456789ABCDEF";

/* empty the buffer to the output device when the buffer becomes full */
void empty_buffer (Bit_stream_struc * bs, int minimum)
			/* bit stream structure */
			/* end of the buffer to empty */
{
  register int i;

#if BS_FORMAT == BINARY
  for (i = bs->buf_size - 1; i >= minimum; i--)
    fwrite (&bs->buf[i], sizeof (unsigned char), 1, bs->pt);
#else
  for (i = bs->buf_size - 1; i >= minimum; i--) {
    char val[2];
    val[0] = he[((bs->buf[i] >> 4) & 0x0F)];
    val[1] = he[(bs->buf[i] & 0x0F)];
    fwrite (val, sizeof (char), 2, bs->pt);
  }
#endif

  for (i = minimum - 1; i >= 0; i--)
    bs->buf[bs->buf_size - minimum + i] = bs->buf[i];

  bs->buf_byte_idx = bs->buf_size - 1 - minimum;
  bs->buf_bit_idx = 8;
}

/* open the device to write the bit stream into it */
void open_bit_stream_w (Bit_stream_struc * bs, char *bs_filenam, int size)
			/* bit stream structure */
			/* name of the bit stream file */
			/* size of the buffer */
{
  if ((bs->pt = fopen (bs_filenam, "w+")) == NULL) {
    printf ("Could not create \"%s\".\n", bs_filenam);
    exit (0);
  }
  alloc_buffer (bs, size);
  bs->buf_byte_idx = size - 1;
  bs->buf_bit_idx = 8;
  bs->totbit = 0;
  bs->mode = WRITE_MODE;
  bs->eob = FALSE;
  bs->eobs = FALSE;
}

/* open the device to read the bit stream from it */
void open_bit_stream_r (Bit_stream_struc * bs, char *bs_filenam, int size)
			/* bit stream structure */
			/* name of the bit stream file */
			/* size of the buffer */
{
  register unsigned long n;
  register int i = 0;
  register unsigned char flag = 1;
  unsigned char val;

  if ((bs->pt = fopen (bs_filenam, "rb")) == NULL) {
    printf ("Could not find \"%s\".\n", bs_filenam);
    exit (0);
  }

  do {
    n = fread (&val, sizeof (unsigned char), 1, bs->pt);
    switch (val) {
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0xa:			/* \n */
      break;

    default:			/* detection of an binary character */
      flag--;
      i = 300;
      break;
    }

  } while (flag & n);

  if (flag) {
    if (verbosity >= 2)
      printf ("the bit stream file %s is an ASCII file\n", bs_filenam);
    bs->format = ASCII;
  } else {
    bs->format = BINARY;
    if (verbosity >= 2)
      printf ("the bit stream file %s is a BINARY file\n", bs_filenam);
  }

  fclose (bs->pt);

  if ((bs->pt = fopen (bs_filenam, "rb")) == NULL) {
    printf ("Could not find \"%s\".\n", bs_filenam);
    exit (0);
  }

  alloc_buffer (bs, size);
  bs->buf_byte_idx = 0;
  bs->buf_bit_idx = 0;
  bs->totbit = 0;
  bs->mode = READ_MODE;
  bs->eob = FALSE;
  bs->eobs = FALSE;
}

/* close the device containing the bit stream after a read process */
void close_bit_stream_r (Bit_stream_struc * bs)
{
  fclose (bs->pt);
  desalloc_buffer (bs);
}

/*close the device containing the bit stream after a write process*/
void close_bit_stream_w (Bit_stream_struc * bs)
{
  empty_buffer (bs, bs->buf_byte_idx + 1);
  fclose (bs->pt);
  desalloc_buffer (bs);
}

/* open and initialize the buffer; */
void alloc_buffer (Bit_stream_struc * bs, int size)
{
  bs->buf =
    (unsigned char *) mem_alloc (size * sizeof (unsigned char), "buffer");
  bs->buf_size = size;
}

/* empty and close the buffer */
void desalloc_buffer (Bit_stream_struc * bs)
{
  free (bs->buf);
}

int putmask[9] = { 0x0, 0x1, 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff };
int mask[8] = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80 };

/*read 1 bit from the bit stream */
unsigned int get1bit (Bit_stream_struc * bs)
			/* bit stream structure */
{
  unsigned int bit;
  register int i;

  bs->totbit++;

  if (!bs->buf_bit_idx) {
    bs->buf_bit_idx = 8;
    bs->buf_byte_idx--;
    if ((bs->buf_byte_idx < MINIMUM) || (bs->buf_byte_idx < bs->eob)) {
      if (bs->eob)
	bs->eobs = TRUE;
      else {
	for (i = bs->buf_byte_idx; i >= 0; i--)
	  bs->buf[bs->buf_size - 1 - bs->buf_byte_idx + i] = bs->buf[i];
	refill_buffer (bs);
	bs->buf_byte_idx = bs->buf_size - 1;
      }
    }
  }
  bit = bs->buf[bs->buf_byte_idx] & mask[bs->buf_bit_idx - 1];
  bit = bit >> (bs->buf_bit_idx - 1);
  bs->buf_bit_idx--;
#ifdef	PrintBitDebug
  printf ("pos: %5d getbits: %2d code: %4x val: %5d\n",
	  bs->totbit - 1, 1, bit, bit);
  fflush (stdout);
#endif
  return (bit);
}

/*write 1 bit from the bit stream */
void put1bit (Bit_stream_struc * bs, int bit)
			/* bit stream structure */
			/* bit to write into the buffer */
{
  //  register int i;

#ifdef	PrintBitDebug
  printf ("pos: %5d putbits: %2d code: %4x val: %5d\n",
	  bs->totbit, 1, bit, bit);
  fflush (stdout);
#endif

  bs->totbit++;

  bs->buf[bs->buf_byte_idx] |= (bit & 0x1) << (bs->buf_bit_idx - 1);
  bs->buf_bit_idx--;
  if (!bs->buf_bit_idx) {
    bs->buf_bit_idx = 8;
    bs->buf_byte_idx--;
    if (bs->buf_byte_idx < 0)
      empty_buffer (bs, MINIMUM);
    bs->buf[bs->buf_byte_idx] = 0;
  }
}

/*read N bit from the bit stream */
unsigned long getbits (Bit_stream_struc * bs, int N)
			/* bit stream structure */
			/* number of bits to read from the bit stream */
{
  unsigned long val = 0;
  register int i;
  register int j = N;
  register int k, tmp;

  if (N > MAX_LENGTH)
    printf ("Cannot read or write more than %d bits at a time.\n", MAX_LENGTH);

  bs->totbit += N;
  while (j > 0) {
    if (!bs->buf_bit_idx) {
      bs->buf_bit_idx = 8;
      bs->buf_byte_idx--;
      if ((bs->buf_byte_idx < MINIMUM) || (bs->buf_byte_idx < bs->eob)) {
	if (bs->eob)
	  bs->eobs = TRUE;
	else {
	  for (i = bs->buf_byte_idx; i >= 0; i--)
	    bs->buf[bs->buf_size - 1 - bs->buf_byte_idx + i] = bs->buf[i];
	  refill_buffer (bs);
	  bs->buf_byte_idx = bs->buf_size - 1;
	}
      }
    }
    k = MIN (j, bs->buf_bit_idx);
    tmp = bs->buf[bs->buf_byte_idx] & putmask[bs->buf_bit_idx];
    tmp = tmp >> (bs->buf_bit_idx - k);
    val |= tmp << (j - k);
    bs->buf_bit_idx -= k;
    j -= k;
  }
#ifdef	PrintBitDebug
  printf ("pos: %5d getbits: %2d code: %4x val: %5d\n",
	  bs->totbit - N, N, val, val);
  fflush (stdout);
#endif
  return (val);
}

/*write N bits into the bit stream */
void putbits (Bit_stream_struc * bs, unsigned int val, int N)
			/* bit stream structure */
			/* val to write into the buffer */
			/* number of bits of val */
{
  //  register int i;
  register int j = N;
  register int k, tmp;

  if (N > MAX_LENGTH)
    printf ("Cannot read or write more than %d bits at a time.\n", MAX_LENGTH);

#ifdef	PrintBitDebug
  printf ("pos: %5d putbits: %2d code: %4x val: %5d\n",
	  bs->totbit, N, val, val);
  fflush (stdout);
#endif

  bs->totbit += N;
  while (j > 0) {
    k = MIN (j, bs->buf_bit_idx);
    tmp = val >> (j - k);
    bs->buf[bs->buf_byte_idx] |= (tmp & putmask[k]) << (bs->buf_bit_idx - k);
    bs->buf_bit_idx -= k;
    if (!bs->buf_bit_idx) {
      bs->buf_bit_idx = 8;
      bs->buf_byte_idx--;
      if (bs->buf_byte_idx < 0)
	empty_buffer (bs, MINIMUM);
      bs->buf[bs->buf_byte_idx] = 0;
    }
    j -= k;
  }
}

/*return the current bit stream length (in bits)*/
unsigned long sstell (Bit_stream_struc * bs)
			/* bit stream structure */
{
  return (bs->totbit);
}

/*return the status of the bit stream*/
/* returns 1 if end of bit stream was reached */
/* returns 0 if end of bit stream was not reached */
int end_bs (Bit_stream_struc * bs)
			/* bit stream structure */
{
  return (bs->eobs);
}

/*****************************************************************************
*
*  End of bit_stream.c package
*
*****************************************************************************/

int transmission_channel (frame_params * fr_ps, int sbgr, int m)
{
  int config = fr_ps->config;
  int tca = fr_ps->header->tc_alloc[sbgr];

  /* 960627 FdB TCA table dependent on configuration */
  if (config == 320)
      return (transmission_channel5[tca][m]);	/* 3/2 */
  else if (config == 310)
    return (transmission_channel4a[tca][m]);	/* 3/1 */
  else if (config == 220)
    return (transmission_channel4b[tca][m]);	/* 2/2 */
  else if (config == 300 || config == 302 || config == 210)
    return (transmission_channel3[tca][m]);	/* 3/0 (+2/0) and 2/1 */
  else
    return (m);
}

int dyn_ch (frame_params * fr_ps, int sbgr, int m)
{
  int config = fr_ps->config;
  int dynx = fr_ps->header->dyn_cross[sbgr];
  int dynx2stereo = fr_ps->header->dyn_second_stereo[sbgr];
  /* 960627 FdB Dyn_ch table dependent on configuration */
  if (config == 320)
      return (dyn_ch4[dynx][m - 2]);
  else if (config == 310 || config == 220)
    return (dyn_ch3[dynx][m - 2]);
  else if (config == 300 || config == 302 || config == 210) {
    if (config == 302 && dynx2stereo && m == 4)
      return (0);
    else
      return (dyn_ch1[dynx][m - 2]);
  } else if (config == 202 && dynx2stereo && m == 3)
    return (0);
  else if (config == 102 && dynx2stereo && m == 2)
    return (0);
  else
    return (1);
}

int dyn_bbal (int config, int center, int dynx, int sbgr)
{
  /* 960627 FdB Dyn_ch table dependent on configuration */
  if (config == 320) {
    if (center == 3)
      return (dyn_bbal4PhC[dynx][sbgr]);
    else
      return (dyn_bbal4[dynx][sbgr]);
  } else if (config == 310 || config == 220) {
    if (center == 3)
      return (dyn_bbal3PhC[dynx][sbgr]);
    else
      return (dyn_bbal3[dynx][sbgr]);
  } else if (config == 300 || config == 302 || config == 210) {
    if (center == 3)
      return (dyn_bbal1PhC[dynx][sbgr]);
    else
      return (dyn_bbal1[dynx][sbgr]);
  } else
    return (0);
}

int dyn_bbal_2ndst (int dynx, int sbgr)
{
  return (dyn_bbal4[dynx][sbgr]);
}



void init_mc_pred (frame_params * fr_ps)
{
  layer *info = fr_ps->header;
  int i, j, k;

  switch (fr_ps->config) {
  case 320:
    for (i = 0; i < 16; i++)
      n_pred_coef[i] = n_pred_coef4[i];
    break;
  case 310:
  case 220:
    for (i = 0; i < 16; i++)
      n_pred_coef[i] = n_pred_coef3[i];
    break;
  case 300:
  case 302:
  case 210:
    for (i = 0; i < 16; i++)
      n_pred_coef[i] = n_pred_coef1[i];
    break;
  default:
    for (i = 0; i < 16; i++)
      n_pred_coef[i] = 0;
    break;
  }

  for (i = 0; i < 8; i++) {
    info->mc_pred[i] = 0;
    for (j = 0; j < 6; j++) {
      info->delay_comp[i][j] = 0;
      info->predsi[i][j] = 0;
      for (k = 0; k < 3; k++)
	info->pred_coef[i][j][k] = 127;
    }
  }
}

void set_mc_pred (frame_params * fr_ps)
{
  layer *info = fr_ps->header;
  //int config = fr_ps->config;
  int dynx;
  int i, j, k, npred;

  for (i = 0; i < 8; i++) {
    info->mc_pred[i] = rand () % 2;
    if (info->mc_pred[i]) {
      dynx = fr_ps->header->dyn_cross[i];
      npred = n_pred_coef[dynx];
      for (j = 0; j < npred; j++) {
	info->predsi[i][j] = rand () % 4;
	if (info->predsi[i][j]) {
	  info->delay_comp[i][j] = rand () % 8;
	  for (k = 0; k < info->predsi[i][j]; k++)
	    info->pred_coef[i][j][k] = rand () % 256;
	}
      }
    }
  }
}


