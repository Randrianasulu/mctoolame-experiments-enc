#include "common.h"
#include "encoder.h"
#include "encode.h"
#include "audio_read.h"
#include <stdint.h>

/************************************************************************
*
* read_samples()
*
* PURPOSE:  reads the PCM samples from a file to the buffer
*
*  SEMANTICS:
* Reads #samples_read# number of shorts from #musicin# filepointer
* into #sample_buffer[]#.  Returns the number of samples read.
*
************************************************************************/

unsigned long read_samples (FILE * musicin, int16_t *sample_buffer,
			    long unsigned int num_samples,
			    long unsigned int frame_size, int
			    *byte_per_sample, int *aiff)
{
  unsigned long samples_read =0 ;
  static unsigned long samples_to_read=0;
  static char init = TRUE;
  int16_t pcm_sample_buffer[9216];	/*for correct reading of pcm-data */
  int i;
  
  //printf("AIFF = %i \n", *aiff); // hack
  //printf("BPS= %i \n", *byte_per_sample);
  //printf("NSamples, %i \n", num_samples);
  //printf("FRSize %i \n", frame_size);

  if (init) {
    samples_to_read = num_samples;
    init = FALSE;
    aiff_seek_to_sound_data(musicin);
  }
  if (samples_to_read >= frame_size)
    samples_read = frame_size;
  else
    samples_read = samples_to_read;

  if ((*aiff == 1) && (*byte_per_sample == 2)) {
    
    

    
    if ((samples_read =
	 fread (sample_buffer, *byte_per_sample, (int) samples_read,
		musicin)) == 0)
      if (verbosity >= 2)
	printf ("Hit end of audio data (aiff). samples read %li \n", samples_read);

  } else {
    
    if ((samples_read =
	 fread (pcm_sample_buffer, sizeof (int16_t), (int) samples_read,
		musicin)) == 0)
      if (verbosity >= 2)
	printf ("Hit end of audio data (pcm)\n");
    for (i = 0; i < 9216; ++i)
      sample_buffer[i] = pcm_sample_buffer[i];
  }

  samples_to_read -= samples_read;
  if (samples_read < frame_size && samples_read > 0) {
    if (verbosity >= 2)
      printf ("Insufficient PCM input for one frame - fillout with zeros\n");
    for (; samples_read < frame_size; sample_buffer[samples_read++] = 0);
    samples_to_read = 0;
  }
  return (samples_read);
}


unsigned long read_samples_new (FILE * musicin, long int *sample_buffer,
			    long unsigned int num_samples,
			    long unsigned int frame_size, int
			    *byte_per_sample, int *aiff)
{
  unsigned long samples_read;
  static unsigned long samples_to_read;
  static char init = TRUE;
  int16_t pcm_sample_buffer[9216];	/*for correct reading of pcm-data */
  int i;

  if (init) {
    samples_to_read = num_samples;
    init = FALSE;
  }
  if (samples_to_read >= frame_size)
    samples_read = frame_size;
  else
    samples_read = samples_to_read;

 
  if ((samples_read =
       fread (pcm_sample_buffer, sizeof (int16_t), (int) samples_read,
	      musicin)) == 0)
    if (verbosity >= 2)
      printf ("Hit end of audio data\n");
  for (i = 0; i < 9216; ++i)
    sample_buffer[i] = pcm_sample_buffer[i];
  

  samples_to_read -= samples_read;
  if (samples_read < frame_size && samples_read > 0) {
    if (verbosity >= 2)
      printf ("Insufficient PCM input for one frame - fillout with zeros\n");
    for (; samples_read < frame_size; sample_buffer[samples_read++] = 0);
    samples_to_read = 0;
  }
  return (samples_read);
}

