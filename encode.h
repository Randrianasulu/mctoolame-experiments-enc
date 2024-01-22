
void 	   normalizing (double (*sb_sample)[3][12][SBLIMIT], frame_params *fr_ps);
void 	   matricing (double (*sb_sample)[3][12][SBLIMIT], frame_params *fr_ps);
#ifndef NEWSUBBAND
void        read_ana_window (double *ana_win);
void        window_subband (double **buffer, double *z, int k);
void        create_ana_filter (double (*filter)[64]);
void        filter_subband (double *z, double *s);
#endif
void        encode_info (frame_params *fr_ps, Bit_stream_struc *bs);
void        encode_info_mc1 (frame_params *fr_ps, Bit_stream_struc *bs);
void        encode_info_mc2 (frame_params *fr_ps, Bit_stream_struc *bs);
void        encode_info_ext1 (frame_params *fr_ps, Bit_stream_struc *bs_ext);
void        encode_info_ext2 (frame_params *fr_ps, Bit_stream_struc *bs_ext, unsigned int crc);
void 	   II_combine_LR (double (*sb_sample)[3][12][SBLIMIT], double (*joint_sample)[3][12][SBLIMIT],
					    int sblimit);
void 	   II_scale_factor_calc (frame_params *fr_ps, double (*sb_sample)[3][12][SBLIMIT],
					unsigned int (*scalar)[3][SBLIMIT], int sblimit, int l, int m);
void 	   II_scale_factor_calc1 (double (*sb_sample)[3][12][SBLIMIT], unsigned int (*scalar)[3][SBLIMIT],
					int sblimit, int dim);
void        pick_scale (unsigned int (*scalar)[3][SBLIMIT], frame_params *fr_ps, double (*max_sc)[SBLIMIT],
					int cha_sw, int aug_cha_sw, int aiff);
void        put_scale (unsigned int (*scalar)[3][SBLIMIT], frame_params *fr_ps, double (*max_sc)[SBLIMIT]);
void        II_transmission_pattern (unsigned int (*scalar)[3][SBLIMIT], unsigned int (*scfsi)[SBLIMIT],
					frame_params *fr_ps);

void II_encode_scale (unsigned int (*bit_alloc)[SBLIMIT],
			     unsigned int (*scfsi)[SBLIMIT],
			     unsigned int (*scalar)[3][SBLIMIT],
			     unsigned int lfe_alloc, 
			     unsigned int lfe_scalar, 
			     frame_params *fr_ps,
			     Bit_stream_struc *bs,
			     int *l,
			     int *z);

int         II_bits_for_nonoise (double (*perm_smr)[SBLIMIT], unsigned int (*scfsi)[SBLIMIT],
				    frame_params *fr_ps, int a, int b, int *aiff);

void	   II_main_bit_allocation (double (*perm_smr)[SBLIMIT],
					   double (*ltmin)[SBLIMIT],
					   unsigned int (*scfsi)[SBLIMIT],
					   unsigned int (*bit_alloc)[SBLIMIT],
					   int *adb,
					   frame_params *fr_ps,
					   int *aiff,
					   double (*sb_sample)[3][12][SBLIMIT],
					   unsigned int (*scalar)[3][SBLIMIT],
					   double (*max_sc)[SBLIMIT],
					   double (*buffer)[1152],
					   double (*spiki)[SBLIMIT],
					   double (*joint_sample)[3][12][SBLIMIT],
					   unsigned int (*j_scale)[3][SBLIMIT], 
					   int dyn_cr, 
					   int aug_dyn_cr, 
					   unsigned int (*scfsi_dyn)[SBLIMIT], 
					   unsigned int (*scalar_dyn)[3][SBLIMIT]);

int         II_a_bit_allocation (double (*perm_smr)[SBLIMIT],
					unsigned int (*scfsi)[SBLIMIT],
					unsigned int (*bit_alloc)[SBLIMIT],
					int *adb,
					frame_params *fr_ps,
					int *aiff);

void        II_subband_quantization (unsigned int (*scalar)[3][SBLIMIT],
					    double (*sb_samples)[3][12][SBLIMIT],
					    unsigned int (*j_scale)[3][SBLIMIT],
					    double (*j_samps)[3][12][SBLIMIT],
					    unsigned int (*bit_alloc)[SBLIMIT],
					    unsigned int (*sbband)[3][12][SBLIMIT],
					    frame_params *fr_ps);
void        II_subband_quantization_mc (unsigned int (*scalar)[3][SBLIMIT],
					       double (*sb_samples)[3][12][SBLIMIT],
					       unsigned int (*j_scale)[3][SBLIMIT],
					       double (*j_samps)[3][12][SBLIMIT],
					       unsigned int (*bit_alloc)[SBLIMIT],
					       unsigned int (*sbband)[3][12][SBLIMIT],
					       frame_params *fr_ps);
void        II_encode_bit_alloc (unsigned int (*bit_alloc)[SBLIMIT], frame_params *fr_ps, Bit_stream_struc *bs);
void        II_encode_bit_alloc_mc (unsigned int (*bit_alloc)[SBLIMIT], frame_params *fr_ps, Bit_stream_struc *bs);
void        II_sample_encoding (unsigned int (*sbband)[3][12][SBLIMIT],
				       unsigned int (*bit_alloc)[SBLIMIT],
				       frame_params *fr_ps,
				       Bit_stream_struc *bs);
void        II_sample_encoding_mc (unsigned int (*sbband)[3][12][SBLIMIT],
					  unsigned int lfe_sbband[12],
					  unsigned int (*bit_alloc)[SBLIMIT],
					  unsigned int lfe_alloc,
					  frame_params *fr_ps,
					  Bit_stream_struc *bs);
void        encode_CRC (unsigned int crc, Bit_stream_struc *bs);
void	   ancillary_encode (frame_params*,Bit_stream_struc*,int);

void	   matricing_fft (double (*buffer)[1152], double (*buffer_matr)[1152], frame_params *fr_ps);
void        tc_alloc (frame_params *fr_ps, double (*max_sc)[SBLIMIT]);
int         II_bits_for_indi (double (*perm_smr)[SBLIMIT], unsigned int (*scfsi)[SBLIMIT], frame_params *fr_ps, int *a, int *b, int *aiff);
int         required_bits ();
int         max_alloc ();
 


void II_encode_scale_ml (unsigned int (*bit_alloc)[32],
			 unsigned int (*scfsi)[32],
			 unsigned int (*scalar)[3][32], frame_params * fr_ps,
			 Bit_stream_struc * bs, int *l, int *z);
void II_subband_quantization_ml (unsigned int (*scalar)[3][32],
				 double (*sb_samples)[3][12][32],
				 unsigned int (*j_scale)[3][32],
				 double (*j_samps)[3][12][32],
				 unsigned int (*bit_alloc)[32],
				 unsigned int (*sbband)[3][12][32],
				 frame_params * fr_ps);


