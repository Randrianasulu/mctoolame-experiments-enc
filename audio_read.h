
unsigned long  read_samples (FILE *musicin,
				    int32_t *sample_buffer,
				    long unsigned int num_samples,
				    long unsigned int frame_size,
				    int *byte_per_sample,
				    int *aiff);


unsigned long
get_audio (
	FILE		*musicin,
	double		(*buffer)[1152],
	long unsigned int num_samples,
	int		stereo,
	IFF_AIFF	*aiff_ptr,
	int		stereomc,
	int		stereoaug,
	frame_params	*fr_ps,
	int		*aiff,
	int		*byte_per_sample,
	double		(*buffer_matr)[1152]
);

unsigned long
get_audio_new (
	FILE		*musicin,
	double		(*buffer)[1152],
	long unsigned int num_samples,
	int		stereo,
	IFF_AIFF	*aiff_ptr,
	int		stereomc,
	int		stereoaug,
	frame_params	*fr_ps,
	int		*aiff,
	int		*byte_per_sample,
	double		(*buffer_matr)[1152]
);
