# Para empezar

1. Crear un repo propio y clonarlo en un directorio local.
2. Entrar al directorio y hacer: 
`git remote add docentes https://git.exactas.uba.ar/ltaravilse/algo1-tpi`
3. Luego para traer los cambios
`git pull docentes master`
4. (Opcional) Desde CLion, ir a File -> Import Project, "Open Project".
 Una vez que termina la carga del proyecto, para correr los tests, 
 elegir "correrTests" desde la esquina superior derecha y 
 hacer click en el botón Play.
 
Pueden mantener su repositorio actualizado siempre ejecutando `git pull docentes master`

Si no desean usar Git (NO recomendado), pueden descargar desde aquí mismo el código fuente.

# Cómo correr los tests desde la línea de comandos (si no usan CLion)

1. mkdir build && cd build
2. cmake ..
3. make
4. ./tests/correrTests

Para volver a compilar, simplemente correr "make" de nuevo.

En caso de que no funcione correctamente la compilación, pueden borrar 
el directorio "build" y volver a realizar los 4 pasos.