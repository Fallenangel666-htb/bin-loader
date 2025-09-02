# Bin-Loader

Bin-Loader es una herramienta para ejecutar archivos .bin, como shellcode, en sistemas operativos Windows. Opera a bajo nivel, asignando memoria ejecutable y lanzando el contenido en un hilo separado, de manera nativa.

### ¿Qué la hace especial?
- 100% en C++: Utiliza librerías como windows.h para funciones de WinAPI como VirtualAlloc y CreateThread, iostream para entrada/salida, fstream para lectura de archivos y cstring para operaciones como memcpy. No tiene dependencias externas.
- Operación a bajo nivel: Asigna memoria con permisos de ejecución (PAGE_EXECUTE_READWRITE), copia el contenido del .bin y lo ejecuta en un hilo dedicado. Incluye prácticas de seguridad como limpiar el buffer original después de la copia.
- Soporte actual: Solo admite archivos locales (.bin en la máquina). No soporta descargas desde servidores HTTP. Se está trabajando en agregar soporte para archivos remotos.

Esta herramienta es para cargar y ejecutar binarios/shellcode en Windows. Adecuada para desarrolladores, investigadores de seguridad o entusiastas del reversing.

### Requisitos
- Sistema operativo: Windows (probado en versiones modernas).
- Compilador: C++ compatible con WinAPI (como Visual Studio o MinGW).
- No se requieren bibliotecas adicionales; todo es estándar.

### Cómo usarlo
1. Compila el código: Usa un compilador. Por ejemplo, con g++:
   ```
   g++ loader.cpp -o loader.exe
   ```
   (Incluye las flags necesarias para WinAPI si usas MinGW).

2. Ejecuta el loader: Pasa la ruta al archivo .bin como argumento:
   ```
   loader.exe <ruta_al_shellcode.bin>
   ```
   - El programa lee el .bin, lo carga en memoria ejecutable y lo lanza en un hilo.
   
   Notas importantes:
   - El .bin debe ser shellcode válido y compatible con la arquitectura (x86/x64).
   - Si el shellcode no retorna, ajusta el WaitForSingleObject según sea necesario.
   - Manejo de errores: Verifica argumentos, apertura de archivos, asignación de memoria y creación de hilos, mostrando mensajes en caso de fallos.

### Demo

la demo es ejecutar un .bin que me da una sesion sliver (c2)

Lo estoy probando en mi portatil OS fedora usando un podman (docker) de kali linux (debian) y ejecutando el .bin en la ultima version de windows 11 con el defender y firewalls activos en una maquina virtual de virtual box

<img width="1762" height="1011" alt="Captura de pantalla 2025-08-28 143003" src="https://github.com/user-attachments/assets/a6cd1a7c-2555-460b-95a2-881ce1071a70" />

No puedo subir un video de prueba porque es muy grande el video :/

### Limitaciones actuales
- Solo archivos locales: No soporta descargas HTTP/HTTPS (en desarrollo).
- Asume que el shellcode es auto-contenido y compatible; no maneja dependencias externas.

### Futuro desarrollo
- Soporte para archivos remotos (HTTP/HTTPS).
Para contribuir, reportar un bug o sugerir mejoras, abre un issue o un pull request en el repositorio. El feedback es aceptado.

Gracias por usar Bin-Loader. Si hay preguntas, deja un comentario.
