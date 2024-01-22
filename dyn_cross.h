/* The following functions are in the file "dyn_cross.c" */

void take_dyn_cross (
	int		dyn_cr,	
	frame_params	*fr_ps,  		    
	double		sb_sample_sum[5][3][SCALE_BLOCK][SBLIMIT], 	    
    	unsigned int	scalar_sum[][3][SBLIMIT], 			
	unsigned int	scfsi_sum[][SBLIMIT],  				
	unsigned int	scfsi_dyn[][SBLIMIT],  				
	double		sb_sample[CHANMAX3][3][SCALE_BLOCK][SBLIMIT],	
	unsigned int	scalar[][3][SBLIMIT], 				
	unsigned int	scfsi[][SBLIMIT]
	);
	
#ifdef Augmentation_7ch
void take_dyn_cross_aug (
	int		aug_dyn_cr,	
	frame_params	*fr_ps,  		    
	double		sb_sample_sum[5][3][SCALE_BLOCK][SBLIMIT], 	    
    	unsigned int	scalar_sum[][3][SBLIMIT], 			
	unsigned int	scfsi_sum[][SBLIMIT],  				
	unsigned int	scfsi_dyn[][SBLIMIT],  				
	double		sb_sample[CHANMAX3][3][SCALE_BLOCK][SBLIMIT],	
	unsigned int	scalar[][3][SBLIMIT], 				
	unsigned int	scfsi[][SBLIMIT]
	);
#endif
	
void trans_chan (frame_params *fr_ps);
#ifdef Augmentation_7ch
void trans_chan_aug (frame_params *fr_ps);
#endif
	 				
void combine (frame_params *fr_ps, double sb_sample[CHANMAX3][3][SCALE_BLOCK][SBLIMIT],
	      double sb_sample_sum[5][3][SCALE_BLOCK][SBLIMIT]);
#ifdef Augmentation_7ch
void combine_aug (frame_params *fr_ps, double sb_sample[CHANMAX3][3][SCALE_BLOCK][SBLIMIT],
		  double sb_sample_sum[5][3][SCALE_BLOCK][SBLIMIT]);
#endif
	
void dyn_bal (
	unsigned int	scfsi[CHANMAX3][SBLIMIT],  
	int		sbgr,			    
	frame_params	*fr_ps,
	int		min_ch,			    
	int		min_sb,			   
	int		*seli,			    
	int		*scale
	);
	
#ifdef Augmentation_7ch
void dyn_bal_aug (
	unsigned int	scfsi[CHANMAX3][SBLIMIT],  
	int		sbgr,			    
	frame_params	*fr_ps,
	int		min_ch,			    
	int		min_sb,			   
	int		*seli,			    
	int		*scale
	);
#endif

void choose_dyn (
	frame_params	*fr_ps, 
	int		min_ch,				
	int		min_sb,				
	int		sbgr, 				
	unsigned int	bit_alloc[CHANMAX3][SBLIMIT]
	);	
				    
#ifdef Augmentation_7ch
void choose_dyn_aug (
	frame_params	*fr_ps, 
	int		min_ch,				
	int		min_sb,				
	int		sbgr, 				
	unsigned int	bit_alloc[CHANMAX3][SBLIMIT]
	);	
#endif
			    
void scfsi_calc_dyn (
	unsigned int	scalar_dyn[][3][SBLIMIT],   
	int		ch, 			    
	int		sblimit,		    
	unsigned int	scfsi_dyn[][SBLIMIT]
	);
	 	    
void scfsi_calc (
	unsigned int	scalar[][3][SBLIMIT], 	
	int		ch, 			
	int		sblimit,		
	unsigned int	scfsi[][SBLIMIT]
	);
	 	
void scf_calc (
	double		sample[][3][SCALE_BLOCK][SBLIMIT], 
	int		sblimit,		
	int		ch,			
	unsigned int	scf[][3][SBLIMIT]
	);	