/************************************************************************
*
* get_audio()
*
* PURPOSE:  reads a frame of audio data from a file to the buffer,
*   aligns the data for future processing, and separates the
*   left and right channels
*
*  SEMANTICS:
* Calls read_samples() to read a frame of audio data from filepointer
* #musicin# to #insampl[]#.  The data is shifted to make sure the data
* is centered for the 1024pt window to be used by the psychoacoustic model,
* and to compensate for the 256 sample delay from the filter bank. For
* stereo, the channels are also demultiplexed into #buffer[0][]# and
* #buffer[1][]#
*
* 21/03/1995 JMZ Multimode adaptations
************************************************************************/

//! Byte swap short
static int16_t swap_int16( int16_t val )
{
    return (val << 8) | ((val >> 8) & 0xFF);
}

unsigned long
get_audio (FILE * musicin,
	   double (*buffer)[1152],
	   long unsigned int num_samples,
	   int stereo,
	   IFF_AIFF * aiff_ptr,
	   int stereomc,
	   int stereoaug,
	   frame_params * fr_ps,
	   int *aiff, int *byte_per_sample, double (*buffer_matr)[1152]
  )
{
  int k, j, i;
  int16_t insamp[9216];
  unsigned long samples_read;
  int lay;
  int lfe;
  layer *info = fr_ps->header;

  lay = info->lay;
  lfe = info->lfe;
  
  int endian_order = DetermineByteOrder();

 {
   if (*aiff == 1) {
     k = aiff_ptr->numChannels;
     samples_read = read_samples (musicin, insamp, num_samples,
				  (uint32_t) (k * 1152), byte_per_sample,
				  aiff);
     
     
     for (i = 0; i < k; i++)
       for (j = 0; j < 1152; j++)
       
       if(endian_order == 1)
	    buffer[i][j] = swap_int16(insamp[k * j + i]); // for Little-Endian machine
	if(endian_order == 2 || endian_order == 3)
	    buffer[i][j] = insamp[k * j + i]; // for Big-Endian machine

   } else {			/* layerII, stereo */
     if (stereo == 2) {
       samples_read = read_samples (musicin, insamp, num_samples,
				    (uint32_t) ((2 + lfe) * 1152),
				     byte_per_sample, aiff);
	for (j = 0; j < 1152; j++) {	/* fixed bug 28.6.93 S.R. */
	  buffer[0][j] = insamp[(2 + lfe) * j];
	  buffer[1][j] = insamp[(2 + lfe) * j + 1];
	  buffer[2][j] = 0;
	  buffer[3 + lfe][j] = 0;
	  buffer[4 + lfe][j] = 0;
	  if (lfe)
	    buffer[3][j] = insamp[(2 + lfe) * j + 2];	/* ########### */
	}
      } else {			/* layer 2 (or 3), mono */
	samples_read = read_samples (musicin, insamp, num_samples,
				     (uint32_t) 1152, byte_per_sample,
				     aiff);
	for (j = 0; j < 1152; j++) {
	  buffer[0][j] = insamp[j];
	  buffer[1][j] = 0;
	  buffer[2][j] = 0;
	  buffer[3][j] = 0;
	  buffer[4][j] = 0;
	}
      }
    }
  }

  /*
   * If LFE is not enabled, "buffer" contains:
   *  buffer[0]       L
   *  buffer[1]       R
   *  buffer[2]       C
   *  buffer[3]       Ls
   *  buffer[4]       Rs
   *
   * If LFE is enabled, "buffer" contains:
   *  buffer[0]       L
   *  buffer[1]       R
   *  buffer[2]       C
   *  buffer[3]       LFE
   *  buffer[4]       Ls
   *  buffer[5]       Rs
   */

 matricing_fft (buffer, buffer_matr, fr_ps);

  /*
   * After matrixing, "buffer_matr" contains:
   *  buffer_matr[0]  Lo
   *  buffer_matr[1]  Ro
   *  buffer_matr[2]  C
   *  buffer_matr[3]  Ls
   *  buffer_matr[4]  Rs
   *  buffer_matr[5]  L
   *  buffer_matr[6]  R
   */

  return (samples_read);
}


