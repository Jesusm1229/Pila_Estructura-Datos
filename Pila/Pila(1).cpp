//JESUS MEDINA C.I:24225319 Asignación 1: Lectura de archivo XML

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>

using std::cout;
using std::string;
using std::endl;


enum Excepcion {
	UNDERFLOw = 0,
	OVERFLOw
};

const int maxi = 100;


class Pila {
	string S[maxi];
	int tope;
public:
	Pila() { tope = -1; }

	void Push(string x);
	string Pop();
	bool PilaVacia();
	string Tope();
	~Pila() {};
	
};

void Pila:: Push(string x) 
	{
	if (tope == (maxi - 1))
		throw std::overflow_error("OVERFLOW\n");
	else {
		tope++;
		S[tope] = x;
		}
	}

	//Funciones miembro de la clase Pila
string Pila:: Pop()
	{
	if (PilaVacia())
		throw std::underflow_error("UNDERFLOW\n");
	else
		tope--;
	return S[tope + 1];
	}


bool Pila::PilaVacia()
	{ 
	return (tope == -1); 
	}


string Pila:: Tope() 
	{ 
	return S[tope]; 
	}



	//Funciones 
	bool HayEspacio(string aux)
	{
		for (size_t i = 0; i < aux.length(); i++)
			if (aux[i] == ' ' && (aux[i + 1] != '>' && aux[i+1]!=' '))
				return true;
			
		return false;
	}


	bool EsCierre(string aux)
	{
		for (size_t i = 0; i < aux.length(); i++)
			if (aux[i] == '/')
				return true;
		return false;
	}



	bool TopeIgual(string aux, Pila p)
	{
		aux.erase(1, 1);
		if (p.Tope()==aux)
			return true;
		else return false;
	}


	//Eliminar espacio en blanco previo a la etiqueta 	
	string ElimEspPrev(string line) 
	{   
		
		//Tabulaciones
		line.erase(remove(line.begin(), line.end(), '\t'), line.end());

		//Mediante un espacio
		for (size_t i = 0; i < line.find('<'); i++)
				if (line[i] == ' ')
					line.erase(i, line.find('<'));

			return line;
		
	}


	//Eliminar espacio en blanco dentro de la etiqueta despues de la clave
	string ElimEspEtiqueta(string aux)
	{
		aux.erase(remove(aux.begin(), aux.end(), ' '), aux.end());
			return aux;
	}


	

	//Main
int main() {
	Pila S;
	string line, lineA;
	std::ifstream archive("entrada.xml");
	if (!archive) { std::cerr << "Error al leer archivo\n"; system("pause"); return 1; }

	
	try {
		
			while (std::getline(archive, line))
			{
				//Se elimina espacio previo a las etiquetas
				lineA = ElimEspPrev(line);
				
				string aux,auxA;
				size_t found = lineA.find('<');
				size_t found2 = lineA.find('>');
							
				

				while (found != string::npos)
				{
					//Se coloca en variable auxiliar lo que esté entre los signos <>, incluyendolos  
					aux = (lineA.substr(found, found2 + 1));					

					//Si hay espacio dentro de la etiqueta: dos palabras o más = Negado
					if (HayEspacio(aux))
						{ 
							std::cerr<< "No aceptado.\n";							
							system("pause");
							return 1; 
						}
					/*Se elimina el espacio despues de la clave de la etiqueta. Ej: <nombre     > , con el fin de ser reconocido por
					su cierre </nombre>*/

					auxA = ElimEspEtiqueta(aux);

					//Comprobación de si la etiqueta leída es de apertura o cierre.  
					if (EsCierre(auxA) == false)
						S.Push(auxA); 

					if (EsCierre(auxA))
						if (TopeIgual(auxA, S) == true)
							S.Pop();
						else if (TopeIgual(auxA, S) == false)
						{
							std::cerr << "No aceptado\n"; 
							system("pause"); 
							return 1;
						}
					
					/*Busqueda para etiqueta de cierre en misma linea de apertura a partir de la posición 
					exactamente siguiente del hallado */
					found = lineA.find(('<'), found + 1);
					found2 = lineA.find(('>'), found2 + 1);
				}

			}
			
			//Comprobacion Final. Si la Pila está vacía = ACEPTADO
			if (S.PilaVacia())cout << "Aceptado" << endl;
			else cout << "No aceptado" << endl;
			system("pause");

		}	
	catch (const Excepcion& ex) {
		if (ex == UNDERFLOw)
			std::cerr << "UNDERFLOW HAS BEEN CAUGHT" << endl;
		else
			if (ex == OVERFLOw)
				std::cerr << "OVERFLOW HAS BEEN CAUGHT" << endl;
		return -1;
		}
	catch (...) {
		std::cerr << "UNKNOWN EXCEPTION CAUGHT\nQUITTING...";
		return -2;
		}
			
		


	return 0;
}