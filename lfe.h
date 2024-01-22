/* The following functions are in the file "lfe.c" */

extern void        lfe_filter(double**,double[12]);
extern void        lf_scalefactor(double[12],unsigned int*);
extern void        II_encode_lfe_scale(unsigned int, Bit_stream_struc*);
extern void        lfe_allocation(unsigned int*,int*);
extern void        II_lfe_quantisation(unsigned int,double[12],
                                       unsigned int, unsigned int[12],
                                       frame_params*);
extern void        II_encode_lfe_alloc(unsigned int, frame_params*, Bit_stream_struc*);
extern void        II_lfe_sample_encoding(unsigned int[12],
                                       unsigned int, frame_params*,
                                       Bit_stream_struc*);
