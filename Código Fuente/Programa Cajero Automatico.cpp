#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // Incluimos conio.h para getch()
#include <time.h>  // Para obtener fecha y hora

#define MAX_USUARIOS 5
#define MAX_MOVIMIENTOS 3

// Estructura para almacenar la información del usuario
typedef struct {
	char nombre[20];
	int numero_cuenta;
	char contrasena[20];
	float saldo;
	char movimientos[MAX_MOVIMIENTOS][50];
	char fechas[MAX_MOVIMIENTOS][20]; // Nueva columna para almacenar fecha y hora
	int indice_movimientos;
} Usuario;

Usuario usuarios[MAX_USUARIOS];

int obtenerNumero(const char *mensaje);
void obtenerTexto(const char *mensaje, char *texto, int tamano);
void obtenerContrasena(const char *mensaje, char *contrasena, int tamano);
void inicializarUsuarios();
void mostrarMenuPrincipal();
void realizarRetiro(int indice);
void realizarDeposito(int indice);
void realizarTransferencia(int indice);
void estadoDeCuenta(int indice);
void exportarEstadoDeCuenta(int indice); // Nueva función
void registrarMovimiento(Usuario *usuario, const char *descripcion);
void registrarFechaMovimiento(Usuario *usuario);
int validarMultiploDe10(int cantidad);
int verificarContrasena(int indice);

int main() {
	inicializarUsuarios();
	int opcion, indiceUsuario = -1;
	
	do {
		system("cls");
		printf("**************************************\n");
		printf("*        BIENVENIDX AL POLIBANCO      *\n");
		printf("**************************************\n");
		
		printf("\nIngrese su número de cuenta: ");
		int numeroCuenta = obtenerNumero("");
		
		for (int i = 0; i < MAX_USUARIOS; i++) {
			if (usuarios[i].numero_cuenta == numeroCuenta) {
				if (verificarContrasena(i)) {
					indiceUsuario = i;
				} else {
					printf("\nContraseña incorrecta. Intente de nuevo.\n");
				}
				break;
			}
		}
		
		if (indiceUsuario == -1) {
			printf("\nNúmero de cuenta no válido. Intente de nuevo.\n");
			system("pause");
		}
	} while (indiceUsuario == -1);
	
	do {
		system("cls");
		printf("**************************************\n");
		printf("*        BIENVENIDX AL POLIBANCO      *\n");
		printf("**************************************\n");
		mostrarMenuPrincipal();
		opcion = obtenerNumero("Seleccione una opción: ");
		
		switch (opcion) {
		case 1:
			realizarRetiro(indiceUsuario);
			break;
		case 2:
			realizarDeposito(indiceUsuario);
			break;
		case 3:
			realizarTransferencia(indiceUsuario);
			break;
		case 4:
			estadoDeCuenta(indiceUsuario);
			break;
		case 5:
			exportarEstadoDeCuenta(indiceUsuario); // Nueva opción para exportar
			break;
		case 6:
			printf("\nGracias por usar el cajero automático.\n");
			break;
		default:
			printf("\nOpción no válida. Intente de nuevo.\n");
			system("pause");
		}
	} while (opcion != 6);
	
	return 0;
}

void inicializarUsuarios() {
	for (int i = 0; i < MAX_USUARIOS; i++) {
		sprintf(usuarios[i].nombre, "Usuario %d", i + 1);
		usuarios[i].numero_cuenta = 202501 + i;
		sprintf(usuarios[i].contrasena, "$0%dUsuario", i + 1);
		usuarios[i].saldo = 100.0f; // Saldo inicial
		usuarios[i].indice_movimientos = 0;
		for (int j = 0; j < MAX_MOVIMIENTOS; j++) {
			usuarios[i].movimientos[j][0] = '\0';
			usuarios[i].fechas[j][0] = '\0'; // Inicializamos las fechas
		}
	}
}

void mostrarMenuPrincipal() {
	printf("\n--- Menú Principal ---\n");
	printf("1. Retiro\n");
	printf("2. Depósito\n");
	printf("3. Transferencia\n");
	printf("4. Estado de Cuenta\n");
	printf("5. Exportar Estado de Cuenta\n");
	printf("6. Salir\n");
}

