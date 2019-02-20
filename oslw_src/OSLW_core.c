/*
 * OSLW_core.c
 *
 *  Created on: 2017-7-14
 *      Author: slw
 */

#include "OSLW_include.h"

//------------------------------------------
//<������>OSlwTaskDispatch</������>
//<����˵��>��������� ����ϵͳ����</����˵��>
//<����˵��>pOS:this</����˵��>
//<���˵��>void</���˵��>
//------------------------------------------
void OSlwTaskDispatch(OSlwCoreSTU *pOS)
{

	OSLW_assert(!pOS);

	if(!(pOS->DispatchEable))//�жϵ������Ƿ�����
	{
		while(pOS->pCurrentTask->TaskStatus != OSlwTaskStatus_Ready);//ֱ�ӵȴ��������׼��״̬

		return ;
	}
	if(pOS->InitialFlagGroup.all)//�жϳ�ʼ����־���Ƿ�Ϊ0
	{//�����Ϊ0 ˵��������δ��ʼ��������
		for(pOS->n1_Dispatch=0;pOS->n1_Dispatch<pOS->TaskRunningNum;pOS->n1_Dispatch++)//ѭ������δ��ʼ��������  //---------���Բ����㷨�Ż�--------//
		{
			pOS->Temp=pOS->TaskRunningList[pOS->n1_Dispatch];
			if((pOS->InitialFlagGroup.all & ((lw_u64)1<<(pOS->Temp))) && //�����ʼ����־���ĳһλΪ1
					(pOS->pTaskList[pOS->Temp]))//����������Ѿ�ע����
			{
				pOS->pCurrentTask=pOS->pTaskList[pOS->Temp];

				if(!SAVE(pOS->DispatchBreakPoint))//�ȴ�����������
				{
					if(pOS->pCurrentTask->TaskFun)//��ת֮ǰ���жϺ���ָ���Ƿ�Ϊ0
					{
						pOS->pCurrentTask->TaskFun(pOS->pCurrentTask);
					}//end if

				}//end if
				pOS->InitialFlagGroup.all&=(~((lw_u64)1<<(pOS->Temp)));//�����ʼ����־λ
				pOS->ReadyFlagGroup.all|=((lw_u64)1<<(pOS->Temp));
				pOS->pLastTask=pOS->pCurrentTask;
				pOS->pCurrentTask->TaskStatus=OSlwTaskStatus_Ready;
			}//end if
		}//end for
	}
	if(pOS->ReadyFlagGroup.all & (~((lw_u64)1<<(OSLW_TASK_NUM_MAX-1))))//����������ȼ�--�������� �鿴�����Ƿ�׼�����
	{
		for(pOS->n2_Dispatch=0;pOS->n2_Dispatch<pOS->TaskRunningNum;pOS->n2_Dispatch++)//ѭ�����Ҿ���������  //---------���Բ����㷨�Ż�--------//
		{
			if(pOS->ReadyFlagGroup.all & ((lw_u64)1<<(pOS->TaskRunningList[pOS->n2_Dispatch]))) //���������־���ĳһλΪ1
			{
				pOS->LastTaskIndex=pOS->CurrentTaskIndex;
				pOS->pLastTask=pOS->pCurrentTask;//��¼��һ������

				pOS->CurrentTaskIndex=pOS->TaskRunningList[pOS->n2_Dispatch];
				pOS->pCurrentTask=pOS->pTaskList[pOS->CurrentTaskIndex];//���±�������
				pOS->pCurrentTask->TaskStatus=OSlwTaskStatus_Running;//��������״̬
				LOAD(pOS->pCurrentTask->BreakPoint[OSLW_TASK_BREAKPOINT_DEEP-1],pOS->LastTaskIndex);//������ת
			}//end if
		}//end for
	}//end if
	else//˵����ǰû������׼������ ִ�п�������
	{
		pOS->pLastTask=pOS->pCurrentTask;
		pOS->LastTaskIndex=pOS->CurrentTaskIndex;
		pOS->pCurrentTask=pOS->pTaskList[OSLW_TASK_NUM_MAX-1];
		LOAD(pOS->pCurrentTask->BreakPoint[OSLW_TASK_BREAKPOINT_DEEP-1],pOS->LastTaskIndex);
	}

	return;
}

