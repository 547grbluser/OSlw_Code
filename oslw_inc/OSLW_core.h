/*
 * OSLW_core.h
 *
 *  Created on: 2017-7-14
 *      Author: slw
 */

#ifndef OSLW_CORE_H_
#define OSLW_CORE_H_

#include "OSLW_define.h"
#include <limits.h>
#include <stdlib.h>

typedef int (*_compar_fn)(const void *,const void *);

//------------------------------------------
//<��������>OSlwCoreGroupUN</��������>
//<�����幦��>�ں˱�־�鹲���� ����OSLW_TASK_NUM_MAXȷ������</�����幦��>
//------------------------------------------
typedef struct OSLW_CORE_GROUP_UNION{
#if OSLW_TASK_NUM_MAX<=8
	struct{
		lw_u8 bit7:1;
		lw_u8 bit6:1;
		lw_u8 bit5:1;
		lw_u8 bit4:1;
		lw_u8 bit3:1;
		lw_u8 bit2:1;
		lw_u8 bit1:1;
		lw_u8 bit0:1;
	}bits;
	lw_u8 all;
#elif OSLW_TASK_NUM_MAX>8 && OSLW_TASK_NUM_MAX<=16
	struct{
		lw_u16 bit15:1;
		lw_u16 bit14:1;
		lw_u16 bit13:1;
		lw_u16 bit12:1;
		lw_u16 bit11:1;
		lw_u16 bit10:1;
		lw_u16 bit9:1;
		lw_u16 bit8:1;
		lw_u16 bit7:1;
		lw_u16 bit6:1;
		lw_u16 bit5:1;
		lw_u16 bit4:1;
		lw_u16 bit3:1;
		lw_u16 bit2:1;
		lw_u16 bit1:1;
		lw_u16 bit0:1;
	}bits;
	lw_u16 all;
#elif OSLW_TASK_NUM_MAX>16 && OSLW_TASK_NUM_MAX<=32
	struct{
		lw_u32 bit31:1;
		lw_u32 bit30:1;
		lw_u32 bit29:1;
		lw_u32 bit28:1;
		lw_u32 bit27:1;
		lw_u32 bit26:1;
		lw_u32 bit25:1;
		lw_u32 bit24:1;
		lw_u32 bit23:1;
		lw_u32 bit22:1;
		lw_u32 bit21:1;
		lw_u32 bit20:1;
		lw_u32 bit19:1;
		lw_u32 bit18:1;
		lw_u32 bit17:1;
		lw_u32 bit16:1;
		lw_u32 bit15:1;
		lw_u32 bit14:1;
		lw_u32 bit13:1;
		lw_u32 bit12:1;
		lw_u32 bit11:1;
		lw_u32 bit10:1;
		lw_u32 bit9:1;
		lw_u32 bit8:1;
		lw_u32 bit7:1;
		lw_u32 bit6:1;
		lw_u32 bit5:1;
		lw_u32 bit4:1;
		lw_u32 bit3:1;
		lw_u32 bit2:1;
		lw_u32 bit1:1;
		lw_u32 bit0:1;
	}bits;
	lw_u32 all;
#elif OSLW_TASK_NUM_MAX>32 && OSLW_TASK_NUM_MAX<=64
	struct{
		lw_u64 bit63:1;
		lw_u64 bit62:1;
		lw_u64 bit61:1;
		lw_u64 bit60:1;
		lw_u64 bit59:1;
		lw_u64 bit58:1;
		lw_u64 bit57:1;
		lw_u64 bit56:1;
		lw_u64 bit55:1;
		lw_u64 bit54:1;
		lw_u64 bit53:1;
		lw_u64 bit52:1;
		lw_u64 bit51:1;
		lw_u64 bit50:1;
		lw_u64 bit49:1;
		lw_u64 bit48:1;
		lw_u64 bit47:1;
		lw_u64 bit46:1;
		lw_u64 bit45:1;
		lw_u64 bit44:1;
		lw_u64 bit43:1;
		lw_u64 bit42:1;
		lw_u64 bit41:1;
		lw_u64 bit40:1;
		lw_u64 bit39:1;
		lw_u64 bit38:1;
		lw_u64 bit37:1;
		lw_u64 bit36:1;
		lw_u64 bit35:1;
		lw_u64 bit34:1;
		lw_u64 bit33:1;
		lw_u64 bit32:1;
		lw_u64 bit31:1;
		lw_u64 bit30:1;
		lw_u64 bit29:1;
		lw_u64 bit28:1;
		lw_u64 bit27:1;
		lw_u64 bit26:1;
		lw_u64 bit25:1;
		lw_u64 bit24:1;
		lw_u64 bit23:1;
		lw_u64 bit22:1;
		lw_u64 bit21:1;
		lw_u64 bit20:1;
		lw_u64 bit19:1;
		lw_u64 bit18:1;
		lw_u64 bit17:1;
		lw_u64 bit16:1;
		lw_u64 bit15:1;
		lw_u64 bit14:1;
		lw_u64 bit13:1;
		lw_u64 bit12:1;
		lw_u64 bit11:1;
		lw_u64 bit10:1;
		lw_u64 bit9:1;
		lw_u64 bit8:1;
		lw_u64 bit7:1;
		lw_u64 bit6:1;
		lw_u64 bit5:1;
		lw_u64 bit4:1;
		lw_u64 bit3:1;
		lw_u64 bit2:1;
		lw_u64 bit1:1;
		lw_u64 bit0:1;
	}bits;
	lw_u64 all;
#else
	#error "TASK NUM IS OVER"
#endif
}OSlwCoreGroupUN;