void realizarRetiro(int indice) {
	printf("\n--- Retiro ---\n");
	printf("1. $10\n2. $20\n3. $30\n4. $40\n5. $50\n6. Otra cantidad\n");
	int opcion = obtenerNumero("Seleccione una opción: ");
	float monto = 0;
	
	switch (opcion) {
	case 1: monto = 10; break;
	case 2: monto = 20; break;
	case 3: monto = 30; break;
	case 4: monto = 40; break;
	case 5: monto = 50; break;
	case 6:
		monto = obtenerNumero("Ingrese un monto múltiplo de 10: ");
		if (!validarMultiploDe10(monto) || monto <= 0 || monto >= 400) {
			printf("\nEl monto debe ser múltiplo de 10, mayor que cero y no superar los $400.00.\n Operación cancelada.\n");
			system("pause");
			return;
		}
		break;
	default:
		printf("\nOpción no válida.\n");
		system("pause");
		return;
	}
	
	if (monto > usuarios[indice].saldo) {
		printf("\nSaldo insuficiente.\n");
	} else {
		usuarios[indice].saldo -= monto;
		char descripcion[50];
		sprintf(descripcion, "RETIRO -$%.2f", monto);
		registrarMovimiento(&usuarios[indice], descripcion);
		registrarFechaMovimiento(&usuarios[indice]); // Registrar fecha y hora
		printf("\nRetiro realizado exitosamente. Saldo actual: $%.2f\n", usuarios[indice].saldo);
	}
	system("pause");
}

void realizarDeposito(int indice) {
	printf("\n--- Depósito ---\n");
	printf("1. $10\n2. $20\n3. $30\n4. $40\n5. $50\n6. Otra cantidad\n");
	int opcion = obtenerNumero("Seleccione una opción: ");
	float monto = 0;
	
	switch (opcion) {
	case 1: monto = 10; break;
	case 2: monto = 20; break;
	case 3: monto = 30; break;
	case 4: monto = 40; break;
	case 5: monto = 50; break;
	case 6:
		monto = obtenerNumero("Ingrese un monto múltiplo de 10: ");
		if (!validarMultiploDe10(monto) || monto <= 0) {
			printf("\nEl monto debe ser múltiplo de 10 y mayor a 0. Operación cancelada.\n");
			system("pause");
			return;
		}
		break;
	default:
		printf("\nOpción no válida.\n");
		system("pause");
		return;
	}
	
	usuarios[indice].saldo += monto;
	char descripcion[50];
	sprintf(descripcion, "DEPOSITO +$%.2f", monto);
	registrarMovimiento(&usuarios[indice], descripcion);
	registrarFechaMovimiento(&usuarios[indice]); // Registrar fecha y hora
	printf("\nDepósito realizado exitosamente. Saldo actual: $%.2f\n", usuarios[indice].saldo);
	system("pause");
}

void realizarTransferencia(int indice) {
	printf("\n--- Transferencia ---\n");
	int cuentaDestino = obtenerNumero("Ingrese el número de cuenta destino: ");
	if (cuentaDestino == usuarios[indice].numero_cuenta) {
		printf("\nError: No puede transferir a la misma cuenta.\n");
		system("pause");
		return;
	}
	
	int indiceDestino = -1;
	for (int i = 0; i < MAX_USUARIOS; i++) {
		if (usuarios[i].numero_cuenta == cuentaDestino) {
			indiceDestino = i;
			break;
		}
	}
	
	if (indiceDestino == -1) {
		printf("\nCuenta destino no válida.\n");
		system("pause");
		return;
	}
	
	float monto = obtenerNumero("Ingrese el monto a transferir: ");
	if (monto <= 0) {
		printf("\nEl monto debe ser mayor que 0.\n");
		system("pause");
		return;
	}
	
	if (monto > usuarios[indice].saldo) {
		printf("\nSaldo insuficiente.\n");
	} else {
		usuarios[indice].saldo -= monto;
		usuarios[indiceDestino].saldo += monto;
		char descripcionOrigen[50], descripcionDestino[50];
		sprintf(descripcionOrigen, "TRANSFERENCIA -$%.2f", monto);
		sprintf(descripcionDestino, "TRANSFERENCIA +$%.2f", monto);
		registrarMovimiento(&usuarios[indice], descripcionOrigen);
		registrarMovimiento(&usuarios[indiceDestino], descripcionDestino);
		registrarFechaMovimiento(&usuarios[indice]);       // Registrar fecha y hora en origen
		registrarFechaMovimiento(&usuarios[indiceDestino]); // Registrar fecha y hora en destino
		printf("\nTransferencia realizada exitosamente. Saldo actual: $%.2f\n", usuarios[indice].saldo);
	}
	system("pause");
}

