# C-snake
Implementación en lenguaje C del clásico juego Snake para entornos UNIX/Linux. Desarrollado con la biblioteca `ncurses`

## Requisitos del Sistema

Para compilar y ejecutar el proyecto es necesario disponer de un compilador de C y de la librería de desarrollo de `ncurses`:

* **GCC / Clang**
* **libncurses5-dev** o **libncursesw5-dev**

En distribuciones basadas en Debian/Ubuntu:
```bash
sudo apt update
sudo apt install build-essential libncurses-dev
```

---

## Compilación y Ejecución

Compilación mediante `gcc` vinculando la biblioteca `ncurses`:

```bash
gcc main.c -o snake -lncurses
```

Ejecución básica (color por defecto):
```bash
./snake
```

Ejecución con selector de tema de color:
```bash
# Opciones disponibles: -t [r (rojo) | b (azul) | g (verde) | y (amarillo)]
./snake -t g
```

---

## Controles del Juego

* **Flecha Arriba:** Mover hacia arriba
* **Flecha Abajo:** Mover hacia abajo
* **Flecha Izquierda:** Mover hacia la izquierda
* **Flecha Derecha:** Mover hacia la derecha
* **Ctrl + C:** Salir de la ejecución

---
