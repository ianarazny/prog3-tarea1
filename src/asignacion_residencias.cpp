/*
  Módulo de implementación de `asignacion_residencias'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/asignacion_residencias.h"
#include <cstddef>


Asignacion asignarResidencias(nat m, nat *C, nat n, nat **hPrefs, nat **ePrefs)
{
  // Completar...
  // En principio todos los hospitales tienen plaza

  // Arreglo con la siguiente preferencia del hospital a la cual no se le ha propuesto
  nat* next = new nat[m];
  for (nat k = 0; k <= m - 1; k++)
    next[k] = 0;
  // En caso de hacer una propuesta, el hospital i propone a hPrefs[i, next[i]]
  // Si un estudiante no puede ser tomado, next[i] incrementa en 1

  // Un arreglo para saber si un estudiante está asignado a un hospital, cuál es el h
  int* hActual = new int[n];
  for (nat l = 0; l <= n - 1; l++){
    hActual[l] = -1;
  }
  //-1 significa que un estudiante esta desasignado, inicialmente todos los estudiantes estan desasignados
  // Si un estudiante e es asignado a un hospital h, eOcupado[e] = h;

  // Necesito poder comparar el orden de las preferencias de los estudiantes en orden cte.
  // tq: la preferencia del i esimo estudiante es el hospital j es de ranking[i][j]
  int** eRanking= new int*[n];
  for(nat i=0; i<=n-1; i++)
    eRanking[i] = new int[m];
  
  for (nat a = 0; a <= n - 1; a++){
    for (nat b = 0; b <= m - 1; b++){
      eRanking[a][ePrefs[a][b]] = b;
    }
  }
  // si la ePrefs[i][j] es la j esima preferencia del i esimo estudiante
  // entonces, ranking[i][j] devuelve qué número de preferencia tiene el estudiante i sobre el hospital j.

  Pila hospConC = crear_pila();
  for (nat i = 0; i <= m-1; i++)
    apilar(i, hospConC);

  // algoritmo principal

  Asignacion plaza = crear_asignacion();
  // for(int i=0; i<m-1, i++){
  while (!es_vacia_pila(hospConC)){
    if(C[cima(hospConC)]>0){

      int ePrio = hPrefs[cima(hospConC)][next[cima(hospConC)]];
      next[cima(hospConC)]++;
      if (hActual[ePrio] == -1){
        C[cima(hospConC)]--;
        hActual[ePrio] = cima(hospConC);
      }else{
        if (eRanking[ePrio][cima(hospConC)] < eRanking[ePrio][hActual[ePrio]]){
          //Las plazas del hospital actual del estudiante aumentan
          C[hActual[ePrio]]++;
          //next[cima(hospConC)]++; 
          
          //h decrementa sus plazas libres
          C[cima(hospConC)]--;


          int aux = hActual[ePrio];

          //next[cima(hospConC)]++;

          //Cambio el hospital actual del estudiante
          hActual[ePrio] = cima(hospConC);
          //Agrego el hospital actual a la pila
          apilar(aux, hospConC);

        
        } 
      }
    } else 
      desapilar(hospConC);
  }

  for(nat i=0; i<= n-1; i++){
    par pareja;
    pareja.hid = hActual[i];
    pareja.eid = i;
    insertar_par(pareja,plaza);
  }
  delete[] next;
  delete[] hActual;
  for(nat i=0; i<= n-1; i++)
    delete[] eRanking[i];
  delete[] eRanking;
  destruir_pila(hospConC);

  return plaza; // se debe retornar algo de tipo asignacion
}
