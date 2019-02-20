/*
 * OSLW_parameter.c
 *
 *  Created on: 2017-7-14
 *      Author: slw
 */
#include "OSLW_include.h"

//------------------------------------------
//<������>OSlwParameter_toForm</������>
//<����˵��>��parameterת���ɸ�ʽ ���ö��������д洢 һ��5�ֽ� ʵ����ֵ=(arr[1]*2^24+arr[2]*2^16+arr[3]*2^8+arr[4])/(2^arr[0])</����˵��>
//<����˵��>p:this  arr[]:Ŀ���ַ</����˵��>
//<���˵��>p:this</���˵��>
//------------------------------------------

OSlwParameterSTU *OSlwParameter_toForm(OSlwParameterSTU *p,lw_u8 arr[5])
{
	fixpoint buf;
#if OSLW_GLOBAL_MATH_TYPE == OSLW_GLOBAL_MATH_DOUBLE
	buf=(fixpoint)(p->ParameterShallow*(double)(1<<p->Q));
#elif OSLW_GLOBAL_MATH_TYPE == OSLW_GLOBAL_MATH_FLOAT
	buf=(fixpoint)(p->ParameterShallow*(float)(1<<p->Q));
#elif OSLW_GLOBAL_MATH_TYPE == OSLW_GLOBAL_MATH_Q
	buf=FP_A_TO_FP_B(OSLW_GLOBAL_MATH_Q_FORM,(p->Q),(p->ParameterShallow));
#else
	buf=0;
#endif
	*arr++=p->Q;
	*arr++=((buf&0xf000)>>24);
	*arr++=((buf&0x0f00)>>16);
	*arr++=((buf&0x00f0)>>8);
	*arr++=((buf&0x000f)>>0);
	return p;
}

//------------------------------------------
//<������>OSlwParameter_set</������>
//<����˵��>������Ӱ�ӼĴ�������ʵ�ʲ����Ĵ���</����˵��>
//<����˵��>p:this</����˵��>
//<���˵��>p:this</���˵��>
//------------------------------------------
OSlwParameterSTU *OSlwParameter_set(OSlwParameterSTU *p)
{
	p->Parameter=p->ParameterShallow;
	return p;
}

//------------------------------------------
//<������>OSlwParameter_UpSelf</������>
//<����˵��>�������� parameter=parameter+delt</����˵��>
//<����˵��>p:this</����˵��>
//<���˵��>p:this</���˵��>
//------------------------------------------

OSlwParameterSTU *OSlwParameter_UpSelf(OSlwParameterSTU *p)
{
	p->ParameterShallow=_ParaAdd(p->ParameterShallow,p->delt);
	return p;
}

//------------------------------------------
//<������>OSlwParameter_DownSelf</������>
//<����˵��>�������� parameter=parameter-delt</����˵��>
//<����˵��>p:this</����˵��>
//<���˵��>p:this</���˵��>
//------------------------------------------
OSlwParameterSTU *OSlwParameter_DownSelf(OSlwParameterSTU *p)
{
	p->ParameterShallow=_ParaSub(p->ParameterShallow,p->delt);
	return p;
}
