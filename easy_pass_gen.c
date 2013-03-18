#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#if __unix || __linux || __FreeBSD__ || __NetBSD__
//未定
#endif
 
#if _WIN32 || _WIN64
#include <windows.h>
int ccp(LPTSTR szData);
#endif

/*
GPL v3 LICENSE http://www.gnu.org/licenses/gpl.html
Copyright (C) α改 @alpha_kai_NET 2012-2013 alpha-kai-net.info
簡易パスワードジェネレーター
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

	printf("任意の桁数のパスワードを生成します\n");
	printf("abcdefghijklmnopqrstuvexyz01234567_\n");
	printf("上の37この文字を組み合わせて文字列(パスワード)を生成します\n\n");
	printf("パスワードの桁数をセットしてください\n>");
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
				printf("error:事故りました・・・終了します\nゴメンなサイ\n");

				//return 2;
				break;
			}
		}
	}
	
	printf("設定された桁数:%d\n",i);
	printf("RESULT:\n%s\n",str); 
	//暫定Winのみに対応 文字列クリップボードにコピー
#if _WIN32 || _WIN64
	printf("現在生成したパスワードをクリップボードにコピーしますか？\n");
	printf("入力してください(1:コピーする 2:コピーしないで終了)\n>");
	scanf("%d", &ss);
	switch(ss){
		case 1:
		
			rccp=ccp(str);
			
			if(rccp!=0){
					printf("生成したパスワードのクリップボードへのコピーに失敗しました\n");
			}
			else{
				printf("正常にコピーしました\n");
			}
		
		break;
		
		case 2:
			printf("クリップボードへのコピーは行われませんでした\n");
		break;
		
		default:
			printf("1/2以外の値が入力されました\n");
			printf("クリップボードへのコピーは行われませんでした\n");
		break;
	}
#endif 
 	printf("DONE\n");

	return 0;
}

//Win用クリップボードにコピー
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
