% Mario Ruiz Calvo. 27/05/17
function [ canales, frecMuestreo, resolucion, numeroBytesMuestras ] = getCabeceraWav( fichero )
    % Obtener la cabecera del fichero wav, que se corresponden con los
    % primeros 44 bytes.
    % Abrir el fichero.
    fileID = fopen(fichero,'r');
    % Leer los 44 primeros bytes.
    cabecera = fread (fileID,44);
    % Cerrar el fichero.
    fclose(fileID);
    % Obtener los valores pedidos y convertirlos a decimal, extrayendo los datos de la cabecera
    % atendiendo al formato de la cabecera wav.
    canales = hexa_a_decimal(cabecera(23:24));
    frecMuestreo = hexa_a_decimal(cabecera(25:28)) ;
    resolucion = hexa_a_decimal(cabecera(35:36)) ;
    numeroBytesMuestras = hexa_a_decimal(cabecera(41:44)) ;
end

