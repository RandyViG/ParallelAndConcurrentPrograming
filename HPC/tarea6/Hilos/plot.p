set title 'Pulso Cardiaco'
plot '../PulseSensor.dat' with lines
pause -1 "Hit any key to continue\n"

set title 'Ventana Hann (Hilos)'
plot 'ventanaHann.dat' with lines
pause -1 "Hit any key to continue\n"

set title 'Producto (Hilos)'
plot 'producto.dat' with lines
pause -1 "Hit any key to continue\n"

set title 'Autocorrelación (Hilos)'
plot 'resultado.dat' with lines
pause -1 "Hit any key to continue\n"
