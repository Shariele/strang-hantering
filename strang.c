#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STRINGMAX 1024

int getLine(char *dummyChar, int size, int wantInt);
void concStr(char* sp, char* dummyChar, char* newString);
void addBlank(char* sp, char* newString);
int strangLen(char* sp);
int compStrang(char* sp, char* compString);
void flipStrang(char* sp);
void shiftStrangLeft(char* sp);
void shiftStrangRight(char* sp);
void commonToCapital(char* sp);
void copyString(char* sp, char* dummyChar);


int strangLen(char* sp){
	char c = '\0';
	int size = 0;

	while(*sp++ != c)
		size++;

	return size;
}

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
			*sp++;
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
	int spSize = strangLen(sp), compSize = strangLen(compString), commonLow = 97, commonHigh = 122, result, capitalLow = 65, capitalHigh = 90, c, o;
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

// Just nu funkar den precis som den ska, är lite lång och otymplig samt skulle kunna minimeras och göras bättre, har tyvärr dock inte tid utan blir ett 
// projekt i framtida kurser, tror den är överkurs som den är redan!
int getLine(char *dummyChar, int size, int wantInt){
	int n = 0, digit = 0;
	char c, eol = '\n';


	while(c != eol){
		c = getchar();

		//Want to have digits only.
		if(wantInt == 1){
			digit = isdigit(c); 

			//Check if space left
			if(n < (size)){
				if(c == eol){
					*dummyChar = '\0';
				}else{
					if(digit != 0){
						*dummyChar++ = c;
						n++;

					}else{
						if(c != eol){
							cleanseBuffer();
						}
						return -1;
					}
				}
			}else{
				if(c != eol){
					cleanseBuffer();
				}
				return -1;
			}
		// Regular character input.
		}else{
			// Check if space availiable.
			if(n < (size)){
				if(c == eol){
					*dummyChar = '\0';
				}else{
					*dummyChar++ = c;
					n++;
				}
			}else{
				if(c != eol){
					cleanseBuffer();
				}
				return -1;
			}
		}
	}
	//Return the number of entered characters.
	return n;
}