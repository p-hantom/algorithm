#define LOCAL
#include <cstdio>
using namespace std;

int main(){
	#ifdef LOCAL
		freopen("test.txt","r",stdin);
		freopen("test.out","w",stdout);
	#endif
	int x;
	scanf("%d",&x);
	printf("%d",x);
	
	return 0;
}
