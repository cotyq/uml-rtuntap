
#ifdef CONFIG_UML_DVK

#ifdef DVK_GLOBAL_HERE
#define EXTERN
#else
#define EXTERN extern
#endif

#ifndef CONFIG_DVKIPC
EXTERN dvs_usr_t 	dvs;
#else // CONFIG_DVKIPC
extern dvs_usr_t 	dvs;
#endif // CONFIG_DVKIPC

EXTERN dc_usr_t 	dcu;
EXTERN proc_usr_t 	uml_proc;
EXTERN proc_usr_t 	rdc_proc;
EXTERN int 			dcid; 

EXTERN int 			uml_ep;		// UML KERNEL ENDPOING : from boot parameter
EXTERN int 			rdc_ep;		// RDISK Client ENDPOING :  the lowest USER endpoint 
EXTERN int 			rd_ep;		// RDISK Endpoint (external from UML)  from boot parameter

extern int  dvk_fd; 
extern int local_nodeid;
#ifdef DVK_GLOBAL_HERE
char *dvk_dev = UML_DVK_DEV;
#else 
extern char *dvk_dev;
#endif 
	

#endif // CONFIG_UML_DVK

