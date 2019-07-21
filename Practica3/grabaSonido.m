% Mario Ruiz Calvo. 27/05/17
function [y]=grabaSonido(fichero, frecMuestreo, resolucion,canales, duracion)
    % Crear un objeto de tipo audiorecorder para hacer la grabación.
    recorder = audiorecorder(frecMuestreo,resolucion,canales);
    % Grabar el sonido indicando la duración.
    recordblocking(recorder,duracion);
    % Convertir el sonido grabado en un vector con la señal, indicando 
    % el rango de valores que podrá tomar.
    y=getaudiodata(recorder,'double');
    % Almacenar la señal obtenida en el fichero indicado.
    audiowrite(fichero,y,frecMuestreo,'BitsPerSample',resolucion);
end

