% Mario Ruiz Calvo. 27/05/17
function [y]=reverse (signal)
    % Obtener el n�mero de canales.
    [~, nc] = size(signal);
    % Almacenar en y el primer canal invertido.
    y = signal(end:-1:1,1);
    %Para cada canal:
    for i = 2:nc
        % Obtener el canal i.
        s = signal(:,i);
        % Invertir el canal i.
        s = s(end:-1:1,:);
        % A�adir el canal invertido como nueva columna de la se�al y.
        y = [y s];
    end
end

