% Mario Ruiz Calvo. 02/06/17
% 1. Leer un fichero .WAV con wavread (no muy largo, de menos de 20 segundos de duración).
clc;
fichero = 'mika_relax.wav';
signal = audioread(fichero);
fprintf(1,'Fichero leido!!');
fprintf(1,'\nPulse una tecla para continuar...\n');
pause;

% 2. Dibujar la forma de onda de los canales con “dibujaSonido”.
clc;
fprintf(1,'Mostrar grafica de %s\n', fichero);
pause;
dibujaSonido(signal,'Señal');
fprintf(1,'\nPulse una tecla para continuar...\n');
pause;

% 3. Obtener la información de la cabecera del fichero con “getCabeceraWav”.
clc;
fprintf(1,'Cabecera de %s:\n',fichero);
pause;
[ch, freq, resol, numBytes] = getCabeceraWav(fichero);
fprintf(1,'Canales: %d, Frequencia: %d, Resolucion: %d, NumBytes: %d\n',ch,freq,resol,numBytes);
fprintf(1,'\nPulse una tecla para continuar...\n');
pause;

% 4. Grabar un fichero de 2 segundos desde la tarjeta de sonido.
clc;
fprintf(1,'Grabar sonido:\n');
pause;
fprintf(1,'Grabando...\n');
grabacion = grabaSonido('sonido.wav', freq, resol, ch, 2);
fprintf(1,'Fin grabacion!!\n');
fprintf(1,'\nPulse una tecla para continuar...\n');
pause;

% 5. Insertar la señal grabada a los 3 segundos de la primera señal.
clc;
fprintf(1,'Insertar la grabacion a los 3s de %s:\n', fichero);
pause;
sg = insertaSonido(signal, grabacion, freq, 3);
fprintf(1,'Insertado!!\n');
fprintf(1,'\nPulse una tecla para continuar...\n');
pause;

% 6. Aplicar un eco del 40% con 0.5 segundos de retraso.
clc;
fprintf(1,'Aplicar un eco del 40 por ciento con 0.5 segundos de retraso:\n');
pause;
sge = eco(sg, freq, 0.5, 0.4);
fprintf(1,'Aplicado eco!!\n');
fprintf(1,'\nPulse una tecla para continuar...\n');
pause;

% 7. Aplicar un efecto de fadeout en el último segundo.
clc;
fprintf(1,'Aplicar un efecto de fadeout en el último segundo:\n');
pause;
sgef = fadeOut(sge, freq, 1);
fprintf(1,'Aplicado fadeout!!\n');
fprintf(1,'\nPulse una tecla para continuar...\n');
pause;

% 8. Dibujar Grafica de la señal resultante.
clc;
fprintf(1,'Mostrar grafica del signal resultante\n');
pause;
figure;
dibujaSonido(sgef,'SeñalMezcla');
fprintf(1,'\nPulse una tecla para continuar...\n');
pause;

% 9. Almacenar la señal obtenida como un fichero WAV denominado “mezcla.wav”.
clc;
fprintf(1,'Almacenar la señal en el fichero "mezcla.wav":\n');
pause;
% Si hay valores fuera del intervalo [-1 1] (debido a la función eco) los valores se truncan.
audiowrite('mezcla.wav', sgef, freq, 'BitsPerSample', resol);
fprintf(1,'Almacenado!!\n');
fprintf(1,'\nPulse una tecla para continuar...\n');
pause;

% 10. Reproducir al revés la señal obtenida.
clc;
fprintf(1,'Invertir la señal y reproducirla:\n');
pause;
sgefr = reverse(sgef);
reproduceSonido(sgefr, freq, resol);
fprintf(1,'\nPulse una tecla para continuar...\n');
pause;

