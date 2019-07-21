% Mario Ruiz Calvo. 27/05/17
function [y]=grabaSonido(fichero, frecMuestreo, resolucion,canales, duracion)
    % Crear un objeto de tipo audiorecorder para hacer la grabaci�n.
    recorder = audiorecorder(frecMuestreo,resolucion,canales);
    % Grabar el sonido indicando la duraci�n.
    recordblocking(recorder,duracion);
    % Convertir el sonido grabado en un vector con la se�al, indicando 
    % el rango de valores que podr� tomar.
    y=getaudiodata(recorder,'double');
    % Almacenar la se�al obtenida en el fichero indicado.
    audiowrite(fichero,y,frecMuestreo,'BitsPerSample',resolucion);
end

