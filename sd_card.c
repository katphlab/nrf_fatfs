#include "sd_card.h"
#include "app_timer.h"

#define		SD_LIB_DEBUG

uint32_t time1;
uint32_t time2;
uint32_t time3;
uint32_t time4;
uint32_t time5;
uint32_t time6;
uint32_t time7;

uint32_t time_diff1;
uint32_t time_diff2;
uint32_t time_diff3;
uint32_t time_diff4;
uint32_t time_diff5;

bool mount_sd(void)
{
	uint8_t temp;
	for(int i=0; i<5; i++)
	{
		temp = f_mount(&FatFs, "", 1);     /* Give a work area to the default drive */
	#ifdef SD_LIB_DEBUG
		debug("temp is %x\n", temp);
	#endif	//DEBUG
		if(temp == 0)   break;
	}
	sd_spi_uninit();
	return temp == 0;
}

bool write_sd(void * data, uint16_t data_len)
{
	app_timer_cnt_get(&time1);
	sd_spi_init();
	app_timer_cnt_get(&time2);
    UINT bw;
	if (f_open(&Fil, "data.txt", FA_WRITE | FA_OPEN_APPEND) == FR_OK)
	{
		app_timer_cnt_get(&time3);

		/* Create a file */
//		f_lseek(&Fil, f_size(&Fil));
		f_write(&Fil, data, data_len, &bw);	/* Write data to the file */

		app_timer_cnt_get(&time4);
		f_close(&Fil);								/* Close the file */
		app_timer_cnt_get(&time5);
	#ifdef SD_LIB_DEBUG
		debug("number of bytes written is %x\n", bw);
	#endif	//DEBUG
//		if (bw != data_len)
//		{
//			return false;
//		}
	}
	app_timer_cnt_get(&time6);
	sd_spi_uninit();
	app_timer_cnt_get(&time7);
	app_timer_cnt_diff_compute(time2, time1, &time_diff1);
	app_timer_cnt_diff_compute(time3, time2, &time_diff2);
	app_timer_cnt_diff_compute(time4, time3, &time_diff3);
	app_timer_cnt_diff_compute(time5, time4, &time_diff4);
	app_timer_cnt_diff_compute(time7, time6, &time_diff5);
	debug("spi init:%d\n f_open:%d\n f_write:%d\n f_close=%d\n spi_uninit:%d\n", time_diff1, time_diff2, time_diff3, time_diff4, time_diff5);
	return true;
}
