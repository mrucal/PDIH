% Mario Ruiz Calvo. 02/06/17
function [y]=eco(signal, frecMuestreo, retraso, potencia)
    % Convertir el retraso en segundos en indice para una señal de
    % frecuencia frecMuestreo (se redondea para el caso en que el retraso
    % no es de tipo entero).
    indice_retraso = round(retraso * frecMuestreo);
    % Obtener el número de canales de la señal.
    [~, nc] = size(signal);
    % Obtener la señal de eco. Para ello se crea una matriz de 0 con tantas
    % filas como indique retraso (expresado en indices) y tantas columnas
    % como canales. A esta matriz se le añade la señal original
    % multiplicada escalarmente por el valor potencia.
    eco = [zeros(indice_retraso,nc) ; signal .* potencia];
    % Se añade al final de la señal original un vector de 0 como en la
    % matriz anterior para que ambas señales tengan la misma longitud y se
    % pueda hacer la suma.
    signal = [signal ; zeros(indice_retraso,nc)];
    % Sumar las dos señales para obtener la señal final con eco.
    y = eco + signal;
    % Normalizar la señal (en cada canal) para que no haya valores fuera del rango [-1,1]
    for i = 1:nc
        y(:,i) = ((2*(y(:,i)-min(y(:,i))))/(max(y(:,i))-min(y(:,i))))-1;
    end
end

