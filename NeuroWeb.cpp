#include "NeuroWeb.h"

NeuroWeb::NeuroWeb(void)
{
}

//По заданному количеству переменных функция сразу устанавливает длину вектора значений.
void NeuroWeb::setAmountOfVariables(int value)
{
	amountOfVariables = value;
	lengthInputVector = 1;
	lengthInputVector <<= amountOfVariables;

	memoryFile = "Memory/memory0" + to_string(amountOfVariables) + ".txt";

	initialStruct(); 
}

//Функция выделяет память для векторов входных значений, памяти. Задает имена нейронам.
void NeuroWeb::initialStruct()
{
	for (int i = 0; i < NUMOFNEURONS; ++i)
	{
		neuroWeb[i].input = new int[lengthInputVector];
		neuroWeb[i].memory = new int[lengthInputVector];
		neuroWeb[i].output = 0;
		neuroWeb[i].weight = 0;
	}
	neuroWeb[0].name = "T0";
	neuroWeb[1].name = "T1";
	neuroWeb[2].name = "Linear";
	neuroWeb[3].name = "Self-dual";
	neuroWeb[4].name = "Monotonic";
}

void NeuroWeb::memoryReset()
{
	ofstream file;
	file.open(memoryFile);
	for (int i = 0; i < NUMOFNEURONS; ++i)
	{
		for (int j = 0; j < lengthInputVector; ++j)
			file << "0 ";
		file << endl;
	}
	file.close();
}

void NeuroWeb::memoryRead()
{
	//Считываем память в массив. Если памяти нет - создаем пустую память и считываем ее.

	if (ifstream(memoryFile) == NULL)
		memoryReset();

	ifstream file;
	file.open(memoryFile);
	for (int i = 0; i < NUMOFNEURONS; ++i)
	{
		for (int j = 0; j < lengthInputVector; ++j)
			file >> neuroWeb[i].memory[j];
	}
	file.close();
}

void NeuroWeb::inputRead()
{
	//Сделать проверку на существование файла

	ifstream inputFile;
	inputFile.open("input.txt");
	for (int i = 0; i < NUMOFNEURONS; ++i)
	{
		for (int j = 0; j < lengthInputVector; ++j)
		{
			int temp;
			inputFile >> temp;
			neuroWeb[i].input[j] = temp * SENSITIVITY;
		}
	}
	inputFile.close();
}


NeuroWeb::~NeuroWeb(void)
{
}
