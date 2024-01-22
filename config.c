#include "common.h"
#include "encoder.h"
#include "config.h"




#ifdef DONTUSEINTERACTIVE
void
obtain_parameters (frame_params * fr_ps,
		   int *psy,
		   long unsigned int *num_samples,
		   long unsigned int *num_samples_ml,
		   char *original_file_name,
		   char *encoded_file_name,
		   IFF_AIFF * pcm_aiff_data,
		   IFF_AIFF * pcm_aiff_data_ml,
		   int *aiff,
		   int *byte_per_sample,
		   int *mat_mode,
		   int *aug_mat_mode,
		   int *cha_sw,
		   int *aug_cha_sw,
		   char *encoded_file_name_ext,
		   int *bit_rate,
		   char *encoded_file_name_mpg,
		   int *dyn_cr,
		   int *dyn_cr_LR,
		   int *aug_dyn_cr, int *ancillaryUse, int *verbosity)
{
  int j, bool, max_rate, max_rate_index;
  long int i;
  int tot_channels = 0;		/* 21/03/1995 JMZ Multimode */
  char configuration[50];	/* 21/03/1995 JMZ Multimode */
  char t[50];

  layer *info = fr_ps->header;

  *aiff = 0;			/* flag for AIFF-Soundfile */

  do {
    printf ("Enter PCM input file name <required>: ");
    gets (original_file_name);
    if (original_file_name[0] == NULL_CHAR)
      printf ("PCM input file name is required.\n");
  } while (original_file_name[0] == NULL_CHAR);

  printf (">>> PCM input file name is: %s\n", original_file_name);

  if ((musicin = fopen (original_file_name, "rb")) == NULL) {
    printf ("Could not find \"%s\".\n", original_file_name);
    exit (1);
  }

/***************************************************************************/
/* 08/03/1995 Multi lingual extension JMZ                                  */

  printf ("Do you have multi lingual channels? (Y)es, (<N>)o: ");
  gets (multilingual_file_name);
  if ((*multilingual_file_name == 'Y') || (multilingual_file_name[0] == 'y')) {
    printf ("Enter multilingual input file name <%s.%s>: ", original_file_name,
	    DFLT_ML_EXT);
    gets (multilingual_file_name);
    if (multilingual_file_name[0] == NULL_CHAR) {
      printf ("Null char\n");
      strcat (strcpy (multilingual_file_name, original_file_name), DFLT_ML_EXT);
    }
    if ((musicin_ml = fopen (multilingual_file_name, "rb")) == NULL) {
      printf ("Could not find \"%s\".\n", multilingual_file_name);
      exit (1);
    }

    /*remplir fr_ps il y a au moins un multilingual */
    if (aiff_read_headers (musicin_ml, pcm_aiff_data_ml, byte_per_sample) == 0) {
      printf (">>> Using Audio IFF multilingual file headers\n");
      info->multiling_ch = pcm_aiff_data_ml->numChannels;
      printf (">>> Using %d multilingual channels\n", info->multiling_ch);
      *num_samples_ml = pcm_aiff_data_ml->numChannels *
	pcm_aiff_data_ml->numSampleFrames;
    } else {			/* Not using Audio IFF sound file headers. */

      printf
	("***WARNING: Could not read AIFF header - No MultiLingual coding!!\n");
      info->multiling_ch = 0;
    }
  } else {
    printf ("no multi lingual coding!!\n");
    info->multiling_ch = 0;
  }

/* 08/03/1995 Multi lingual extension JMZ                                  */
/***************************************************************************/

  printf ("Enter MPEG encoded output file name <%s%s>: ",
	  original_file_name, DFLT_EXT);

  gets (encoded_file_name);

  if (encoded_file_name[0] == NULL_CHAR) {
    strcat (strcpy (encoded_file_name_ext, original_file_name), DFLT_EXT_EXT);
    strcat (strcpy (encoded_file_name, original_file_name), DFLT_EXT);
    strcat (strcpy (encoded_file_name_mpg, encoded_file_name), DFLT_EXT);
  } else {
    strcat (strcpy (encoded_file_name_ext, encoded_file_name), DFLT_EXT_EXT);
    strcat (encoded_file_name, DFLT_EXT);
    strcat (strcpy (encoded_file_name_mpg, encoded_file_name), DFLT_EXT);
  }
  printf (">>> MPEG encoded output file name is: %s\n", encoded_file_name);

  open_bit_stream_w (&bs, encoded_file_name, BUFFER_SIZE);

  if (aiff_read_headers (musicin, pcm_aiff_data, byte_per_sample) == 0) {

    *aiff = 1;
    printf (">>> Using Audio IFF sound file headers\n");

/**********************************************************/
/* 21/03/1995 JMZ Multimode */

    tot_channels = pcm_aiff_data->numChannels;
    printf (">>> Using %d audio channels\n", tot_channels);

	/********* 27/01/97, FdB, select LFE ********************/
    if (tot_channels > 1) {
      printf ("Do you want to use LFE coding? (y/<n>) ");
      gets (t);
      if ((*t == 'y') || (*t == 'Y')) {
	printf (">>> LFE coding is used.\n");
	info->lfe = 1;
      } else {
	printf (">>> No LFE coding.\n");
	info->lfe = 0;
      }
    }
    if (tot_channels - info->lfe == 5) {
      fr_ps->stereomc = 3;
      fr_ps->stereoaug = 0;
      fr_ps->lfe_pos = 3;
      printf ("Which configuration do you want to use?\n");
      printf ("Available: 3/2 (<1>), 3/0 + 2/0 (2): ");
      gets (configuration);
      switch (*configuration) {
      case '1':
	info->center = 1;
	info->surround = 2;
	fr_ps->config = 320;
	printf (">>> Using 3/2 configuration.\n");
	break;
      case '2':
	info->center = 1;
	info->surround = 3;
	fr_ps->config = 302;
	printf (">>> Using 3/0 + 2/0 configuration.\n");
	break;
      default:
	info->center = 1;
	info->surround = 2;
	fr_ps->config = 320;
	printf (">>> Using default 3/2 configuration.\n");
	break;
      }
    } else if (tot_channels - info->lfe == 4) {
      fr_ps->stereomc = 2;
      fr_ps->stereoaug = 0;
      printf ("Which configuration do you want to use?\n");
      printf ("Available: 3/1 (<1>), 2/2 (2), 2/0 + 2/0 (3): ");
      gets (configuration);
      switch (*configuration) {
      case '1':
	info->center = 1;
	info->surround = 1;
	fr_ps->config = 310;
	fr_ps->lfe_pos = 3;
	printf (">>> Using 3/1 configuration.\n");
	break;
      case '2':
	info->center = 0;
	info->surround = 2;
	fr_ps->config = 220;
	fr_ps->lfe_pos = 2;
	printf (">>> Using 2/2 configuration.\n");
	break;
      case '3':
	info->center = 0;
	info->surround = 3;
	fr_ps->config = 202;
	fr_ps->lfe_pos = 2;
	printf (">>> Using 2/0 + 2/0 configuration.\n");
	break;
      default:
	info->center = 1;
	info->surround = 1;
	fr_ps->config = 310;
	fr_ps->lfe_pos = 3;
	printf (">>> Using default 3/1 configuration.\n");
	break;
      }
    } else if (tot_channels - info->lfe == 3) {
      fr_ps->stereoaug = 0;
      printf ("Which configuration do you want to use?\n");
      printf ("Available: 3/0 (<1>), 2/1 (2), 1/0 + 2/0 (3): ");
      gets (configuration);
      switch (*configuration) {
      case '1':
	info->center = 1;
	info->surround = 0;
	fr_ps->config = 300;
	fr_ps->stereomc = 1;
	fr_ps->lfe_pos = 3;
	printf (">>> Using 3/0 configuration.\n");
	break;
      case '2':
	info->center = 0;
	info->surround = 1;
	fr_ps->config = 210;
	fr_ps->stereomc = 1;
	fr_ps->lfe_pos = 2;
	printf (">>> Using 2/1 configuration.\n");
	break;
      case '3':
	info->center = 0;
	info->surround = 3;
	fr_ps->config = 102;
	fr_ps->stereomc = 2;
	fr_ps->lfe_pos = 1;
	printf (">>> Using 1/0 + 2/0 configuration.\n");
	break;
      default:
	info->center = 1;
	info->surround = 0;
	fr_ps->config = 300;
	fr_ps->stereomc = 1;
	fr_ps->lfe_pos = 3;
	printf (">>> Using default 3/0 configuration.\n");
	break;
      }
    } else if (tot_channels - info->lfe == 2) {
      fr_ps->config = 200;
      fr_ps->stereomc = 0;
      fr_ps->stereoaug = 0;
      fr_ps->lfe_pos = 2;
    } else if (tot_channels - info->lfe == 1) {
      if (info->lfe) {
	printf ("single channel plus LFE not supported.\n");
	exit (1);
      }
      fr_ps->config = 100;
      fr_ps->stereomc = 0;
      fr_ps->stereoaug = 0;
    } else {
      printf ("Channels = %d not supported.\n", tot_channels);
      exit (1);
    }

    aiff_check (original_file_name, pcm_aiff_data);

/* 21/03/1995 JMZ Multimode */
/**********************************************************/


    info->sampling_frequency = SmpFrqIndex ((long) pcm_aiff_data->sampleRate);
    printf (">>> %.f Hz sampling frequency selected\n",
	    pcm_aiff_data->sampleRate);

    /* Determine number of samples in sound file */
    *num_samples = pcm_aiff_data->numChannels * pcm_aiff_data->numSampleFrames;

    if (info->multiling_ch > 0) {
      switch (SmpFrqIndex ((long) pcm_aiff_data_ml->sampleRate) -
	      info->sampling_frequency) {
      case 16:
	printf ("MultiLingual is LSF coded.\n");
	info->multiling_fs = 1;
	break;
      case 0:
	printf ("MultiLingual sample rate equals that of Audio.\n");
	info->multiling_fs = 0;
	break;
      default:
	printf
	  ("***WARNING: MultiLingual sample rate does not equal (half) mc sample rate.\n");
	printf ("            No MultiLingual coding!!!\n");
	info->multiling_ch = 0;
	break;
      }				/*switch */
    }				/*if (ml_ch>0) */
  } else {			/* Not using Audio IFF sound file headers. */
    printf ("no multichannel coding!!\n");
    fr_ps->stereomc = 0;
    fr_ps->stereoaug = 0;
    info->multiling_ch = 0;
    printf ("What is the sampling frequency? <48000>[Hz]: ");
    gets (t);
    i = atol (t);
    switch (i) {
    case 48000:
      info->sampling_frequency = 1;
      printf (">>> %ld Hz sampling freq selected\n", i);
      break;
    case 44100:
      info->sampling_frequency = 0;
      printf (">>> %ld Hz sampling freq selected\n", i);
      break;
    case 32000:
      info->sampling_frequency = 2;
      printf (">>> %ld Hz sampling freq selected\n", i);
      break;
    default:
      info->sampling_frequency = 1;
      printf (">>> Default 48 kHz samp freq selected\n");
    }

    if (fseek (musicin, 0, SEEK_SET) != 0) {
      printf ("Could not seek to PCM sound data in \"%s\".\n",
	      original_file_name);
      exit (1);
    }

    /* Declare sound file to have "infinite" number of samples. */
    *num_samples = MAX_U_32_NUM;
  }

  printf ("Which layer do you want to use?\n");
  printf ("Available: Layer (1), Layer (<2>): ");
  gets (t);
  switch (*t) {
  case '1':
    info->lay = 1;
    printf (">>> Using Layer %s\n", t);
    break;
  case '2':
    info->lay = 2;
    printf (">>> Using Layer %s\n", t);
    break;
  default:
    info->lay = 2;
    printf (">>> Using default Layer 2\n");
    break;
  }

  printf ("Which mode do you want for the two front channels?\n");
  printf ("Available: (<s>)tereo, (j)oint stereo, ");
  printf ("(d)ual channel, s(i)ngle Channel, n(o)ne: ");
  gets (t);
  if (fr_ps->config < 200) {	/* compatible is mono */
    info->mode = MPG_MD_MONO;
    info->mode_ext = 0;
    printf (">>> Using default mono mode\n");
  } else
    switch (*t) {
    case 's':
    case 'S':
      info->mode = MPG_MD_STEREO;
      info->mode_ext = 0;
      printf (">>> Using mode %s\n", t);
      break;
    case 'j':
    case 'J':
      info->mode = MPG_MD_JOINT_STEREO;
      printf (">>> Using mode %s\n", t);
      break;
    case 'd':
    case 'D':
      info->mode = MPG_MD_DUAL_CHANNEL;
      info->mode_ext = 0;
      printf (">>> Using mode %s\n", t);
      break;
    case 'i':
    case 'I':
      info->mode = MPG_MD_MONO;
      info->mode_ext = 0;
      printf (">>> Using mode %s\n", t);
      break;
    case 'o':
    case 'O':
      info->mode = MPG_MD_NONE;
      info->mode_ext = 0;
      printf (">>> Using mode %s\n", t);
      break;
    default:
      info->mode = MPG_MD_STEREO;
      info->mode_ext = 0;
      printf (">>> Using default stereo mode\n");
      break;
    }

  *psy = DFLT_PSY;

  if (info->mode == MPG_MD_MONO)
    max_rate_index = 10;
  else
    max_rate_index = 14;
  /*    max_rate_index = 6; *//* 48 kHz => 96 kbps for multiple table testing */
  max_rate = bitrate[info->lay - 1][max_rate_index];
  printf ("What is the total bitrate? <%u>[kbps]: ", DFLT_BRT);
  gets (t);
  i = atol (t);
  if (i == 0)
    i = -10;
  j = 0;
  while (j <= max_rate_index) {
    if (bitrate[info->lay - 1][j] == (int) i)
      break;
    j++;
  }
  if (j > max_rate_index) {
    if (i < max_rate) {
      if (DFLT_BRT <= max_rate) {
	i = DFLT_BRT;
	printf (">>> Using default %u kbps\n", DFLT_BRT);
      } else {
	i = max_rate;
	printf (">>> Using max. bitrate %u kbps\n", max_rate);
      }
      for (j = 0; j < 15; j++)
	if (bitrate[info->lay - 1][j] == (int) i) {
	  info->bitrate_index = j;
	  break;
	}
    } else {
      info->ext_bit_stream_present = 1;
      *bit_rate = i;
      if (DFLT_BRT <= max_rate)
	i = DFLT_BRT;
      else
	i = max_rate;
      for (j = 0; j < 15; j++)
	if (bitrate[info->lay - 1][j] == (int) i) {
	  info->bitrate_index = j;
	  break;
	}
      info->ext_length =
	((*bit_rate - i) * 144) / s_freq[info->sampling_frequency];
      printf (">>> Bitrate = %d kbps\n", *bit_rate);
    }
  } else {
    info->bitrate_index = j;
    printf (">>> Bitrate = %d kbps\n", bitrate[info->lay - 1][j]);
  }

  printf ("What type of de-emphasis should the decoder use?\n");
  printf ("Available: (<n>)one, (5)0/15 microseconds, (c)citt j.17: ");
  gets (t);
  if (*t != 'n' && *t != '5' && *t != 'c') {
    printf (">>> Using default no de-emphasis\n");
    info->emphasis = 0;
  } else {
    if (*t == 'n')
      info->emphasis = 0;
    else if (*t == '5')
      info->emphasis = 1;
    else if (*t == 'c')
      info->emphasis = 3;
    printf (">>> Using de-emphasis %c\n", *t);
  }

/*  Start 2. Part changes for CD Ver 3.2; jsp; 22-Aug-1991 */

  printf ("Do you want to set the private bit? (y/<n>): ");
  gets (t);
  if (*t == 'y' || *t == 'Y')
    info->extension = 1;
  else
    info->extension = 0;
  if (info->extension)
    printf (">>> Private bit set\n");
  else
    printf (">>> Private bit not set\n");

/*  End changes for CD Ver 3.2; jsp; 22-Aug-1991 */

  printf ("Do you want error protection? (y/<n>): ");
  gets (t);
  if (*t == 'y' || *t == 'Y')
    info->error_protection = TRUE;
  else
    info->error_protection = FALSE;
  if (info->error_protection)
    printf (">>> Error protection used\n");
  else
    printf (">>> Error protection not used\n");


  printf ("Is the material copyrighted? (y/<n>): ");
  gets (t);
  if (*t == 'y' || *t == 'Y')
    info->copyright = 1;
  else
    info->copyright = 0;
  if (info->copyright)
    printf (">>> Copyrighted material\n");
  else
    printf (">>> Material not copyrighted\n");

  printf ("Is this the original? (y/<n>): ");
  gets (t);
  if (*t == 'y' || *t == 'Y')
    info->original = 1;
  else
    info->original = 0;
  if (info->original)
    printf (">>> Original material\n");
  else
    printf (">>> Material not original\n");

  /* Option for multichannel for matricing, 7/12/93,SR */
  if (*aiff == 1) {
    printf ("which kind of matrix do you want(<(-3, -3) = 0>;(-xx, -3) = 1;");
    printf (" (-oo, -3) = 2; (-oo, -oo) = 3)  ");
    gets (t);
    if (strcmp (t, "") == 0)
      info->matrix = 0;
    else
      info->matrix = atoi (t);
    printf ("The matrix %d is chosen\n", info->matrix);
    *mat_mode = info->matrix;


    printf ("Do you want to have Channel-switching?(<y>/n) ");
    gets (t);
    if (*t == 'y' || *t == 'Y')
      *cha_sw = *aug_cha_sw = 1;

    if (*cha_sw == 0 || info->matrix == 3) {
      *cha_sw = 0;
      printf ("Channel-switching is not used!\n");
      printf ("Which mode of Channel-switching do you want? (not used) ");
      gets (t);
      printf ("CHA mode: %d\n", *cha_sw);
    } else {
      *cha_sw = 1;
      printf ("Channel-switching is used\n");
      do {
	printf ("Which mode of Channel-switching do you want? (-2 ... 7) ");
	gets (t);
	*cha_sw = atoi (t);
	printf ("CHA mode: %d\n", *cha_sw);
	if (fr_ps->config == 320)
	  bool = *cha_sw > 7;
	else if (fr_ps->config == 310 && info->matrix == 2)
	  bool = *cha_sw > 5;
	else if (fr_ps->config == 310)
	  bool = *cha_sw > 4;
	else if (fr_ps->config == 220)
	  bool = *cha_sw > 3;
	else if (fr_ps->config == 300 || fr_ps->config == 302
		 || fr_ps->config == 210)
	  bool = *cha_sw > 2;
	else
	  bool = *cha_sw > 0;
	if (bool)
	  printf
	    ("!!! Channel-switching mode %d cannot be used together with Configuration: %d !!!\n",
	     *cha_sw, fr_ps->config);
      } while (bool);
    }

      *aug_cha_sw = 0;

	/********* 27/07/95, WtK , phantom coding ********************/
    if ((fr_ps->stereomc > 0) && (info->center == 1)) {
      printf
	("Do you want to use Phantom Coding of the Center signal? (y/<n>) ");
      gets (t);
      if ((*t == 'y') || (*t == 'Y')) {
	printf (">>> Phantom Coding is used.\n");
	fr_ps->phantom_c = 1;
      } else {
	printf (">>> No Phantom Coding.\n");
	fr_ps->phantom_c = 0;
      }
    }

	/********* 05/24/95, SR , dynamic cross_talk ********************/
    printf ("Do you want to have Dynamic Crosstalk?(y/<n>) ");
    gets (t);
    if (*t == 'y') {
      printf ("Dynamic Crosstalk is used!\n");
      bool = 1;
      do {
	printf ("Which mode of Dynamic Crosstalk do you want? (-1 ... 14) ");
	gets (t);
	*dyn_cr = atoi (t);
	printf ("DynX mode: %d\n", *dyn_cr);
	if (fr_ps->phantom_c && fr_ps->config == 320)
	  bool = ((*dyn_cr == 9) || (*dyn_cr == 10) || (*dyn_cr == 11)
		  || (*dyn_cr == 12) || (*dyn_cr == 14));
	else if (fr_ps->phantom_c
		 && ((fr_ps->config == 310) || (fr_ps->config == 220)))
	  bool = (*dyn_cr == 4);
	else
	  bool = 0;
	if (bool)
	  printf
	    ("!!! Dynamic Crosstalk mode %d cannot be used together with Phantom Coding !!!\n",
	     *dyn_cr);
      } while (bool);

    } else {
      *dyn_cr = 0;
      printf ("Dynamic Crosstalk is not used\n");
      printf ("Which mode of Dynamic Crosstalk do you want? (not used) ");
      gets (t);
      printf ("DynX mode: %d\n", *dyn_cr);
    }
    bool = 1;
    do {
      printf ("Value for dyn_cross_LR?(<0>/1) ");
      gets (t);
      *dyn_cr_LR = atoi (t);
      bool = *dyn_cr_LR < -1 || *dyn_cr_LR > 1;

      if (bool)
	printf ("!!! dyn_cross_LR %d invalid value -1, 0 or 1 !!!\n",
		*dyn_cr_LR);
    } while (bool);
    printf ("dyn_cross_LR: %d\n", *dyn_cr_LR);

	/********* 27/01/97, FdB, select prediction ********************/
    if (fr_ps->stereomc > 0 && fr_ps->config != 202 && fr_ps->config != 102) {
      printf ("Do you want to use MC prediction? (y/<n>) ");
      gets (t);
      if ((*t == 'y') || (*t == 'Y')) {
	printf (">>> MC prediction is used.\n");
	info->mc_prediction_on = 1;
      } else {
	printf (">>> No MC prediction.\n");
	info->mc_prediction_on = 0;
      }
    }
  }

  /* YBKim060695 ancillary */
  printf ("Do you want to use ancillary part ? (y:<n>): ");
  gets (t);
  *ancillaryUse = (*t == 'y' || *t == 'Y');
  printf ("Ancillary: %d\n", *ancillaryUse);

  printf ("How verbose would you like the output ? (0, <1>, 2, 3): ");
  gets (t);
  if (*t >= '0' && *t <= '3')
    *verbosity = atoi (t);
  else
    *verbosity = DFLT_VERB;
  printf ("Verbose level: %d\n", *verbosity);

  printf ("Do you wish to exit (last chance before encoding)? (y/<n>): ");
  gets (t);
  if (*t == 'y' || *t == 'Y')
    exit (1);
}

#endif
