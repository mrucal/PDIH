% Mario Ruiz Calvo. 27/05/17
function [y]=insertaSonido(s1, s2, frecMuestreo, tiempo)
    % Obtener el tama�o de la primera se�al, y el n�mero de canales de las
    % dos se�ales.
    [n1, nc1] = size(s1);
    [~, nc2] = size(s2);
    % Combrobar que las dos se�ales tienen el mismo n�mero de canales. En
    % caso contrario no se hace nada.
    if nc1==nc2
        % Obtener el indice en el que se va a insertar la segunda se�al.
        indice = round(frecMuestreo * tiempo);
        % Si el indice es mayor que el tama�o de la primera se�al la
        % segunda se�al se a�ade al final de la primera.
        if indice > n1
            y = [s1; s2];
        % En caso contrario la se�al resultante se compone creando una
        % matriz con s1 en el intervalo desde el inicio hasta el indice,
        % seguido de s2 y el resto de s1.
        else
            y = [s1(1:indice,:) ; s2; s1(indice+1:n1,:)];
        end
    end
end