//------------------------------------------
//<������>OSlwClockCallBack</������>
//<����˵��>����ϵͳʱ�ӽ��Ļص� �˺�������붨ʱ���ж�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!</����˵��>
//<����˵��>pOS:this</����˵��>
//<���˵��>void</���˵��>
//------------------------------------------
void OSlwClockCallBack(OSlwCoreSTU *pOS)
{
	OSLW_assert(!pOS);

	lw_u8 n=0;
	lw_u8 tindex=0;
	OSlwTaskSTU *pta;
	if(pOS->CoreStatus!=OSlwCoreStatus_Running)
		return;
	for(;n<pOS->TaskRunningNum;n++)//ѭ�������б�
	{
		tindex=pOS->TaskRunningList[n];
		pta=pOS->pTaskList[tindex];//ȡ�����������
		//�ж�����״̬
		if(pta->TaskStatus==OSlwTaskStatus_Wait_ForSleep)//����� �ȴ�˯��״̬
		{
			if(!(--(pta->SleepCount)))//˯�߼Ĵ���-- ���Ϊ0��˵������ʱ�䵽��
			{
				pOS->ReadyFlagGroup.all|=(1<<tindex);
				pta->TaskStatus=OSlwTaskStatus_Ready;//ת������״̬ Ϊ׼��̬
			}//end if

		}//end if

	}//end for

	pOS->pTaskList[OSLW_TASK_NUM_MAX-1]->PrivateMem.m8[0]++;


}

//------------------------------------------
//<������>OSlwCoreInitial</������>
//<����˵��>����ϵͳ�ں˳�ʼ������ ��ʼ���ں˼Ĵ��� ����ϵͳ�ڲ�����</����˵��>
//<����˵��>pOS:this</����˵��>
//<���˵��>void</���˵��>
//------------------------------------------

void OSlwCoreInitial(OSlwCoreSTU *pOS)
{
	OSLW_assert(!pOS);
	memset(pOS,0,sizeof(OSlwCoreSTU));//�������
	memset(pOS->TaskRunningList,OSLW_TASK_NUM_MAX+1,sizeof(pOS->TaskRunningList));//ִ�б��ʼ��

	//����ָ���ʼ��
	pOS->ClockCBFun=OSlwClockCallBack;
	pOS->DispatchFun=OSlwTaskDispatch;
	pOS->TaskAppendFun=OSlwTaskAppend;
	pOS->StartFun=OSlwCoreStart;
	//�ڲ����� ��������
	OSlwTaskInit(//���������ʼ��
			&OSlwInlineTaskBoring,
			OSLW_TASK_NUM_MAX-1,
			"~_~",
			0,
			(void *)0,
			OSlwInlineTaskBoringExe
			);
			
	OSlwTaskAppend(pOS,&OSlwInlineTaskBoring);//��������׷��


}

//------------------------------------------
//<������>OSlwTaskAppend</������>
//<����˵��>����ϵͳ׷������ !!!!!!�ú�������������ƿ�ĳ�ʼ��!!!!!!!!!</����˵��>
//<����˵��>pOS:this pta:׷��������ƿ�</����˵��>
//<���˵��>pOS:this</���˵��>
//------------------------------------------
OSlwCoreSTU *OSlwTaskAppend(OSlwCoreSTU *pOS,OSlwTaskSTU *pta)
{
	OSLW_assert(!pOS);
	OSLW_assert(!pta);

	if(pOS->pTaskList[pta->Priority])//�жϸ�������Ƿ��Ѿ���ע��
	{
		pOS->CoreError=OSlwCoreError_PriorityRedefine;//�ں��쳣����
		return pOS;//����
	}

	pta->pOS=pOS;//���������Ĳ���ϵͳָ��


	pOS->pTaskList[pta->Priority]=pta;//������ƿ������Ӧλ��

	pOS->TaskRunningList[pOS->TaskRunningNum]=pta->Priority;//�������ȼ����������б��
	
	pOS->TaskRunningNum++;//����������+1
	
	_quicksort(pOS->TaskRunningList,pOS->TaskRunningNum+20,sizeof(pOS->TaskRunningList[0]),comp);//�����б��������� ��С���

	pOS->InitialFlagGroup.all|=((lw_u64)1<<pta->Priority);//�ں˳�ʼ����־������

	return pOS;
}

//------------------------------------------
//<������>OSlwCoreStart</������>
//<����˵��>OSLW��ʼ !!!!!��������������ƿ������ϵͳ�ں˳�ʼ�����֮���ٵ���!!!!!!</����˵��>
//<����˵��>pOS:this</����˵��>
//<���˵��>void</���˵��>
//------------------------------------------
void OSlwCoreStart(OSlwCoreSTU *pOS)
{

	pOS->DispatchEable=1;//������ʹ��
	pOS->CoreStatus=OSlwCoreStatus_Running;//�����ں�ת��Ϊ����̬
	pOS->DispatchFun(pOS);//ִ���������

	while(1)//!!!!!!!!!!!!��������²���������ѭ��!!!!!!!!!!!!!!!!!!!!!
	{
		;
	}

}


