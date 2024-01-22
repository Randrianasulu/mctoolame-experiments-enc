#include "common.h"
#include "crc.h"

void II_CRC_calc (frame_params * fr_ps, unsigned int (*bit_alloc)[32],
		  unsigned int (*scfsi)[32], unsigned int *crc)
{
  int i, k;
  layer *info = fr_ps->header;
  int stereo = fr_ps->stereo;
  int sblimit = fr_ps->sblimit;
  int jsbound = fr_ps->jsbound;
  al_table *alloc = fr_ps->alloc;

  *crc = 0xffff;		/* changed from '0' 92-08-11 shn */
  update_CRC (info->bitrate_index, 4, crc);
  update_CRC (info->sampling_frequency, 2, crc);
  update_CRC (info->padding, 1, crc);
  update_CRC (info->extension, 1, crc);
  update_CRC (info->mode, 2, crc);
  update_CRC (info->mode_ext, 2, crc);
  update_CRC (info->copyright, 1, crc);
  update_CRC (info->original, 1, crc);
  update_CRC (info->emphasis, 2, crc);

  for (i = 0; i < sblimit; i++)
    for (k = 0; k < ((i < jsbound) ? stereo : 1); k++)
      update_CRC (bit_alloc[k][i], (*alloc)[i][0].bits, crc);

  for (i = 0; i < sblimit; i++)
    for (k = 0; k < stereo; k++)
      if (bit_alloc[k][i])
	update_CRC (scfsi[k][i], 2, crc);
}

void II_CRC_calc_mc (frame_params * fr_ps, unsigned int (*bit_alloc)[32],
		     unsigned int lfe_alloc, unsigned int (*scfsi)[32],
		     unsigned int *crc)
{
  int i, k, m, l;
  layer *info = fr_ps->header;
  //int nr_tc = fr_ps->stereo + fr_ps->stereomc;
  int center = info->center;
  int surround = info->surround;
  int sblimit = fr_ps->sblimit_mc;
  al_table *alloc = fr_ps->alloc_mc;

  *crc = 0xffff;		/* changed from '0' 92-08-11 shn */
  update_CRC (info->ext_bit_stream_present, 1, crc);
  if (info->ext_bit_stream_present == 1)
    update_CRC (info->n_ad_bytes, 8, crc);
  update_CRC (center, 2, crc);
  update_CRC (surround, 2, crc);
  update_CRC (info->lfe, 1, crc);
  update_CRC (info->audio_mix, 1, crc);
  update_CRC (info->matrix, 2, crc);
  update_CRC (info->multiling_ch, 3, crc);
  update_CRC (info->multiling_fs, 1, crc);
  update_CRC (info->multiling_lay, 1, crc);
  update_CRC (info->copy_ident_bit, 1, crc);
  update_CRC (info->copy_ident_start, 1, crc);

  update_CRC (info->tc_sbgr_select, 1, crc);
  update_CRC (info->dyn_cross_on, 1, crc);
  update_CRC (info->mc_prediction_on, 1, crc);
  /* 960627 FdB tca bits dependent on configuration */
  if ((center == 1 || center == 3) && (surround == 1 || surround == 2)) {
    /* 3 bits for tca's */
    if (info->tc_sbgr_select == 1)
      update_CRC (info->tc_allocation, 3, crc);
    else
      for (i = 0; i < 12; i++)
	update_CRC (info->tc_alloc[i], 3, crc);
  } else if (center == 1 || center == 3 || surround == 1 || surround == 2) {
    /* 2 bits for tca's */
    if (info->tc_sbgr_select == 1)
      update_CRC (info->tc_allocation, 2, crc);
    else
      for (i = 0; i < 12; i++)
	update_CRC (info->tc_alloc[i], 2, crc);
  }
  if (info->dyn_cross_on == 1) {
    update_CRC (info->dyn_cross_LR, 1, crc);
    for (i = 0; i < 12; i++) {
      /* 960627 FdB DynX bits dependent on configuration */
      if ((center == 1 || center == 3) && surround == 2)
	/* 3/2 */
	update_CRC (info->dyn_cross[i], 4, crc);
      else if (((center == 1 || center == 3) && surround == 1) ||
	       (center == 0 && surround == 2))
	/* 3/1 and 2/2 */
	update_CRC (info->dyn_cross[i], 3, crc);
      else if (center == 1 || center == 3 || surround == 1)
	/* 3/0 (+2/0) and 2/1 */
	update_CRC (info->dyn_cross[i], 1, crc);
      if (surround == 3)
	update_CRC (info->dyn_second_stereo[i], 1, crc);
    }
  }

  if (info->mc_prediction_on == 1) {
    for (i = 0; i < 8; i++) {
      update_CRC (info->mc_pred[i], 1, crc);
      if (info->mc_pred[i] == 1)
	for (k = 0; k < n_pred_coef[info->dyn_cross[i]]; k++)
	  update_CRC (info->predsi[i][k], 2, crc);
    }
  }

  if (fr_ps->header->lfe == 1)
    update_CRC (lfe_alloc, (*alloc)[0][0].bits, crc);

  for (i = 0; i < sblimit; i++) {
    l = sbgrp[i];

    for (m = fr_ps->stereo; m < fr_ps->stereo + fr_ps->stereomc; m++) {
      k = transmission_channel (fr_ps, l, m);

      if ((i < 12) || (k != 2) || (fr_ps->header->center != 3)) {
	/* 960627 FdB DynX dependent on configuration */
	if (dyn_ch (fr_ps, l, m) == 1)
	  update_CRC (bit_alloc[k][i], (*alloc)[i][0].bits, crc);
      }
    }
  }

  for (i = 0; i < sblimit; i++) {
    l = sbgrp[i];

    for (m = fr_ps->stereo; m < fr_ps->stereo + fr_ps->stereomc; m++) {
      k = transmission_channel (fr_ps, l, m);

      if (bit_alloc[k][i] && (i < 12 || m != 2 || center != 3))
	update_CRC (scfsi[k][i], 2, crc);
    }
  }
}

void II_CRC_calc_ext (frame_params * fr_ps, unsigned int *z, unsigned int *crc)
{
  int i;

  layer *info = fr_ps->header;
  *crc = 0xffff;
  update_CRC (info->ext_length, 11, crc);
  update_CRC (info->ext_bit, 1, crc);
  for (i = 0; i < 14; i++) {
    update_CRC (z[i], 8, crc);
  }
  update_CRC (z[14], 4, crc);
}


void update_CRC (unsigned int data, unsigned int length, unsigned int *crc)
{
  unsigned int masking, carry;

  masking = 1 << length;

  while (masking >>= 1) {
    carry = *crc & 0x8000;
    *crc <<= 1;
    if (!carry ^ !(data & masking))
      *crc ^= CRC16_POLYNOMIAL;
  }
  *crc &= 0xffff;

#ifdef	PrintCRCDebug
  printf ("crc_len: %2d code: %4x crc: %4x\n", length, data, *crc);
  fflush (stdout);
#endif
}
