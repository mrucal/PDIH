% Mario Ruiz Calvo. 27/05/17
function [y]=reverse (signal)
    % Obtener el número de canales.
    [~, nc] = size(signal);
    % Almacenar en y el primer canal invertido.
    y = signal(end:-1:1,1);
    %Para cada canal:
    for i = 2:nc
        % Obtener el canal i.
        s = signal(:,i);
        % Invertir el canal i.
        s = s(end:-1:1,:);
        % Añadir el canal invertido como nueva columna de la señal y.
        y = [y s];
    end
end

