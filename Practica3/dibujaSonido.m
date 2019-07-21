% Mario Ruiz Calvo. 27/05/17
function [  ] = dibujaSonido( signal, nombre )
    % Si no se ha especificado el parametro nombre, por defecto sera
    % Sonido.
    if ~exist('nombre','var') 
        nombre='Sonido'; 
    end
    % Obtener el numero de canales de la señal.
    [~, n_canales] = size(signal);
    % Para cada canal mostrar la gráfica (en la misma ventana) y añadir un
    % título.
    for i = 1:n_canales
        subplot(n_canales,1,i)
        plot(signal(:,i));
        title(strcat(nombre,int2str(i)));
    end
end

