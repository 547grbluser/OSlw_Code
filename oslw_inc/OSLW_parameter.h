/*
 * OSLW_parameter.h
 *
 *  Created on: 2017-7-14
 *      Author: slw
 */

#ifndef OSLW_PARAMETER_H_
#define OSLW_PARAMETER_H_

#include "OSLW_define.h"


//------------------------------------------
//<�ṹ����>OSlwParameter</�ṹ����>
//<��Ա����>
//Parameter:ʵ�ʲ���
//ParameterShallow:ʵ�ʲ�����Ӱ�ӼĴ���
//delt:Ӱ�Ӳ���������
//Q:��ʽ������ ���ڸ�ʽ��
//</��Ա����>
//<��Ա����>
//toFormFun:��ʽ������
//setFun:���ú��� Ӱ�ӼĴ�������
//UpSelfFun:��������
//DownSelfFun:�����Լ�
//</��Ա����>
//------------------------------------------

typedef struct OSLW_PARAMETER_STRUCT{
	ParaType Parameter;
	ParaType ParameterShallow;
	ParaType delt;
	lw_u8 Q;

	struct OSLW_PARAMETER_STRUCT* (*toFormFun)(struct OSLW_PARAMETER_STRUCT *p,lw_u8 arr[5]);
	struct OSLW_PARAMETER_STRUCT* (*setFun)(struct OSLW_PARAMETER_STRUCT *p);
	struct OSLW_PARAMETER_STRUCT* (*UpSelfFun)(struct OSLW_PARAMETER_STRUCT *p);
	struct OSLW_PARAMETER_STRUCT* (*DownSelfFun)(struct OSLW_PARAMETER_STRUCT *p);

}OSlwParameterSTU;

//��������
OSlwParameterSTU *OSlwParameter_toForm(OSlwParameterSTU *p,lw_u8 arr[5]);
OSlwParameterSTU *OSlwParameter_set(OSlwParameterSTU *p);
OSlwParameterSTU *OSlwParameter_UpSelf(OSlwParameterSTU *p);
OSlwParameterSTU *OSlwParameter_DownSelf(OSlwParameterSTU *p);


//<����˵��>�������Ͷ��� ����������õ��㷨</����˵��>
#if OSLW_GLOBAL_MATH_TYPE==OSLW_GLOBAL_MATH_Q
	#define _ParaAdd(A,B) ((A)+(B))
	#define _ParaSub(A,B) ((A)-(B))
	#define _ParaMpy(A,B) (_IQmpy(A,B))
	#define _ParaDiv(A,B) (_IQdiv(A,B))
	#define _ParaInt(A) (_IQint(A))
	#define _ParaFrac(A) (_IQfrac(A))
#elif OSLW_GLOBAL_MATH_TYPE==OSLW_GLOBAL_MATH_FLOAT
	#define _ParaAdd(A,B) ((A)+(B))
	#define _ParaSub(A,B) ((A)-(B))
	#define _ParaMpy(A,B) ((A)*(B))
	#define _ParaDiv(A,B) ((A)/(B))
	#define _ParaInt(A) ((int)(A))
	#define _ParaFrac(A) ((A)-int(A))
#elif OSLW_GLOBAL_MATH_TYPE==OSLW_GLOBAL_MATH_DOUBLE
	#define _ParaAdd(A,B) ((A)+(B))
	#define _ParaSub(A,B) ((A)-(B))
	#define _ParaMpy(A,B) ((A)*(B))
	#define _ParaDiv(A,B) ((A)/(B))
	#define _ParaInt(A) ((int)(A))
	#define _ParaFrac(A) ((A)-int(A))
#else
	#error "MATH TYPE IS NOT DEFINED"
#endif


#endif /* OSLW_PARAMETER_H*/
