
unsigned long read_samples_ml (FILE * musicin, long int *sample_buffer,
			       long unsigned int num_samples,
			       long unsigned int frame_size,
			       int *byte_per_sample, int *aiff);
unsigned long
get_audio_ml (FILE * musicin_ml,
	      double (*buffer)[1152],
	      long unsigned int num_samples,
	      IFF_AIFF * aiff_ptr,
	      frame_params * fr_ps,
	      int *aiff, int *byte_per_sample, double (*buffer_matr)[1152]
	      );
void II_sample_encoding_ml (unsigned int (*sbband)[3][12][32],
			    unsigned int (*bit_alloc)[32], frame_params * fr_ps,
			    Bit_stream_struc * bs);
void II_encode_bit_alloc_ml (unsigned int (*bit_alloc)[32],
			     frame_params * fr_ps, Bit_stream_struc * bs);
void ml_sb_sample_swap (int ch0, int ch1, double subsample[14][3][12][SBLIMIT]);
void pick_scale_ml_2 (frame_params * fr_ps,
		      double subsample[14][3][12][SBLIMIT],
		      double (*max_sc)[32]);
void ml_sb_sample_shift (int ch0, int ch1, double subsample[14][3][12][SBLIMIT]);
