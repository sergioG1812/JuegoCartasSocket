# Pasos para jugar en red
primero que todo para emepezar a jugar cada jugador debe tener instalado la apliacion Visual Studio Community 2022
para instalarlo es muy sencillo:
1) ingresar al siguiente link: https://visualstudio.microsoft.com/es/vs/community
2)dar click en descargar: ![image](https://github.com/user-attachments/assets/93ce4549-872b-4b58-954d-2ef5dfe1ba91)
3)empezar la instalacion del programa
4)Luego de eso les aparecera esta ventana donde deberan marcar la opcion que aparece en pantalla ![image](https://github.com/user-attachments/assets/6fccc40d-0797-44d3-a506-cc0054bef189)
5)luego de instalarse, les aparecera esta ventana, le dan a la opcion señalada en rojo ![image](https://github.com/user-attachments/assets/f1bdfb1b-5769-40da-a8b6-f7a590fde863)
6)luego les aparecera esta opcion le dan a la opcion que señala la flecha roja ![image](https://github.com/user-attachments/assets/fefd9790-acec-4553-b70e-67ea6188f083)
NOTA: este paso lo debe hacer cada dispositivo, un proyecto que albergue la clase client pero no la server, y otra para la clase server sin agregar la clase client
7)para hacer mas facil la distincion le pueden poner al proyecto de la clase server, servidor y a la clase client, cliente
8)pueden borrar la clase main por defecto que nos muestra apenas creamos el proyecto
9)les aparecera en pantalla de la siguiente manera:![image](https://github.com/user-attachments/assets/c11f8455-01a9-4df0-a446-31423118fc84)
MUY IMPORTANTE: en donde aparece la flecha en rojo deben ir agregando los archivos que terminan.cpp y la flecha verde agreguen los archivos terminados en .h
 En el proyecto servidor deberan agregar todas las clases del proyecto excluyendo solamente la clase client.cpp ya que esa hace parte de el proyecto cliente
igualmente para el proyecto cliente deberan agregar todas las clases excluyendo la clase server.cpp
luego de haber agregado todas las clases deberan hacer lo siguente: ![image](https://github.com/user-attachments/assets/2184a3cd-f5d2-4769-9e26-ea8661a95605)
en la parte de arriba deberan de ternerlo de manera similar, luego deberan darle al boton verde rellenado
IMPORTANTE: deben iniciar siempre el proyecto server primero.
luego de haber iniciado server les aparecera lo siguente: ![image](https://github.com/user-attachments/assets/1f9bb103-fa6c-4643-82ea-4736944d1216)
lo que significa que esta esperando a que el proyecto cliente se conecte a el
# Para la clase cliente
Importante que entren al archivo client.cpp y hagan lo siguente:
1)Deben estar conectados a la misma red WI-FI
2) La pc con la clase server.cpp debera pasarles la direccion IP correspondiente a la conexion WI-FI
(si no saben donde se encuentra la direccion IP pueden hacer lo siguiente:
-ir a configuracion
-presionar la opcion WI-FI: ![image](https://github.com/user-attachments/assets/814196c1-780a-4be1-91d0-6fcaa30ba654)
-Presionar la opcion Propiedades: ![image](https://github.com/user-attachments/assets/5b5ff1f2-2ebd-4f6f-8f77-7a2b0db39823)
En ese lugar encontraran una opcion Llamada Direccion IPv4, la cual esa seria la direccion a utilizar).
Luego de obtener la direccion IP lo que van a hacer es dirigirse a client.cpp dentro del Visual Studio y encontraran el siguiente apartado: ![image](https://github.com/user-attachments/assets/416eb9db-ee82-4360-85fa-5ab471ba39c5)
ahi lo que deberan hacer es cambiar esa direccion IP por defecto, a la que les paso el PC que tiene el programa server.cpp
luego de eso, deberan oprimir el siguiente boton (El mismo que oprime Server para correr el juego): ![image](https://github.com/user-attachments/assets/8b8fb5e8-c452-45b4-8084-b9f948640278)
Y si hicieron todo correctamente les aparecera lo siguiente: ![image](https://github.com/user-attachments/assets/96a8df20-f6e3-48ae-9eaf-06ad2b8e66af)
Ya en el proyecto server se veria algo asi: ![image](https://github.com/user-attachments/assets/df84856c-966d-4753-8c68-add85e57c206)
Y podran empezar a jugar.
