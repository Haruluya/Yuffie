#include"reagentCheckStruct.h"


//��ȡ����apply�ļ�����
Status initReagentApplyFiles();

//��ʼ���������б�
Status initReagentApplyList();

//��������
Status addReagentCheckItem(ReagentCheckItem);

//ɾ�������
Status deleteReagentCheckItemById(int);

//�ύ�����
Status commitReagentCheck();