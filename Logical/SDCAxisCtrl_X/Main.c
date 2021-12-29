
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void increase_counters(void);

void _INIT ProgramInit(void)
{
	//Устанваливаем типы SDC модулей
	gAxis01_HW.EncIf1_Typ = ncSDC_ENC16;
	gAxis01_HW.DiDoIf_Typ = ncSDC_DIDO;
	gAxis01_HW.DrvIf_Typ = ncSDC_DRVSERVO16;
	
	//Устанавливаем имена переменных
	strcpy(gAxis01_HW.EncIf1_Name, "AxisX_EncIf");
	strcpy(gAxis01_HW.DrvIf_Name, "AxisX_DrvIf");
	strcpy(gAxis01_HW.DiDoIf_Name, "AxisX_DiDoIf");
		
	//Устанавливаем входы готовности и нормальной работы

	gAxis01_DrvIf.iDrvOK = 1;
	gAxis01_DrvIf.iStatusEnable = 1;
	gAxis01_DiDoIf.iDriveReady = 1;

	fb_controller.dt = 0.002;
	fb_controller.k_i = 0.16;
	fb_controller.k_p = 0.0064;
	fb_controller.max_abs_value = 24.0;
	
	pwm_period = 200;
}

void _CYCLIC ProgramCyclic(void)
{
	FB_Axis(&axis_X);
	coil_pwm_value = coil_powered ? 32767 : 0;
	
	increase_counters();
	
	//Формирование показаний датчика
	
	//AxisX_EncIf.iActTime = (INT)	AsIOTimeCyclicStart();
//	AxisX_EncIf.iActPos = axis_X.counter;
	gAxis01_DiDoIf.iPosHwEnd = axis_X.endswitch_b_reached;
	gAxis01_DiDoIf.iNegHwEnd = axis_X.endswitch_a_reached;
	fb_controller.in = gAxis01_DrvIf.oSetPos;
	
	if((fb_controller.in<min_task)&&(fb_controller.in>(-min_task))) fb_controller.in = 0; 
	fb_controller.in = fb_controller.in * 6500/32767 - axis_X.speed;

	FB_Controller(&fb_controller);

	axis_X.pwm_value = fb_controller.out / 24.0 * 32767;
}

void increase_counters(void)
{
	//AxisX_EncIf.iLifeCnt++;
	gAxis01_DiDoIf.iLifeCntDriveEnable++; 
	gAxis01_DiDoIf.iLifeCntDriveReady++; 
	gAxis01_DiDoIf.iLifeCntNegHwEnd++; 
	gAxis01_DiDoIf.iLifeCntPosHwEnd++; 
	gAxis01_DiDoIf.iLifeCntReference++;
	gAxis01_DrvIf.iLifeCnt++;
}

void _EXIT ProgramExit(void)
{
	// Insert code here 

}

