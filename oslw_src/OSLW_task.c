/*
 * OSLW_task.c
 *
 *  Created on: 2017-7-14
 *      Author: slw
 */

#include "OSLW_include.h"

OSlwTaskSTU OSlwInlineTaskBoring;

//------------------------------------------
//<������>OSlwTaskInit</������>
//<����˵��>�����ʼ������</����˵��>
//<����˵��>pta:������ƿ�ָ��  priority:���ȼ�  name:����(����:OSLW_TASK_NAME_LENGTH_MAX) ExMemLen:�ⲿ�洢���� ExMemarr:�ⲿ�洢��ַ fun:������</����˵��>
//<���˵��>void</���˵��>
//------------------------------------------
void OSlwTaskInit(OSlwTaskSTU *pta,
		lw_u8 priority,
		lw_8 *name,
		lw_u16 ExMemLen,
		void *ExMemarr,
		void (*fun)(struct OSLW_TASK_STRUCT *pta)
		)
{
	memset(pta,0,sizeof(OSlwTaskSTU));//���������ƿ�
	pta->Priority=priority;//���ȼ�
	strncpy(pta->Name,name,OSLW_TASK_NAME_LENGTH_MAX);//����
	pta->TaskFun=fun;//������
	pta->SleepFun=OSlwTaskSleep;//˯�ߺ���
	if(ExMemarr!=NULL && ExMemLen!=0)//��� �ⲿ�洢��������
	{
		pta->ExternMem.Length=ExMemLen;
		pta->ExternMem.arr=ExMemarr;
	}


}

//------------------------------------------
//<������>OSlwInlineTaskBoringExe</������>
//<����˵��>����������</����˵��>
//<����˵��>pta:this</����˵��>
//<���˵��>void</���˵��>
//------------------------------------------
void OSlwInlineTaskBoringExe(OSlwTaskSTU *pta)
{

	
	OSLW_TASK_BENGIN(pta);//���� ���������ʼ�����
	for(;;)//��ѭ��
	{
		
		while(!(pta->PrivateMem.m8[0])){;}//�ȴ��������һ�� !!!!!�����ڴ�ʱ����͹���ģʽ!!!!!!!!
		pta->PrivateMem.m8[0]=0;//����
		pta->pOS->DispatchFun(pta->pOS);//ִ���������
						
	}




}

//------------------------------------------
//<������>OSlwTaskSleep</������>
//<����˵��>����˯�ߺ���</����˵��>
//<����˵��>pta:this, n :˯�߽�����</����˵��>
//<���˵��>void</���˵��>
//------------------------------------------
void OSlwTaskSleep(OSlwTaskSTU *pta,lw_u32 n)
{
	pta->SleepCount=n;
	pta->TaskStatus=OSlwTaskStatus_Wait_ForSleep;
	pta->pOS->ReadyFlagGroup.all&=~((lw_u64)1<<(pta->Priority));
	pta->pOS->DispatchFun(pta->pOS);
}