void estadoDeCuenta(int indice) {
	printf("\n--- Estado de Cuenta ---\n");
	printf("Nombre: %s\n", usuarios[indice].nombre);
	printf("Número de Cuenta: %d\n", usuarios[indice].numero_cuenta);
	printf("Saldo: $%.2f\n", usuarios[indice].saldo);
	printf("\nUltimos Movimientos:\n");
	
	for (int i = 0; i < MAX_MOVIMIENTOS; i++) {
		int pos = (usuarios[indice].indice_movimientos - i - 1 + MAX_MOVIMIENTOS) % MAX_MOVIMIENTOS;
		if (strlen(usuarios[indice].movimientos[pos]) > 0) {
			printf("%d: %s - %s\n", i + 1, usuarios[indice].movimientos[pos], usuarios[indice].fechas[pos]); // Mostramos fecha y hora
		}
	}
	system("pause");
}

// Nueva función para exportar estado de cuenta a un archivo .txt
void exportarEstadoDeCuenta(int indice) {
	FILE *archivo = fopen("EstadoCuenta.txt", "w");
	if (archivo == NULL) {
		printf("\nError al crear el archivo.\n");
		system("pause");
		return;
	}
	
	fprintf(archivo, "--- Estado de Cuenta ---\n");
	fprintf(archivo, "Nombre: %s\n", usuarios[indice].nombre);
	fprintf(archivo, "Numero de Cuenta: %d\n", usuarios[indice].numero_cuenta);
	fprintf(archivo, "Saldo: $%.2f\n", usuarios[indice].saldo);
	fprintf(archivo, "\nUltimos Movimientos:\n");
	
	for (int i = 0; i < MAX_MOVIMIENTOS; i++) {
		int pos = (usuarios[indice].indice_movimientos - i - 1 + MAX_MOVIMIENTOS) % MAX_MOVIMIENTOS;
		if (strlen(usuarios[indice].movimientos[pos]) > 0) {
			fprintf(archivo, "%d: %s - %s\n", i + 1, usuarios[indice].movimientos[pos], usuarios[indice].fechas[pos]); // Escribimos fecha y hora
		}
	}
	
	fclose(archivo);
	printf("\nEl estado de cuenta se ha exportado exitosamente al archivo 'EstadoCuenta.txt'.\n");
	system("pause");
}

void registrarMovimiento(Usuario *usuario, const char *descripcion) {
	strncpy(usuario->movimientos[usuario->indice_movimientos % MAX_MOVIMIENTOS], descripcion, 50);
	usuario->indice_movimientos++;
}


void registrarFechaMovimiento(Usuario *usuario) {
	time_t ahora = time(NULL); // Obtiene la hora actual
	struct tm *tiempoLocal = localtime(&ahora); // Convierte a tiempo local
	
	// Guarda la fecha y hora en el índice correspondiente, usando el módulo para evitar desbordamiento
	strftime(usuario->fechas[usuario->indice_movimientos++ % MAX_MOVIMIENTOS], 20, "%d/%m/%Y %H:%M", tiempoLocal);
	
	// Incrementa el índice de movimientos
	
}

int validarMultiploDe10(int cantidad) {
	return cantidad % 10 == 0;
}

int obtenerNumero(const char *mensaje) {

	int numero;
	printf("%s", mensaje);
	while (scanf("%d", &numero) != 1 || getchar() != '\n') {
		printf("Error: Entrada no válida. Intente nuevamente.\n");
		while (getchar() != '\n');
		printf("%s", mensaje);
	}
	return numero;
}

// Nueva función para ingresar la contraseña con asteriscos
void obtenerContrasena(const char *mensaje, char *contrasena, int tamano) {
	printf("%s", mensaje);
	int i = 0;
	char ch;
	while ((ch = getch()) != '\r') {  // getch() lee sin mostrar el caracter
		if (ch == '\b' && i > 0) {    // Si se presiona backspace
			printf("\b \b");
			i--;
		} else if (ch != '\b' && i < tamano - 1) {
			contrasena[i++] = ch;
			printf("*");
		}
	}
	contrasena[i] = '\0';
	printf("\n");
}

int verificarContrasena(int indice) {
	char contrasenaIngresada[20];
	obtenerContrasena("Ingrese su contraseña: ", contrasenaIngresada, 20);
	return strcmp(usuarios[indice].contrasena, contrasenaIngresada) == 0;
}
