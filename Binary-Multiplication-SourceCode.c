/* UFUK GURBUZ. */

#include <stdio.h>
#include <ctype.h>		// Including for "atoi()" function ( converting "string" to "int" )

struct eleman {
	struct eleman* geri ;
	int icerik ;				// Struct for element
	struct eleman* ileri ;

};

typedef struct eleman Eleman;
typedef Eleman* ElemanPtr ;

struct liste {
	ElemanPtr bas;				// Struct for list
	ElemanPtr son;
};

typedef struct liste Liste ;
typedef Liste * ListePtr ;


ElemanPtr elemanOlustur( int icerik ){
	ElemanPtr eleman;
	eleman = malloc(sizeof(Eleman));
											// Creating element
	eleman->geri = NULL;
	eleman->icerik = icerik;
	eleman->ileri = NULL;
	
	return eleman;
}


ListePtr listeOlustur (){
	ListePtr liste ;
	liste = malloc(sizeof(Liste));
										 // Creating list
	liste ->bas = NULL;
	liste ->son = NULL;
	
	return liste;
}

void bitlereCevirveEkle(ListePtr liste, int deger, int basamak);
void basinaEkle ( ListePtr liste , ElemanPtr yeni);
void sonunaEkle ( ListePtr liste , ElemanPtr yeni);
void basindanSil ( ListePtr liste);
void listeyiCevir(ListePtr liste);
ListePtr multiplication(ElemanPtr bas1, int m, ElemanPtr bas2, int n);
ListePtr addition(ListePtr liste3, ListePtr liste4);
void duzYazdir(ListePtr liste);
int decimalSayiAl();
char * binarySayiAl();
int menu();


int main( )
 {
 	char x[10];
 	
 	while( strcmp(x,"0") != 0 ) {				// While x != 0 , loop continues
	 	
		ListePtr liste1 = listeOlustur();	// -> Creating list for first multiplier
	 	ListePtr liste2 = listeOlustur();	// -> Creating list for second multiplier
		//*********************
		int m,n;
		char c = menu();
		if( c == '1'){
			
			printf( "\nPlease, enter first decimal number : " );
			int number1=decimalSayiAl();			// Taking decimal first multiplier
		 	
			while( number1<0 ){			// If it is negative, taking again.
		 		printf("Please, enter first \"positive\" decimal \"maximum ten-digit\" number: ");
		 		number1=decimalSayiAl();
		 	}
		 	
		 	for(m=1 ; pow(2,m) <= number1 ; m++){ ; }	// ->>  2^i < number1 ("i" is bitwise digit number of first decimal number)
		 	
		 	printf( "Please, enter second decimal number: " );
		 	int number2=decimalSayiAl();		    // Taking decimal first multiplier
		 	
			 while( number2<0 ){		// If it is negative, taking again.
		 		printf("Please, enter second \"positive\" decimal \"maximum ten-digit\" number: ");
		 		number2=decimalSayiAl();
		 	}
		 	
		 	for(n=1 ; pow(2,n) <= number2 ; n++){ ; }	// ->>  2^j < number2 ("j" is bitwise digit number of second decimal number)
		 	
		 		
			bitlereCevirveEkle(liste1, number1, m);	// The first number is translated into bits and add to the list.
			bitlereCevirveEkle(liste2, number2, n);	// The second number is translated into bits and add to the list.
			
		}
		else{
			printf( "\nPlease, enter first binary number : " );
			char number[30]; 
			strcpy(number,binarySayiAl());
			
			for(m=0 ; number[m] != '\0'; m++ ){;}		// Number
			/////////////
			int c;
			for (c = 0; c < m; c++) {
				sonunaEkle(liste1, elemanOlustur( (number[c]-48) ? 1 : 0));			// Putting zeros and ones to list
	 		}
			//////////////
			printf( "\nPlease, enter second binary number : " );
			char number2[30]; 
			strcpy(number2,binarySayiAl());
			
			for(n=0 ; number2[n] != '\0'; n++ ){;}
			////////////////
			for (c = 0; c < n; c++) {
				sonunaEkle(liste2, elemanOlustur( (number2[c]-48) ? 1 : 0));		// Putting zeros and ones to list
	 		}
			/////////////////
			
			
		}
		printf("\n\nFirst Multiplier: ");
	 	duzYazdir(liste1);					// Printing the form of bits number for first multiplier
	 	printf("Second Multiplier: ");
	 	duzYazdir(liste2);					// Printing the form of bits number for second multiplier
	 	printf("\n");
	 	
		listeyiCevir(liste1);		// Reverses the first list
		listeyiCevir(liste2);		// Reverses the second list
		/////////////////
		
		ElemanPtr bas1 = liste1->bas;	// Defining head for list1 and list2
		ElemanPtr bas2 = liste2->bas;
		
			ListePtr liste3 = listeOlustur();	// Creating list3
			ElemanPtr bas3 = liste3->bas;		// Defining head for list3
			
			int i;
			for(i=1; i<=m; i++){
				int carpim = (bas1->icerik) * (bas2->icerik);	// Multiplicating for one digit and adding to list3
				basinaEkle(liste3, elemanOlustur(carpim));
				bas1 = bas1->geri;
			}
		
			int j;
		for(j=1;j<n;j++){
			bas1 = liste1->bas;
			bas2 = bas2->geri;
			ListePtr liste4 = multiplication(bas1, m, bas2, n);		// Multiplicating other digits and adding list4
			
			basinaEkle(liste3,elemanOlustur(0));
			int k;					// Adding one "0" to head of list3
			for(k=1;k<=j;k++)
				sonunaEkle(liste4,elemanOlustur(0));				// Adding "n" times "0" to last of lis4
		
			liste3 = addition(liste3,liste4);						// Then additioning list3 and list4 and equalizing to list3
			free(liste4);											// Releasing memory space of list4
		}
		//////////////////
		while( (liste3->bas->icerik) == 0){
			basindanSil(liste3);					// Deleting zeros from head of result
		}
		//////////////////
		printf("\nProduct Result: ");
		duzYazdir(liste3);											// Printing result of multiplication
	printf("-------------------------------------------------------------------------------");
	printf("\n\nPress any key to process. Enter \'0\' to exit: "); scanf("%s", x);		// Taking character for continue or exit

	//*************************
	}
	printf("\n! The program was terminated...");		// If the character is "0", exit from program.
	return 0;
 }

 void bitlereCevirveEkle (ListePtr liste, int deger, int basamak)		// ->> Converting decimal number to bits and creating list
 {
	 	int c, maske = 1 << basamak-1;
		
	 	for (c = 1; c <= basamak; c++) {
			sonunaEkle(liste, elemanOlustur(deger & maske ? 1 : 0));
	 		deger <<= 1;
	 	}

 }
 
 void basinaEkle (ListePtr liste, ElemanPtr yeni){			// ->> Adding to head of list
	if ( liste->son == NULL)
		liste->son = yeni;
	else
		liste->bas->geri = yeni;
	yeni->ileri = liste->bas;
	liste->bas = yeni;
}
 
 void sonunaEkle (ListePtr liste, ElemanPtr yeni){	// ->> Adding to last of list
	if (liste->bas == NULL)
		liste->bas = yeni;
	else
		liste->son->ileri = yeni;
	yeni->geri = liste->son;
	liste->son = yeni;
}

