# Polibanco: Flujo de Trabajo en Git
Este repositorio contiene el desarrollo de un sistema de cajero automático para el banco ficticio "PoliBanco", implementado en C. El proyecto simula las operaciones típicas de un cajero automático, ofreciendo una experiencia intuitiva para los usuarios y cumpliendo con buenas prácticas de programación.
# Branching, Commits y Merge
Esta es una prueba.
Este repositorio sigue un flujo de trabajo organizado que permite el desarrollo eficiente de nuevas funcionalidades, corrección de errores y mejoras. A continuación, se describe el proceso de **branching**, **commits** y **merge** seguido en el desarrollo del proyecto, así como una descripción de las modificaciones realizadas.

## Estructura del Proyecto

La estructura básica del proyecto es la siguiente:

- **CodigoFuente/**: Contiene los archivos de código fuente del proyecto.
- **Documentos/**: Incluye el manual de usuario (`ManualUsuario.pdf`) y el manual técnico (`ManualTecnico.pdf`).
- **EstadoDeCuenta.txt**: Archivo de texto que almacena el estado de cuenta.
- **README.md**: Archivo con la explicación del flujo seguido.

## Flujo de Trabajo

### 1. **Ramas (Branches)**

Durante el desarrollo del proyecto, se crearon diferentes ramas para abordar tareas específicas. A continuación, se describen las ramas creadas, los cambios realizados y los merges realizados exitosamente:

### Ramas y Commits

#### **Branch: corrección-registrar-movimiento**

- **Commit:** Se modificó la función `registrarMovimiento` para corregir un problema donde las fechas no se imprimían correctamente en ciertos movimientos al visualizar el estado de cuenta. Se ajustó el uso de `strftime`, restando 1 en lugar de sumarlo, lo que solucionó el error de impresión.
  
- **Merge:** La fusión de esta rama con `main` se realizó sin conflictos, logrando una integración exitosa.

#### **Branch: mejora-estadocuenta**

- **Commit:** Se modificó la función `estadoDeCuenta` para mostrar la cuenta a la que se realizó la transferencia en los movimientos de tipo transferencia. También se implementó la impresión del saldo total al final de todos los movimientos.

- **Merge:** La fusión fue exitosa, sin conflictos, y las modificaciones fueron integradas correctamente.

#### **Branch: mejora-transferencia**

- **Commit:** Se mejoró la función `transferencia`, limitando la cantidad máxima de transferencia a $400. Además, se añadió un mensaje de error si se intentaba realizar una transferencia superior al monto establecido.

- **Merge:** La fusión no presentó conflictos y el funcionamiento del programa fue verificado.

#### **Branch: control-contrasena**

- **Commit:** Se añadió una validación para limitar los intentos de ingresar una contraseña incorrecta a tres intentos. Después de estos intentos fallidos, se bloquea la cuenta para mejorar la seguridad.

- **Merge:** La fusión fue exitosa sin conflictos.

#### **Branch: mejora-retiro**

- **Commit:** Se implementó un límite para la cantidad de retiro, estableciendo un máximo de $400. Esta mejora se integró sin problemas.

- **Merge:** No se presentó ningún conflicto al fusionar la rama.

#### **Branch: mejora-deposito**

- **Commit:** Se estableció un límite de depósito de $1000, evitando que los usuarios puedan ingresar cantidades mayores. La funcionalidad fue probada y no presentó inconvenientes.

- **Merge:** La fusión fue exitosa sin conflictos.

#### **Branch: exportar-archivo**

- **Commit:** Se modificó la función `exportarArchivo` para ofrecer mensajes más detallados cuando no se puede abrir o cerrar el archivo. También se añadió la funcionalidad para imprimir las fechas junto con los movimientos, asegurando la consistencia en la salida.

- **Merge:** La fusión se realizó sin conflictos.

### 2. **Conflictos y Resolución**

Durante el proceso de fusión, se presentó un pequeño conflicto al intentar fusionar la rama `mejora-transferencia` con `main`. El conflicto ocurrió en el archivo `Programa Cajero Automatico.cpp`, donde ambas ramas habían modificado la misma sección de código. La solución fue:

1. **Identificación del conflicto:** El conflicto ocurrió porque ambas ramas cambiaron el límite de la cantidad de transferencia en el mismo bloque de código.
   
2. **Resolución del conflicto:** Se revisaron los cambios y se optó por combinar ambas modificaciones: el límite de $400 establecido en `mejora-transferencia` y un mensaje de advertencia más claro sobre el monto máximo. El código fue actualizado para reflejar ambas necesidades.

3. **Pruebas:** Después de la resolución, se realizaron pruebas unitarias y de integración para verificar que la nueva lógica funcionara correctamente sin romper otras funcionalidades.

### 3. **Merge Final y Estrategia de Integración**

Las ramas se fusionaron en `main` de manera ordenada, con cada funcionalidad revisada y probada. Las fusiones a `main` se realizaron una vez que todas las características fueron verificadas y listas su ejecución.

### 4. **Evidencias de los Conflictos Resueltos**

Todos los conflictos fueron identificados y resueltos con éxito, manteniendo el flujo de trabajo eficiente y asegurando la estabilidad del proyecto.

## Conclusión

Este flujo de trabajo basado en ramas permitió realizar mejoras significativas en el proyecto, al tiempo que se mantuvo un control adecuado sobre el código fuente. El uso de ramas específicas para cada tarea, junto con pruebas exhaustivas y una correcta gestión de los merges, asegura que el proyecto pueda continuar su evolución sin inconvenientes.


