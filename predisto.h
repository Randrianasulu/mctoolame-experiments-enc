/* The following functions are in the file "predisto.c" */

void matri (
	double (*sbs_sample)[3][12][SBLIMIT],
	frame_params *fr_ps,
	double (*sb_sample)[3][12][SBLIMIT],
	unsigned int (*scalar)[3][SBLIMIT],
	int sblimit,
	unsigned int (*scfsi)[SBLIMIT],
	unsigned int (*scfsi_dyn)[SBLIMIT],
	unsigned int (*bit_alloc)[SBLIMIT],
	unsigned int (*subband)[3][12][SBLIMIT]
);

void trans_pattern (
	unsigned int (*scalar)[3][SBLIMIT],
	unsigned int (*scfsi)[SBLIMIT],
	frame_params *fr_ps,
	unsigned int (*scfsi_dyn)[SBLIMIT]
);

void pre_quant (
	double (*sbs_sample)[3][12][SBLIMIT],
	int l,
	int m,
	double (*sb_sample)[3][12][SBLIMIT],
	unsigned int (*scalar)[3][SBLIMIT],
	unsigned int (*bit_alloc)[SBLIMIT],
	unsigned int (*subband)[3][12][SBLIMIT],
	frame_params *fr_ps
);

void II_dequantize_sample (
	unsigned int (*sample)[3][SBLIMIT],
	unsigned int (*bit_alloc)[SBLIMIT],
	double (*fraction)[3][12][SBLIMIT],
	frame_params *fr_ps,
	int l,
	int m,
	int z
);

void II_denormalize_sample (
	double (*fraction)[3][12][SBLIMIT],
	unsigned int (*scale_index)[3][SBLIMIT],
	frame_params *fr_ps,
	int x,
	int l,
	int m,
	int z
);

void scale_factor_calc (
	unsigned int (*scalar)[3][SBLIMIT],
	int sblimit,
	int l,
	int m,
	int z,
	double (*sb_sample)[3][12][SBLIMIT]
);

void predistortion (
		    double (*sb_sample)[3][12][32], 
		    unsigned int (*scalar)[3][32], 
		    unsigned int (*bit_alloc)[32], 
		    unsigned int (*subband)[3][12][32], 
		    frame_params *fr_ps, 
		    double (*perm_smr)[32], 
		    unsigned int (*scfsi)[32], 
		    int *adb, 
		    unsigned int (*scfsi_dyn)[32]
		    );

int bit_all (double (*perm_smr)[32], unsigned int (*scfsi)[32],
	     unsigned int (*bit_alloc)[32], int *adb, frame_params * fr_ps);
