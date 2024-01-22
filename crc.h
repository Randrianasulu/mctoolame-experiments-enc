
void II_CRC_calc (frame_params * fr_ps, unsigned int (*bit_alloc)[32],
		  unsigned int (*scfsi)[32], unsigned int *crc);
void II_CRC_calc_mc (frame_params * fr_ps, unsigned int (*bit_alloc)[32],
		     unsigned int lfe_alloc, unsigned int (*scfsi)[32],
		     unsigned int *crc);
void II_CRC_calc_ext (frame_params * fr_ps, unsigned int *z, unsigned int *crc);
void update_CRC (unsigned int data, unsigned int length, unsigned int *crc);