//------------------------------------------
//<������>comp</������>
//<����˵��>�ȽϺ��� �������ȼ�����</����˵��>
//------------------------------------------
lw_16 comp(const void*a,const void*b)
{

	return (*(lw_u8*)a-*(lw_u8*)b);

}

//------------------------------------------
//<������>_quicksort</������>
//<����˵��>��������</����˵��>
//------------------------------------------
void _quicksort (void *const pbase, size_t total_elems, size_t size,_compar_fn cmp)
{
  char *base_ptr = (char *) pbase;

  const size_t max_thresh = MAX_THRESH * size;

  if (total_elems == 0)
    /* Avoid lossage with unsigned arithmetic below.  */
    return;

  if (total_elems > MAX_THRESH)
    {
      char *lo = base_ptr;
      char *hi = &lo[size * (total_elems - 1)];
      stack_node stack[STACK_SIZE];
      stack_node *top = stack;

      PUSH (NULL, NULL);

      while (STACK_NOT_EMPTY)
        {
          char *left_ptr;
          char *right_ptr;
	  char *mid = lo + size * ((hi - lo) / size >> 1);

	  if ((*cmp) ((void *) mid, (void *) lo) < 0)
	    SWAP (mid, lo, size);
	  if ((*cmp) ((void *) hi, (void *) mid) < 0)
	    SWAP (mid, hi, size);
	  else
	    goto jump_over;
	  if ((*cmp) ((void *) mid, (void *) lo) < 0)
	    SWAP (mid, lo, size);
	jump_over:;

	  left_ptr  = lo + size;
	  right_ptr = hi - size;
	  do
	    {
	      while ((*cmp) ((void *) left_ptr, (void *) mid) < 0)
		left_ptr += size;

	      while ((*cmp) ((void *) mid, (void *) right_ptr) < 0)
		right_ptr -= size;

	      if (left_ptr < right_ptr)
		{
		  SWAP (left_ptr, right_ptr, size);
		  if (mid == left_ptr)
		    mid = right_ptr;
		  else if (mid == right_ptr)
		    mid = left_ptr;
		  left_ptr += size;
		  right_ptr -= size;
		}
	      else if (left_ptr == right_ptr)
		{
		  left_ptr += size;
		  right_ptr -= size;
		  break;
		}
	    }
	  while (left_ptr <= right_ptr);

          if ((size_t) (right_ptr - lo) <= max_thresh)
            {
              if ((size_t) (hi - left_ptr) <= max_thresh)
		/* Ignore both small partitions. */
                POP (lo, hi);
              else
		/* Ignore small left partition. */
                lo = left_ptr;
            }
          else if ((size_t) (hi - left_ptr) <= max_thresh)
	    /* Ignore small right partition. */
            hi = right_ptr;
          else if ((right_ptr - lo) > (hi - left_ptr))
            {
	      /* Push larger left partition indices. */
              PUSH (lo, right_ptr);
              lo = left_ptr;
            }
          else
            {
	      /* Push larger right partition indices. */
              PUSH (left_ptr, hi);
              hi = right_ptr;
            }
        }
    }

#define min(x, y) ((x) < (y) ? (x) : (y))
  {
    char *const end_ptr = &base_ptr[size * (total_elems - 1)];
    char *tmp_ptr = base_ptr;
    char *thresh = min(end_ptr, base_ptr + max_thresh);
    char *run_ptr;
    for (run_ptr = tmp_ptr + size; run_ptr <= thresh; run_ptr += size)
      if ((*cmp) ((void *) run_ptr, (void *) tmp_ptr) < 0)
        tmp_ptr = run_ptr;

    if (tmp_ptr != base_ptr)
      SWAP (tmp_ptr, base_ptr, size);

    run_ptr = base_ptr + size;
    while ((run_ptr += size) <= end_ptr)
      {
	tmp_ptr = run_ptr - size;
	while ((*cmp) ((void *) run_ptr, (void *) tmp_ptr) < 0)
	  tmp_ptr -= size;

	tmp_ptr += size;
        if (tmp_ptr != run_ptr)
          {
            char *trav;

	    trav = run_ptr + size;
	    while (--trav >= run_ptr)
              {
                char c = *trav;
                char *hi, *lo;

                for (hi = lo = trav; (lo -= size) >= tmp_ptr; hi = lo)
                  *hi = *lo;
                *hi = c;
              }
          }
      }
  }
}