void listeyiCevir(ListePtr liste){					// ->> Turning way of list
 	ElemanPtr temp = liste->bas;
 	liste->bas = liste->son;
 	liste->son = temp;
}

ListePtr multiplication(ElemanPtr bas1, int m, ElemanPtr bas2, int n){		// Multiplication one list with one digit
	ListePtr liste4 = listeOlustur();			// Creating list4
	
	int i;
	for(i=1; i<=m; i++){
		int carpim = (bas1->icerik) * (bas2->icerik);
		basinaEkle(liste4, elemanOlustur(carpim));
		bas1 = bas1->geri;
	}
	return liste4;				// Returning list4
}

ListePtr addition(ListePtr liste3, ListePtr liste4){				// Addition lists
	listeyiCevir(liste3);		// Converting way of list3
	listeyiCevir(liste4);		// Converting way of list4
	
	ElemanPtr temp3 = liste3->bas;		// Copying head adrees of list3
	ElemanPtr temp4 = liste4->bas;		// Copying head adrees of list4
	
	ListePtr liste5 = listeOlustur();	// Creating list5
	int elde=0;
		while(temp3 != NULL && temp4!= NULL){			// Addition unless the end of list3 and list4
			
			int total = temp3->icerik + temp4->icerik + elde;
			if(total == 0){
				basinaEkle (liste5, elemanOlustur(0));
				elde=0;
			}
			else if(total == 1){
				basinaEkle (liste5, elemanOlustur(1));
				elde=0;
			}
			else if(total == 2){
				basinaEkle (liste5, elemanOlustur(0));
				elde=1;
			}
			else{	// If total == 3
				basinaEkle (liste5, elemanOlustur(1));
				elde=1;
			}

			temp3 = temp3->geri;
			temp4 = temp4->geri;
			
		}
		if( liste3->son->icerik + liste4->son->icerik + elde == 2 || liste3->son->icerik + liste4->son->icerik + elde == 3)		// Carry(out) = 1 condition
			basinaEkle (liste5, elemanOlustur(1));
			
		return liste5;			// Returning list5
}

void duzYazdir(ListePtr liste){
	ElemanPtr temp = liste->bas;						// ->> Printing list
	while(temp != NULL){
		printf("%d", temp->icerik);
		temp = temp->ileri;
	}
	printf("\n");
}

int decimalSayiAl(){								// Taking number
	char c, number[30];
	int i = 0;
	
	if((c=getchar()) == '\n'){
		c=getchar();
	}
	while( c != '\n' ){
		if( isdigit(c) ) 				// Special character control condition
			number[i++] = c;
		else{
			printf("\n! You have entered the wrong character. The program is terminating..."); // If there are speacial characters, the program terminates.
			exit(0);
		}
		c=getchar();		
	}
	number[i] = NULL;
	
	int sayi = atoi(number);	// Converting "string" to "int"
	
	return sayi;		// Returning number
}

char * binarySayiAl(){								// Taking number
	char c, number[30];
	int i = 0;
	
	if((c=getchar()) == '\n'){
		c=getchar();
	}
	while( c != '\n' ){
		if( c == '0' || c == '1' ) 				// Special character control condition
			number[i++] = c;
		else{
			printf("\n! You have entered the wrong character. The program is terminating..."); // If there are speacial characters, the program terminates.
			exit(0);
		}
		c=getchar();		
	}
	number[i] = NULL;
	
	char *returnValue = malloc(sizeof(char) * 30);		// Returning character array pointer
    strcpy(returnValue, number);
    
	return returnValue;	
}

void basindanSil (ListePtr liste){			// Deleting head of list
	liste->bas = liste->bas->ileri;
	if ( liste->bas == NULL)
		liste->son = NULL;
	else
		liste->bas->geri = NULL;
}

int menu(){
	printf("Enter \'1\' for Decimal operation, anything chracter for Binary Operation: "); 
	char c; 	
	if((c=getchar()) == '\n'){							// Menu
		c=getchar();
	}
	return c;
}
