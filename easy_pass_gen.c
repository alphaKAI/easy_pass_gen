#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#if __unix || __linux || __FreeBSD__ || __NetBSD__
//����
#endif
 
#if _WIN32 || _WIN64
#include <windows.h>
int ccp(LPTSTR szData);
#endif

/*
GPL v3 LICENSE http://www.gnu.org/licenses/gpl.html
Copyright (C) ���� @alpha_kai_NET 2012-2013 alpha-kai-net.info
�ȈՃp�X���[�h�W�F�l���[�^�[
*/

int main(void){
 
	int i;
	int t;
	int ss;
	int rccp;
	char str[100000]={0};
	//abcdefghijklmnopqrstuvexyz01234567_
	char strset[38] = {'\0','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','_'};
	
	t=0;
	rccp=0;
	
	srand((unsigned)time(NULL));

	printf("�C�ӂ̌����̃p�X���[�h�𐶐����܂�\n");
	printf("abcdefghijklmnopqrstuvexyz01234567_\n");
	printf("���37���̕�����g�ݍ��킹�ĕ�����(�p�X���[�h)�𐶐����܂�\n\n");
	printf("�p�X���[�h�̌������Z�b�g���Ă�������\n>");
	scanf("%d",&i);

	#pragma omp parallel
	{
		while(1){
			str[t] = strset[rand()%37 + 1];
 
			t++;

			if(t==i&&strlen(str)==i){
				break;
			}
			else if(t==i&&strlen(str)!=i){
				printf("error:���̂�܂����E�E�E�I�����܂�\n�S�����ȃT�C\n");

				//return 2;
				break;
			}
		}
	}
	
	printf("�ݒ肳�ꂽ����:%d\n",i);
	printf("RESULT:\n%s\n",str); 
	//�b��Win�݂̂ɑΉ� ������N���b�v�{�[�h�ɃR�s�[
#if _WIN32 || _WIN64
	printf("���ݐ��������p�X���[�h���N���b�v�{�[�h�ɃR�s�[���܂����H\n");
	printf("���͂��Ă�������(1:�R�s�[���� 2:�R�s�[���Ȃ��ŏI��)\n>");
	scanf("%d", &ss);
	switch(ss){
		case 1:
		
			rccp=ccp(str);
			
			if(rccp!=0){
					printf("���������p�X���[�h�̃N���b�v�{�[�h�ւ̃R�s�[�Ɏ��s���܂���\n");
			}
			else{
				printf("����ɃR�s�[���܂���\n");
			}
		
		break;
		
		case 2:
			printf("�N���b�v�{�[�h�ւ̃R�s�[�͍s���܂���ł���\n");
		break;
		
		default:
			printf("1/2�ȊO�̒l�����͂���܂���\n");
			printf("�N���b�v�{�[�h�ւ̃R�s�[�͍s���܂���ł���\n");
		break;
	}
#endif 
 	printf("DONE\n");

	return 0;
}

//Win�p�N���b�v�{�[�h�ɃR�s�[
#if _WIN32 || _WIN64
int ccp(LPTSTR szData)
{
	HGLOBAL hGlobal;
	LPTSTR pMem;
 
	hGlobal = GlobalAlloc(GHND, lstrlen( szData ) + 128 );
	if(hGlobal==NULL) {
		return 2;
	}
	pMem = (LPTSTR)GlobalLock( hGlobal );
	if(pMem==NULL) {
		GlobalFree(hGlobal);
		return 3;
	}
	lstrcpy(pMem, szData);
	GlobalUnlock(hGlobal);
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hGlobal);
	CloseClipboard();
 
	return 0;
}
#endif
