#include <stdio.h>
#include <stdlib.h>
#include "dm.h"
#define NPASOS 1000
#define NFREQ_DUMP 20
#define NFREQ_INFO 100

void equilibrar(void);
void produccion(void);

int main(int argc, char *argv[]){

    equilibrar();
    produccion();
    return 0;
}

void equilibrar(void){
  double densidad = 0.8;
  double temp_inicio = 2.0;
  double temp = 1.0;
  double semilla = 1234;
  int numero_particulas = 800;
  int num_pasos = 2000;
  double dt = 0.005;
  int nfreq_dump = 2000;

  sys *sistema = system_alloc(numero_particulas, dt, nfreq_dump, NFREQ_INFO); // Se aloja memoria e inicializan variables
  crear_red_sc(sistema, densidad); // Se crea la red sc
  crear_velocidades_gaussiana(sistema, temp_inicio, semilla); // Se inicializan las velocidades de las particulas

  set_outputs(sistema, "equilibrio.dat"); // Se crea un archivo y se asigna a la estructura auxiliar
  agregar_termostato(sistema, temp, 500, 2000, 100); // Se agrega un termostato con temperatura 1
  simular(sistema, num_pasos);
  system_free(sistema);
}

void produccion(void){
  int numero_particulas = 800;
  double dt = 0.005;
  sys *sistema = system_alloc(numero_particulas, dt,
                              NFREQ_DUMP, NFREQ_INFO);

  leer_datos(sistema, "equilibrio.dat");

  set_outputs(sistema, "produccion.dat");
  simular(sistema, NPASOS);
  graficar_distribuciones(sistema);
  system_free(sistema);
}