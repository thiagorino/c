
#include <stdio.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define lengthMax 6
#define capacityMax 10
/* Variáveis */
  int capacity = capacityMax; //capacidade da mochila
  int numberObjects = 0; //quantidade de objetos
  int objectWeight[lengthMax]; //peso dos objetos 
  int objectValue[lengthMax]; //valor dos objetos
  int value = 0; //valor máximo
  int sumWeights = 0; //soma dos pesos
  int table[lengthMax][capacityMax]; //tabela
void msg()
{
  printf("\t\t\t Problema da Mochila\n");
  printf("\n\t A capacidade da mochila foi definida como %i" , capacityMax - 1);
  printf("\n\t O número de objetos foi definido como %i", lengthMax - 1);
}
/*Função que imprime matriz*/
void print()
{
  for(int i = 1; i < lengthMax; i++)
  {
    printf("|  ");
    for(int j = 0; j < 10; j++)
    {
      if(table[i][j] < 10)
        printf("%i   ", table[i][j]);
      else
        printf("%i  ", table[i][j]);
      printf("|  ");
    }
    printf("\n");
  }
}
/*ordena pelo peso */
void orderByWeight(int * objectsWeight, int * objectsValues)
{
  int aux = 0;
  for(int i = 0; i < 6; i++)
  {
    for(int j = i+1; j < 6; j++)
    {
      if(objectsWeight[i] > objectsWeight[j])
      {
        aux = objectsWeight[i];
        objectsWeight[i] = objectsWeight[j];
        objectsWeight[j] = aux;
        aux = objectsValues[i];
        objectsValues[i] = objectsValues[j];
        objectsValues[j] = aux;  
      }
    }
  }
}
/*constroi tabela*/
int buildBag(int sumWeights, 
             int capacity, 
             int * objectWeight, 
             int * objectValue, 
             int parcialValue, 
             int object,
             int numberObject)
{
  if(object > numberObject) //condição de parada
  {
    return 1;
  }
  if(sumWeights == 0) //condição para zerar a primeira coluna
  {
    table[object][sumWeights] = 0;
    return buildBag(sumWeights + 1, capacity, objectWeight, objectValue, parcialValue, object, numberObject);
  }
  else if(sumWeights < capacity) //condição para continuar realizando a operação
  {
    if(objectWeight[object] <= sumWeights) // se o pesso do item for menor ou igual que a soma dos pesos
    {
      parcialValue = MAX(table[object-1][sumWeights], objectValue[object] + table[object-1][sumWeights - objectWeight[object]]); 
      table[object][sumWeights] = parcialValue;
    } 
    else //caso seja maior
    {
      table[object][sumWeights] = table[object-1] [sumWeights];
    }
    return buildBag(sumWeights + 1, capacity, objectWeight, objectValue, parcialValue, object, numberObject); //chama a função até a capacidade atingit o máximo
    }
  else //depois, zera a soma dos pesos e vai para o segundo objeto
  {
    return buildBag(0, capacity, objectWeight, objectValue, parcialValue, object + 1, numberObject);
  }
}
int main(void) {
  msg();
  int aux = 0; 
  /*preenche o vetor de peso e o vetor de objeto*/
  for(int i = 1; i < lengthMax; i++)
  {
    printf("\n-> Objeto %i", i);
    printf("\n Peso   -> ");
    scanf("%i", &aux);
    objectWeight[i] = aux;
    aux = 0;
    printf(" Valor  -> ");
    scanf("%i", &aux);
    objectValue[i] = aux;
    aux = 0;
  }
  orderByWeight(objectWeight, objectValue);
  buildBag(0, capacity + 1, objectWeight, objectValue, 0, 1, lengthMax-1);
  print();
  printf("\n\tConclusão");
  printf("\nO máximo valor possível é -> %i", table[lengthMax-1][capacityMax-1]);
  return 0;
}
