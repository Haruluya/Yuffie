#include"reagentApply.h"


Status initReagentApply() {
	reagentApplyList = (ReagentApplyLinkList)malloc(sizeof(RNode));
	if (!reagentApplyList)
	{
		return ERROR;
	}
	reagentApplyList->next = NULL; 
	return OK;
}



Status addReagentApplyItem(ReagentApplyItem item) {
	if (!item.reagentName) {
		return INFASIBLE;
	}
	ReagentApplyLinkList ptr = reagentApplyList;
	while (ptr->next) {
		ptr = reagentApplyList->next;
	}
	RNode* node = (RNode*)malloc(sizeof(RNode));
	node->data.reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
	strcpy(node->data.reagentName, item.reagentName);
	node->data.reagentId = item.reagentId;
	node->data.reagentNum = item.reagentNum;
	ptr->next = node;
	node->next = NULL;

	reagentApplyListLen++;
	return OK;
}


Status deleteReagentApplyItemById(int index) {
	if (index < 0) {
		return INFASIBLE;
	}
	ReagentApplyLinkList ptr = reagentApplyList->next;
	while ((ptr-reagentApplyList) < reagentApplyListLen) {
		if ((ptr - reagentApplyList) == index) {
			ptr->next = ptr->next->next;
			return OK;
		}
		ptr = ptr->next;
	}
	reagentApplyListLen--;
	return NOT_FOUND;
}


Status commitReagentApply() {
	FILE* fp;
	String fileName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
	String str = (String)malloc(sizeof(char) * INFO_MAXSIZE);
	sprintf(str, "%d", presentUser.id);
	fileName = strcat(strcat(strcat(strcpy(fileName, "./reagentApply/"), str), presentUser.userName), ".txt");
	/*
	   @check:"�ļ��򿪴�����."
	*/
	if (!(fp = fopen(fileName, "w")))
	{
		return ERROR;
	}
	ReagentApplyLinkList ptr = reagentApplyList->next;
	while (ptr) {
		fprintf(fp,
			"%s %d %d\n",
			ptr->data.reagentName,
			ptr->data.reagentId,
			ptr->data.reagentNum
		);
		ptr = ptr->next;
	}
	fclose(fp);
	return OK;
}




Status initResultList() {
	FILE* fp;
	/*
		   @check:"�ļ��򿪴�����."
		*/
	if (!(fp = fopen("reagentAuditResult.txt", "r")))
	{
		return ERROR;
	}
	while (!feof(fp))
	{
		fgets(BUFF, sizeof(BUFF), fp);
		if (!strcmp(BUFF, "\0")) {
			break;
		}
		//��ȡ�Կո��зֵ���������.
		String* reagentResultInfo = yuffieSplit(BUFF);

		if (atoi(reagentResultInfo[3]) == presentUser.id) {
			String* reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
			strcpy(reagentName, reagentResultInfo[0]);
			ReagentApplyItem item = {
				reagentName,
				atoi(reagentResultInfo[1]),
				atoi(reagentResultInfo[2]),
			};
			reagentResultList[reagentResultListLen++] = item;
		}
		BUFF[0] = '\0';
	}
	fclose(fp);
	return OK;
}