% Mario Ruiz Calvo. 27/05/17
function [y]=fadeOut(signal, frecMuestreo, duracion)
    % Obtener la duraci�n del desvanecimiento en segundos.
    seg_desvanecimiento = round(frecMuestreo * duracion);
    % Obtener el tama�o de la se�al.
    [n, nc] = size(signal);
    % Obtener el indice en el que empieza el desvanecimiento, restando la
    % duraci�n al tama�o de la se�al.
    indice = n - seg_desvanecimiento + 1;
    % Si la duraci�n del fadeOut es mayor a la duraci�n de la canci�n (el
    % indice donde empieza el fadeOut es menor que 0) el fadeOut comienza
    % al principio (indice 1) y la duraci�n del fadeOut es la duraci�n
    % completa (n).
    if indice <= 0 
        indice = 1; 
        seg_desvanecimiento = n;
    end
    % Crear un vector con valores de 0 a 1 del tama�o de la duraci�n del
    % fadeOut.
    l=linspace(0,1,seg_desvanecimiento);
    % Invertir el vector anterior para que los valores vayan de 1 a 0.
    l = l(end:-1:1);
    % Copiar la se�al de entrada en la de salida.
    y = signal;
    % Para cada canal modificar los valores correspondientes para hacer el fadeOut. Esto es
    % desde el indice en el que empieza el desvanecimiento hasta el final.
    % Se multiplican por el vector de valores de 1 a 0.
    for i = 1:nc
        y(indice:end,i)= signal(indice:end,i).*l';
    end
end

