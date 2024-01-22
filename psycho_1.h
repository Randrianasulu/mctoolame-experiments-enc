#ifdef NEWP1TABLES
void psycho_1_read_freq_band (int *sub_size, g_ptr *ltg, int lay, int freq);
int *psycho_1_read_cbound (int lay, int freq, int *crit_band);
#else
void        read_cbound(int lay, int freq, int crit_band, int *cbound);
void        read_freq_band(int *sub_size, g_ptr *ltg, int lay, int freq);
#endif
void        make_map(int sub_size, mask *power, g_thres *ltg);
double      add_db(double a, double b);
void        II_f_f_t(double *sample, mask *power);
void        II_hann_win(double *sample);
void        II_pick_max(mask *power, double *spike);
void        II_tonal_label(mask *power, int *tone);
void        noise_label(int crit_band, int *cbound, mask *power, int *noise, g_thres *ltg);
void        subsampling(mask *power, g_thres *ltg, int *tone, int *noise);
void        threshold(int sub_size, mask *power, g_thres *ltg, int *tone, int *noise, int bit_rate);
void        II_minimum_mask(int sub_size, g_thres *ltg, double *ltmin, int sblimit);
void        II_smr(double *ltmin, double *smr, double *spike, double *scale, int sblimit, int l, int m);
void        psycho_1(double (*buffer)[1152], double (*scale)[SBLIMIT], double (*ltmin)[SBLIMIT], frame_params *fr_ps, double (*smr)[SBLIMIT], double (*spiki)[SBLIMIT], int aiff);
double      non_lin_add(double a, double b, double c);
void II_Psycho_One_ml (double (*buffer)[1152],
		       double (*scale)[32],
		       double (*ltmin)[32],
		       frame_params * fr_ps,
		       double (*smr)[32], double (*spiki)[32]
		       );
