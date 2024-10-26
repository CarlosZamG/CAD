1. ¿Cuál es la salida del siguiente código?

```c
#include <stdio.h>

int main(){

    #pragma omp parallel{
        printf("Hola Mundo\n");
    }

}
```

- [ ] `Hola Mundo` una sola vez.
- [ ] `Hola Mundo` varias veces según el número de cores disponibles.
- [ ] Error en ejecución.
- [ ] Error de compilación.

<details>
<summary>Respuesta</summary>
<b>Error de compilación.</b>
<p>Para que el programa pueda compilarse correctamente, se debe colocar la llave en otra línea.</p>
</details>

2. ¿Cuál es la salida del siguiente código?

```c
#include <stdio.h>
#include <omp.h>

int main(){

    #pragma omp parallel num_threads(4)
    {
        #pragma omp parallel num_threads(4)
        {
            printf("Hola Mundo\n");
        }
    }

}
```

- [ ] `Hola mundo` 16 veces.
- [ ] `Hola mundo` 4 veces.
- [ ] `Hola mundo` una vez.
- [ ] Error de compilación.

<details>
<summary>Respuesta</summary>
<b>`Hola mundo` 4 veces.</b> 
<p>Esto debido a que por defecto el <em>paralelismo anidado</em> está deshabilitado en OpenMP.</p>
</details>


3. ¿Cuál es la salida del siguiente código?

```c
#include <stdio.h>
#include <omp.h>

int main(){

    #pragma omp parallel num_threads(4)
    {
        #pragma omp parallel num_threads(4)
        {
            printf("Hola Mundo desde el hilo %d\n", omp_get_thread_num());
        }
    }

}
```

- [ ] `Hola Mundo desde el hilo i` 16 veces con `0 <= i <= 16`.
- [ ] `Hola Mundo desde el hilo i` 4 veces con `0 <= i <= 4`.
- [ ] `Hola Mundo desde el hilo 0` 16 veces.
- [ ] `Hola Mundo desde el hilo 0` 4 veces.

<details>
<summary>Respuesta</summary>
<b>`Hola Mundo desde el hilo 0` 4 veces.</b>
<p>Esto debido a que por defecto el <em>paralelismo anidado</em> está deshabilitado en OpenMP. Así que falla en la en lanzamiento de nuevos hilos. Sin embargo, al anidar una segunda construcción paralela, cada hilo se ve así mismo como el hilo maestro, por lo que cada uno imprime su <em>`id`</em> igual a 0</p>
</details>

4. ¿Cuál es la salida del siguiente código?

```c

```

- [ ] .
- [ ] .
- [ ] .
- [ ] .

<details>
<summary>Respuesta</summary>

</details>