//------------------------------------------
//<ö��>OSlwCoreErrorNUM</ö��>
//<ö�ٹ���>ö���ں˴�������</ö�ٹ���>
//------------------------------------------
typedef enum{
	OSlwCoreError_NoError=0,//�޴���
	OSlwCoreError_PriorityRedefine//�������ȼ��ض������
}OSlwCoreErrorNUM;

//------------------------------------------
//<ö��>OSlwCoreStatusNUM</ö��>
//<ö�ٹ���>ö���ں�״̬����</ö�ٹ���>
//------------------------------------------
typedef enum{
	OSlwCoreStatus_NAN=0,//δ����״̬
	OSlwCoreStatus_Initial=1,//��ʼ����
	OSlwCoreStatus_Running=0xaa,//����������
	OSlwCoreStatus_Error=0x55//�ں˴���
}OSlwCoreStatusNUM;


//------------------------------------------
//<�ṹ����>OSlwParameter_toForm</�ṹ����>
//<�ṹ�幦��>����ϵͳ�ں˽ṹ��</�ṹ�幦��>
//------------------------------------------
typedef struct OSLW_CORE_STRUCT{

	//��Ա����
	OSlwCoreGroupUN InitialFlagGroup;//��ʼ����־��
	OSlwCoreGroupUN ReadyFlagGroup;//׼����ɱ�־��

	OSlwCoreErrorNUM CoreError;//�ں˴���
	OSlwCoreStatusNUM CoreStatus;//�ں�״̬

	lw_u8 DispatchEable;//������ʹ�ܱ�־ 0:�رյ����� 1:����������
	lw_u8 TaskRunningNum;//��ǰע����������
	lw_u8 TaskRunningList[OSLW_TASK_NUM_MAX];//�Լ�ע�����������ȼ� ���ڿ��ٲ�ѯ����

	struct OSLW_TASK_STRUCT *pTaskList[OSLW_TASK_NUM_MAX];//ע���������Ŀ��ƿ�

	lw_u8 CurrentTaskIndex;//��ǰ��������ȼ�
	struct OSLW_TASK_STRUCT *pCurrentTask;//��ǰ������ƿ�

	lw_u8 LastTaskIndex;//֮ǰ��������ȼ�
	struct OSLW_TASK_STRUCT *pLastTask;//֮ǰ��������ȼ�

	_BP DispatchBreakPoint;//�������ϵ�

	//��Ա����
	void (*DispatchFun)(struct OSLW_CORE_STRUCT *pOS);//����������
	void (*ClockCBFun)(struct OSLW_CORE_STRUCT *pOS);//ϵͳʱ�ӻص����� !!!!!!!!!�������Գ�Ա��������!!!!!!!!!
	void (*StartFun)(struct OSLW_CORE_STRUCT *pOS);//ϵͳ��ʼ����
	struct OSLW_CORE_STRUCT *(*TaskAppendFun)(struct OSLW_CORE_STRUCT *pOS,struct OSLW_TASK_STRUCT *pta);//����ע�ắ��


	//������ʱ�м����
	lw_u8 n1_Dispatch,n2_Dispatch;
	lw_u8 Temp;
	lw_u8 temp2;

}OSlwCoreSTU;



