set title 'Pulso Cardiaco'
plot '../PulseSensor.dat' with lines
pause -1 "Hit any key to continue\n"

set title 'Ventana Hann (Procesos)'
plot 'ventanaHann.dat' with lines
pause -1 "Hit any key to continue\n"


set title 'Producto (Procesos)'
plot 'producto.dat' with lines
pause -1 "Hit any key to continue\n"

set title 'Autocorrelación (Procesos)'
plot 'resultado.dat' with lines
pause -1 "Hit any key to continue\n"
