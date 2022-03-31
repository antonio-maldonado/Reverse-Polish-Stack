/*
Antonio Maldonado Pinzon
Tarea 5
Estructura de datos
*/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"
#include <math.h>
using namespace std;

//Prototipos
int prioridad_actual(char);
int prioridad_pila(char);
string pila_polaca(string);
int calcular(string);
bool comprobar(string);

//Función principal
int main() {
  string buffer="",au,cadena;
  ifstream fileData( "aux.txt" );
	int acu=0;
	//Cuento cuantos caracteres tiene el archivo txt
	while(!fileData.eof()){
		fileData>>au;
		if(!fileData.fail()){
			acu++;
		}else
			break;
	}
  //Abro el archivo y guardo la expresión en un string
	freopen("aux.txt","r",stdin);
  char g;
	int i=0;
  cin>>g;
  for(int i=0;i<acu;i++){
		buffer+=g;
	  cin>>g;
	}
  cout << "Expresion a analizar : " << buffer<<endl;
	Stack S;
	bool flag=true;
	i=0;
	//Compruebo si la expresion tiene parentesis balanceados
	while(buffer[i]!='\0'){
		char c=buffer[i++];
		if(c=='(')
			flag=flag&&!push(&S,c);
		if(c==')')
			flag=flag&&!pop(&S,&c);
	}
	if(flag&&empty(&S))
		cout<<"Los paréntesis de la expresión están balanceados"<<endl;
	else{
		cout<<"Los paréntesis de la expresión NO están balanceados"<<endl;
		exit(1);
	}
	//Compruebo si la expresión está en forma de polaca inversa o no
	if(comprobar(buffer)==1){//Si no está en polaca inversa
		cadena=pila_polaca(buffer); //Paso de expresión infija a polaca inversa
		cout<<"La expresión NO está en forma polaca inversa"<<endl<<"En forma polaca inversa: ";
		cout<<cadena<<endl<<"Resultado: "<<calcular(cadena)<<endl<<endl;//Calculo el resultadi
	}else{//Si está en forma polaca inversa calculo el resultado
		cout<<"La expresión está en forma polaca inversa"<<endl<<"Resultado: "<<calcular(buffer)<<endl<<endl;
	}
return 0;
}

bool comprobar(string buffer){ //Funcion para comprobar si esta en forma infijo o polaca inversa
	int i=0,j=0;

	while(buffer[i]!='\0'){
		char c=buffer[i++];
		if(c>='0'&&c<='9'&&buffer[i]>='0'&&buffer[i]<='9'){
		j++;
		}
	}
	return (j==0)? true:false;
}

int prioridad_actual(char c){ //Funcion para decidir cual operador va primero
	int a;
	
	switch(c){
		case '^':
			a=3;	 break;
		case '*':
			a=2;	 break;
		case '/':
			a=2;	 break;
		case '+':
			a=1;	 break;
		case '-':
			a=1;	 break;
		case '(':
			a=5;	 break;
	}
return a;
}

int prioridad_pila(char c){//Funcion para decidir cual operador va primero
	int a;

	switch(c){
		case '^':
			a=3;	 break;
		case '*':
			a=2;	 break;
		case '/':
			a=2;	 break;
		case '+':
			a=1;	 break;
		case '-':
			a=1;	 break;
		case '(':
			a=0;	 break;
	}
return a;
}

string pila_polaca(string buffer){//Función para convertir de forma infija a polaca inversa
	Stack OP; //Pila que va a almacenar a los operadores
	int i=0,j;
	string cadena=""; //Cadena que almacenará la expresión convertida

	while(buffer[i]!='\0'){
		char c=buffer[i++],a;
		j=i;
		if(c>='0'&&c<='9'){//Si es un numero 
			cadena+=c; //Lo pongo en la cadena
		}else if(c=='+'||c=='-'||c=='*'||c=='/'||c=='^'||c=='('){//Si es un operador
			if(empty(&OP)){ //Si está vacío
				!push(&OP,c); //Lo meto en la pila
			}else{
				!pop(&OP,&a); //Saco el ultimo elemento de la pila
				if(prioridad_actual(c)>prioridad_pila(a)){ //Evaluo cual operador tiene mayor prioridad
					!push(&OP,a);
					!push(&OP,c);
				}else {
					!push(&OP,c);
					cadena+=a; //Meto el operador a la expresión
				}
			}
		}else if(c==')'){ //Si encuentro un )
			!pop(&OP,&a); //Saco los elementos de la pila
			while(a!='('){ //saco los elementos de la pila hasta encontrar el parentesis que lo cierra
				cadena+=a; //Voy metiendo los operadores a la expresión
				!pop(&OP,&a);
				}
		}
		if(buffer[j]=='\0'){ //Si se llegó al final de la cadena
			while(!empty(&OP)){ //Meter todos los operadores a la expresión
				!pop(&OP,&c);
				cadena+=c;
			}
		}
	}
return cadena;
}
int calcular(string cadena){ //Función que calcula la expresión 
Stack S; //Pila que va a almacenar la expresión y el resultado final

	for(unsigned int i=0;i<cadena.size();i++){ //Recorro toda la cadena
		if(cadena[i]>='0'&&cadena[i]<='9'){ //
			!push(&S,cadena[i]-'0'); //Meto el numero a la pila y restándole 48 lo convierto a un numero
		}else if(cadena[i]=='+'||cadena[i]=='-'||cadena[i]=='*'||cadena[i]=='/'||cadena[i]=='^'){ //Si es un operador
			char op1,op2,resultado;
			!pop(&S,&op1); //Saco los dos últimos números
			!pop(&S,&op2);
			switch(cadena[i]){ //Le aplico el operando a los dos números
				case '+':
					resultado=(op2)+(op1);
					!push(&S,resultado);
					break;
				case '-':
					resultado=(op2)-(op1);
					!push(&S,resultado);
					break;
				case '/':
					resultado=(op2)/(op1);
					!push(&S,resultado);
					break;
				case '*':
					resultado=(op2)*(op1);
					!push(&S,resultado);
					break;
				case '^':
					resultado=pow((op2),(op1));
					!push(&S,resultado);
					break;
			}
		}
	}
	char a;
	!pop(&S,&a); //Saco el último número de la pila el cual es el resultado final
return int(a); //Devuelvo el resultado final
}
