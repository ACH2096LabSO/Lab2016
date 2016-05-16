#include <stdio.h>

void imprime(){
	printf("%s\n", "Teste");
	return;
}

int main(){
	
	for (int i = 0; i < 3; ++i)
	{
		/* code */
		imprime();
	}
	return 0;
}