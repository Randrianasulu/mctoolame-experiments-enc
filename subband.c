#ifdef NEWSUBBAND
#include "common.h"
#include "enwindow.h"
#include "subband.h"

#ifdef REFERENCECODE
/************************************************************************
*
* window_subband()
*
* PURPOSE:  Overlapping window on PCM samples
*
* SEMANTICS:
* 32 16-bit pcm samples are scaled to fractional 2's complement and
* concatenated to the end of the window buffer #x#. The updated window
* buffer #x# is then windowed by the analysis window #c# to produce the
* windowed sample #z#
*
************************************************************************/
#define MAXCHANNELS 14 //6 "normal" channels, plus all the multi-linguals (7 ML channels?)
void window_subband (double **buffer, double z[64], int k)
{
  typedef double XX[MAXCHANNELS][HAN_SIZE];
  static XX *x;
  double *xk;
  int i;
  static int off[MAXCHANNELS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static char init = 0;
  double t;
  double *ep0, *ep1, *ep2, *ep3, *ep4, *ep5, *ep6, *ep7;
  if (!init) {
    x = (XX *) mem_alloc (sizeof (XX), "x");
    memset (x, 0, MAXCHANNELS * HAN_SIZE * sizeof (double));
    init = 1;
  }
  xk = (*x)[k];

  //fprintf(stdout,"k %i\n",k);

  /* replace 32 oldest samples with 32 new samples */
  for (i = 0; i < 32; i++)
    xk[31 - i + off[k]] = *(*buffer)++ / SCALE;

  ep0 = &enwindow[0];
  ep1 = &enwindow[64];
  ep2 = &enwindow[128];
  ep3 = &enwindow[192];
  ep4 = &enwindow[256];
  ep5 = &enwindow[320];
  ep6 = &enwindow[384];
  ep7 = &enwindow[448];

  /* shift samples into proper window positions */
  for (i = 0; i < 64; i++) {
    t = xk[(i + off[k]) & (512 - 1)] * *ep0++;
    t += xk[(i + 64 + off[k]) & (512 - 1)] * *ep1++;
    t += xk[(i + 128 + off[k]) & (512 - 1)] * *ep2++;
    t += xk[(i + 192 + off[k]) & (512 - 1)] * *ep3++;
    t += xk[(i + 256 + off[k]) & (512 - 1)] * *ep4++;
    t += xk[(i + 320 + off[k]) & (512 - 1)] * *ep5++;
    t += xk[(i + 384 + off[k]) & (512 - 1)] * *ep6++;
    t += xk[(i + 448 + off[k]) & (512 - 1)] * *ep7++;
    z[i] = t;
  }

  off[k] += 480;		/*offset is modulo (HAN_SIZE-1) */
  off[k] &= HAN_SIZE - 1;

}


/************************************************************************
*
* filter_subband()
*
* PURPOSE:  Calculates the analysis filter bank coefficients
*
* SEMANTICS:
*      The windowed samples #z# is filtered by the digital filter matrix #m#
* to produce the subband samples #s#. This done by first selectively
* picking out values from the windowed samples, and then multiplying
* them by the filter matrix, producing 32 subband samples.
*
************************************************************************/
void filter_subband (double z[HAN_SIZE], double s[SBLIMIT])
{
  double yprime[32];
  register int i, j;

  static double m[16][32];
  static int init = 0;

  if (init == 0) {
    init++;
    create_dct_matrix (m);
  }

  yprime[0] = z[16];
  for (i = 1; i <= 16; i++)
    yprime[i] = z[i + 16] + z[16 - i];
  for (i = 17; i <= 31; i++)
    yprime[i] = z[i + 16] - z[80 - i];

  for (i = 15; i >= 0; i--) {
    register double s0 = 0.0, s1 = 0.0;
    register double *mp = m[i];
    register double *xinp = yprime;
    for (j = 0; j < 8; j++) {
      s0 += *mp++ * *xinp++;
      s1 += *mp++ * *xinp++;
      s0 += *mp++ * *xinp++;
      s1 += *mp++ * *xinp++;
    }
    s[i] = s0 + s1;
    s[31 - i] = s0 - s1;
  }
}
#endif //REFERENCECODE

void create_dct_matrix (double filter[16][32])
{
  register int i, k;

  for (i = 0; i < 16; i++)
    for (k = 0; k < 32; k++) {
      if ((filter[i][k] = 1e9 * cos ((double) ((2 * i + 1) * k * PI64))) >= 0)
	modf (filter[i][k] + 0.5, &filter[i][k]);
      else
	modf (filter[i][k] - 0.5, &filter[i][k]);
      filter[i][k] *= 1e-9;
    }
}

//____________________________________________________________________________
//____ WindowFilterSubband() _________________________________________
//____ RS&A - Feb 2003 _______________________________________________________
void WindowFilterSubband (short *pBuffer, int ch, double s[SBLIMIT])
{
  register int i, j;
  int pa, pb, pc, pd, pe, pf, pg, ph;
  double t;
  double *dp, *dp2;
  double *pEnw;
  double y[64];
  double yprime[32];

  static double x[2][512];
  static double m[16][32];
  static int init = 0;
  static int off[2];
  static int half[2];

  if (init == 0) {
    init++;
    off[0] = 0;
    off[1] = 0;
    half[0] = 0;
    half[1] = 0;
    for (i = 0; i < 2; i++)
      for (j = 0; j < 512; j++)
	x[i][j] = 0;
    create_dct_matrix (m);
  }

  dp = x[ch] + off[ch] + half[ch] * 256;

  /* replace 32 oldest samples with 32 new samples */
  for (i = 0; i < 32; i++)
    dp[(31 - i) * 8] = (double) pBuffer[i] / SCALE;

  // looks like "school example" but does faster ...
  dp = (x[ch] + half[ch] * 256);
  pa = off[ch];
  pb = (pa + 1) % 8;
  pc = (pa + 2) % 8;
  pd = (pa + 3) % 8;
  pe = (pa + 4) % 8;
  pf = (pa + 5) % 8;
  pg = (pa + 6) % 8;
  ph = (pa + 7) % 8;

  for (i = 0; i < 32; i++) {
    dp2 = dp + i * 8;
    pEnw = enwindow + i;
    t = dp2[pa] * pEnw[0];
    t += dp2[pb] * pEnw[64];
    t += dp2[pc] * pEnw[128];
    t += dp2[pd] * pEnw[192];
    t += dp2[pe] * pEnw[256];
    t += dp2[pf] * pEnw[320];
    t += dp2[pg] * pEnw[384];
    t += dp2[ph] * pEnw[448];
    y[i] = t;
  }

  yprime[0] = y[16];		// Michael Chen´s dct filter

  dp = half[ch] ? x[ch] : (x[ch] + 256);
  pa = half[ch] ? (off[ch] + 1) & 7 : off[ch];
  pb = (pa + 1) % 8;
  pc = (pa + 2) % 8;
  pd = (pa + 3) % 8;
  pe = (pa + 4) % 8;
  pf = (pa + 5) % 8;
  pg = (pa + 6) % 8;
  ph = (pa + 7) % 8;

  for (i = 0; i < 32; i++) {
    dp2 = dp + i * 8;
    pEnw = enwindow + i + 32;
    t = dp2[pa] * pEnw[0];
    t += dp2[pb] * pEnw[64];
    t += dp2[pc] * pEnw[128];
    t += dp2[pd] * pEnw[192];
    t += dp2[pe] * pEnw[256];
    t += dp2[pf] * pEnw[320];
    t += dp2[pg] * pEnw[384];
    t += dp2[ph] * pEnw[448];
    y[i + 32] = t;
    // 1st pass on Michael Chen´s dct filter
    if (i > 0 && i < 17)
      yprime[i] = y[i + 16] + y[16 - i];
  }

  // 2nd pass on Michael Chen´s dct filter
  for (i = 17; i < 32; i++)
    yprime[i] = y[i + 16] - y[80 - i];

  for (i = 15; i >= 0; i--) {
    register double s0 = 0.0, s1 = 0.0;
    register double *mp = m[i];
    register double *xinp = yprime;
    for (j = 0; j < 8; j++) {
      s0 += *mp++ * *xinp++;
      s1 += *mp++ * *xinp++;
      s0 += *mp++ * *xinp++;
      s1 += *mp++ * *xinp++;
    }
    s[i] = s0 + s1;
    s[31 - i] = s0 - s1;
  }

  half[ch] = (half[ch] + 1) & 1;
  if (half[ch] == 1)
    off[ch] = (off[ch] + 7) & 7;
}


#endif //NEWSUBBAND
