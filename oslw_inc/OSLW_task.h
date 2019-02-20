/*
 * OSLW_task.h
 *
 *  Created on: 2017-7-14
 *      Author: slw
 */

#ifndef OSLW_TASK_H_
#define OSLW_TASK_H_

#include <setjmp.h>
#include "OSLW_define.h"
//------------------------------------------
//<�ṹ����>OSlwTaskPrivateMemorySTU</�ṹ����>
//<�ṹ�幦��>����˽�д洢�� ÿƬ����ΪTASK_PRIVATE_MEMORY_SECTION_LENGTH</�ṹ�幦��>
//------------------------------------------
typedef struct OSLW_TASK_PRIVATE_MEMORY_STRUCT{
	lw_u8 m8[TASK_PRIVATE_MEMORY_SECTION_LENGTH];
	lw_u16 m16[TASK_PRIVATE_MEMORY_SECTION_LENGTH];
	lw_u32 m32[TASK_PRIVATE_MEMORY_SECTION_LENGTH];
	lw_u64 m64[TASK_PRIVATE_MEMORY_SECTION_LENGTH];
	lw_sf msf[TASK_PRIVATE_MEMORY_SECTION_LENGTH];
	lw_df mdf[TASK_PRIVATE_MEMORY_SECTION_LENGTH];
}OSlwTaskPrivateMemorySTU;


//------------------------------------------
//<�ṹ����>OSlwTaskExternMemorySTU</�ṹ����>
//<�ṹ�幦��>�����ⲿ�洢�� ����ΪLength �׵�ַΪarr</�ṹ�幦��>
//------------------------------------------
typedef struct OSLW_TASK_EXTERN_MEMORY_STRUCT{
	lw_u16 Length;
	void *arr;
}OSlwTaskExternMemorySTU;

//------------------------------------------
//<ö��>OSlwTaskStatusNUM</ö��>
//<ö�ٹ���>����״̬����</ö�ٹ���>
//------------------------------------------
typedef enum{OSlwTaskStatus_Init=0,//��ʼ��
	OSlwTaskStatus_Ready,//����׼����� �ȴ�ִ��
	OSlwTaskStatus_Running,//������������
	OSlwTaskStatus_Wait_ForSleep,//����ȴ� �ȴ�ԭ��Ϊ˯��
	OSlwTaskStatus_Wait_ForSignal,//����ȴ� �ȴ�ԭ��Ϊ�ȴ��ź���
	OSlwTaskStatus_Wait_ForMessage,//����ȴ� �ȴ�ԭ��Ϊ�ȴ���Ϣ
	OSlwTaskStatus_Frozen//���񶳽�
}OSlwTaskStatusNUM;

//------------------------------------------
//<�ṹ����>OSlwTaskSTU</�ṹ����>
//<�ṹ�幦��>������ƿ�</�ṹ�幦��>
//------------------------------------------
typedef struct OSLW_TASK_STRUCT{
	//��Ա����
	lw_u8 Priority;//���ȼ�

	lw_8 Name[OSLW_TASK_NAME_LENGTH_MAX+1];//���� ������OSLW_TASK_NAME_LENGTH_MAX����

	OSlwTaskPrivateMemorySTU PrivateMem;//����˽�д洢��
	
	OSlwTaskExternMemorySTU ExternMem;//�����ⲿ�洢��

	_BP BreakPoint[OSLW_TASK_BREAKPOINT_DEEP];//�ϵ��б� ��ʾ֧�ֵĺ���Ƕ�״���

	lw_u16 BreakPointReturn[OSLW_TASK_BREAKPOINT_DEEP];//�ϵ㷵�ر� ��ʾ�����ϵ�ķ���ֵ

	OSlwTaskStatusNUM TaskStatus;//����״̬

	lw_u8 TaskFrozenFlag;
	
	lw_u32 SleepCount;//˯�߼�����
	
	struct OSLW_CORE_STRUCT *pOS;//����ϵͳָ�� ָ��������������ϵͳ
	
	//��Ա����
	void (*TaskFun)(struct OSLW_TASK_STRUCT *pta);//������
	void (*SleepFun)(struct OSLW_TASK_STRUCT *pta,lw_u32 n);//˯�ߺ���
}OSlwTaskSTU;


//��������
extern OSlwTaskSTU OSlwInlineTaskBoring;
void OSlwInlineTaskBoringExe(OSlwTaskSTU *pta);
void OSlwTaskSleep(OSlwTaskSTU *pta,lw_u32 n);
void OSlwTaskInit(OSlwTaskSTU *pta,
		lw_u8 priority,
		lw_8 *name,
		lw_u16 ExMemLen,
		void *ExMemarr,
		void (*fun)(struct OSLW_TASK_STRUCT *pta)
		);


#define OSLW_TASK_BENGIN(A)		do{if(!SAVE(A->BreakPoint[OSLW_TASK_BREAKPOINT_DEEP-1]))\
{\
	A->TaskStatus=OSlwTaskStatus_Ready;\
	LOAD(A->pOS->DispatchBreakPoint,A->Priority);\
}}while(0)
	

#define OSLW_TASK_LOOP(A) OSLW_TASK_BENGIN(A); for(;;)



#endif /* OSLW_TASK_H_*/
