# GCC y la Compilación

Comúnmente solemos pensar un **compilador** como gcc como un *traductor que c convierte el código fuente en un programa ejecutable*. Sin embargo la realidad es que para pasar de nuestro código a un ejecutable, `gcc` realiza dos pasos:

1. **Compilación**: Convierte un archivo **`.c`** a código *object* que guarda en un archivo **`.o`** que **casi** es Lenguaje Máquina. Durante este proceso analiza que el programa no tenga errores de sintáxis.

Veamos como podemos visualizar este paso con gcc:

Primero supongamos que tenemos un archivo `hello_world.c` que queremos compilar:

```c
#include <stdio.h>

int main(){
    printf("Hola Mundo\n");

}
```
Para generar el archivo `.o` tenemos que ejecutar el comando `gcc -c hello_world.c`. Esto nos generará un archivo `hello_world.o`. Notemos que si queremos ver este archivo desde nuestra consola, el resultado no será muy agradable:

```sh
��UH��H�=��]�Hola MundoGCC: (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0GNU�zRx



RC
��      ello_world.cmain_GLOBAL_OFFSET_TABLE_puts
                                                 ��������
                                                         �������� .symtab.strtab.shstrtab.rela.text.data.bss.rodata.comment.note.GNU-stack.note.gnu.property.rela.eh_frame @X0
                                                     &[[1[
                                                          90f,B�R�j�e@�
                                                                       �8

        (/�t
```

Esto se debe a nuestro archivo `hello_world.o` no es un archivo de texto plano.

2. **Enlazamiento**: Este es el proceso en el que se combinan los códigos `object` necesarios para poder crear el ejecutable.

Para poder realizar este paso, basta con utilizar `gcc` y pasarle los archivos `.o` resultantes del proceso de compilación: En nuestro caso utilizamos `gcc hello_world.o`, lo que nos genera el ejecuutable `a.out`.

## Referencias

1. [Compiling and linking step by step](https://www.it.uc3m.es/pbasanta/asng/course_notes/gcc_compiling_linking_en.html)