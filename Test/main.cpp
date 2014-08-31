#include "main.h"


main::main(void)
{
}


main::~main(void)
{
}


int main () {
	try{
		//int a = 1 / 0;
		
		throw 1;
	}catch(int i){
		printf("%d", i);
	}
}