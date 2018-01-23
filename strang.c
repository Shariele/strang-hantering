/*Rasmus Lennartsson 2017-2018*/



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STRINGMAX 1024


int strangLen(char* sp){
	char c = '\0';
	int size = 0;

	while(*sp++ != c)
		size++;

	return size;
}

// sp = destination dummyChar = source
void copyString(char* sp, char* dummyChar){
	int size = strangLen(dummyChar), i;
	char* spCopy = sp;
	for (i = 0; i < size; i++){
		*sp++ = *dummyChar++;
		if(i == size-1){
			*sp = '\0';
		}
	}

	sp = spCopy;
}

void commonToCapital(char* sp){
	int size = strangLen(sp), i, commonLow = 97, commonHigh = 122, ascii = 0;
	char *spCopy = sp, c;

	for(i = 0; i < size; i++){
		c = (int)*sp; 
		if(c >= commonLow && c <= commonHigh){
			ascii = c;
			ascii -= 32;
			*sp++ = (char)ascii;
		}else{
			// *sp++;
		}
	}

	sp = spCopy;
}

void shiftStrangLeft(char* sp){
	int size = strangLen(sp), i;
	char *buffer, sll, *spCopy = sp, *bufferCopy;

	buffer = (char *)malloc(size * sizeof(char));
	bufferCopy = buffer;

	// printf("Sp: %d\n", sp);
	sll = *sp++;

	for(i = 1; i < size; i++){
		// printf("Sp: %d\n", sp);
		// printf("Buff: %d\n", buffer);
		*buffer++ = *sp++;
	}
	sp = spCopy;
	buffer = bufferCopy;
	// printf("Sp: %d\n", sp);
	// printf("Buff: %d\n", buffer);
	for(i = 0; i < size; i++){
		*sp++ = *buffer++;
	}
	sp -= 1;	//korrigera pekaren
	*sp = sll;
	sp = spCopy;
	buffer = bufferCopy;
	free(buffer);

	// printf("%s\n", sp);
}

void shiftStrangRight(char* sp){
	int size = strangLen(sp), i;
	char *buffer, srl, *spCopy = sp, *bufferCopy;

	buffer = (char *)malloc(size * sizeof(char));
	bufferCopy = buffer;

	sp += size-1;
	srl = *sp;
	sp = spCopy;

	for(i = 0; i < size - 1; i++){
		*buffer++ = *sp++;
	}
	sp = spCopy;
	*sp++ = srl;
	buffer = bufferCopy;
	for(i = 1; i < size; i++){
		*sp++ = *buffer++;
	}
	sp = spCopy;
	buffer = bufferCopy;
	free(buffer);

	// printf("%s\n", sp);
}

void flipStrang(char* sp){
	int size = strangLen(sp), i;
	char *buffer, *bufferCopy;

	buffer = (char *)malloc(size * sizeof(char));
	bufferCopy = buffer;

	for(i = 0; i < size; i++){
		*buffer++ = *sp++;
	}
	sp -= size;		//hoppa tillbaks till element ett.
	buffer -= 1;	//korrigera pekaren
	for(i = 0; i < size; i++){
		*sp++ = *buffer--;
	}

	buffer = bufferCopy;
	free(buffer);
}

void concStr(char* sp, char* dummyChar, char* newString){
	int i, newSize = 0, dummySize = strangLen(dummyChar), currentSize = strangLen(sp);
	newSize = currentSize + dummySize;
	
	// sp = sp + currentSize;
	for(i = 0; i < currentSize; i++){
		*newString++ = *sp++;
		// printf("%d\n", newString);
	}
	for(i = 0; i < dummySize; i++){
		*newString++ = *dummyChar++;
		// printf("%d\n", newString);
		if(i == dummySize-1){
			*newString = '\0';
		}
	}
	// printf("%d\n", newSize);
	newString -= newSize;

	// printf("%s\n", newString);
	// printf("%d\n", newSize);
}

void addBlank(char* sp, char* newString){
	int i, currentSize = strangLen(sp) + 1;		//+ 1 för att väga upp att \0 inte tas med i beräkningen från strangLen

	for(i = 0; i < currentSize; i++){
		// printf("%d\n", newString);
		*newString++ = *sp++;
		if(i == currentSize -1){
			*newString = '\0';
			// printf("%d\n", newString);
		}else if(i == currentSize - 2){
			*newString++ = ' ';
		}
	}
	currentSize += 1;
	
	
	newString -= currentSize;
	// printf("%d\n", newString);
	// printf("%s\n", newString);
	// printf("%d\n", newString);
	
	// printf("%d\n", *currentSize);
	// printf("%s\n", newString);
	// printf("%d\n", *currentSize);
}

int compStrang(char* sp, char* compString){
	// printf("%s\n", sp);
	int spSize = strangLen(sp), compSize = strangLen(compString), result, capitalLow = 65, capitalHigh = 90, c, o;
	char *spCopy = sp, *compCopy = compString;

	//o = original string
	//c = compare string
	while(*sp != '\0' || *compString != '\0'){
		o = (int)*sp;
		c = (int)*compString;
		// printf("O: %d\n", o);
		// printf("C: %d\n", c);

		if((*sp >= capitalLow && *sp <= capitalHigh)){
			o += 32;	// Difference between common and capital
		}
		if (*compString >= capitalLow && *compString <= capitalHigh){
			c += 32;
		}
		//Compare 
		if(o == c){
			result = 0;
		}else if(o <= c){
			result = 1;
			sp = spCopy;
			compString = compCopy;
			return result;
		}else if(o >= c){
			result = -1;
			sp = spCopy;
			compString = compCopy;
			return result;
		}
		sp++;
		compString++;
	}

	if(result == 0 && (spSize != compSize)){
		if(spSize < compSize){
			result = 1;
		}else{
			result = -1;
		}
	}

	sp = spCopy;
	compString = compCopy;
	return result;
}

void cleanseBuffer(){
	char eol = '\n';
	while((getchar()) != eol)
		;
}

// Can be used in combination with atoi to get integers from input.
char* getLine(int size){
	int n = 0;
	char c, eol = '\n', *buff, *returnBuff, *buffCopy;

	buff = malloc(size * sizeof(char) + 1);
	buffCopy = buff;

	printf("\nInput: ");
	while(c != eol){
		c = getchar();

		// Check if space availiable.
		if(n <= size){
			if(c == eol){
				*buff = '\0';
			}else{
				*buff++ = c;
				n++;
			}
		}else{
			if(c != eol){
				cleanseBuffer();
			}
			printf("\nToo much input, maximum is: %d\nPlease type again!\n", size);
			printf("\nInput: ");

			// Exception handling as the size+1:th input might be '\0' which would make the while loop end.
			if(n == size+1){
				c = ' ';
			}
			n = 0;
			buff = buffCopy;
		}
	}

	buff = buffCopy;
	n = strangLen(buff);
	returnBuff = malloc(n * sizeof(char) + 1);

	copyString(returnBuff, buff);
	free(buff);

	//Return result
	return returnBuff;
}