/***********************************
get_audio new
reads from 5 seperate files 
************************************/

#define MAXCHANNELS 7
char soundfile[MAXCHANNELS][256] = {"left.pcm", "right.pcm", "centre.pcm", "left_surround.pcm", "right_surround.pcm"};
FILE *audioin[MAXCHANNELS];
int numinputs = 5;

void init_audio_inputs(void) {
  int i;

  for (i=0;i<numinputs;i++) {
    if ((audioin[i] = fopen(soundfile[i], "r")) == NULL) {
      fprintf(stderr, "Can't open %s for input\n",soundfile[i]);
      exit(99);
    }
  }
}

unsigned long
get_audio_new (FILE * musicin,
	   double (*buffer)[1152],
	   long unsigned int num_samples,
	   int stereo,
	   IFF_AIFF * aiff_ptr,
	   int stereomc,
	   int stereoaug,
	   frame_params * fr_ps,
	   int *aiff, int *byte_per_sample, double (*buffer_matr)[1152]
  )
{
  int j, i;
  int16_t insamp[9216];
  unsigned long samples_read=0;
  //MFC  int lay;
  int lfe;
  layer *info = fr_ps->header;
  static int init=0;

  if (!init) {
    init_audio_inputs();
    init++;
  }
      

  lfe = info->lfe;
  
#define NEWREAD
#ifdef NEWREAD
  for (i=0;i<numinputs;i++) {
    samples_read += read_samples(audioin[i], insamp, num_samples, 1152, byte_per_sample, aiff);
    //fprintf(stdout,"%i samples read %i\n",i, samples_read);
    for (j=0;j<1152;j++)
      buffer[i][j] = insamp[j];
  }
#else
  if (stereo == 2) {
    samples_read = read_samples (musicin, insamp, num_samples,
				 (uint32_t) ((2 + lfe) * 1152),
				 byte_per_sample, aiff);
    for (j = 0; j < 1152; j++) {	/* fixed bug 28.6.93 S.R. */
      buffer[0][j] = insamp[(2 + lfe) * j];
      buffer[1][j] = insamp[(2 + lfe) * j + 1];
      buffer[2][j] = 0;
      buffer[3 + lfe][j] = 0;
      buffer[4 + lfe][j] = 0;
      if (lfe)
	buffer[3][j] = insamp[(2 + lfe) * j + 2];	/* ########### */
    }
  } else {			/* layer 2 (or 3), mono */
    samples_read = read_samples (musicin, insamp, num_samples,
				 (uint32_t) 1152, byte_per_sample,
				 aiff);
    for (j = 0; j < 1152; j++) {
      buffer[0][j] = insamp[j];
      buffer[1][j] = 0;
      buffer[2][j] = 0;
      buffer[3][j] = 0;
      buffer[4][j] = 0;
    }
  }
#endif // NEWREAD
  /*
   * If LFE is not enabled, "buffer" contains:
   *  buffer[0]       L
   *  buffer[1]       R
   *  buffer[2]       C
   *  buffer[3]       Ls
   *  buffer[4]       Rs
   *
   * If LFE is enabled, "buffer" contains:
   *  buffer[0]       L
   *  buffer[1]       R
   *  buffer[2]       C
   *  buffer[3]       LFE
   *  buffer[4]       Ls
   *  buffer[5]       Rs
   */

    matricing_fft (buffer, buffer_matr, fr_ps);

  /*
   * After matrixing, "buffer_matr" contains:
   *  buffer_matr[0]  Lo
   *  buffer_matr[1]  Ro
   *  buffer_matr[2]  C
   *  buffer_matr[3]  Ls
   *  buffer_matr[4]  Rs
   *  buffer_matr[5]  L
   *  buffer_matr[6]  R
   */

  return (samples_read);
}