//��������
void OSlwTaskDispatch(OSlwCoreSTU *pOS);
void OSlwClockCallBack(OSlwCoreSTU *pOS);
void OSlwCoreInitial(OSlwCoreSTU *pOS);
OSlwCoreSTU* OSlwTaskAppend(OSlwCoreSTU *pOS,struct OSLW_TASK_STRUCT *pta);
void OSlwCoreStart(OSlwCoreSTU *pOS);
void _quicksort (void *const pbase, size_t total_elems, size_t size,_compar_fn cmp);
lw_16 comp(const void*a,const void*b);



//<�����㷨��>
#define SWAP(a, b, size)						      \
  do									      \
    {									      \
      size_t __size = (size);						      \
      char *__a = (a), *__b = (b);					      \
      do								      \
	{								      \
	  char __tmp = *__a;						      \
	  *__a++ = *__b;						      \
	  *__b++ = __tmp;						      \
	} while (--__size > 0);						      \
    } while (0)

#define MAX_THRESH 4


typedef struct
  {
    char *lo;
    char *hi;
  } stack_node;

#define STACK_SIZE	(CHAR_BIT * sizeof(size_t))
#define PUSH(low, high)	((void) ((top->lo = (low)), (top->hi = (high)), ++top))
#define	POP(low, high)	((void) (--top, (low = top->lo), (high = top->hi)))
#define	STACK_NOT_EMPTY	(stack < top)
//</�����㷨��>


//�꺯�� & ��ģ��

//�ϵ㱣��
#define REMEMBER(x,r) r=SAVE((x));if(!(r))

//�����Ӻ�������
//<����>LV:Ƕ�׵ȼ��ȼ�(����������ֱ��ʹ�õ�����ȼ�Ϊ0 ����һ��Ϊ1 ��������) pta:����ָ�� F:�����õĺ���</����>
//<ʾ��> TaskSubFunCall(0,pta,fun1); pta�������fun1Ƕ�׵ȼ�0 </ʾ��> 
//!!!!!!!!!!!!void fun1(OSlwTaskSTU *pta,void *p)!!!!!!!!!!!!!!!!!!!!!!!!!

#define OSlwTaskSubFunCall(LV,PTA,F) do {REMEMBER(PTA->BreakPoint[LV],PTA->BreakPointReturn[LV])\
																				{F(PTA,(void *)(&(PTA->BreakPoint[LV])));}}while(0)

//�����Ӻ�������
//!!!!!!��TaskSubFunCall�ɶԵ��� ���ڷ���!!!!!!																				
#define OSlwTaskSubFunReturn(PTA,P) do { LOAD((*((_BP *)(P))),PTA->Priority);}while(0)

//˯��N��ʱ��
//<����>A:������ƿ�ָ�� N:����</����>
#define OSlwSleepN(A,N) do {REMEMBER(A->BreakPoint[OSLW_TASK_BREAKPOINT_DEEP-1],A->BreakPointReturn[OSLW_TASK_BREAKPOINT_DEEP-1]){ A->SleepFun(A,N-1);}} while(0)


#endif /* OSLW_CORE_H_ */
